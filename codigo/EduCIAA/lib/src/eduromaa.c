/*==================[inclusiones]=============================================*/
#include "eduromaa.h"

/*==================[definiciones]============================================*/

/*==================[implementaciones]==============================================*/

void iniEduromaa(void)
{
  /* Todos los módulos se inicializan en estado APAGADO */

  /* Inicializa EduCIAA */
  boardConfig();

  /* Inicializa Paragolpes */
  iniParagolpes();

  /* Inicializa Bocina */
  iniBocina();

  /* Inicializa Motores */
  iniMotores();
  apagarMotores();

  /* Inicializa Sonar */
  iniSonar();
  apagarSonar();

  /* Inicializa Tacometros */
  iniTacometros();
  apagarTacometros();

  /* Inicializa Sensores IR */
  iniSensoresIR();
  apagarSensoresIR();

  /* Inicializa m�dulo Bluetooth */
  iniBT();
  apagarBT();

  /* Configuración de UART por USB */
  uartConfig(UART_USB, 115200);
}

