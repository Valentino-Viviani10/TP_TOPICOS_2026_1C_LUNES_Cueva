#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GBT/gbt.h"
#include "font8x8_basic.h"
#include "colores.h"
#include "dibujar.h"
#include "tablero.h"
#include "juego.h"

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



void dibujar_inst(int ancho, int alto) {
    // TODO: Implementar
}

static uint8_t elegir_color_permitido(void) {
    static const uint8_t coloresPermitidos[] = {
        COL_AZUL_BRILL,
        COL_VERDE_BRILL,
        COL_CIAN_BRILL,
        COL_ROJO_BRILL
    };

    return coloresPermitidos[rand() % (sizeof(coloresPermitidos) / sizeof(coloresPermitidos[0]))];
}

int main(int argc, char* argv[])
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    srand((unsigned)time(NULL));

    tablero_inicializar();
    juego_inicializar();

    int ancho = CGA_ANCHO;
    int alto = CGA_ALTO;
    int escala = 2;

    // Validar que se pasen argumentos
    if (argc < 2) {
        fprintf(stderr, "Uso: %s <CGA|VGA> [escala]\n", argv[0]);
        fprintf(stderr, "Ejemplos:\n");
        fprintf(stderr, "  %s CGA\n", argv[0]);
        fprintf(stderr, "  %s VGA\n", argv[0]);
        fprintf(stderr, "  %s CGA 2\n", argv[0]);
        fprintf(stderr, "  %s VGA 3\n", argv[0]);
        return -1;
    }

    // Parsear resolución (argumento obligatorio)
    if (strcmp(argv[1], "VGA") == 0 || strcmp(argv[1], "vga") == 0) {
        ancho = VGA_ANCHO;
        alto = VGA_ALTO;
    } else if (strcmp(argv[1], "CGA") == 0 || strcmp(argv[1], "cga") == 0) {
        ancho = CGA_ANCHO;
        alto = CGA_ALTO;
    } else {
        fprintf(stderr, "Error: Resolucion no valida '%s'. Use CGA o VGA.\n", argv[1]);
        return -1;
    }

    // Parsear escala (argumento opcional)
    if (argc > 2) {
        escala = atoi(argv[2]);

        if (strcmp(argv[1], "VGA") == 0) {
            if(escala > 2 || escala <= 0) {
                fprintf(stderr, "Error: Escala no valida '%s'. Use una escala para VGA de maximo 2 y minimo 1.\n", argv[2]);
                printf("Ajustando escala a 2.\n");
                escala = 2;
            }
        } else if (strcmp(argv[1], "CGA") == 0) {
            if(escala > 4 || escala <= 0) {
                fprintf(stderr, "Error: Escala no valida '%s'. Use una escala para CGA de maximo 4 y minimo 1.\n", argv[2]);
                printf("Ajustando escala a 3.\n");
                escala = 3;
            }
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

    const char titulo[] = "TETRIS";
    const char *opcionJugar = "JUGAR";
    const char *opcionInstrucciones = "INSTRUCCIONES";
    int xTitulo = calcular_x_centrada(titulo, ancho);
    int xJugar = calcular_x_centrada(opcionJugar, ancho);
    int xInstrucciones = calcular_x_centrada(opcionInstrucciones, ancho);

    int menuIzquierdo = xTitulo;
    int menuDerecho = xTitulo + (int)strlen(titulo) * 8;

    if (xJugar < menuIzquierdo) {
        menuIzquierdo = xJugar;
    }
    if (xInstrucciones < menuIzquierdo) {
        menuIzquierdo = xInstrucciones;
    }

    if (xJugar + (int)strlen(opcionJugar) * 8 > menuDerecho) {
        menuDerecho = xJugar + (int)strlen(opcionJugar) * 8;
    }
    if (xInstrucciones + (int)strlen(opcionInstrucciones) * 8 > menuDerecho) {
        menuDerecho = xInstrucciones + (int)strlen(opcionInstrucciones) * 8;
    }

    int anchoTetromino = 4 * TETROMINO_ESCALA;
    int limiteIzquierdoTetrominos = menuIzquierdo - 20 - anchoTetromino;
    int limiteDerechoTetrominos = menuDerecho + 20;

    if (limiteIzquierdoTetrominos < 0) {
        limiteIzquierdoTetrominos = 0;
    }
    if (limiteDerechoTetrominos > ancho - anchoTetromino) {
        limiteDerechoTetrominos = ancho - anchoTetromino;
    }

    tGBT_Temporizador *temporizador = gbt_temporizador_crear(1.0);
    if (!temporizador) {
        fprintf(stderr, "Error al crear el temporizador para los tetrominos: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temp_activar_tetrominos = gbt_temporizador_crear(2.0);
    if (!temp_activar_tetrominos) {
        fprintf(stderr, "Error al crear el temporizador de activación: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temp_caida_tetrominos = gbt_temporizador_crear(0.1);
    if (!temp_caida_tetrominos) {
        fprintf(stderr, "Error al crear el temporizador de caída: %s\n", gbt_obtener_log());
        return -1;
    }

    // Inicializar tetrominos decorativos
    tTetrominoFondo tetrominos_decorativos[4];
    inicializar_tetrominos_fondo(tetrominos_decorativos);

    int corriendo = 1;
    int opcionSeleccionada = 0;
    int pantalla = 0;

    // variable global o que le pases como parametro
    uint8_t colorSeleccionado = COL_AMARILLO;

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

        if(pantalla == 1){
            if(tecla == GBTK_IZQUIERDA){
                juego_mover_izquierda();
            }

            if(tecla == GBTK_DERECHA){
                juego_mover_derecha();
            }
        }
    }

    // Dibujar fondo y bordes
        dibujar_fondo(alto, ancho);
        dibujar_borde(alto, ancho);

        // Lógica según pantalla
        if(pantalla == 0){
            if(tecla == GBTK_ABAJO || tecla == GBTK_ARRIBA) {
                colorSeleccionado = elegir_color_permitido();
            }

            // Actualizar tetrominos decorativos
            actualizar_tetrominos_fondo(tetrominos_decorativos, alto, ancho, limiteIzquierdoTetrominos, limiteDerechoTetrominos, temp_caida_tetrominos, temp_activar_tetrominos);

            // Dibujar menú y tetrominos
            dibujar_menu(opcionSeleccionada, ancho, alto, colorSeleccionado);

            for(int t = 0; t < 4; t++){
                if(tetrominos_decorativos[t].activo){
                    dibujar_tetromino(tetrominos_decorativos[t], 0, tetrominos_decorativos[t].rot, alto, ancho);
                }
            }
        } else if(pantalla == 1){
            dibujar_juego(ancho, alto);
        } else if(pantalla == 2){
            dibujar_inst(ancho, alto);
        }

        gbt_volcar_backbuffer();

        if(pantalla == 1){
            juego_caer();
        }


        gbt_esperar(16);
    }
}
