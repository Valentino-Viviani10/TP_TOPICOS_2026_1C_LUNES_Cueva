#include <stdio.h>
#include <stdlib.h>

void sumar_puntos(int lineas_completadas, int casillasManuales, int* puntaje) {
    if(lineas_completadas < 0 && casillasManuales < 0) return;

    switch(lineas_completadas) {
        case 1:
            *puntaje += 100;
            break;
        case 2:
            *puntaje += 200;
            break;
        case 3:
            *puntaje += 400;
            break;
        case 4:
            *puntaje += 800;
            break;
        default:
            break;
    }

    *puntaje += casillasManuales;
}