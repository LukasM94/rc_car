#!/usr/bin/python
import serial
import sys

ser = serial.Serial(
  port=sys.argv[1],
  baudrate=9600,
  stopbits=2,
  bytesize=8,
  parity=serial.PARITY_ODD)
while 1:
  c = ser.readline()
  if c != '':
    print(c))
