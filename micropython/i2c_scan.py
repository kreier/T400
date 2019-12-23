from machine import Pin, I2C
i2c = I2C(0)
i2c = I2C(1, scl=Pin(5), sda=Pin(4), freq=400000) # in esp32 it is 22 and 21
i2c.scan()
