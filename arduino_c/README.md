# Programming in C with the Arduino IDE

As a parallel development we have some code for the esp8266 on the motorshield board written in C. It helps troubleshooting behaviour and usability of pins, combinations etc.

The board uses the pin D1 to D4 to control tle L293DD motor bridge. The I2C is usually booked on these pins, they have to be remapped therefore.

## I2C Display 1602

It works only with D5 and D6. D7 and D8 throw errors when unconnected to a I2C bus and stop the program when connected. Same is for SD2 and SD3 (GPIO9 and GPIO10).

