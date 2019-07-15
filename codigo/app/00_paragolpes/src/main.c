/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "paragolpes.h"

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{
    estadosParagolpes estodoPg = LIBRE;

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
            gpioWrite(LED1, OFF);
            gpioWrite(LED3, OFF);
            break;

        case GOLPE_IZQ:
            gpioWrite(LED3, ON);
            break;

        case GOLPE_DER:
            gpioWrite(LED1, ON);
            break;

        case GOLPE_AMBOS:
            gpioWrite(LED1, ON);
            gpioWrite(LED3, ON);
            break;

        default:
            break;
        }

        delay(5000);
    }
    return 0;
}

