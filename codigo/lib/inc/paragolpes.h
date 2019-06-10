#ifndef _PARAGOLPES_H
#define _PARAGOLPES_H

/*==================[inclusiones]============================================*/
#include "sapi.h"
//#include "chip.h"
#include "board.h"

/*==================[definiciones]===========================================*/
typedef enum
{
    LIBRE, GOLPE_IZQ, GOLPE_DER, GOLPE_AMBOS
} estadosParagolpes;

/*==================[protitipos]=============================================*/

bool_t iniParagolpes(void);

bool_t leerParagolpesIzq(void);
bool_t leerParagolpesDer(void);

estadosParagolpes leerParagolpes(void);

uint8_t prenderIntParagolpes(void (*ptrIzq)(void), void (*ptrDer)(void));
uint8_t apagarIntParagolpes(void);

void paragolpesIzqInt(void);
void paragolpesDerInt(void);

#endif /* _PARAGOLPES_H */

