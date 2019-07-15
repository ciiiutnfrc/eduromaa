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

/*==================[implementaciones]=======================================*/
int main(void)
{
    float dist_cm;
    uint8_t marcha;
    delay_t retardo_ir; // Variable de Retardo NO bloqueante para infrarrojos


    iniEduromaa();  // Inicializa EduRoMAA

    /* Inicializa seguidor de líneas */
    prenderSensoresIR();
    delayInit(&retardo_ir, 20);

    /* Inicializa control de motores según distancia aobstáculos */
    prenderSonar();
    prenderMotores();
    marcha = 0;


    while (1)
    {

        if (delayRead(&retardo_ir))
        {

            leerSonar(&dist_cm);
            if (dist_cm < 5)
            {
                marcha = MOTOR_PARADO;
            } else if (dist_cm < 10)
            {
                marcha = MARCHA_LENTA;

            } else
            {
                marcha = MARCHA_NORMAL;
            }

            switch (seguir_linea())
            {
            case LINEA_IZQ_DER_OK:
                gpioWrite(LED1, OFF);
                gpioWrite(LED2, ON);
                gpioWrite(LED3, OFF);
                /* Motores: ambos avanzan a la misma velocidad */
                escribirMotores(marcha, marcha);
                break;
            case LINEA_DER_OK:
                gpioWrite(LED1, ON);
                gpioWrite(LED2, OFF);
                gpioWrite(LED3, OFF);
                /* Motores: motor izquierdo avanza a mayor velocidad que el derecho */
                escribirMotores(marcha/2 , marcha);
                break;
            case LINEA_IZQ_OK:
                gpioWrite(LED1, OFF);
                gpioWrite(LED2, OFF);
                gpioWrite(LED3, ON);
                /* Motores: motor derecho avanza a mayor velocidad que el izquierdo */
                escribirMotores(marcha, marcha/2);
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
    }
    /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
     por ningun S.O. */
    return 0;
}

/*==================[end of file]============================================*/

