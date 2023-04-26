/*==================[inclusiones]============================================*/
#include "sapi_gpio.h"
#include "paragolpes.h"

/*==================[definiciones]===========================================*/

/* PARAGOLPES IZQUIERDO */
#define PARAGOLPES_IZQ				       ENET_RXD0 /* Pin para IRQ por PININT */
#define PARAGOLPES_IZQ_PORT          0  /* Puerto GPIO a mapear PININT: GPIO0 */
#define PARAGOLPES_IZQ_PIN           2  /* Pin GPIO a mapear PININT: GPIO[2] */
#define PARAGOLPES_IZQ_PIN_PORT      1  /* Puerto SCU: P1 */
#define PARAGOLPES_IZQ_PIN_BIT       15 /* Pin SCU: P1_15 */
#define PARAGOLPES_IZQ_MODE_FUNC     SCU_MODE_FUNC0 /* Funci�n del pin para GPIO */
#define PARAGOLPES_IZQ_PININT_INDEX  3  /* Índice de PININT para mapeo de GPIO */
#define PARAGOLPES_IZQ_INTERRUPCION  GPIO3_IRQHandler /* Nombre de ISR PININT */
#define PARAGOLPES_IZQ_PININT_NVIC_NAME PIN_INT3_IRQn /* Fuente de IRQ */

/* PARAGOLPES DERECHO */
#define PARAGOLPES_DER				       ENET_CRS_DV /* Pin para IRQ por PININT */
#define PARAGOLPES_DER_PORT          0	/* Puerto GPIO a mapear PININT: GPIO0 */
#define PARAGOLPES_DER_PIN           3	/* Pin GPIO a mapear PININT: GPIO[3] */
#define PARAGOLPES_DER_PIN_PORT      1	/* Puerto SCU: P1 */
#define PARAGOLPES_DER_PIN_BIT       16	/*  Pin SCU: P1_16 */
#define PARAGOLPES_DER_MODE_FUNC     SCU_MODE_FUNC0 /* Funci�n del pin para GPIO */
#define PARAGOLPES_DER_PININT_INDEX  4	/* Indice de PININT para mapeo de GPIO */
#define PARAGOLPES_DER_INTERRUPCION  GPIO4_IRQHandler  /* Nombre de ISR PININT */
#define PARAGOLPES_DER_PININT_NVIC_NAME PIN_INT4_IRQn /* Fuente de IRQ */

/**
 * Manejadores de Interrupciones por PININT
 */
void PARAGOLPES_IZQ_INTERRUPCION(void);
void PARAGOLPES_DER_INTERRUPCION(void);

/**
 * Punteros a las funciones para callbacks
 */
static void (*ptrParagolpesIzqCback)(void);
static void (*ptrParagolpesDerCback)(void);

/*==================[implementaciones]=======================================*/

/**
 * bool_t iniParagolpes(void)
 *
 * Devuelve valor distinto de 0 solo cuando ambos pines GPIO fueron
 * configurados correctamente como entradas.
 * */
bool_t iniParagolpes(void)
{
  if (gpioConfig(PARAGOLPES_IZQ, GPIO_INPUT) &&
      gpioConfig(PARAGOLPES_DER, GPIO_INPUT))
  {
    return 1;
  }
  return 0;
}

/**
 *
 */

bool_t leerParagolpesIzq(void)

  return gpioRead(PARAGOLPES_IZQ);
}

bool_t leerParagolpesDer(void)
{
  return gpioRead(PARAGOLPES_DER);
}

estadosParagolpes leerParagolpes(void)
{
  return gpioRead(PARAGOLPES_IZQ) + (gpioRead(PARAGOLPES_DER) << 1);
}

uint8_t prenderIntParagolpes(void (*ptrIzq)(void), void (*ptrDer)(void))
{
  Chip_PININT_Init(LPC_GPIO_PIN_INT);

  /* PARAGOLPES IZQUIERDO */
  /* Configurar el canal de interrupci�n en bloque SysCon */
  Chip_SCU_GPIOIntPinSel(PARAGOLPES_IZQ_PININT_INDEX, PARAGOLPES_IZQ_PORT,
      PARAGOLPES_IZQ_PIN);

  /* Configurar interrupci�n para flanco descendente */
  Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_IZQ_PININT_INDEX));
  Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_IZQ_PININT_INDEX));
  Chip_PININT_SetPinModeLevel(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_IZQ_PININT_INDEX));
  Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_IZQ_PININT_INDEX));

  /* Asignaci�n de funci�n de Callback */
  ptrParagolpesIzqCback = ptrIzq;

  /* Habilitar interrupcion en NVIC */
  NVIC_ClearPendingIRQ(PARAGOLPES_IZQ_PININT_NVIC_NAME);
  NVIC_EnableIRQ(PARAGOLPES_IZQ_PININT_NVIC_NAME);

  /* PARAGOLPES DERECHO */
  /* Configurar el canal de interrupci�n en bloque SysCon */
  Chip_SCU_GPIOIntPinSel(PARAGOLPES_DER_PININT_INDEX, PARAGOLPES_DER_PORT,
      PARAGOLPES_DER_PIN);

  /* Configurar interrupci�n para flanco descendente */
  Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_DER_PININT_INDEX));
  Chip_PININT_SetPinModeEdge(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_DER_PININT_INDEX));
  Chip_PININT_SetPinModeLevel(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_DER_PININT_INDEX));
  Chip_PININT_EnableIntHigh(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_DER_PININT_INDEX));

  /* Asignaci�n de funci�n de Callback */
  ptrParagolpesDerCback = ptrDer;

  /* Habilitar interrupcion en NVIC */
  NVIC_ClearPendingIRQ(PARAGOLPES_DER_PININT_NVIC_NAME);
  NVIC_EnableIRQ(PARAGOLPES_DER_PININT_NVIC_NAME);

  return 1;
}

uint8_t apagarIntParagolpes(void)
{
  /* PARAGOLPES IZQUIERDO */
  /* Deshabilitar interrupcion en NVIC */
  NVIC_ClearPendingIRQ(PARAGOLPES_IZQ_PININT_NVIC_NAME);
  NVIC_DisableIRQ(PARAGOLPES_IZQ_PININT_NVIC_NAME);

  /* PARAGOLPES DERECHO */
  /* Deshabilitar interrupcion en NVIC */
  NVIC_ClearPendingIRQ(PARAGOLPES_DER_PININT_NVIC_NAME);
  NVIC_DisableIRQ(PARAGOLPES_DER_PININT_NVIC_NAME);

  return 1;
}

void PARAGOLPES_IZQ_INTERRUPCION(void)
{
  Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_IZQ_PININT_INDEX));

  ptrParagolpesIzqCback();
}

void PARAGOLPES_DER_INTERRUPCION(void)
{
  Chip_PININT_ClearIntStatus(LPC_GPIO_PIN_INT,
      PININTCH(PARAGOLPES_DER_PININT_INDEX));

  ptrParagolpesDerCback();
}

