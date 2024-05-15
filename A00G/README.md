[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/jPyTaYok)
# a00g-devices-designs-diagrams

    * Team Number: 26
    * Team Name: Circuit Crusaders
    * Team Members: Binh Nguyen, Saurabh Parulekar
    * Description of hardware: 
      1. HP Pavilion Windows Gaming laptop, 15" 8GB i5
      2. Apple M2 Pro - Macbook 
    * Repository Link: https://github.com/ese5160/a00g-devices-designs-diagrams-circuit-crusaders

## 1. Device Description
The motivation for this project stems from the urgent need to enhance safety for two-wheeler vehicle riders. The helmet is designed to be a simple yet effective way to encourage riders to wear helmets for protection. The device will fit onto any helmet and use the rider's mobile device to receive navigational directions over Bluetooth; the rider will receive directions through two haptic motors placed on either side of the helmet(left and right). This method of indication is less intrusive and more subtle. The device will have turn lights visible to the vehicle behind the rider, indicating turns automatically/Manually from directions received from the rider's phone.

Along with turn signals, it will also have a brake light that will flash when the User stops and stays solid when the rider starts moving; an onboard accelerometer will detect the movement. The accelerometer system in the helmet can detect sudden movements and help sense changes in motion to spot crashes and prevent severe accidents quickly. Also, if someone tries to steal the helmet/bike, it senses unusual movements and triggers an alert to the User as a security feature. This helmet also has a Blind Spot Monitoring System, which utilizes IR-based Obstacle Sensors to detect objects outside the rider's direct line of sight. This feature aims to reduce accident risks caused by unseen vehicles or obstacles. The User can Activate/Deactivate Theft Detection, Control, and Personalize Turn Indicators, as well as brake light from a centralized dashboard; the dashboard will also feature vitals such as Theft detection alerts, Accelerometer data, and Crash detection alerts from the helmet.

## 2. Hardware Requirements Specification (HRS)
#### 2.1 Overview: 
This project combines different hardware parts to make a smart helmet safer and more interactive. Main features include a Directional Haptic Vibration Notification System for turn indication, a Blind Spot Monitoring System for obstacle detection, a precision Accelerometer System for motion tracking, Bluetooth and WiFi Modules for connectivity, and an Indication LED System for visual alerts. The system shall be driven by a SAMD21 Microcontroller, to create an advanced, interactive smart helmet with the users.

#### 2.2 Definitions, Abbreviations: 

+ Directional Haptic Feedback: Tactile feedback technology for direction indication.
+ WiFi Module (ATWINC1500): A network controller for wireless internet connectivity.
+ SAMD21 MicroController: A microcontroller used for managing various electronic components.
+ I2C: Inter-Integrated Circuit, a communication protocol.
+ UART: Universal Asynchronous Receiver-Transmitter, a communication protocol.
+ SPI: Serial Peripheral Interface, a communication protocol.
+ LED Strip: I2C interfaced array of APA102 LEDS.
+ IR distance sensor: Infrared distance sensor
+ OPAM: Operational Amplifier
  
#### 2.3 Functionality: 
* Directional Haptic Vibration Notification System: 
  - HRS 01 - This helmet shall have two haptic vibration sensors to indicate turning directions placed on either side of the helmet. These vibration sensors shall activate to indicate the appropriate turn direction when either a left or right turn signal is triggered. The motor driver shall communicate with the microcontroller over I2C.
* Blind Spot Monitoring System:
  - HRS 02 - Dual IR distance sensors to detect objects in the vehicle's blind spots, with a maximum detection range of 1 meter. IR distance sensor's analog output shall be given to an OPAM which will generate a digital signal depending on the distance selected
* Accelerometer System:
  - HRS 03 - 3-Axis Accelerometer shall be used to detect rider motion. It shall communicate with the microcontroller over SPI/I2C.
* Bluetooth Module: 
  - HRS 04 - The system shall use smartphone Bluetooth for data transmission and a Bluetooth module on our board for reception. The Bluetooth module shall communicate with the microcontroller over UART.
* Wifi Module: 
  - HRS 05 - This system shall incorporate the Atmel® SmartConnect ATWINC1500, which shall be used for uploading and downloading vitals and commands from a cloud dashboard respectively. it shall communicate with the microcontroller through SPI.
* Indication LED System: 
  - HRS 06 - The system shall include left and right turn LED indicators and a brake light LED strip. it shall communicate with the microcontroller via I2C. Left, Right and Brake LED strips shall be daisy-chained together and share the same I2C bus.
  
## 3. Software Requirements Specification (SRS)
#### 3.1 Overview:
This software is designed for a smart helmet, focusing on safety and interaction. It includes systems for vibration alerts when turning, sensors to detect objects in blind spots, tracking movement, and wireless communication for data sharing. The software ensures these components work in sync and aims to improve the safety and experience of bikers.
#### 3.2 Definitions, Abbreviations:

+ Navigational Data: real-time data received primarily from Google Maps.
+ Resolution: 16-bit analog-to-digital converter (ADC). That means it can differentiate between 65,536 (2^16) levels within this range.
+ LED Strip: I2C interfaced array of APA102 LEDS.
  
#### 3.3 Functionality: 
* Directional Haptic Vibration Notification System: 
  - SRS 01 - The software shall control the vibration motor via a motor driver controlled over I2C protocol to vary intensity based on distance from a turn and navigational data
  - SRS 02 - The software shall enable the appropriate vibration motor(left or right) based on directions received. it shall have different vibration patterns and intensity based on the type of turn and distance from a turn.
* Blind Spot Monitoring System:
  - SRS 03 - The software shall start recording obstacles from the Obstacle sensors when turn signals are active.
  - SRS 04 - The software shall also indicate to the user via vibration motors if there are obstacles present.
* Accelerometer System:
  - SRS 05 - The accelerometer shall continuously read all axes every 500ms with a resolution of 16 bits.
  - SRS 06 - The accelerometer shall be used to detect if the rider is stationary or in motion.
  - SRS 07 - The accelerometer shall be used to detect a crash and raise an alert.
  - SRS 08 - The accelerometer shall be used to detect unusual motion when the helmet is in lock mode.
* Bluetooth Module: 
  - SRS 09 - The software shall manage the Bluetooth module to establish an effective and reliable wireless connection between the helmet and a smartphone for data transmission for receiving navigational data only.
* Wifi Module: 
  - SRS 10 - The software shall manage the Atmel® SmartConnect ATWINC1500 WiFi module to enable wireless internet connectivity for IoT applications in the helmet.
* Indication LED System: 
  - SRS 11 - The system shall turn left and right LED strips to blink orange during a respective turn signal
  - SRS 12 - The system shall blink the brake LED strip when the rider is stationary and turn solid when in motion. stationary and motion states will be determined via the accelerometer.


## 4. Simple System Diagram
![Simple Block Diagram](https://github.com/ese5160/a00g-devices-designs-diagrams-circuit-crusaders/blob/final_changes_to_design/Design/Block_Diagrams/simple_block_diagram.png)

## 5. Detailed System Diagram
![Detailed Block Diagram](https://github.com/ese5160/a00g-devices-designs-diagrams-circuit-crusaders/blob/main/Design/Block_Diagrams/detailed_block_diagram.png)

## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
