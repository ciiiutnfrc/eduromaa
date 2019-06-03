/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "sonar.h"


/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{
  float dist_cm;

  /* Inicializa EduCIAA */
  boardConfig();

  /* Inicializa Sonar */
  iniSonar();
  prenderSonar();


  while(true)
  {
    leerSonar(&dist_cm);

    if(dist_cm > 10)
      gpioWrite(LED1, ON);
    else
      gpioWrite(LED1, OFF);

  //  delay(500);
 //   gpioWrite(LED2, ON);
 //   delay(500);
 //   gpioWrite(LED2, OFF);
  };

  return 0;
}
