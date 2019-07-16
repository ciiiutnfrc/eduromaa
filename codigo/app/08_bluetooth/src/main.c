/*
 * main.c
 *
 *  Created on: 14 jul. 2019
 *      Author: marti
 */

/*==================[inclusiones]============================================*/

#include "eduromaa.h"
#include <stdlib.h>

/*==================[definiciones]===========================================*/

#define MARCHA_NORMAL 1.0 // ¿Tiene sentido este cambio?
#define MARCHA_LENTA  0.7 // ¿Qué problemas introduce?
#define MOTOR_PARADO  0

#define DIAMETRO_RUEDAS_CM   6.67   // Diámetro de las ruedas [cm]
#define RANURAS_ENCODER     20      // Cantidad de ranuras del encoder
// Longitud del arco de la rueda entre 2 pulsos de enconder
#define DIST_CUENTA_CM (3.1416 * DIAMETRO_RUEDAS_CM / RANURAS_ENCODER)

typedef struct
{
    uint32_t cuenta_anterior, dist_recorrida, rpm;
    uint8_t vel_cuentas_seg, vel_cm_seg;

} odometria_t;

typedef enum {COM_AVANZAR, COM_RETROCEDER, COM_GIRAR_IZQ, COM_GIRAR_DER,
    COM_DETENER, COM_AV_IZQ, COM_AV_DER, COM_RET_IZQ, COM_RET_DER,
    COM_X, COM_Y, COM_LUZ_ON, COM_LUZ_OFF, COM_R1, COM_R2} comandos;

float procesar_sonar(float *dist_cm);
void procesar_tacometros(odometria_t *odo_izq, odometria_t *odo_der);
void procesar_indicadores(void);
void procesar_comandos(int8_t *v_izq, int8_t *v_der, uint8_t *dato);
void procesar_motores(float marcha, int8_t ref_v_izq, int8_t ref_v_der);

/* Variables para seguir estado de paragolpes */
estadosParagolpes estodoPg;
delay_t retardo_paragolpes;

/*==================[implementaciones]=======================================*/
int main(void)
{
    odometria_t odo_i, odo_d;
    float marcha = 0;
    uint8_t com_v_izq, com_v_der, com_valor;

    uint8_t vel_rueda_i, vel_rueda_d;
    float dist_cm;
    char buffer[10];

    // Variables para Retardos NO bloqueantes
    delay_t retardo_sonar, retardo_uart, retardo_odometria;

    iniEduromaa();  // Inicializa EduRoMAA

    /* Habilita Funcionamiento de Paragolpes por Interrupción */
    estodoPg = LIBRE;
    delayInit(&retardo_paragolpes, 1000);
    prenderIntParagolpes(paragolpesIzqInt, paragolpesDerInt);
    apagarBocina();

    /* Prender solo los Módulos a utilizar */
    prenderSensoresIR();
    prenderSonar();
    prenderMotores();
    prenderTacometros();
    prenderBT();

    vel_rueda_d = vel_rueda_i = 0;

    odo_i.dist_recorrida = 0;
    odo_d.dist_recorrida = 0;
    delayInit(&retardo_sonar, 20);
    delayInit(&retardo_odometria, 1000);
    delayInit(&retardo_uart, 500);

    while (1)
    {
        /* En cada ciclo ver si hace falta apagar los indicadores */
        procesar_indicadores();

        if (delayRead(&retardo_sonar))
        {
            marcha = procesar_sonar(&dist_cm);
            procesar_motores(marcha, com_v_izq, com_v_der);
        }

        if (delayRead(&retardo_odometria))
        {
            procesar_tacometros(&odo_i, &odo_d);
        }

        if (delayRead(&retardo_uart))
        {

            printf("Ti[c/s]: %d\tTi[cm/s]: %d\tTi[rpm]:%d\tTi[cm]:%d\r\n",
                    odo_i.vel_cuentas_seg, odo_i.vel_cm_seg, odo_i.rpm,
                    odo_i.dist_recorrida);
            printf("Td[c/s]: %d\tTd[cm/s]: %d\tTd[rpm]:%d\tTd[cm]:%d\r\n",
                    odo_d.vel_cuentas_seg, odo_d.vel_cm_seg, odo_d.rpm,
                    odo_d.dist_recorrida);

            procesar_comandos(&com_v_izq, &com_v_der, &com_valor);

            sprintf(buffer, "D%d\n", (uint8_t) dist_cm);
            transmitirBT(buffer);

        }
    }

    /* NO DEBE LLEGAR NUNCA AQUI, ¿el programa se ejecuta eternamente? */
    return 0;
}

void procesar_motores(float marcha, int8_t ref_v_izq, int8_t ref_v_der)
{
    escribirMotores((int8_t)(marcha*ref_v_izq), (int8_t)(marcha*ref_v_der));
}

void procesar_comandos(int8_t *v_izq, int8_t *v_der, uint8_t *dato)
{
    uint8_t bt_dato;

    if (recibirBT(&bt_dato))
    {
        switch (bt_dato)
        {
        case BT_AVANZAR:
            *v_izq = 100;
            *v_der = 100;
            break;

        case BT_RETROCEDER:
            *v_izq = -100;
            *v_der = -100;
            break;
        case BT_GIRAR_IZQ:
            *v_izq = -100;
            *v_der = 100;
            break;
        case BT_GIRAR_DER:
            *v_izq = 100;
            *v_der = -100;
            break;
        case BT_DETENER:
            *v_izq = 0;
            *v_der = 0;
            break;
        case BT_AV_IZQ:
            *v_izq = 60;
            *v_der = 100;
            break;
        case BT_AV_DER:
            *v_izq = 100;
            *v_der = 60;
            break;
        case BT_RET_IZQ:
            *v_izq = -60;
            *v_der = -100;
            break;
        case BT_RET_DER:
            *v_izq = -100;
            *v_der = -60;
            break;
        case BT_X:
            break;
        case BT_Y:
            break;
        case BT_LUZ_ON:
            gpioWrite(LED1, ON);
            gpioWrite(LED3, ON);
            break;
        case BT_LUZ_OFF:
            gpioWrite(LED3, OFF);
            gpioWrite(LED3, OFF);
            break;
        case BT_RANGO1:
//            *comandos = COM_R1;
            recibirBT(&bt_dato);
            *dato = (uint8_t)bt_dato;
            break;
        case BT_RANGO2:
//            *comandos = COM_R2;
            recibirBT(&bt_dato);
            *dato = (uint8_t)bt_dato;
            break;
        default:
             break;

        }
    }
}

void procesar_tacometros(odometria_t *odo_izq, odometria_t *odo_der)
{
    tacometro_t tacoIzq, tacoDer;

    leerTacometros(&tacoIzq, &tacoDer);

    odo_izq->vel_cuentas_seg = tacoIzq.cuenta - odo_izq->cuenta_anterior;
    odo_izq->vel_cm_seg = odo_izq->vel_cuentas_seg * DIST_CUENTA_CM;
    odo_izq->rpm = odo_izq->vel_cuentas_seg * 3;  // <--¿De dónde sale el 3?
    odo_izq->dist_recorrida += odo_izq->vel_cm_seg;
    odo_izq->cuenta_anterior = tacoIzq.cuenta;

    odo_der->vel_cuentas_seg = tacoDer.cuenta - odo_der->cuenta_anterior;
    odo_der->vel_cm_seg = odo_der->vel_cuentas_seg * DIST_CUENTA_CM;
    odo_der->rpm = odo_der->vel_cuentas_seg * 3;  // <--¿De dónde sale el 3?
    odo_der->dist_recorrida += odo_der->vel_cm_seg;
    odo_der->cuenta_anterior = tacoDer.cuenta;
}

float procesar_sonar(float *dist_cm)
{
    leerSonar(dist_cm);

    if (*dist_cm < 5)
    {
        return MOTOR_PARADO;
    } else if (*dist_cm < 10)
    {
        return MARCHA_LENTA;

    } else
    {
        return MARCHA_NORMAL;
    }
}

void procesar_indicadores(void)
{
    if (estodoPg != LIBRE)
    {
        if (delayRead(&retardo_paragolpes))
        {
            apagarBocina();
            gpioWrite(LEDR, OFF);
            gpioWrite(LEDG, OFF);
            estodoPg = LIBRE;
        }
    }
}

/**
 * Funciones de Manejo de Interrupción
 */
void paragolpesIzqInt(void)
{
    gpioWrite(LEDR, ON);
    escribirMotores(0, 0);
    prenderBocina();
    estodoPg += GOLPE_IZQ;
    delayRead(&retardo_paragolpes);
}

void paragolpesDerInt(void)
{
    gpioWrite(LEDG, ON);
    escribirMotores(0, 0);
    prenderBocina();
    estodoPg += GOLPE_DER;
    delayRead(&retardo_paragolpes);
}
