#ifndef COLORES_H_INCLUDED
#define COLORES_H_INCLUDED
#include "GBT/gbt.h"

#define CANT_COLORES 18

#define COL_NEGRO       0
#define COL_AZUL        1
#define COL_VERDE       2
#define COL_CIAN        3
#define COL_ROJO        4
#define COL_MAGENTA     5
#define COL_MARRON      6
#define COL_GRIS_CLARO  7
#define COL_GRIS_OSC    8
#define COL_AZUL_BRILL  9
#define COL_VERDE_BRILL 10
#define COL_CIAN_BRILL  11
#define COL_ROJO_BRILL  12
#define COL_MAG_BRILL   13
#define COL_AMARILLO    14
#define COL_PURPURA     15
#define COL_NARANJA     16
#define COL_TRANSPAR    17

// Colores semánticos — cambian según paleta
extern uint8_t COL_SEM_TEXTO_PRINCIPAL;
extern uint8_t COL_SEM_TEXTO_SECUNDARIO;
extern uint8_t COL_SEM_TEXTO_IMPORTANTE;
extern uint8_t COL_SEM_BORDE;
extern uint8_t COL_SEM_ACENTO;
extern uint8_t COL_SEM_FONDO_1;
extern uint8_t COL_SEM_FONDO_2;

extern tGBT_ColorRGB paletaCGA[CANT_COLORES];

extern tGBT_ColorRGB paletaRetroGB[CANT_COLORES];

extern tGBT_ColorRGB paletaCyberpunk[CANT_COLORES];

void inicializar_colores_semanticos(int paleta_id);

#endif // COLORES_H_INCLUDED
