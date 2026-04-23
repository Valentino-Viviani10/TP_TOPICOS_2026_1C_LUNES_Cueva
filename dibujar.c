#include "dibujar.h"

void dibujar_texto(const char *texto, uint16_t x, uint16_t y, uint8_t color) {
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
