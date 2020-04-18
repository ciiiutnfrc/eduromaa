/*==================[inclusiones]=============================================*/
#include "bocina.h"

/*==================[definiciones]============================================*/
#define BOCINA_GPIO T_COL1
#define BOCINA_OFF OFF
#define BOCINA_ON ON

/*==================[implementaciones]==============================================*/

void iniBocina(void)
{
  gpioConfig(BOCINA_GPIO, GPIO_ENABLE);
  gpioConfig(BOCINA_GPIO, GPIO_OUTPUT);
  gpioWrite(BOCINA_GPIO, BOCINA_OFF);
}

void prenderBocina(void)
{
  gpioWrite(BOCINA_GPIO, BOCINA_ON);
}

void apagarBocina(void)
{
  gpioWrite(BOCINA_GPIO, BOCINA_OFF);
}

