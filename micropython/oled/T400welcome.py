from machine import Pin, I2C
import ssd1306

# ESP32 Pin assignment 
#i2c = I2C(1, scl=Pin(22), sda=Pin(21))

# ESP8266 Pin
i2c = I2C(-1, scl=Pin(12), sda=Pin(14)) # negative 1 for software i2c

oled_width = 128
oled_height = 64
oled = ssd1306.SSD1306_I2C(oled_width, oled_height, i2c)

# draw some boxes

for x in range(0, 127): # horizontal lines
  oled.pixel(x, 0, 1)
  oled.pixel(x, 15, 1)
  oled.pixel(x, 16, 1)
  oled.pixel(x, 63, 1)
  
for y in range(0, 63): # vertical lines
  oled.pixel(0, y, 1)
  oled.pixel(127, y, 1)

oled.text('T400 Robot Car', 8, 4)
oled.text('Programmed in', 4, 22)
oled.text('MicroPython on', 4, 32)
oled.text('a ESP8266.', 4, 42)
oled.text('Used at AISVN.', 4, 52)
  
oled.show()

