/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "eduromaa.h"
#include <stdio.h>

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{
    uint16_t cuenta;
    /* Inicializa EduCIAA */
    boardConfig();

    cuenta = 0;

    /* Configuración de UART por USB */
    uartConfig(UART_USB, 115200);

    printf("Prueba USB_UART: \r\n");

    while (true)
    {
        delay(1000);
        printf("Cuenta: %d\r\n", cuenta++);

    }
    return 0;
}
