/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "paragolpes.h"

/*==================[definiciones]===========================================*/
#define TIEMPO_PARAGOLPES 5000

/*==================[implementaciones]=======================================*/
int main(void)
{
    estadosParagolpes estodoPg = LIBRE;

    delay_t retardo_paragolpes;

    /* Inicializa EduCIAA */
    boardConfig();

    /* Inicializa Paragolpes */
    iniParagolpes();

    while (true)
    {
        estodoPg = leerParagolpes();

        switch (estodoPg)
        {
        case LIBRE:
            if (delayRead(&retardo_paragolpes))
            {
                gpioWrite(LED1, OFF);
                gpioWrite(LED3, OFF);
            }
            break;

        case GOLPE_IZQ:
            gpioWrite(LED3, ON);
            delayInit(&retardo_paragolpes, TIEMPO_PARAGOLPES);
            break;

        case GOLPE_DER:
            gpioWrite(LED1, ON);
            delayInit(&retardo_paragolpes, TIEMPO_PARAGOLPES);
            break;

        case GOLPE_AMBOS:
            gpioWrite(LED1, ON);
            gpioWrite(LED3, ON);
            delayInit(&retardo_paragolpes, TIEMPO_PARAGOLPES);
            break;

        default:
            break;
        }

        delay(500);
    }
    return 0;
}

