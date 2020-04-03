#!/bin/bash
make clean && make debug && avrdude -v -patmega328p -carduino -P /dev/ttyUSB0 -b57600 -D -Uflash:w:release/main.hex:i && python communicate.py /dev/ttyUSB0 
