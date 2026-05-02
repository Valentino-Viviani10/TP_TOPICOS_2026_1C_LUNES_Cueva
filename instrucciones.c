#include "instrucciones.h"
#include "dibujar.h"
#include "colores.h"

void dibujar_inst(int ancho, int alto) {
    const int x_ini = OFFSET_X;
    const int x_fin = ancho - OFFSET_X;
    int y = OFFSET_Y;

    dibujar_linea_horizontal(x_ini, x_fin, y);

    dibujar_texto_8x8("CONTROLES", x_ini, y + ESPACIADO_ENTRE_LINEAS, COL_VERDE);
    dibujar_texto_8x8("FLECHAS IZQ/DER: mover a izquierda", x_ini, y + ESPACIADO_ENTRE_LINEAS * 2, COL_GRIS_CLARO);
    dibujar_texto_8x8("y derecha", x_ini, y + ESPACIADO_ENTRE_LINEAS * 3, COL_GRIS_CLARO);
    dibujar_texto_8x8("R: rotar", x_ini, y + ESPACIADO_ENTRE_LINEAS * 4, COL_GRIS_CLARO);
    dibujar_texto_8x8("FLECHA ABAJO: mover hacia abajo", x_ini, y + ESPACIADO_ENTRE_LINEAS * 5, COL_GRIS_CLARO);
    dibujar_texto_8x8("ESC: terminar juego", x_ini, y + ESPACIADO_ENTRE_LINEAS * 6, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y + ESPACIADO_ENTRE_LINEAS * 7 + ESPACIADO_ENTRE_LINEAS / 2);

    dibujar_texto_8x8("PUNTAJE", x_ini, y + ESPACIADO_ENTRE_LINEAS * 8, COL_VERDE);
    dibujar_texto_8x8("1 linea: 100 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 9, COL_GRIS_CLARO);
    dibujar_texto_8x8("2 lineas: 200 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 10, COL_GRIS_CLARO);
    dibujar_texto_8x8("3 lineas: 400 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 11, COL_GRIS_CLARO);
    dibujar_texto_8x8("4 lineas: 800 puntos", x_ini, y + ESPACIADO_ENTRE_LINEAS * 12, COL_GRIS_CLARO);
    dibujar_texto_8x8("Bajar manual: 10pt por casilla", x_ini, y + ESPACIADO_ENTRE_LINEAS * 13, COL_GRIS_CLARO);

    dibujar_linea_horizontal(x_ini, x_fin, y + ESPACIADO_ENTRE_LINEAS * 14 + ESPACIADO_ENTRE_LINEAS / 2);

    dibujar_texto_8x8("VELOCIDAD", x_ini, y + ESPACIADO_ENTRE_LINEAS * 15, COL_VERDE);
    dibujar_texto_8x8("Cada 10 piezas +3% velocidad", x_ini, y + ESPACIADO_ENTRE_LINEAS * 16, COL_GRIS_CLARO);
    dibujar_texto_8x8("Inicio: 1000ms por caida", x_ini, y + ESPACIADO_ENTRE_LINEAS * 17, COL_GRIS_CLARO);
}