/*
 * ir_linea.c
 *
 *  Created on: 14 jul. 2019
 *      Author: marti
 */

/*==================[inclusiones]============================================*/
#include "ir_linea.h"



/*==================[definiciones]===========================================*/

sensor_linea_t ir_izq = {0, LINEA_UMBRAL, LINEA_HISTERESIS, LINEA_NEGRO, SENSOR_IR_IZQ};
sensor_linea_t ir_der = {0, LINEA_UMBRAL, LINEA_HISTERESIS, LINEA_NEGRO, SENSOR_IR_DER};

/*==================[implementaciones]=======================================*/



bool_t actualizar_estado_linea(sensor_linea_t *sensor){
    sensor->valor = leerSensorIR(sensor->canal);

    if(sensor->estado == LINEA_NEGRO){            // Último estado NEGRO
        if(sensor->valor < (sensor->umbral - sensor->histeresis /2)){
            sensor->estado = LINEA_BLANCO;
        }
    }
    else{                                           // Último estado BLANCO
        if(sensor->valor > (sensor->umbral + sensor->histeresis /2)){
            sensor->estado = LINEA_NEGRO;
        }
    }
    return sensor->estado;
}

bool_t leer_sensor_ir(uint8_t ir_sensor_id){
    bool_t resultado = FALSE;
    switch (ir_sensor_id){              // Se utiliza un switch case por si se quieren agregar más sensores
        case LINEA_ID_IZQUIERDA:
            actualizar_estado_linea(&ir_izq);
            resultado = ir_izq.estado;
            break;
        case LINEA_ID_DERECHA:
            actualizar_estado_linea(&ir_der);
            resultado = ir_der.estado;
            break;
        default:
            break;
    }
    return resultado;
}

uint8_t seguir_linea(void){
    uint8_t accion = LINEA_DETENER;

    actualizarSensoresIR();

    if(actualizar_estado_linea(&ir_izq) == LINEA_COLOR){
        accion += LINEA_GIRAR_IZQ;
    }
    if(actualizar_estado_linea(&ir_der) == LINEA_COLOR){
        accion += LINEA_GIRAR_DER;
    }
    return accion;
}



