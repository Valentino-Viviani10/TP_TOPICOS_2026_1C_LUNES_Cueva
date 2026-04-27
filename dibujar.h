#ifndef DIBUJAR_H_INCLUDED
#define DIBUJAR_H_INCLUDED

#include "font8x8_basic.h"
#include "GBT/gbt.h"

#define GROSOR_BORDE 2

void dibujar_texto_8x8(const char *texto, uint16_t x, uint16_t y, uint8_t color);

void dibujar_menu(const int opcionSeleccionada, const int ancho, const int alto, uint8_t colorSeleccionado);

void dibujar_fondo(const int alto, const int ancho);

void dibujar_borde(const int alto, const int ancho);

#endif // DIBUJAR_H_INCLUDED
