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
L Connector:Conn_01x04_Male J1
U 1 1 5E90BCEC
P 550 2200
F 0 "J1" H 600 2400 50  0000 C CNN
F 1 "Conn_01x04_Male" H 658 2390 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 550 2200 50  0001 C CNN
F 3 "~" H 550 2200 50  0001 C CNN
	1    550  2200
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R1
U 1 1 5E90D00A
P 1600 1950
F 0 "R1" V 1395 1950 50  0000 C CNN
F 1 "390" V 1486 1950 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1640 1940 50  0001 C CNN
F 3 "~" H 1600 1950 50  0001 C CNN
	1    1600 1950
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R2
U 1 1 5E90D942
P 1600 2550
F 0 "R2" V 1395 2550 50  0000 C CNN
F 1 "390" V 1486 2550 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 1640 2540 50  0001 C CNN
F 3 "~" H 1600 2550 50  0001 C CNN
	1    1600 2550
	0    1    1    0   
$EndComp
$Comp
L Isolator:SFH617A-1 U1
U 1 1 5E90FC54
P 2200 2050
F 0 "U1" H 2200 2375 50  0000 C CNN
F 1 "PC123" H 2200 2284 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 2000 1850 50  0001 L CIN
F 3 "https://global.sharp/products/device/lineup/data/pdf/datasheet/PC123XxYSZ1B_e.pdf" H 2200 2050 50  0001 L CNN
	1    2200 2050
	1    0    0    -1  
$EndComp
$Comp
L Isolator:SFH617A-1 U2
U 1 1 5E910B34
P 2200 2650
F 0 "U2" H 2200 2975 50  0000 C CNN
F 1 "PC123" H 2200 2884 50  0000 C CNN
F 2 "Package_DIP:DIP-4_W7.62mm" H 2000 2450 50  0001 L CIN
F 3 "https://global.sharp/products/device/lineup/data/pdf/datasheet/PC123XxYSZ1B_e.pdf" H 2200 2650 50  0001 L CNN
	1    2200 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	1750 1950 1900 1950
Wire Wire Line
	1750 2550 1900 2550
Wire Wire Line
	1300 2100 1300 1950
Wire Wire Line
	1300 1950 1450 1950
Wire Wire Line
	1300 2300 1300 2550
Wire Wire Line
	1300 2550 1450 2550
Wire Wire Line
	1400 2200 1400 2150
Wire Wire Line
	1400 2150 1900 2150
Wire Wire Line
	1900 2750 1200 2750
Wire Wire Line
	1200 2750 1200 2400
$Comp
L Device:R_US R3
U 1 1 5E91D324
P 2600 1700
F 0 "R3" H 2532 1654 50  0000 R CNN
F 1 "4k7" H 2532 1745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2640 1690 50  0001 C CNN
F 3 "~" H 2600 1700 50  0001 C CNN
	1    2600 1700
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R4
U 1 1 5E91DA72
P 2900 1700
F 0 "R4" H 2832 1654 50  0000 R CNN
F 1 "4k7" H 2832 1745 50  0000 R CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 2940 1690 50  0001 C CNN
F 3 "~" H 2900 1700 50  0001 C CNN
	1    2900 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2500 1950 2600 1950
Wire Wire Line
	2600 1950 2600 1850
Wire Wire Line
	2600 1550 2600 1450
Wire Wire Line
	2900 1450 2900 1550
Wire Wire Line
	2900 1850 2900 2550
Wire Wire Line
	2900 2550 2500 2550
$Comp
L power:GND #PWR06
U 1 1 5E926F1A
P 2600 2250
F 0 "#PWR06" H 2600 2000 50  0001 C CNN
F 1 "GND" H 2605 2077 50  0000 C CNN
F 2 "" H 2600 2250 50  0001 C CNN
F 3 "" H 2600 2250 50  0001 C CNN
	1    2600 2250
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR07
U 1 1 5E9271A0
P 2600 2850
F 0 "#PWR07" H 2600 2600 50  0001 C CNN
F 1 "GND" H 2605 2677 50  0000 C CNN
F 2 "" H 2600 2850 50  0001 C CNN
F 3 "" H 2600 2850 50  0001 C CNN
	1    2600 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 2150 2600 2150
Wire Wire Line
	2600 2150 2600 2250
Wire Wire Line
	2500 2750 2600 2750
Wire Wire Line
	2600 2750 2600 2850
$Comp
L 74xx:74HC14 U3
U 1 1 5E928DAF
P 3500 1950
F 0 "U3" H 3500 2267 50  0000 C CNN
F 1 "74HC14" H 3500 2176 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 3500 1950 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 3500 1950 50  0001 C CNN
	1    3500 1950
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U3
U 2 1 5E92A749
P 3500 3450
F 0 "U3" H 3500 3767 50  0000 C CNN
F 1 "74HC14" H 3500 3676 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 3500 3450 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 3500 3450 50  0001 C CNN
	2    3500 3450
	1    0    0    -1  
$EndComp
$Comp
L 74xx:74HC14 U3
U 7 1 5E92B7B1
P 2350 3850
F 0 "U3" H 2580 3896 50  0000 L CNN
F 1 "74HC14" H 2580 3805 50  0000 L CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 2350 3850 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 2350 3850 50  0001 C CNN
	7    2350 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 1950 2600 1950
Connection ~ 2600 1950
Connection ~ 2900 2550
Wire Wire Line
	2900 2550 3200 2550
$Comp
L power:GND #PWR04
U 1 1 5E940D52
P 2350 4400
F 0 "#PWR04" H 2350 4150 50  0001 C CNN
F 1 "GND" H 2355 4227 50  0000 C CNN
F 2 "" H 2350 4400 50  0001 C CNN
F 3 "" H 2350 4400 50  0001 C CNN
	1    2350 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2350 4400 2350 4350
Wire Wire Line
	2350 3350 2350 3300
Wire Wire Line
	4600 1950 3900 1950
Wire Wire Line
	4600 3450 3800 3450
Wire Wire Line
	4600 2050 4550 2050
Wire Wire Line
	4550 2050 4550 2550
Wire Wire Line
	4550 3550 4600 3550
Wire Wire Line
	3800 2550 4150 2550
Wire Wire Line
	4550 2550 4550 3550
Connection ~ 4550 2550
Wire Wire Line
	3900 3000 3100 3000
Wire Wire Line
	3100 3000 3100 3450
Wire Wire Line
	3100 3450 3200 3450
Wire Wire Line
	3900 1950 3900 3000
Connection ~ 3900 1950
Wire Wire Line
	3900 1950 3800 1950
$Comp
L power:VCC #PWR015
U 1 1 5E96E43D
P 4900 2850
F 0 "#PWR015" H 4900 2700 50  0001 C CNN
F 1 "VCC" H 5000 2900 50  0000 C CNN
F 2 "" H 4900 2850 50  0001 C CNN
F 3 "" H 4900 2850 50  0001 C CNN
	1    4900 2850
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR013
U 1 1 5E971253
P 4900 1350
F 0 "#PWR013" H 4900 1200 50  0001 C CNN
F 1 "VCC" H 4917 1523 50  0000 C CNN
F 2 "" H 4900 1350 50  0001 C CNN
F 3 "" H 4900 1350 50  0001 C CNN
	1    4900 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 1350 4900 1400
Wire Wire Line
	4900 2950 4900 2900
$Comp
L Device:C C4
U 1 1 5E973839
P 4450 1600
F 0 "C4" H 4250 1650 50  0000 L CNN
F 1 "100n" H 4150 1550 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4488 1450 50  0001 C CNN
F 3 "~" H 4450 1600 50  0001 C CNN
	1    4450 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 1450 4450 1400
Wire Wire Line
	4450 1400 4900 1400
Connection ~ 4900 1400
Wire Wire Line
	4900 1400 4900 1450
$Comp
L Device:C C5
U 1 1 5E9775B4
P 4450 3100
F 0 "C5" H 4250 3150 50  0000 L CNN
F 1 "100n" H 4150 3050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4488 2950 50  0001 C CNN
F 3 "~" H 4450 3100 50  0001 C CNN
	1    4450 3100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2950 4450 2900
Wire Wire Line
	4450 2900 4900 2900
Connection ~ 4900 2900
Wire Wire Line
	4900 2900 4900 2850
Wire Wire Line
	4450 2500 4800 2500
Wire Wire Line
	4900 2500 4900 2450
$Comp
L power:GND #PWR016
U 1 1 5E97D486
P 4900 4050
F 0 "#PWR016" H 4900 3800 50  0001 C CNN
F 1 "GND" H 4905 3877 50  0000 C CNN
F 2 "" H 4900 4050 50  0001 C CNN
F 3 "" H 4900 4050 50  0001 C CNN
	1    4900 4050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR014
U 1 1 5E97D867
P 4900 2550
F 0 "#PWR014" H 4900 2300 50  0001 C CNN
F 1 "GND" H 5050 2450 50  0000 C CNN
F 2 "" H 4900 2550 50  0001 C CNN
F 3 "" H 4900 2550 50  0001 C CNN
	1    4900 2550
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 2550 4900 2500
Connection ~ 4900 2500
$Comp
L Diode:1N4007 D2
U 1 1 5E982D0F
P 5600 2900
F 0 "D2" H 5600 2684 50  0000 C CNN
F 1 "1N4007" H 5600 2775 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5600 2725 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5600 2900 50  0001 C CNN
	1    5600 2900
	-1   0    0    1   
$EndComp
$Comp
L Diode:1N4007 D1
U 1 1 5E984843
P 5600 1400
F 0 "D1" H 5600 1184 50  0000 C CNN
F 1 "1N4007" H 5600 1275 50  0000 C CNN
F 2 "Diode_THT:D_DO-41_SOD81_P10.16mm_Horizontal" H 5600 1225 50  0001 C CNN
F 3 "http://www.vishay.com/docs/88503/1n4001.pdf" H 5600 1400 50  0001 C CNN
	1    5600 1400
	-1   0    0    1   
$EndComp
$Comp
L Device:C C11
U 1 1 5E98CB89
P 5750 3450
F 0 "C11" H 5550 3550 50  0000 L CNN
F 1 "470n" H 5550 3350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5788 3300 50  0001 C CNN
F 3 "~" H 5750 3450 50  0001 C CNN
	1    5750 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C10
U 1 1 5E98D098
P 5750 1950
F 0 "C10" H 5550 2050 50  0000 L CNN
F 1 "470n" H 5550 1850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5788 1800 50  0001 C CNN
F 3 "~" H 5750 1950 50  0001 C CNN
	1    5750 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  2100 1300 2100
Wire Wire Line
	750  2200 1400 2200
Wire Wire Line
	750  2300 1300 2300
Wire Wire Line
	750  2400 1200 2400
Text Label 800  2100 0    50   ~ 0
pwm_signal
Text Label 800  2300 0    50   ~ 0
select
$Comp
L Transistor_FET:IRF3205 Q2
U 1 1 5E9A7675
P 6850 2900
F 0 "Q2" H 6550 2950 50  0000 L CNN
F 1 "IRF3205" H 6500 2850 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7100 2825 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 6850 2900 50  0001 L CNN
	1    6850 2900
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF3205 Q4
U 1 1 5E9A800C
P 7300 2900
F 0 "Q4" H 7505 2946 50  0000 L CNN
F 1 "IRF3205" H 7505 2855 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7550 2825 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 7300 2900 50  0001 L CNN
	1    7300 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 2700 7150 2700
Wire Wire Line
	6950 3100 7150 3100
Wire Wire Line
	7100 2900 7100 3050
Wire Wire Line
	6550 3050 7100 3050
Wire Wire Line
	6650 2900 6550 2900
Wire Wire Line
	6250 2900 6200 2900
Wire Wire Line
	6200 2900 6200 3050
Wire Wire Line
	6200 3050 6250 3050
$Comp
L Transistor_FET:IRF3205 Q1
U 1 1 5E9CA883
P 6850 2000
F 0 "Q1" H 6550 2050 50  0000 L CNN
F 1 "IRF3205" H 6500 1950 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7100 1925 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 6850 2000 50  0001 L CNN
	1    6850 2000
	1    0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF3205 Q3
U 1 1 5E9CA889
P 7300 2000
F 0 "Q3" H 7505 2046 50  0000 L CNN
F 1 "IRF3205" H 7505 1955 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 7550 1925 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 7300 2000 50  0001 L CNN
	1    7300 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6950 1800 7150 1800
Wire Wire Line
	6950 2200 7150 2200
Wire Wire Line
	7100 2000 7100 2150
$Comp
L Device:R_US R10
U 1 1 5E9CA898
P 6400 2000
F 0 "R10" V 6195 2000 50  0000 C CNN
F 1 "4.7" V 6286 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6440 1990 50  0001 C CNN
F 3 "~" H 6400 2000 50  0001 C CNN
	1    6400 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	6550 2150 7100 2150
Wire Wire Line
	6650 2000 6550 2000
Wire Wire Line
	6250 2000 6200 2000
Wire Wire Line
	6200 2000 6200 2150
Wire Wire Line
	6200 2150 6250 2150
$Comp
L Device:R_US R11
U 1 1 5E9CDF5F
P 6400 2150
F 0 "R11" V 6600 2150 50  0000 C CNN
F 1 "4.7" V 6500 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6440 2140 50  0001 C CNN
F 3 "~" H 6400 2150 50  0001 C CNN
	1    6400 2150
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R13
U 1 1 5E9CF618
P 6400 3050
F 0 "R13" V 6600 3050 50  0000 C CNN
F 1 "4.7" V 6500 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6440 3040 50  0001 C CNN
F 3 "~" H 6400 3050 50  0001 C CNN
	1    6400 3050
	0    1    1    0   
$EndComp
$Comp
L Device:R_US R12
U 1 1 5E9CFAD4
P 6400 2900
F 0 "R12" V 6195 2900 50  0000 C CNN
F 1 "4.7" V 6286 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 6440 2890 50  0001 C CNN
F 3 "~" H 6400 2900 50  0001 C CNN
	1    6400 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	7150 2200 7150 2450
Connection ~ 7150 2200
Wire Wire Line
	7150 2200 7400 2200
Connection ~ 7150 2700
Wire Wire Line
	7150 2700 7400 2700
Wire Wire Line
	7150 1550 7950 1550
Connection ~ 7150 1800
Wire Wire Line
	7150 1800 7400 1800
Wire Wire Line
	7150 3350 7950 3350
Connection ~ 7150 3100
Wire Wire Line
	7150 3100 7400 3100
Wire Wire Line
	7150 2450 7950 2450
Connection ~ 7150 2450
Wire Wire Line
	7150 2450 7150 2700
$Comp
L Device:D_Schottky D3
U 1 1 5E9E4827
P 7950 2000
F 0 "D3" V 7904 2079 50  0000 L CNN
F 1 "80SQ045" V 7995 2079 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 7950 2000 50  0001 C CNN
F 3 "~" H 7950 2000 50  0001 C CNN
	1    7950 2000
	0    1    1    0   
$EndComp
Wire Wire Line
	7950 1550 7950 1850
Wire Wire Line
	7950 2750 7950 2450
Wire Wire Line
	7950 2150 7950 2450
Connection ~ 7950 2450
$Comp
L Transistor_FET:IRF3205 Q8
U 1 1 5EA073E4
P 10150 2900
F 0 "Q8" H 9850 2950 50  0000 L CNN
F 1 "IRF3205" H 9800 2850 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 10400 2825 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 10150 2900 50  0001 L CNN
	1    10150 2900
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF3205 Q6
U 1 1 5EA073EA
P 9700 2900
F 0 "Q6" H 9905 2946 50  0000 L CNN
F 1 "IRF3205" H 9905 2855 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9950 2825 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 9700 2900 50  0001 L CNN
	1    9700 2900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10050 2700 9850 2700
Wire Wire Line
	10050 3100 9850 3100
Wire Wire Line
	9900 2900 9900 3050
Wire Wire Line
	10450 3050 9900 3050
Wire Wire Line
	10350 2900 10450 2900
Wire Wire Line
	10750 2900 10800 2900
Wire Wire Line
	10800 2900 10800 3050
Wire Wire Line
	10800 3050 10750 3050
$Comp
L Transistor_FET:IRF3205 Q7
U 1 1 5EA073F8
P 10150 2000
F 0 "Q7" H 9850 2050 50  0000 L CNN
F 1 "IRF3205" H 9800 1950 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 10400 1925 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 10150 2000 50  0001 L CNN
	1    10150 2000
	-1   0    0    -1  
$EndComp
$Comp
L Transistor_FET:IRF3205 Q5
U 1 1 5EA073FE
P 9700 2000
F 0 "Q5" H 9905 2046 50  0000 L CNN
F 1 "IRF3205" H 9905 1955 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 9950 1925 50  0001 L CIN
F 3 "http://www.irf.com/product-info/datasheets/data/irf3205.pdf" H 9700 2000 50  0001 L CNN
	1    9700 2000
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10050 1800 9850 1800
Wire Wire Line
	10050 2200 9850 2200
Wire Wire Line
	9900 2000 9900 2150
$Comp
L Device:R_US R14
U 1 1 5EA07407
P 10600 2000
F 0 "R14" V 10395 2000 50  0000 C CNN
F 1 "4.7" V 10486 2000 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10640 1990 50  0001 C CNN
F 3 "~" H 10600 2000 50  0001 C CNN
	1    10600 2000
	0    -1   1    0   
$EndComp
Wire Wire Line
	10450 2150 9900 2150
Wire Wire Line
	10750 2000 10800 2000
Wire Wire Line
	10800 2000 10800 2150
Wire Wire Line
	10800 2150 10750 2150
$Comp
L Device:R_US R15
U 1 1 5EA07412
P 10600 2150
F 0 "R15" V 10800 2150 50  0000 C CNN
F 1 "4.7" V 10700 2150 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10640 2140 50  0001 C CNN
F 3 "~" H 10600 2150 50  0001 C CNN
	1    10600 2150
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R17
U 1 1 5EA07418
P 10600 3050
F 0 "R17" V 10800 3050 50  0000 C CNN
F 1 "4.7" V 10700 3050 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10640 3040 50  0001 C CNN
F 3 "~" H 10600 3050 50  0001 C CNN
	1    10600 3050
	0    -1   1    0   
$EndComp
$Comp
L Device:R_US R16
U 1 1 5EA0741E
P 10600 2900
F 0 "R16" V 10395 2900 50  0000 C CNN
F 1 "4.7" V 10486 2900 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 10640 2890 50  0001 C CNN
F 3 "~" H 10600 2900 50  0001 C CNN
	1    10600 2900
	0    -1   1    0   
$EndComp
Wire Wire Line
	9850 2200 9850 2450
Connection ~ 9850 2200
Wire Wire Line
	9850 2200 9600 2200
Connection ~ 9850 2700
Wire Wire Line
	9850 2700 9600 2700
Connection ~ 9850 1800
Wire Wire Line
	9850 1800 9600 1800
Connection ~ 9850 3100
Wire Wire Line
	9850 3100 9600 3100
Connection ~ 9850 2450
Wire Wire Line
	9850 2450 9850 2700
Wire Wire Line
	9050 2750 9050 2450
Wire Wire Line
	9050 2150 9050 2450
Connection ~ 9050 2450
Wire Wire Line
	5200 1750 5850 1750
Wire Wire Line
	5850 1750 5850 2000
Connection ~ 7950 1550
Wire Wire Line
	7950 3350 8500 3350
Connection ~ 7950 3350
Wire Wire Line
	9050 3350 9850 3350
Wire Wire Line
	10900 3050 10800 3050
Connection ~ 10800 3050
Wire Wire Line
	11000 3650 11000 2450
Wire Wire Line
	11000 2450 9850 2450
Wire Wire Line
	9050 2450 9850 2450
Wire Wire Line
	11100 3550 11100 2150
Wire Wire Line
	11100 2150 10800 2150
Connection ~ 10800 2150
Wire Wire Line
	7950 3050 7950 3350
Wire Wire Line
	9050 3050 9050 3350
Wire Wire Line
	7150 3100 7150 3350
Wire Wire Line
	9850 3100 9850 3350
Wire Wire Line
	7150 1800 7150 1550
Wire Wire Line
	9850 1800 9850 1550
$Comp
L Device:D_Schottky D4
U 1 1 5EAA7ED1
P 7950 2900
F 0 "D4" V 7904 2979 50  0000 L CNN
F 1 "80SQ045" V 7995 2979 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 7950 2900 50  0001 C CNN
F 3 "~" H 7950 2900 50  0001 C CNN
	1    7950 2900
	0    1    1    0   
$EndComp
$Comp
L Device:D_Schottky D6
U 1 1 5EAAF111
P 9050 2900
F 0 "D6" V 9004 2979 50  0000 L CNN
F 1 "80SQ045" V 9095 2979 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 9050 2900 50  0001 C CNN
F 3 "~" H 9050 2900 50  0001 C CNN
	1    9050 2900
	0    -1   1    0   
$EndComp
$Comp
L Device:D_Schottky D5
U 1 1 5EAB4C88
P 9050 2000
F 0 "D5" V 9004 2079 50  0000 L CNN
F 1 "80SQ045" V 9095 2079 50  0000 L CNN
F 2 "Diode_THT:D_DO-201AD_P12.70mm_Horizontal" H 9050 2000 50  0001 C CNN
F 3 "~" H 9050 2000 50  0001 C CNN
	1    9050 2000
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR020
U 1 1 5EABED05
P 8500 3400
F 0 "#PWR020" H 8500 3150 50  0001 C CNN
F 1 "GND" H 8650 3300 50  0000 C CNN
F 2 "" H 8500 3400 50  0001 C CNN
F 3 "" H 8500 3400 50  0001 C CNN
	1    8500 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 3400 8500 3350
$Comp
L power:VCC #PWR019
U 1 1 5EAC7951
P 8500 1500
F 0 "#PWR019" H 8500 1350 50  0001 C CNN
F 1 "VCC" H 8517 1673 50  0000 C CNN
F 2 "" H 8500 1500 50  0001 C CNN
F 3 "" H 8500 1500 50  0001 C CNN
	1    8500 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	8500 1500 8500 1550
Wire Wire Line
	8500 1550 7950 1550
$Comp
L Device:CP1 C13
U 1 1 5EAD0241
P 6800 1500
F 0 "C13" H 6915 1546 50  0000 L CNN
F 1 "220u" H 6915 1455 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 6800 1500 50  0001 C CNN
F 3 "~" H 6800 1500 50  0001 C CNN
	1    6800 1500
	1    0    0    -1  
$EndComp
$Comp
L Device:C C12
U 1 1 5EAD32A2
P 6400 1500
F 0 "C12" H 6515 1546 50  0000 L CNN
F 1 "470n" H 6515 1455 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W5.0mm_P10.00mm_FKS3_FKP3_MKS4" H 6438 1350 50  0001 C CNN
F 3 "~" H 6400 1500 50  0001 C CNN
	1    6400 1500
	1    0    0    -1  
$EndComp
Wire Wire Line
	6400 1350 6400 1300
Wire Wire Line
	6400 1300 6800 1300
Wire Wire Line
	7150 1300 7150 1550
Connection ~ 7150 1550
Wire Wire Line
	6800 1350 6800 1300
Connection ~ 6800 1300
Wire Wire Line
	6800 1650 6800 1700
Wire Wire Line
	6800 1700 6600 1700
Wire Wire Line
	6400 1700 6400 1650
$Comp
L power:GND #PWR018
U 1 1 5EAF3C87
P 6600 1750
F 0 "#PWR018" H 6600 1500 50  0001 C CNN
F 1 "GND" H 6750 1650 50  0000 C CNN
F 2 "" H 6600 1750 50  0001 C CNN
F 3 "" H 6600 1750 50  0001 C CNN
	1    6600 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 1750 6600 1700
Connection ~ 6600 1700
Wire Wire Line
	6600 1700 6400 1700
$Comp
L Device:CP1 C14
U 1 1 5EB1060A
P 10200 1500
F 0 "C14" H 10450 1550 50  0000 R CNN
F 1 "220u" H 10500 1450 50  0000 R CNN
F 2 "Capacitor_THT:CP_Radial_D10.0mm_P5.00mm" H 10200 1500 50  0001 C CNN
F 3 "~" H 10200 1500 50  0001 C CNN
	1    10200 1500
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C15
U 1 1 5EB10610
P 10600 1500
F 0 "C15" H 10715 1546 50  0000 L CNN
F 1 "470n" H 10715 1455 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L13.0mm_W5.0mm_P10.00mm_FKS3_FKP3_MKS4" H 10638 1350 50  0001 C CNN
F 3 "~" H 10600 1500 50  0001 C CNN
	1    10600 1500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	10600 1350 10600 1300
Wire Wire Line
	10600 1300 10200 1300
Wire Wire Line
	9850 1300 9850 1550
Connection ~ 9850 1550
Wire Wire Line
	10200 1350 10200 1300
Connection ~ 10200 1300
Wire Wire Line
	10200 1650 10200 1700
Wire Wire Line
	10600 1700 10600 1650
Wire Wire Line
	10200 1700 10400 1700
$Comp
L power:GND #PWR021
U 1 1 5EB1F401
P 10400 1750
F 0 "#PWR021" H 10400 1500 50  0001 C CNN
F 1 "GND" H 10250 1650 50  0000 C CNN
F 2 "" H 10400 1750 50  0001 C CNN
F 3 "" H 10400 1750 50  0001 C CNN
	1    10400 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	10400 1750 10400 1700
Connection ~ 10400 1700
Wire Wire Line
	10400 1700 10600 1700
Wire Wire Line
	6800 1300 7150 1300
Wire Wire Line
	10350 2000 10450 2000
Wire Wire Line
	9850 1300 10200 1300
$Comp
L Device:C C1
U 1 1 5EB609F6
P 2800 3500
F 0 "C1" H 2915 3546 50  0000 L CNN
F 1 "100n" H 2915 3455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 2838 3350 50  0001 C CNN
F 3 "~" H 2800 3500 50  0001 C CNN
	1    2800 3500
	1    0    0    -1  
$EndComp
Connection ~ 2350 3300
Wire Wire Line
	2350 3300 2350 3250
Wire Wire Line
	2800 3650 2800 3700
Wire Wire Line
	2800 3350 2800 3300
Wire Wire Line
	2350 3300 2800 3300
$Comp
L power:GND #PWR08
U 1 1 5EB7BF43
P 2800 3700
F 0 "#PWR08" H 2800 3450 50  0001 C CNN
F 1 "GND" H 2950 3600 50  0000 C CNN
F 2 "" H 2800 3700 50  0001 C CNN
F 3 "" H 2800 3700 50  0001 C CNN
	1    2800 3700
	1    0    0    -1  
$EndComp
Wire Wire Line
	10900 3050 10900 3750
Wire Wire Line
	5850 2000 6200 2000
Connection ~ 6200 2000
Text Label 5850 2000 0    50   ~ 0
left_high
Text Label 5850 2650 0    50   ~ 0
left_low
Text Label 5850 2450 0    50   ~ 0
left_motor
Text Label 5850 3550 0    50   ~ 0
right_high
Text Label 5850 3650 0    50   ~ 0
right_motor
Text Label 5850 3750 0    50   ~ 0
right_low
Text Label 3950 2550 0    50   ~ 0
!enable
Text Label 3950 1950 0    50   ~ 0
pwm_left
Text Label 3950 3450 0    50   ~ 0
pwm_right
$Comp
L Connector:Screw_Terminal_01x02 J3
U 1 1 5EC06F32
P 8450 2200
F 0 "J3" V 8414 2012 50  0000 R CNN
F 1 "motor" V 8323 2012 50  0000 R CNN
F 2 "Connector_Wire:SolderWirePad_1x02_P7.62mm_Drill2.5mm" H 8450 2200 50  0001 C CNN
F 3 "~" H 8450 2200 50  0001 C CNN
	1    8450 2200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	8550 2400 8550 2450
Wire Wire Line
	8450 2400 8450 2450
Wire Wire Line
	8450 2450 7950 2450
Wire Wire Line
	5200 3750 10900 3750
Wire Wire Line
	8550 2450 9050 2450
Wire Wire Line
	9050 3350 8500 3350
Connection ~ 9050 3350
Connection ~ 8500 3350
Connection ~ 8500 1550
Wire Wire Line
	8500 1550 9050 1550
Wire Wire Line
	9850 1550 9050 1550
Connection ~ 9050 1550
Wire Wire Line
	9050 1550 9050 1850
$Comp
L Connector:Screw_Terminal_01x02 J2
U 1 1 5EC5F22F
P 1250 5150
F 0 "J2" H 1168 5367 50  0000 C CNN
F 1 "voltage_in" H 1168 5276 50  0000 C CNN
F 2 "Connector_Wire:SolderWirePad_1x02_P7.62mm_Drill2.5mm" H 1250 5150 50  0001 C CNN
F 3 "~" H 1250 5150 50  0001 C CNN
	1    1250 5150
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1450 5150 1550 5150
Wire Wire Line
	1550 5150 1550 5050
Wire Wire Line
	1450 5250 1550 5250
Wire Wire Line
	1550 5250 1550 5350
$Comp
L power:GND #PWR02
U 1 1 5EC7D88F
P 1550 5350
F 0 "#PWR02" H 1550 5100 50  0001 C CNN
F 1 "GND" H 1555 5177 50  0000 C CNN
F 2 "" H 1550 5350 50  0001 C CNN
F 3 "" H 1550 5350 50  0001 C CNN
	1    1550 5350
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR01
U 1 1 5EC80F75
P 1550 5050
F 0 "#PWR01" H 1550 4900 50  0001 C CNN
F 1 "VCC" H 1567 5223 50  0000 C CNN
F 2 "" H 1550 5050 50  0001 C CNN
F 3 "" H 1550 5050 50  0001 C CNN
	1    1550 5050
	1    0    0    -1  
$EndComp
$Comp
L power:VCC #PWR010
U 1 1 5EC8F4A8
P 3500 5100
F 0 "#PWR010" H 3500 4950 50  0001 C CNN
F 1 "VCC" H 3517 5273 50  0000 C CNN
F 2 "" H 3500 5100 50  0001 C CNN
F 3 "" H 3500 5100 50  0001 C CNN
	1    3500 5100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5EC8FE76
P 3900 6050
F 0 "#PWR011" H 3900 5800 50  0001 C CNN
F 1 "GND" H 3905 5877 50  0000 C CNN
F 2 "" H 3900 6050 50  0001 C CNN
F 3 "" H 3900 6050 50  0001 C CNN
	1    3900 6050
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 5200 3500 5200
Wire Wire Line
	3500 5200 3500 5100
$Comp
L Device:C C3
U 1 1 5ECAD922
P 3350 5400
F 0 "C3" H 3465 5446 50  0000 L CNN
F 1 "100n" H 3465 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 3388 5250 50  0001 C CNN
F 3 "~" H 3350 5400 50  0001 C CNN
	1    3350 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5ECAE47E
P 4500 5400
F 0 "C6" H 4615 5446 50  0000 L CNN
F 1 "100n" H 4615 5355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 4538 5250 50  0001 C CNN
F 3 "~" H 4500 5400 50  0001 C CNN
	1    4500 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4500 5200 4500 5250
Wire Wire Line
	4500 5550 4500 5600
Wire Wire Line
	3350 5600 3350 5550
Wire Wire Line
	3350 5250 3350 5200
Wire Wire Line
	3350 5200 3500 5200
Connection ~ 3500 5200
$Comp
L Device:CP1 C2
U 1 1 5ECE2E7F
P 2950 5400
F 0 "C2" H 3065 5446 50  0000 L CNN
F 1 "10u" H 3065 5355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 2950 5400 50  0001 C CNN
F 3 "~" H 2950 5400 50  0001 C CNN
	1    2950 5400
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C7
U 1 1 5ECE664C
P 4900 5400
F 0 "C7" H 5015 5446 50  0000 L CNN
F 1 "1u" H 5015 5355 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.50mm" H 4900 5400 50  0001 C CNN
F 3 "~" H 4900 5400 50  0001 C CNN
	1    4900 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4900 5250 4900 5200
Wire Wire Line
	4900 5200 4500 5200
Connection ~ 4500 5200
Wire Wire Line
	4900 5550 4900 5600
Wire Wire Line
	4900 5600 4500 5600
Wire Wire Line
	3350 5600 2950 5600
Wire Wire Line
	2950 5600 2950 5550
Wire Wire Line
	2950 5250 2950 5200
Wire Wire Line
	2950 5200 3350 5200
Connection ~ 3350 5200
Wire Wire Line
	4900 3950 4900 4000
Wire Wire Line
	4900 4000 4800 4000
Connection ~ 4900 4000
Wire Wire Line
	4900 4000 4900 4050
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5ED69A55
P 1650 5150
F 0 "#FLG01" H 1650 5225 50  0001 C CNN
F 1 "PWR_FLAG" V 1650 5278 50  0000 L CNN
F 2 "" H 1650 5150 50  0001 C CNN
F 3 "~" H 1650 5150 50  0001 C CNN
	1    1650 5150
	0    1    1    0   
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5ED69CF4
P 1650 5250
F 0 "#FLG02" H 1650 5325 50  0001 C CNN
F 1 "PWR_FLAG" V 1650 5378 50  0000 L CNN
F 2 "" H 1650 5250 50  0001 C CNN
F 3 "~" H 1650 5250 50  0001 C CNN
	1    1650 5250
	0    1    1    0   
$EndComp
Wire Wire Line
	1650 5150 1550 5150
Connection ~ 1550 5150
Wire Wire Line
	1650 5250 1550 5250
Connection ~ 1550 5250
$Comp
L Driver_FET:IR21844 U5
U 1 1 5E942096
P 4900 1950
F 0 "U5" H 4750 2450 50  0000 C CNN
F 1 "IR21844" H 5100 2400 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 4900 1950 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4" H 4900 1950 50  0001 C CNN
	1    4900 1950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2450 4800 2500
Connection ~ 4800 2500
Wire Wire Line
	4800 2500 4900 2500
$Comp
L Device:C C8
U 1 1 5E97398E
P 5400 1950
F 0 "C8" H 5200 2000 50  0000 L CNN
F 1 "470n" H 5200 1850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5438 1800 50  0001 C CNN
F 3 "~" H 5400 1950 50  0001 C CNN
	1    5400 1950
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R6
U 1 1 5E98D959
P 4350 2300
F 0 "R6" H 4450 2350 50  0000 C CNN
F 1 "RDT" H 4450 2250 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4390 2290 50  0001 C CNN
F 3 "~" H 4350 2300 50  0001 C CNN
	1    4350 2300
	-1   0    0    1   
$EndComp
Wire Wire Line
	4350 2150 4600 2150
Wire Wire Line
	4350 2450 4350 2500
Wire Wire Line
	4350 2500 4450 2500
Connection ~ 4450 2500
$Comp
L Driver_FET:IR21844 U6
U 1 1 5E9B7059
P 4900 3450
F 0 "U6" H 4750 3900 50  0000 C CNN
F 1 "IR21844" H 5100 3900 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 4900 3450 50  0001 C CIN
F 3 "https://www.infineon.com/dgdl/ir2184.pdf?fileId=5546d462533600a4015355c955e616d4" H 4900 3450 50  0001 C CNN
	1    4900 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 3950 4800 4000
Connection ~ 4800 4000
Wire Wire Line
	4800 4000 4450 4000
$Comp
L Device:R_US R7
U 1 1 5E9C6EDC
P 4350 3800
F 0 "R7" H 4450 3850 50  0000 C CNN
F 1 "RDT" H 4450 3750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4390 3790 50  0001 C CNN
F 3 "~" H 4350 3800 50  0001 C CNN
	1    4350 3800
	-1   0    0    1   
$EndComp
Wire Wire Line
	4350 3950 4350 4000
Wire Wire Line
	4350 4000 4450 4000
Connection ~ 4450 4000
Wire Wire Line
	4350 3650 4600 3650
$Comp
L Device:C C9
U 1 1 5E9E6010
P 5400 3450
F 0 "C9" H 5200 3500 50  0000 L CNN
F 1 "470n" H 5200 3350 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" H 5438 3300 50  0001 C CNN
F 3 "~" H 5400 3450 50  0001 C CNN
	1    5400 3450
	1    0    0    -1  
$EndComp
Wire Wire Line
	5850 2150 5850 2450
Wire Wire Line
	7150 2450 5850 2450
Wire Wire Line
	5200 2250 5750 2250
Wire Wire Line
	4450 3250 4450 4000
Wire Wire Line
	5200 2150 5750 2150
Wire Wire Line
	5750 1400 5750 1650
Wire Wire Line
	5750 2100 5750 2150
Connection ~ 5750 2150
Wire Wire Line
	5750 2150 5850 2150
Wire Wire Line
	5200 1650 5750 1650
Connection ~ 5750 1650
Wire Wire Line
	5750 1650 5750 1800
Wire Wire Line
	4900 1400 5400 1400
Wire Wire Line
	5400 1800 5400 1400
Connection ~ 5400 1400
Wire Wire Line
	5400 1400 5450 1400
Wire Wire Line
	5400 2100 5400 2500
Wire Wire Line
	5400 2500 4900 2500
Wire Wire Line
	4450 1750 4450 2500
Wire Wire Line
	5850 3250 5850 3550
Wire Wire Line
	5200 3250 5850 3250
Wire Wire Line
	11100 3550 5850 3550
Wire Wire Line
	6200 2900 6200 2650
Wire Wire Line
	6200 2650 5750 2650
Wire Wire Line
	5750 2650 5750 2250
Connection ~ 6200 2900
Wire Wire Line
	5200 3650 5750 3650
Wire Wire Line
	5750 3600 5750 3650
Connection ~ 5750 3650
Wire Wire Line
	5750 3650 11000 3650
Wire Wire Line
	5750 3300 5750 3150
Wire Wire Line
	5400 3600 5400 4000
Wire Wire Line
	4900 4000 5400 4000
Wire Wire Line
	5400 3300 5400 2900
Wire Wire Line
	4900 2900 5400 2900
Wire Wire Line
	5400 2900 5450 2900
Connection ~ 5400 2900
Wire Wire Line
	5200 3150 5750 3150
Connection ~ 5750 3150
Wire Wire Line
	5750 3150 5750 2900
$Comp
L Regulator_Linear:LM317_3PinPackage U4
U 1 1 5EC95543
P 3900 5200
F 0 "U4" H 3900 5442 50  0000 C CNN
F 1 "LM317" H 3900 5351 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Horizontal_TabDown" H 3900 5450 50  0001 C CIN
F 3 "http://www.ti.com/lit/ds/symlink/lm317.pdf" H 3900 5200 50  0001 C CNN
	1    3900 5200
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR017
U 1 1 5ECA7A09
P 5450 5100
F 0 "#PWR017" H 5450 4950 50  0001 C CNN
F 1 "+3.3V" H 5465 5273 50  0000 C CNN
F 2 "" H 5450 5100 50  0001 C CNN
F 3 "" H 5450 5100 50  0001 C CNN
	1    5450 5100
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR03
U 1 1 5ECA81FD
P 2350 3250
F 0 "#PWR03" H 2350 3100 50  0001 C CNN
F 1 "+3.3V" H 2365 3423 50  0000 C CNN
F 2 "" H 2350 3250 50  0001 C CNN
F 3 "" H 2350 3250 50  0001 C CNN
	1    2350 3250
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR09
U 1 1 5ECB2684
P 2900 1450
F 0 "#PWR09" H 2900 1300 50  0001 C CNN
F 1 "+3.3V" H 2915 1623 50  0000 C CNN
F 2 "" H 2900 1450 50  0001 C CNN
F 3 "" H 2900 1450 50  0001 C CNN
	1    2900 1450
	1    0    0    -1  
$EndComp
$Comp
L power:+3.3V #PWR05
U 1 1 5ECB2E2B
P 2600 1450
F 0 "#PWR05" H 2600 1300 50  0001 C CNN
F 1 "+3.3V" H 2615 1623 50  0000 C CNN
F 2 "" H 2600 1450 50  0001 C CNN
F 3 "" H 2600 1450 50  0001 C CNN
	1    2600 1450
	1    0    0    -1  
$EndComp
$Comp
L Device:R_US R9
U 1 1 5ECB7A39
P 4300 5800
F 0 "R9" H 4400 5850 50  0000 C CNN
F 1 "390" H 4400 5750 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4340 5790 50  0001 C CNN
F 3 "~" H 4300 5800 50  0001 C CNN
	1    4300 5800
	-1   0    0    1   
$EndComp
$Comp
L Device:R_US R8
U 1 1 5ECB8386
P 4300 5400
F 0 "R8" H 4400 5450 50  0000 C CNN
F 1 "240" H 4400 5350 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4340 5390 50  0001 C CNN
F 3 "~" H 4300 5400 50  0001 C CNN
	1    4300 5400
	-1   0    0    1   
$EndComp
Wire Wire Line
	4300 5200 4300 5250
Wire Wire Line
	4500 5600 4500 6000
Connection ~ 4500 5600
Connection ~ 3350 5600
Wire Wire Line
	4500 6000 4300 6000
Wire Wire Line
	3350 6000 3350 5600
Wire Wire Line
	3900 6000 3900 6050
Wire Wire Line
	3900 6000 3350 6000
Wire Wire Line
	4300 5950 4300 6000
Wire Wire Line
	4300 5200 4500 5200
$Comp
L Device:Jumper_NC_Small JP1
U 1 1 5ED79066
P 5200 5200
F 0 "JP1" H 5200 5321 50  0000 C CNN
F 1 "Jumper_NC_Small" H 5200 5321 50  0001 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5200 5200 50  0001 C CNN
F 3 "~" H 5200 5200 50  0001 C CNN
	1    5200 5200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5450 5100 5450 5200
Wire Wire Line
	5450 5200 5300 5200
Wire Wire Line
	5100 5200 4900 5200
Connection ~ 4900 5200
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5EDADDDE
P 5550 5200
F 0 "#FLG03" H 5550 5275 50  0001 C CNN
F 1 "PWR_FLAG" V 5550 5328 50  0000 L CNN
F 2 "" H 5550 5200 50  0001 C CNN
F 3 "~" H 5550 5200 50  0001 C CNN
	1    5550 5200
	0    1    1    0   
$EndComp
Wire Wire Line
	5550 5200 5450 5200
Connection ~ 5450 5200
$Comp
L Device:R_US R5
U 1 1 5EDC146D
P 4150 2750
F 0 "R5" H 4250 2800 50  0000 C CNN
F 1 "10k" H 4250 2700 50  0000 C CNN
F 2 "Resistor_SMD:R_0805_2012Metric" V 4190 2740 50  0001 C CNN
F 3 "~" H 4150 2750 50  0001 C CNN
	1    4150 2750
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR012
U 1 1 5EDC3552
P 4150 2950
F 0 "#PWR012" H 4150 2700 50  0001 C CNN
F 1 "GND" H 4050 2800 50  0000 C CNN
F 2 "" H 4150 2950 50  0001 C CNN
F 3 "" H 4150 2950 50  0001 C CNN
	1    4150 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 2600 4150 2550
Connection ~ 4150 2550
Wire Wire Line
	4150 2550 4550 2550
Wire Wire Line
	4150 2900 4150 2950
Wire Wire Line
	4300 5550 4300 5600
Wire Wire Line
	4300 5200 4200 5200
Connection ~ 4300 5200
Wire Wire Line
	4300 6000 3900 6000
Connection ~ 4300 6000
Connection ~ 3900 6000
Wire Wire Line
	3900 5600 3900 5500
Wire Wire Line
	3900 5600 4300 5600
Connection ~ 4300 5600
Wire Wire Line
	4300 5600 4300 5650
$Comp
L 74xx:74HC14 U3
U 3 1 5EEFAB55
P 3500 2550
F 0 "U3" H 3500 2867 50  0000 C CNN
F 1 "74HC14" H 3500 2776 50  0000 C CNN
F 2 "Package_DIP:DIP-14_W7.62mm_LongPads" H 3500 2550 50  0001 C CNN
F 3 "http://www.ti.com/lit/gpn/sn74HC14" H 3500 2550 50  0001 C CNN
	3    3500 2550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
