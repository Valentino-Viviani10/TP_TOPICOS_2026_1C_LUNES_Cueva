#include <stdio.h>
#include <stdlib.h>
#include "GBT/gbt.h"
#include "font8x8_basic.h"
#include "colores.h"
#include "dibujar.h"

#define CGA_ANCHO 320
#define CGA_ALTO 200
#define VGA_ANCHO 640
#define VGA_ALTO 480

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

int main(int argc, char* argv[])
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    int ancho = CGA_ANCHO;
    int alto = CGA_ALTO;
    int escala = 3;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0 && i+1 < argc) {
            if (strcmp(argv[i+1], "VGA") == 0) {
                ancho = VGA_ANCHO;
                alto = VGA_ALTO;
            }
        } else if (strcmp(argv[i], "-e") == 0 && i+1 < argc) {
            escala = atoi(argv[i+1]);
            if (escala <= 0) escala = 3;
        }
    }

    char nombreVentana[50];
    sprintf(nombreVentana, "TETRIS - %dx%d", ancho, alto);

    if(gbt_crear_ventana(nombreVentana, ancho, alto, escala) != 0){
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

    int corriendo = 1;
    int offsetX, offsetY;
    int opcionSeleccionada = 0;
    int pantalla = 0;

    // variable global o que le pases como parametro
    uint8_t colorSeleccionado = COL_AMARILLO;

    // cuando el usuario presiona ARRIBA o ABAJO en el main

    while(corriendo){
        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        if(tecla == GBTK_ESCAPE){

            corriendo = 0;
            printf("Saliendo del juego.\n");
        } else if (tecla != GBTK_DESCONOCIDA){
            if(pantalla == 0){
                if(tecla == GBTK_ABAJO){
                    opcionSeleccionada = 1;
                }

                if(tecla == GBTK_ARRIBA){
                    opcionSeleccionada = 0;
                }

                if(tecla == GBTK_ENTER){
                    if(opcionSeleccionada == 0){
                        pantalla = 1;
                    } else if(opcionSeleccionada == 1){
                        pantalla = 2;
                    }
                }
            }

        }

        dibujar_fondo(alto, ancho);

        dibujar_borde(alto, ancho);

        if(tecla == GBTK_ABAJO || tecla == GBTK_ARRIBA){
            colorSeleccionado = rand() % CANT_COLORES;
        }

        if(pantalla == 0){
            dibujar_menu(opcionSeleccionada, ancho, alto, colorSeleccionado);
        } else if(pantalla == 1){
            dibujar_juego(ancho, alto);
        } else if(pantalla == 2){
            dibujar_inst(ancho, alto);
        }

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }
}
