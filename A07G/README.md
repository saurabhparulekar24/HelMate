[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Hy2o8sq9)
# ESE5160 IoT Firmware Starter Codebase

This codebase will be used first in A07G Exploring the CLI, then will be expanded upon in parts of A08G Comm Protocols, A09G The Bootloader Waltz, A10G Cloud, A11G Firmware Drivers, and A14G Final Submission.

# A07G Exploring the CLI

    * Team Number: 26
    * Team Name: Circuit Crusaders
    * Team Members: Saurabh Parulekar, Binh Nguyen
    * Github Repository URL: https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders
    * Description of test hardware: (development boards, sensors, actuators, laptop + OS, etc) 
      + 1. HP Pavilion Windows Gaming laptop, 15" 8GB i5
      + 2. Apple M2 Pro - Macbook  

## 1 Understanding the Starter Code

1. What does “InitializeSerialConsole()” do? In said function, what is “cbufRx” and “cbufTx”? What type of data structure is it?

+ The InitializeSerialConsole() function is designed to set up a serial communication interface by establishing circular buffers. It does initialization and configuration of hardware and software components necessary for data transmission and reception through a serial port. It also configures USART parameters, sets callbacks for handling serial events, and starts a continuous read operation for incoming data. 
+ "cbufRx" and "cbufTx" are circular buffer data structures used for the reception and transmission of serial data, respectively. The cbufRx buffer stores incoming data from the serial port until it can be processed, whereas cbufTx holds data ready to be sent out through the serial interface. 

2. How are “cbufRx” and “cbufTx” initialized? Where is the library that defines them (please list the *C file they come from).

+ The "cbufRx" and "cbufTx" circular buffers are initialized in the InitializeSerialConsole function of the SerialConsole.c file. They are set up using the circular_buf_init function defined in the circular_buffer.c, to which memory spaces designated by "rxCharacterBuffer" and "txCharacterBuffer", along with their respective sizes (RX_BUFFER_SIZE and TX_BUFFER_SIZE), are passed as arguments. This initialization prepares cbufRx for receiving data and cbufTx for transmitting data through the UART channel.

3. Where are the character arrays where the RX and TX characters are being stored at the end? Please mention their name and size. Tip: Please note "cBufRx" and "cBufTx" are structures.

+ The character arrays where the received (RX) and transmitted (TX) characters are stored are named "rxCharacterBuffer" and "txCharacterBuffer", respectively. These arrays serve as the underlying storage for the circular buffers "cbufRx" and "cbufTx". The size of both arrays is defined by constants RX_BUFFER_SIZE and TX_BUFFER_SIZE, which are both set to 1024 bytes. This means each array can store up to 1024 characters, providing ample space for buffering serial data for both receiving and transmitting operations within the serial communication setup.

4. Where are the interrupts for UART character received and UART character sent defined?

+ The interrupts for UART character received and UART character sent are defined in the SerialConsole.c. The setup involves registering "usart_read_callback" and "usart_write_callback" via the ""configure_usart_callbacks()" function, and utilizes the USART module's capabilities for asynchronous communication. These callbacks are automatically triggered by the USART driver upon receiving or completing the transmission of characters, effectively managing the serial communication process.

5. What are the callback functions that are called when:
A character is received? (RX)
A character has been sent? (TX)

+ Receiving a character (RX): The callback function is "usart_read_callback". This function is triggered by the USART module when a character is successfully received.
+ Sending a character (TX): The callback function is "usart_write_callback". This function is executed once the USART module has completed transmitting a character.

6. Explain what is being done on each of these two callbacks and how they relate to the cbufRx and cbufTx buffers.

+ In the SerialConsole.c code, the "usart_read_callback" and "usart_write_callback" functions manage asynchronous serial communication by interacting with cbufRx and cbufTx, the circular buffers for received and transmitted data, respectively.
  +  usart_read_callback: this is activated when a character is received via UART. So it will take a received character and store it in "cbufRx" buffer. This makes sure that the incoming data is queued in order and the data is ready for processing when it is received. 
  +  usart_write_callback: This is triggered after a character is sent, this callback checks and sends the next character from the "cbufTx" buffer if available.

7. Draw a diagram that explains the program flow for UART receive – starting with the user typing a character and ending with how that characters ends up in the circular buffer “cbufRx”. Please make reference to specific functions in the starter code.

![Question 7](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/Q7.jpg)

8. Draw a diagram that explains the program flow for the UART transmission – starting from a string added by the program to the circular buffer “cbufTx” and ending on characters being shown on the screen of a PC (On Teraterm, for example). Please make reference to specific functions in the starter code.

![Question 8](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/Q8.jpg)

9.  What is done in the function “startTasks()” in main.c? How many threads are started?
+ The startTasks() function in main.c is designed to initialize and launch essential tasks for an application running on FreeRTOS, a real-time operating system used for multitasking in embedded systems. Initially, the function assesses and reports the system's available heap memory, and provides a baseline for memory usage before task creation begins. Next, It proceeds to create a Command Line Interface (CLI) task, which facilitates user interaction through command parsing and execution. Upon attempting this task's creation, the function reports the heap memory again to evaluate the CLI task's memory impact. After that, a WiFi task is initiated to manage network communication and connectivity, an operation critical for applications requiring internet access or network communication. Following the WiFi task creation attempt, heap memory is reported for the third time to assess the additional memory footprint. Each task creation step includes error handling that outputs an error message if task initialization fails, ensuring that any issues can be promptly addressed. This careful orchestration of task initialization, coupled with diligent memory monitoring, ensures the application's tasks are started efficiently while maintaining awareness of the system's memory utilization.
  
+ Based on the function startTasks(), two threads are started:
  +  CLI Task: For handling command line interface operations.
  +  WiFi Task: For managing WiFi functionalities.

## 2 Debug Logger Module

## 3 Wiretap the convo
### Connections to Saleae
From the Initialization of the USART module, we traced back to the Pin initialized, from the below image we can see that RX is PB11 and TX PB10, as we need to capture the outgoing messages from the module we will connect the logic analyzer to PB10 and Ground of the analyzer to ground of the SAMW25 board.
#### Pins from Firmware
![FimwareInitilization](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/USART_Pins.png)

#### Hardware Connections
![Hardware Connections](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/Hardware%20Connections%20To%20Saleae.jpg)

#### Hardware Connections Closeup
![Hardware Connections Closeup](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/Hardware%20Connections%20To%20Saleae%202.jpg)

### Snooping Data
We can see the decoded message as well as the captured trace
#### Wiretap Trace
![Wiretap Trace](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/ScreenCapture.png)

#### Wiretap Capture File
[Saleae Capture Trace File](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/USART_Capture.sal)

## 4 Complete the CLI
![Reset from CLI](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/ResetfromCLI.png)

## 5 Add CLI commands

[Raw CLI Video MP4](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/COM11%20%20(EDBG%20Virtual%20COM%20Port%20(COM11))%202024-03-20%2013-27-54.mp4)



https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/assets/57740824/fd8dffc4-06ca-41ec-9100-262da5a4182a




We also made a Python GUI, for performing the above commands and will add more functionality later. [Python GUI Repo](https://github.com/saurabhparulekar24/SerialTerminalApp)

[Raw Python GUI MP4](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/COM11%20%20(EDBG%20Virtual%20COM%20Port%20(COM11))%202024-03-20%2013-27-54.mp4)



https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/assets/57740824/410ad585-a342-4728-ba0e-e9d1ca7e5f5f



## 6 Using Percepio
Using Percepio
![Percipio](https://github.com/ese5160/a07g-exploring-the-cli-t26-circuit-crusaders/blob/main/Images%20and%20Captures/percipio.png)

## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
* Code formatting and extension recommendation files come with this repository.
* Ctrl+Shift+V will render the README.md (maybe not the images though)
