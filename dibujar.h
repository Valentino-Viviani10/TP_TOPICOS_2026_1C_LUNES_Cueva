#ifndef DIBUJAR_H_INCLUDED
#define DIBUJAR_H_INCLUDED

#include "fuentes.h"
#include "GBT/gbt.h"
#include "tetrominos.h"
#include "juego.h"
#include "tablero.h"
#include "config.h"

#define GROSOR_BORDE 2
#define ESPACIO_ENTRE_SCORES 10

int calcular_x_centrada(const char *palabra, int ancho);

void dibujar_linea_horizontal(int x_ini, int x_fin, int y);

void dibujar_menu(int opcionSeleccionada, int ancho, int alto, uint8_t colorSeleccionado);

void dibujar_fondo(int alto, int ancho, int paleta_id);

void dibujar_borde(int alto, int ancho, int iniX, int iniY);

void dibujar_tetromino(tTetrominoFondo tetromino, int pantalla, int rot, int alto, int ancho);

void dibujar_juego(int ancho, int alto, int** tablero, tPiezaActiva* pieza, int juego_terminado, int marco_x, int marco_y, int lado_bloque);

void dibujar_inst(int ancho, int alto);

void dibujar_puntuacion(int* puntaje, char nombre_jugador[], int lineas, int piezas_caidas, int velocidad_caida_ms, int altoPantalla, int altoJuego, int anchoPantalla, int anchoJuego, tPiezaActiva* pieza_siguiente);

void dibujar_estadisticas(tEstadisticas* stats, int altoPantalla, int altoJuego, int anchoJuego);

void dibujar_inicio_usuario(int ancho, int alto, char *nombre_jugador, int mostrar_error_nombre);

void dibujar_configuracion(int ancho, int alto, const Config *config, int opcionSeleccionada);

int calcular_lado_bloque_juego(int alto);

#endif // DIBUJAR_H_INCLUDED
