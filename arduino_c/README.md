# Programming in C with the Arduino IDE

As a parallel development we have some code for the esp8266 on the motorshield board written in C. It helps troubleshooting behaviour and usability of pins, combinations etc.

The board uses the pin D1 to D4 to control tle L293DD motor bridge. The I2C is usually booked on these pins, they have to be remapped therefore.

## I2C Display 1602

It works only with D5 and D6. D7 and D8 throw errors when unconnected to a I2C bus and stop the program when connected. Same is for SD2 and SD3 (GPIO9 and GPIO10).

``` c
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup(){
  Wire.begin(12,14); // I2C on D6 and D5 since D1 and D2 are connected to the motor driver
  lcd.init();
  lcd.backlight();
  pinMode(16, OUTPUT);
}

void loop(){
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
  digitalWrite(16, LOW);
  delay(500);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Hello, World!");
  digitalWrite(16, HIGH);
  delay(500);
  lcd.clear(); 
}
```
