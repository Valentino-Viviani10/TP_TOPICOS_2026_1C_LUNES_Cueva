#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "GBT/gbt.h"
#include "colores.h"
#include "dibujar.h"
#include "tablero.h"
#include "juego.h"
#include "instrucciones.h"
#include "puntuaciones.h"

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

static void fijar_y_nueva_pieza(tPiezaActiva *pieza, tPiezaActiva *pieza_siguiente, tEstadisticas *stats, int *puntaje, int **tablero, int *casillasManuales, int *juego_terminado, int *piezas_caidas, int *velocidad_caida_ms, tGBT_Temporizador **temp_juego_caida, int *lineas_eliminadas){

    juego_fijar_pieza(pieza, tablero);
    stats->piezas_usadas++;

    int filasElim = borrar_lineas(tablero, filas, columnas);
    if(filasElim >= 1 && filasElim <= 4){
        stats->lineas_por_jugada[filasElim]++;
    }
    sumar_puntos(filasElim, *casillasManuales, puntaje, (*piezas_caidas) / 10);
    *lineas_eliminadas += filasElim;
    *casillasManuales = 0;

    (*piezas_caidas)++;

    if((*piezas_caidas) % 10 == 0){

        *velocidad_caida_ms = ((*velocidad_caida_ms * 97) + 50) / 100;
        gbt_temporizador_destruir(*temp_juego_caida);
        *temp_juego_caida = gbt_temporizador_crear(*velocidad_caida_ms / 1000.0);
        printf("Velocidad actual: %d ms\n", *velocidad_caida_ms);
    }

    *pieza = *pieza_siguiente;
    juego_inicializar_pieza(pieza_siguiente);

    if(!juego_puede_iniciar_pieza(pieza, tablero)){
        *juego_terminado = 1;
        remove("partida_guardada.bin");
    }
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

static void reiniciar_partida(int **tablero, tPiezaActiva *pieza, tPiezaActiva *pieza_siguiente, tEstadisticas *stats, int *puntaje, int *piezas_caidas, int *velocidad_caida_ms, int *lineas_eliminadas, int *casillasManuales, int *juego_terminado, tGBT_Temporizador **temp_juego_caida) {

        int fila;
        int col;
        for(fila = 0; fila < filas; fila++){
            for(col = 0; col < columnas; col++){
                tablero[fila][col] = 0;
            }
        }
        *puntaje = 0;
        *piezas_caidas = 0;
        *velocidad_caida_ms = 1000;
        *lineas_eliminadas = 0;
        *casillasManuales = 0;
        *juego_terminado = 0;
        stats->piezas_usadas = 0;
        for(int i = 0; i < 5; i++){
            stats->lineas_por_jugada[i] = 0;
        }

        gbt_temporizador_destruir(*temp_juego_caida);
        *temp_juego_caida = gbt_temporizador_crear(1.0);
        juego_inicializar_pieza(pieza);
        juego_inicializar_pieza(pieza_siguiente);
}

static int caracter_soportado(eGBT_Tecla tecla){

    return (tecla >= GBTK_a && tecla <= GBTK_z) || (tecla >= GBTK_0 && tecla <= GBTK_9) || tecla == GBTK_ESPACIO || tecla == GBTK_MENOS;
}

static char convertir_caracter_nombre(eGBT_Tecla tecla)
{
    if(tecla >= GBTK_a && tecla <= GBTK_z){
        return tecla - 32; //convierte lo que el usuario tipea en minúscula a mayúscula
    }

    return tecla;
}

static int guardar_config(int *velocidad_caida_ms, int *paleta_id, int *res, int *escala, char *nomArch) {
    int resolucion[2] = { *res, *escala };

    FILE* arch = fopen(nomArch, "wb");
    if (!arch) return 0;

    if (fwrite(velocidad_caida_ms, sizeof(int), 1, arch) != 1) { fclose(arch); return 0; }
    if (fwrite(paleta_id, sizeof(int), 1, arch) != 1) { fclose(arch); return 0; }
    if (fwrite(resolucion, sizeof(int), 2, arch) != 2) { fclose(arch); return 0; }

    fclose(arch);
    return 1;
}

static int cargar_config(int *velocidad_caida_ms, int *paleta_id, int *res, int *escala, char *nomArch) {
    FILE* arch = fopen(nomArch, "rb");
    if (!arch) return 0;

    if (fread(velocidad_caida_ms, sizeof(int), 1, arch) != 1) { 
        fclose(arch); 
        return 0; 
    }
    if (fread(paleta_id, sizeof(int), 1, arch) != 1) { 
        fclose(arch); 
        return 0; 
    }

    int resolucion[2];
    if (fread(resolucion, sizeof(int), 2, arch) != 2) { 
        fclose(arch); 
        return 0; 
    }

    *res = resolucion[0];
    *escala = resolucion[1];

    fclose(arch);
    return 1;
}

int main()
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    srand((unsigned)time(NULL));

    int ancho = CGA_ANCHO;
    int alto = CGA_ALTO;
    int escala = 2;
    int velocidad_caida_ms = 1000;
    int paleta_id = 1;



    char nombreVentana[50];
    snprintf(nombreVentana, sizeof(nombreVentana), "TETRIS - %dx%d", ancho, alto);

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
    const char *opcionConfig = "CONFIGURACION";
    int xTitulo = calcular_x_centrada(titulo, ancho);
    int xJugar = calcular_x_centrada(opcionJugar, ancho);
    int xInstrucciones = calcular_x_centrada(opcionInstrucciones, ancho);
    int xConfig = calcular_x_centrada(opcionConfig, ancho);

    int menuIzquierdo = xTitulo;
    // int menuDerecho = xTitulo + (int)strlen(titulo) * 8; //
    int menuDerecho = xTitulo + calcular_ancho_texto_5x7(titulo);

    if (xJugar < menuIzquierdo) {
        menuIzquierdo = xJugar;
    }
    if (xInstrucciones < menuIzquierdo) {
        menuIzquierdo = xInstrucciones;
    }

    if(xConfig < menuIzquierdo) {
        menuIzquierdo = xConfig;
    }

    if (xJugar + calcular_ancho_texto_5x7(opcionJugar) > menuDerecho) {
        menuDerecho = xJugar + calcular_ancho_texto_5x7(opcionJugar);
    }

    if (xInstrucciones + calcular_ancho_texto_5x7(opcionInstrucciones) > menuDerecho) {
        menuDerecho = xInstrucciones + calcular_ancho_texto_5x7(opcionInstrucciones);
    }

    if(xConfig + calcular_ancho_texto_5x7(opcionConfig) > menuDerecho) {
        menuDerecho = xConfig + calcular_ancho_texto_5x7(opcionConfig);
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

    tGBT_Temporizador *temp_juego_caida = gbt_temporizador_crear(1.0);
    if (!temp_juego_caida) {
        fprintf(stderr, "Error al crear el temporizador de caída de juego: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temp_movimiento_lateral = gbt_temporizador_crear(0.25);
    if (!temp_movimiento_lateral) {
        fprintf(stderr, "Error al crear el temporizador de movimiento lateral: %s\n", gbt_obtener_log());
        return -1;
    }

    tGBT_Temporizador *temp_caida_rapida = gbt_temporizador_crear(0.07);
    if (!temp_caida_rapida) {
        fprintf(stderr, "Error al crear el temporizador de movimiento abajo: %s\n", gbt_obtener_log());
        return -1;
    }

    // Inicializar tetrominos decorativos
    tTetrominoFondo tetrominos_decorativos[4];
    inicializar_tetrominos_fondo(tetrominos_decorativos);

    int corriendo = 1;
    int opcionSeleccionada = 0;
    int pantalla = 0;
    int juego_terminado = 0;
    int juego_pausado = 0;

    char nombre_jugador[16] = "";
    int largo_nombre = 0;
    int mostrar_error_nombre = 0;

    int puntaje = 0;
    int piezas_caidas = 0;
    int lineas_eliminadas = 0;
    int casillasManuales = 0;
    tEstadisticas stats = {0};
    int lado_bloque = calcular_lado_bloque_juego(alto);
    int marco_x = (ancho / 2) - ((columnas * lado_bloque) / 2);
    int marco_y = (alto / 2) - ((filas * lado_bloque) / 2);
    int fin_tablero_x = marco_x + (columnas * lado_bloque);
    int fin_tablero_y = marco_y + (filas * lado_bloque);
    static int sostenida_activa = 0;
    static int cooldown_lateral = 0;
    static int das_activo = 0;  // 1 = ya pasó el DAS inicial, auto-repeat activo

    uint8_t colorSeleccionado = COL_AMARILLO;

    //creacion de tablero de juego
    int** tablero = crear_tablero(filas, columnas, sizeof(int));
    if (!tablero) {
        return -1;
    }
    
    // Intentar cargar partida guardada
    if(cargar_tablero(tablero, filas, columnas, "partida_guardada.bin")) {
        printf("Partida guardada cargada exitosamente.\n");
    }
    tPiezaActiva pieza_activa;
    juego_inicializar_pieza(&pieza_activa);

    tPiezaActiva pieza_siguiente;
    juego_inicializar_pieza(&pieza_siguiente);

    while(corriendo) {

        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        //MENU
        if(tecla == GBTK_ESCAPE && (pantalla == 1 || pantalla == 0)) {
            if(pantalla == 1 && !juego_terminado){
                guardar_tablero(tablero, filas, columnas, "partida_guardada.bin");
                printf("Partida guardada exitosamente.\n");
            }
            corriendo = 0;
            printf("Saliendo del juego.\n");
        }
        else if (tecla == GBTK_ESCAPE && (pantalla == 2 || pantalla == 4)) {
            pantalla = 0;
            printf("Volviendo al menu principal.\n");
        }
        else if (tecla != GBTK_DESCONOCIDA) {
            if(pantalla == 1 && juego_terminado && tecla == GBTK_ENTER){
                reiniciar_partida(tablero, &pieza_activa, &pieza_siguiente, &stats, &puntaje, &piezas_caidas, &velocidad_caida_ms, &lineas_eliminadas, &casillasManuales, &juego_terminado, &temp_juego_caida);
            }
            if(pantalla == 0){
                if(tecla == GBTK_ABAJO){
                    opcionSeleccionada = (opcionSeleccionada + 1) % 3;
                }
                if(tecla == GBTK_ARRIBA){
                    opcionSeleccionada = (opcionSeleccionada + 2) % 3;
                }
                if(tecla == GBTK_ENTER){
                    if(opcionSeleccionada == 0) {
                        pantalla = 3;
                        tecla = GBTK_DESCONOCIDA;
                        mostrar_error_nombre = 0;
                    }
                    else if(opcionSeleccionada == 1) {
                        pantalla = 2;
                    }
                    else if(opcionSeleccionada == 2) {
                        pantalla = 4;
                    }
                }
            }
            //JUEGO
            if(pantalla == 1 && !juego_terminado){
                if(tecla == GBTK_p){
                    juego_pausado = !juego_pausado;
                }

                if(!juego_pausado){
                    if(tecla == GBTK_r || tecla == GBTK_ARRIBA){
                        juego_rotar(&pieza_activa, tablero);
                    }
                    if(tecla == GBTK_q){
                        juego_rotar_izquierda(&pieza_activa, tablero);
                    }
                }
                //cheat
                if(!juego_pausado && (tecla >= GBTK_1 && tecla <= GBTK_9)){
                    int indice_fila = filas - (tecla - '0');
                    if(indice_fila >= 0) {
                        eliminar_fila_y_bajar(tablero, indice_fila, columnas);
                    }
                }
            }

            if(pantalla == 3){

                if(tecla == GBTK_ENTER){

                    if(largo_nombre == 0){
                        strcpy(nombre_jugador, "ANONIMO");
                        largo_nombre = 8;
                    }

                    mostrar_error_nombre = 0;
                    pantalla = 1;
                }
                else if(tecla == GBTK_RETROCESO && largo_nombre > 0){

                    largo_nombre--;
                    nombre_jugador[largo_nombre] = '\0';
                    mostrar_error_nombre = 0;
                }
                else if(caracter_soportado(tecla) && largo_nombre < 15){

                    nombre_jugador[largo_nombre] = convertir_caracter_nombre(tecla);
                    largo_nombre++;
                    nombre_jugador[largo_nombre] = '\0';
                    mostrar_error_nombre = 0;
                }
                else if(tecla != GBTK_DESCONOCIDA){
                    mostrar_error_nombre = 1;
                }
            }
        }

        if(pantalla == 1 && !juego_terminado && !juego_pausado){

            int izq = gbt_tecla_sostenida(GBTK_IZQUIERDA);
            int der = gbt_tecla_sostenida(GBTK_DERECHA);

            if (cooldown_lateral > 0) {
                cooldown_lateral--;
            }

            if (izq || der) {
                if (cooldown_lateral == 0) {
                    if (izq) juego_mover_izquierda(&pieza_activa, tablero);
                    if (der) juego_mover_derecha(&pieza_activa, tablero);

                    if (!das_activo) {
                        // Primera pulsación o DAS delay: ~192ms (12 frames * 16ms)
                        cooldown_lateral = 12;
                        das_activo = 1;
                    } else {
                        // Auto-repeat: ~48ms (3 frames * 16ms)
                        cooldown_lateral = 3;
                    }
                }
            } else {
                // Tecla soltada: resetear DAS
                cooldown_lateral = 0;
                das_activo = 0;
            }

            if(tecla == GBTK_ABAJO) {
                sostenida_activa = 0;
                gbt_temporizador_consumir(temp_caida_rapida);
                if(juego_caer(&pieza_activa, tablero)) {
                    casillasManuales++;
                } else {
                    fijar_y_nueva_pieza(&pieza_activa, &pieza_siguiente, &stats, &puntaje, tablero, &casillasManuales, &juego_terminado, &piezas_caidas, &velocidad_caida_ms, &temp_juego_caida, &lineas_eliminadas);
                }
            } else if (gbt_tecla_sostenida(GBTK_ABAJO)) {
                if(!sostenida_activa && gbt_temporizador_consumir(temp_caida_rapida)) {
                    sostenida_activa = 1;
                }
                if(sostenida_activa && gbt_temporizador_consumir(temp_caida_rapida)) {
                    if(juego_caer(&pieza_activa, tablero)) {
                        casillasManuales++;
                    } else {
                        fijar_y_nueva_pieza(&pieza_activa, &pieza_siguiente, &stats, &puntaje, tablero, &casillasManuales, &juego_terminado, &piezas_caidas, &velocidad_caida_ms, &temp_juego_caida, &lineas_eliminadas);
                    }
                }
            } else {
                if(gbt_temporizador_consumir(temp_juego_caida)){
                    if(!juego_caer(&pieza_activa, tablero)){
                        fijar_y_nueva_pieza(&pieza_activa, &pieza_siguiente, &stats, &puntaje, tablero, &casillasManuales, &juego_terminado, &piezas_caidas, &velocidad_caida_ms, &temp_juego_caida, &lineas_eliminadas);
                    }
                }
            }
        }

        // Dibujar fondo y bordes
        dibujar_fondo(alto, ancho);
        dibujar_borde(alto, ancho, 0, 0);

        // Cambiar color de opciones al presionar arriba/abajo
        if(tecla == GBTK_ABAJO || tecla == GBTK_ARRIBA){
            colorSeleccionado = elegir_color_permitido();
        }

        // Lógica según pantalla
        if(pantalla == 0){
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
            dibujar_juego(ancho, alto, tablero, &pieza_activa, juego_terminado, marco_x, marco_y, lado_bloque);
            dibujar_puntuacion(&puntaje, nombre_jugador, lineas_eliminadas, piezas_caidas, velocidad_caida_ms, alto, fin_tablero_y, ancho, fin_tablero_x, &pieza_siguiente);
            dibujar_estadisticas(&stats, alto, fin_tablero_y, marco_x);

            if(juego_pausado && !juego_terminado){
                dibujar_texto_5x7("PAUSA", calcular_x_centrada("PAUSA", ancho), alto / 2, COL_AMARILLO);
                dibujar_texto_5x7("P PARA CONTINUAR", calcular_x_centrada("P PARA CONTINUAR", ancho), alto / 2 + 12, COL_GRIS_CLARO);
            }
          }
          else if(pantalla == 2){
            dibujar_inst(ancho, alto);
          }
          else if(pantalla == 3){
            dibujar_texto_5x7("INGRESE NOMBRE", calcular_x_centrada("INGRESE NOMBRE", ancho), alto / 2 - 20, COL_VERDE_BRILL);
            dibujar_texto_5x7(nombre_jugador, calcular_x_centrada(nombre_jugador, ancho), alto / 2, COL_AMARILLO);
            dibujar_texto_5x7("ENTER PARA JUGAR", calcular_x_centrada("ENTER PARA JUGAR", ancho), alto / 2 + 20, COL_GRIS_CLARO);

            if(mostrar_error_nombre){
                dibujar_texto_5x7("CARACTER NO SOPORTADO", calcular_x_centrada("CARACTER NO SOPORTADO", ancho), alto / 2 + 32, COL_ROJO_BRILL);
            }
          }
          

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    destruir_tablero(tablero, filas);
    gbt_temporizador_destruir(temp_caida_tetrominos);
    gbt_temporizador_destruir(temp_activar_tetrominos);
    gbt_temporizador_destruir(temp_juego_caida);
    gbt_temporizador_destruir(temp_movimiento_lateral);
    gbt_temporizador_destruir(temp_caida_rapida);
    return 0;
}
