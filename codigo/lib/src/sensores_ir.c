/*==================[inclusiones]=============================================*/
#include "sensores_ir.h"

/*==================[definiciones]============================================*/
#define SENSORES_IR_H CAN_TD
#define SENSORES_IR_OFF OFF
#define SENSORES_IR_ON ON

#define SENSOR_IR_CH_IZQ CH1
#define SENSOR_IR_CH_DER CH2

uint16_t sensores_ir[SENSOR_IR_CANT];

/*==================[implementacion]==========================================*/

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

