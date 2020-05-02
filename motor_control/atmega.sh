#!/bin/bash
gpio write 22 1 && make && avrdude -v -patmega328p -carduino -P /dev/ttyUSB0 -b57600 -D -Uflash:w:release/main.hex:i && gpio write 22 0
