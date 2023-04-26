/*==================[inclusiones]=============================================*/
#include "sonar.h"

/*==================[definiciones]============================================*/
#define SONAR_ONOFF_GPIO GPIO4
#define SONAR_ON ON
#define SONAR_OFF OFF

bool sonar_on = false;

/*==================[protitipos]==============================================*/

void iniSonar(void)
{
  /* Inicializar el sensor ultrasonico #0 */
  ultrasonicSensorConfig(ULTRASONIC_SENSOR_0, ULTRASONIC_SENSOR_ENABLE);

  /* Configurar pin de encendido/apagado */
  gpioConfig(SONAR_ONOFF_GPIO, GPIO_ENABLE);
  gpioConfig(SONAR_ONOFF_GPIO, GPIO_OUTPUT);
}

void prenderSonar(void)
{
  sonar_on = 1;
  gpioWrite(SONAR_ONOFF_GPIO, SONAR_ON);
}

void apagarSonar(void)
{
  sonar_on = 0;
  gpioWrite(SONAR_ONOFF_GPIO, SONAR_OFF);
}

bool leerSonar(float *dist_cm)
{
  if (sonar_on == true)
  {
    *dist_cm = ultrasonicSensorGetDistance(ULTRASONIC_SENSOR_0, CM);
    return true; /* Sin error */
  } else
    *dist_cm = 500;
  return false; /* Con error */
}

