EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 7 10
Title "VerilogBoy Handheld"
Date "2020-01-06"
Rev "0.2"
Comp "Wenting Zhang"
Comment1 "zephray@outlook.com"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Switch:SW_Push SW_LEFT1
U 1 1 5EFB6CDB
P 4000 3500
F 0 "SW_LEFT1" H 4000 3693 50  0000 C CNN
F 1 "SW_Push" H 4000 3694 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 4000 3700 50  0001 C CNN
F 3 "~" H 4000 3700 50  0001 C CNN
	1    4000 3500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_UP1
U 1 1 5EFB866D
P 4800 3100
F 0 "SW_UP1" H 4800 3293 50  0000 C CNN
F 1 "SW_Push" H 4800 3294 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 4800 3300 50  0001 C CNN
F 3 "~" H 4800 3300 50  0001 C CNN
	1    4800 3100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_RIGHT1
U 1 1 5EFB8B83
P 5600 3500
F 0 "SW_RIGHT1" H 5600 3693 50  0000 C CNN
F 1 "SW_Push" H 5600 3694 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 5600 3700 50  0001 C CNN
F 3 "~" H 5600 3700 50  0001 C CNN
	1    5600 3500
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_DOWN1
U 1 1 5EFB90E1
P 4800 4000
F 0 "SW_DOWN1" H 4800 4193 50  0000 C CNN
F 1 "SW_Push" H 4800 4194 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 4800 4200 50  0001 C CNN
F 3 "~" H 4800 4200 50  0001 C CNN
	1    4800 4000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_B1
U 1 1 5EFB95A9
P 7300 4000
F 0 "SW_B1" H 7300 4193 50  0000 C CNN
F 1 "SW_Push" H 7300 4194 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 7300 4200 50  0001 C CNN
F 3 "~" H 7300 4200 50  0001 C CNN
	1    7300 4000
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_A1
U 1 1 5EFB9ABA
P 8300 3800
F 0 "SW_A1" H 8300 3993 50  0000 C CNN
F 1 "SW_Push" H 8300 3994 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 8300 4000 50  0001 C CNN
F 3 "~" H 8300 4000 50  0001 C CNN
	1    8300 3800
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_START1
U 1 1 5EFBA0D1
P 7300 3100
F 0 "SW_START1" H 7300 3293 50  0000 C CNN
F 1 "SW_Push" H 7300 3294 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 7300 3300 50  0001 C CNN
F 3 "~" H 7300 3300 50  0001 C CNN
	1    7300 3100
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW_SELECT1
U 1 1 5EFBA462
P 8300 3100
F 0 "SW_SELECT1" H 8300 3293 50  0000 C CNN
F 1 "SW_Push" H 8300 3294 50  0001 C CNN
F 2 "footprint:Contact_4mm" H 8300 3300 50  0001 C CNN
F 3 "~" H 8300 3300 50  0001 C CNN
	1    8300 3100
	1    0    0    -1  
$EndComp
Text GLabel 3300 2300 0    50   Input ~ 0
P15
Text GLabel 3300 2400 0    50   Input ~ 0
P14
Text GLabel 3300 5400 0    50   Output ~ 0
P10
Text GLabel 3300 5300 0    50   Output ~ 0
P11
Text GLabel 3300 5200 0    50   Output ~ 0
P12
Text GLabel 3300 5100 0    50   Output ~ 0
P13
$Comp
L Device:R R500
U 1 1 5EFBAD1B
P 3400 4850
F 0 "R500" H 3470 4896 50  0000 L CNN
F 1 "10K" H 3470 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3330 4850 50  0001 C CNN
F 3 "~" H 3400 4850 50  0001 C CNN
	1    3400 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R501
U 1 1 5EFBC765
P 3700 4850
F 0 "R501" H 3770 4896 50  0000 L CNN
F 1 "10K" H 3770 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3630 4850 50  0001 C CNN
F 3 "~" H 3700 4850 50  0001 C CNN
	1    3700 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R502
U 1 1 5EFBC9E8
P 4000 4850
F 0 "R502" H 4070 4896 50  0000 L CNN
F 1 "10K" H 4070 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 3930 4850 50  0001 C CNN
F 3 "~" H 4000 4850 50  0001 C CNN
	1    4000 4850
	1    0    0    -1  
$EndComp
$Comp
L Device:R R503
U 1 1 5EFBCD99
P 4300 4850
F 0 "R503" H 4370 4896 50  0000 L CNN
F 1 "10K" H 4370 4805 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4230 4850 50  0001 C CNN
F 3 "~" H 4300 4850 50  0001 C CNN
	1    4300 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3300 2400 4500 2400
Wire Wire Line
	4500 2400 4500 3100
Wire Wire Line
	4500 4000 4600 4000
Wire Wire Line
	4600 3100 4500 3100
Connection ~ 4500 3100
Wire Wire Line
	4500 3100 4500 3500
Wire Wire Line
	3800 3500 3800 3100
Wire Wire Line
	3800 3100 4500 3100
Wire Wire Line
	5400 3500 4500 3500
Connection ~ 4500 3500
Wire Wire Line
	4500 3500 4500 4000
Wire Wire Line
	3300 2300 7000 2300
Wire Wire Line
	7000 2300 7000 3100
Wire Wire Line
	7000 4000 7100 4000
Wire Wire Line
	7100 3100 7000 3100
Connection ~ 7000 3100
Wire Wire Line
	7000 3100 7000 3200
Wire Wire Line
	7000 3200 8000 3200
Wire Wire Line
	8000 3200 8000 3100
Wire Wire Line
	8000 3100 8100 3100
Connection ~ 7000 3200
Wire Wire Line
	7000 3200 7000 3800
Wire Wire Line
	8100 3800 7000 3800
Connection ~ 7000 3800
Wire Wire Line
	7000 3800 7000 4000
Wire Wire Line
	3300 5100 3400 5100
Wire Wire Line
	5100 5100 5100 4000
Wire Wire Line
	5100 4000 5000 4000
Wire Wire Line
	3400 5000 3400 5100
Connection ~ 3400 5100
Wire Wire Line
	3400 5100 5100 5100
Wire Wire Line
	3300 5200 3700 5200
Wire Wire Line
	5200 5200 5200 3100
Wire Wire Line
	5200 3100 5000 3100
Wire Wire Line
	3700 5000 3700 5200
Connection ~ 3700 5200
Wire Wire Line
	3700 5200 5200 5200
Wire Wire Line
	3300 5300 4000 5300
Wire Wire Line
	5300 5300 5300 3600
Wire Wire Line
	5300 3600 4200 3600
Wire Wire Line
	4200 3600 4200 3500
Wire Wire Line
	4000 5000 4000 5300
Connection ~ 4000 5300
Wire Wire Line
	4000 5300 5300 5300
Wire Wire Line
	3300 5400 4300 5400
Wire Wire Line
	5400 5400 5400 3600
Wire Wire Line
	5400 3600 5800 3600
Wire Wire Line
	5800 3600 5800 3500
Wire Wire Line
	4300 5000 4300 5400
Connection ~ 4300 5400
Wire Wire Line
	4300 5400 5400 5400
Wire Wire Line
	5100 5100 7600 5100
Wire Wire Line
	7600 5100 7600 3100
Wire Wire Line
	7600 3100 7500 3100
Connection ~ 5100 5100
Wire Wire Line
	5200 5200 8600 5200
Wire Wire Line
	8600 5200 8600 3100
Wire Wire Line
	8600 3100 8500 3100
Connection ~ 5200 5200
Wire Wire Line
	5300 5300 7700 5300
Wire Wire Line
	7700 5300 7700 4000
Wire Wire Line
	7700 4000 7500 4000
Connection ~ 5300 5300
Wire Wire Line
	5400 5400 8700 5400
Wire Wire Line
	8700 5400 8700 3800
Wire Wire Line
	8700 3800 8500 3800
Connection ~ 5400 5400
$Comp
L power:+3V3 #PWR086
U 1 1 5EFC56FA
P 3400 4600
F 0 "#PWR086" H 3400 4450 50  0001 C CNN
F 1 "+3V3" H 3415 4773 50  0000 C CNN
F 2 "" H 3400 4600 50  0001 C CNN
F 3 "" H 3400 4600 50  0001 C CNN
	1    3400 4600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4300 4700 4300 4600
Wire Wire Line
	4300 4600 4000 4600
Wire Wire Line
	3400 4700 3400 4600
Connection ~ 3400 4600
Wire Wire Line
	3700 4700 3700 4600
Connection ~ 3700 4600
Wire Wire Line
	3700 4600 3400 4600
Wire Wire Line
	4000 4700 4000 4600
Connection ~ 4000 4600
Wire Wire Line
	4000 4600 3700 4600
$Comp
L Connector_Generic_MountingPin:Conn_01x04_MountingPin ENC1
U 1 1 5EFD1C01
P 3600 6000
F 0 "ENC1" H 3688 5914 50  0000 L CNN
F 1 "SIQ-02FVS3" H 3688 5823 50  0000 L CNN
F 2 "footprint:SIQ-02FVS3" H 3600 6000 50  0001 C CNN
F 3 "~" H 3600 6000 50  0001 C CNN
	1    3600 6000
	1    0    0    -1  
$EndComp
Text GLabel 3300 5900 0    50   Output ~ 0
ENC_A
Text GLabel 3300 6000 0    50   Output ~ 0
ENC_B
Text GLabel 3300 6100 0    50   Output ~ 0
PEK
$Comp
L power:GND #PWR087
U 1 1 5EFD2C7B
P 3600 6400
F 0 "#PWR087" H 3600 6150 50  0001 C CNN
F 1 "GND" H 3605 6227 50  0000 C CNN
F 2 "" H 3600 6400 50  0001 C CNN
F 3 "" H 3600 6400 50  0001 C CNN
	1    3600 6400
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 6200 3400 6400
Wire Wire Line
	3400 6400 3600 6400
Connection ~ 3600 6400
Wire Wire Line
	3300 6100 3400 6100
Wire Wire Line
	3300 5900 3400 5900
Wire Wire Line
	3300 6000 3400 6000
$EndSCHEMATC
