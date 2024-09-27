# 51-MicroController Learning Progress

This repository contains various projects and exercises developed using the **STC89C52RC microcontroller** (based on the Intel 8051 architecture). The focus is on using **Modular Programming in C** to control various hardware components such as LEDs, seven-segment displays, switches, buzzers, and more. 

<div align="center">
  <img src="https://github.com/user-attachments/assets/833acd6d-df5d-428b-8266-76efa64f5af3" alt="image">
</div>


## Microcontroller Specifications

- **Microcontroller**: STC89C52RC
- **Architecture**: Intel 8051
- **Clock**: 11.0592 MHz Quartz Crystal
- **I/O Pin Details**:
  - **Buzzer Pin**: P2^5
  - **Matrix LED Control**: Jumper (cap) required

## Projects Overview

Each folder in this repository contains a specific project for learning and experimenting with the microcontroller. Below is a brief description of each project:

1. **01_LED** - Basic LED control.
2. **02_LED_OnOffLoop** - Loop to turn an LED on and off.
3. **03_LED_LoopAround** - LEDs loop in a circular manner.
4. **04_LED_LoopAroundPlus** - Enhanced version of LED loop.
5. **05_SwitchBasics** - Basic switch control.
6. **06_SwitchPlus** - Advanced switch control.
7. **08_SwitchControlLEDShowBinaryIncrement** - Using a switch to display a binary increment on LEDs.
8. **09_SwitchControlSingleLEDShiftRight** - Switch control to shift LED light to the right.
9. **10_SevenSegmentDisplayStaticSingle** - Static display on a seven-segment unit.
10. **11_DynamicSSDisplay** - Dynamic seven-segment display.
11. **12_ModularProgramming** - Example of modular programming in C.
12. **13_LCD1602TestTool** - Basic testing tool for LCD1602.
13. **14_MatrixKeyboad** - Matrix keyboard interface.
14. **15_MatrixKeyboad_PasswordLock** - Password lock using matrix keyboard.
15. **16_BottomControlLEDPatternDirection(BaseOnTimer)** - Control LED pattern direction based on a timer.
16. **17_ClockBasedOnTimerAndInterrupt** - A clock implemented with a timer and interrupt system.
17. **18_SerialCommunicationSend** - Sending data via serial communication.
18. **19_SerialCOMControlLED** - Serial communication controlling LEDs.
19. **20_DotMatrixDisplayShowImage** - Display images on a dot matrix.
20. **21_DotMatrixDisplayShowAnimation** - Animated images on a dot matrix.
21. **22_DS1302Clock** - A real-time clock using the DS1302 chip.
22. **23_DS1302AdjustableClock** - Adjustable clock with DS1302.
23. **24_BuzzerBuzzWhenBottomPressed** - Make a buzzer sound when a button is pressed.
24. **25_BuzzerPlayMusic** - Play music with a buzzer.
25. **27_StopWatchWithSave** - Stopwatch with key scanning and display.
26. **28_DS18B20ReadTemperature** - Read temperature using DS18B20.
27. **29_DS18B20TemperatureAlarm** - Alarm based on DS18B20 temperature readings.
28. **30_LCD1602BaseCode** - Basic LCD1602 code.
29. **31_LEDBreath(PWMControl)** - LED breath effect using PWM control.
30. **32_DCMotorThreeSpeeds(PWMControlEmbeddedInTimerInterrupt)** - Control DC motor speed using PWM embedded in timer interrupts.
31. **33_ADConversion** - Analog to Digital conversion.
32. **34_DAConversion** - Digital to Analog conversion.
33. **35_IRRemoteControl** - Control devices using IR remote.
34. **36_IRRemoteDCMotorThreeSpeeds** - Control DC motor speeds with IR remote.

## Additional Files

- **BoardSchematics.pdf** - Schematics for the hardware setup.
- **Hex files** for downloading to the microcontroller can be found in the `Object` directory.
- **README.md** - This file.

## Credits

This project is a learning initiative for 51-Microcontroller development. Special thanks to Jiangsu University of Science and Technology for providing the framework and tools.
