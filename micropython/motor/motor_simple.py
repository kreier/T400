
import machine
import time

M1 = machine.Pin(0, machine.Pin.OUT)
M2 = machine.Pin(2, machine.Pin.OUT)
E1 = machine.Pin(5, machine.Pin.OUT) # PWM
E2 = machine.Pin(4, machine.Pin.OUT) # PWM

E1.on()
E2.on()
M1.on()
M2.on()

print("Motor on")

time.sleep(2)

E1.off()
E2.off()
M1.off()
M2.off()

print("Motor off")


