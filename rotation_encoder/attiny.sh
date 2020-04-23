#!/bin/bash
make && avrdude -v -pattiny85 -cavrispv2 -P /dev/ttyACM0 -b57600 -Uflash:w:release/main.hex:i
