# ProfessorXY

## Purpose
The goal of this project was to rebuild a humanoid robot previously worked on by other graduate students at the University of North Carolina
at Charlotte. The robots previously ran on two 12V car batteries with 24V motors. In addition to restoring the functionality, the robot would 
run on only one battery and the motors would be swapped to 12V equivalents. The robot was controlled with a PlayStation 3 controller which utilize
Bluetooth to convey inputs to the Arduino controlling the actuators and motors.


## Re-design
### Battery
- Two 12v -> One 12v
### Motors
- 24v -> 12v
### Charging
- Extension cord
### Switch
- On, Off, and charging mode
### Tighten mechanical parts
1. Straighted up the body
2. Fixed misaligned wheels
3. Checked every joint


## Switch positions
- Up: Charging \
- Middle: Off \
- Down: On


## Running ProfessorX
1. Turn switch from Off position to On position.
2. Wait for approximately 10 seconds.
3. Connect controller.
4. You should now be able to move the robot. 


## Charging ProfessorX
1. Turn switch to charging position.
2. Verify red LED on Battery Charger is on, then it is in charging mode.


## Components
| Quantity  | Component |
| :-------------: | :-------------: |
| 1 | Arduino Mega 2560  |
| 1 | 12V Battery |
| 1 | Battery Charger |
| 1 | ESP32 Development Module |
| 1 | Roboclaw 2x60A |
| 6 | Pololu 18v15 motor controller  |
| 6 | Concentric LACT2 Actuator |


## Schematic
![Schematic](/Images/Schematic.png?raw=true "Optional Title")


## Supporting Libraries/Drivers
1. PS3 for ESP32 library: https://www.arduinolibraries.info/libraries/ps3-controller-host  
2. MAC address of PS3 Controller: https://drive.google.com/file/d/1REzlr4g94jwLLZkhJq9sQmbUKnL9tOMD/view  
3. Windows drivers for ESP32: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads  
  -Run the .inf file in main folder to install necessary drivers  
4. Roboclaw Library: https://www.basicmicro.com/downloads  
