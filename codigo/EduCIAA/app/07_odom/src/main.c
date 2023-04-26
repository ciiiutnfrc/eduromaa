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

#define DIAMETRO_RUEDAS_CM   6.67   // Diámetro de las ruedas [cm]
#define RANURAS_ENCODER     20      // Cantidad de ranuras del encoder
// Longitud del arco de la rueda entre 2 pulsos de enconder
#define DIST_CUENTA_CM (3.1416 * DIAMETRO_RUEDAS_CM / RANURAS_ENCODER)

uint8_t procesar_sonar(void);
void procesar_seguidor_linea(uint8_t vel_ruedas);

/*==================[implementaciones]=======================================*/
int main(void)
{

    uint32_t ti_cuenta_anterior, ti_dist_recorrida, ti_rpm;
    uint8_t td_vel_cuentas_seg, td_vel_cm_seg;
    uint32_t td_cuenta_anterior, td_dist_recorrida, td_rpm;
    uint8_t ti_vel_cuentas_seg, ti_vel_cm_seg;

    uint8_t marcha;

    // Variables para Retardos NO bloqueantes
    delay_t retardo_ir, retardo_uart, retardo_odometria;
    tacometro_t tacoIzq, tacoDer;

    iniEduromaa();  // Inicializa EduRoMAA

    /* Prender solo los Módulos a utilizar */
    prenderSensoresIR();
    prenderSonar();
    prenderMotores();
    prenderTacometros();

    marcha = 0;
    ti_dist_recorrida = 0;
    delayInit(&retardo_ir, 20);
    delayInit(&retardo_odometria, 1000);
    delayInit(&retardo_uart, 2000);


    while (1)
    {
        if (delayRead(&retardo_ir))
        {
            marcha = procesar_sonar();
            procesar_seguidor_linea(marcha);
        }

        if (delayRead(&retardo_odometria))
        {
            leerTacometros(&tacoIzq, &tacoDer);

            ti_vel_cuentas_seg = tacoIzq.cuenta - ti_cuenta_anterior;
            ti_vel_cm_seg = ti_vel_cuentas_seg * DIST_CUENTA_CM;
            ti_rpm = ti_vel_cuentas_seg * 3;// <--¿De dónde sale el 3?
            ti_dist_recorrida += ti_vel_cm_seg;
            ti_cuenta_anterior = tacoIzq.cuenta;

            td_vel_cuentas_seg = tacoDer.cuenta - td_cuenta_anterior;
            td_vel_cm_seg = td_vel_cuentas_seg * DIST_CUENTA_CM;
            td_rpm = td_vel_cuentas_seg * 3;// <--¿De dónde sale el 3?
            td_dist_recorrida += td_vel_cm_seg;
            td_cuenta_anterior = tacoDer.cuenta;

        }

        if (delayRead(&retardo_uart))
        {

            printf("Ti[c/s]: %d\tTi[cm/s]: %d\tTi[rpm]:%d\tTi[cm]:%d\r\n",
                    ti_vel_cuentas_seg, ti_vel_cm_seg, ti_rpm,
                    ti_dist_recorrida);
            printf("Td[c/s]: %d\tTd[cm/s]: %d\tTd[rpm]:%d\tTd[cm]:%d\r\n",
                                td_vel_cuentas_seg, td_vel_cm_seg, td_rpm,
                                td_dist_recorrida);
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

