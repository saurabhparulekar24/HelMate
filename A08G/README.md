[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/etSYLxW4)
# a08g-comm-protocols

    * Team Number: 26
    * Team Name: Circuit Crusaders
    * Team Members: Binh Nguyen, Saurabh Parulekar
    * Github Repository URL: https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders
    * Description of test hardware: (development boards, sensors, actuators, laptop + OS, etc):
        + 1. 2 Samw25 Xplained Pro Boards
        + 2. Saleae Logic Analyzer
        + 3. HP Pavilion Windows Gaming laptop, 15" 8GB i5
        + 4. Apple M2 Pro - Macbook  

*For Q4, you will be expanding on the codebase from A07G!*

## 1. UART: Universal Asynchronous Receiver Transmitter

1. How does UART synchronize data reception and transmission? 

+ The UART protocol is an asynchronous communication method. This means that the sender and receiver devices do not necessarily have to be operating on the same clock. The UART packet has a predetermined structure for both the transmitter and receiver. It consists of a start bit, data bits, a parity bit, and stop bits. To establish successful communication, both devices must have the same configuration for the baud rate (in our experiment, set at 9600), the number of data bits (either 8 or 9), the type of parity (odd or even), and the number of stop bits (either 1 or 2).

2. How is hardware flow control implemented in UART?

+ In addition to the standard transmit (TX) and receive (RX) lines, RTS flow control uses the Request-to-Send (RTS) and Clear-to-Send (CTS) lines. The active-low RTS and CTS signals work together to control transmission flow. When one device wishes to transmit data, the device pulls the RTS line low, which signals the slave device, through its CTS input, to begin to monitor its RX input. When the slave device is ready to accept the data, it pulls its RTS line low, informing the master, through its CTS line, to begin sending data. Once the transaction has been completed, the master device pulls the RTS line high.

3. Which part of the data is sent first, LSB or MSB?

+ From the Logic Analyzer, we see that LSB is sent first.

### Code

The code for all Communication protocols is written in one project itself, a selector variable `select_interface` is present in main which decides which protocol will be used for bi-directional communication.
[Code](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/tree/main/CommProtocols_A08G)

### Video Of Setup



https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/assets/57740824/0021920e-6ba6-47b0-984b-cb2af155c451



### Screenshot of Capture and Saleae Capture of Packets UART

#### From Saurabhs to Vincents Board

![S to V](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/UART_S_to_V.png)

#### From  Vincents to Saurabhs Board

![V to S](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/UART_V_to_S.png)

[Saleae Capture UART](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/UART_Capture.sal)

## 2. I2C: Inter-Integrated Circuit

1. Explain in chronological order the events that take place when a controller wants to send data to a peripheral?

+ First, the controller sends a start signal on the I2C bus(i.e. Pulling SDA line low).incase of a multi master setup, the master will check if the SDA line is not used.

+ Then, the controller sends a 8-bit, Highest 7-bits are the slave address of the peripheral it wants to communicate with, and last bit is 0(R/W bit).

+ The addressed peripheral acknowledges the receipt of its address by pulling the SDA line low.

+ Next, the controller sends one byte of the data at a time and waits for ACK/NACK from peripheral.

+ After each byte is transmitted, the peripheral acknowledges its receipt by pulling the SDA line low, and the communication continues until the controller sends a stop signal.

+ Finally, the controller sends a stop signal, which releases the SDA and SCL lines, indicating the end of the transaction.


2. Explain in chronological order the events that take place when a controller wants to read data from a peripheral?

+ Start Condition: The master generates a start condition on the bus by pulling the data line (SDA) low while the clock line (SCL) is high. This indicates the beginning of a communication sequence.

+ The master sends the address of the peripheral it wants to communicate with, along with a bit indicating that it wants to read data from the peripheral.then the masters sends value of register from which it wants to read data(this depends on the peripheral).

+ After sending the address, the master releases the SDA line, allowing the peripheral to respond. If the peripheral exists and is ready to communicate, it pulls the SDA line low to acknowledge the address.

+ Following the acknowledgment, the master enters a reception mode and waits to receive data from the peripheral. The peripheral then sends the requested data byte(s) to the master.

+ After receiving each byte, the master sends an acknowledgment (ACK) or negative acknowledgment (NACK) to the peripheral to indicate whether it should continue sending data. Typically, the master sends an ACK after receiving each byte to signal that it is ready for the next byte. However, if the master does not want to receive more data, it sends a NACK.

+ Once the master has received all the data it needs, it generates a stop condition by pulling the SDA line from low to high while the clock line (SCL) remains high. This indicates the end of the communication sequence.

3. The following data packet is observed when a controller wants to write some data to a peripheral.

a. Highlight the boxes (bytes) or box (byte) that are sampled when the controller controls the SDA line

+ ![a](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/I2C_a.png)

b. Identify which bytes are the:

+ Peripheral address

+ ![b1](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/I2C_addr.png)

+ Register address

+ ![b2](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/I2C_reg.png)

+ Data byte

+ ![b3](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/I2C_data.png)

### Code

The code for all Communication protocols is written in one project itself, a selector variable `select_interface` is present in main which decides which protocol will be used for bi-directional communication.
[Code](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/tree/main/CommProtocols_A08G)

### Video of Setup



https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/assets/57740824/d608ef0d-b04e-4986-bbcd-a7e58fdd9c29



### Screenshot of Capture and Saleae Capture of Packets I2C

#### From Saurabhs to Vincents Board(Vice Versa)

![S to V](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/I2C_SS.png)

[Saleae Capture I2C](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/I2C_Capture.sal)

## 3. SPI: Serial Peripheral Interface

1. Who generates the clock in SPI communication and does it ever change through one communication cycle?

+ The master generates the clock, the clock does not change between a communication cycle but may change between different communication cycles.

2. What is clock polarity in SPI and how does it help with data verification?

+ Clock Polarity(CPOL) is a parameter in SPI communication protocol that defines the idle state of the clock(i.e when no transmission is happening), when CPOL = 0, in the idle clock is at 0, and transitions from 0 to 1 during communication, for CPOL = 1, in idle clock is at 1, and transitions from 1 to 0 during communications. the CPOL makes sure that the data is sampled at the correct time when.

3. How would you implement SPI if you have more than one slave device and no select lines? Explain with the help of a block diagram and you may assume the number of slaves to be 3.

+ I would daisy-chain the slaves i.e. connect the MOSI pin to the MISO pin of the first slave, then connect MOSI pin of the slave to the next slave's MISO. Then for communicating with the slaves, I will send a large data chunk, the chunk will consist total of the intended number of bytes each slave consumes. If I want to access the second slave, I will send the required data in the big chunk but keep the data space for 1st and 3rd slave void(data that does not get processed by the slaves or is ignored).

![Daisychain](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/Daisychain.drawio.png)

### Code

The code for all Communication protocols is written in one project itself, a selector variable `select_interface` is present in main which decides which protocol will be used for bi-directional communication.
[Code](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/tree/main/CommProtocols_A08G)

### Video of Setup



https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/assets/57740824/ef14d01a-993d-4ba6-a5a6-62f004e67599




### Screenshot of Capture and Saleae Capture of Packets SPI

#### From Saurabhs to Vincents Board

![S to V](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/SPI_S_to_V.png)

#### From  Vincents to Saurabhs Board

![V to S](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/SPI_V_to_S.png)

[Saleae Capture SPI](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/SPI_Capture.sal)

## 4. Your I2C Device

### Photo of Setup

![Setup](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/IMU_Setup.jpg)

### Screenshot of Capture and Saleae Capture

![saleae](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/IMU_SS.png)

[Saleae Capture IMU](https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/blob/main/Images%20and%20Captures/IMU_Capture.sal)

### Video of IMU in Action



https://github.com/ese5160/a08g-comm-protocols-t26-circuit-crusaders/assets/57740824/12cc2938-83d0-408c-9ba1-98b6980f2b24



## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
* Code formatting and extension recommendation files come with this repository.
* Ctrl+Shift+V will render the README.md (maybe not the images though)
