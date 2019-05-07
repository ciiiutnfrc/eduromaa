#include "sapi.h"
#include "sonar.h"

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

    delay(1000);
  };

  return 0;
}

