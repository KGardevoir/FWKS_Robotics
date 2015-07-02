#!/bin/zsh
python -c"
import serial
with serial.Serial(port='$1',
                   baudrate=1200, parity=serial.PARITY_NONE,
                   stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS) as ser:
   print('kicking', ser.port)
"


/home/enmar/opt/arduino-1.6.0/hardware/tools/avr/bin/avrdude \
   -C/home/enmar/opt/arduino-1.6.0/hardware/tools/avr/etc/avrdude.conf \
   -v -patmega32u4 -cavr109 -P$1 -b57600 -D -Uflash:w:$2:i
