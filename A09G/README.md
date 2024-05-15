[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/ay6zu56-)
# a09g-the-bootloader-waltz
```
  * Team Number: 26
  * Team Name: Circuit Crusaders
  * Team Members: Binh Nguyen, Saurabh Parulekar
  * Github Repository URL: https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders
  * Description of test hardware: (development boards, sensors, actuators, laptop + OS, etc):
      + 1. 2 Samw25 Xplained Pro Boards, SDCard Module
      + 2. Saleae Logic Analyzer
      + 3. HP Pavilion Windows Gaming laptop, 15" 8GB i5
      + 4. Apple M2 Pro - Macbook  
```
*You will be expanding on the codebase from A08G! Copy your A08G codebase into this repository before starting the assignment.*

## 1. Capture SD Card Comms
+ A block diagram of the hardware setup: 

![Block_Diagram](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/hardware_block_diagram.jpg)

+ A photo of your hardware connections between the SAMW25 Xplained dev board and the logic analyzer:

![Hardware_Setup](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/hardware_setup.jpg)

+  A screenshot of the a decoded message:
  
![Decode_Message](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/Saleae_Capture_SS.jpg)

+ A capture file of the SD card communication:
[The Capture File](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/SDCARD_Capture.sal)

## 2. Bootloader Design
+ A flow chart of your bootloader implementation:

![BootLoader_FlowChart](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/BootLoader_FlowChart.png)


+ The BootLoader is designed to implement and update the firmware of IoT devices. It plays a pivotal role in the lifecycle of devices by enabling software updates after deployment, which is crucial for fixing bugs, patching security vulnerabilities, and adding new features.

1. Initialization: The BootLoader prepares essential hardware components, including the SD card interface, serial console, and CRC (Cyclic Redundancy Check) calculation module.

2. Flag Check: 
+ The BootLoader checks for the presence of designated flag files (FlagA.txt or FlagB.txt) on an SD card at startup. If the file exists, it's deleted (f_unlink). Also, These flag files indicates which firmware binary files (TestA.bin or TestB.bin) is located and needs to be flashed onto the device's internal NVM (Non-Volatile Memory). This mechanism allows for flexible and condition-based firmware updates, and it can be crucial for phased rollouts, testing, or recovery scenarios.

3. Loop and Firmware Flashing:
+ Open Firmware Binary: The BootLoader opens the designated firmware binary file (TestA.bin or TestB.bin). This process reads the firmware file in 256-byte blocks. For each block, this process involves erasing the appropriate sections of the device's Non-Volatile Memory (NVM) and writing the new firmware data to it, and then performs a CRC check on the written data to ensure data integrity and confirm that the data has been correctly written and is not corrupted. It continues reading, erasing, writing, and performing CRC checks on firmware data chunks until the entire firmware file is processed. 


4. Jump to Application:	After successful flashing of the firmware, the BootLoader jumps to the newly written application code and starts its execution.

Overall, the BootLoader acts as an intermediary between the SD card and the microcontroller's NVM. It fetches the firmware update from the SD card, validates it, and programs it into the NVM, allowing the microcontroller to run the updated firmware upon reboot. It can adapt and enhance device functionality over time, the BootLoader framework ensures that IoT devices can remain secure, efficient, and up-to-date with the latest software improvements.


## 3. Bootloader Implementation

### Bootloader Code

[BootMain.c](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/Bootloader/src/BootMain.c)

### Bootloader in Action



https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/assets/57740824/8add1993-181f-447c-ada7-cf783397b929



## 4. Your Device Driver

1. Our functioning I2C device driver for Haptic Motor Driver:

[Haptic Driver Code](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/tree/main/Application/src/Haptic)

2. Screenshots of decoded I2C messages between the MCU and I2C device:

+ Capture 1:

![Haptic_Driver_Capture1](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/haptic_i2c_capture1.png)

+ Capture 2:
  
![Haptic_Driver_Capture2](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/haptic_i2c_capture2%202.png)

+ The capture file:[Haptic_Capture_File](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/haptic_i2c_capture.sal)

3. A photo of the hardware connection between the SAMW25 Xplained board and your I2C device: 

![Haptic hardware](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/haptic_hardware.png)

4. A video in your README.md of the device functioning:



https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/assets/57740824/d6ecb40a-b012-42e3-b4b1-c46b62320ae3



5. Block Diagram of the hardware

![Block Diagram of Hardware](https://github.com/ese5160/a09g-the-bootloader-waltz-t26-circuit-crusaders/blob/main/images%20and%20Captures/BlockDiagramI2C.drawio%20(1).png)


## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
