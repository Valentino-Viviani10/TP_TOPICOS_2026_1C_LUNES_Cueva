#include "instrucciones.h"
#include "dibujar.h"
#include "colores.h"
#include "juego.h"

/*
void dibujar_inst(int ancho, int alto) {
    const int x_ini = OFFSET_X;
    const int x_fin = ancho - OFFSET_X;
    int y = OFFSET_Y;

    dibujar_linea_horizontal(x_ini, x_fin, y);

    dibujar_texto("CONTROLES", x_ini, y + ESPACIADO_ENTRE_LINEAS, COL_VERDE);
    dibujar_texto("FLECHAS IZQ/DER: mover a izquierda", x_ini, y + ESPACIADO_ENTRE_LINEAS * 2, COL_GRIS_CLARO);
    dibujar_texto("y derecha", x_ini, y + ESPACIADO_ENTRE_LINEAS * 3, COL_GRIS_CLARO);
    dibujar_texto("R: rotar", x_ini, y + ESPACIADO_ENTRE_LINEAS * 4, COL_GRIS_CLARO);
    dibujar_texto("FLECHA ABAJO: mover hacia abajo", x_ini, y + ESPACIADO_ENTRE_LINEAS * 5, COL_GRIS_CLARO);
    dibujar_texto("ESC: terminar juego", x_ini, y + ESPACIADO_ENTRE_LINEAS * 6, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y + ESPACIADO_ENTRE_LINEAS * 7 + ESPACIADO_ENTRE_LINEAS / 2);

    dibujar_texto("PUNTAJE", x_ini, y + ESPACIADO_ENTRE_LINEAS * 8, COL_VERDE);
    dibujar_texto("1 linea: 100 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 9, COL_GRIS_CLARO);
    dibujar_texto("2 lineas: 200 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 10, COL_GRIS_CLARO);
    dibujar_texto("3 lineas: 400 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 11, COL_GRIS_CLARO);
    dibujar_texto("4 lineas: 800 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 12, COL_GRIS_CLARO);
    dibujar_texto("Bajar manual: 10pt por casilla", x_ini, y + ESPACIADO_ENTRE_LINEAS * 13, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y + ESPACIADO_ENTRE_LINEAS * 14 + ESPACIADO_ENTRE_LINEAS / 2);

    dibujar_texto("VELOCIDAD", x_ini, y + ESPACIADO_ENTRE_LINEAS * 15, COL_VERDE);
    dibujar_texto("Cada 10 piezas +3% velocidad", x_ini, y + ESPACIADO_ENTRE_LINEAS * 16, COL_GRIS_CLARO);
    dibujar_texto("Inicio: 1000ms por caida", x_ini, y + ESPACIADO_ENTRE_LINEAS * 17, COL_GRIS_CLARO);
}*/

void dibujar_inst(int ancho, int alto){

    const int x_ini = OFFSET_X;
    const int x_fin = ancho - OFFSET_X;

    int y = OFFSET_Y;
    
    // Distancia vertical entre renglones dependiente de la resolucion
    int esp = (escala_ui > 1) ? 14 : 10;

    int y_titulo = y + ((escala_ui > 1) ? 10 : 0);
    int y_controles = y_titulo + ((escala_ui > 1) ? 30 : 18);
    int y_puntaje = y_controles + 7 * esp + ((escala_ui > 1) ? 20 : 10);
    int y_mecanicas = y_puntaje + 3 * esp + ((escala_ui > 1) ? 20 : 10);

    // Columnas adaptables a la resolucion
    int x1 = (escala_ui > 1) ? 50 : 25;
    int x2 = (escala_ui > 1) ? 200 : 120;
    int x3 = (escala_ui > 1) ? 400 : 220;

    dibujar_linea_horizontal(x_ini, x_fin, y_titulo - 4);

    if (modo_deluxe) {
        dibujar_texto_7x9("JUEGO DELUXE", calcular_x_centrada("JUEGO DELUXE", ancho), y_titulo, COL_VERDE_BRILL);
    } else {
        dibujar_texto("JUEGO NORMAL", calcular_x_centrada("JUEGO NORMAL", ancho), y_titulo, COL_VERDE_BRILL);
    }

    dibujar_linea_horizontal(x_ini, x_fin, y_titulo + ((escala_ui > 1) ? 16 : 12));


    // FILA 1 - CONTROLES
    dibujar_texto("CONTROLES", x1, y_controles, COL_AMARILLO);

    dibujar_texto("<- -> MOVER", x1, y_controles + esp, COL_GRIS_CLARO);
    dibujar_texto("ABAJO BAJAR", x2, y_controles + esp, COL_GRIS_CLARO);
    dibujar_texto("P PAUSA", x3, y_controles + esp, COL_GRIS_CLARO);

    dibujar_texto("R/ARR ROT DER", x1, y_controles + 2*esp, COL_GRIS_CLARO);
    dibujar_texto("Q ROT IZQ", x2, y_controles + 2*esp, COL_GRIS_CLARO);
    dibujar_texto("ESC SALIR", x3, y_controles + 2*esp, COL_GRIS_CLARO);

    dibujar_texto("ENTER REINICIA", x1, y_controles + 3*esp, COL_GRIS_CLARO);
    dibujar_texto("E GUARDAR PIEZA", x2, y_controles + 3*esp, COL_GRIS_CLARO);

    dibujar_texto("C CONTINUAR", x1, y_controles + 4*esp, COL_GRIS_CLARO);
    dibujar_texto("N NUEVA PARTIDA", x3, y_controles + 4*esp, COL_GRIS_CLARO);

    dibujar_texto("S GUARD/REANUDAR", x1, y_controles + 5*esp, COL_GRIS_CLARO);
    dibujar_texto("X SALIR AL MENU", x3, y_controles + 5*esp, COL_GRIS_CLARO);

    dibujar_texto("1-9 ELIM FILA", x1, y_controles + 6*esp, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y_controles + 6*esp + ((escala_ui > 1) ? 12 : 8));


    // FILA 2 - PUNTAJE
    dibujar_texto("PUNTAJE", x1, y_puntaje, COL_CIAN_BRILL);

    dibujar_texto("1L 100", x1, y_puntaje + esp, COL_GRIS_CLARO);
    dibujar_texto("2L 200", x2, y_puntaje + esp, COL_GRIS_CLARO);
    dibujar_texto("3L 400", x1, y_puntaje + 2*esp, COL_GRIS_CLARO);
    dibujar_texto("4L 800", x2, y_puntaje + 2*esp, COL_GRIS_CLARO);

    dibujar_texto("MANUAL 10 PTS/CAS", x1, y_puntaje + 3*esp, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y_puntaje + 3*esp + ((escala_ui > 1) ? 12 : 8));


    // FILA 3 - MECANICAS
    dibujar_texto("MECANICAS", x1, y_mecanicas, COL_VERDE_BRILL);

    dibujar_texto("CADA 10 PIEZAS", x1, y_mecanicas + esp, COL_GRIS_CLARO);
    dibujar_texto("+3% VEL", x2, y_mecanicas + esp, COL_GRIS_CLARO);

    if (modo_deluxe) {
        dibujar_texto("BOLSA DE 11", x1, y_mecanicas + 2*esp, COL_GRIS_CLARO);
        dibujar_texto("MOVIMIENTO 360", x2, y_mecanicas + 2*esp, COL_GRIS_CLARO);
    }
}
