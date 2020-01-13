# Complete project details at https://RandomNerdTutorials.com

try:
  import usocket as socket
except:
  import socket

from machine import Pin, I2C
import network
import ssd1306

import esp
esp.osdebug(None)

import gc
gc.collect()

ssid = 'makerspace'
password = 'makerspace'

i2c = I2C(scl=Pin(12), sda=Pin(14))
station = network.WLAN(network.STA_IF)
oled = ssd1306.SSD1306_I2C(128, 64, i2c)
oled.text('Connecting to:', 0, 0)
oled.text(ssid, 0, 8)
oled.show()

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

oled.text("Connected!", 0, 16)
ip = str(station.ifconfig())
x = ip.find("'", 2)
ip = ip[2:x]
oled.text(ip, 0, 24)
oled.show()
print('Connection successful')
print(station.ifconfig())

led = Pin(2, Pin.OUT)
