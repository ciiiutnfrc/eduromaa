#ifndef _MOTORES_H
#define _MOTORES_H

/*==================[inclusiones]============================================*/
#include "sapi.h"

/*==================[definiciones]===========================================*/

/*==================[protitipos]=============================================*/

void iniMotores(void);

void prenderMotores(void); // EN=1 y PWM=50%
void apagarMotores(void);

/*
 * Ancho de Pulso Modulado: 0 a 255
 * */

void escribirPWMMotorIzq(int8_t pwmIzq);
void escribirPWMMotorDer(int8_t pwmDer);
void escribirPWMMotores(uint8_t pwmDer, uint8_t pwmIzq);

/*
 * Velocidad de Motores en porcentaje -100 a 100
 * */

void escribirMotorIzq(int8_t porcentajeIzq);
void escribirMotorDer(int8_t porcentajeDer);
void escribirMotores(int8_t porcentajeIzq, int8_t porcentajeDer);

/*
 * Velocidad de Motores en cm/s
 * */

void escribirVelMotorIzq(int8_t velMotIzq);
void escribirVelMotorDer(int8_t velMotDer);
void escribirVelMotores(int8_t velMotIzq, int8_t velMotDer);



#endif

