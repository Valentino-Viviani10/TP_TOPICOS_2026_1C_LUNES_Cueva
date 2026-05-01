#include "dibujar.h"
#include "juego.h"
#include "colores.h"
#include "string.h"

int calcular_x_centrada(const char *palabra, const int ancho) {
    return (ancho - strlen(palabra) * 8) / 2;
}


void dibujar_texto_8x8(const char *texto, uint16_t x, uint16_t y, uint8_t color) {
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        for (int fila = 0; fila < 8; fila++) {
            for (int col = 0; col < 8; col++) {
                if (font8x8_basic[(int)c][fila] & (1 << col)) {
                    gbt_dibujar_pixel(x + i*8 + col, y + fila, color);
                }
            }
        }
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

    dibujar_texto_8x8(titulo, xTitulo, y, COL_VERDE_BRILL);

    y = alto / 2;

    uint8_t colorJugar = (opcionSeleccionada == 0) ? colorSeleccionado : COL_GRIS_CLARO;
    uint8_t colorInstrucciones = (opcionSeleccionada == 1) ? colorSeleccionado : COL_GRIS_CLARO;

    dibujar_texto_8x8(opciones[0], xJugar, y, colorJugar);
    dibujar_texto_8x8(opciones[1], xInstrucciones, y + 20, colorInstrucciones);

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

void dibujar_borde(const int alto, const int ancho) {
    int x, y;

    for(int g = 0; g < GROSOR_BORDE; g++){
        for(x = 0; x < ancho; x++){
            gbt_dibujar_pixel(x, g, COL_AZUL);          // superior
            gbt_dibujar_pixel(x, alto - 1 - g, COL_AZUL); // inferior
        }
        for(y = 0; y < alto; y++){
            gbt_dibujar_pixel(g, y, COL_AZUL);          // izquierdo
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


void dibujar_juego(int ancho, int alto)
{
    tTetrominoFondo tetromino;
    tetromino.x = juego_obtener_x();
    tetromino.y = juego_obtener_y();
    tetromino.tipo = 0;
    tetromino.rot = 0;
    tetromino.activo = 1;
    tetromino.color = COL_CIAN;

    dibujar_tetromino(tetromino, 1, tetromino.rot, alto, ancho);
}
