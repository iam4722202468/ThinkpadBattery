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
L Device:R R2
U 1 1 5EC31CEC
P 4600 2500
F 0 "R2" H 4670 2546 50  0000 L CNN
F 1 "9.1K" H 4670 2455 50  0000 L CNN
F 2 "Parts:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4530 2500 50  0001 C CNN
F 3 "~" H 4600 2500 50  0001 C CNN
	1    4600 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5EC30F8F
P 4300 2500
F 0 "R1" H 4370 2546 50  0000 L CNN
F 1 "3K" H 4370 2455 50  0000 L CNN
F 2 "Parts:R_1206_3216Metric_Pad1.42x1.75mm_HandSolder" V 4230 2500 50  0001 C CNN
F 3 "~" H 4300 2500 50  0001 C CNN
	1    4300 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5EC353CA
P 4450 3250
F 0 "#PWR0101" H 4450 3000 50  0001 C CNN
F 1 "GND" H 4455 3077 50  0000 C CNN
F 2 "" H 4450 3250 50  0001 C CNN
F 3 "" H 4450 3250 50  0001 C CNN
	1    4450 3250
	-1   0    0    1   
$EndComp
$Comp
L Connector:Conn_01x07_Male J1
U 1 1 5EC62E55
P 3100 3550
F 0 "J1" V 3027 3528 50  0000 C CNN
F 1 "Conn_01x07_Male" V 2936 3528 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x07_P2.54mm_Vertical" H 3100 3550 50  0001 C CNN
F 3 "~" H 3100 3550 50  0001 C CNN
	1    3100 3550
	0    -1   -1   0   
$EndComp
Text GLabel 2800 3350 1    50   Input ~ 0
12v
Text GLabel 2900 3350 1    50   Input ~ 0
12v
Text GLabel 3000 3350 1    50   Input ~ 0
SCL
Text GLabel 3100 3350 1    50   Input ~ 0
SDA
Text GLabel 3200 3350 1    50   Input ~ 0
T
Text GLabel 3300 3350 1    50   Input ~ 0
GND
Text GLabel 3400 3350 1    50   Input ~ 0
GND
$Comp
L Regulator_Linear:LD1117S33TR_SOT223 U2
U 1 1 5EC32906
P 4500 1650
F 0 "U2" H 4500 1892 50  0000 C CNN
F 1 "LD1117S33TR_SOT223" H 4500 1801 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 4500 1850 50  0001 C CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00000544.pdf" H 4600 1400 50  0001 C CNN
	1    4500 1650
	-1   0    0    1   
$EndComp
$Comp
L power:+12V #PWR0102
U 1 1 5EC34276
P 4050 3250
F 0 "#PWR0102" H 4050 3100 50  0001 C CNN
F 1 "+12V" H 4065 3423 50  0000 C CNN
F 2 "" H 4050 3250 50  0001 C CNN
F 3 "" H 4050 3250 50  0001 C CNN
	1    4050 3250
	1    0    0    -1  
$EndComp
Text GLabel 4050 3250 2    50   Input ~ 0
12v
Text GLabel 4450 3250 2    50   Input ~ 0
GND
Text GLabel 4800 1650 2    50   Input ~ 0
12v
Text GLabel 4200 1650 0    50   Input ~ 0
3.3v
Text GLabel 4500 1350 0    50   Input ~ 0
GND
Text GLabel 4600 2350 1    50   Input ~ 0
12v
Wire Wire Line
	4600 2650 4300 2650
Text GLabel 4300 2350 1    50   Input ~ 0
GND
Text GLabel 4300 2650 0    50   Input ~ 0
VBatSensor
Text GLabel 2800 2350 3    50   Input ~ 0
VBatSensor
Text GLabel 2200 1750 0    50   Input ~ 0
GND
Text GLabel 3400 1750 2    50   Input ~ 0
3.3v
Text GLabel 3000 2350 3    50   Input ~ 0
CurrentSensor
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20SU U1
U 1 1 5EC2F108
P 2800 1750
F 0 "U1" H 2271 1796 50  0000 R CNN
F 1 "ATtiny85-20SU" H 2271 1705 50  0000 R CNN
F 2 "Package_SO:SOIJ-8_5.3x5.3mm_P1.27mm" H 2800 1750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 2800 1750 50  0001 C CNN
	1    2800 1750
	0    1    1    0   
$EndComp
Text GLabel 2700 2350 3    50   Input ~ 0
T
Text GLabel 2900 2350 3    50   Input ~ 0
SCL
Text GLabel 3100 2350 3    50   Input ~ 0
SDA
$Comp
L Connector:Conn_01x01_Male J2
U 1 1 5ECDB575
P 4050 3450
F 0 "J2" H 4158 3631 50  0000 C CNN
F 1 "Conn_01x01_Male" H 4158 3540 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 4050 3450 50  0001 C CNN
F 3 "~" H 4050 3450 50  0001 C CNN
	1    4050 3450
	0    -1   -1   0   
$EndComp
$Comp
L Connector:Conn_01x01_Male J3
U 1 1 5ECDC6DD
P 4450 3450
F 0 "J3" H 4558 3631 50  0000 C CNN
F 1 "Conn_01x01_Male" H 4558 3540 50  0000 C CNN
F 2 "Connector_Pin:Pin_D1.4mm_L8.5mm_W2.8mm_FlatFork" H 4450 3450 50  0001 C CNN
F 3 "~" H 4450 3450 50  0001 C CNN
	1    4450 3450
	0    -1   -1   0   
$EndComp
$EndSCHEMATC
