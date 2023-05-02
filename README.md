# Purpose
The goal of this project was to rebuild a humanoid robot previously worked on by other graduate students at the University of North Carolina
at Charlotte. The robots previously ran on two 12V car batteries with 24V motors. In addition to restoring the functionality, the robot would
run on only one battery and the motors would be swapped to 12V equivalents. The robot was controlled with a PlayStation 3 controller which utilize
Bluetooth to convey inputs to the Arduino controlling the actuators and motors.

# Setup
### Get MAC address
1. Download *SixAxisPairTool* (See 1. in Supporting Libraries/Drivers)
2. Run the downloaded .exe file
3. Follow the install wizard to install the tool
4. Plug in the PS3 into your PC using a USB-A to Mini USB  cable
5. Run the installed *SixAxisPairTool*
6. The *SixAxisPairTool* will display the MAC address for the controller (save for later)

### Update ESP32 code
1. Open the ESP32PS3.ino file
2. Go to the setup function
3. Find the line starting with *Ps3.begin*
4. Pass the MAC address previously acquired as an argument in *Ps3.begin*
5. The final line should look something like this: *Ps3.begin("e8:48:b8:c8:20:00");*

### Upload Code
#### Arduino
1. Connect the USB-A to USB-B cable to the Arduino Mega
2. Open *ArduinoReceive.ino* in the Arduino IDE
3. Select Tools > Board > Arduino AVR Boards > Arduino Mega or Arduino 2560
4. Select Tools > Port > *COM port associated with connected Arduino*
5. Upload the code to the Arduino

#### ESP32
1. Connect the USB-A to Micro USB cable to the ESP32
2. Open *ESP32PS3.ino* in the Arduino IDE
3. Select Tools > Board > ESP32 Arduino > ESP32-WROOM-DA Module
4. Select Tools > Port > *COM port associated with connected ESP32*
5. Upload the code to the ESP32

# Operation
### Startup of Robot
1. Flip the Switch to the on position (Down)
2. Wait for the motor control boards to blink orange (10-15s)
3. Power on the PS3 controller associated with the robot
4. Wait for the controller to connect (1-5s)
5. The robot is now ready to be controlled

### Charging of Robot
1. Plug in extension cord to male connector located on the side
2. Turn switch to Charging position (see below for switch positions)
3. Verify that the charger indicates charging of the battery
     - Red LED indicates charging
     - Green LED indicates battery fully charged
     - Red blinking LED indicates battery not connected

### Switch positions
  - Up = Charging
  - Middle = Off
  - Down = On

# Design overview
### Re-design
The original robot was designed to run on 24V, utilizing two 12V car batteries. This design made it difficult to run the control boards and Arduino as they all relied on 12V. By downsizing the robot to run off 12V we eliminated some of the complexity of powering the individual components and reduced the overall weight by removing one of the car batteries. To accommodate the new power source the main drive motors, for the wheels, were replaced with equivalent 12V motors.  

The new power system was then wired in with the battery charger, to allow for easy re-charging with a simple extension cord. The 6-terminal DPDT switch was utilized to switch between standby, charging, and operating mode. The switch simply toggles whether the battery is connected to itself (standby), the charger (charging), or the components (operating). See the section entitled *Switch positions* above to see which position enables which mode.  

In addition to improving the electrical aspects we ensured that the mechanical aspects of the robot are in good working order. This meant adjusting some of the struts to ensure the torso is straight and stable during operation. In addition, the wheels needed to be re-aligned to aid in straight driving and prevent the chains from jumping off the sprockets. Lastly, we ensured that all joints were aligned properly and would allow for a smooth range of motion.


# Components
| Quantity  | Component |
| :-------------: | :-------------: |
| 1 | Arduino Mega 2560  |
| 1 | ESP32 Development Module |
| 1 | 12V Battery |
| 1 | Battery Charger |
| 1 | Roboclaw 2x60A |
| 2 | 12 Volt 100 Watt Motors |
| 6 | Pololu 18v15 motor controllers  |
| 6 | Concentric LACT2 Actuators |


# Schematic
![Schematic](/References/Schematic.png?raw=true "Optional Title")


# Supporting Libraries/Drivers
1. PS3 for ESP32 library: https://www.arduinolibraries.info/libraries/ps3-controller-host  
2. MAC address of PS3 Controller: https://drive.google.com/file/d/1REzlr4g94jwLLZkhJq9sQmbUKnL9tOMD/view  
3. Windows drivers for ESP32: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads  
     - Run the .inf file in main folder to install necessary drivers  
4. Roboclaw Library: https://www.basicmicro.com/downloads  
