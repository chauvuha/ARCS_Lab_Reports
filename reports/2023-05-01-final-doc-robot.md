# Final progress
- [x] Write a simple sketch to control the motors
- [x] Find the stop signal for each motor (modify by a little each time)
- [x] Remotely control the motor using the wifi access point
- [x] Create the wiring needed for the battery
- [x] Solder the black wire to the charging board with the heat shrink
- [x] One side of all three black wires needs to have dupont connector
- [x] Control the cardboard robot from wifi
- [ ] Make the cardboard box (put everything in) + the wheels attached (to be done when coming back)


# Schema:
 <img width="560" alt="Screen Shot 2023-03-26 at 11 16 52 AM" src="https://user-images.githubusercontent.com/79251745/227795826-fdba7b32-bdb4-47f2-a40b-6937271902b9.png">

# Charging instructions:
1. The microcontroller: Connected to the push-down button. Charged by a cable that is plugged in the computer. Solid yellow light = charging; flickering yellow light = not charging. Button looks pressed when not charging.
2. The motor driver: Connected to the three-way button and the battery. Charged by the charged board and plugged in to the wall. Red light = charging. 
  + To check if the motor driver is fully charged, follow these steps:
    + Use a multimeter and set it to DC mode.
    + Connect the black tip of the meter to the black wire of the battery, and do the same with the red tip.
    + Since this is a 3.7-volt battery, if the multimeter reading is greater than 3.7 volts, it indicates that the battery is fully charged.
    + If the tips of the battery are too small to touch the battery safety tips without touching each other, use the appropriate white header. Please refer to Professor Clark for the correct type of header to use.

# How to run the robot:
1. Assemble the robot according to the provided schema. 
2. Ensure that both the microcontroller and the battery for the motor driver are fully charged using the instructions mentioned earlier. While charging the microcontroller, open Arduino and upload the code from "2023-05-01-final-code-robot."
3. Connect to the access point named "yourAp."
4. Open your web browser and enter the following URLs:
    http://192.168.4.1/H to turn the LED on.
    http://192.168.4.1/L to turn the LED off.
    http://192.168.4.1/F to move forward.
    http://192.168.4.1/B to move backward.
    http://192.168.4.1/S to stop.
These URLs will appear as buttons already if you have the code from "2023-05-01-final-code-robot."
