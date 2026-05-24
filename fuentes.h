#ifndef FUENTES_H_INCLUDED
#define FUENTES_H_INCLUDED

#include <stdint.h>
#include "fuentes_7x9.h"

#define FUENTE_ANCHO 5
#define FUENTE_ALTO 7
#define FUENTE_ESPACIO 1
#define FUENTE_AVANCE (FUENTE_ANCHO + FUENTE_ESPACIO)

void dibujar_texto_5x7(const char texto[], uint16_t x, uint16_t y, uint8_t color);

int calcular_ancho_texto_5x7(const char texto[]);

#endif // FUENTES_H_INCLUDED
