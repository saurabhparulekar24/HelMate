[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/1emwVOMU)
# a04g-layout

    * Team Number: 26
    * Team Name: Circuit Crusaders
    * Team Members: Saurabh Sandeep Parulekar, Binh Nguyen
    * Description of hardware: (embedded hardware, laptop, etc):
       + 1. HP Pavilion Windows Gaming laptop, 15" 8GB i5
       + 2. Apple M2 Pro - Macbook  
    * Github Repository URL: https://github.com/ese5160/a04g-layout-t26-circuit-crusaders

## 1 PCB Hot Topics
1. If you wanted to run a trace with 1A of current on the top or bottom signal layer, how thick should it be on our circuit board? 10*C rise is acceptable. You should use the Layer Stack Manager to review critical stackup elements. Show how you got to this answer. 
+ Using PCB Trace Width Calculator: 

![Pic1](https://github.com/ese5160/a04g-layout-t26-circuit-crusaders/blob/main/image/trace_width.png)
   
2. What will happen if a PCB trace is thinner than needed for the current it carries?
+ PCB traces that are thinner than needed for the current they carry can lead to some significant problems. The traces can heat up excessively and damage themselves, and nearby components, and potentially cause circuit failure. Moreover, traces subjected to higher temperatures tend to have reduced reliability, a shorter operational lifespan, and even safety hazards like smoke or fire. Additionally, thinner traces can exacerbate electromagnetic problems and voltage drops should be a concern.


3. Describe the purpose of thermal reliefs in the context of PCB design.
+ In the context of PCB design, the purpose of thermal reliefs plays a vital role in manufacturing and reliability to distribute the heat during the soldering process, making it easier to solder and desolder components without compromising the integrity of the PCB. By creating a controlled connection between component pads and the copper planes, they prevent heat from being drawn away, which leads to better solder flow, better connections, and does not damage the board or lift the pads. 


4. In the Altium starter project schematics labeled FTDI and Memory, identify the design elements that protect against electrostatic discharge (ESD) and noise on the power and signal lines.
+  FTDI Schematic:
   + D2 is a protection device for the USB data lines, labeled PRT5V0U2X,215
   + C1, C2, C3, C4, C5, C6, C7: Capacitors for filtering noise on power and signal lines.
   + FB1: The ferrite bead (labeled 'BLM21PG221SN1') on the VBUS line acts as a filter for high-frequency noise, preventing it from reaching the rest of the circuit.
+ Memory:
  + ECLAMP2410PQTCT: This is an ESD protection device that provides both transient voltage suppression and it must be placed in series with the traces between the SD card holder and the MCU as mentioned in the note on the schematic. This protects the communication lines with the SD card.
  + C13: This is a bypass capacitor of 0.1uF, it is used to filter out noise on power lines, providing a stable voltage supply and reducing high-frequency noise.


5. Review the BQ24075 datasheet. What is the ESD rating?
+ The ESD rating of the BQ24075 is: 
  + Device HBM ESD Classification Level H2
  + Device CDM ESD Classification Level C3B


6. Review TI’s app note on Semiconductor and IC Package Thermal Metrics. What is RθJA and how does it affect our PCB layout? What factors affect RθJA?
+ RθJA, or Junction-to-Ambient thermal resistance, is a critical parameter in PCB design that measures the effectiveness of an integrated circuit in releasing heat to its surrounding environment.
+ RθJA influences PCB design by indicating how components are placed and managed for thermal dissipation. This thermal characteristic can make adjustments in the layout to prevent overheating. If RθJA value is high, this means the heat transfer is less efficient, the PCB may need a design that includes thermal management strategies, such as greater distances between heat-generating parts, spreading out heat-generating components, incorporating heat sinks, adding thermal relief, or use thermal vias to improve heat transfer to other layers or to the ambient environment. the durability and functionality of the electronic device need to keep components within their thermal limits, and RθJA is a key factor in that design consideration.
+ The factors affecting RθJA include:
  + PCB Design
  + Chip or Pad Size
  + Internal Package Geometrical Configuration
  + Altitude
  + External Ambient Temperature
  + Power Dissipation
  

## 2 PCB Layout
[PCB Layout](https://upenn-eselabs.365.altium.com/designs/114505C5-8A92-40C3-9C26-AFBB1F629568#design)

## 3 Team Logo
![Team Logo](https://github.com/ese5160/a04g-layout-t26-circuit-crusaders/blob/main/image/Logo.jpg)

## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
