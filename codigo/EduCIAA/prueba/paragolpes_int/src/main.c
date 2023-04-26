/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "paragolpes.h"

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{

    /* Inicializa EduCIAA */
    boardConfig();

    /* Inicializa Módulo de Paragolpes */
    iniParagolpes();

    /* Habilita Funcionamiento de Paragolpes por Interrupción */
    prenderIntParagolpes(paragolpesIzqInt, paragolpesDerInt);

    while (true)
    {
        /* Apaga los LEDs, si fueron encendidos por Interrupciones */
        gpioWrite(LED3, OFF);
        gpioWrite(LED1, OFF);

        delay(6000);
    }
    return 0;
}

/**
 * Funciones de Manejo de Interrupción
 */
void paragolpesIzqInt(void)
{
    gpioWrite(LED3, ON);
}

void paragolpesDerInt(void)
{
    gpioWrite(LED1, ON);
}

