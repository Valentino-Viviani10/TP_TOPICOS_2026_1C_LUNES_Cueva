#include <stdio.h>
#include <stdlib.h>

void sumar_puntos(int lineas_completadas, int casillasManuales, int *puntaje,
                  int nivel_velocidad) {
  if (lineas_completadas < 0 || casillasManuales < 0)
    return;

  int puntos_lineas = 0;

  switch (lineas_completadas) {
  case 1:
    puntos_lineas = 400;
    break;
  case 2:
    puntos_lineas = 1000;
    break;
  case 3:
    puntos_lineas = 3000;
    break;
  case 4:
    puntos_lineas = 12000;
    break;
  default:
    break;
  }

  // Bonus del 10% por cada nivel de velocidad
  puntos_lineas += puntos_lineas * nivel_velocidad / 10;

  *puntaje += puntos_lineas;
  *puntaje += casillasManuales * 10;
}
