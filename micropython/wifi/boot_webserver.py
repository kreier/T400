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

ssid = 'Hofkoh'
password = 'kreier2013'

station = network.WLAN(network.STA_IF)

station.active(True)
station.connect(ssid, password)

while station.isconnected() == False:
  pass

print('Connection successful')
print(station.ifconfig())

led = Pin(2, Pin.OUT)


