#ifndef _SENSOR_IR_
#define _SENSOR_IR_

/*==================[inclusiones]=============================================*/
#include "sapi.h"

/*==================[definiciones]============================================*/
typedef enum {
  SENSOR_IR_IZQ,
  SENSOR_IR_DER,
  SENSOR_IR_CANT
} sensores_ir_t;

/*==================[protitipos]==============================================*/
void iniSensoresIR(void);

void prenderSensoresIR(void);
void apagarSensoresIR(void);

void actualizarSensoresIR(void);
uint16_t leerSensorIR(uint8_t indice);

#endif /* _SENSOR_IR_ */

