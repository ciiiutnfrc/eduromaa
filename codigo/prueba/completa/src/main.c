/*==================[inclusiones]=============================================*/
#include "eduromaa.h"
#include <stdio.h>

/*==================[definiciones]===========================================*/
/* Variables para seguir estado de paragolpes */
estadosParagolpes estodoPg;
delay_t retardo_paragolpes;

/*==================[implementaciones]=======================================*/
int main(void)
{

    float dist_cm;
    delay_t retardo_sonar;

    tacometro_t tacoIzq, tacoDer;
    uint16_t ir_izq, ir_der;

    char buffer[5];
    uint16_t cuenta_lin;
    delay_t retardo_uart;

    /* Inicializa EduRoMAA */
    iniEduromaa();

    prenderBocina();
    delay(20);
    apagarBocina();
    delay(200);
    prenderBocina();
    delay(20);
    apagarBocina();
    delay(200);
    prenderBocina();
    delay(100);
    apagarBocina();

    /* Habilita Funcionamiento de Paragolpes por Interrupción */
    estodoPg = LIBRE;
    delayInit(&retardo_paragolpes, 1000);
    prenderIntParagolpes(paragolpesIzqInt, paragolpesDerInt);


    /* Configuración de transmisión por uart */
    cuenta_lin = 0; // Cantidad de datos transmitidos
    delayInit(&retardo_uart, 2000); // Envía información cada 2 segundos

    /* Inicializar sonar*/
    delayInit(&retardo_sonar, 200);
    prenderSonar();

    prenderTacometros();
    prenderSensoresIR();

    printf("\r\nEduRoMAA 0.1: Hola...\r\n");
    prenderMotores();
    escribirMotores(100, 100);
    while (1)
    {
        /* En cada ciclo ver si hace falta apagar los indicadores */
        if(estodoPg != LIBRE)
        {
            if (delayRead(&retardo_paragolpes))
            {
                apagarBocina();
                gpioWrite(LED1, OFF);
                gpioWrite(LED3, OFF);
                estodoPg = LIBRE;
            }
        }


        if(delayRead(&retardo_sonar))
        {
            apagarBocina();
            leerSonar(&dist_cm);
            if (dist_cm < 5)
            {
                escribirMotores(0, 0);
                prenderBocina();
            } else if (dist_cm < 10)
            {
                escribirMotores(50, 50);
            } else if (dist_cm < 30)
            {
                escribirMotores(80, 80);
            } else
            {
                escribirMotores(100, 100);
            }
        }

        if(delayRead(&retardo_uart))
        {
            leerTacometros(&tacoIzq, &tacoDer);
            actualizarSensoresIR();
            ir_izq = leerSensorIR(SENSOR_IR_IZQ);
            ir_der = leerSensorIR(SENSOR_IR_DER);

            printf("%d: S[cm]:%d\tTI:%d\tTD:%d\tII:%d\tID:%d\r\n", cuenta_lin++,
                    (uint8_t) dist_cm, tacoIzq.cuenta, tacoDer.cuenta, ir_izq,
                    ir_der);
        }

        delay(100);
    }
    return 0;
}

/**
 * Funciones de Manejo de Interrupción
 */
void paragolpesIzqInt(void)
{
    gpioWrite(LED3, ON);
    escribirMotores(0, 0);
    prenderBocina();
    estodoPg += GOLPE_IZQ;
    delayRead(&retardo_paragolpes);
}

void paragolpesDerInt(void)
{
    gpioWrite(LED1, ON);
    escribirMotores(0, 0);
    prenderBocina();
    estodoPg += GOLPE_DER;
    delayRead(&retardo_paragolpes);
}
