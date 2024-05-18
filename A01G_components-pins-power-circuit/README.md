[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/NIMa0T3C)
# a01g-components-pins-power

    * Team Number: 26
    * Team Name: Circuit Crusaders
    * Team Members: Binh Nguyen, Saurabh Parulekar
    * Description of hardware: 
      1. HP Pavilion Windows Gaming laptop, 15" 8GB i5
      2. Apple M2 Pro - Macbook
    * Git Repository Link: https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders

## 1 Component Verification & Simple BOM

## 2 Power Requirements
In the development of our helmet, careful consideration has been given to the power requirements to ensure both efficiency and reliability. The Bill of Materials (BOM) has been meticulously reviewed to ascertain the current draw for each component at their respective operating voltages. This review aids in the accurate sizing of our power regulators to handle the demands of the system without exceeding their capabilities. We've analyzed the current consumption for each component and added a 10% safety margin to accommodate any potential power surges during operation.

Here are the regulated power supplies' requirements:

+ 3.3V Supply: 
  + Total Current (Worst Case): 501mA
  + Total Current (Worst Case) with 10% Safety Margin: 550mA
+ 5V Supply: 
  + Total Current (Worst Case): 1136mA
  + Total Current (Worst Case) with 10% Safety Margin: 1300mA (rounded up from 1249.2mA for practicality)
  
These values ensure our regulators are capable of handling the system's power needs under all conditions. The attached table provides a detailed view of the power requirements, and these tables also are available in the BOM.

![Power Requirements](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/power_requirements.jpeg)


Webench - Ti Design: 
+ The DC/DC 3.3V regulator (TPS62082): 

![3.3V Regulator](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/62082.png)

![3.3V Chart](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/62082_charts.png)

+ The DC/DC 5V regulator (TPS61023): 

![5V Regulator](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/tps61023.png)

![5V Chart](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/61023_charts.png)

## 3 Power Architecture

![Power Architecture](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/power_architecture.png)

## 4 MCU Pin & Protocol Assignment
Software Components
![Interface Connections](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/Sercom_interface.png)

GPIO Pins
![GPIO Mux](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/images/GPIO_interface.png)

Pin and Protocol Configuration File: [Atmel Start File](https://github.com/ese5160/a01g-components-pins-power-circuit-crusaders/blob/main/Circuit_Crusaders.atstart)

## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
