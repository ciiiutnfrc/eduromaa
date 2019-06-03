/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "tacometros.h"
#include <stdlib.h>

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{
  tacometro_t tacoIzq, tacoDer;
  char buffer[5];

  /* Inicializa EduCIAA */
  boardConfig();

  /* Configuración de UART */
  uartConfig(UART_USB, 9600);

  /* Inicializa Tacometros */
  iniTacometros();

  while(true)
  {
    prenderTacometros();
    leerTacometros(&tacoIzq, &tacoDer);

    uartWriteString(UART_USB, "T_Iz: ");
    uartWriteString(UART_USB, itoa(tacoIzq.cuenta, buffer, 10));
    uartWriteString(UART_USB, " T_De: ");
    uartWriteString(UART_USB, itoa(tacoDer.cuenta, buffer, 10));
    uartWriteString(UART_USB, "\r\n");
    delay(1000);
  };

  return 0;
}

