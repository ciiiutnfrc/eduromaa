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
    delay_t retardo_trayectoria;

    /* Inicializa EduRoMAA */
    iniEduromaa();

    /* Habilita Funcionamiento de Paragolpes por Interrupción */
    estodoPg = LIBRE;
    delayInit(&retardo_paragolpes, 1000);
    prenderIntParagolpes(paragolpesIzqInt, paragolpesDerInt);


    prenderMotores();
    delayInit(&retardo_trayectoria, 1000);

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
                escribirMotores(0, 0);
                estodoPg = LIBRE;
            }
        }


        if(delayRead(&retardo_trayectoria))
        {

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
    escribirMotores(70, 40);
    prenderBocina();
    estodoPg += GOLPE_IZQ;
    delayRead(&retardo_paragolpes);
}

void paragolpesDerInt(void)
{
    gpioWrite(LED1, ON);
    escribirMotores(40, 70);
    prenderBocina();
    estodoPg += GOLPE_DER;
    delayRead(&retardo_paragolpes);
}
