EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 10 10
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
L symbols:XC7S25-CSGA225 U?
U 4 1 5FEEF0D0
P 3500 5800
F 0 "U?" H 3500 4425 50  0000 C CNN
F 1 "XC7S25-CSGA225" H 3500 4334 50  0000 C CNN
F 2 "Package_BGA:Xilinx_CSGA225" H 3500 5800 50  0001 C CNN
F 3 "https://www.xilinx.com/support/documentation/data_sheets/ds180_7Series_Overview.pdf" H 3500 5800 50  0001 C CNN
	4    3500 5800
	1    0    0    -1  
$EndComp
$Comp
L symbols:XC7S25-CSGA225 U?
U 3 1 5FEEB2B7
P 8500 2500
F 0 "U?" H 8500 1125 50  0000 C CNN
F 1 "XC7S25-CSGA225" H 8500 1034 50  0000 C CNN
F 2 "Package_BGA:Xilinx_CSGA225" H 8500 2500 50  0001 C CNN
F 3 "https://www.xilinx.com/support/documentation/data_sheets/ds180_7Series_Overview.pdf" H 8500 2500 50  0001 C CNN
	3    8500 2500
	1    0    0    -1  
$EndComp
$Comp
L symbols:XC7S25-CSGA225 U?
U 2 1 5FEE1FC1
P 3500 2500
F 0 "U?" H 3500 1125 50  0000 C CNN
F 1 "XC7S25-CSGA225" H 3500 1034 50  0000 C CNN
F 2 "Package_BGA:Xilinx_CSGA225" H 3500 2500 50  0001 C CNN
F 3 "https://www.xilinx.com/support/documentation/data_sheets/ds180_7Series_Overview.pdf" H 3500 2500 50  0001 C CNN
	2    3500 2500
	1    0    0    -1  
$EndComp
Text Label 7900 4800 1    50   ~ 0
DONE
Text Label 8100 4800 1    50   ~ 0
PROGRAM_B
Text Label 8800 4800 1    50   ~ 0
FPGA_TDI
Text Label 8900 4800 1    50   ~ 0
FPGA_TDO
Text Label 8700 4800 1    50   ~ 0
FPGA_TCK
Text Label 9000 4800 1    50   ~ 0
FPGA_TMS
$Comp
L Device:R R?
U 1 1 5FFE979B
P 7150 4600
AR Path="/5E129219/5FFE979B" Ref="R?"  Part="1" 
AR Path="/5FEE12C8/5FFE979B" Ref="R?"  Part="1" 
F 0 "R?" V 7100 4400 50  0000 C CNN
F 1 "10K" V 7100 4800 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" V 7080 4600 50  0001 C CNN
F 3 "~" H 7150 4600 50  0001 C CNN
	1    7150 4600
	0    1    1    0   
$EndComp
Wire Wire Line
	8800 4350 8800 4900
Wire Wire Line
	8900 4350 8900 4900
Wire Wire Line
	9000 4350 9000 4900
Wire Wire Line
	8700 4350 8700 4900
$Comp
L power:+3V3 #PWR?
U 1 1 5FFE97A5
P 6900 4400
AR Path="/5E129219/5FFE97A5" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE97A5" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6900 4250 50  0001 C CNN
F 1 "+3V3" V 6915 4528 50  0000 L CNN
F 2 "" H 6900 4400 50  0001 C CNN
F 3 "" H 6900 4400 50  0001 C CNN
	1    6900 4400
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 4400 7000 4400
Text Label 7700 4800 1    50   ~ 0
FPGA_CCLK
Wire Wire Line
	7700 4900 7700 4300
$Comp
L Device:C C?
U 1 1 5FFE97AE
P 6150 6800
AR Path="/5E1291BC/5FFE97AE" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE97AE" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE97AE" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6650 50  0000 C CNN
F 1 "470nF" V 6100 6950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 6650 50  0001 C CNN
F 3 "~" H 6150 6800 50  0001 C CNN
	1    6150 6800
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE97B4
P 6150 6900
AR Path="/5E1291BC/5FFE97B4" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE97B4" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE97B4" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6750 50  0000 C CNN
F 1 "470nF" V 6100 7050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 6750 50  0001 C CNN
F 3 "~" H 6150 6900 50  0001 C CNN
	1    6150 6900
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE97BA
P 6150 7000
AR Path="/5E1291BC/5FFE97BA" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE97BA" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE97BA" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6850 50  0000 C CNN
F 1 "4.7uF" V 6100 7150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 6850 50  0001 C CNN
F 3 "~" H 6150 7000 50  0001 C CNN
	1    6150 7000
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FFE97C0
P 5900 7100
AR Path="/5E129219/5FFE97C0" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE97C0" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5900 6850 50  0001 C CNN
F 1 "GND" H 5905 6927 50  0000 C CNN
F 2 "" H 5900 7100 50  0001 C CNN
F 3 "" H 5900 7100 50  0001 C CNN
	1    5900 7100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6000 6800 5900 6800
Wire Wire Line
	5900 6800 5900 6900
Wire Wire Line
	6000 6900 5900 6900
Connection ~ 5900 6900
Wire Wire Line
	5900 6900 5900 7000
Wire Wire Line
	6000 7000 5900 7000
Connection ~ 5900 7000
Wire Wire Line
	5900 7000 5900 7100
Wire Wire Line
	6300 7000 6400 7000
Wire Wire Line
	6400 7000 6400 6900
Connection ~ 6400 6800
Wire Wire Line
	6400 6800 6300 6800
Wire Wire Line
	6300 6900 6400 6900
Wire Wire Line
	6400 6900 6400 6800
$Comp
L power:+3V3 #PWR?
U 1 1 5FFE97D4
P 6400 6800
AR Path="/5E129219/5FFE97D4" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE97D4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6400 6650 50  0001 C CNN
F 1 "+3V3" H 6415 6973 50  0000 C CNN
F 2 "" H 6400 6800 50  0001 C CNN
F 3 "" H 6400 6800 50  0001 C CNN
	1    6400 6800
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FFE97DC
P 10800 5600
AR Path="/5E129219/5FFE97DC" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE97DC" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10800 5350 50  0001 C CNN
F 1 "GND" H 10805 5427 50  0000 C CNN
F 2 "" H 10800 5600 50  0001 C CNN
F 3 "" H 10800 5600 50  0001 C CNN
	1    10800 5600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10700 5800 10700 5600
Wire Wire Line
	10800 5600 10700 5600
$Comp
L power:GND #PWR?
U 1 1 5FFE97E4
P 10000 4800
AR Path="/5E129219/5FFE97E4" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE97E4" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 10000 4550 50  0001 C CNN
F 1 "GND" H 10005 4627 50  0000 C CNN
F 2 "" H 10000 4800 50  0001 C CNN
F 3 "" H 10000 4800 50  0001 C CNN
	1    10000 4800
	0    -1   -1   0   
$EndComp
Wire Wire Line
	9300 4900 9300 4800
Wire Wire Line
	9300 4800 9500 4800
Wire Wire Line
	9500 4900 9500 4800
Connection ~ 9500 4800
Wire Wire Line
	9500 4800 9600 4800
Wire Wire Line
	9600 4900 9600 4800
Connection ~ 9600 4800
Wire Wire Line
	9600 4800 9800 4800
Wire Wire Line
	9800 4900 9800 4800
Connection ~ 9800 4800
Wire Wire Line
	9800 4800 9900 4800
Wire Wire Line
	9900 4900 9900 4800
Connection ~ 9900 4800
Wire Wire Line
	9900 4800 10000 4800
Connection ~ 6400 6900
Wire Wire Line
	6000 5700 5900 5700
Wire Wire Line
	5900 5600 5900 5700
Connection ~ 5900 5600
Wire Wire Line
	6000 5600 5900 5600
Wire Wire Line
	5900 5500 5900 5600
Wire Wire Line
	6000 5500 5900 5500
Wire Wire Line
	6400 5700 6400 5600
Wire Wire Line
	6300 5700 6400 5700
Wire Wire Line
	6400 5600 6400 5500
Connection ~ 6400 5600
Wire Wire Line
	6300 5600 6400 5600
Wire Wire Line
	6300 5500 6400 5500
Connection ~ 6400 5500
$Comp
L power:+1V2 #PWR?
U 1 1 5FFE9806
P 6400 5500
AR Path="/5E1291BC/5FFE9806" Ref="#PWR?"  Part="1" 
AR Path="/5E129219/5FFE9806" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE9806" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6400 5350 50  0001 C CNN
F 1 "+1V2" H 6415 5673 50  0000 C CNN
F 2 "" H 6400 5500 50  0001 C CNN
F 3 "" H 6400 5500 50  0001 C CNN
	1    6400 5500
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE980C
P 6150 5700
AR Path="/5E1291BC/5FFE980C" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE980C" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE980C" Ref="C?"  Part="1" 
F 0 "C?" V 6100 5550 50  0000 C CNN
F 1 "47uF" V 6100 5850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 5550 50  0001 C CNN
F 3 "~" H 6150 5700 50  0001 C CNN
	1    6150 5700
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE9812
P 6150 5600
AR Path="/5E129219/5FFE9812" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9812" Ref="C?"  Part="1" 
F 0 "C?" V 6100 5450 50  0000 C CNN
F 1 "4.7uF" V 6100 5750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 5450 50  0001 C CNN
F 3 "~" H 6150 5600 50  0001 C CNN
	1    6150 5600
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE9818
P 6150 5500
AR Path="/5E129219/5FFE9818" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9818" Ref="C?"  Part="1" 
F 0 "C?" V 6100 5350 50  0000 C CNN
F 1 "470nF" V 6100 5650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 5350 50  0001 C CNN
F 3 "~" H 6150 5500 50  0001 C CNN
	1    6150 5500
	0    -1   1    0   
$EndComp
Wire Wire Line
	6000 4800 5900 4800
Wire Wire Line
	5900 4700 5900 4800
Connection ~ 5900 4700
Wire Wire Line
	6000 4700 5900 4700
Wire Wire Line
	5900 4600 5900 4700
Wire Wire Line
	6000 4600 5900 4600
Wire Wire Line
	6400 4800 6400 4700
Wire Wire Line
	6300 4800 6400 4800
Wire Wire Line
	6400 4700 6400 4600
Connection ~ 6400 4700
Wire Wire Line
	6300 4700 6400 4700
Wire Wire Line
	6300 4600 6400 4600
Connection ~ 6400 4600
$Comp
L power:+1V2 #PWR?
U 1 1 5FFE982B
P 6400 4600
AR Path="/5E1291BC/5FFE982B" Ref="#PWR?"  Part="1" 
AR Path="/5E129219/5FFE982B" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE982B" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6400 4450 50  0001 C CNN
F 1 "+1V2" H 6415 4773 50  0000 C CNN
F 2 "" H 6400 4600 50  0001 C CNN
F 3 "" H 6400 4600 50  0001 C CNN
	1    6400 4600
	-1   0    0    -1  
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE9831
P 6150 4800
AR Path="/5E1291BC/5FFE9831" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE9831" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9831" Ref="C?"  Part="1" 
F 0 "C?" V 6100 4650 50  0000 C CNN
F 1 "470nF" V 6100 4950 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 4650 50  0001 C CNN
F 3 "~" H 6150 4800 50  0001 C CNN
	1    6150 4800
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE9837
P 6150 4700
AR Path="/5E1291BC/5FFE9837" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE9837" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9837" Ref="C?"  Part="1" 
F 0 "C?" V 6100 4550 50  0000 C CNN
F 1 "470nF" V 6100 4850 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 4550 50  0001 C CNN
F 3 "~" H 6150 4700 50  0001 C CNN
	1    6150 4700
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE983D
P 6150 4600
AR Path="/5E129219/5FFE983D" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE983D" Ref="C?"  Part="1" 
F 0 "C?" V 6100 4450 50  0000 C CNN
F 1 "470nF" V 6100 4750 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 4450 50  0001 C CNN
F 3 "~" H 6150 4600 50  0001 C CNN
	1    6150 4600
	0    -1   1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FFE9843
P 5900 5700
AR Path="/5E129219/5FFE9843" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE9843" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5900 5450 50  0001 C CNN
F 1 "GND" H 5905 5527 50  0000 C CNN
F 2 "" H 5900 5700 50  0001 C CNN
F 3 "" H 5900 5700 50  0001 C CNN
	1    5900 5700
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6000 6400 5900 6400
Wire Wire Line
	6000 6300 5900 6300
Wire Wire Line
	6000 6100 5900 6100
Wire Wire Line
	6400 6400 6400 6300
Wire Wire Line
	6300 6400 6400 6400
Wire Wire Line
	6400 6300 6400 6200
Connection ~ 6400 6300
Wire Wire Line
	6300 6300 6400 6300
Wire Wire Line
	6300 6100 6400 6100
$Comp
L Device:C C?
U 1 1 5FFE9852
P 6150 6400
AR Path="/5E1291BC/5FFE9852" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE9852" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9852" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6250 50  0000 C CNN
F 1 "47uF" V 6100 6550 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 6250 50  0001 C CNN
F 3 "~" H 6150 6400 50  0001 C CNN
	1    6150 6400
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE9858
P 6150 6300
AR Path="/5E129219/5FFE9858" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9858" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6150 50  0000 C CNN
F 1 "4.7uF" V 6100 6450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 6150 50  0001 C CNN
F 3 "~" H 6150 6300 50  0001 C CNN
	1    6150 6300
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE985E
P 6150 6200
AR Path="/5E129219/5FFE985E" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE985E" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6050 50  0000 C CNN
F 1 "470nF" V 6100 6350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 6050 50  0001 C CNN
F 3 "~" H 6150 6200 50  0001 C CNN
	1    6150 6200
	0    -1   1    0   
$EndComp
Connection ~ 5900 6300
$Comp
L power:GND #PWR?
U 1 1 5FFE9865
P 5900 6400
AR Path="/5E129219/5FFE9865" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE9865" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5900 6150 50  0001 C CNN
F 1 "GND" H 5905 6227 50  0000 C CNN
F 2 "" H 5900 6400 50  0001 C CNN
F 3 "" H 5900 6400 50  0001 C CNN
	1    5900 6400
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5900 6300 5900 6400
$Comp
L power:+1V8 #PWR?
U 1 1 5FFE986C
P 6400 6100
AR Path="/5E129219/5FFE986C" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE986C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6400 5950 50  0001 C CNN
F 1 "+1V8" H 6415 6273 50  0000 C CNN
F 2 "" H 6400 6100 50  0001 C CNN
F 3 "" H 6400 6100 50  0001 C CNN
	1    6400 6100
	-1   0    0    -1  
$EndComp
Connection ~ 6400 6100
Wire Wire Line
	5900 7500 5900 7600
Wire Wire Line
	6000 7500 5900 7500
Wire Wire Line
	6300 7500 6400 7500
$Comp
L Device:C C?
U 1 1 5FFE9876
P 6150 7500
AR Path="/5E129219/5FFE9876" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE9876" Ref="C?"  Part="1" 
F 0 "C?" V 6100 7350 50  0000 C CNN
F 1 "470nF" V 6100 7650 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 7350 50  0001 C CNN
F 3 "~" H 6150 7500 50  0001 C CNN
	1    6150 7500
	0    -1   1    0   
$EndComp
$Comp
L power:+1V8 #PWR?
U 1 1 5FFE987C
P 6400 7500
AR Path="/5E129219/5FFE987C" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE987C" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6400 7350 50  0001 C CNN
F 1 "+1V8" H 6415 7673 50  0000 C CNN
F 2 "" H 6400 7500 50  0001 C CNN
F 3 "" H 6400 7500 50  0001 C CNN
	1    6400 7500
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FFE9883
P 5900 7600
AR Path="/5E129219/5FFE9883" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE9883" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5900 7350 50  0001 C CNN
F 1 "GND" H 5905 7427 50  0000 C CNN
F 2 "" H 5900 7600 50  0001 C CNN
F 3 "" H 5900 7600 50  0001 C CNN
	1    5900 7600
	-1   0    0    -1  
$EndComp
$Comp
L power:GND #PWR?
U 1 1 5FFE9889
P 6900 6200
AR Path="/5E129219/5FFE9889" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE9889" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6900 5950 50  0001 C CNN
F 1 "GND" H 6905 6027 50  0000 C CNN
F 2 "" H 6900 6200 50  0001 C CNN
F 3 "" H 6900 6200 50  0001 C CNN
	1    6900 6200
	1    0    0    -1  
$EndComp
Wire Wire Line
	7900 4900 7900 4300
Wire Wire Line
	5900 5000 5900 5100
Connection ~ 5900 5000
Wire Wire Line
	6000 5000 5900 5000
Wire Wire Line
	5900 4900 5900 5000
Connection ~ 5900 4900
Wire Wire Line
	6000 4900 5900 4900
Wire Wire Line
	5900 4800 5900 4900
$Comp
L power:GND #PWR?
U 1 1 5FFE98A6
P 5900 5100
AR Path="/5E129219/5FFE98A6" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/5FFE98A6" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5900 4850 50  0001 C CNN
F 1 "GND" H 5905 4927 50  0000 C CNN
F 2 "" H 5900 5100 50  0001 C CNN
F 3 "" H 5900 5100 50  0001 C CNN
	1    5900 5100
	-1   0    0    -1  
$EndComp
Wire Wire Line
	6400 5000 6400 4900
Wire Wire Line
	6300 5000 6400 5000
Wire Wire Line
	6400 4900 6400 4800
Connection ~ 6400 4900
Wire Wire Line
	6300 4900 6400 4900
$Comp
L Device:C C?
U 1 1 5FFE98B1
P 6150 5000
AR Path="/5E129219/5FFE98B1" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE98B1" Ref="C?"  Part="1" 
F 0 "C?" V 6100 4850 50  0000 C CNN
F 1 "4.7uF" V 6100 5150 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 4850 50  0001 C CNN
F 3 "~" H 6150 5000 50  0001 C CNN
	1    6150 5000
	0    -1   1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 5FFE98B7
P 6150 4900
AR Path="/5E129219/5FFE98B7" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE98B7" Ref="C?"  Part="1" 
F 0 "C?" V 6100 4750 50  0000 C CNN
F 1 "4.7uF" V 6100 5050 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 4750 50  0001 C CNN
F 3 "~" H 6150 4900 50  0001 C CNN
	1    6150 4900
	0    -1   1    0   
$EndComp
Connection ~ 6400 4800
Connection ~ 5900 4800
$Comp
L Device:C C?
U 1 1 5FFE98BF
P 6150 5100
AR Path="/5E1291BC/5FFE98BF" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE98BF" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE98BF" Ref="C?"  Part="1" 
F 0 "C?" V 6100 4950 50  0000 C CNN
F 1 "100uF" V 6100 5250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 4950 50  0001 C CNN
F 3 "~" H 6150 5100 50  0001 C CNN
	1    6150 5100
	0    -1   1    0   
$EndComp
Wire Wire Line
	6000 5100 5900 5100
Connection ~ 5900 5100
Wire Wire Line
	6300 5100 6400 5100
Wire Wire Line
	6400 5100 6400 5000
Connection ~ 6400 5000
Connection ~ 5900 6400
Wire Wire Line
	5900 6100 5900 6200
Wire Wire Line
	6400 6200 6400 6100
$Comp
L Device:C C?
U 1 1 5FFE98CD
P 6150 6100
AR Path="/5E129219/5FFE98CD" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE98CD" Ref="C?"  Part="1" 
F 0 "C?" V 6100 5950 50  0000 C CNN
F 1 "470nF" V 6100 6250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 6188 5950 50  0001 C CNN
F 3 "~" H 6150 6100 50  0001 C CNN
	1    6150 6100
	0    -1   1    0   
$EndComp
Wire Wire Line
	6000 6200 5900 6200
Connection ~ 5900 6200
Wire Wire Line
	5900 6200 5900 6300
Wire Wire Line
	6300 6200 6400 6200
Connection ~ 6400 6200
Connection ~ 5900 5700
$Comp
L Device:C C?
U 1 1 5FFE98DB
P 6150 7100
AR Path="/5E1291BC/5FFE98DB" Ref="C?"  Part="1" 
AR Path="/5E129219/5FFE98DB" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/5FFE98DB" Ref="C?"  Part="1" 
F 0 "C?" V 6100 6950 50  0000 C CNN
F 1 "4.7uF" V 6100 7250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6188 6950 50  0001 C CNN
F 3 "~" H 6150 7100 50  0001 C CNN
	1    6150 7100
	0    -1   1    0   
$EndComp
Wire Wire Line
	6000 7100 5900 7100
Connection ~ 5900 7100
Wire Wire Line
	6300 7100 6400 7100
Wire Wire Line
	6400 7100 6400 7000
Connection ~ 6400 7000
$Comp
L symbols:XC7S25-CSGA225 U?
U 1 1 5FFE98E7
P 8800 5700
AR Path="/5E129219/5FFE98E7" Ref="U?"  Part="1" 
AR Path="/5FEE12C8/5FFE98E7" Ref="U?"  Part="1" 
F 0 "U?" V 9450 5850 50  0000 L CNN
F 1 "XC7S25-CSGA225" V 9550 5600 50  0000 L CNN
F 2 "Package_BGA:Xilinx_CSGA225" H 8800 5700 50  0001 C CNN
F 3 "https://www.xilinx.com/support/documentation/data_sheets/ds180_7Series_Overview.pdf" H 8800 5700 50  0001 C CNN
	1    8800 5700
	0    -1   1    0   
$EndComp
Connection ~ 10700 5600
Wire Wire Line
	6400 7500 6800 7500
Wire Wire Line
	6800 7500 6800 6000
Wire Wire Line
	6800 6000 6900 6000
Connection ~ 6400 7500
Wire Wire Line
	6400 6800 6700 6800
Wire Wire Line
	6700 6800 6700 5800
Wire Wire Line
	6700 5800 6900 5800
Wire Wire Line
	6400 6100 6600 6100
Wire Wire Line
	6600 6100 6600 5600
Wire Wire Line
	6600 5600 6900 5600
Wire Wire Line
	6400 5500 6500 5500
Wire Wire Line
	6500 5500 6500 5400
Wire Wire Line
	6500 5400 6900 5400
Wire Wire Line
	6400 4600 6500 4600
Wire Wire Line
	6500 4600 6500 5200
Wire Wire Line
	6500 5200 6900 5200
Text GLabel 2100 4600 0    50   BiDi ~ 0
CRAM_DQ0
Text GLabel 2100 4700 0    50   BiDi ~ 0
CRAM_DQ1
Text GLabel 2100 4800 0    50   BiDi ~ 0
CRAM_DQ2
Text GLabel 2100 4900 0    50   BiDi ~ 0
CRAM_DQ3
Text GLabel 2100 5000 0    50   BiDi ~ 0
CRAM_DQ4
Text GLabel 2100 5100 0    50   BiDi ~ 0
CRAM_DQ5
Text GLabel 2100 5200 0    50   BiDi ~ 0
CRAM_DQ6
Text GLabel 2100 5300 0    50   BiDi ~ 0
CRAM_DQ7
Text GLabel 2100 5400 0    50   BiDi ~ 0
CRAM_DQ8
Text GLabel 2100 5500 0    50   BiDi ~ 0
CRAM_DQ9
Text GLabel 2100 5600 0    50   BiDi ~ 0
CRAM_DQ10
Text GLabel 2100 5700 0    50   BiDi ~ 0
CRAM_DQ11
Text GLabel 2100 5800 0    50   BiDi ~ 0
CRAM_DQ12
Text GLabel 2100 5900 0    50   BiDi ~ 0
CRAM_DQ13
Text GLabel 2100 6000 0    50   BiDi ~ 0
CRAM_DQ14
Text GLabel 2100 6100 0    50   BiDi ~ 0
CRAM_DQ15
Text GLabel 2100 6200 0    50   Output ~ 0
CRAM_LBN
Text GLabel 2100 6300 0    50   Output ~ 0
CRAM_UBN
Text GLabel 2100 6400 0    50   Output ~ 0
CRAM_OEN
Text GLabel 2100 6500 0    50   Output ~ 0
CRAM_CEN
Text GLabel 2100 6700 0    50   Output ~ 0
CRAM_CRE
Text GLabel 2100 6600 0    50   Output ~ 0
CRAM_WEN
Text GLabel 2100 6900 0    50   Output ~ 0
CRAM_CLK
Text GLabel 2100 7000 0    50   Output ~ 0
CRAM_ADVN
Text GLabel 2100 6800 0    50   Input ~ 0
CRAM_WAIT
Text GLabel 4900 4600 2    50   Output ~ 0
CRAM_A0
Text GLabel 4900 4700 2    50   Output ~ 0
CRAM_A1
Text GLabel 4900 4800 2    50   Output ~ 0
CRAM_A2
Text GLabel 4900 4900 2    50   Output ~ 0
CRAM_A3
Text GLabel 4900 5000 2    50   Output ~ 0
CRAM_A4
Text GLabel 4900 5100 2    50   Output ~ 0
CRAM_A5
Text GLabel 4900 5200 2    50   Output ~ 0
CRAM_A6
Text GLabel 4900 5300 2    50   Output ~ 0
CRAM_A7
Text GLabel 4900 5400 2    50   Output ~ 0
CRAM_A8
Text GLabel 4900 5500 2    50   Output ~ 0
CRAM_A9
Text GLabel 4900 5600 2    50   Output ~ 0
CRAM_A10
Text GLabel 4900 5700 2    50   Output ~ 0
CRAM_A11
Text GLabel 4900 5800 2    50   Output ~ 0
CRAM_A12
Text GLabel 4900 5900 2    50   Output ~ 0
CRAM_A13
Text GLabel 4900 6000 2    50   Output ~ 0
CRAM_A14
Text GLabel 4900 6100 2    50   Output ~ 0
CRAM_A15
Text GLabel 4900 6200 2    50   Output ~ 0
CRAM_A16
Text GLabel 4900 6300 2    50   Output ~ 0
CRAM_A17
Text GLabel 4900 6400 2    50   Output ~ 0
CRAM_A18
Text GLabel 4900 6500 2    50   Output ~ 0
CRAM_A19
Text GLabel 4900 6600 2    50   Output ~ 0
CRAM_A20
Text GLabel 4900 6700 2    50   Output ~ 0
CRAM_A21
$Comp
L Device:C C?
U 1 1 604A431B
P 5450 4100
AR Path="/5E1291BC/604A431B" Ref="C?"  Part="1" 
AR Path="/5E129219/604A431B" Ref="C?"  Part="1" 
AR Path="/5E129265/604A431B" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/604A431B" Ref="C?"  Part="1" 
F 0 "C?" V 5400 3950 50  0000 C CNN
F 1 "470nF" V 5400 4250 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5488 3950 50  0001 C CNN
F 3 "~" H 5450 4100 50  0001 C CNN
	1    5450 4100
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 604A4321
P 5450 4200
AR Path="/5E1291BC/604A4321" Ref="C?"  Part="1" 
AR Path="/5E129219/604A4321" Ref="C?"  Part="1" 
AR Path="/5E129265/604A4321" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/604A4321" Ref="C?"  Part="1" 
F 0 "C?" V 5400 4050 50  0000 C CNN
F 1 "470nF" V 5400 4350 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" H 5488 4050 50  0001 C CNN
F 3 "~" H 5450 4200 50  0001 C CNN
	1    5450 4200
	0    1    1    0   
$EndComp
$Comp
L Device:C C?
U 1 1 604A4327
P 5450 4300
AR Path="/5E1291BC/604A4327" Ref="C?"  Part="1" 
AR Path="/5E129219/604A4327" Ref="C?"  Part="1" 
AR Path="/5E129265/604A4327" Ref="C?"  Part="1" 
AR Path="/5FEE12C8/604A4327" Ref="C?"  Part="1" 
F 0 "C?" V 5400 4150 50  0000 C CNN
F 1 "4.7uF" V 5400 4450 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5488 4150 50  0001 C CNN
F 3 "~" H 5450 4300 50  0001 C CNN
	1    5450 4300
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 604A432D
P 5700 4400
AR Path="/5E129219/604A432D" Ref="#PWR?"  Part="1" 
AR Path="/5E129265/604A432D" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/604A432D" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5700 4150 50  0001 C CNN
F 1 "GND" H 5705 4227 50  0000 C CNN
F 2 "" H 5700 4400 50  0001 C CNN
F 3 "" H 5700 4400 50  0001 C CNN
	1    5700 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 4100 5700 4100
Wire Wire Line
	5700 4100 5700 4200
Wire Wire Line
	5600 4200 5700 4200
Connection ~ 5700 4200
Wire Wire Line
	5700 4200 5700 4300
Wire Wire Line
	5600 4300 5700 4300
Connection ~ 5700 4300
Wire Wire Line
	5700 4300 5700 4400
Wire Wire Line
	5300 4300 5200 4300
Wire Wire Line
	5200 4100 5300 4100
Wire Wire Line
	5300 4200 5200 4200
Wire Wire Line
	5200 4300 5200 4200
Connection ~ 5200 4200
Wire Wire Line
	5200 4200 5200 4100
Connection ~ 5200 4100
$Comp
L power:+1V8 #PWR?
U 1 1 604A4342
P 5200 4100
AR Path="/5E129265/604A4342" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/604A4342" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 5200 3950 50  0001 C CNN
F 1 "+1V8" H 5215 4273 50  0000 C CNN
F 2 "" H 5200 4100 50  0001 C CNN
F 3 "" H 5200 4100 50  0001 C CNN
	1    5200 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3500 4300 5200 4300
Connection ~ 5200 4300
$Comp
L Device:R R?
U 1 1 604C45A1
P 1300 1300
AR Path="/5E129219/604C45A1" Ref="R?"  Part="1" 
AR Path="/5E129265/604C45A1" Ref="R?"  Part="1" 
F 0 "R?" V 1350 1500 50  0000 C CNN
F 1 "2.2K" V 1350 1100 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" V 1230 1300 50  0001 C CNN
F 3 "~" H 1300 1300 50  0001 C CNN
	1    1300 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	1450 1300 1550 1300
$Comp
L power:GND #PWR?
U 1 1 604C45A8
P 1050 1300
AR Path="/5E129219/604C45A8" Ref="#PWR?"  Part="1" 
AR Path="/5E129265/604C45A8" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 1050 1050 50  0001 C CNN
F 1 "GND" V 1055 1172 50  0000 R CNN
F 2 "" H 1050 1300 50  0001 C CNN
F 3 "" H 1050 1300 50  0001 C CNN
	1    1050 1300
	0    1    1    0   
$EndComp
Wire Wire Line
	1150 1300 1050 1300
Text GLabel 6000 2800 0    50   Input ~ 0
LCD_TE
Text GLabel 1300 3400 0    50   Output ~ 0
FPGA_BCLK
Text GLabel 1300 3500 0    50   Output ~ 0
FPGA_MCLK
Text GLabel 1300 3600 0    50   Output ~ 0
FPGA_DOUT
Text GLabel 1300 3700 0    50   Output ~ 0
FPGA_LRCK
NoConn ~ 300  3200
NoConn ~ 300  2300
Text GLabel 6000 2300 0    50   Output ~ 0
LCD_D0
Text GLabel 6000 2700 0    50   Output ~ 0
LCD_D1
Text GLabel 6000 2200 0    50   Output ~ 0
LCD_D2
Text GLabel 6000 3000 0    50   Output ~ 0
LCD_D3
Text GLabel 6000 1800 0    50   Output ~ 0
LCD_D4
Text GLabel 6000 1400 0    50   Output ~ 0
LCD_D6
Text GLabel 1300 3200 0    50   Output ~ 0
LCD_D7
Text GLabel 1300 3100 0    50   Output ~ 0
LCD_D8
Text GLabel 1300 3000 0    50   Output ~ 0
LCD_D9
Text GLabel 6000 1900 0    50   Output ~ 0
LCD_D10
Text GLabel 1300 2800 0    50   Output ~ 0
LCD_D11
Text GLabel 1300 2700 0    50   Output ~ 0
LCD_D12
Text GLabel 1300 2400 0    50   Output ~ 0
LCD_D13
Text GLabel 1300 1900 0    50   Output ~ 0
LCD_D14
Text GLabel 1300 2000 0    50   Output ~ 0
LCD_D15
Text GLabel 1300 1500 0    50   Output ~ 0
LCD_D16
Text GLabel 1300 1600 0    50   Output ~ 0
LCD_D17
Text GLabel 6000 2000 0    50   Output ~ 0
LCD_PCLK
Text GLabel 6000 2900 0    50   Output ~ 0
LCD_DE
Text GLabel 6000 2400 0    50   Output ~ 0
LCD_HS
Text GLabel 6000 2100 0    50   Output ~ 0
LCD_D5
Text GLabel 6000 1700 0    50   Output ~ 0
LCD_CLK
Text GLabel 6000 2600 0    50   Output ~ 0
LCD_VS
Text GLabel 6000 3300 0    50   Input ~ 0
MCU_SCLK
Text GLabel 6000 3400 0    50   Input ~ 0
MCU_CS
Text GLabel 6000 3500 0    50   BiDi ~ 0
MCU_D0
Text GLabel 6000 3600 0    50   BiDi ~ 0
MCU_D1
Text GLabel 6000 3700 0    50   BiDi ~ 0
MCU_D2
Text GLabel 6000 3800 0    50   BiDi ~ 0
MCU_D3
$Comp
L Device:R R?
U 1 1 605158AD
P 7150 4400
AR Path="/5E129219/605158AD" Ref="R?"  Part="1" 
AR Path="/5FEE12C8/605158AD" Ref="R?"  Part="1" 
F 0 "R?" V 7100 4200 50  0000 C CNN
F 1 "10K" V 7100 4600 50  0000 C CNN
F 2 "Capacitor_SMD:C_0402_1005Metric" V 7080 4400 50  0001 C CNN
F 3 "~" H 7150 4400 50  0001 C CNN
	1    7150 4400
	0    1    1    0   
$EndComp
$Comp
L power:+3V3 #PWR?
U 1 1 605158B3
P 6900 4600
AR Path="/5E129219/605158B3" Ref="#PWR?"  Part="1" 
AR Path="/5FEE12C8/605158B3" Ref="#PWR?"  Part="1" 
F 0 "#PWR?" H 6900 4450 50  0001 C CNN
F 1 "+3V3" V 6915 4728 50  0000 L CNN
F 2 "" H 6900 4600 50  0001 C CNN
F 3 "" H 6900 4600 50  0001 C CNN
	1    6900 4600
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6900 4600 7000 4600
Wire Wire Line
	8100 4300 8100 4600
Wire Wire Line
	7300 4400 7800 4400
Wire Wire Line
	7800 4400 7800 4900
Wire Wire Line
	7300 4600 8100 4600
Connection ~ 8100 4600
Wire Wire Line
	8100 4600 8100 4900
Wire Wire Line
	7800 4300 7800 4400
Connection ~ 7800 4400
Text Label 7800 4800 1    50   ~ 0
CFGBVS
$EndSCHEMATC
