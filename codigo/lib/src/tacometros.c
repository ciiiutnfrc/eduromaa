/*==================[inclusiones]=============================================*/
#include "sapi.h"
#include "tacometros.h"

/*==================[definiciones]============================================*/
#define TACOMETRO_GPIO_H  ENET_TXD0
#define TACOMETRO_ON      ON
#define TACOMETRO_OFF     OFF

#define TACOMETRO_CAP_IZQ 3
#define TACOMETRO_CAP_DER 2

#define RUEDA_MAX_RPM    130    // Velocidad nominal del motor
#define DIAMETRO_RUEDAS    6.67 // Diámetro de las ruedas del robot [cm]
#define DIST_ENTRE_RUEDAS 13.25 // Distancia entre los centros de las ruedas
#define CIRCUNF_RUEDAS (DIAMETRO_RUEDAS * 3.1416) // Distancia en giro 360° rueda
#define CIRCUNF_GIRO (DIST_ENTRE_RUEDAS * 3.1416) // Distancia en giro 360° de robot
#define DIST_FLANCOS (CIRCUNF_RUEDAS / 20)

uint32_t frec_timer;
tacometro_t tacometro_izq, tacometro_der;

/*==================[implementacion]==========================================*/
void iniTacometros(void)
{
    /* Configurar GPIO de encendidp/apagado */
    gpioConfig(TACOMETRO_GPIO_H, GPIO_ENABLE);
    gpioConfig(TACOMETRO_GPIO_H, GPIO_OUTPUT);
    gpioWrite(TACOMETRO_GPIO_H, TACOMETRO_OFF);

    /*Configurar pin de Entrada de Captura
     * ETH_TXD1: ENC_DER --> P1_20 - FUNC4 - T0_CAP2
     */
    Chip_SCU_PinMux(0x1, 20, MD_PLN_FAST, SCU_MODE_FUNC4);
    LPC_GIMA->CAP0_IN[0][2] = 0x20;

    /*Configurar pin de Entrada de Captura
     * MDIO: ENC_IZQ --> P1_17 - FUNC4 - T0_CAP3
     */
    Chip_SCU_PinMux(1, 17, MD_PLN_FAST, SCU_MODE_FUNC4);
    /*Ver que Canal 3 de todos los capture se configura distinto!*/
    LPC_GIMA->CAP0_IN[0][3] = 0x10;

    /* Habilitar TIMER0 y Resetearlo */
    Chip_TIMER_Init(LPC_TIMER0);
    Chip_RGU_TriggerReset(RGU_TIMER0_RST);
    while (Chip_RGU_InReset(RGU_TIMER0_RST))
    {
    }

    /* Obtener frecuencia del reloj del TIMER0 */
    frec_timer = Chip_Clock_GetRate(CLK_MX_TIMER0);

    Chip_TIMER_Reset(LPC_TIMER0);
    Chip_TIMER_TIMER_SetCountClockSrc(LPC_TIMER0, TIMER_CAPSRC_RISING_PCLK,
            TACOMETRO_CAP_IZQ);

    Chip_TIMER_ClearCapture(LPC_TIMER0, TACOMETRO_CAP_IZQ);
    Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER0, TACOMETRO_CAP_IZQ);

    Chip_TIMER_ClearCapture(LPC_TIMER0, TACOMETRO_CAP_DER);
    Chip_TIMER_CaptureRisingEdgeEnable(LPC_TIMER0, TACOMETRO_CAP_DER);

    /*Habilitar Interrupciones por captura */
    Chip_TIMER_CaptureEnableInt(LPC_TIMER0, TACOMETRO_CAP_IZQ);
    Chip_TIMER_CaptureEnableInt(LPC_TIMER0, TACOMETRO_CAP_DER);

    /* Habilitar interrupciones del timer */
    NVIC_EnableIRQ(TIMER0_IRQn);
    NVIC_ClearPendingIRQ(TIMER0_IRQn);

    Chip_TIMER_Enable(LPC_TIMER0);
}

void prenderTacometros(void)
{
    gpioWrite(TACOMETRO_GPIO_H, TACOMETRO_ON);
    tacometro_izq.t_flanco_previo = 0;
    tacometro_der.t_flanco_previo = 0;

}

void apagarTacometros(void)
{
    gpioWrite(TACOMETRO_GPIO_H, TACOMETRO_OFF);
}

void leerTacometros(tacometro_t *tacoIzq, tacometro_t * tacoDer)
{
    *tacoIzq = tacometro_izq;
    *tacoDer = tacometro_der;
}

void TIMER0_IRQHandler(void)
{

    if (Chip_TIMER_CapturePending(LPC_TIMER0, TACOMETRO_CAP_IZQ))
    {
        Chip_TIMER_ClearCapture(LPC_TIMER0, TACOMETRO_CAP_IZQ);

        if (tacometro_izq.t_flanco_previo == 0)
        {
            tacometro_izq.t_flanco_previo = Chip_TIMER_ReadCapture(LPC_TIMER0,
                    TACOMETRO_CAP_IZQ);
            tacometro_izq.cuenta = 0;

        } else
        {
            tacometro_izq.t_flanco_previo = tacometro_izq.t_flanco_actual;
            tacometro_izq.t_flanco_actual = Chip_TIMER_ReadCapture(LPC_TIMER0,
                    TACOMETRO_CAP_IZQ);
            tacometro_izq.cuenta++;

            // Si la cuenta actual es menor a la anterior, hubo un desborde del TIMER
            if (tacometro_izq.t_flanco_actual < tacometro_izq.t_flanco_previo)
            {
                // El periodo es igual a lo que faltaba para quedesborde
                // (se obtiene haciendo el complemento a 2) mas el flanco actual
                tacometro_izq.t_flancos = tacometro_izq.t_flanco_actual
                        + (~tacometro_izq.t_flanco_previo) + 1;
            } else
            {
                tacometro_izq.t_flancos = tacometro_izq.t_flanco_actual
                        - tacometro_izq.t_flanco_previo;
            }
        }
    }

    if (Chip_TIMER_CapturePending(LPC_TIMER0, TACOMETRO_CAP_DER))
    {
        Chip_TIMER_ClearCapture(LPC_TIMER0, TACOMETRO_CAP_DER);
        if (tacometro_der.t_flanco_previo == 0)
        {
            tacometro_der.t_flanco_previo = Chip_TIMER_ReadCapture(LPC_TIMER0,
                    TACOMETRO_CAP_DER);
            tacometro_der.cuenta = 0;
        } else
        {
            tacometro_der.t_flanco_previo = tacometro_der.t_flanco_actual;
            tacometro_der.t_flanco_actual = Chip_TIMER_ReadCapture(LPC_TIMER0,
                    TACOMETRO_CAP_DER);
            tacometro_der.cuenta++;

            // Si la cuenta actual es menor a la anterior, hubo un desborde del TIMER
            if (tacometro_der.t_flanco_actual < tacometro_der.t_flanco_previo)
            {
                // El periodo es igual a lo que faltaba para que desborde
                // (se obtiene haciendo el complemento a 2) mas el flanco actual
                tacometro_der.t_flancos = tacometro_der.t_flanco_actual
                        + (~tacometro_der.t_flanco_previo) + 1;
            } else
            {
                tacometro_der.t_flancos = tacometro_der.t_flanco_actual
                        - tacometro_der.t_flanco_previo;
            }
        }
    }
}

