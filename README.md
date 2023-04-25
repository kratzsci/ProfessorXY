# ProfessorXY

##Purpose
The goal of this project was to rebuild a humanoid robot previously worked on by other graduate students at the University of North Carolina
at Charlotte. The robots previously ran on two 12V car batteries with 24V motors. In addition to restoring the functionality the robot would 
run on only one battery and the motors would be swapped to 12V equivalents. The robot was controlled with a PlayStation 3 controller which utilize
Bluetooth to convey inputs to the Arduino controlling the actuators and motors.

├── Actuators             # Folder that contains code for the Actuators
│   ├── Actuators.ino     # Code for all 5 actuators


PS3 for ESP32 library: https://www.arduinolibraries.info/libraries/ps3-controller-host
MAC address: https://drive.google.com/file/d/1REzlr4g94jwLLZkhJq9sQmbUKnL9tOMD/view
Windows drivers: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads
	run the .inf file in main folder