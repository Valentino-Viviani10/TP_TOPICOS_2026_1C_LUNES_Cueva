#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#include "tablero.h"
#include "tetrominos.h"

extern int modo_deluxe;

typedef struct {
    int x;          // Posicion X en el tablero 0 a 9
    int y;          // Posicion Y en el tablero 0 a 21
    int tipo;       // Que pieza es (0 a 6)
    int rotacion;   // Estado (0 a 3)
    int color;      // Color
} tPiezaActiva;

typedef struct {
    int piezas_usadas;
    int lineas_por_jugada[5]; // usamos indices 1, 2, 3 y 4 para almacenar las cuatro opciones de eliminar lineas
} tEstadisticas;

typedef struct {
    char nombre_jugador[16];
    int puntaje;
    int piezas_caidas;
    int velocidad_caida_ms;
    int lineas_eliminadas;
    tPiezaActiva pieza_activa;
    tPiezaActiva pieza_siguiente;
    tEstadisticas stats;
    int bolsa_tetrominos[11];
    int indice_bolsa;
} tPartidaGuardada;

void juego_inicializar_pieza(tPiezaActiva* pieza);

void juego_mover_izquierda(tPiezaActiva* pieza, int** tablero);

void juego_mover_derecha(tPiezaActiva* pieza, int** tablero);

void juego_rotar(tPiezaActiva* pieza, int** tablero);

void juego_rotar_izquierda(tPiezaActiva* pieza, int** tablero);

int juego_caer(tPiezaActiva* pieza, int** tablero);

void juego_fijar_pieza(tPiezaActiva* pieza, int** tablero);

int juego_puede_iniciar_pieza(tPiezaActiva* pieza, int** tablero);

void juego_obtener_bolsa(int* bolsa_destino, int* indice_destino);

void juego_cargar_bolsa(const int* bolsa_origen, int indice_origen);

void guardar_partida(int** tablero, int filas, int columnas, const tPartidaGuardada* datos, const char* archivo);

int cargar_partida(int*** tablero_ptr, int* filas_leidas, int* columnas_leidas, tPartidaGuardada* datos, const char* archivo);

#endif // JUEGO_H_INCLUDED
