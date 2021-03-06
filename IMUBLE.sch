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
LIBS:Cypress_BLE
LIBS:components
LIBS:IMUBLE-cache
EELAYER 25 0
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
L CY8CKIT-142 U4
U 1 1 571F7D26
P 5050 2200
F 0 "U4" H 4800 3650 60  0000 C CNN
F 1 "CY8CKIT-142" H 5050 3550 60  0000 C CNN
F 2 "CypressModule:CY8CKIT-142" H 3250 2250 60  0001 C CNN
F 3 "" H 3250 2250 60  0000 C CNN
	1    5050 2200
	1    0    0    -1  
$EndComp
$Comp
L SL_LSM9DS0 U3
U 1 1 571F8B79
P 2200 2600
F 0 "U3" H 1800 3250 60  0000 C CNN
F 1 "SL_LSM9DS0" H 2350 3250 60  0000 C CNN
F 2 "components:ST_LSM9DS0" H 1850 2550 60  0001 C CNN
F 3 "" H 1850 2550 60  0000 C CNN
	1    2200 2600
	1    0    0    -1  
$EndComp
$Comp
L SL_ADXL375 U1
U 1 1 5723ADC9
P 2150 1300
F 0 "U1" H 1650 850 60  0000 C CNN
F 1 "SL_ADXL375" H 2450 850 60  0000 C CNN
F 2 "components:ST_ADXL375" H 2150 1300 60  0001 C CNN
F 3 "" H 2150 1300 60  0000 C CNN
	1    2150 1300
	1    0    0    -1  
$EndComp
$Comp
L NJM11100 U2
U 1 1 5723B2F6
P 2150 4100
F 0 "U2" H 1800 4450 60  0000 C CNN
F 1 "NJM11100" H 2300 4450 60  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 2150 3950 60  0001 C CNN
F 3 "" H 2150 3950 60  0000 C CNN
	1    2150 4100
	1    0    0    -1  
$EndComp
$Comp
L Battery BT1
U 1 1 5723B36F
P 1100 4200
F 0 "BT1" H 1200 4250 50  0000 L CNN
F 1 "CR2" H 1200 4150 50  0000 L CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x02" V 1100 4240 50  0001 C CNN
F 3 "" V 1100 4240 50  0000 C CNN
	1    1100 4200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR01
U 1 1 5723B3D8
P 1100 4350
F 0 "#PWR01" H 1100 4100 50  0001 C CNN
F 1 "GND" H 1100 4200 50  0000 C CNN
F 2 "" H 1100 4350 50  0000 C CNN
F 3 "" H 1100 4350 50  0000 C CNN
	1    1100 4350
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 5723B558
P 2150 4550
F 0 "#PWR02" H 2150 4300 50  0001 C CNN
F 1 "GND" H 2150 4400 50  0000 C CNN
F 2 "" H 2150 4550 50  0000 C CNN
F 3 "" H 2150 4550 50  0000 C CNN
	1    2150 4550
	1    0    0    -1  
$EndComp
$Comp
L C_Small C1
U 1 1 5723B5A0
P 1450 4400
F 0 "C1" H 1460 4470 50  0000 L CNN
F 1 "100n" H 1460 4320 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1450 4400 50  0001 C CNN
F 3 "" H 1450 4400 50  0000 C CNN
	1    1450 4400
	1    0    0    -1  
$EndComp
$Comp
L C_Small C3
U 1 1 5723B62D
P 2900 4000
F 0 "C3" H 2700 4050 50  0000 L CNN
F 1 "100p" H 2700 3950 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2900 4000 50  0001 C CNN
F 3 "" H 2900 4000 50  0000 C CNN
	1    2900 4000
	1    0    0    -1  
$EndComp
$Comp
L R_Small R1
U 1 1 5723B675
P 3150 4000
F 0 "R1" H 3180 4020 50  0000 L CNN
F 1 "10k" H 3180 3960 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 3150 4000 50  0001 C CNN
F 3 "" H 3150 4000 50  0000 C CNN
	1    3150 4000
	1    0    0    -1  
$EndComp
$Comp
L R_Small R2
U 1 1 5723B6CA
P 3150 4400
F 0 "R2" H 3180 4420 50  0000 L CNN
F 1 "10k" H 3180 4360 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 3150 4400 50  0001 C CNN
F 3 "" H 3150 4400 50  0000 C CNN
	1    3150 4400
	1    0    0    -1  
$EndComp
$Comp
L C_Small C2
U 1 1 5723B6FF
P 2750 4400
F 0 "C2" H 2760 4470 50  0000 L CNN
F 1 "10n" H 2760 4320 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 2750 4400 50  0001 C CNN
F 3 "" H 2750 4400 50  0000 C CNN
	1    2750 4400
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR03
U 1 1 5723B9ED
P 2750 4500
F 0 "#PWR03" H 2750 4250 50  0001 C CNN
F 1 "GND" H 2750 4350 50  0000 C CNN
F 2 "" H 2750 4500 50  0000 C CNN
F 3 "" H 2750 4500 50  0000 C CNN
	1    2750 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 5723BA16
P 3150 4500
F 0 "#PWR04" H 3150 4250 50  0001 C CNN
F 1 "GND" H 3150 4350 50  0000 C CNN
F 2 "" H 3150 4500 50  0000 C CNN
F 3 "" H 3150 4500 50  0000 C CNN
	1    3150 4500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR05
U 1 1 5723BA3F
P 1450 4550
F 0 "#PWR05" H 1450 4300 50  0001 C CNN
F 1 "GND" H 1450 4400 50  0000 C CNN
F 2 "" H 1450 4550 50  0000 C CNN
F 3 "" H 1450 4550 50  0000 C CNN
	1    1450 4550
	1    0    0    -1  
$EndComp
$Comp
L +2.5V #PWR06
U 1 1 5723BDA2
P 3400 3900
F 0 "#PWR06" H 3400 3750 50  0001 C CNN
F 1 "+2.5V" H 3400 4040 50  0000 C CNN
F 2 "" H 3400 3900 50  0000 C CNN
F 3 "" H 3400 3900 50  0000 C CNN
	1    3400 3900
	1    0    0    -1  
$EndComp
$Comp
L +2.5V #PWR07
U 1 1 5723C3E6
P 4550 3250
F 0 "#PWR07" H 4550 3100 50  0001 C CNN
F 1 "+2.5V" H 4550 3390 50  0000 C CNN
F 2 "" H 4550 3250 50  0000 C CNN
F 3 "" H 4550 3250 50  0000 C CNN
	1    4550 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR08
U 1 1 5723C40F
P 4550 3450
F 0 "#PWR08" H 4550 3200 50  0001 C CNN
F 1 "GND" H 4550 3300 50  0000 C CNN
F 2 "" H 4550 3450 50  0000 C CNN
F 3 "" H 4550 3450 50  0000 C CNN
	1    4550 3450
	1    0    0    -1  
$EndComp
$Comp
L +2.5V #PWR09
U 1 1 5723C7BF
P 1400 2800
F 0 "#PWR09" H 1400 2650 50  0001 C CNN
F 1 "+2.5V" H 1400 2940 50  0000 C CNN
F 2 "" H 1400 2800 50  0000 C CNN
F 3 "" H 1400 2800 50  0000 C CNN
	1    1400 2800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 5723C810
P 1400 3100
F 0 "#PWR010" H 1400 2850 50  0001 C CNN
F 1 "GND" H 1400 2950 50  0000 C CNN
F 2 "" H 1400 3100 50  0000 C CNN
F 3 "" H 1400 3100 50  0000 C CNN
	1    1400 3100
	1    0    0    -1  
$EndComp
$Comp
L +2.5V #PWR011
U 1 1 5723C9AD
P 2950 1000
F 0 "#PWR011" H 2950 850 50  0001 C CNN
F 1 "+2.5V" H 2950 1140 50  0000 C CNN
F 2 "" H 2950 1000 50  0000 C CNN
F 3 "" H 2950 1000 50  0000 C CNN
	1    2950 1000
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 5723C9D6
P 2950 1600
F 0 "#PWR012" H 2950 1350 50  0001 C CNN
F 1 "GND" H 2950 1450 50  0000 C CNN
F 2 "" H 2950 1600 50  0000 C CNN
F 3 "" H 2950 1600 50  0000 C CNN
	1    2950 1600
	1    0    0    -1  
$EndComp
Text Label 4000 1600 0    60   ~ 0
LSM_MOSI
Text Label 4000 1700 0    60   ~ 0
LSM_MISO
Text Label 4000 1800 0    60   ~ 0
LSM_CS_G
Text Label 4000 2300 0    60   ~ 0
LSM_CS_XM
Text Label 4000 1900 0    60   ~ 0
LSM_SCK
Text Label 4000 2600 0    60   ~ 0
ADX_MOSI
Text Label 4000 2700 0    60   ~ 0
ADX_MISO
Text Label 4000 2800 0    60   ~ 0
ADX_CS
Text Label 4000 2900 0    60   ~ 0
ADX_SCK
Wire Wire Line
	1100 4050 1100 3900
Wire Wire Line
	1100 3900 1550 3900
Wire Wire Line
	1550 3900 1550 4100
Connection ~ 1550 3900
Wire Wire Line
	2750 4100 3150 4100
Wire Wire Line
	2750 3900 3400 3900
Connection ~ 2900 3900
Connection ~ 2900 4100
Wire Wire Line
	3150 4100 3150 4300
Connection ~ 3150 4100
Wire Wire Line
	2750 4200 2750 4300
Wire Wire Line
	2150 4550 2150 4550
Wire Wire Line
	1450 4500 1450 4550
Wire Wire Line
	1450 4300 1450 3900
Connection ~ 1450 3900
Connection ~ 3150 3900
Wire Wire Line
	4550 3350 4550 3350
Wire Wire Line
	4550 3150 4550 3150
Wire Wire Line
	1400 3100 1550 3100
Wire Wire Line
	1550 2900 1400 2900
Wire Wire Line
	1400 2900 1400 2800
Wire Wire Line
	1400 2800 1550 2800
Connection ~ 1400 2800
Wire Wire Line
	2950 1600 2950 1500
Wire Wire Line
	2950 1100 2950 1000
Connection ~ 2950 1600
Connection ~ 2950 1000
Wire Wire Line
	4550 1600 4000 1600
Wire Wire Line
	4550 1700 4000 1700
Wire Wire Line
	4550 1800 4000 1800
Wire Wire Line
	4550 1900 4000 1900
Wire Wire Line
	4550 2300 4000 2300
Wire Wire Line
	4550 2600 4000 2600
Wire Wire Line
	4000 2700 4550 2700
Wire Wire Line
	4550 2800 4000 2800
Wire Wire Line
	4000 2900 4550 2900
Wire Wire Line
	1550 2100 1050 2100
Wire Wire Line
	1550 2200 1050 2200
Wire Wire Line
	1550 2400 1050 2400
Wire Wire Line
	1550 2300 1050 2300
Wire Wire Line
	1550 2500 1050 2500
Wire Wire Line
	1550 2600 1050 2600
Text Label 1050 2100 0    60   ~ 0
LSM_CS_G
Text Label 1050 2200 0    60   ~ 0
LSM_CS_XM
Text Label 1050 2300 0    60   ~ 0
LSM_MISO
Text Label 1050 2400 0    60   ~ 0
LSM_MOSI
Text Label 1050 2500 0    60   ~ 0
LSM_SCK
Text Label 1050 2600 0    60   ~ 0
LSM_MISO
Wire Wire Line
	1350 1000 850  1000
Wire Wire Line
	1350 1100 850  1100
Wire Wire Line
	1350 1200 850  1200
Wire Wire Line
	1350 1300 850  1300
Text Label 850  1000 0    60   ~ 0
ADX_SCK
Text Label 850  1200 0    60   ~ 0
ADX_MISO
Text Label 850  1100 0    60   ~ 0
ADX_MOSI
Text Label 850  1300 0    60   ~ 0
ADX_CS
Wire Wire Line
	2850 2100 3300 2100
Wire Wire Line
	2850 2200 3300 2200
Wire Wire Line
	2850 2300 3300 2300
Wire Wire Line
	2850 2500 3300 2500
Wire Wire Line
	2850 2600 3300 2600
Wire Wire Line
	1350 1500 850  1500
Wire Wire Line
	1350 1600 850  1600
Text Label 850  1500 0    60   ~ 0
ADX_INT1
Text Label 850  1600 0    60   ~ 0
ADX_INT2
Text Label 2900 2100 0    60   ~ 0
LSM_INT2
Text Label 2900 2200 0    60   ~ 0
LSM_INT1
Text Label 2900 2300 0    60   ~ 0
LSM_INTG
Text Label 2850 2500 0    60   ~ 0
LSM_DRDY
Text Label 2900 2600 0    60   ~ 0
LSM_DEN
Wire Wire Line
	4000 2000 4550 2000
Wire Wire Line
	4000 2100 4550 2100
Wire Wire Line
	4000 2200 4550 2200
Wire Wire Line
	6100 1600 5550 1600
Wire Wire Line
	5550 1700 6100 1700
Text Label 4000 2000 0    60   ~ 0
LSM_INT2
Text Label 4000 2100 0    60   ~ 0
LSM_INT1
Text Label 4000 2200 0    60   ~ 0
LSM_INTG
Text Label 6100 1600 2    60   ~ 0
LSM_DRDY
Text Label 5700 1700 0    60   ~ 0
LSM_DEN
Wire Wire Line
	4000 2400 4550 2400
Wire Wire Line
	4000 2500 4550 2500
Text Label 4000 2400 0    60   ~ 0
ADX_INT1
Text Label 4000 2500 0    60   ~ 0
ADX_INT2
Wire Wire Line
	5550 1500 6700 1500
$Comp
L C_Small C4
U 1 1 572441A7
P 3400 4150
F 0 "C4" H 3410 4220 50  0000 L CNN
F 1 "1u" H 3410 4070 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 3400 4150 50  0001 C CNN
F 3 "" H 3400 4150 50  0000 C CNN
	1    3400 4150
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 3900 3400 4050
Wire Wire Line
	3400 4250 3400 4500
$Comp
L GND #PWR013
U 1 1 572442EA
P 3400 4500
F 0 "#PWR013" H 3400 4250 50  0001 C CNN
F 1 "GND" H 3400 4350 50  0000 C CNN
F 2 "" H 3400 4500 50  0000 C CNN
F 3 "" H 3400 4500 50  0000 C CNN
	1    3400 4500
	1    0    0    -1  
$EndComp
Connection ~ 3400 3900
NoConn ~ 5550 1000
NoConn ~ 5550 1100
$Comp
L Led_Small D1
U 1 1 5724509D
P 6700 2100
F 0 "D1" H 6600 2200 50  0000 L CNN
F 1 "RED" H 6750 2200 50  0000 L CNN
F 2 "LEDs:LED_0805" V 6700 2100 50  0001 C CNN
F 3 "" V 6700 2100 50  0000 C CNN
	1    6700 2100
	0    -1   -1   0   
$EndComp
$Comp
L Led_Small D2
U 1 1 572458A6
P 6900 2100
F 0 "D2" H 6800 2200 50  0000 L CNN
F 1 "GREEN" H 6950 2200 50  0000 L CNN
F 2 "LEDs:LED_0805" V 6900 2100 50  0001 C CNN
F 3 "" V 6900 2100 50  0000 C CNN
	1    6900 2100
	0    -1   -1   0   
$EndComp
$Comp
L R_Small R6
U 1 1 57245F0A
P 6700 1700
F 0 "R6" H 6730 1720 50  0000 L CNN
F 1 "470" H 6730 1660 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 6700 1700 50  0001 C CNN
F 3 "" H 6700 1700 50  0000 C CNN
	1    6700 1700
	1    0    0    -1  
$EndComp
$Comp
L R_Small R7
U 1 1 57246072
P 6900 1700
F 0 "R7" H 6930 1720 50  0000 L CNN
F 1 "470" H 6930 1660 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 6900 1700 50  0001 C CNN
F 3 "" H 6900 1700 50  0000 C CNN
	1    6900 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	6700 1800 6700 2000
Wire Wire Line
	6900 2000 6900 1800
Wire Wire Line
	6900 1400 6900 1600
Wire Wire Line
	6900 1400 5550 1400
Wire Wire Line
	6700 1500 6700 1600
$Comp
L GND #PWR014
U 1 1 57246400
P 6700 2200
F 0 "#PWR014" H 6700 1950 50  0001 C CNN
F 1 "GND" H 6700 2050 50  0000 C CNN
F 2 "" H 6700 2200 50  0000 C CNN
F 3 "" H 6700 2200 50  0000 C CNN
	1    6700 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR015
U 1 1 57246438
P 6900 2200
F 0 "#PWR015" H 6900 1950 50  0001 C CNN
F 1 "GND" H 6900 2050 50  0000 C CNN
F 2 "" H 6900 2200 50  0000 C CNN
F 3 "" H 6900 2200 50  0000 C CNN
	1    6900 2200
	1    0    0    -1  
$EndComp
$Comp
L +BATT #PWR016
U 1 1 57246870
P 1100 3900
F 0 "#PWR016" H 1100 3750 50  0001 C CNN
F 1 "+BATT" H 1100 4040 50  0000 C CNN
F 2 "" H 1100 3900 50  0000 C CNN
F 3 "" H 1100 3900 50  0000 C CNN
	1    1100 3900
	1    0    0    -1  
$EndComp
Connection ~ 1100 3900
$Comp
L +BATT #PWR017
U 1 1 572468B1
P 5900 2350
F 0 "#PWR017" H 5900 2200 50  0001 C CNN
F 1 "+BATT" H 5900 2490 50  0000 C CNN
F 2 "" H 5900 2350 50  0000 C CNN
F 3 "" H 5900 2350 50  0000 C CNN
	1    5900 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 2600 5900 2600
$Comp
L R_Small R3
U 1 1 57246B95
P 5900 2450
F 0 "R3" H 5930 2470 50  0000 L CNN
F 1 "2k" H 5930 2410 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 5900 2450 50  0001 C CNN
F 3 "" H 5900 2450 50  0000 C CNN
	1    5900 2450
	1    0    0    -1  
$EndComp
$Comp
L R_Small R4
U 1 1 57246BED
P 5900 2750
F 0 "R4" H 5930 2770 50  0000 L CNN
F 1 "1k" H 5930 2710 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 5900 2750 50  0001 C CNN
F 3 "" H 5900 2750 50  0000 C CNN
	1    5900 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 2550 5900 2650
$Comp
L GND #PWR018
U 1 1 57246D6C
P 5900 2850
F 0 "#PWR018" H 5900 2600 50  0001 C CNN
F 1 "GND" H 5900 2700 50  0000 C CNN
F 2 "" H 5900 2850 50  0000 C CNN
F 3 "" H 5900 2850 50  0000 C CNN
	1    5900 2850
	1    0    0    -1  
$EndComp
Connection ~ 5900 2600
$Comp
L R_Small R5
U 1 1 57247F7A
P 6350 2300
F 0 "R5" H 6380 2320 50  0000 L CNN
F 1 "10k" H 6380 2260 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" H 6350 2300 50  0001 C CNN
F 3 "" H 6350 2300 50  0000 C CNN
	1    6350 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 2400 6350 2400
$Comp
L +2.5V #PWR019
U 1 1 572480FA
P 6350 2200
F 0 "#PWR019" H 6350 2050 50  0001 C CNN
F 1 "+2.5V" H 6350 2340 50  0000 C CNN
F 2 "" H 6350 2200 50  0000 C CNN
F 3 "" H 6350 2200 50  0000 C CNN
	1    6350 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR020
U 1 1 57248170
P 6350 2850
F 0 "#PWR020" H 6350 2600 50  0001 C CNN
F 1 "GND" H 6350 2700 50  0000 C CNN
F 2 "" H 6350 2850 50  0000 C CNN
F 3 "" H 6350 2850 50  0000 C CNN
	1    6350 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6350 2850 6350 2800
Connection ~ 6350 2400
NoConn ~ 5550 1800
NoConn ~ 5550 2000
NoConn ~ 5550 2100
NoConn ~ 5550 2200
NoConn ~ 5550 2300
NoConn ~ 5550 2400
NoConn ~ 5550 2500
NoConn ~ 5550 2700
NoConn ~ 5550 2800
NoConn ~ 5550 3000
NoConn ~ 5550 3100
NoConn ~ 5550 3200
NoConn ~ 5550 3300
$Comp
L PUSH_SW SW1
U 1 1 572476FC
P 6350 2600
F 0 "SW1" H 6350 2750 50  0000 C CNN
F 1 "SKWPACE010" H 6350 2850 50  0000 C CNN
F 2 "components:SKRPACE010" H 6350 2450 60  0001 C CNN
F 3 "" H 6350 2450 60  0000 C CNN
	1    6350 2600
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG021
U 1 1 5727A318
P 1450 3900
F 0 "#FLG021" H 1450 3995 50  0001 C CNN
F 1 "PWR_FLAG" H 1450 4080 50  0001 C CNN
F 2 "" H 1450 3900 60  0000 C CNN
F 3 "" H 1450 3900 60  0000 C CNN
	1    1450 3900
	1    0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG022
U 1 1 5727A4A5
P 1050 4950
F 0 "#FLG022" H 1050 5045 50  0001 C CNN
F 1 "PWR_FLAG" H 1050 5130 50  0001 C CNN
F 2 "" H 1050 4950 60  0000 C CNN
F 3 "" H 1050 4950 60  0000 C CNN
	1    1050 4950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR023
U 1 1 5727AA41
P 1050 4950
F 0 "#PWR023" H 1050 4700 50  0001 C CNN
F 1 "GND" H 1050 4800 50  0000 C CNN
F 2 "" H 1050 4950 50  0000 C CNN
F 3 "" H 1050 4950 50  0000 C CNN
	1    1050 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	5550 1900 6200 1900
Wire Wire Line
	6200 1900 6200 2400
$Comp
L CONN_01X05 P1
U 1 1 574467BA
P 4050 1200
F 0 "P1" H 4050 1500 50  0000 C CNN
F 1 "CONN_01X05" V 4150 1200 50  0001 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 4050 1200 50  0001 C CNN
F 3 "" H 4050 1200 50  0000 C CNN
	1    4050 1200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	4550 1000 4250 1000
Wire Wire Line
	4550 1200 4250 1200
Wire Wire Line
	4250 1300 4550 1300
Wire Wire Line
	4550 1400 4250 1400
$Comp
L GND #PWR024
U 1 1 574475A1
P 4300 1100
F 0 "#PWR024" H 4300 850 50  0001 C CNN
F 1 "GND" H 4300 950 50  0000 C CNN
F 2 "" H 4300 1100 50  0000 C CNN
F 3 "" H 4300 1100 50  0000 C CNN
	1    4300 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 1100 4250 1100
$Comp
L CONN_01X02 P2
U 1 1 574480C8
P 5950 3250
F 0 "P2" H 5950 3400 50  0000 C CNN
F 1 "DebugTX" V 6050 3250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 5950 3250 50  0000 C CNN
F 3 "" H 5950 3250 50  0000 C CNN
	1    5950 3250
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR025
U 1 1 5744832F
P 5750 3300
F 0 "#PWR025" H 5750 3050 50  0001 C CNN
F 1 "GND" H 5750 3150 50  0000 C CNN
F 2 "" H 5750 3300 50  0000 C CNN
F 3 "" H 5750 3300 50  0000 C CNN
	1    5750 3300
	1    0    0    -1  
$EndComp
Wire Wire Line
	5750 3200 5750 2900
Wire Wire Line
	5750 2900 5550 2900
$EndSCHEMATC
