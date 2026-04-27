#include "dibujar.h"
#include "colores.h"
#include "string.h"

int calcularMitadEjeX(const char *palabra, const int ancho, const int alto);

int calcularMitadEjeX(const char *palabra, const int ancho, const int alto) {
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
    
    int mitadEjeX = calcularMitadEjeX(titulo, ancho, alto);

    y = 20;

    dibujar_texto_8x8(titulo, mitadEjeX, y, COL_GRIS_CLARO);

    y = alto / 2;

    for(int i = 0; i < 2; i++){
        uint8_t color = (i == opcionSeleccionada) ? colorSeleccionado : COL_GRIS_CLARO;
        dibujar_texto_8x8(opciones[i], mitadEjeX, y + i * 20, color);
    }
    
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
    int x, y, g;

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
