/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "motores.h"

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void)
{

	/* Inicializa EduCIAA */
	boardConfig();

	/* Inicializa Motores */
	iniMotores();


	while(1){
		/* Prueba PWM hacia atrás */
		prenderMotores();

		escribirPWMMotores(120, 120);
		delay(1000);
		escribirPWMMotores(100, 100);
		delay(1000);
		escribirPWMMotores(80, 80);
		delay(1000);
		escribirPWMMotores(60, 60);
		delay(1000);
		escribirPWMMotores(40, 40);
		delay(1000);
		escribirPWMMotores(20, 20);
		delay(2000);


		/* Prueba PWM hacia detenido */
		escribirPWMMotores(128, 128); //|+ Vel. cero +|
		delay(2000);


		/* Prueba PWM hacia atrás */
		escribirPWMMotores(140, 140);
		delay(2000);
		escribirPWMMotores(160, 160);
		delay(1000);
		escribirPWMMotores(180, 180);
		delay(1000);
		escribirPWMMotores(200, 200);
		delay(1000);
		escribirPWMMotores(240, 240);
		delay(1000);
		apagarMotores();
		delay(1000);
	}
	return 0;
}
