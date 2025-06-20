# Intorduction:
this project is a very simple way to make your gopro shoot smooth timelapses on the Bamboolab A1 mini printer using only an Esp 32 dev board, button, jumper wires and some 3D printed parts

# Stuf you need:
- any esp 32 dev board
- any cheap ass button 
- the generic square jumper wires
- some printed parts

# How it Works?

when the board starts, it looks for any connectable GoPro camers with bluetooth capabilities, if found than the board waits until the button is pressed.
on the button press the board sends a bluetooth command to start capture on the cammera, than it waits until the button is unpressed again and the cycle repeats.

# printing:
1. Poop deflector by: -fill if- modified to have a button attached needed for the capture cycle to begin
2. a Gopro mount (any version) attached to the filament cuttet arm, for steady shots
- can be printed with any material
- tolarences are adjusted for the A1 mini, may need adjustment for different printers



