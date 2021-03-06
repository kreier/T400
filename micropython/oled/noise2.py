import machine
import uos
import sh1106
import utime
from machine import I2C, Pin, ADC

adc = machine.ADC(0)
i2c = I2C(scl=Pin(12), sda=Pin(14))
oled = sh1106.SH1106_I2C(128, 64, i2c)

while True: 
    for _ in range(500):
        x = int(uos.urandom(1)[0] / 2)
        y = int(uos.urandom(1)[0] / 4)
        oled.pixel(x, y, 1)
    oled.show()
    utime.sleep_ms(200)
    oled.fill(0)
    
