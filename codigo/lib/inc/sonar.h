#ifndef SONAR_H
#define SONAR_H

/*==================[inclusiones]=============================================*/
#include "sapi.h"

/*==================[definiciones]============================================*/

/*==================[protitipos]==============================================*/

void iniSonar(void);
void prenderSonar(void);
void apagarSonar(void);
bool leerSonar(float *dist_cm);

#endif /* SONAR_H */

