#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include "font8x8_basic.h"

#define CANT_COLORES 18
#define CGA_ANCHO 320
#define CGA_ALTO 200
#define VGA_ANCHO 640
#define VGA_ALTO 480
#define ESCALA_VENTANA 5

/*
    Apellido: Viviani, Valentino
    DNI: 46582790
    Usuario: Valentino-Viviani10
    Entrega: Si

    Apellido: Bestene, Valentin Ezequiel
    DNI: 42201972
    Usuario: valengap
    Entrega: Si

    Apellido: Fernandez, Sergio Gabriel
    DNI: 28007021
    Usuario: sergiogfernandez-dev
    Entrega: Si
*/

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {

    /// 0-17: Colores CGA (18 colores)
    {0x00, 0x00, 0x00}, // 0:   Negro
    {0x00, 0x00, 0xAA}, // 1:   Azul
    {0x00, 0xAA, 0x00}, // 2:   Verde
    {0x00, 0xAA, 0xAA}, // 3:   Cian
    {0xAA, 0x00, 0x00}, // 4:   Rojo
    {0xAA, 0x00, 0xAA}, // 5:   Magenta
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13:  Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}, // 15:  Usado como transparente por GBT
    {0xFF, 0x80, 0x00}, // 16:  Naranja
    {0x4C, 0x28, 0x82} // 17:   Purpura
};

int main(int argc, char* argv[])
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    int ancho = CGA_ANCHO;
    int alto = CGA_ALTO;

    if (argc > 1) {
        if (strcmp(argv[1], "VGA") == 0) {
            ancho = VGA_ANCHO;
            alto = VGA_ALTO;
        }
    }

    char nombreVentana[50];
    sprintf(nombreVentana, "TETRIS - %dx%d", ancho, alto);

    if(gbt_crear_ventana(nombreVentana, ancho, alto, ESCALA_VENTANA) != 0)
    {
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    if (gbt_aplicar_paleta(paletaCGA, CANT_COLORES, GBT_FORMATO_888) != 0) {
        fprintf(stderr, "Error al aplicar la nueva paleta de colores: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(1.0);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador para los tetrominos: %s\n", gbt_obtener_log());
        return -1;
    }
}
