[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/Vy1tQVwT)
# a06p-freertos-i2c

    * Name: Saurabh Parulekar
    * Github Repository URL: https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24
    * Description of hardware: (embedded hardware, laptop, etc): HP Pavilion Windows Gaming laptop, 15" 8GB i5

## 1 Updating the WINC1500
![Winc1500 Update](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/WINC1500Update.png)

## 2 Porting FreeRTOS
[Project and FreeRTOS Porting Files](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/tree/main/PortingFreeRTOS_Code/Porting_FreeRTOS)

![Porting FreeRTOS](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/Porting_FreeRTOS.gif)

## 3 FreeRTOS Basics
[Concurrency Challenge Implemented](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/tree/main/Concurrency_Challenge/Concurrency_Challenge_FreeRTOS)

![Concurrency Challenge](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/Concurrency_Challenge.gif)

### For LED Task
![LED Task Before Init](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/LED_Start_Stack.png)
![LED Task After Init](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/LED_End_Stack.png)
We can see that the LED task consumes 60 words from the stack, incase of SAMD21, the word size is 4 Bytes(usually 2 Bytes), so the total stack size for the LED task is 60*4 = 240 Bytes.

### For Button Task
![Button Task Before Init](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/Button_Start_Stack.png)
![Button Task After Init](https://github.com/ese5160/a06p-freertos-i2c-saurabhparulekar24/blob/main/images/Button_End_Stack.png)
We can see that the Button task consumes 60 words from the stack, incase of SAMD21, the word size is 4 Bytes(usually 2 Bytes), so the total stack size for the Button task is 60*4 = 240 Bytes.


## Github Repo Submission Resources

* [ESE5160 Example Repo Submission](https://github.com/ese5160/example-repository-submission)
* [Markdown Guide: Basic Syntax](https://www.markdownguide.org/basic-syntax/)
* [Adobe free video to gif converter](https://www.adobe.com/express/feature/video/convert/video-to-gif)
* [Curated list of example READMEs](https://github.com/matiassingers/awesome-readme)
* [VS Code](https://code.visualstudio.com/) is heavily recommended to develop code and handle Git commits
  * Code formatting and extension recommendation files come with this repository.
  * Ctrl+Shift+V will render the README.md (maybe not the images though)
