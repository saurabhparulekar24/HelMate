[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/U-8Xix3F)

# a11-board-bringup

```
  * Team Number: 26
  * Team Name: Circuit Crusaders
  * Team Members: Binh Nguyen, Saurabh Parulekar
  * Github Repository URL: https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders
  * Description of test hardware: (development boards, sensors, actuators, laptop + OS, etc):
      + 1. 2 Samw25 Xplained Pro Boards, SDCard Module, LED Strip
      + 3. HP Pavilion Windows Gaming laptop, 15" 8GB i5
      + 4. Apple M2 Pro - Macbook  
      + 5. Our Own Board, ESD Strap, Oscilloscope, ELoad, Multimeter, Soldering Station
```

## 1. Visual Board Inspection & Photograph

The correct components seem to be soldered, the board looks like the 3D model. components seem to be placed correctly no rotated components and no solder bridging.

![Board Photos](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/top_photo_board.jpg)

![Board Photos 2](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/from_wifi_board.jpg)

![Board Photos 3](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/from_charger_board.jpg)

## 2. Power System Evaluation

### 2.1 Distinct Power Modes

Our board has two DC-DC Converters, one 3.3V(Buck) and one 5V(Boost) The Distinct Power Modes in the PCBA are

1. Unregulated Battery is only connected, voltage range from 3.2V to 4.2V
2. Regulated USB only, ranges from 4.85V to 5.25V
3. Both unregulated battery and USB are connected, voltage ranges from 4.85 to 5.25V.

### 2.2 Power Regulation Evaluation

My Power system consists of one Buck Converter of 3.3V and another Boost converter of 5V. Disconnected JP13, JP14, JP17, JP18. Each converter has an input and output test point. Soldered cables to TP45(in), TP50(out) for Buck and TP42(in), TP46(out) for Boost and Ground on TP41.

![Power system](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Power%20system.png)

![Setup](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Board_Connections.jpg)

#### Buck Converter

##### Buck Startup Transient

![Buck Startup](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/buck/Buck_2.png)

The buck takes around 13.32ms to startup, we do not see an overshoot or undershoot, and regulation is quick

##### Buck Steady State

![Buck Steady](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/buck/Buck_1.png)

Average: 3.14V

Minimum Voltage: 3.05V

Maximum Voltage: 3.25V

Voltage Ripple: 6.36%

#### Boost Converter

##### Boost Startup Transient

![Boost Startup](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/boost/Boost_Transient2.png)

The Boost takes around 3.8ms to start

##### Boost Steady State

![Boost Steady](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/boost/Boost_SteadyState.png)

![Boost Steady min max](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/boost/Boost_MinMaxVoltage.png)

Average: 5.01V

Minimum Voltage: 5.06V

Maximum Voltage: 4.96V

Voltage Ripple: 2.01%

For the Buck, we observed that the voltage output was a bit less noisy and the ripple voltage was around 6% which is high, for the Boost converter we got a clean output with less noise and expected voltage. We did not see any failures during the test. The startup transient for both the converters looked good, no overshoot undershoot or ringing was observed. Overall the outputs and working were within specification

### 2.3 Load Testing

In our setup, we have a Boost which powers the majority of the components on boards such as LED strips (upto 600mA), Haptic Motors, and Distance sensors. Hence we will be doing a load test on the Boost and check if it supports all the components.

![Eload Setup](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Eload%20Setup.jpg)

Voltage Measured at the Eload

![Eload Table](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/E-LoadChart.JPG)

No Issues were encountered as such, and did not see any significant voltage drop from the Boost, the boost was able to handle and supply enough current.

### 2.4 Thermal Image

To get the maximum temperature that would be possible ran the Boost converter at 1300mA load for 5 minutes

![Thermal Image](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Thermal.jpeg)

![Closeup](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/5V_1300mA_Load_Closeup.jpeg)

## 3. Programming

![Photo of Debugger](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Programmer_Board.jpg)

![Target Voltage](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Target_Voltage.png)

No Issues were encountered here

## 4. Peripheral Evaluation

### 4.1 Debug LED



https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/assets/57740824/1eaa0858-4b7b-4b6c-bc54-8012c0e48ed2



### 4.2 Debug Button



https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/assets/57740824/37b5466d-9eca-4586-8707-415520fc05f5



### 4.3 UART Communication

![CLI](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/CLI.gif)

### 4.4 SD Card

![SDCARD](https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/blob/main/Images/Sdcard.png)

### 4.5 I2C Device

https://github.com/ese5160/a11g-board-bringup-t26-circuit-crusaders/assets/57740824/1eb0d85d-f620-4903-b214-c9a5c1fe899e






## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
