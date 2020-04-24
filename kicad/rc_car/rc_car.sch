EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L 4xxx:4001 U1
U 1 1 5E8E5212
P 5200 2350
F 0 "U1" H 5200 2675 50  0000 C CNN
F 1 "4001" H 5200 2584 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 5200 2350 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4000bms-01bms-02bms-25bms.pdf" H 5200 2350 50  0001 C CNN
	1    5200 2350
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:BC547 Q1
U 1 1 5E8E6A73
P 4200 2450
F 0 "Q1" H 4391 2496 50  0000 L CNN
F 1 "BC547" H 4391 2405 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 4400 2375 50  0001 L CIN
F 3 "http://www.fairchildsemi.com/ds/BC/BC547.pdf" H 4200 2450 50  0001 L CNN
	1    4200 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R7
U 1 1 5E8F6564
P 4300 2000
F 0 "R7" H 4368 2046 50  0000 L CNN
F 1 "10k" H 4368 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4340 1990 50  0001 C CNN
F 3 "~" H 4300 2000 50  0001 C CNN
	1    4300 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R5
U 1 1 5E8F6CC0
P 3750 2450
F 0 "R5" V 3545 2450 50  0000 C CNN
F 1 "1k" V 3636 2450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3790 2440 50  0001 C CNN
F 3 "~" H 3750 2450 50  0001 C CNN
	1    3750 2450
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R8
U 1 1 5E8FFDBF
P 4700 2000
F 0 "R8" H 4768 2046 50  0000 L CNN
F 1 "10k" H 4768 1955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4740 1990 50  0001 C CNN
F 3 "~" H 4700 2000 50  0001 C CNN
	1    4700 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1850 4300 1650
Wire Wire Line
	4700 1650 4700 1850
Wire Wire Line
	4300 2150 4300 2250
Wire Wire Line
	4900 2250 4300 2250
Connection ~ 4300 2250
Wire Wire Line
	4900 2450 4700 2450
Wire Wire Line
	4700 2450 4700 2150
Wire Wire Line
	3900 2450 4000 2450
Wire Wire Line
	4300 2650 4300 3050
Wire Wire Line
	5500 2350 5700 2350
Text Label 5500 2350 0    50   ~ 0
!reset
Text Label 8700 1900 0    50   ~ 0
!reset
Text Label 8700 3000 0    50   ~ 0
scl
Text Label 4050 1950 0    50   ~ 0
sda
Text Label 4050 2050 0    50   ~ 0
scl
$Comp
L Device:R_US R4
U 1 1 5E947517
P 3650 1400
F 0 "R4" H 3718 1446 50  0000 L CNN
F 1 "2.2k" H 3718 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3690 1390 50  0001 C CNN
F 3 "~" H 3650 1400 50  0001 C CNN
	1    3650 1400
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R6
U 1 1 5E9484EA
P 3950 1400
F 0 "R6" H 4018 1446 50  0000 L CNN
F 1 "2.2k" H 4018 1355 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 3990 1390 50  0001 C CNN
F 3 "~" H 3950 1400 50  0001 C CNN
	1    3950 1400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 1950 3950 1550
Wire Wire Line
	3650 1550 3650 2050
Connection ~ 3650 2050
Wire Wire Line
	3650 2050 4050 2050
Wire Wire Line
	3950 1950 4050 1950
Connection ~ 3950 1950
Wire Wire Line
	3650 1250 3650 1050
Wire Wire Line
	3950 1050 3950 1250
$Comp
L power:GND #PWR010
U 1 1 5E95F47A
P 4500 3050
F 0 "#PWR010" H 4500 2800 50  0001 C CNN
F 1 "GND" H 4505 2877 50  0000 C CNN
F 2 "" H 4500 3050 50  0001 C CNN
F 3 "" H 4500 3050 50  0001 C CNN
	1    4500 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4700 3050 4500 3050
Wire Wire Line
	4300 3050 4500 3050
Connection ~ 4500 3050
Wire Wire Line
	1700 1250 1700 1100
Wire Wire Line
	1500 3850 1500 3900
$Comp
L power:GND #PWR02
U 1 1 5E965D13
P 1500 4000
F 0 "#PWR02" H 1500 3750 50  0001 C CNN
F 1 "GND" H 1505 3827 50  0000 C CNN
F 2 "" H 1500 4000 50  0001 C CNN
F 3 "" H 1500 4000 50  0001 C CNN
	1    1500 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR016
U 1 1 5E969FEE
P 8000 3750
F 0 "#PWR016" H 8000 3500 50  0001 C CNN
F 1 "GND" H 8005 3577 50  0000 C CNN
F 2 "" H 8000 3750 50  0001 C CNN
F 3 "" H 8000 3750 50  0001 C CNN
	1    8000 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 1650 2900 1650
Wire Wire Line
	2700 2350 2900 2350
Text Label 2900 1650 0    50   ~ 0
led_green
Text Label 2900 1750 0    50   ~ 0
button
Text Label 2800 2350 0    50   ~ 0
led_red
$Comp
L Device:R_US R2
U 1 1 5E8EC442
P 2050 5350
F 0 "R2" V 1845 5350 50  0000 C CNN
F 1 "1k" V 1936 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2090 5340 50  0001 C CNN
F 3 "~" H 2050 5350 50  0001 C CNN
	1    2050 5350
	0    1    1    0   
$EndComp
$Comp
L Device:C C2
U 1 1 5E8F04A9
P 1000 1300
F 0 "C2" H 1115 1346 50  0000 L CNN
F 1 "100n" H 1115 1255 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 1038 1150 50  0001 C CNN
F 3 "~" H 1000 1300 50  0001 C CNN
	1    1000 1300
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C1
U 1 1 5E8F1DF2
P 700 1300
F 0 "C1" H 815 1346 50  0000 L CNN
F 1 "10u" H 815 1255 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 700 1300 50  0001 C CNN
F 3 "~" H 700 1300 50  0001 C CNN
	1    700  1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	700  1150 700  1100
Wire Wire Line
	700  1100 1000 1100
Connection ~ 1700 1100
Wire Wire Line
	1700 1100 1700 1050
Wire Wire Line
	1000 1150 1000 1100
Connection ~ 1000 1100
Wire Wire Line
	1000 1100 1700 1100
Wire Wire Line
	1000 1450 1000 1550
Wire Wire Line
	1000 1550 700  1550
Wire Wire Line
	700  1450 700  1550
Wire Wire Line
	700  1550 700  1650
Connection ~ 700  1550
$Comp
L power:GND #PWR01
U 1 1 5E8F5AAF
P 700 1650
F 0 "#PWR01" H 700 1400 50  0001 C CNN
F 1 "GND" H 705 1477 50  0000 C CNN
F 2 "" H 700 1650 50  0001 C CNN
F 3 "" H 700 1650 50  0001 C CNN
	1    700  1650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5E8F6B68
P 8500 1450
F 0 "C4" H 8615 1496 50  0000 L CNN
F 1 "100n" H 8615 1405 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 8538 1300 50  0001 C CNN
F 3 "~" H 8500 1450 50  0001 C CNN
	1    8500 1450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR018
U 1 1 5E8F880E
P 8500 1650
F 0 "#PWR018" H 8500 1400 50  0001 C CNN
F 1 "GND" H 8505 1477 50  0000 C CNN
F 2 "" H 8500 1650 50  0001 C CNN
F 3 "" H 8500 1650 50  0001 C CNN
	1    8500 1650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1250 8500 1300
$Comp
L Device:LED D1
U 1 1 5E8FC88A
P 2450 5350
F 0 "D1" H 2443 5095 50  0000 C CNN
F 1 "LED" H 2443 5186 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 2450 5350 50  0001 C CNN
F 3 "~" H 2450 5350 50  0001 C CNN
	1    2450 5350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2300 5350 2200 5350
Wire Wire Line
	2600 5350 2800 5350
$Comp
L Device:R_US R3
U 1 1 5E9021A4
P 2050 5650
F 0 "R3" V 1845 5650 50  0000 C CNN
F 1 "1k" V 1936 5650 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2090 5640 50  0001 C CNN
F 3 "~" H 2050 5650 50  0001 C CNN
	1    2050 5650
	0    1    1    0   
$EndComp
$Comp
L Device:LED D2
U 1 1 5E9021AA
P 2450 5650
F 0 "D2" H 2443 5395 50  0000 C CNN
F 1 "LED" H 2443 5486 50  0000 C CNN
F 2 "LED_THT:LED_D3.0mm" H 2450 5650 50  0001 C CNN
F 3 "~" H 2450 5650 50  0001 C CNN
	1    2450 5650
	-1   0    0    1   
$EndComp
Wire Wire Line
	2300 5650 2200 5650
Wire Wire Line
	2600 5650 2800 5650
Wire Wire Line
	2800 5350 2800 5650
Wire Wire Line
	2800 5650 2800 5750
Connection ~ 2800 5650
$Comp
L power:GND #PWR07
U 1 1 5E905301
P 2800 5750
F 0 "#PWR07" H 2800 5500 50  0001 C CNN
F 1 "GND" H 2805 5577 50  0000 C CNN
F 2 "" H 2800 5750 50  0001 C CNN
F 3 "" H 2800 5750 50  0001 C CNN
	1    2800 5750
	1    0    0    -1  
$EndComp
Text Label 1500 5350 0    50   ~ 0
led_green
Text Label 1500 5650 0    50   ~ 0
led_red
Wire Wire Line
	1500 5350 1900 5350
Wire Wire Line
	1500 5650 1900 5650
Wire Wire Line
	8400 2900 8700 2900
Wire Wire Line
	8400 3000 8700 3000
$Comp
L Switch:SW_Push SW1
U 1 1 5E92318F
P 2200 6450
F 0 "SW1" H 2200 6735 50  0000 C CNN
F 1 "SW_Push_Dual" H 2200 6644 50  0000 C CNN
F 2 "Button_Switch_THT:SW_PUSH_6mm" H 2200 6650 50  0001 C CNN
F 3 "~" H 2200 6650 50  0001 C CNN
	1    2200 6450
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E92B4AC
P 2500 6550
F 0 "#PWR06" H 2500 6300 50  0001 C CNN
F 1 "GND" H 2505 6377 50  0000 C CNN
F 2 "" H 2500 6550 50  0001 C CNN
F 3 "" H 2500 6550 50  0001 C CNN
	1    2500 6550
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5E92BF2B
P 1500 6350
F 0 "#PWR03" H 1500 6200 50  0001 C CNN
F 1 "+3.3V" H 1515 6523 50  0000 C CNN
F 2 "" H 1500 6350 50  0001 C CNN
F 3 "" H 1500 6350 50  0001 C CNN
	1    1500 6350
	1    0    0    -1  
$EndComp
Wire Wire Line
	2400 6450 2500 6450
Wire Wire Line
	2500 6450 2500 6550
$Comp
L Device:R_US R1
U 1 1 5E92E89A
P 1750 6450
F 0 "R1" V 1545 6450 50  0000 C CNN
F 1 "10k" V 1636 6450 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1790 6440 50  0001 C CNN
F 3 "~" H 1750 6450 50  0001 C CNN
	1    1750 6450
	0    1    1    0   
$EndComp
Wire Wire Line
	1900 6450 1950 6450
Wire Wire Line
	1600 6450 1500 6450
Wire Wire Line
	1500 6450 1500 6350
Text Label 1500 6700 0    50   ~ 0
button
Wire Wire Line
	2700 1950 3950 1950
Wire Wire Line
	2700 2050 3650 2050
Wire Wire Line
	7400 2800 6950 2800
Wire Wire Line
	6950 2900 7400 2900
Wire Wire Line
	6950 3000 7400 3000
Text Label 6950 2800 0    50   ~ 0
pwm1a
Text Label 6950 2900 0    50   ~ 0
pwm1b
Text Label 6950 3000 0    50   ~ 0
pwm2
Wire Wire Line
	850  1650 1100 1650
Wire Wire Line
	850  1750 1100 1750
Wire Wire Line
	2700 2450 3600 2450
Wire Wire Line
	2700 1750 2900 1750
$Comp
L Connector:Raspberry_Pi_2_3 J1
U 1 1 5E8E3BA6
P 1900 2550
F 0 "J1" H 1900 4031 50  0000 C CNN
F 1 "Raspberry_Pi_2_3" H 1900 3940 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x20_P2.54mm_Vertical" H 1900 2550 50  0001 C CNN
F 3 "https://www.raspberrypi.org/documentation/hardware/raspberrypi/schematics/rpi_SCH_3bplus_1p0_reduced.pdf" H 1900 2550 50  0001 C CNN
	1    1900 2550
	1    0    0    -1  
$EndComp
Text Label 850  1750 0    50   ~ 0
rxd
Text Label 850  1650 0    50   ~ 0
txd
$Comp
L Connector:Conn_01x04_Female J5
U 1 1 5E97CD04
P 10350 5750
F 0 "J5" H 10378 5726 50  0000 L CNN
F 1 "Conn_01x04_Female" H 10378 5635 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10350 5750 50  0001 C CNN
F 3 "~" H 10350 5750 50  0001 C CNN
	1    10350 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10150 5650 9850 5650
Wire Wire Line
	9950 5750 10150 5750
Wire Wire Line
	9950 5850 10150 5850
Wire Wire Line
	9850 5950 10150 5950
$Comp
L power:GND #PWR023
U 1 1 5E997A40
P 9850 6000
F 0 "#PWR023" H 9850 5750 50  0001 C CNN
F 1 "GND" H 9855 5827 50  0000 C CNN
F 2 "" H 9850 6000 50  0001 C CNN
F 3 "" H 9850 6000 50  0001 C CNN
	1    9850 6000
	1    0    0    -1  
$EndComp
Text Label 9950 5850 0    50   ~ 0
rxd
Text Label 9950 5750 0    50   ~ 0
txd
Wire Wire Line
	9850 5650 9850 5600
Wire Wire Line
	9850 5950 9850 6000
$Comp
L Connector:Conn_01x04_Male J9
U 1 1 5E9B8A78
P 10400 4850
F 0 "J9" H 10372 4824 50  0000 R CNN
F 1 "Conn_01x04_Male" H 10372 4733 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 10400 4850 50  0001 C CNN
F 3 "~" H 10400 4850 50  0001 C CNN
	1    10400 4850
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9850 5100 9850 5050
Wire Wire Line
	9850 5050 10200 5050
Wire Wire Line
	10200 4750 9850 4750
Wire Wire Line
	9850 4750 9850 4700
$Comp
L power:GND #PWR021
U 1 1 5E9C3FCA
P 9850 5100
F 0 "#PWR021" H 9850 4850 50  0001 C CNN
F 1 "GND" H 9855 4927 50  0000 C CNN
F 2 "" H 9850 5100 50  0001 C CNN
F 3 "" H 9850 5100 50  0001 C CNN
	1    9850 5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	10200 4850 9950 4850
Wire Wire Line
	9950 4950 10200 4950
Text Label 9950 4850 0    50   ~ 0
sda
Text Label 9950 4950 0    50   ~ 0
scl
$Comp
L Connector:Conn_01x03_Male J6
U 1 1 5E9CADC0
P 10400 1750
F 0 "J6" H 10372 1774 50  0000 R CNN
F 1 "Conn_01x03_Male" H 10372 1683 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 10400 1750 50  0001 C CNN
F 3 "~" H 10400 1750 50  0001 C CNN
	1    10400 1750
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J7
U 1 1 5E9CC3D8
P 10400 2250
F 0 "J7" H 10372 2274 50  0000 R CNN
F 1 "Conn_01x03_Male" H 10372 2183 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 10400 2250 50  0001 C CNN
F 3 "~" H 10400 2250 50  0001 C CNN
	1    10400 2250
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x03_Male J8
U 1 1 5E9CC917
P 10400 2750
F 0 "J8" H 10372 2774 50  0000 R CNN
F 1 "Conn_01x03_Male" H 10372 2683 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 10400 2750 50  0001 C CNN
F 3 "~" H 10400 2750 50  0001 C CNN
	1    10400 2750
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10200 2850 10000 2850
Wire Wire Line
	10000 2850 10000 2350
Wire Wire Line
	10000 1850 10200 1850
Wire Wire Line
	10200 2350 10000 2350
Connection ~ 10000 2350
Wire Wire Line
	10000 2350 10000 1850
Wire Wire Line
	10200 2750 10050 2750
Wire Wire Line
	10050 2750 10050 2250
Wire Wire Line
	10050 1750 10200 1750
Wire Wire Line
	10200 2250 10050 2250
Connection ~ 10050 2250
Wire Wire Line
	10050 2250 10050 1750
Wire Wire Line
	10200 1650 9700 1650
Wire Wire Line
	10200 2150 9700 2150
Wire Wire Line
	10200 2650 9700 2650
Text Label 9700 1650 0    50   ~ 0
pwm1a
Text Label 9700 2150 0    50   ~ 0
pwm1b
Text Label 9700 2650 0    50   ~ 0
pwm2
Connection ~ 10050 1750
Wire Wire Line
	10050 1150 10050 1750
$Comp
L power:+7.5V #PWR025
U 1 1 5E9E82FC
P 10050 1100
F 0 "#PWR025" H 10050 950 50  0001 C CNN
F 1 "+7.5V" H 10065 1273 50  0000 C CNN
F 2 "" H 10050 1100 50  0001 C CNN
F 3 "" H 10050 1100 50  0001 C CNN
	1    10050 1100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR024
U 1 1 5E9E8A92
P 10000 2950
F 0 "#PWR024" H 10000 2700 50  0001 C CNN
F 1 "GND" H 10005 2777 50  0000 C CNN
F 2 "" H 10000 2950 50  0001 C CNN
F 3 "" H 10000 2950 50  0001 C CNN
	1    10000 2950
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR019
U 1 1 5E9E8EB9
P 9250 1600
F 0 "#PWR019" H 9250 1350 50  0001 C CNN
F 1 "GND" H 9255 1427 50  0000 C CNN
F 2 "" H 9250 1600 50  0001 C CNN
F 3 "" H 9250 1600 50  0001 C CNN
	1    9250 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10000 2950 10000 2850
Connection ~ 10000 2850
$Comp
L Device:C C6
U 1 1 5E9EEA3B
P 9600 1350
F 0 "C6" H 9715 1396 50  0000 L CNN
F 1 "100n" H 9715 1305 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 9638 1200 50  0001 C CNN
F 3 "~" H 9600 1350 50  0001 C CNN
	1    9600 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C5
U 1 1 5E9EFC23
P 9250 1350
F 0 "C5" H 9365 1396 50  0000 L CNN
F 1 "47u" H 9365 1305 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D6.3mm_P2.50mm" H 9250 1350 50  0001 C CNN
F 3 "~" H 9250 1350 50  0001 C CNN
	1    9250 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10050 1150 9600 1150
Wire Wire Line
	9600 1150 9600 1200
Wire Wire Line
	9600 1150 9250 1150
Wire Wire Line
	9250 1150 9250 1200
Connection ~ 9600 1150
Wire Wire Line
	10050 1150 10050 1100
Connection ~ 10050 1150
Wire Wire Line
	9600 1500 9600 1550
Wire Wire Line
	9600 1550 9250 1550
Wire Wire Line
	9250 1550 9250 1600
Wire Wire Line
	9250 1550 9250 1500
Connection ~ 9250 1550
$Comp
L Device:Jumper_NO_Small JP1
U 1 1 5EA1347E
P 4700 2750
F 0 "JP1" V 4654 2798 50  0000 L CNN
F 1 "Jumper_NO_Small" V 4745 2798 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4700 2750 50  0001 C CNN
F 3 "~" H 4700 2750 50  0001 C CNN
	1    4700 2750
	0    1    1    0   
$EndComp
Wire Wire Line
	4700 2450 4700 2650
Connection ~ 4700 2450
Wire Wire Line
	4700 2850 4700 3050
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5EA38020
P 5000 4550
F 0 "J2" H 4918 4767 50  0000 C CNN
F 1 "Screw_Terminal_01x02" H 4918 4676 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x02_P5.08mm_Drill1.5mm" H 5000 4550 50  0001 C CNN
F 3 "~" H 5000 4550 50  0001 C CNN
	1    5000 4550
	-1   0    0    -1  
$EndComp
$Comp
L power:VCC #PWR04
U 1 1 5EA3F077
P 1700 1050
F 0 "#PWR04" H 1700 900 50  0001 C CNN
F 1 "VCC" H 1717 1223 50  0000 C CNN
F 2 "" H 1700 1050 50  0001 C CNN
F 3 "" H 1700 1050 50  0001 C CNN
	1    1700 1050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR08
U 1 1 5EA5CAF4
P 3800 1050
F 0 "#PWR08" H 3800 900 50  0001 C CNN
F 1 "VCC" H 3817 1223 50  0000 C CNN
F 2 "" H 3800 1050 50  0001 C CNN
F 3 "" H 3800 1050 50  0001 C CNN
	1    3800 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3650 1050 3800 1050
Connection ~ 3800 1050
Wire Wire Line
	3800 1050 3950 1050
$Comp
L power:VCC #PWR09
U 1 1 5EA62D3F
P 4500 1650
F 0 "#PWR09" H 4500 1500 50  0001 C CNN
F 1 "VCC" H 4517 1823 50  0000 C CNN
F 2 "" H 4500 1650 50  0001 C CNN
F 3 "" H 4500 1650 50  0001 C CNN
	1    4500 1650
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR017
U 1 1 5EA6322C
P 8100 1150
F 0 "#PWR017" H 8100 1000 50  0001 C CNN
F 1 "VCC" H 8117 1323 50  0000 C CNN
F 2 "" H 8100 1150 50  0001 C CNN
F 3 "" H 8100 1150 50  0001 C CNN
	1    8100 1150
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR020
U 1 1 5EA6E3AA
P 9850 4700
F 0 "#PWR020" H 9850 4550 50  0001 C CNN
F 1 "VCC" H 9867 4873 50  0000 C CNN
F 2 "" H 9850 4700 50  0001 C CNN
F 3 "" H 9850 4700 50  0001 C CNN
	1    9850 4700
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR022
U 1 1 5EA6FC4A
P 9850 5600
F 0 "#PWR022" H 9850 5450 50  0001 C CNN
F 1 "VCC" H 9867 5773 50  0000 C CNN
F 2 "" H 9850 5600 50  0001 C CNN
F 3 "" H 9850 5600 50  0001 C CNN
	1    9850 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1650 4500 1650
Connection ~ 4500 1650
Wire Wire Line
	4500 1650 4700 1650
$Comp
L power:GND #PWR012
U 1 1 5EA8030D
P 5400 4750
F 0 "#PWR012" H 5400 4500 50  0001 C CNN
F 1 "GND" H 5405 4577 50  0000 C CNN
F 2 "" H 5400 4750 50  0001 C CNN
F 3 "" H 5400 4750 50  0001 C CNN
	1    5400 4750
	1    0    0    -1  
$EndComp
$Comp
L power:+7.5V #PWR011
U 1 1 5EA8078D
P 5400 4450
F 0 "#PWR011" H 5400 4300 50  0001 C CNN
F 1 "+7.5V" H 5415 4623 50  0000 C CNN
F 2 "" H 5400 4450 50  0001 C CNN
F 3 "" H 5400 4450 50  0001 C CNN
	1    5400 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 4650 5400 4650
Wire Wire Line
	5400 4750 5400 4650
Wire Wire Line
	5200 4550 5400 4550
Wire Wire Line
	5400 4550 5400 4450
Wire Wire Line
	1950 6450 1950 6700
Wire Wire Line
	1950 6700 1500 6700
Connection ~ 1950 6450
Wire Wire Line
	1950 6450 2000 6450
$Comp
L power:VCC #PWR013
U 1 1 5E944298
P 6050 1800
F 0 "#PWR013" H 6050 1650 50  0001 C CNN
F 1 "VCC" H 6067 1973 50  0000 C CNN
F 2 "" H 6050 1800 50  0001 C CNN
F 3 "" H 6050 1800 50  0001 C CNN
	1    6050 1800
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E946B91
P 6550 2150
F 0 "C3" H 6665 2196 50  0000 L CNN
F 1 "100n" H 6665 2105 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 6588 2000 50  0001 C CNN
F 3 "~" H 6550 2150 50  0001 C CNN
	1    6550 2150
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5E949A4D
P 6050 3000
F 0 "#PWR014" H 6050 2750 50  0001 C CNN
F 1 "GND" H 6055 2827 50  0000 C CNN
F 2 "" H 6050 3000 50  0001 C CNN
F 3 "" H 6050 3000 50  0001 C CNN
	1    6050 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6050 1900 6050 1850
Wire Wire Line
	6050 2900 6050 3000
$Comp
L 4xxx:4001 U1
U 5 1 5E91C9A9
P 6050 2400
F 0 "U1" H 6280 2446 50  0000 L CNN
F 1 "4001" H 6280 2355 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm_Socket_LongPads" H 6050 2400 50  0001 C CNN
F 3 "http://www.intersil.com/content/dam/Intersil/documents/cd40/cd4000bms-01bms-02bms-25bms.pdf" H 6050 2400 50  0001 C CNN
	5    6050 2400
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR015
U 1 1 5E96021D
P 6550 2400
F 0 "#PWR015" H 6550 2150 50  0001 C CNN
F 1 "GND" H 6555 2227 50  0000 C CNN
F 2 "" H 6550 2400 50  0001 C CNN
F 3 "" H 6550 2400 50  0001 C CNN
	1    6550 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 2300 6550 2400
Wire Wire Line
	6550 2000 6550 1850
Wire Wire Line
	6550 1850 6050 1850
Connection ~ 6050 1850
Wire Wire Line
	6050 1850 6050 1800
$Comp
L power:+3.3V #PWR05
U 1 1 5E982B06
P 2000 1050
F 0 "#PWR05" H 2000 900 50  0001 C CNN
F 1 "+3.3V" H 2015 1223 50  0000 C CNN
F 2 "" H 2000 1050 50  0001 C CNN
F 3 "" H 2000 1050 50  0001 C CNN
	1    2000 1050
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 1050 2000 1250
Wire Wire Line
	1700 1100 1800 1100
Wire Wire Line
	1800 1100 1800 1250
Wire Wire Line
	8100 1150 8100 1250
Wire Wire Line
	8500 1250 8100 1250
Connection ~ 8100 1250
Wire Wire Line
	8100 1250 8100 1500
Wire Wire Line
	8500 1650 8500 1600
Wire Wire Line
	8400 1900 8700 1900
Wire Wire Line
	1500 3900 1600 3900
Wire Wire Line
	1600 3900 1600 3850
Connection ~ 1500 3900
Wire Wire Line
	1500 3900 1500 4000
Wire Wire Line
	1600 3900 1700 3900
Wire Wire Line
	1700 3900 1700 3850
Connection ~ 1600 3900
Wire Wire Line
	1700 3900 1800 3900
Wire Wire Line
	1800 3900 1800 3850
Connection ~ 1700 3900
Wire Wire Line
	1800 3900 1900 3900
Wire Wire Line
	1900 3900 1900 3850
Connection ~ 1800 3900
Wire Wire Line
	1900 3900 2000 3900
Wire Wire Line
	2200 3900 2200 3850
Connection ~ 1900 3900
Wire Wire Line
	2000 3850 2000 3900
Connection ~ 2000 3900
Wire Wire Line
	2000 3900 2100 3900
Wire Wire Line
	2100 3850 2100 3900
Connection ~ 2100 3900
Wire Wire Line
	2100 3900 2200 3900
Wire Wire Line
	7400 2300 6950 2300
Wire Wire Line
	8000 3750 8000 3500
Wire Wire Line
	7400 2200 6950 2200
$Comp
L MCU_Module:Arduino_Nano_v3.x A1
U 1 1 5E8E2E00
P 7900 2500
F 0 "A1" H 7900 1411 50  0000 C CNN
F 1 "Arduino_Nano_v3.x" H 7900 1320 50  0000 C CNN
F 2 "Module:Arduino_Nano" H 7900 2500 50  0001 C CIN
F 3 "http://www.mouser.com/pdfdocs/Gravitech_Arduino_Nano3_0.pdf" H 7900 2500 50  0001 C CNN
	1    7900 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2400 7400 2400
Wire Wire Line
	7400 2700 6950 2700
Wire Wire Line
	7400 2500 6950 2500
Wire Wire Line
	6950 2600 7400 2600
Text Label 6950 2200 0    50   ~ 0
d3
Text Label 6950 2300 0    50   ~ 0
d4
Text Label 6950 2400 0    50   ~ 0
d5
Text Label 6950 2500 0    50   ~ 0
d6
Text Label 6950 2600 0    50   ~ 0
d7
Text Label 6950 2700 0    50   ~ 0
d8
Wire Wire Line
	7400 2100 6950 2100
Text Label 6950 2100 0    50   ~ 0
d2
Wire Wire Line
	8400 2800 8700 2800
Wire Wire Line
	8400 2700 8700 2700
Wire Wire Line
	8400 2600 8700 2600
Wire Wire Line
	8400 2500 8700 2500
Text Label 8700 2900 0    50   ~ 0
sda
Text Label 8700 2500 0    50   ~ 0
a0
Text Label 8700 2600 0    50   ~ 0
a1
Text Label 8700 2700 0    50   ~ 0
a2
Text Label 8700 2800 0    50   ~ 0
a3
$Comp
L Connector:Conn_01x04_Female J4
U 1 1 5F199A37
P 8400 5650
F 0 "J4" H 8428 5626 50  0000 L CNN
F 1 "Conn_01x04_Female" H 8428 5535 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8400 5650 50  0001 C CNN
F 3 "~" H 8400 5650 50  0001 C CNN
	1    8400 5650
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 4650 7700 4650
Wire Wire Line
	8200 4750 7700 4750
Wire Wire Line
	8200 4850 7700 4850
Wire Wire Line
	8200 4950 7700 4950
Wire Wire Line
	8200 5050 7700 5050
Wire Wire Line
	8200 5150 7700 5150
Wire Wire Line
	8200 5550 7700 5550
Wire Wire Line
	7700 5650 8200 5650
Wire Wire Line
	7700 5750 8200 5750
Wire Wire Line
	7700 5850 8200 5850
Text Label 7700 4650 0    50   ~ 0
d2
Text Label 7700 4750 0    50   ~ 0
d3
Text Label 7700 4850 0    50   ~ 0
d4
Text Label 7700 4950 0    50   ~ 0
d5
Text Label 7700 5050 0    50   ~ 0
d6
Text Label 7700 5150 0    50   ~ 0
d7
Text Label 7700 5550 0    50   ~ 0
a0
Text Label 7700 5650 0    50   ~ 0
a1
Text Label 7700 5750 0    50   ~ 0
a2
Text Label 7700 5850 0    50   ~ 0
a3
$Comp
L Connector:Conn_01x07_Female J3
U 1 1 5F1EB4D2
P 8400 4950
F 0 "J3" H 8428 4976 50  0000 L CNN
F 1 "Conn_01x07_Female" H 8428 4885 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 8400 4950 50  0001 C CNN
F 3 "~" H 8400 4950 50  0001 C CNN
	1    8400 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	8200 5250 7700 5250
Text Label 7700 5250 0    50   ~ 0
d8
$EndSCHEMATC