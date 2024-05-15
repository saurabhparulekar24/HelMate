[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Gk8hE5zE)

# a12g-firmware-drivers

```
    * Team Number: 26
    * Team Name: Circuit Crusaders
    * Team Members: Binh Nguyen, Saurabh Sandeep Parulekar
    * Github Repository URL:  https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders
    * Description of test hardware: (development boards, sensors, actuators, laptop + OS, etc)
      + 1. Our board, LED Strip APA102C, Onboard Haptic Drivers, 2 IR Sensors GP2Y0A21YK0F, LIS2DH Accelerometer
      + 2. Lots of VSCOde and Github
      + 3. HP Pavilion Windows Gaming laptop, 15" 8GB i5
      + 4. Apple M2 Pro - Macbook
```

*You will be expanding on the codebase from the previous assignment! Copy your previous assignment's codebase into this repository before starting the assignment.*

## 1. Sensor Drivers

### IR Distance Sensor

#### Block Diagram

![IR Sensor](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/IR_Sensor.drawio.png)

#### Code

Link: [IR Sensor Code](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/tree/main/Application/src/IRDistanceSensor)

#### Photo of Hardware

![IR Sensor Hardware Setup](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/IR_Sensor.png)

#### Video

[Video Link](https://drive.google.com/file/d/1-NeuIHf8TISOKZClrjXXN706EgbNKxkI/view?usp=sharing)

### LED STRIP:

#### Block Diagram


![LED Strip](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/LED_Strip.png)

#### Code


Link: [LED_Strip_Code](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/tree/main/Application/src/LED_Strip)

#### Photo of Hardware

![LED_Strip_Hardware](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/LED_Hardware.png)

#### Video

https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/assets/54522586/16359bd3-98e9-4316-b1d7-5a1071ce022a

### 3-AXIS ACCELEROMETER

#### Block Diagram

![Accelerometer](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/Accelerometer.png)

#### Code

We are using the LIS2DH Accelerometer on board, I had kept LSM6DSO as a backup hence drivers for both are present. The particular driver can be selected from the [imu.h](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/Application/src/IMU/imu.h) file. This makes the code modular and resilient.

Link: [Accelerometer_Code](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/tree/main/Application/src/IMU)

#### Photo of Hardware

![Accelerometer_Hardware](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/Accelerometer_hardware.png)

#### Video

https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/assets/54522586/9464cd6c-5eb7-45e6-b412-7ab3d1e62686

## 2. Actuator Drivers

### Haptic Motors

#### Block Diagram

![Haptic Block Diagram](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/Haptic_BD.drawio.png)

#### Code

[Driver Link](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/tree/main/Application/src/Haptic)

#### Photo of Hardware

![On Board Haptic Driver](https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/blob/main/images/Haptic_Hardware.png)

#### Video

https://github.com/ese5160/a12g-firmware-drivers-t26-circuit-crusaders/assets/54522586/5166da47-01c6-48fd-a1a6-de525667d0f4


## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
