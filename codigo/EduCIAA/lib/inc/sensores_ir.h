#ifndef SENSOR_IR_
#define SENSOR_IR_

/*==================[inclusiones]============================================*/
#include "sapi.h"

/*==================[definiciones]===========================================*/

typedef enum
{
  SENSOR_IR_IZQ, SENSOR_IR_DER, SENSOR_IR_CANT
} sensores_ir_t;

/*----------------------- Opciones configurables ----------------------------*/
/* Umbral promedio: se debe ajustar de acuerdo al comportamiento de los i
 * sensores */
#define LINEA_UMBRAL        200

/* Histéresis: Idem anterior */
#define LINEA_HISTERESIS    400

/* Valor lógico para el material reflectivo (depende del diseño de hardware) */
#define LINEA_BLANCO        TRUE

/* Valor lógico para el material opaco (depende del diseño de hardware) */
#define LINEA_NEGRO         FALSE

/* Color de la línea que se desea seguir */
#define LINEA_COLOR         LINEA_NEGRO

/*===========================================================================*/

#define LINEA_IZQ_DER_OK    3
#define LINEA_IZQ_OK        2
#define LINEA_DER_OK        1
#define LINEA_DETENER       0

typedef struct {
  uint16_t valor;
  uint16_t umbral;
  uint16_t histeresis;
  bool_t estado;
  adcMap_t canal;
} sensor_linea_t;

/*==================[protitipos]==============================================*/

void iniSensoresIR(void);

void prenderSensoresIR(void);
void apagarSensoresIR(void);

void actualizarSensoresIR(void);
uint16_t leerSensorIR(uint8_t indice);

uint8_t seguir_linea(void);
bool_t actualizar_estado_linea(sensor_linea_t *sensor);

#endif /* SENSOR_IR_ */

