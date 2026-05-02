#ifndef DIBUJAR_H_INCLUDED
#define DIBUJAR_H_INCLUDED

#include "font8x8_basic.h"
#include "GBT/gbt.h"
#include "tetrominos.h"
#include "juego.h"

#define GROSOR_BORDE 2

int calcular_x_centrada(const char *palabra, const int ancho);

void dibujar_linea_horizontal(const int x_ini, const int x_fin, const int y);

void dibujar_texto_8x8(const char *texto, uint16_t x, uint16_t y, uint8_t color);

void dibujar_menu(const int opcionSeleccionada, const int ancho, const int alto, uint8_t colorSeleccionado);

void dibujar_fondo(const int alto, const int ancho);

void dibujar_borde(const int alto, const int ancho);

void dibujar_tetromino(tTetrominoFondo tetromino, const int pantalla, const int rot, const int alto, const int ancho);

void dibujar_juego(int ancho, int alto,int** tablero, tPiezaActiva* pieza);

void dibujar_marco_juego();

void dibujar_inst(int ancho, int alto);
#endif // DIBUJAR_H_INCLUDED
