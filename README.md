# Interrupting LEDs

## Description
Application for switching LEDs on the STM32F411 board. The LEDs are switched using an interrupt when the User button is pressed. The HAL library was used to implement the application.

## Hardware requirements
+ STM32F411E DISCO

## Software requirements
+ Programming language C
+ Keil uVision 5

## Instructions for use
To work with the application, you need to download it and open interrupting_LEDs.uvprojx in Keil uVision. After that, run the program and two green and red LEDs will light up on the board. When the User button is pressed, the LEDs will change to blue and yellow. Pins PD12-PD15 are responsible for LEDs. PD12 - green, PD13 - yellow, PD14 - red, PD15 - blue.

## The result of the program
![LEDs_ON](https://github.com/MukolaMartyniuk/interrupting_LEDs/blob/main/images/LEDs_ON.jpeg)
_____
![LEDs_OFF](https://github.com/MukolaMartyniuk/interrupting_LEDs/blob/main/images/LEDs_OFF.jpeg)
