/*==================[inclusiones]=============================================*/
#include "eduromaa.h"
#include <stdlib.h>

/*==================[definiciones]===========================================*/
char* itoa(int, char* , int);
/*==================[implementaciones]=======================================*/
int main(void) {

    float dist_cm;
    tacometro_t tacoIzq, tacoDer;
    uint16_t ir_izq, ir_der;
    char buffer[5];
    uint16_t cuenta_lin;

    /* Inicializa EduRoMAA */
    iniEduromaa();
    /* Habilita Funcionamiento de Paragolpes por Interrupci�n */
    prenderIntParagolpes(paragolpesIzqInt, paragolpesDerInt);

    cuenta_lin = 0;

    prenderBocina();
    delay(20);
    apagarBocina();
    delay(200);
    prenderBocina();
    delay(20);
    apagarBocina();
    delay(200);
    prenderBocina();
    delay(100);
    apagarBocina();

    prenderSonar();
    prenderTacometros();
    prenderSensoresIR();

    uartWriteString(UART_USB, "\r\nEduRoMAA 0.1: Hola...\r\n");
    prenderMotores();
    escribirMotores(100, 100);
    while (1) {

        delay(1000);
        /* Apagar paragolpes en cada ciclo */
        apagarBocina();
        gpioWrite(LED3, OFF);
        gpioWrite(LED1, OFF);

        leerSonar(&dist_cm);

        if (dist_cm < 5) {
            escribirMotores(0, 0);
            prenderBocina();
        } else if(dist_cm < 10){
            escribirMotores(50, 50);
        } else if (dist_cm < 30){
            escribirMotores(80, 80);
        } else {
            escribirMotores(100, 100);
        }

        leerTacometros(&tacoIzq, &tacoDer);
        actualizarSensoresIR();

        itoa(cuenta_lin++, buffer, 10);
        uartWriteString(UART_USB, buffer);
        uartWriteString(UART_USB, ": ");

        uartWriteString(UART_USB, "S[cm]: ");
        itoa(dist_cm, buffer, 10);
        uartWriteString(UART_USB, buffer);

        uartWriteString(UART_USB, "\tTI: ");
        itoa(tacoIzq.cuenta, buffer, 10);
        uartWriteString(UART_USB, buffer);
        uartWriteString(UART_USB, " TD: ");
        itoa(tacoDer.cuenta, buffer, 10);
        uartWriteString(UART_USB, buffer);

        ir_izq = leerSensorIR(SENSOR_IR_IZQ);
        ir_der = leerSensorIR(SENSOR_IR_DER);
        uartWriteString(UART_USB, "\tII: ");
        itoa(ir_izq, buffer, 10);
        uartWriteString(UART_USB, buffer);

        uartWriteString(UART_USB, " ID: ");
        itoa(ir_der, buffer, 10);
        uartWriteString(UART_USB, buffer);
        uartWriteString(UART_USB, "\r\n");

    }
    return 0;
}

/**
 * Funciones de Manejo de Interrupci�n
 */
void paragolpesIzqInt(void) {
    gpioWrite(LED3, ON);
    escribirMotores(0, 0);
    prenderBocina();
}

void paragolpesDerInt(void) {
    gpioWrite(LED1, ON);
    escribirMotores(0, 0);
    prenderBocina();
}
