#include "dibujar.h"
#include "juego.h"
#include "colores.h"
#include <string.h>
#include <stdio.h>
#include "tablero.h"
#include "fuentes.h"

int calcular_x_centrada(const char *palabra, int ancho) {
    return (ancho - calcular_ancho_texto_5x7(palabra)) / 2;
}

void dibujar_linea_horizontal(int x_ini, int x_fin, int y) {
    for(int x = x_ini; x <= x_fin; x++) {
        gbt_dibujar_pixel(x, y, COL_MAG_BRILL);
    }
}


void dibujar_menu(int opcionSeleccionada, int ancho, int alto, uint8_t colorSeleccionado) {
    int y;

    const char *opciones[3] = {"JUGAR", "INSTRUCCIONES", "CONFIGURACION"};

    const char titulo[] = "TETRIS";

    int xTitulo = calcular_x_centrada(titulo, ancho);
    int xJugar = calcular_x_centrada(opciones[0], ancho);
    int xInstrucciones = calcular_x_centrada(opciones[1], ancho);
    int xConfig = calcular_x_centrada(opciones[2], ancho);

    y = 20;

    dibujar_texto_5x7(titulo, xTitulo, y, COL_VERDE_BRILL);

    y = alto / 2;

    uint8_t colorJugar = (opcionSeleccionada == 0) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorInstrucciones = (opcionSeleccionada == 1) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorConfig = (opcionSeleccionada == 2) ? colorSeleccionado : COL_GRIS_CLARO;

    dibujar_texto_5x7(opciones[0], xJugar, y, colorJugar);
    dibujar_texto_5x7(opciones[1], xInstrucciones, y + 20, colorInstrucciones);
    dibujar_texto_5x7(opciones[2], xConfig, y + 40, colorConfig);

}

void dibujar_fondo(int alto, int ancho) {
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

void dibujar_borde(int alto, int ancho, int iniX, int iniY) {
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

void dibujar_tetromino(tTetrominoFondo tetromino, int pantalla, int rot, int alto, int ancho)
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
    alto_tablero = filas * lado_bloque;

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

    for(fila = 0; fila < filas; fila++){
        for(col = 0; col < columnas; col++){
            color = tablero[fila][col];

            if(color == 0){
                color = COL_NEGRO;
            }

            dibujar_bloque_tablero(marco_x + col * lado_bloque,
                                   marco_y + fila * lado_bloque,
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
                grilla_y = pieza->y + fila;

                if(grilla_x >= 0 && grilla_x < columnas && grilla_y >= 0 && grilla_y < filas){
                    dibujar_bloque_tablero(marco_x + grilla_x * lado_bloque,
                                           marco_y + grilla_y * lado_bloque,
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

void dibujar_puntuacion(int* puntaje, char nombre_jugador[], int lineas, int piezas_caidas, int velocidad_caida_ms, int altoPantalla, int altoJuego, int anchoPantalla, int anchoJuego, tPiezaActiva* pieza_siguiente){

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

void dibujar_inicio_usuario(int ancho, int alto, char *nombre_jugador, int mostrar_error_nombre) {
    dibujar_texto_5x7("INGRESE NOMBRE", calcular_x_centrada("INGRESE NOMBRE", ancho), alto / 2 - 20, COL_VERDE_BRILL);
    dibujar_texto_5x7(nombre_jugador, calcular_x_centrada(nombre_jugador, ancho), alto / 2, COL_AMARILLO);
    dibujar_texto_5x7("ENTER PARA JUGAR", calcular_x_centrada("ENTER PARA JUGAR", ancho), alto / 2 + 20, COL_GRIS_CLARO);

    if(mostrar_error_nombre){
        dibujar_texto_5x7("CARACTER NO SOPORTADO", calcular_x_centrada("CARACTER NO SOPORTADO", ancho), alto / 2 + 32, COL_ROJO_BRILL);
    }
}

void dibujar_configuracion(int ancho, int alto, const Config *config, int opcionSeleccionada) {
    
    static const char *nombres_paleta[] = { "CGA", "RETRO GB", "CYBERPUNK" };
    static const char *nombres_res[]    = { "CGA", "VGA" };

    dibujar_texto_5x7("CONFIGURACION", calcular_x_centrada("CONFIGURACION", ancho), 20, COL_MAGENTA);

    int y = alto / 2;

    // Velocidad
    char buf_vel[20];
    snprintf(buf_vel, sizeof(buf_vel), "< %d MS >", config->velocidad_caida_ms);

    uint8_t col_vel = (opcionSeleccionada == 0) ? COL_AMARILLO : COL_MAGENTA;
    uint8_t col_res = (opcionSeleccionada == 1) ? COL_AMARILLO : COL_MAGENTA;
    uint8_t col_pal = (opcionSeleccionada == 2) ? COL_AMARILLO : COL_MAGENTA;

    dibujar_texto_5x7("VELOCIDAD", calcular_x_centrada("VELOCIDAD", ancho), y - 40, col_vel);
    dibujar_texto_5x7(buf_vel, calcular_x_centrada(buf_vel, ancho), y - 25, COL_VERDE_BRILL);

    // Resolución
    char buf_res[10];
    snprintf(buf_res, sizeof(buf_res), "< %s >", nombres_res[config->resolucion]);

    dibujar_texto_5x7("RESOLUCION", calcular_x_centrada("RESOLUCION", ancho), y, col_res);
    dibujar_texto_5x7(buf_res, calcular_x_centrada(buf_res, ancho), y + 15, COL_VERDE_BRILL);

    // Paleta
    char buf_pal[20];
    snprintf(buf_pal, sizeof(buf_pal), "< %s >", nombres_paleta[config->paleta_id]);

    dibujar_texto_5x7("PALETA", calcular_x_centrada("PALETA", ancho), y + 40, col_pal);
    dibujar_texto_5x7(buf_pal, calcular_x_centrada(buf_pal, ancho), y + 55, COL_VERDE_BRILL);

    dibujar_texto_5x7("ENTER PARA GUARDAR", calcular_x_centrada("ENTER PARA GUARDAR", ancho), y + 80, COL_GRIS_CLARO);
}
