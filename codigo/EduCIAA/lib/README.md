# Robot EduRoMAA-CIAA

Capa de bajo nivel utilizando librería sAPI

## Asignacion de pines

* Buzzer: 1 salida PWM o GPIO
	* T_COL1: BUZZER	- P7_4 - FUNC1 - CTOUT13  - PWM5 de sAPI


* Motores por Puente H (motores.h): 2 salidas PWM y 1 salida digital
	* T_FIL0: MOTOR_ENABLE 	- P4_0 - FUNC0 - GPIO2[0]
	* T_FIL2: PWM_DER		- P4_2 - FUNC1 - CTOUT0 - PWM3 de sAPI
	* T_FIL3: PWM_IZQ		- P4_3 - FUNC1 - CTOUT3 - PWM4 de sAPI

     
* Detector de líneas Infrarrojos (ir_linea.h): 2 entradas analógicas y 1 salida
digital
    * CH1: 		IR_DER -	  - FUNC0 - ADC0_1 
    * CH2: 		IR_IZQ - 	  - FUNC0 - ADC0_2
    * CAN_TD:	IR_H   - P3_2 - FUNC4 - GPIO5[9]
    
    
* Paragolpes (paragolpes.h): 2 entradas digitales con EINT
    * ENET_RXD0: 	PARAGOLPES_IZQ - P1_15 - FUNC0 - GPIO0[2] - PININT3
    * ENET_CRS_DV: 	PARAGOLPES_DER - P1_16 - FUNC0 - GPIO0[3] - PININT4


* Sonar (sonar.h): 2 salidas digitales y 1 entrada digital con EINT 
    * GPIO0: ULTRASONIC_SENSOR_TRIGGER_GPIO - P6_1 - FUNC0 - GPIO3[0] 
    * GPIO2: ULTRASONIC_SENSOR_0            - P6_5 - FUNC0 - GPIO3[4] - PININT0
    * GPIO4: SONAR_H                        - P6_8 - FUNC4 - GPIO5[16]


* Encoders IR (encoders.h): 2 entradas digitales (en modo captura de eventos)
  y una salida digital
    * ENET_TXD1: ENC_IZQ - P1_20 - FUNC4 - T0_CAP2	
    * ENET_MDIO: ENC_DER - P1_17 - FUNC4 - T0_CAP3	
    * ENET_TXD0: ENC_H   - P1_18 - FUNC0 - GPIO0[13]
 

* Bluetooth (bluetooth.h): 2 pines de UART_232 y 1 salida digital
    * RS232_TXD: BT_TX - P2_3 - FUNC2 - U3_TXD - UART_232 de sAPI
    * RS232_RXD: BT_RX - P2_4 - FUNC2 - UR_RXD - UART_232 de sAPI
    * CAN_RD:    BT_H  - P3_1 - FUNC4 - GPIO5[8]



