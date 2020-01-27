
import machine
from machine import Pin, PWM
import time

pwm1 = PWM(Pin(5), freq=1000, duty=0)
pwm2 = PWM(Pin(4), freq=1000, duty=0)
M1 = machine.Pin(0, machine.Pin.OUT)
M2 = machine.Pin(2, machine.Pin.OUT)

M1.on() # forward
M2.on() # forward

print("Motor on")
speed = 10

while speed < 1030 :
  speed += 10
  time.sleep_ms(50)
  pwm1.duty(speed)
  pwm2.duty(speed)
  
print("Max speed")
  
while speed > 20:
  speed -= 10
  time.sleep_ms(50)
  pwm1.duty(speed)
  pwm2.duty(speed)

M1.off() # now backward
M2.off()

while speed < 1030 :
  speed += 10
  time.sleep_ms(50)
  pwm1.duty(speed)
  pwm2.duty(speed)
  
print("Max speed")
  
while speed > 20:
  speed -= 10
  time.sleep_ms(50)
  pwm1.duty(speed)
  pwm2.duty(speed)

pwm1.deinit()
pwm2.deinit()
print("Motor off")


