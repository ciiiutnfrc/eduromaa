#include "sapi.h"
#include "bocina.h"

int main(void)
{
	/* Inicializa EduCIAA */
	boardConfig();

	/* Inicializa Bocina */
  iniBocina();

	while(true)	
  {
    prenderBocina();
    delay(20);
    apagarBocina();
    delay(20);
	}
	return 0;
}

