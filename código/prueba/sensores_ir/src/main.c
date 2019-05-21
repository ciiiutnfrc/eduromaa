#include "sapi.h"
#include "sensores_ir.h"

int main(void)
{
  uint16_t ir_izq, ir_der;

	/* Inicializa EduCIAA */
	boardConfig();

  /* Configuración de UART */
  uartConfig(UART_USB, 9600);

	/* Inicializa Sensores IR */
  iniSensoresIR();

	while(true)	
  {
    prenderSensoresIR();
    actualizarSensoresIR();

    ir_izq = leerSensorIR(SENSOR_IR_IZQ);
    uartTxWrite(UART_USB, (ir_izq>>8));
    uartTxWrite(UART_USB, ir_izq);

    apagarSensoresIR();
    delay(1000);
	}
	return 0;
}

