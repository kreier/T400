import machine
import utime
import sh1106
from machine import I2C, Pin, ADC

adc = machine.ADC(0)
i2c = I2C(scl=Pin(12), sda=Pin(14))
oled = sh1106.SH1106_I2C(128, 64, i2c)

while True:
    breit = adc.read()
    oled.fill(0)    
    oled.text(str(breit), 0, 20)
    breit = breit * 128/ 1024
    oled.rect(0,0,int(breit),16,1)
    oled.show()
    #utime.sleep_ms(50)
