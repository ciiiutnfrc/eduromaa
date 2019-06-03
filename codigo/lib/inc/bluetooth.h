#ifndef	_BLUETOOTH_H
#define _BLUETOOTH_H
/*==================[inclusiones]=============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[definiciones]=================================================*/


/* Definiciones para uso de control remoto */
#define	BT_AVANZAR			'F'			/* Caracteres configurados para aplicación */
#define	BT_RETROCEDER		'G'			/* Arduino Car */
#define	BT_GIRAR_IZQ		'L'
#define	BT_GIRAR_DER		'R'
#define	BT_DETENER			'S'

/* Definiciones para uso de consola */
#define CMD_INIT_COM		      '*'      // init comunicacion
#define CMD_RESET_ALL   	      'r'      // reset all
#define CMD_ENABLE_MOTOR          'h'       // habilita las llaves H
#define CMD_DISABLE_MOTOR         'H'       // deshabilita las llaves H
#define CMD_SET_PWM               'p'       // set motor PWM (in open loop)
#define CMD_GET_PWM               'P'       // get motor PWM
#define CMD_RUEDA_DER			  'd'		//Rueda Derecha
#define CMD_RUEDA_IZQ			  'i'		//Rueda Izquierda


/* Prototipos de funciones */

void iniBT(void);
void prenderBT(void);
void apagarBT(void);

bool_t 	leerBT(uint8_t *dato);

#endif

/*==================[end of file]============================================*/
