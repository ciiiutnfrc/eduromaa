/*==================[inclusiones]=============================================*/
#include "motores.h"

/*==================[definiciones]===========================================*/
#define MOTOR_ENABLE  T_FIL0
#define MOTOR_PWM_DER PWM3    // T_FIL2
#define MOTOR_PWM_IZQ PWM4    // T_FIL3

#define MOTOR_ON ON
#define MOTOR_OFF OFF

#define MOTOR_PWM_MAX 255 // 50% de PWM mantiene motores "trabados"
#define MOTOR_PWM_PARADO 127 // 50% de PWM mantiene motores "trabados"

#define MOTOR_VEL_MAX 100

/*==================[implementaciones]=======================================*/

void iniMotores(void)
{
  gpioConfig(MOTOR_ENABLE, GPIO_ENABLE);
  gpioConfig(MOTOR_ENABLE, GPIO_OUTPUT);

  /* Habilitaci�n general */
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

/*
 * Ancho de Pulso Modulado: 0 a 255
 * */

void escribirPWMMotorIzq(int8_t pwmIzq)
{
  pwmWrite(MOTOR_PWM_IZQ, pwmIzq);
}
void escribirPWMMotorDer(int8_t pwmDer)
{
  pwmWrite(MOTOR_PWM_DER, pwmDer);
}

void escribirPWMMotores(uint8_t pwmIzq, uint8_t pwmDer)
{
  pwmWrite(MOTOR_PWM_IZQ, pwmIzq);
  pwmWrite(MOTOR_PWM_DER, pwmDer);
}

/*
 * Velocidad de Motores en porcentaje -100 a 100
 * */

void escribirMotorIzq(int8_t porcentajeIzq)
{
  if (porcentajeIzq >= -MOTOR_VEL_MAX && porcentajeIzq <= MOTOR_VEL_MAX)
  {
    int16_t pwmIzq = porcentajeIzq * 
      ((float) MOTOR_PWM_PARADO / MOTOR_VEL_MAX) + MOTOR_PWM_PARADO;
    pwmWrite(MOTOR_PWM_IZQ, pwmIzq);
  }

}

void escribirMotorDer(int8_t porcentajeDer)
{
  if (porcentajeDer >= -MOTOR_VEL_MAX && porcentajeDer <= MOTOR_VEL_MAX)
  {
    int16_t pwmDer = porcentajeDer * 
      ((float) MOTOR_PWM_PARADO / MOTOR_VEL_MAX) + MOTOR_PWM_PARADO;
    pwmWrite(MOTOR_PWM_DER, pwmDer);
  }
}

void escribirMotores(int8_t porcentajeIzq, int8_t porcentajeDer)
{
  escribirMotorIzq(porcentajeIzq);
  escribirMotorDer(porcentajeDer);
}

/*
 * Velocidad de Motores en cm/s
 * */

void escribirVelMotorIzq(int8_t velMotIzq)
{
}

void escribirVelMotorDer(int8_t velMotDer)
{

}
void escribirVelMotores(int8_t velMotIzq, int8_t velMotDer)
{
}

