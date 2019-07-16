/*==================[inclusiones]=============================================*/
#include "bluetooth.h"

/*==================[definiciones]======================================*/
#define BT_H CAN_RD
#define BT_ON ON
#define BT_OFF OFF

bool bt_on = false;

/*==================[protitipos]==============================================*/

void iniBT(void)
{
    /* Configuración del GPIO prender/apagar */
    gpioConfig(BT_H, GPIO_ENABLE);
    gpioConfig(BT_H, GPIO_OUTPUT);

    /* Apaga Sensores IR */
    gpioWrite(BT_H, BT_OFF);

    /* Inicializar UART_232 a 9600 baudios
     * velocidad por defecto del HC-05 */
    uartConfig(UART_232, 9600);
}

void prenderBT(void)
{
    gpioWrite(BT_H, BT_ON);
    bt_on = true;
}

void apagarBT(void)
{
    bt_on = false;
    gpioWrite(BT_H, BT_OFF);
}

bool_t recibirBT(uint8_t *dato)
{

    if (bt_on == true)
    {
        return uartReadByte(UART_232, dato); /* Sin error */
    } else
        return false; /* Con error */
}

bool_t transmitirBT(const char* str)
{
    if (bt_on == true)
    {
        uartWriteString(UART_232, str); /* Sin error */
        return true;
    } else
        return false; /* Con error */
}
