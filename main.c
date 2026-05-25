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
#include "config.h"

#define CGA_ANCHO 320
#define CGA_ALTO 200
#define VGA_ANCHO 640
#define VGA_ALTO 480

#define PANTALLA_MENU 0
#define PANTALLA_JUEGO 1
#define PANTALLA_INSTRUCCIONES 2
#define PANTALLA_NOMBRE 3
#define PANTALLA_MODO 4
#define PANTALLA_ALTO 5
#define PANTALLA_CONFIGURACION 6
#define PANTALLA_ESC_MENU 7
#define PANTALLA_REANUDAR 8



int modo_deluxe = 0;

static void construir_nombre_archivo(const char *nombre_jugador, int deluxe, int num_columnas, char *destino, int tam)
{
    if(deluxe){
        snprintf(destino, tam, "partida_deluxe_%s_%d.bin", nombre_jugador, num_columnas);
    } else {
        snprintf(destino, tam, "partida_normal_%s.bin", nombre_jugador);
    }
}

static void fijar_y_nueva_pieza(tPiezaActiva *pieza, tPiezaActiva *pieza_siguiente, tEstadisticas *stats, int *puntaje, int **tablero, int *casillasManuales, int *juego_terminado, int *piezas_caidas, int *velocidad_caida_ms, tGBT_Temporizador **temp_juego_caida, int *lineas_eliminadas, const char *nombre_jugador_actual, int *hold_usado){

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
        char archivo_guardado[40];
                    construir_nombre_archivo(nombre_jugador_actual, modo_deluxe, columnas, archivo_guardado, sizeof(archivo_guardado));
        remove(archivo_guardado);
    }
    *hold_usado = 0;
}

static uint8_t elegir_color_permitido(void) {
    uint8_t opciones[] = {
        COL_SEM_ACENTO,
        COL_SEM_TEXTO_PRINCIPAL
    };

    return opciones[rand() % 2];
}

static void reiniciar_partida(int **tablero, tPiezaActiva *pieza, tPiezaActiva *pieza_siguiente, tEstadisticas *stats, int *puntaje, int *piezas_caidas, int *velocidad_caida_ms, int *lineas_eliminadas, int *casillasManuales, int *juego_terminado, tGBT_Temporizador **temp_juego_caida, int velocidad_base, int *tiene_pieza_guardada, int *hold_usado) {

        int fila;
        int col;
        for(fila = 0; fila < filas; fila++){
            for(col = 0; col < columnas; col++){
                tablero[fila][col] = 0;
            }
        }
        *puntaje = 0;
        *piezas_caidas = 0;
        *velocidad_caida_ms = velocidad_base;
        *lineas_eliminadas = 0;
        *casillasManuales = 0;
        *juego_terminado = 0;
        stats->piezas_usadas = 0;
        for(int i = 0; i < 5; i++){
            stats->lineas_por_jugada[i] = 0;
        }

        gbt_temporizador_destruir(*temp_juego_caida);
        *temp_juego_caida = gbt_temporizador_crear(velocidad_base / 1000.0);
        juego_inicializar_pieza(pieza);
        juego_inicializar_pieza(pieza_siguiente);
        *tiene_pieza_guardada = 0;
        *hold_usado = 0;
}

static int ajustar_velocidad(int *velocidad, const int dir) {
    *velocidad += dir * 50;

    if(*velocidad < 100)  *velocidad = 100;
    if(*velocidad > 2000) *velocidad = 2000;

    return *velocidad;
}

static int caracter_soportado(eGBT_Tecla tecla){

    return (tecla >= GBTK_a && tecla <= GBTK_z) || (tecla >= GBTK_0 && tecla <= GBTK_9) || tecla == GBTK_MENOS;
}

static char convertir_caracter_nombre(eGBT_Tecla tecla)
{
    if(tecla >= GBTK_a && tecla <= GBTK_z){
        return tecla - 32; //convierte lo que el usuario tipea en minúscula a mayúscula
    }

    return tecla;
}

int main(int argc, char *argv[])
{
    if (gbt_iniciar() != 0) {
        fprintf(stderr, "Error al iniciar GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    srand((unsigned)time(NULL));

    Config config = {
        .velocidad_caida_ms = 1000,
        .paleta_id          = 0,
        .resolucion         = 0,   // 0=CGA, 1=VGA
        .escala             = 2
    };

    // 2. Pisar con config guardada si existe
    cargar_config(&config, "config.cfg");

    // Traducir resolucion guardada a ancho/alto
    int ancho = (config.resolucion == 1) ? VGA_ANCHO : CGA_ANCHO;
    int alto  = (config.resolucion == 1) ? VGA_ALTO  : CGA_ALTO;

    // 3. Pisar con argumentos si los hay (máxima prioridad)
    int ret = parsearResolucion(argc, argv, &ancho, &alto, &config.escala);
    if (ret == -1) return -1;  // arg inválido

    escala_ui = (config.resolucion == 1) ? 2 : 1;

    int velocidad_caida_ms = config.velocidad_caida_ms;
    int paleta_id          = config.paleta_id;
    int escala             = config.escala;
    tGBT_ColorRGB *paleta;

    switch(paleta_id) {
        case 1:
            paleta = paletaRetroGB;
            break;
        case 2:
            paleta = paletaCyberpunk;
            break;
        default:
            paleta = paletaCGA;
            break;
    }

    char nombreVentana[50];
    snprintf(nombreVentana, sizeof(nombreVentana), "TETRIS - %dx%d", ancho, alto);

    if(gbt_crear_ventana(nombreVentana, ancho, alto, escala) != 0){
        fprintf(stderr, "Error al iniciar el modulo de graficos de GBT: %s\n", gbt_obtener_log());
        return -1;
    }

    if (gbt_aplicar_paleta(paleta, CANT_COLORES, GBT_FORMATO_888) != 0) {
        fprintf(stderr, "Error al aplicar la nueva paleta de colores: %s\n", gbt_obtener_log());
        return -1;
    }

    inicializar_colores_semanticos(paleta_id);

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
    int menuDerecho = xTitulo + calcular_ancho_texto(titulo);

    if (xJugar < menuIzquierdo) {
        menuIzquierdo = xJugar;
    }
    if (xInstrucciones < menuIzquierdo) {
        menuIzquierdo = xInstrucciones;
    }

    if(xConfig < menuIzquierdo) {
        menuIzquierdo = xConfig;
    }

    if (xJugar + calcular_ancho_texto(opcionJugar) > menuDerecho) {
        menuDerecho = xJugar + calcular_ancho_texto(opcionJugar);
    }

    if (xInstrucciones + calcular_ancho_texto(opcionInstrucciones) > menuDerecho) {
        menuDerecho = xInstrucciones + calcular_ancho_texto(opcionInstrucciones);
    }

    if(xConfig + calcular_ancho_texto(opcionConfig) > menuDerecho) {
        menuDerecho = xConfig + calcular_ancho_texto(opcionConfig);
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
    tGBT_Temporizador *temp_fijacion = gbt_temporizador_crear(0.5);

    if (!temp_caida_rapida) {
        fprintf(stderr, "Error al crear el temporizador de movimiento abajo: %s\n", gbt_obtener_log());
        return -1;
    }




    // Inicializar tetrominos decorativos
    tTetrominoFondo tetrominos_decorativos[4];
    inicializar_tetrominos_fondo(tetrominos_decorativos);

    int corriendo = 1;
    int opcionSeleccionada = 0;
    int opcionMenuConfig = 0;
    int pantalla = PANTALLA_MENU;
    int juego_terminado = 0;
    int juego_pausado = 0;
    int ancho_tablero_deluxe = 10;

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
    int marco_y = (alto / 2) - (((filas - 2) * lado_bloque) / 2);
    int fin_tablero_x = marco_x + (columnas * lado_bloque);
    int fin_tablero_y = marco_y + ((filas - 2) * lado_bloque);
    static int sostenida_activa = 0;
    static int cooldown_lateral = 0;
    static int das_activo = 0;  // 1 = ya pasó el DAS inicial, auto-repeat activo
    static int esperando_fijacion = 0;

    uint8_t colorSeleccionado = COL_AMARILLO;

    int** tablero = NULL;

    tPiezaActiva pieza_activa;
    tPiezaActiva pieza_siguiente;
    tPiezaActiva pieza_guardada;
    int tiene_pieza_guardada = 0;
    int hold_usado = 0;

    while(corriendo) {

        gbt_procesar_entrada();
        eGBT_Tecla tecla = gbt_obtener_tecla_presionada();

        //MENU
        if(tecla == GBTK_ESCAPE && pantalla == PANTALLA_MENU) {
            corriendo = 0;
            printf("Saliendo del juego.\n");
        }
        else if(tecla == GBTK_ESCAPE && pantalla == PANTALLA_JUEGO && juego_terminado) {
            filas = 22;
            columnas = 10;
            pantalla = PANTALLA_MENU;
        }
        else if(tecla == GBTK_ESCAPE && pantalla == PANTALLA_JUEGO && !juego_terminado) {
            pantalla = PANTALLA_ESC_MENU;
        }
        else if (tecla == GBTK_ESCAPE && (pantalla == PANTALLA_INSTRUCCIONES || pantalla == PANTALLA_CONFIGURACION)) {
            pantalla = PANTALLA_MENU;
            printf("Volviendo al menu principal.\n");
        }
        else if (tecla == GBTK_ESCAPE && pantalla == PANTALLA_MODO) {
            pantalla = PANTALLA_MENU;
            opcionSeleccionada = 0;
        }
        else if (tecla == GBTK_ESCAPE && pantalla == PANTALLA_ALTO) {
            pantalla = PANTALLA_MODO;
            opcionSeleccionada = 1;
        }
        else if (tecla != GBTK_DESCONOCIDA) {
            if(pantalla == PANTALLA_JUEGO && juego_terminado && tecla == GBTK_ENTER){
                esperando_fijacion = 0;
                largo_nombre = 0;
                nombre_jugador[0] = '\0';
                filas = 22;
                columnas = 10;
                pantalla = PANTALLA_MENU;
                opcionSeleccionada = 0;
                tecla = GBTK_DESCONOCIDA;
            }
            if(pantalla == PANTALLA_MENU){
                if(tecla == GBTK_ABAJO){
                    opcionSeleccionada = (opcionSeleccionada + 1) % 3;
                }
                if(tecla == GBTK_ARRIBA){
                    opcionSeleccionada = (opcionSeleccionada + 2) % 3;
                }
                if(tecla == GBTK_ENTER){
                    if(opcionSeleccionada == 0){
                        pantalla = PANTALLA_MODO;
                        opcionSeleccionada = 0; // Por defecto modo normal
                        tecla = GBTK_DESCONOCIDA;
                    }
                    else if(opcionSeleccionada == 1){
                        pantalla = PANTALLA_INSTRUCCIONES;
                    }
                    else if(opcionSeleccionada == 2) {
                        pantalla = PANTALLA_CONFIGURACION;
                        tecla = GBTK_DESCONOCIDA;
                    }
                }
            }
            else if(pantalla == PANTALLA_MODO){
                if(tecla == GBTK_ABAJO){
                    opcionSeleccionada = 1;
                }
                if(tecla == GBTK_ARRIBA){
                    opcionSeleccionada = 0;
                }
                if(tecla == GBTK_ENTER){
                    modo_deluxe = opcionSeleccionada;
                    if (tablero) {
                        destruir_tablero(tablero, filas);
                        tablero = NULL;
                    }
                    if(opcionSeleccionada == 0){
                        filas = 22;
                        columnas = 10;
                    } else {
                        columnas = 10;
                    }
                    largo_nombre = 0;
                    nombre_jugador[0] = '\0';
                    mostrar_error_nombre = 0;
                    tecla = GBTK_DESCONOCIDA;
                    if(opcionSeleccionada == 0){
                        pantalla = PANTALLA_NOMBRE;
                    } else {
                        pantalla = PANTALLA_ALTO;
                    }
                }
            }
            else if(pantalla == PANTALLA_ALTO){
                if(tecla == GBTK_IZQUIERDA && ancho_tablero_deluxe > 8){
                    ancho_tablero_deluxe--;
                }
                if(tecla == GBTK_DERECHA && ancho_tablero_deluxe < 16){
                    ancho_tablero_deluxe++;
                }
                if(tecla == GBTK_ENTER){
                    filas = 22;
                    columnas = ancho_tablero_deluxe;
                    pantalla = PANTALLA_NOMBRE;
                    tecla = GBTK_DESCONOCIDA;
                    mostrar_error_nombre = 0;
                }
            }
            //JUEGO
            if(pantalla == PANTALLA_JUEGO && !juego_terminado){
                if(tecla == GBTK_p){
                    juego_pausado = !juego_pausado;
                }

                if(!juego_pausado){
                    if(tecla == GBTK_r || tecla == GBTK_ARRIBA){
                        juego_rotar(&pieza_activa, tablero);
                        esperando_fijacion = 0;
                        gbt_temporizador_destruir(temp_fijacion);
                        temp_fijacion = gbt_temporizador_crear(velocidad_caida_ms * 0.5 / 1000.0);
                    }
                    if(tecla == GBTK_q){
                        juego_rotar_izquierda(&pieza_activa, tablero);
                        esperando_fijacion = 0;
                        gbt_temporizador_destruir(temp_fijacion);
                        temp_fijacion = gbt_temporizador_crear(velocidad_caida_ms * 0.5 / 1000.0);
                    }
                    if(tecla == GBTK_e && !hold_usado){
                        if(!tiene_pieza_guardada){
                            pieza_guardada.tipo = pieza_activa.tipo;
                            pieza_guardada.color = pieza_activa.color;
                            pieza_guardada.rotacion = 0;
                            tiene_pieza_guardada = 1;
                            pieza_activa = pieza_siguiente;
                            pieza_activa.x = columnas / 2 - 2;
                            pieza_activa.y = 0;
                            pieza_activa.rotacion = 0;
                            juego_inicializar_pieza(&pieza_siguiente);
                        } else {
                            tPiezaActiva temp;
                            temp.tipo = pieza_guardada.tipo;
                            temp.color = pieza_guardada.color;
                            pieza_guardada.tipo = pieza_activa.tipo;
                            pieza_guardada.color = pieza_activa.color;
                            pieza_guardada.rotacion = 0;
                            pieza_activa.tipo = temp.tipo;
                            pieza_activa.color = temp.color;
                            pieza_activa.rotacion = 0;
                            pieza_activa.x = columnas / 2 - 2;
                            pieza_activa.y = 0;
                        }
                        hold_usado = 1;
                        esperando_fijacion = 0;
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

            if(pantalla == PANTALLA_ESC_MENU){
                if(tecla == GBTK_c){
                    pantalla = PANTALLA_JUEGO;
                }
                if(tecla == GBTK_s){
                    tPartidaGuardada datos;
                    datos.puntaje = puntaje;
                    datos.piezas_caidas = piezas_caidas;
                    datos.velocidad_caida_ms = velocidad_caida_ms;
                    datos.lineas_eliminadas = lineas_eliminadas;
                    datos.pieza_activa = pieza_activa;
                    datos.pieza_siguiente = pieza_siguiente;
                    datos.stats = stats;
                    datos.pieza_guardada = pieza_guardada;
                    datos.tiene_pieza_guardada = tiene_pieza_guardada;
                    strcpy(datos.nombre_jugador, nombre_jugador);
                    juego_obtener_bolsa(datos.bolsa_tetrominos, &datos.indice_bolsa);
                    char archivo_guardado[40];
                    construir_nombre_archivo(nombre_jugador, modo_deluxe, columnas, archivo_guardado, sizeof(archivo_guardado));
                    guardar_partida(tablero, filas, columnas, &datos, archivo_guardado);
                    printf("Partida guardada exitosamente.\n");
                    filas = 22;
                    columnas = 10;
                    pantalla = PANTALLA_MENU;
                }
                if(tecla == GBTK_x){
                    filas = 22;
                    columnas = 10;
                    pantalla = PANTALLA_MENU;
                }
            }
            if(pantalla == PANTALLA_NOMBRE){

                if(tecla == GBTK_ENTER){

                    if(largo_nombre == 0){
                        strcpy(nombre_jugador, "ANONIMO");
                        largo_nombre = 8;
                    }

                    mostrar_error_nombre = 0;

                    // Verificar si hay partida guardada
                    char arch_guardado[40];
                    construir_nombre_archivo(nombre_jugador, modo_deluxe, columnas, arch_guardado, sizeof(arch_guardado));
                    FILE* f_check = fopen(arch_guardado, "rb");
                    if(f_check){
                        fclose(f_check);
                        pantalla = PANTALLA_REANUDAR;
                    } else {
                        pantalla = PANTALLA_JUEGO;

                        if (tablero) {
                            destruir_tablero(tablero, filas);
                        }
                        tablero = crear_tablero(filas, columnas, sizeof(int));
                        if (!tablero) return -1;

                        lado_bloque = calcular_lado_bloque_juego(alto);
                        marco_x = (ancho / 2) - ((columnas * lado_bloque) / 2);
                        marco_y = (alto / 2) - (((filas - 2) * lado_bloque) / 2);
                        fin_tablero_x = marco_x + (columnas * lado_bloque);
                        fin_tablero_y = marco_y + ((filas - 2) * lado_bloque);

                        reiniciar_partida(tablero, &pieza_activa, &pieza_siguiente, &stats, &puntaje, &piezas_caidas, &velocidad_caida_ms, &lineas_eliminadas, &casillasManuales, &juego_terminado, &temp_juego_caida, config.velocidad_caida_ms, &tiene_pieza_guardada, &hold_usado);
                        esperando_fijacion = 0;
                    }
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
            if(pantalla == PANTALLA_REANUDAR){
                if(tecla == GBTK_s){
                    // Cargar partida guardada
                    tPartidaGuardada datos_guardados;
                    int f_leidas, c_leidas;
                    char arch_guardado[40];
                    construir_nombre_archivo(nombre_jugador, modo_deluxe, columnas, arch_guardado, sizeof(arch_guardado));
                    if(cargar_partida(&tablero, &f_leidas, &c_leidas, &datos_guardados, arch_guardado)){
                        filas = f_leidas;
                        columnas = c_leidas;
                        puntaje = datos_guardados.puntaje;
                        piezas_caidas = datos_guardados.piezas_caidas;
                        velocidad_caida_ms = datos_guardados.velocidad_caida_ms;
                        lineas_eliminadas = datos_guardados.lineas_eliminadas;
                        pieza_activa = datos_guardados.pieza_activa;
                        pieza_siguiente = datos_guardados.pieza_siguiente;
                        stats = datos_guardados.stats;
                        juego_cargar_bolsa(datos_guardados.bolsa_tetrominos, datos_guardados.indice_bolsa);
                        pieza_guardada = datos_guardados.pieza_guardada;
                        tiene_pieza_guardada = datos_guardados.tiene_pieza_guardada;
                        hold_usado = 0;
                        gbt_temporizador_destruir(temp_juego_caida);
                        temp_juego_caida = gbt_temporizador_crear(velocidad_caida_ms / 1000.0);
                        lado_bloque = calcular_lado_bloque_juego(alto);
                        marco_x = (ancho / 2) - ((columnas * lado_bloque) / 2);
                        marco_y = (alto / 2) - (((filas - 2) * lado_bloque) / 2);
                        fin_tablero_x = marco_x + (columnas * lado_bloque);
                        fin_tablero_y = marco_y + ((filas - 2) * lado_bloque);
                        esperando_fijacion = 0;
                        pantalla = PANTALLA_JUEGO;
                        printf("Partida guardada cargada exitosamente.\n");
                    }
                }
                if(tecla == GBTK_n){
                    // Borrar partida guardada y arrancar nueva
                    char arch_guardado[40];
                    construir_nombre_archivo(nombre_jugador, modo_deluxe, columnas, arch_guardado, sizeof(arch_guardado));
                    remove(arch_guardado);

                    if (tablero) {
                        destruir_tablero(tablero, filas);
                    }
                    tablero = crear_tablero(filas, columnas, sizeof(int));
                    if (!tablero) return -1;

                    lado_bloque = calcular_lado_bloque_juego(alto);
                    marco_x = (ancho / 2) - ((columnas * lado_bloque) / 2);
                    marco_y = (alto / 2) - (((filas - 2) * lado_bloque) / 2);
                    fin_tablero_x = marco_x + (columnas * lado_bloque);
                    fin_tablero_y = marco_y + ((filas - 2) * lado_bloque);

                    reiniciar_partida(tablero, &pieza_activa, &pieza_siguiente, &stats, &puntaje, &piezas_caidas, &velocidad_caida_ms, &lineas_eliminadas, &casillasManuales, &juego_terminado, &temp_juego_caida, config.velocidad_caida_ms, &tiene_pieza_guardada, &hold_usado);
                    esperando_fijacion = 0;
                    pantalla = PANTALLA_JUEGO;
                }
            }
            if(pantalla == PANTALLA_CONFIGURACION) {
                if (tecla == GBTK_ARRIBA)
                    opcionMenuConfig = (opcionMenuConfig + 2) % 3;
                if (tecla == GBTK_ABAJO)
                    opcionMenuConfig = (opcionMenuConfig + 1) % 3;

                if (tecla == GBTK_IZQUIERDA || tecla == GBTK_DERECHA) {
                    int dir = (tecla == GBTK_DERECHA) ? 1 : -1;
                    switch(opcionMenuConfig) {
                        case 0: // velocidad
                            config.velocidad_caida_ms = ajustar_velocidad(&config.velocidad_caida_ms, dir);
                            break;
                        case 1: // resolución: alterna entre 0 y 1
                            config.resolucion = !config.resolucion;
                            break;
                        case 2: // paleta: cicla entre 0, 1, 2
                            config.paleta_id = ((config.paleta_id + dir) + 3) % 3;
                            break;
                    }
                }

                if (tecla == GBTK_ENTER) {
                    guardar_config(&config, "config.cfg");

                    tGBT_ColorRGB *paleta_nueva;
                    switch(config.paleta_id) {
                        case 1:  paleta_nueva = paletaRetroGB;   break;
                        case 2:  paleta_nueva = paletaCyberpunk; break;
                        default: paleta_nueva = paletaCGA;       break;
                    }
                    gbt_aplicar_paleta(paleta_nueva, CANT_COLORES, GBT_FORMATO_888);
                    inicializar_colores_semanticos(config.paleta_id);

                    printf("configuracion guardada correctamente\n");
                    pantalla = 0;
                }
            }
        }

        if(pantalla == PANTALLA_JUEGO && !juego_terminado && !juego_pausado){

            int izq = gbt_tecla_sostenida(GBTK_IZQUIERDA);
            int der = gbt_tecla_sostenida(GBTK_DERECHA);

            if (cooldown_lateral > 0) {
                    cooldown_lateral--;
            }

            if (izq || der) {
                if (cooldown_lateral == 0) {
                    if (izq) juego_mover_izquierda(&pieza_activa, tablero);
                    if (der) juego_mover_derecha(&pieza_activa, tablero);
                    esperando_fijacion = 0;
                    gbt_temporizador_destruir(temp_fijacion);
                    temp_fijacion = gbt_temporizador_crear(velocidad_caida_ms * 0.5 / 1000.0);

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
                    fijar_y_nueva_pieza(&pieza_activa, &pieza_siguiente, &stats, &puntaje, tablero, &casillasManuales, &juego_terminado, &piezas_caidas, &velocidad_caida_ms, &temp_juego_caida, &lineas_eliminadas, nombre_jugador, &hold_usado);
                }
            } else if (gbt_tecla_sostenida(GBTK_ABAJO)) {
                if(!sostenida_activa && gbt_temporizador_consumir(temp_caida_rapida)) {
                    sostenida_activa = 1;
                }
                if(sostenida_activa && gbt_temporizador_consumir(temp_caida_rapida)) {
                    if(juego_caer(&pieza_activa, tablero)) {
                        casillasManuales++;
                    } else {
                        fijar_y_nueva_pieza(&pieza_activa, &pieza_siguiente, &stats, &puntaje, tablero, &casillasManuales, &juego_terminado, &piezas_caidas, &velocidad_caida_ms, &temp_juego_caida, &lineas_eliminadas, nombre_jugador, &hold_usado);
                    }
                }
            } else {
                if(gbt_temporizador_consumir(temp_juego_caida)){
                    if(!juego_caer(&pieza_activa, tablero)){
                        if(!esperando_fijacion){
                            esperando_fijacion = 1;
                            gbt_temporizador_destruir(temp_fijacion);
                            temp_fijacion = gbt_temporizador_crear(velocidad_caida_ms * 0.5 / 1000.0);
                        }
                    } else {
                        esperando_fijacion = 0;
                    }
                }
                if(esperando_fijacion && gbt_temporizador_consumir(temp_fijacion)){
                    esperando_fijacion = 0;
                    fijar_y_nueva_pieza(&pieza_activa, &pieza_siguiente, &stats, &puntaje, tablero, &casillasManuales, &juego_terminado, &piezas_caidas, &velocidad_caida_ms, &temp_juego_caida, &lineas_eliminadas, nombre_jugador, &hold_usado);
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
        if(pantalla == PANTALLA_MENU){
            // Actualizar tetrominos decorativos
            actualizar_tetrominos_fondo(tetrominos_decorativos, alto, ancho, limiteIzquierdoTetrominos, limiteDerechoTetrominos, temp_caida_tetrominos, temp_activar_tetrominos);

            // Dibujar menú y tetrominos
            dibujar_menu(opcionSeleccionada, ancho, alto, colorSeleccionado);

            for(int t = 0; t < 4; t++){
                if(tetrominos_decorativos[t].activo){
                    dibujar_tetromino(tetrominos_decorativos[t], 0, tetrominos_decorativos[t].rot, alto, ancho);
                }
            }
        } else if(pantalla == PANTALLA_MODO){
            actualizar_tetrominos_fondo(tetrominos_decorativos, alto, ancho, limiteIzquierdoTetrominos, limiteDerechoTetrominos, temp_caida_tetrominos, temp_activar_tetrominos);
            dibujar_seleccion_modo(opcionSeleccionada, ancho, alto, colorSeleccionado);
            for(int t = 0; t < 4; t++){
                if(tetrominos_decorativos[t].activo){
                    dibujar_tetromino(tetrominos_decorativos[t], 0, tetrominos_decorativos[t].rot, alto, ancho);
                }
            }
        } else if(pantalla == PANTALLA_ALTO){
            actualizar_tetrominos_fondo(tetrominos_decorativos, alto, ancho, limiteIzquierdoTetrominos, limiteDerechoTetrominos, temp_caida_tetrominos, temp_activar_tetrominos);
            dibujar_seleccion_ancho(ancho_tablero_deluxe, ancho, alto);
            for(int t = 0; t < 4; t++){
                if(tetrominos_decorativos[t].activo){
                    dibujar_tetromino(tetrominos_decorativos[t], 0, tetrominos_decorativos[t].rot, alto, ancho);
                }
            }
        } else if(pantalla == PANTALLA_JUEGO){
            dibujar_juego(ancho, alto, tablero, &pieza_activa, juego_terminado, marco_x, marco_y, lado_bloque);
            dibujar_puntuacion(&puntaje, nombre_jugador, lineas_eliminadas, piezas_caidas, velocidad_caida_ms, alto, fin_tablero_y, ancho, fin_tablero_x, &pieza_siguiente);
            dibujar_estadisticas(&stats, alto, fin_tablero_y, marco_x, &pieza_guardada, tiene_pieza_guardada);

            if(juego_pausado && !juego_terminado){
                if(modo_deluxe){
                    dibujar_texto_7x9("PAUSA", calcular_x_centrada("PAUSA", ancho), alto / 2, COL_AMARILLO);
                    dibujar_texto_7x9("P PARA CONTINUAR", calcular_x_centrada("P PARA CONTINUAR", ancho), alto / 2 + 15, COL_GRIS_CLARO);
                } else{
                    dibujar_texto("PAUSA", calcular_x_centrada("PAUSA", ancho), alto / 2, COL_AMARILLO);
                    dibujar_texto("P PARA CONTINUAR", calcular_x_centrada("P PARA CONTINUAR", ancho), alto / 2 + 12, COL_GRIS_CLARO);
                }
            }
        }
        else if(pantalla == PANTALLA_ESC_MENU){
            dibujar_juego(ancho, alto, tablero, &pieza_activa, juego_terminado, marco_x, marco_y, lado_bloque);
            dibujar_puntuacion(&puntaje, nombre_jugador, lineas_eliminadas, piezas_caidas, velocidad_caida_ms, alto, fin_tablero_y, ancho, fin_tablero_x, &pieza_siguiente);
            dibujar_estadisticas(&stats, alto, fin_tablero_y, marco_x, &pieza_guardada, tiene_pieza_guardada);
            dibujar_texto("C CONTINUAR",  calcular_x_centrada("C CONTINUAR",  ancho), alto / 2 - 20, COL_VERDE_BRILL);
            dibujar_texto("S GUARDAR Y SALIR", calcular_x_centrada("S GUARDAR Y SALIR", ancho), alto / 2,      COL_AMARILLO);
            dibujar_texto("X SALIR SIN GUARDAR", calcular_x_centrada("X SALIR SIN GUARDAR", ancho), alto / 2 + 20, COL_ROJO_BRILL);
        }
        else if(pantalla == PANTALLA_REANUDAR){
            dibujar_texto("PARTIDA GUARDADA", calcular_x_centrada("PARTIDA GUARDADA", ancho), alto / 2 - 30 * escala_ui, COL_VERDE_BRILL);
            dibujar_texto("DESEA CONTINUARLA?", calcular_x_centrada("DESEA CONTINUARLA?", ancho), alto / 2 - 15 * escala_ui, COL_GRIS_CLARO);
            dibujar_texto("S CONTINUAR", calcular_x_centrada("S CONTINUAR", ancho), alto / 2 + 5 * escala_ui, COL_AMARILLO);
            dibujar_texto("N NUEVA PARTIDA", calcular_x_centrada("N NUEVA PARTIDA", ancho), alto / 2 + 20 * escala_ui, COL_ROJO_BRILL);
        }
        else if(pantalla == PANTALLA_INSTRUCCIONES){
            dibujar_inst(ancho, alto);
        }
        else if(pantalla == PANTALLA_NOMBRE){
            dibujar_inicio_usuario(ancho, alto, nombre_jugador, mostrar_error_nombre);
        }
        else if(pantalla == PANTALLA_CONFIGURACION) {
            dibujar_configuracion(ancho, alto, &config, opcionMenuConfig);
        }

        gbt_volcar_backbuffer();
        gbt_esperar(16);
    }

    if (tablero) {
        destruir_tablero(tablero, filas);
    }
    gbt_temporizador_destruir(temp_caida_tetrominos);
    gbt_temporizador_destruir(temp_activar_tetrominos);
    gbt_temporizador_destruir(temp_juego_caida);
    gbt_temporizador_destruir(temp_movimiento_lateral);
    gbt_temporizador_destruir(temp_caida_rapida);
    gbt_temporizador_destruir(temp_fijacion);

    return 0;

}
