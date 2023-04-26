/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "sensores_ir.h"
#include <stdio.h>

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{
    uint16_t ir_izq, ir_der;
    static char buffer[10];

    /* Inicializa EduCIAA */
    boardConfig();

    /* Configuración de UART */
    uartConfig(UART_USB, 115200);

    /* Inicializa Sensores IR */
    iniSensoresIR();
    prenderSensoresIR();

    while (true)
    {
        actualizarSensoresIR();

        ir_izq = leerSensorIR(SENSOR_IR_IZQ);
        ir_der = leerSensorIR(SENSOR_IR_DER);

        printf("IR_I:%d\tIR_D:%d\r\n", ir_izq, ir_der);

        delay(2000);
    }
    return 0;
}

