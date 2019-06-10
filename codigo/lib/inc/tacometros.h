#ifndef _TACOMETRO_H
#define _TACOMETRO_H

/*==================[inclusiones]=============================================*/
#include "sapi.h"

/*==================[definiciones]============================================*/
typedef struct
{
    uint32_t cuenta;
    uint32_t t_flanco_actual;
    uint32_t t_flanco_previo;
    uint32_t t_flancos;
} tacometro_t;

/*==================[protitipos]==============================================*/
void iniTacometros(void);

void prenderTacometros(void);
void apagarTacometros(void);

void leerTacometros(tacometro_t *, tacometro_t *);

#endif
