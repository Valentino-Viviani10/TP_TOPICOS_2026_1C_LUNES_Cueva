#include "instrucciones.h"
#include "dibujar.h"
#include "colores.h"

/*
void dibujar_inst(int ancho, int alto) {
    const int x_ini = OFFSET_X;
    const int x_fin = ancho - OFFSET_X;
    int y = OFFSET_Y;

    dibujar_linea_horizontal(x_ini, x_fin, y);

    dibujar_texto_5x7("CONTROLES", x_ini, y + ESPACIADO_ENTRE_LINEAS, COL_VERDE);
    dibujar_texto_5x7("FLECHAS IZQ/DER: mover a izquierda", x_ini, y + ESPACIADO_ENTRE_LINEAS * 2, COL_GRIS_CLARO);
    dibujar_texto_5x7("y derecha", x_ini, y + ESPACIADO_ENTRE_LINEAS * 3, COL_GRIS_CLARO);
    dibujar_texto_5x7("R: rotar", x_ini, y + ESPACIADO_ENTRE_LINEAS * 4, COL_GRIS_CLARO);
    dibujar_texto_5x7("FLECHA ABAJO: mover hacia abajo", x_ini, y + ESPACIADO_ENTRE_LINEAS * 5, COL_GRIS_CLARO);
    dibujar_texto_5x7("ESC: terminar juego", x_ini, y + ESPACIADO_ENTRE_LINEAS * 6, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y + ESPACIADO_ENTRE_LINEAS * 7 + ESPACIADO_ENTRE_LINEAS / 2);

    dibujar_texto_5x7("PUNTAJE", x_ini, y + ESPACIADO_ENTRE_LINEAS * 8, COL_VERDE);
    dibujar_texto_5x7("1 linea: 100 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 9, COL_GRIS_CLARO);
    dibujar_texto_5x7("2 lineas: 200 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 10, COL_GRIS_CLARO);
    dibujar_texto_5x7("3 lineas: 400 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 11, COL_GRIS_CLARO);
    dibujar_texto_5x7("4 lineas: 800 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 12, COL_GRIS_CLARO);
    dibujar_texto_5x7("Bajar manual: 10pt por casilla", x_ini, y + ESPACIADO_ENTRE_LINEAS * 13, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y + ESPACIADO_ENTRE_LINEAS * 14 + ESPACIADO_ENTRE_LINEAS / 2);

    dibujar_texto_5x7("VELOCIDAD", x_ini, y + ESPACIADO_ENTRE_LINEAS * 15, COL_VERDE);
    dibujar_texto_5x7("Cada 10 piezas +3% velocidad", x_ini, y + ESPACIADO_ENTRE_LINEAS * 16, COL_GRIS_CLARO);
    dibujar_texto_5x7("Inicio: 1000ms por caida", x_ini, y + ESPACIADO_ENTRE_LINEAS * 17, COL_GRIS_CLARO);
}*/

void dibujar_inst(int ancho, int alto){

    const int x_ini = OFFSET_X;
    const int x_fin = ancho - OFFSET_X;

    int y = OFFSET_Y;

    int y_titulo = y + 2;
    int y_controles = y + 26;
    int y_puntaje = y + 86;
    int y_mecanicas = y + 144;

    int x1 = 25;
    int x2 = 115;
    int x3 = 215;

    dibujar_linea_horizontal(x_ini, x_fin, y-4);

    dibujar_texto_5x7("JUEGO NORMAL", calcular_x_centrada("JUEGO NORMAL", ancho), y_titulo,COL_VERDE_BRILL);

    dibujar_linea_horizontal(x_ini, x_fin, y + 16);


    // FILA 1 - CONTROLES
    dibujar_texto_5x7("CONTROLES", x1, y_controles, COL_AMARILLO);

    dibujar_texto_5x7("<- -> MOVER", x1, y_controles + 14, COL_GRIS_CLARO);
    dibujar_texto_5x7("ABAJO BAJAR", x2, y_controles + 14, COL_GRIS_CLARO);
    dibujar_texto_5x7("P PAUSA", x3, y_controles + 14, COL_GRIS_CLARO);

    dibujar_texto_5x7("R/ARR ROT DER", x1, y_controles + 28, COL_GRIS_CLARO);
    dibujar_texto_5x7("Q ROT IZQ", x2, y_controles + 28, COL_GRIS_CLARO);
    dibujar_texto_5x7("ESC SALIR", x3, y_controles + 28, COL_GRIS_CLARO);

    dibujar_texto_5x7("ENTER REINICIA", x1, y_controles + 42, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y_controles + 55);


    // FILA 2 - PUNTAJE
    dibujar_texto_5x7("PUNTAJE", x1, y_puntaje, COL_CIAN_BRILL);

    dibujar_texto_5x7("1L 100", x1, y_puntaje + 14, COL_GRIS_CLARO);
    dibujar_texto_5x7("2L 200", x2, y_puntaje + 14, COL_GRIS_CLARO);
    dibujar_texto_5x7("3L 400", x1, y_puntaje + 28, COL_GRIS_CLARO);
    dibujar_texto_5x7("4L 800", x2, y_puntaje + 28, COL_GRIS_CLARO);

    dibujar_texto_5x7("MANUAL 10 PTS/CAS", x1, y_puntaje + 42, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y_puntaje + 55);


    // FILA 3 - MECANICAS
    dibujar_texto_5x7("MECANICAS", x1, y_mecanicas, COL_VERDE_BRILL);

    dibujar_texto_5x7("CADA 10 PIEZAS", x1, y_mecanicas + 14, COL_GRIS_CLARO);
    dibujar_texto_5x7("+3% VEL", x2 + 25, y_mecanicas + 14, COL_GRIS_CLARO);

    dibujar_texto_5x7("BOLSA DE 7", x1, y_mecanicas + 28, COL_GRIS_CLARO);
    dibujar_texto_5x7("SIN REPETICION", x2 + 25, y_mecanicas + 28, COL_GRIS_CLARO);
}
