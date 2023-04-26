/*
 * ir_linea.h
 *
 *  Created on: 14 jul. 2019
 *      Author: marti
 */

#ifndef IR_LINEA_H_
#define IR_LINEA_H_

/*==================[inclusiones]============================================*/
#include "sapi.h"              // Librerías sAPI, las vamos a usar en todos los proyectos
#include "sensores_ir.h"


/*==================[definiciones]===========================================*/

/*----------------------- Opciones configurables ------------------------------*/

#define LINEA_UMBRAL        200              // Umbral promedio: se debe ajustar de acuerdo al comportamiento de los sensores
#define LINEA_HISTERESIS    50              // Histéresis: Idem anterior
#define LINEA_BLANCO        TRUE            // Valor lógico para el material reflectivo (depende del diseño de hardware)
#define LINEA_NEGRO         FALSE           // Valor lógico para el material opaco (depende del diseño de hardware)
#define LINEA_COLOR         LINEA_NEGRO     // Color de la línea que se desea seguir

/*=============================================================================*/

#define LINEA_ID_IZQUIERDA  1
#define LINEA_ID_DERECHA    2

#define LINEA_ADELANTE      3
#define LINEA_GIRAR_IZQ     2
#define LINEA_GIRAR_DER     1
#define LINEA_DETENER       0

typedef struct
{
    uint16_t valor;
    uint16_t umbral;
    uint16_t histeresis;
    bool_t estado;
    adcMap_t canal;
}sensor_linea_t;


/*==================[protitipos]=============================================*/

uint8_t seguir_linea(void);
bool_t actualizar_estado_linea(sensor_linea_t *sensor);



#endif /* IR_LINEA_H_ */
