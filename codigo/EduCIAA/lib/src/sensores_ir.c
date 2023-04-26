/*==================[inclusiones]============================================*/
#include "sensores_ir.h"

/*==================[definiciones]===========================================*/
#define SENSORES_IR_H CAN_TD
#define SENSORES_IR_OFF OFF
#define SENSORES_IR_ON ON

#define SENSOR_IR_CH_IZQ CH1
#define SENSOR_IR_CH_DER CH2

sensor_linea_t ir_izq = {0, LINEA_UMBRAL, LINEA_HISTERESIS,
  LINEA_NEGRO, SENSOR_IR_IZQ};
sensor_linea_t ir_der = {0, LINEA_UMBRAL, LINEA_HISTERESIS,
  LINEA_NEGRO, SENSOR_IR_DER};

uint16_t sensores_ir[SENSOR_IR_CANT];

/*==================[implementacion]=========================================*/

void iniSensoresIR(void)
{
  adcConfig(ADC_ENABLE);

  /* Configuración del GPIO prender/apagar */
  gpioConfig(SENSORES_IR_H, GPIO_ENABLE);
  gpioConfig(SENSORES_IR_H, GPIO_OUTPUT);

  /* Apaga Sensores IR */
  gpioWrite(SENSORES_IR_H, SENSORES_IR_OFF);
}

void prenderSensoresIR(void)
{
  gpioWrite(SENSORES_IR_H, SENSORES_IR_ON);
}

void apagarSensoresIR(void)
{
  gpioWrite(SENSORES_IR_H, SENSORES_IR_OFF);
}

void actualizarSensoresIR(void)
{
  sensores_ir[SENSOR_IR_IZQ] = adcRead(SENSOR_IR_CH_IZQ);
  sensores_ir[SENSOR_IR_DER] = adcRead(SENSOR_IR_CH_DER);
}

uint16_t leerSensorIR(uint8_t indice)
{
  return sensores_ir[indice];
}

bool_t actualizar_estado_linea(sensor_linea_t *sensor)
{
  actualizarSensoresIR();

  sensor->valor = leerSensorIR(sensor->canal);

  if(sensor->estado == LINEA_NEGRO){     /* Último estado NEGRO */
    if(sensor->valor < sensor->umbral){
      sensor->estado = LINEA_BLANCO;
    }
  }
  else{                                  /* Último estado BLANCO */
    if(sensor->valor > (sensor->umbral + sensor->histeresis)){
      sensor->estado = LINEA_NEGRO;
    }
  }
  return sensor->estado;
}

uint8_t seguir_linea(void)
{
  uint8_t accion = LINEA_DETENER;

  if(actualizar_estado_linea(&ir_izq) == LINEA_COLOR){
    accion += LINEA_IZQ_OK;
  }
  if(actualizar_estado_linea(&ir_der) == LINEA_COLOR){
    accion += LINEA_DER_OK;
  }
  return accion;
}

