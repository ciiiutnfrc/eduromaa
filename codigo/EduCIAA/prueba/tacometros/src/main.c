/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "tacometros.h"
#include <stdio.h>
/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{
    tacometro_t tacoIzq, tacoDer;
    char buffer[5];

    /* Inicializa EduCIAA */
    boardConfig();

    /* Configuración de UART */
    uartConfig(UART_USB, 115200);

    /* Inicializa Tacometros */
    iniTacometros();

    while (true)
    {
        prenderTacometros();
        leerTacometros(&tacoIzq, &tacoDer);

        printf("T_Iz:%d\tT_De:%d\r\n", tacoIzq.cuenta, tacoDer.cuenta);
        delay(1000);
    };

    return 0;
}

