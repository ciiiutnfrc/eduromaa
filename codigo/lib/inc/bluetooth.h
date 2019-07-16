#ifndef	_BLUETOOTH_H
#define _BLUETOOTH_H
/*==================[inclusiones]============================================*/

#include "sapi.h"         /* <= sAPI header */

/*==================[definiciones]===========================================*/

/* Definiciones para uso de control remoto */
#define	BT_AVANZAR		'F'	/* Caracteres configurados para aplicación */
#define BT_AV_IZQ       'Q' /* Arduino Car */
#define BT_AV_DER       'E'
#define	BT_RETROCEDER	'G'
#define BT_RET_IZQ      'Z'
#define BT_RET_DER      'C'
#define	BT_GIRAR_IZQ	'L'
#define	BT_GIRAR_DER	'R'
#define	BT_DETENER		'S'
#define BT_X            'X'
#define BT_Y            'Y'
#define BT_LUZ_ON       'M'
#define BT_LUZ_OFF      'm'
#define BT_RANGO1       'J'
#define BT_RANGO2       'K'


/*==================[protitipos]==============================================*/

void iniBT(void);
void prenderBT(void);
void apagarBT(void);

bool_t recibirBT(uint8_t *dato);
bool_t transmitirBT(const char* str);

#endif

/*==================[end of file]============================================*/
