/*
 * main.c
 *
 *  Created on: 14 jul. 2019
 *      Author: marti
 */

/*==================[inclusiones]============================================*/

#include "eduromaa.h"

/*==================[definiciones]===========================================*/

#define MARCHA_NORMAL 70
#define MARCHA_LENTA  50
#define MOTOR_PARADO  0

uint8_t procesar_sonar(void);
void procesar_seguidor_linea(uint8_t vel_ruedas);

/*==================[implementaciones]=======================================*/
int main(void)
{

    uint8_t marcha;
    delay_t retardo_ir; // Variables para Retardos NO bloqueante
    tacometro_t tacoIzq, tacoDer;

    iniEduromaa();  // Inicializa EduRoMAA

    /* Prender solo los Módulos a utilizar */
    prenderSensoresIR();
    prenderSonar();
    prenderMotores();
    prenderTacometros();

    marcha = 0;
    delayInit(&retardo_ir, 20);


    while (1)
    {
        if (delayRead(&retardo_ir))
        {
            marcha = procesar_sonar();
            procesar_seguidor_linea(marcha);
        }

    }

    /* NO DEBE LLEGAR NUNCA AQUI, ¿el programa se ejecuta eternamente? */
    return 0;
}

uint8_t procesar_sonar(void)
{
    float dist_cm;

    leerSonar(&dist_cm);

    if (dist_cm < 5)
    {
        return MOTOR_PARADO;
    } else if (dist_cm < 10)
    {
        return MARCHA_LENTA;

    } else
    {
        return MARCHA_NORMAL;
    }
}

void procesar_seguidor_linea(uint8_t vel_ruedas)
{
    switch (seguir_linea())
    {
    case LINEA_IZQ_DER_OK:
        gpioWrite(LED1, OFF);
        gpioWrite(LED2, ON);
        gpioWrite(LED3, OFF);
        /* Motores: ambos avanzan a la misma velocidad */
        escribirMotores(vel_ruedas, vel_ruedas);
        break;
    case LINEA_DER_OK:
        gpioWrite(LED1, ON);
        gpioWrite(LED2, OFF);
        gpioWrite(LED3, OFF);
        /* Motores: motor izquierdo avanza a mayor velocidad que el derecho */
        escribirMotores(vel_ruedas/2, vel_ruedas);
        break;
    case LINEA_IZQ_OK:
        gpioWrite(LED1, OFF);
        gpioWrite(LED2, OFF);
        gpioWrite(LED3, ON);
        /* Motores: motor derecho avanza a mayor velocidad que el izquierdo */
        escribirMotores(vel_ruedas, vel_ruedas/ 2);
        break;
    case LINEA_DETENER:
    default:
        gpioWrite(LED1, OFF);
        gpioWrite(LED2, OFF);
        gpioWrite(LED3, OFF);
        /* Motores: ambos motores se detienen */
        escribirMotores(MOTOR_PARADO, MOTOR_PARADO);
        break;
    }
}
