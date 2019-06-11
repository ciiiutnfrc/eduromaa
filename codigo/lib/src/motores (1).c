/*==================[inclusiones]=============================================*/
#include "motores.h"

/*==================[definiciones]===========================================*/
#define MOTOR_ENABLE  T_FIL0
#define MOTOR_PWM_DER PWM3    // T_FIL2
#define MOTOR_PWM_IZQ PWM4    // T_FIL3

#define MOTOR_ON ON
#define MOTOR_OFF OFF

#define MOTOR_VEL_MAX 100
#define MOTOR_PWM_PARADO 128 // 50% de PWM mantiene motores "trabados"

/*==================[implementaciones]=======================================*/
void iniMotores(void)
{
	gpioConfig(MOTOR_ENABLE, GPIO_ENABLE);
	gpioConfig(MOTOR_ENABLE, GPIO_OUTPUT);

	/* Habilitación general */
	pwmConfig(0, PWM_ENABLE);

	pwmConfig(MOTOR_PWM_IZQ, PWM_ENABLE_OUTPUT);
	pwmConfig(MOTOR_PWM_DER, PWM_ENABLE_OUTPUT);

	/* Valores iniciales */
	pwmWrite(MOTOR_PWM_IZQ, MOTOR_PWM_PARADO); // 50%
	pwmWrite(MOTOR_PWM_DER, MOTOR_PWM_PARADO); // 50%
}

void prenderMotores(void)
{
	pwmWrite(MOTOR_PWM_IZQ, MOTOR_PWM_PARADO); // 50%
	pwmWrite(MOTOR_PWM_DER, MOTOR_PWM_PARADO); // 50%
	gpioWrite(MOTOR_ENABLE, MOTOR_ON);
}

void apagarMotores(void)
{
	gpioWrite(MOTOR_ENABLE, MOTOR_OFF);
}

void escribirMotorIzq(int8_t velMotIzq)
{
	if (velMotIzq >= -MOTOR_VEL_MAX && velMotIzq <= MOTOR_VEL_MAX){
			uint8_t pwmIzq = velMotIzq * ((float)MOTOR_PWM_PARADO / MOTOR_VEL_MAX) + MOTOR_PWM_PARADO;
			pwmWrite(MOTOR_PWM_IZQ, pwmIzq);
		}
}

void escribirMotorDer(int8_t velMotDer)
{
	if (velMotDer >= -MOTOR_VEL_MAX && velMotDer <= MOTOR_VEL_MAX){
			uint8_t pwmDer = velMotDer * ((float)MOTOR_PWM_PARADO / MOTOR_VEL_MAX) + MOTOR_PWM_PARADO;
			pwmWrite(MOTOR_PWM_DER, pwmDer);
		}
}

void escribirMotores(int8_t velMotIzq, int8_t velMotDer)
{
	escribirMotorIzq(velMotIzq);
	escribirMotorDer(velMotDer);
}

void escribirPWMMotores(uint8_t pwmDer, uint8_t pwmIzq)
{
	pwmWrite(MOTOR_PWM_IZQ, pwmIzq);
	pwmWrite(MOTOR_PWM_DER, pwmDer);
}

