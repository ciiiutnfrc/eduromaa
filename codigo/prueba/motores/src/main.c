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
    prenderMotores();

    while (1)
    {
        /* Prueba PWM hacia atrás */
        escribirPWMMotores(10, 10);
        delay(3000);

        /* Prueba PWM hacia detenido */
        escribirPWMMotores(128, 128); //|+ Vel. cero +|
        delay(3000);

        /* Prueba PWM hacia atrás */
        escribirPWMMotores(250, 250);
        delay(3000);

    }
    return 0;
}
