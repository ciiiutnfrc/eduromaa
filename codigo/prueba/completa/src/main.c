/*==================[inclusiones]=============================================*/
#include "eduromaa.h"
#include <stdio.h>

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{

    float dist_cm;
    tacometro_t tacoIzq, tacoDer;
    uint16_t ir_izq, ir_der;
    char buffer[5];
    uint16_t cuenta_lin;

    /* Inicializa EduRoMAA */
    iniEduromaa();
    /* Habilita Funcionamiento de Paragolpes por Interrupción */
    prenderIntParagolpes(paragolpesIzqInt, paragolpesDerInt);

    cuenta_lin = 0;

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

    prenderSonar();
    prenderTacometros();
    prenderSensoresIR();

    printf("\r\nEduRoMAA 0.1: Hola...\r\n");
    prenderMotores();
    escribirMotores(100, 100);
    while (1)
    {

        delay(1000);
        /* Apagar paragolpes en cada ciclo */
        apagarBocina();
        gpioWrite(LED3, OFF);
        gpioWrite(LED1, OFF);

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

        leerTacometros(&tacoIzq, &tacoDer);
        actualizarSensoresIR();
        ir_izq = leerSensorIR(SENSOR_IR_IZQ);
        ir_der = leerSensorIR(SENSOR_IR_DER);

        printf("%d: S[cm]:%d\tTI:%d\tTD:%d\tII:%d\tID:%d\r\n", cuenta_lin++,
                (uint8_t) dist_cm, tacoIzq.cuenta, tacoDer.cuenta, ir_izq,
                ir_der);
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
}

void paragolpesDerInt(void)
{
    gpioWrite(LED1, ON);
    escribirMotores(0, 0);
    prenderBocina();
}
