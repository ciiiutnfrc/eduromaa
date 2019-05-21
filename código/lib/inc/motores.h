#ifndef _MOTORES_H
#define _MOTORES_H

/*==================[inclusiones]============================================*/
#include "sapi.h"


/*==================[definiciones]===========================================*/


/*==================[protitipos]=============================================*/

bool_t iniMotores(void);

void prenderMotores(void); // EN=1 y PWM=50%
void apagarMotores(void);

void escribirMotorIzq(int8_t pwmIzq); // +- 100
void escribirMotorDer(int8_t pwmDer); // +- 100
void escribirMotores(int8_t velMotIzq, int8_t velMotDer);

void escribirPWMMotores(uint8_t pwmDer, uint8_t pwmIzq);

#endif

