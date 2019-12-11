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
