#ifndef FUENTES_7X9_H_INCLUDED
#define FUENTES_7X9_H_INCLUDED

#include <stdint.h>

#define F79_ALTO    9
#define F79_ESPACIO 1

void dibujar_texto_7x9(const char texto[], uint16_t x, uint16_t y, uint8_t color);

int calcular_ancho_texto_7x9(const char texto[]);

#endif // FUENTES_7X9_H_INCLUDED
