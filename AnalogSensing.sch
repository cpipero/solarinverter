EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:SolarInverter
LIBS:SolarInverter-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 4 6
Title ""
Date "29 jan 2015"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text HLabel 10550 1850 2    59   Output ~ 0
U_sense_P
Text HLabel 10500 6200 2    59   Output ~ 0
I_sense_P
Text HLabel 6250 4100 2    59   Output ~ 0
U_sense_S
Text HLabel 6300 6300 2    59   Output ~ 0
I_sense_S
Text HLabel 10550 3800 2    59   Output ~ 0
U_sense_BAT
Text HLabel 6100 1700 2    59   Output ~ 0
U_sense_DCB
Text HLabel 6250 4850 2    59   UnSpc ~ 0
+1.65V_REF
Text HLabel 6100 1200 2    59   UnSpc ~ 0
+3.3VA
Text HLabel 3700 900  2    59   UnSpc ~ 0
+5VA
Text HLabel 3550 2450 2    59   UnSpc ~ 0
GNDA
Text HLabel 7700 1600 0    59   UnSpc ~ 0
GND
Text HLabel 7500 2100 0    59   Input ~ 0
DCB_SOLAR
Text HLabel 7500 4050 0    59   Input ~ 0
DCB_BAT
Text HLabel 1050 2050 0    59   UnSpc ~ 0
DC_0
Text HLabel 1050 1000 0    59   UnSpc ~ 0
DC_5
Text HLabel 9450 6300 0    59   Input ~ 0
DCB_pos
Text HLabel 9400 5350 0    59   Input ~ 0
+36V
Text HLabel 1200 4500 0    59   BiDi ~ 0
GND_S
Text HLabel 1250 3350 0    59   UnSpc ~ 0
V_DC_S_pos
Text HLabel 1200 4250 0    59   Input ~ 0
U_sense_PL2
Text HLabel 1200 3950 0    59   Input ~ 0
U_sense_PL1
Text HLabel 1150 6450 0    59   Input ~ 0
I_sense_S2
Text HLabel 1150 6150 0    59   Input ~ 0
I_sense_S1
Text HLabel 1250 1500 0    59   Input ~ 0
U_sense_DC2
Text HLabel 1250 1800 0    59   Input ~ 0
U_sense_DC1
$Comp
L ACPL-C78A U11
U 1 1 548DA594
P 2400 1650
F 0 "U11" H 1950 2200 60  0000 C CNN
F 1 "ACPL-C78A" H 2200 1050 60  0000 C CNN
F 2 "" H 2250 950 60  0000 C CNN
F 3 "" H 2250 950 60  0000 C CNN
	1    2400 1650
	1    0    0    -1  
$EndComp
$Comp
L ACPL-C78A U7
U 1 1 548DA5A1
P 2550 4100
F 0 "U7" H 2100 4650 60  0000 C CNN
F 1 "ACPL-C78A" H 2350 3500 60  0000 C CNN
F 2 "" H 2400 3400 60  0000 C CNN
F 3 "" H 2400 3400 60  0000 C CNN
	1    2550 4100
	1    0    0    -1  
$EndComp
$Comp
L ACPL-C78A U6
U 1 1 548DA5A7
P 2250 6300
F 0 "U6" H 1800 6850 60  0000 C CNN
F 1 "ACPL-C78A" H 2050 5700 60  0000 C CNN
F 2 "" H 2100 5600 60  0000 C CNN
F 3 "" H 2100 5600 60  0000 C CNN
	1    2250 6300
	1    0    0    -1  
$EndComp
$Comp
L AD8552 U4
U 1 1 548DA5AF
P 5450 1700
F 0 "U4" H 5600 1850 60  0000 C CNN
F 1 "AD8552" H 5650 1500 60  0000 C CNN
F 2 "" H 5450 1700 60  0000 C CNN
F 3 "" H 5450 1700 60  0000 C CNN
	1    5450 1700
	1    0    0    -1  
$EndComp
$Comp
L AD8552 U4
U 2 1 548DA5D7
P 8050 5950
F 0 "U4" H 8200 6100 60  0000 C CNN
F 1 "AD8552" H 8250 5750 60  0000 C CNN
F 2 "" H 8050 5950 60  0000 C CNN
F 3 "" H 8050 5950 60  0000 C CNN
	2    8050 5950
	1    0    0    -1  
$EndComp
$Comp
L AD8552 U9
U 2 1 548DA5F0
P 5450 4100
F 0 "U9" H 5600 4250 60  0000 C CNN
F 1 "AD8552" H 5650 3900 60  0000 C CNN
F 2 "" H 5450 4100 60  0000 C CNN
F 3 "" H 5450 4100 60  0000 C CNN
	2    5450 4100
	1    0    0    -1  
$EndComp
$Comp
L AD8552 U9
U 1 1 548DA5FF
P 5250 6300
F 0 "U9" H 5400 6450 60  0000 C CNN
F 1 "AD8552" H 5450 6100 60  0000 C CNN
F 2 "" H 5250 6300 60  0000 C CNN
F 3 "" H 5250 6300 60  0000 C CNN
	1    5250 6300
	1    0    0    -1  
$EndComp
$Comp
L C C17
U 1 1 548DA63F
P 1350 1200
F 0 "C17" H 1350 1300 40  0000 L CNN
F 1 "2.2uF" H 1356 1115 40  0000 L CNN
F 2 "~" H 1388 1050 30  0000 C CNN
F 3 "~" H 1350 1200 60  0000 C CNN
	1    1350 1200
	1    0    0    -1  
$EndComp
Text Notes 500  1400 0    47   ~ 0
Vinmax = +200mV
Text Notes 2250 2400 0    47   ~ 0
G = 8
$Comp
L C C20
U 1 1 548DA69F
P 3350 1150
F 0 "C20" H 3350 1250 40  0000 L CNN
F 1 "2.2uF" H 3356 1065 40  0000 L CNN
F 2 "~" H 3388 1000 30  0000 C CNN
F 3 "~" H 3350 1150 60  0000 C CNN
	1    3350 1150
	1    0    0    -1  
$EndComp
$Comp
L C C87
U 1 1 548DA6F1
P 4300 2250
F 0 "C87" H 4300 2350 40  0000 L CNN
F 1 "0.22uF" H 4306 2165 40  0000 L CNN
F 2 "~" H 4338 2100 30  0000 C CNN
F 3 "~" H 4300 2250 60  0000 C CNN
	1    4300 2250
	1    0    0    -1  
$EndComp
$Comp
L R R19
U 1 1 548DA700
P 4600 1950
F 0 "R19" V 4680 1950 40  0000 C CNN
F 1 "23.2k" V 4607 1951 40  0000 C CNN
F 2 "~" V 4530 1950 30  0000 C CNN
F 3 "~" H 4600 1950 30  0000 C CNN
	1    4600 1950
	0    -1   -1   0   
$EndComp
$Comp
L R R56
U 1 1 548DA70D
P 5200 1000
F 0 "R56" V 5280 1000 40  0000 C CNN
F 1 "46.4k" V 5207 1001 40  0000 C CNN
F 2 "~" V 5130 1000 30  0000 C CNN
F 3 "~" H 5200 1000 30  0000 C CNN
	1    5200 1000
	0    -1   -1   0   
$EndComp
$Comp
L R R57
U 1 1 548DA713
P 5150 2300
F 0 "R57" V 5230 2300 40  0000 C CNN
F 1 "46.4k" V 5157 2301 40  0000 C CNN
F 2 "~" V 5080 2300 30  0000 C CNN
F 3 "~" H 5150 2300 30  0000 C CNN
	1    5150 2300
	0    -1   -1   0   
$EndComp
$Comp
L R R18
U 1 1 548DA719
P 4600 1450
F 0 "R18" V 4680 1450 40  0000 C CNN
F 1 "23.2k" V 4607 1451 40  0000 C CNN
F 2 "~" V 4530 1450 30  0000 C CNN
F 3 "~" H 4600 1450 30  0000 C CNN
	1    4600 1450
	0    -1   -1   0   
$EndComp
$Comp
L R R64
U 1 1 548DA71F
P 4000 1950
F 0 "R64" V 4080 1950 40  0000 C CNN
F 1 "3.32k" V 4007 1951 40  0000 C CNN
F 2 "~" V 3930 1950 30  0000 C CNN
F 3 "~" H 4000 1950 30  0000 C CNN
	1    4000 1950
	0    -1   -1   0   
$EndComp
$Comp
L R R36
U 1 1 548DA725
P 4000 1450
F 0 "R36" V 4080 1450 40  0000 C CNN
F 1 "3.32k" V 4007 1451 40  0000 C CNN
F 2 "~" V 3930 1450 30  0000 C CNN
F 3 "~" H 4000 1450 30  0000 C CNN
	1    4000 1450
	0    -1   -1   0   
$EndComp
$Comp
L C C23
U 1 1 548DA72B
P 4300 1700
F 0 "C23" H 4300 1800 40  0000 L CNN
F 1 "1nF" H 4306 1615 40  0000 L CNN
F 2 "~" H 4338 1550 30  0000 C CNN
F 3 "~" H 4300 1700 60  0000 C CNN
	1    4300 1700
	1    0    0    -1  
$EndComp
$Comp
L C C85
U 1 1 548DA731
P 4300 1100
F 0 "C85" H 4300 1200 40  0000 L CNN
F 1 "0.22uF" H 4306 1015 40  0000 L CNN
F 2 "~" H 4338 950 30  0000 C CNN
F 3 "~" H 4300 1100 60  0000 C CNN
	1    4300 1100
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR027
U 1 1 548DA865
P 5450 2400
F 0 "#PWR027" H 5450 2400 40  0001 C CNN
F 1 "GNDA" H 5450 2330 40  0000 C CNN
F 2 "" H 5450 2400 60  0000 C CNN
F 3 "" H 5450 2400 60  0000 C CNN
	1    5450 2400
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR028
U 1 1 548DAA53
P 4300 2500
F 0 "#PWR028" H 4300 2500 40  0001 C CNN
F 1 "GNDA" H 4300 2430 40  0000 C CNN
F 2 "" H 4300 2500 60  0000 C CNN
F 3 "" H 4300 2500 60  0000 C CNN
	1    4300 2500
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR029
U 1 1 548DAA59
P 4100 950
F 0 "#PWR029" H 4100 950 40  0001 C CNN
F 1 "GNDA" H 4100 880 40  0000 C CNN
F 2 "" H 4100 950 60  0000 C CNN
F 3 "" H 4100 950 60  0000 C CNN
	1    4100 950 
	1    0    0    -1  
$EndComp
$Comp
L C C14
U 1 1 548DAFD7
P 1550 3600
F 0 "C14" H 1550 3700 40  0000 L CNN
F 1 "2.2uF" H 1556 3515 40  0000 L CNN
F 2 "~" H 1588 3450 30  0000 C CNN
F 3 "~" H 1550 3600 60  0000 C CNN
	1    1550 3600
	1    0    0    -1  
$EndComp
$Comp
L R R176
U 1 1 548DAFE4
P 1550 4700
F 0 "R176" V 1630 4700 40  0000 C CNN
F 1 "0" V 1557 4701 40  0000 C CNN
F 2 "~" V 1480 4700 30  0000 C CNN
F 3 "~" H 1550 4700 30  0000 C CNN
	1    1550 4700
	0    -1   -1   0   
$EndComp
Text Notes 550  3800 0    47   ~ 0
Vinmax = +-200mVpp
Text Notes 2500 4850 0    47   ~ 0
G = 8
$Comp
L C C89
U 1 1 548DB30A
P 4100 4650
F 0 "C89" H 4100 4750 40  0000 L CNN
F 1 "0.22uF" H 4106 4565 40  0000 L CNN
F 2 "~" H 4138 4500 30  0000 C CNN
F 3 "~" H 4100 4650 60  0000 C CNN
	1    4100 4650
	1    0    0    -1  
$EndComp
$Comp
L R R46
U 1 1 548DB310
P 4400 4350
F 0 "R46" V 4480 4350 40  0000 C CNN
F 1 "23.2k" V 4407 4351 40  0000 C CNN
F 2 "~" V 4330 4350 30  0000 C CNN
F 3 "~" H 4400 4350 30  0000 C CNN
	1    4400 4350
	0    -1   -1   0   
$EndComp
$Comp
L R R42
U 1 1 548DB316
P 4400 3850
F 0 "R42" V 4480 3850 40  0000 C CNN
F 1 "23.2k" V 4407 3851 40  0000 C CNN
F 2 "~" V 4330 3850 30  0000 C CNN
F 3 "~" H 4400 3850 30  0000 C CNN
	1    4400 3850
	0    -1   -1   0   
$EndComp
$Comp
L R R45
U 1 1 548DB31C
P 3800 4350
F 0 "R45" V 3880 4350 40  0000 C CNN
F 1 "3.32k" V 3807 4351 40  0000 C CNN
F 2 "~" V 3730 4350 30  0000 C CNN
F 3 "~" H 3800 4350 30  0000 C CNN
	1    3800 4350
	0    -1   -1   0   
$EndComp
$Comp
L R R39
U 1 1 548DB322
P 3800 3850
F 0 "R39" V 3880 3850 40  0000 C CNN
F 1 "3.32k" V 3807 3851 40  0000 C CNN
F 2 "~" V 3730 3850 30  0000 C CNN
F 3 "~" H 3800 3850 30  0000 C CNN
	1    3800 3850
	0    -1   -1   0   
$EndComp
$Comp
L C C16
U 1 1 548DB328
P 4100 4100
F 0 "C16" H 4100 4200 40  0000 L CNN
F 1 "1nF" H 4106 4015 40  0000 L CNN
F 2 "~" H 4138 3950 30  0000 C CNN
F 3 "~" H 4100 4100 60  0000 C CNN
	1    4100 4100
	1    0    0    -1  
$EndComp
$Comp
L C C88
U 1 1 548DB32E
P 4100 3500
F 0 "C88" H 4100 3600 40  0000 L CNN
F 1 "0.22uF" H 4106 3415 40  0000 L CNN
F 2 "~" H 4138 3350 30  0000 C CNN
F 3 "~" H 4100 3500 60  0000 C CNN
	1    4100 3500
	1    0    0    -1  
$EndComp
$Comp
L R R173
U 1 1 548DB3D1
P 4700 4650
F 0 "R173" V 4780 4650 40  0000 C CNN
F 1 "46.4k" V 4707 4651 40  0000 C CNN
F 2 "~" V 4630 4650 30  0000 C CNN
F 3 "~" H 4700 4650 30  0000 C CNN
	1    4700 4650
	-1   0    0    1   
$EndComp
$Comp
L R R172
U 1 1 548DB3E7
P 4700 3200
F 0 "R172" V 4780 3200 40  0000 C CNN
F 1 "46.4k" V 4707 3201 40  0000 C CNN
F 2 "~" V 4630 3200 30  0000 C CNN
F 3 "~" H 4700 3200 30  0000 C CNN
	1    4700 3200
	-1   0    0    1   
$EndComp
$Comp
L R R37
U 1 1 548DB3F2
P 5350 3500
F 0 "R37" V 5430 3500 40  0000 C CNN
F 1 "23.2k" V 5357 3501 40  0000 C CNN
F 2 "~" V 5280 3500 30  0000 C CNN
F 3 "~" H 5350 3500 30  0000 C CNN
	1    5350 3500
	0    -1   -1   0   
$EndComp
$Comp
L R R48
U 1 1 548DB402
P 4900 4550
F 0 "R48" V 4980 4550 40  0000 C CNN
F 1 "23.2k" V 4907 4551 40  0000 C CNN
F 2 "~" V 4830 4550 30  0000 C CNN
F 3 "~" H 4900 4550 30  0000 C CNN
	1    4900 4550
	-1   0    0    1   
$EndComp
$Comp
L C C18
U 1 1 548DB40D
P 6150 4500
F 0 "C18" H 6150 4600 40  0000 L CNN
F 1 "0.1uF" H 6156 4415 40  0000 L CNN
F 2 "~" H 6188 4350 30  0000 C CNN
F 3 "~" H 6150 4500 60  0000 C CNN
	1    6150 4500
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR030
U 1 1 548DB701
P 6150 5000
F 0 "#PWR030" H 6150 5000 40  0001 C CNN
F 1 "GNDA" H 6150 4930 40  0000 C CNN
F 2 "" H 6150 5000 60  0000 C CNN
F 3 "" H 6150 5000 60  0000 C CNN
	1    6150 5000
	1    0    0    -1  
$EndComp
$Comp
L C C11
U 1 1 548DB927
P 3550 3300
F 0 "C11" H 3550 3400 40  0000 L CNN
F 1 "2.2uF" H 3556 3215 40  0000 L CNN
F 2 "~" H 3588 3150 30  0000 C CNN
F 3 "~" H 3550 3300 60  0000 C CNN
	1    3550 3300
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR031
U 1 1 548DB937
P 3550 3600
F 0 "#PWR031" H 3550 3600 40  0001 C CNN
F 1 "GNDA" H 3550 3530 40  0000 C CNN
F 2 "" H 3550 3600 60  0000 C CNN
F 3 "" H 3550 3600 60  0000 C CNN
	1    3550 3600
	1    0    0    -1  
$EndComp
Text Label 3450 900  0    47   ~ 0
+5VA
Text Label 3750 3050 2    47   ~ 0
+5VA
Text Label 5650 1200 2    47   ~ 0
+3.3VA
Text Label 6400 3650 2    47   ~ 0
+3.3VA
Text Notes 1550 3250 2    47   ~ 0
+5.0V
Text Notes 1200 5400 2    47   ~ 0
+5.0V
Text Notes 2100 7050 0    47   ~ 0
G = 8
$Comp
L C C12
U 1 1 548DC448
P 1300 5750
F 0 "C12" H 1300 5850 40  0000 L CNN
F 1 "2.2uF" H 1306 5665 40  0000 L CNN
F 2 "~" H 1338 5600 30  0000 C CNN
F 3 "~" H 1300 5750 60  0000 C CNN
	1    1300 5750
	1    0    0    -1  
$EndComp
Text Label 1300 4500 0    47   ~ 0
GND_S
Text Label 1050 6700 0    47   ~ 0
GND_S
Text Label 1300 3350 0    47   ~ 0
V_DC_S_pos
Text Label 650  5500 0    47   ~ 0
V_DC_S_pos
$Comp
L C C13
U 1 1 548DCA43
P 3200 5700
F 0 "C13" H 3200 5800 40  0000 L CNN
F 1 "2.2uF" H 3206 5615 40  0000 L CNN
F 2 "~" H 3238 5550 30  0000 C CNN
F 3 "~" H 3200 5700 60  0000 C CNN
	1    3200 5700
	1    0    0    -1  
$EndComp
Text Label 3450 5450 2    47   ~ 0
+5VA
Wire Wire Line
	1050 1000 1650 1000
Wire Wire Line
	1650 1000 1650 1250
Wire Wire Line
	1650 1250 1750 1250
Connection ~ 1350 1000
Wire Wire Line
	1250 1500 1750 1500
Wire Wire Line
	1250 1800 1750 1800
Wire Wire Line
	1050 2050 1750 2050
Wire Wire Line
	1350 1400 1350 2050
Connection ~ 1350 2050
Wire Wire Line
	3050 1250 3100 1250
Wire Wire Line
	3100 1250 3100 900 
Wire Wire Line
	3100 900  3700 900 
Wire Wire Line
	3350 900  3350 950 
Connection ~ 3350 900 
Wire Wire Line
	4900 1600 4950 1600
Wire Wire Line
	4900 1000 4900 1600
Wire Wire Line
	4900 1000 4950 1000
Wire Wire Line
	4850 1450 4900 1450
Connection ~ 4900 1450
Wire Wire Line
	4950 1800 4900 1800
Wire Wire Line
	4900 1800 4900 2300
Wire Wire Line
	4850 1950 4900 1950
Connection ~ 4900 1950
Wire Wire Line
	5350 2100 5350 2150
Wire Wire Line
	5350 2150 5450 2150
Wire Wire Line
	5400 2300 5450 2300
Connection ~ 5450 2300
Wire Wire Line
	5450 2150 5450 2400
Wire Wire Line
	5950 1700 6100 1700
Connection ~ 6000 1700
Wire Wire Line
	5350 1300 5350 1200
Wire Wire Line
	5350 1200 6100 1200
Wire Wire Line
	4250 1450 4350 1450
Wire Wire Line
	4300 1300 4300 1500
Connection ~ 4300 1450
Wire Wire Line
	4300 1900 4300 2050
Wire Wire Line
	4250 1950 4350 1950
Connection ~ 4300 1950
Wire Wire Line
	4300 2500 4300 2450
Wire Wire Line
	4100 850  4100 950 
Wire Wire Line
	3050 1500 3500 1500
Wire Wire Line
	3500 1500 3500 1950
Wire Wire Line
	3500 1950 3750 1950
Wire Wire Line
	3050 1800 3650 1800
Wire Wire Line
	3650 1800 3650 1450
Wire Wire Line
	3650 1450 3750 1450
Wire Wire Line
	3050 2050 3200 2050
Wire Wire Line
	3200 2050 3200 2450
Wire Wire Line
	3200 2450 3550 2450
Wire Wire Line
	3350 1350 3350 2550
Connection ~ 3350 2450
Wire Wire Line
	4100 850  4300 850 
Wire Wire Line
	4300 850  4300 900 
Wire Wire Line
	5450 1000 6000 1000
Wire Wire Line
	6000 1000 6000 1700
Wire Wire Line
	1200 4500 1900 4500
Connection ~ 1250 4500
Wire Wire Line
	1550 3800 1550 4500
Connection ~ 1550 4500
Wire Wire Line
	1900 3700 1850 3700
Wire Wire Line
	1850 3700 1850 3350
Wire Wire Line
	1850 3350 1250 3350
Wire Wire Line
	1550 3400 1550 3350
Connection ~ 1550 3350
Wire Wire Line
	1200 4250 1900 4250
Wire Wire Line
	1900 3950 1200 3950
Wire Wire Line
	4050 3850 4150 3850
Wire Wire Line
	4100 3700 4100 3900
Connection ~ 4100 3850
Wire Wire Line
	4100 4300 4100 4450
Wire Wire Line
	4050 4350 4150 4350
Connection ~ 4100 4350
Wire Wire Line
	4700 4200 4950 4200
Wire Wire Line
	4700 4200 4700 4400
Wire Wire Line
	4900 4300 4900 4200
Connection ~ 4900 4200
Wire Wire Line
	4650 4350 4700 4350
Connection ~ 4700 4350
Wire Wire Line
	4100 4850 4100 4950
Wire Wire Line
	3350 4950 6150 4950
Wire Wire Line
	4700 4950 4700 4900
Wire Wire Line
	5350 4950 5350 4500
Connection ~ 4700 4950
Wire Wire Line
	5600 3500 6050 3500
Wire Wire Line
	6050 3500 6050 4100
Wire Wire Line
	5950 4100 6250 4100
Wire Wire Line
	5350 3700 5350 3650
Wire Wire Line
	5350 3650 6400 3650
Wire Wire Line
	6150 3650 6150 4300
Wire Wire Line
	6150 4700 6150 5000
Connection ~ 5350 4950
Connection ~ 6150 4950
Wire Wire Line
	4700 3850 4650 3850
Wire Wire Line
	4700 3450 4700 4000
Wire Wire Line
	4700 4000 4950 4000
Connection ~ 4700 3850
Wire Wire Line
	5100 3500 4700 3500
Connection ~ 4700 3500
Wire Wire Line
	4100 2900 4100 3300
Wire Wire Line
	4100 2900 4700 2900
Wire Wire Line
	4700 2900 4700 2950
Wire Wire Line
	3550 3500 3550 3600
Wire Wire Line
	3200 3700 3300 3700
Wire Wire Line
	3300 3700 3300 3050
Wire Wire Line
	3300 3050 3750 3050
Wire Wire Line
	3550 3050 3550 3100
Connection ~ 3550 3050
Wire Wire Line
	3200 3950 3350 3950
Wire Wire Line
	3350 3950 3350 4350
Wire Wire Line
	3350 4350 3550 4350
Wire Wire Line
	3200 4250 3450 4250
Wire Wire Line
	3450 4250 3450 3850
Wire Wire Line
	3450 3850 3550 3850
Wire Wire Line
	3200 4500 3350 4500
Wire Wire Line
	3350 4500 3350 4950
Connection ~ 4100 4950
Wire Wire Line
	3550 3550 3850 3550
Wire Wire Line
	3850 3550 3850 3250
Wire Wire Line
	3850 3250 4100 3250
Connection ~ 4100 3250
Connection ~ 3550 3550
Wire Wire Line
	6250 4850 4900 4850
Wire Wire Line
	4900 4850 4900 4800
Connection ~ 6050 4100
Connection ~ 6150 3650
Wire Wire Line
	1250 4500 1250 4700
Wire Wire Line
	1250 4700 1300 4700
Wire Wire Line
	1800 4700 1850 4700
Wire Wire Line
	1850 4700 1850 4250
Connection ~ 1850 4250
Wire Wire Line
	1300 5550 1300 5500
Wire Wire Line
	650  5500 1550 5500
Wire Wire Line
	1550 5500 1550 5900
Wire Wire Line
	1550 5900 1600 5900
Wire Wire Line
	1300 5950 1300 6700
Wire Wire Line
	1050 6700 1600 6700
Wire Wire Line
	1150 6150 1600 6150
Wire Wire Line
	1150 6450 1600 6450
Connection ~ 1300 6700
Connection ~ 1300 5500
Wire Wire Line
	2900 5900 3000 5900
Wire Wire Line
	3000 5900 3000 5450
Wire Wire Line
	3000 5450 3450 5450
Wire Wire Line
	3200 5450 3200 5500
Connection ~ 3200 5450
Wire Wire Line
	2900 6700 3050 6700
$Comp
L GNDA #PWR032
U 1 1 548DCE50
P 3350 2550
F 0 "#PWR032" H 3350 2550 40  0001 C CNN
F 1 "GNDA" H 3350 2480 40  0000 C CNN
F 2 "" H 3350 2550 60  0000 C CNN
F 3 "" H 3350 2550 60  0000 C CNN
	1    3350 2550
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR033
U 1 1 548DCEED
P 3050 6850
F 0 "#PWR033" H 3050 6850 40  0001 C CNN
F 1 "GNDA" H 3050 6780 40  0000 C CNN
F 2 "" H 3050 6850 60  0000 C CNN
F 3 "" H 3050 6850 60  0000 C CNN
	1    3050 6850
	1    0    0    -1  
$EndComp
$Comp
L C C91
U 1 1 548DD0BC
P 4000 6850
F 0 "C91" H 4000 6950 40  0000 L CNN
F 1 "0.22uF" H 4006 6765 40  0000 L CNN
F 2 "~" H 4038 6700 30  0000 C CNN
F 3 "~" H 4000 6850 60  0000 C CNN
	1    4000 6850
	1    0    0    -1  
$EndComp
$Comp
L R R44
U 1 1 548DD0C2
P 4300 6550
F 0 "R44" V 4380 6550 40  0000 C CNN
F 1 "23.2k" V 4307 6551 40  0000 C CNN
F 2 "~" V 4230 6550 30  0000 C CNN
F 3 "~" H 4300 6550 30  0000 C CNN
	1    4300 6550
	0    -1   -1   0   
$EndComp
$Comp
L R R41
U 1 1 548DD0C8
P 4300 6050
F 0 "R41" V 4380 6050 40  0000 C CNN
F 1 "23.2k" V 4307 6051 40  0000 C CNN
F 2 "~" V 4230 6050 30  0000 C CNN
F 3 "~" H 4300 6050 30  0000 C CNN
	1    4300 6050
	0    -1   -1   0   
$EndComp
$Comp
L R R43
U 1 1 548DD0CE
P 3700 6550
F 0 "R43" V 3780 6550 40  0000 C CNN
F 1 "3.32k" V 3707 6551 40  0000 C CNN
F 2 "~" V 3630 6550 30  0000 C CNN
F 3 "~" H 3700 6550 30  0000 C CNN
	1    3700 6550
	0    -1   -1   0   
$EndComp
$Comp
L R R40
U 1 1 548DD0D4
P 3700 6050
F 0 "R40" V 3780 6050 40  0000 C CNN
F 1 "3.32k" V 3707 6051 40  0000 C CNN
F 2 "~" V 3630 6050 30  0000 C CNN
F 3 "~" H 3700 6050 30  0000 C CNN
	1    3700 6050
	0    -1   -1   0   
$EndComp
$Comp
L C C15
U 1 1 548DD0DA
P 4000 6300
F 0 "C15" H 4000 6400 40  0000 L CNN
F 1 "2.2nF" H 4006 6215 40  0000 L CNN
F 2 "~" H 4038 6150 30  0000 C CNN
F 3 "~" H 4000 6300 60  0000 C CNN
	1    4000 6300
	1    0    0    -1  
$EndComp
$Comp
L C C90
U 1 1 548DD0E0
P 4000 5700
F 0 "C90" H 4000 5800 40  0000 L CNN
F 1 "0.22uF" H 4006 5615 40  0000 L CNN
F 2 "~" H 4038 5550 30  0000 C CNN
F 3 "~" H 4000 5700 60  0000 C CNN
	1    4000 5700
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 6050 4050 6050
Wire Wire Line
	4000 5900 4000 6100
Connection ~ 4000 6050
Wire Wire Line
	4000 6500 4000 6650
Wire Wire Line
	3950 6550 4050 6550
Connection ~ 4000 6550
Wire Wire Line
	3050 6700 3050 6850
$Comp
L GNDA #PWR034
U 1 1 548DD263
P 3200 6000
F 0 "#PWR034" H 3200 6000 40  0001 C CNN
F 1 "GNDA" H 3200 5930 40  0000 C CNN
F 2 "" H 3200 6000 60  0000 C CNN
F 3 "" H 3200 6000 60  0000 C CNN
	1    3200 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3200 5900 3200 6000
Wire Wire Line
	4000 5150 4000 5500
Connection ~ 3200 5950
Wire Wire Line
	2900 6150 3200 6150
Wire Wire Line
	3200 6150 3200 6550
Wire Wire Line
	3200 6550 3450 6550
Wire Wire Line
	2900 6450 3350 6450
Wire Wire Line
	3350 6450 3350 6050
Wire Wire Line
	3350 6050 3450 6050
$Comp
L GNDA #PWR035
U 1 1 548DD5D3
P 4000 7200
F 0 "#PWR035" H 4000 7200 40  0001 C CNN
F 1 "GNDA" H 4000 7130 40  0000 C CNN
F 2 "" H 4000 7200 60  0000 C CNN
F 3 "" H 4000 7200 60  0000 C CNN
	1    4000 7200
	1    0    0    -1  
$EndComp
Wire Wire Line
	4000 7050 4000 7200
$Comp
L R R174
U 1 1 548DD726
P 4600 5450
F 0 "R174" V 4680 5450 40  0000 C CNN
F 1 "46.4k" V 4607 5451 40  0000 C CNN
F 2 "~" V 4530 5450 30  0000 C CNN
F 3 "~" H 4600 5450 30  0000 C CNN
	1    4600 5450
	-1   0    0    1   
$EndComp
$Comp
L R R38
U 1 1 548DD72C
P 5200 5750
F 0 "R38" V 5280 5750 40  0000 C CNN
F 1 "23.2k" V 5207 5751 40  0000 C CNN
F 2 "~" V 5130 5750 30  0000 C CNN
F 3 "~" H 5200 5750 30  0000 C CNN
	1    5200 5750
	0    -1   -1   0   
$EndComp
$Comp
L R R175
U 1 1 548DD76C
P 4600 6850
F 0 "R175" V 4680 6850 40  0000 C CNN
F 1 "46.4k" V 4607 6851 40  0000 C CNN
F 2 "~" V 4530 6850 30  0000 C CNN
F 3 "~" H 4600 6850 30  0000 C CNN
	1    4600 6850
	-1   0    0    1   
$EndComp
$Comp
L R R47
U 1 1 548DD777
P 5100 7000
F 0 "R47" V 5180 7000 40  0000 C CNN
F 1 "23.2k" V 5107 7001 40  0000 C CNN
F 2 "~" V 5030 7000 30  0000 C CNN
F 3 "~" H 5100 7000 30  0000 C CNN
	1    5100 7000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4600 6050 4550 6050
Wire Wire Line
	4600 5700 4600 6200
Wire Wire Line
	4600 6200 4750 6200
Connection ~ 4600 6050
Wire Wire Line
	4950 5750 4600 5750
Connection ~ 4600 5750
Wire Wire Line
	4550 6550 4750 6550
Wire Wire Line
	4600 6400 4600 6600
Wire Wire Line
	4600 6400 4750 6400
Connection ~ 4600 6550
$Comp
L GNDA #PWR036
U 1 1 548DDBF6
P 5150 6750
F 0 "#PWR036" H 5150 6750 40  0001 C CNN
F 1 "GNDA" H 5150 6680 40  0000 C CNN
F 2 "" H 5150 6750 60  0000 C CNN
F 3 "" H 5150 6750 60  0000 C CNN
	1    5150 6750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5150 6700 5150 6750
Wire Wire Line
	4750 6550 4750 7000
Wire Wire Line
	4750 7000 4850 7000
Wire Wire Line
	4600 7100 4600 7150
Wire Wire Line
	4600 7150 4000 7150
Connection ~ 4000 7150
Wire Wire Line
	4600 5150 4600 5200
Connection ~ 4000 5150
Wire Wire Line
	3800 5150 4600 5150
$Comp
L GNDA #PWR037
U 1 1 548DE15B
P 3800 5250
F 0 "#PWR037" H 3800 5250 40  0001 C CNN
F 1 "GNDA" H 3800 5180 40  0000 C CNN
F 2 "" H 3800 5250 60  0000 C CNN
F 3 "" H 3800 5250 60  0000 C CNN
	1    3800 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	3800 5150 3800 5250
Wire Wire Line
	5750 6300 6300 6300
Wire Wire Line
	5450 5750 5800 5750
Wire Wire Line
	5800 5750 5800 6300
Connection ~ 5800 6300
Wire Wire Line
	5150 5900 5150 5850
Wire Wire Line
	5150 5850 6150 5850
Text Label 6150 5850 2    47   ~ 0
+3.3VA
Text Label 5850 6300 0    47   ~ 0
I_SENSE_S
Text Label 5550 4850 0    47   ~ 0
+1.65V_REF
Wire Wire Line
	5350 7000 5900 7000
Text Label 5900 7000 2    47   ~ 0
+1.65V_REF
$Comp
L R R161
U 1 1 548DE73C
P 7300 5750
F 0 "R161" V 7380 5750 40  0000 C CNN
F 1 "47k" V 7307 5751 40  0000 C CNN
F 2 "~" V 7230 5750 30  0000 C CNN
F 3 "~" H 7300 5750 30  0000 C CNN
	1    7300 5750
	-1   0    0    1   
$EndComp
$Comp
L R R162
U 1 1 548DE747
P 7300 6350
F 0 "R162" V 7380 6350 40  0000 C CNN
F 1 "47k" V 7307 6351 40  0000 C CNN
F 2 "~" V 7230 6350 30  0000 C CNN
F 3 "~" H 7300 6350 30  0000 C CNN
	1    7300 6350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7550 5850 7450 5850
Wire Wire Line
	7450 5850 7450 5500
Wire Wire Line
	7450 5500 8600 5500
Wire Wire Line
	8600 5500 8600 5950
Wire Wire Line
	8600 5950 8550 5950
Wire Wire Line
	7300 6000 7300 6100
Wire Wire Line
	7550 6050 7300 6050
Connection ~ 7300 6050
Wire Wire Line
	7950 5400 7950 5550
Wire Wire Line
	7300 5400 8300 5400
Wire Wire Line
	7300 5400 7300 5500
Wire Wire Line
	7300 6600 7300 6650
Wire Wire Line
	7300 6650 7950 6650
Wire Wire Line
	7950 6350 7950 6700
$Comp
L GNDA #PWR038
U 1 1 548DEBFD
P 7950 6700
F 0 "#PWR038" H 7950 6700 40  0001 C CNN
F 1 "GNDA" H 7950 6630 40  0000 C CNN
F 2 "" H 7950 6700 60  0000 C CNN
F 3 "" H 7950 6700 60  0000 C CNN
	1    7950 6700
	1    0    0    -1  
$EndComp
Connection ~ 7950 6650
Connection ~ 7950 5400
Text Label 8300 5400 2    47   ~ 0
+3.3VA
$Comp
L INA169 U1
U 1 1 548DF80D
P 9900 5750
F 0 "U1" H 10250 5750 60  0000 C CNN
F 1 "INA169" V 9600 5700 60  0000 C CNN
F 2 "" H 9750 5150 60  0000 C CNN
F 3 "" H 9750 5150 60  0000 C CNN
	1    9900 5750
	1    0    0    -1  
$EndComp
$Comp
L R R11
U 1 1 548DF81A
P 10050 6500
F 0 "R11" V 10130 6500 40  0000 C CNN
F 1 "46.4k" V 10057 6501 40  0000 C CNN
F 2 "~" V 9980 6500 30  0000 C CNN
F 3 "~" H 10050 6500 30  0000 C CNN
	1    10050 6500
	-1   0    0    1   
$EndComp
$Comp
L GNDA #PWR039
U 1 1 548DF820
P 9900 6850
F 0 "#PWR039" H 9900 6850 40  0001 C CNN
F 1 "GNDA" H 9900 6780 40  0000 C CNN
F 2 "" H 9900 6850 60  0000 C CNN
F 3 "" H 9900 6850 60  0000 C CNN
	1    9900 6850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9900 6150 9900 6850
Wire Wire Line
	10050 6750 10050 6800
Wire Wire Line
	10050 6800 9900 6800
Connection ~ 9900 6800
Wire Wire Line
	10050 6150 10050 6250
Wire Wire Line
	9400 5350 9750 5350
Wire Wire Line
	9750 5350 9750 5400
Wire Wire Line
	9450 6300 9750 6300
Wire Wire Line
	9750 6300 9750 6150
Text Notes 9650 5250 0    47   ~ 0
G = 46.4
Text Notes 8750 6050 0    47   ~ 0
7A*10mOhm = 70mV\nImax = 7.11A
$Comp
L C C3
U 1 1 548DFE3D
P 10500 5650
F 0 "C3" H 10500 5750 40  0000 L CNN
F 1 "0.22uF" H 10506 5565 40  0000 L CNN
F 2 "~" H 10538 5500 30  0000 C CNN
F 3 "~" H 10500 5650 60  0000 C CNN
	1    10500 5650
	1    0    0    -1  
$EndComp
$Comp
L GNDA #PWR040
U 1 1 548DFE4D
P 10500 6000
F 0 "#PWR040" H 10500 6000 40  0001 C CNN
F 1 "GNDA" H 10500 5930 40  0000 C CNN
F 2 "" H 10500 6000 60  0000 C CNN
F 3 "" H 10500 6000 60  0000 C CNN
	1    10500 6000
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 5850 10500 6000
Wire Wire Line
	10050 5400 10050 5350
Wire Wire Line
	10050 5350 10750 5350
Wire Wire Line
	10500 5350 10500 5450
Connection ~ 10500 5350
Wire Wire Line
	10050 6200 10500 6200
Connection ~ 10050 6200
Text Label 10100 6200 0    47   ~ 0
I_sense_P
Text Label 10750 5350 2    47   ~ 0
+3.3VA
$Comp
L AD8552 U2
U 1 1 548E0844
P 9750 1850
F 0 "U2" H 9900 2000 60  0000 C CNN
F 1 "AD8552" H 9950 1650 60  0000 C CNN
F 2 "" H 9750 1850 60  0000 C CNN
F 3 "" H 9750 1850 60  0000 C CNN
	1    9750 1850
	1    0    0    -1  
$EndComp
$Comp
L C C6
U 1 1 548E0856
P 10350 2150
F 0 "C6" H 10350 2250 40  0000 L CNN
F 1 "0.22uF" H 10356 2065 40  0000 L CNN
F 2 "~" H 10388 2000 30  0000 C CNN
F 3 "~" H 10350 2150 60  0000 C CNN
	1    10350 2150
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 548E085C
P 9750 1250
F 0 "R3" V 9830 1250 40  0000 C CNN
F 1 "10k" V 9757 1251 40  0000 C CNN
F 2 "~" V 9680 1250 30  0000 C CNN
F 3 "~" H 9750 1250 30  0000 C CNN
	1    9750 1250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9650 1450 9650 1400
Wire Wire Line
	9650 1400 10750 1400
Text Label 10750 1400 2    47   ~ 0
+3.3VA
Wire Wire Line
	10250 1850 10550 1850
Wire Wire Line
	10000 1250 10450 1250
Wire Wire Line
	10450 1250 10450 1850
Connection ~ 10450 1850
Wire Wire Line
	10350 1950 10350 1400
Connection ~ 10350 1400
Wire Wire Line
	9650 2250 9650 2450
Wire Wire Line
	9650 2400 10350 2400
Wire Wire Line
	10350 2400 10350 2350
$Comp
L GNDA #PWR041
U 1 1 548E0D16
P 9650 2450
F 0 "#PWR041" H 9650 2450 40  0001 C CNN
F 1 "GNDA" H 9650 2380 40  0000 C CNN
F 2 "" H 9650 2450 60  0000 C CNN
F 3 "" H 9650 2450 60  0000 C CNN
	1    9650 2450
	1    0    0    -1  
$EndComp
Connection ~ 9650 2400
$Comp
L R R5
U 1 1 548E0EF1
P 8900 1600
F 0 "R5" V 8980 1600 40  0000 C CNN
F 1 "10k" V 8907 1601 40  0000 C CNN
F 2 "~" V 8830 1600 30  0000 C CNN
F 3 "~" H 8900 1600 30  0000 C CNN
	1    8900 1600
	0    -1   -1   0   
$EndComp
$Comp
L R R12
U 1 1 548E0EF7
P 8900 2100
F 0 "R12" V 8980 2100 40  0000 C CNN
F 1 "10k" V 8907 2101 40  0000 C CNN
F 2 "~" V 8830 2100 30  0000 C CNN
F 3 "~" H 8900 2100 30  0000 C CNN
	1    8900 2100
	0    -1   -1   0   
$EndComp
$Comp
L C C5
U 1 1 548E0F07
P 8600 1850
F 0 "C5" H 8600 1950 40  0000 L CNN
F 1 "1nF" H 8606 1765 40  0000 L CNN
F 2 "~" H 8638 1700 30  0000 C CNN
F 3 "~" H 8600 1850 60  0000 C CNN
	1    8600 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 1600 9200 1600
Wire Wire Line
	9200 1250 9200 1750
Wire Wire Line
	9200 1750 9250 1750
Wire Wire Line
	9150 1250 9500 1250
Connection ~ 9200 1600
Wire Wire Line
	9150 2100 9150 1950
Wire Wire Line
	9150 1950 9250 1950
Wire Wire Line
	8550 1600 8650 1600
Wire Wire Line
	8600 1600 8600 1650
Wire Wire Line
	8600 2050 8600 2100
Wire Wire Line
	8550 2100 8650 2100
$Comp
L R R30
U 1 1 548E16A3
P 8900 1250
F 0 "R30" V 8980 1250 40  0000 C CNN
F 1 "6.81k" V 8907 1251 40  0000 C CNN
F 2 "~" V 8830 1250 30  0000 C CNN
F 3 "~" H 8900 1250 30  0000 C CNN
	1    8900 1250
	0    -1   -1   0   
$EndComp
Connection ~ 9200 1250
Wire Wire Line
	8650 1250 8300 1250
Text Label 8300 1250 0    47   ~ 0
+1.65V_REF
$Comp
L R R4
U 1 1 548E18A6
P 8300 1600
F 0 "R4" V 8380 1600 40  0000 C CNN
F 1 "220" V 8307 1601 40  0000 C CNN
F 2 "~" V 8230 1600 30  0000 C CNN
F 3 "~" H 8300 1600 30  0000 C CNN
	1    8300 1600
	0    -1   -1   0   
$EndComp
$Comp
L R R13
U 1 1 548E18B6
P 8300 2100
F 0 "R13" V 8380 2100 40  0000 C CNN
F 1 "220" V 8307 2101 40  0000 C CNN
F 2 "~" V 8230 2100 30  0000 C CNN
F 3 "~" H 8300 2100 30  0000 C CNN
	1    8300 2100
	0    -1   -1   0   
$EndComp
Connection ~ 8600 2100
Connection ~ 8600 1600
$Comp
L R R9
U 1 1 548E1AB2
P 8000 1850
F 0 "R9" V 8080 1850 40  0000 C CNN
F 1 "1k" V 8007 1851 40  0000 C CNN
F 2 "~" V 7930 1850 30  0000 C CNN
F 3 "~" H 8000 1850 30  0000 C CNN
	1    8000 1850
	-1   0    0    1   
$EndComp
Wire Wire Line
	7700 1600 8050 1600
Wire Wire Line
	7800 2100 8050 2100
$Comp
L R R8
U 1 1 548E1CB7
P 7800 1850
F 0 "R8" V 7880 1850 40  0000 C CNN
F 1 "82k" V 7807 1851 40  0000 C CNN
F 2 "~" V 7730 1850 30  0000 C CNN
F 3 "~" H 7800 1850 30  0000 C CNN
	1    7800 1850
	-1   0    0    1   
$EndComp
Connection ~ 8000 1600
Connection ~ 8000 2100
Connection ~ 7800 1600
$Comp
L R R17
U 1 1 548E20BE
P 8000 2400
F 0 "R17" V 8080 2400 40  0000 C CNN
F 1 "820" V 8007 2401 40  0000 C CNN
F 2 "~" V 7930 2400 30  0000 C CNN
F 3 "~" H 8000 2400 30  0000 C CNN
	1    8000 2400
	-1   0    0    1   
$EndComp
$Comp
L R R16
U 1 1 548E20C4
P 7700 2400
F 0 "R16" V 7780 2400 40  0000 C CNN
F 1 "27k" V 7707 2401 40  0000 C CNN
F 2 "~" V 7630 2400 30  0000 C CNN
F 3 "~" H 7700 2400 30  0000 C CNN
	1    7700 2400
	-1   0    0    1   
$EndComp
Wire Wire Line
	7700 2700 8000 2700
Wire Wire Line
	8000 2700 8000 2650
Wire Wire Line
	8000 2150 8000 2100
Wire Wire Line
	7500 2100 7700 2100
Wire Wire Line
	7700 2100 7700 2150
Wire Wire Line
	7700 2650 7700 2700
$Comp
L AD8552 U2
U 2 1 548E2676
P 9750 3800
F 0 "U2" H 9900 3950 60  0000 C CNN
F 1 "AD8552" H 9950 3600 60  0000 C CNN
F 2 "" H 9750 3800 60  0000 C CNN
F 3 "" H 9750 3800 60  0000 C CNN
	2    9750 3800
	1    0    0    -1  
$EndComp
$Comp
L R R20
U 1 1 548E2682
P 9750 3200
F 0 "R20" V 9830 3200 40  0000 C CNN
F 1 "10k" V 9757 3201 40  0000 C CNN
F 2 "~" V 9680 3200 30  0000 C CNN
F 3 "~" H 9750 3200 30  0000 C CNN
	1    9750 3200
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9650 3400 9650 3350
Wire Wire Line
	9650 3350 10750 3350
Text Label 10750 3350 2    47   ~ 0
+3.3VA
Wire Wire Line
	10250 3800 10550 3800
Wire Wire Line
	10000 3200 10450 3200
Wire Wire Line
	10450 3200 10450 3800
Connection ~ 10450 3800
Wire Wire Line
	9650 4200 9650 4400
$Comp
L GNDA #PWR042
U 1 1 548E2694
P 9650 4400
F 0 "#PWR042" H 9650 4400 40  0001 C CNN
F 1 "GNDA" H 9650 4330 40  0000 C CNN
F 2 "" H 9650 4400 60  0000 C CNN
F 3 "" H 9650 4400 60  0000 C CNN
	1    9650 4400
	1    0    0    -1  
$EndComp
Connection ~ 9650 4350
$Comp
L R R24
U 1 1 548E269B
P 8900 3550
F 0 "R24" V 8980 3550 40  0000 C CNN
F 1 "10k" V 8907 3551 40  0000 C CNN
F 2 "~" V 8830 3550 30  0000 C CNN
F 3 "~" H 8900 3550 30  0000 C CNN
	1    8900 3550
	0    -1   -1   0   
$EndComp
$Comp
L R R29
U 1 1 548E26A1
P 8900 4050
F 0 "R29" V 8980 4050 40  0000 C CNN
F 1 "10k" V 8907 4051 40  0000 C CNN
F 2 "~" V 8830 4050 30  0000 C CNN
F 3 "~" H 8900 4050 30  0000 C CNN
	1    8900 4050
	0    -1   -1   0   
$EndComp
$Comp
L C C8
U 1 1 548E26A7
P 8600 3800
F 0 "C8" H 8600 3900 40  0000 L CNN
F 1 "1nF" H 8606 3715 40  0000 L CNN
F 2 "~" H 8638 3650 30  0000 C CNN
F 3 "~" H 8600 3800 60  0000 C CNN
	1    8600 3800
	1    0    0    -1  
$EndComp
Wire Wire Line
	9150 3550 9200 3550
Wire Wire Line
	9200 3200 9200 3700
Wire Wire Line
	9200 3700 9250 3700
Wire Wire Line
	9150 3200 9500 3200
Connection ~ 9200 3550
Wire Wire Line
	9150 4050 9150 3900
Wire Wire Line
	9150 3900 9250 3900
Wire Wire Line
	8550 3550 8650 3550
Wire Wire Line
	8600 3550 8600 3600
Wire Wire Line
	8600 4000 8600 4050
Wire Wire Line
	8550 4050 8650 4050
$Comp
L R R25
U 1 1 548E26B8
P 8900 3200
F 0 "R25" V 8980 3200 40  0000 C CNN
F 1 "6.81k" V 8907 3201 40  0000 C CNN
F 2 "~" V 8830 3200 30  0000 C CNN
F 3 "~" H 8900 3200 30  0000 C CNN
	1    8900 3200
	0    -1   -1   0   
$EndComp
Connection ~ 9200 3200
Wire Wire Line
	8650 3200 8300 3200
Text Label 8300 3200 0    47   ~ 0
+1.65V_REF
$Comp
L R R23
U 1 1 548E26C1
P 8300 3550
F 0 "R23" V 8380 3550 40  0000 C CNN
F 1 "220" V 8307 3551 40  0000 C CNN
F 2 "~" V 8230 3550 30  0000 C CNN
F 3 "~" H 8300 3550 30  0000 C CNN
	1    8300 3550
	0    -1   -1   0   
$EndComp
$Comp
L R R28
U 1 1 548E26C7
P 8300 4050
F 0 "R28" V 8380 4050 40  0000 C CNN
F 1 "220" V 8307 4051 40  0000 C CNN
F 2 "~" V 8230 4050 30  0000 C CNN
F 3 "~" H 8300 4050 30  0000 C CNN
	1    8300 4050
	0    -1   -1   0   
$EndComp
Connection ~ 8600 4050
Connection ~ 8600 3550
$Comp
L R R27
U 1 1 548E26CF
P 8000 3800
F 0 "R27" V 8080 3800 40  0000 C CNN
F 1 "1k" V 8007 3801 40  0000 C CNN
F 2 "~" V 7930 3800 30  0000 C CNN
F 3 "~" H 8000 3800 30  0000 C CNN
	1    8000 3800
	-1   0    0    1   
$EndComp
Wire Wire Line
	7500 3550 8050 3550
Wire Wire Line
	7800 4050 8050 4050
$Comp
L R R26
U 1 1 548E26D7
P 7800 3800
F 0 "R26" V 7880 3800 40  0000 C CNN
F 1 "82k" V 7807 3801 40  0000 C CNN
F 2 "~" V 7730 3800 30  0000 C CNN
F 3 "~" H 7800 3800 30  0000 C CNN
	1    7800 3800
	-1   0    0    1   
$EndComp
Connection ~ 8000 3550
Connection ~ 8000 4050
Connection ~ 7800 3550
$Comp
L R R33
U 1 1 548E26E0
P 8000 4350
F 0 "R33" V 8080 4350 40  0000 C CNN
F 1 "820" V 8007 4351 40  0000 C CNN
F 2 "~" V 7930 4350 30  0000 C CNN
F 3 "~" H 8000 4350 30  0000 C CNN
	1    8000 4350
	-1   0    0    1   
$EndComp
$Comp
L R R32
U 1 1 548E26E6
P 7700 4350
F 0 "R32" V 7780 4350 40  0000 C CNN
F 1 "27k" V 7707 4351 40  0000 C CNN
F 2 "~" V 7630 4350 30  0000 C CNN
F 3 "~" H 7700 4350 30  0000 C CNN
	1    7700 4350
	-1   0    0    1   
$EndComp
Wire Wire Line
	7700 4650 8000 4650
Wire Wire Line
	8000 4650 8000 4600
Wire Wire Line
	8000 4100 8000 4050
Wire Wire Line
	7500 4050 7700 4050
Wire Wire Line
	7700 4050 7700 4100
Wire Wire Line
	7700 4600 7700 4650
$Comp
L GND #PWR043
U 1 1 548E2821
P 7500 1350
F 0 "#PWR043" H 7500 1350 30  0001 C CNN
F 1 "GND" H 7500 1280 30  0001 C CNN
F 2 "" H 7500 1350 60  0000 C CNN
F 3 "" H 7500 1350 60  0000 C CNN
	1    7500 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 1350 7500 1300
Wire Wire Line
	7500 1300 7800 1300
Wire Wire Line
	7800 1300 7800 1600
$Comp
L GND #PWR044
U 1 1 548E295D
P 7500 3600
F 0 "#PWR044" H 7500 3600 30  0001 C CNN
F 1 "GND" H 7500 3530 30  0001 C CNN
F 2 "" H 7500 3600 60  0000 C CNN
F 3 "" H 7500 3600 60  0000 C CNN
	1    7500 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	7500 3600 7500 3550
Text Notes 7050 3900 0    47   ~ 0
45V DC Max\n15Vmax/Bat
Text Notes 7000 1950 0    47   ~ 0
45V DC Max
$EndSCHEMATC
