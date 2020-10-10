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
F 1 "10K" H 4670 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4530 2500 50  0001 C CNN
F 3 "~" H 4600 2500 50  0001 C CNN
	1    4600 2500
	1    0    0    -1  
$EndComp
$Comp
L Device:R R1
U 1 1 5EC30F8F
P 4300 2500
F 0 "R1" H 4370 2546 50  0000 L CNN
F 1 "3.3K" H 4370 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4230 2500 50  0001 C CNN
F 3 "~" H 4300 2500 50  0001 C CNN
	1    4300 2500
	1    0    0    -1  
$EndComp
Text GLabel 3900 3450 1    50   Input ~ 0
12v
Text GLabel 4400 3450 1    50   Input ~ 0
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
T_C
Text GLabel 2900 2350 3    50   Input ~ 0
SCL
Text GLabel 3100 2350 3    50   Input ~ 0
SDA
$Comp
L Device:R R4
U 1 1 5F803F9D
P 5300 2500
F 0 "R4" H 5370 2546 50  0000 L CNN
F 1 "10k" H 5370 2455 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 5230 2500 50  0001 C CNN
F 3 "~" H 5300 2500 50  0001 C CNN
	1    5300 2500
	1    0    0    -1  
$EndComp
Text GLabel 2600 2350 3    50   Input ~ 0
R
Text GLabel 5300 2650 3    50   Input ~ 0
R
Text GLabel 5300 2350 1    50   Input ~ 0
3.3v
$Comp
L Device:R C1
U 1 1 5F8051D0
P 3700 2250
F 0 "C1" H 3770 2296 50  0000 L CNN
F 1 "22uF" H 3770 2205 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" V 3630 2250 50  0001 C CNN
F 3 "~" H 3700 2250 50  0001 C CNN
	1    3700 2250
	1    0    0    -1  
$EndComp
Text GLabel 3700 2100 1    50   Input ~ 0
3.3v
Text GLabel 3700 2400 3    50   Input ~ 0
GND
Text GLabel 4200 3450 1    50   Input ~ 0
T
$Comp
L Device:R R3
U 1 1 5F813E79
P 4950 2950
F 0 "R3" H 5020 2996 50  0000 L CNN
F 1 "10k" H 5020 2905 50  0000 L CNN
F 2 "Resistor_SMD:R_0402_1005Metric" V 4880 2950 50  0001 C CNN
F 3 "~" H 4950 2950 50  0001 C CNN
	1    4950 2950
	1    0    0    -1  
$EndComp
Text GLabel 4950 3100 3    50   Input ~ 0
T
Text GLabel 4950 2800 1    50   Input ~ 0
T_C
$Comp
L Connector:Conn_01x06_Male J1
U 1 1 5F8168A9
P 4100 3650
F 0 "J1" V 4254 3262 50  0000 R CNN
F 1 "Conn_01x06_Male" V 4163 3262 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Horizontal" H 4100 3650 50  0001 C CNN
F 3 "~" H 4100 3650 50  0001 C CNN
	1    4100 3650
	0    -1   -1   0   
$EndComp
Text GLabel 4300 3450 1    50   Input ~ 0
CurrentSensor
Text GLabel 4100 3450 1    50   Input ~ 0
SCL
Text GLabel 4000 3450 1    50   Input ~ 0
SDA
$Comp
L Device:R C2
U 1 1 5F823DED
P 5500 1650
F 0 "C2" H 5570 1696 50  0000 L CNN
F 1 "22uF" H 5570 1605 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric" V 5430 1650 50  0001 C CNN
F 3 "~" H 5500 1650 50  0001 C CNN
	1    5500 1650
	1    0    0    -1  
$EndComp
Text GLabel 5500 1500 1    50   Input ~ 0
12v
Text GLabel 5500 1800 3    50   Input ~ 0
GND
$Comp
L Connector:Conn_01x02_Male J2
U 1 1 5F81605B
P 3000 3700
F 0 "J2" V 3154 3512 50  0000 R CNN
F 1 "Conn_01x02_Male" V 3063 3512 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 3000 3700 50  0001 C CNN
F 3 "~" H 3000 3700 50  0001 C CNN
	1    3000 3700
	0    -1   -1   0   
$EndComp
Text GLabel 3000 3500 1    50   Input ~ 0
3.3v
Text GLabel 3100 3500 1    50   Input ~ 0
GND
$EndSCHEMATC
