# Conexión con EduCIAA

En la siguiente tabla se muestra el conexionado de los componentes del robot con la placa EduCIAA.


|  # |      Componentes       | EduCIAA  | Pin | SCU Port_Pin | FUNC  |  Periférico   |
|:--:|:----------------------:|:--------:|:---:|:------------:|:-----:|:-------------:|
| 1  | Bocina                 | T_COL1   | 132 | P7_4         | FUNC0 | GPIO3[12]     |
| 2  | Paragolpe izq.         | CRS_DV   | 64  | P1_16        | FUNC0 | GPIO0[3]      |
| 3  | Paragolpe der.         | RXD0     | 62  | P1_15        | FUNC0 | GPIO0[2]      |
| 4  | Habilitación motores   | T_FIL0   | 1   | P4_0         | FUNC0 | GPIO2[0]      |
| 5  | PWM motor izq.         | T_FIL3   | 7   | P4_3         | FUNC1 | CTOUT_3       |
| 6  | PWM motor der.         | T_FIL2   | 8   | P4_2         | FUNC1 | CTOUT_0       |
| 7  | On/Off tacómetro       | TXD0     | 67  | P1_18        | FUNC0 | GPIO0[13]     |
| 8  | Tacómetro izq.         | MDIO     | 66  | P1_17        | FUNC4 | T0_CAP3       |
| 9  | Tacómetro der.         | TXD1     | 70  | P1_20        | FUNC4 | T0_CAP2       |
| 10 | On/Off Detector línea  | CAN_TD   | 116 | P3_2         | FUNC4 | GPIO5[9]      |
| 11 | Detector línea izq.    | CH2      | 143 | ---          | ---   | ADC0_2/ADC1_2 |
| 12 | Detector línea der.    | CH1      | 2   | ---          | ---   | ADC0_1/ADC1_1 |
| 13 | On/Off Bluetooth       | CAN_RD   | 114 | P3_1         | FUNC4 | GPIO5[8]      |
| 14 | Bluetooth Tx           | RS232_TX | 87  | P2_3         | FUNC2 | U3_TXD        |
| 15 | Bluetooth Rx           | RS232_RX | 88  | P2_4         | FUNC2 | U3_RXD        |
| 16 | On/Off sonar           | GPIO4    | 86  | P6_8         | FUNC4 | GPIO5[16]     |
| 17 | Sonar trigger          | GPIO0    | 74  | P6_1         | FUNC0 | GPIO3[0]      |
| 18 | Sonar echo             | GPIO2    | 82  | P6_5         | FUNC0 | GPIO3[4]      |

