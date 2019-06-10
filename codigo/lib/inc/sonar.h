#ifndef _SONAR_H
#define _SONAR_H

/*==================[inclusiones]=============================================*/
#include "sapi.h"

/*==================[definiciones]============================================*/

/*==================[protitipos]==============================================*/
void iniSonar(void);
void prenderSonar(void);
void apagarSonar(void);
bool leerSonar(float *dist_cm);

#endif /* #ifndef _SONAR_H */

