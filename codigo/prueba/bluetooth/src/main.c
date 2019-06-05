/*==================[inclusiones]=============================================*/
#include "bluetooth.h"

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void){

	/* ------------- INICIALIZACIONES ------------- */
	uint8_t bt_dato = 0;


	/* Inicializa EduCIAA */
	boardConfig();

	/* Configuraci�n de UART */
	uartConfig(UART_USB, 9600);

	/* Inicializa m�dulo Bluetooth */
	iniBT();
	prenderBT();

	/* ------------- REPETIR POR SIEMPRE ------------- */
	while(1) {
		delay(2000);
		gpioWrite(LED1, OFF);
		if(leerBT(&bt_dato)){
			if(bt_dato != '\n' && bt_dato != '\r'){
				uartWriteByte(UART_USB, bt_dato);
				uartWriteString(UART_USB, "\r\n");
			}
		}
	}
	/* Esta instrucci�n no deber�a ejecutarse, ya que el programa nunca sale del lazo "while(1)" */
	return 0 ;
}

