#include <Arduino.h>
#include "BLEDevice.h"

#define ServiceCharacteristic(S, C) ThisClient->getService(S)->getCharacteristic(C)

static BLEDevice *ThisDevice;
static BLEClient *ThisClient = ThisDevice->createClient();
BLEScan *ThisScan = ThisDevice->getScan();
static BLEUUID ServiceUUID((uint16_t)0xFEA6);
static BLEUUID CommandWriteCharacteristicUUID("b5f90072-aa8d-11e3-9046-0002a5d5c51b");

static bool ItsC = true;
unsigned long TimeStamp;

static int buttonP = 25;

void ScanAndConnect(void)
{
  Serial.print("Connecting");
  ThisScan->clearResults();
  ThisScan->start(3);
  for (int i = 0; i < ThisScan->getResults().getCount(); i++)
    if (ThisScan->getResults().getDevice(i).haveServiceUUID() && ThisScan->getResults().getDevice(i).isAdvertisingService(BLEUUID(ServiceUUID)))
    {
      ThisScan->stop();
      ThisClient->connect(new BLEAdvertisedDevice(ThisScan->getResults().getDevice(i)));
      Serial.print("Conneced");
      noTone(LED_BUILTIN);
      return;
    }
  Serial.print("Fail");
}

void ConnectionCheck(void)
{
  if (!ThisClient->isConnected()) {
    Serial.println("Connection lost, attempting to reconnect...");
    digitalWrite(LED_BUILTIN, 0);
    tone(LED_BUILTIN, 1);
    ScanAndConnect();
    return;
  }
}

void setup(void)
{
  Serial.begin(115200);
  pinMode(25, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  tone(LED_BUILTIN, 1);
  ThisDevice->init("");
  ThisDevice->setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
  ScanAndConnect();
}

void loop(void)
{

  digitalWrite(LED_BUILTIN, 1);
  if (ItsC == true)
  {
    ServiceCharacteristic(ServiceUUID, CommandWriteCharacteristicUUID)->writeValue({0x02, 0x01, 0x01});
    Serial.println("Waiting");
    while (digitalRead(buttonP))
      ConnectionCheck(); //checks connection while idle, if your anoied by the cammera turning on on its own due to this, just put yeld() here instead

    ServiceCharacteristic(ServiceUUID, CommandWriteCharacteristicUUID)->writeValue({0x03, 0x01, 0x01, 0x01});
    Serial.println("Photo taken");
    ItsC = false;
  }else{
    Serial.println("pausing");
    digitalWrite(LED_BUILTIN, 0);
    while (!digitalRead(buttonP))
      yield();
    ItsC = true;
  }
     
}
