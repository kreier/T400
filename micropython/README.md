# Micropython on the ESP8266

## Install Micropython

Instructions are found at [micropython.org](https://docs.micropython.org/en/latest/esp8266/tutorial/intro.html). For example you can check the size of your flash with `esptool.exe --port COM5 --chip auto flash_id`. Use the firmware found at [the download page of micropython.org](http://micropython.org/download#esp8266) and flash the new firmware with

```
esptool.py --port COM5 --baud 460800 write_flash --flash_size=detect 0 esp8266-20200103-v1.12.bin
```

Now you can connect to your esp8266 using [uPyCraft](http://docs.dfrobot.com/upycraft/) or [Thonny](https://thonny.org/). For the first one you might want to install [SourceCodePro.ttf](https://github.com/kreier/python2018/raw/master/micropython/SourceCodePro.ttf) for all users to avoid the error message.

## Using the OLED display

The OLED display is connected via I2C and the pins are remaped to GPIO 14 (SDA) and GPIO 12 (SCL) because the standard pins are used by the motorshield.



## Logfile

`2019/12/05`

Why Micropython? Because we teach python at school. It is used by data scientists. We use it in Jupyter notebooks. It is easier to learn than Arduino C.

And it has REPL - Read Evaluate Print. You get an immediate response. After flashing micropython v1.11 to my NodeMCU in five minutes the first blink from the commandline was working. Flipping pins without compiling and upload a program is GREAT!
