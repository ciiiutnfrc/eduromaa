/*
 * main.c
 *
 *  Created on: 14 jul. 2019
 *      Author: marti
 */


/*==================[inclusiones]============================================*/

#include "eduromaa.h"
#include "ir_linea.h"

/*==================[definiciones]===========================================*/

/*==================[implementaciones]=======================================*/
int main(void){

   /* ------------- INICIALIZACIONES ------------- */

    /* Variable de Retardo NO bloqueante */
    delay_t retardo_ir;

    /* Variables de configuración de velocidad */
    int8_t vel_alta = 70; //PDG era 80
    int8_t vel_baja = -40; //PDG era 40

    /* Inicializa EduRoMAA */
    iniEduromaa();
    prenderSensoresIR();
    prenderMotores();

   delayInit(&retardo_ir,20); // PDG era 200

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

       if( delayRead( &retardo_ir ) ){

           switch(seguir_linea()){
           case LINEA_ADELANTE:
               gpioWrite(LED1,OFF);
               gpioWrite(LED2,ON);
               gpioWrite(LED3,OFF);
                /* Motores: ambos avanzan a la misma velocidad */
               escribirMotores(vel_alta, vel_alta);
               break;
           case LINEA_GIRAR_DER:
               gpioWrite(LED1,OFF);
               gpioWrite(LED2,OFF);
               gpioWrite(LED3,ON);
                /* Motores: motor izquierdo avanza a mayor velocidad que el derecho */
               escribirMotores(vel_baja, vel_alta);
                break;
           case LINEA_GIRAR_IZQ:
               gpioWrite(LED1,ON);
               gpioWrite(LED2,OFF);
               gpioWrite(LED3,OFF);
                /* Motores: motor derecho avanza a mayor velocidad que el izquierdo */
               escribirMotores(vel_alta, vel_baja);
               break;
           case LINEA_DETENER:
           default:
               gpioWrite(LED1,OFF);
               gpioWrite(LED2,OFF);
               gpioWrite(LED3,OFF);
                /* Motores: ambos motores se detienen */
               escribirMotores(0, 0);

               break;
           }
       }
   }
   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/

