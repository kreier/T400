from machine import Pin
from time import sleep

led = Pin(16, Pin.OUT)

while True:
  led.on()
  sleep(0.5)
  led.off()   # is low and actually led on!
  sleep(0.5)