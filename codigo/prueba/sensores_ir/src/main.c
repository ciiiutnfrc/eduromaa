/*==================[inclusiones]=============================================*/
#include "motores.h"
#include "sapi.h"
#include "sensores_ir.h"
#include <stdlib.h>

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int
main (void)
{
    uint16_t ir_izq, ir_der;
    static char buffer[10];

    /* Inicializa EduCIAA */
    boardConfig ();

    /* Configuración de UART */
    uartConfig (UART_USB, 9600);

    /* Inicializa Sensores IR */
    iniSensoresIR ();
    prenderSensoresIR ();
    while (true)
        {
            actualizarSensoresIR ();

            ir_izq = leerSensorIR (SENSOR_IR_IZQ);
            ir_der = leerSensorIR (SENSOR_IR_DER);

            uartWriteString (UART_USB, "IR_I: ");
            itoa (ir_izq, buffer, 10);
            uartWriteString (UART_USB, buffer);

            uartWriteString (UART_USB, "\tIR_D: ");
            itoa (ir_der, buffer, 10);
            uartWriteString (UART_USB, buffer);
            uartWriteString (UART_USB, "\r\n");

            delay (2000);
        }
    return 0;
}

