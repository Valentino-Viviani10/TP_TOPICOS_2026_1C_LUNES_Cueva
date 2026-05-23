#include "dibujar.h"
#include "juego.h"
#include "colores.h"
#include <string.h>
#include <stdio.h>
#include "tablero.h"
#include "fuentes.h"


int calcular_x_centrada(const char *palabra, const int ancho) {
    return (ancho - calcular_ancho_texto_5x7(palabra)) / 2;
}

void dibujar_linea_horizontal(const int x_ini, const int x_fin, const int y) {
    for(int x = x_ini; x <= x_fin; x++) {
        gbt_dibujar_pixel(x, y, COL_MAG_BRILL);
    }
}


void dibujar_menu(const int opcionSeleccionada, const int ancho, const int alto, uint8_t colorSeleccionado) {
    int y;

    const char *opciones[2] = {"JUGAR", "INSTRUCCIONES"};

    const char titulo[] = "TETRIS";

    int xTitulo = calcular_x_centrada(titulo, ancho);
    int xJugar = calcular_x_centrada(opciones[0], ancho);
    int xInstrucciones = calcular_x_centrada(opciones[1], ancho);

    y = 20;

    dibujar_texto_5x7(titulo, xTitulo, y, COL_VERDE_BRILL);

    y = alto / 2;

    uint8_t colorJugar = (opcionSeleccionada == 0) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorInstrucciones = (opcionSeleccionada == 1) ? colorSeleccionado : COL_GRIS_CLARO;

    dibujar_texto_5x7(opciones[0], xJugar, y, colorJugar);
    dibujar_texto_5x7(opciones[1], xInstrucciones, y + 20, colorInstrucciones);

}

void dibujar_seleccion_modo(const int opcionSeleccionada, const int ancho, const int alto, uint8_t colorSeleccionado) {
    int y = alto / 2 - 20;
    
    dibujar_texto_5x7("ELEGIR MODO", calcular_x_centrada("ELEGIR MODO", ancho), y - 30, COL_VERDE_BRILL);
    
    uint8_t colorNormal = (opcionSeleccionada == 0) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorDeluxe = (opcionSeleccionada == 1) ? colorSeleccionado : COL_GRIS_CLARO;

    dibujar_texto_5x7("NORMAL", calcular_x_centrada("NORMAL", ancho), y, colorNormal);
    dibujar_texto_5x7("DELUXE", calcular_x_centrada("DELUXE", ancho), y + 20, colorDeluxe);
}

void dibujar_seleccion_alto(const int alto_tablero, const int ancho, const int alto) {
    int y = alto / 2;
    char buffer[20];
    
    dibujar_texto_5x7("ALTO DEL TABLERO", calcular_x_centrada("ALTO DEL TABLERO", ancho), y - 30, COL_VERDE_BRILL);
    
    sprintf(buffer, "< %d >", alto_tablero);
    dibujar_texto_5x7(buffer, calcular_x_centrada(buffer, ancho), y, COL_AMARILLO);
    
    dibujar_texto_5x7("ENTER CONFIRMA", calcular_x_centrada("ENTER CONFIRMA", ancho), y + 30, COL_GRIS_CLARO);
}

void dibujar_fondo(const int alto, const int ancho) {
    int x, y;

    for(y = 0; y < alto; y++) {
        for(x = 0; x < ancho; x++) {
            if((x + y) % 2 == 0) {
                gbt_dibujar_pixel(x, y, COL_NEGRO);
            } else {
                gbt_dibujar_pixel(x, y, COL_GRIS_OSC);
            }
        }
    }
}

void dibujar_borde(const int alto, const int ancho, const int iniX, const int iniY) {
    int x, y;

    for(int g = 0; g < GROSOR_BORDE; g++){
        for(x = iniX; x < ancho; x++){
            gbt_dibujar_pixel(x, iniY + g, COL_AZUL);          // superior
            gbt_dibujar_pixel(x, alto - 1 - g, COL_AZUL); // inferior
        }
        for(y = iniY; y < alto; y++){
            gbt_dibujar_pixel(iniX + g, y, COL_AZUL);          // izquierdo
            gbt_dibujar_pixel(ancho - 1 - g, y, COL_AZUL); // derecho
        }
    }
}

void dibujar_tetromino(tTetrominoFondo tetromino, const int pantalla, const int rot, const int alto, const int ancho)
{
    int pi, pj;
    int escala = TETROMINO_ESCALA;

    // Dibujar la pieza en su posición actual (escalada)
    for (pi = 0; pi < 4; pi++) {
        for (pj = 0; pj < 4; pj++) {
            if (piezas[tetromino.tipo][rot][pi][pj]) {
                int px = tetromino.x + pj * escala;
                int py = tetromino.y + pi * escala;

                // Dibujar bloque 3x3
                for (int dy = 0; dy < escala; dy++) {
                    for (int dx = 0; dx < escala; dx++) {
                        int final_x = px + dx;
                        int final_y = py + dy;

                        // Verificar que está dentro de pantalla
                        if (final_x >= 0 && final_x < ancho && final_y >= 0 && final_y < alto) {
                            gbt_dibujar_pixel(final_x, final_y, tetromino.color);
                        }
                    }
                }
            }
        }
    }
}

int calcular_lado_bloque_juego(int alto)
{
    int lado_bloque;

    lado_bloque = alto / 24;

    if(lado_bloque < 6){
        lado_bloque = 6;
    }

    if(lado_bloque > 20){
        lado_bloque = 20;
    }

    return lado_bloque;
}

void dibujar_bloque_tablero(int x, int y, int color, int lado_bloque)
{
    int dx;
    int dy;

    for(dy = 0; dy < lado_bloque - 1; dy++){
        for(dx = 0; dx < lado_bloque - 1; dx++){
            gbt_dibujar_pixel(x + dx, y + dy, color);
        }
    }
}

void dibujar_marco_tablero(int marco_x, int marco_y, int lado_bloque)
{
    int x;
    int y;
    int ancho_tablero;
    int alto_tablero;

    ancho_tablero = columnas * lado_bloque;
    alto_tablero = (filas - 2) * lado_bloque;

    for(x = marco_x - 1; x <= marco_x + ancho_tablero; x++){
        gbt_dibujar_pixel(x, marco_y - 1, COL_MAG_BRILL);
        gbt_dibujar_pixel(x, marco_y + alto_tablero, COL_MAG_BRILL);
    }

    for(y = marco_y - 1; y <= marco_y + alto_tablero; y++){
        gbt_dibujar_pixel(marco_x - 1, y, COL_MAG_BRILL);
        gbt_dibujar_pixel(marco_x + ancho_tablero, y, COL_MAG_BRILL);
    }
}

void dibujar_tablero(int** tablero, int marco_x, int marco_y, int lado_bloque)
{
    int fila;
    int col;
    int color;

    for(fila = 2; fila < filas; fila++){
        for(col = 0; col < columnas; col++){
            color = tablero[fila][col];

            if(color == 0){
                color = COL_NEGRO;
            }

            dibujar_bloque_tablero(marco_x + col * lado_bloque,
                                   marco_y + (fila - 2) * lado_bloque,
                                   color,
                                   lado_bloque);
        }
    }
}

void dibujar_pieza_activa(tPiezaActiva* pieza, int marco_x, int marco_y, int lado_bloque)
{
    int fila;
    int col;
    int grilla_x;
    int grilla_y;

    for(fila = 0; fila < 4; fila++){
        for(col = 0; col < 4; col++){
            if(piezas[pieza->tipo][pieza->rotacion][fila][col]){
                grilla_x = pieza->x + col;
                if (modo_deluxe) {
                    grilla_x = ((grilla_x % columnas) + columnas) % columnas;
                }
                grilla_y = pieza->y + fila;

                if(grilla_x >= 0 && grilla_x < columnas && grilla_y >= 2 && grilla_y < filas){
                    dibujar_bloque_tablero(marco_x + grilla_x * lado_bloque,
                                           marco_y + (grilla_y - 2) * lado_bloque,
                                           pieza->color,
                                           lado_bloque);
                }
            }
        }
    }
}

void dibujar_mini_pieza(int tipo, int color, int x, int y)
{
    int fila;
    int col;

    for(fila = 0; fila < 4; fila++){
        for(col = 0; col < 4; col++){

            if(piezas[tipo][0][fila][col]){

                dibujar_bloque_tablero(
                    x + (col * 4),
                    y + (fila * 4),
                    color,
                    4
                );
            }
        }
    }
}


void dibujar_juego(int ancho, int alto, int** tablero, tPiezaActiva* pieza, int juego_terminado, int marco_x, int marco_y, int lado_bloque)
{
    dibujar_marco_tablero(marco_x, marco_y, lado_bloque);
    dibujar_tablero(tablero, marco_x, marco_y, lado_bloque);

    if(!juego_terminado){
        dibujar_pieza_activa(pieza, marco_x, marco_y, lado_bloque);
    }

    if(juego_terminado){
    dibujar_texto_5x7("JUEGO TERMINADO", calcular_x_centrada("JUEGO TERMINADO", ancho), alto / 2, COL_ROJO_BRILL);
    dibujar_texto_5x7("ENTER REINICIA", calcular_x_centrada("ENTER REINICIA", ancho), alto / 2 + 12, COL_GRIS_CLARO);
    dibujar_texto_5x7("ESC PARA SALIR", calcular_x_centrada("ESC PARA SALIR", ancho), alto / 2 + 24, COL_GRIS_CLARO);
    }
}

void dibujar_puntuacion(int* puntaje, const char nombre_jugador[], int lineas, int piezas_caidas, int velocidad_caida_ms, int altoPantalla, int altoJuego, int anchoPantalla, int anchoJuego, tPiezaActiva* pieza_siguiente){

    int margen = 10;
    int iniX = anchoJuego + margen;
    int finX = anchoPantalla - margen;
    int maxY = altoPantalla - margen;
    int y = margen + 5;
    int iniPal = iniX + 10;


    char bufferPuntaje[20];
    char bufferLineas[20];
    char bufferCaida[20];
    char bufferPiezas[20];

    sprintf(bufferPuntaje, "%07d", *puntaje);
    sprintf(bufferLineas, "%03d", lineas);
    sprintf(bufferCaida, "%04dMS", velocidad_caida_ms);
    sprintf(bufferPiezas, "%03d", piezas_caidas);

    dibujar_borde(maxY, finX, iniX, margen);

    // JUGADOR
    dibujar_texto_5x7("JUGADOR", iniPal, y, COL_AMARILLO);
    dibujar_texto_5x7(nombre_jugador, iniPal, y + 10, COL_AMARILLO);

    // PUNTAJE
    dibujar_texto_5x7("PUNTAJE", iniPal, y + 25, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferPuntaje, iniPal, y + 35, COL_VERDE_BRILL);

    // LINEAS
    dibujar_texto_5x7("LINEAS", iniPal, y + 53, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferLineas, iniPal, y + 63, COL_VERDE_BRILL);

    // CAIDA
    dibujar_texto_5x7("VEL-CAIDA", iniPal, y + 75, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferCaida, iniPal, y + 85, COL_VERDE_BRILL);

    // PIEZAS CAIDAS
    dibujar_texto_5x7("TETROMINOS", iniPal, y + 100, COL_VERDE_BRILL);
    dibujar_texto_5x7("UTILIZADOS", iniPal, y + 110, COL_VERDE_BRILL);
    dibujar_texto_5x7(bufferPiezas, iniPal, y + 120, COL_VERDE_BRILL);

    // SIGUIENTE PIEZA
    dibujar_texto_5x7("SIGUIENTE", iniPal, y + 140, COL_AMARILLO);
    dibujar_texto_5x7("PIEZA", iniPal, y + 150, COL_AMARILLO);

    for(int fila = 0; fila < 4; fila++){
        for(int col = 0; col < 4; col++){
            if(piezas[pieza_siguiente->tipo][0][fila][col]){
                dibujar_bloque_tablero(iniPal + 10 + col * 5, y + 163 + fila * 5, pieza_siguiente->color, 5);
            }
        }
    }
}

void dibujar_estadisticas(tEstadisticas* stats, int altoPantalla, int altoJuego, int anchoJuego){

    int margen = 10;
    int iniX = margen;
    int finX = anchoJuego - margen;
    int maxY = altoPantalla - margen;
    int y = margen + 8;
    int iniPal = iniX + 10;

    char buffer[25];

    dibujar_borde(maxY, finX, iniX, margen);

    dibujar_texto_5x7("ESTADISTICAS", iniPal, y, COL_VERDE_BRILL);

    dibujar_texto_5x7("TETROMINOS", iniPal, y + 22, COL_AMARILLO);
    dibujar_texto_5x7("USADOS", iniPal, y + 32, COL_AMARILLO);

    sprintf(buffer, "%03d", stats->piezas_usadas);
    dibujar_texto_5x7(buffer, iniPal, y + 45, COL_GRIS_CLARO);

    dibujar_texto_5x7("LINEAS ELIM", iniPal, y + 68, COL_VERDE_BRILL);

    dibujar_texto_5x7("1 LINEA", iniPal, y + 88, COL_GRIS_CLARO);
    sprintf(buffer, "%03d", stats->lineas_por_jugada[1]);
    dibujar_texto_5x7(buffer, iniPal + 60, y + 88, COL_GRIS_CLARO);

    dibujar_texto_5x7("2 LINEAS", iniPal, y + 108, COL_GRIS_CLARO);
    sprintf(buffer, "%03d", stats->lineas_por_jugada[2]);
    dibujar_texto_5x7(buffer, iniPal + 60, y + 108, COL_GRIS_CLARO);

    dibujar_texto_5x7("3 LINEAS", iniPal, y + 128, COL_GRIS_CLARO);
    sprintf(buffer, "%03d", stats->lineas_por_jugada[3]);
    dibujar_texto_5x7(buffer, iniPal + 60, y + 128, COL_GRIS_CLARO);

    dibujar_texto_5x7("4 LINEAS", iniPal, y + 148, COL_GRIS_CLARO);
    sprintf(buffer, "%03d", stats->lineas_por_jugada[4]);
    dibujar_texto_5x7(buffer, iniPal + 60, y + 148, COL_GRIS_CLARO);
}
