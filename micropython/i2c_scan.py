from machine import Pin, I2C
i2c = I2C(0)
i2c = I2C(1, scl=Pin(22), sda=Pin(21), freq=400000) # in esp32 it is 5 and 4
i2c.scan()
