# STM32 user program example for the LS012B7DD06 reflective LCD driver
Example user program showing the use of my LS012B7DD06 driver for STM32 available at [this repo](https://github.com/thewideone/ls012b7dd06_stm32).
The code needs a clean-up, but provides a working example. This description will be updated in the future.

LCD_displayFrame() in ls012b7dd06.c has a bit of info of how certain peripherals cooperate with each other to send a single image frame.

TODO:
- add a prefix to defines
- replace TIM registers and related stuff if possible
- code clean-up
- add some documentation
- skip dummy pixels (their count for each line is in the display's datasheet)
