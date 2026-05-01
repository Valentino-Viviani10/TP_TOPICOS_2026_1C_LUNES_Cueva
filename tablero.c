#include "tablero.h"

static int tablero[FILAS][COLUMNAS];

void tablero_inicializar()
{
    int i;
    int j;

    for(i = 0; i < FILAS; i++)
    {
        for(j = 0; j < COLUMNAS; j++)
        {
            tablero[i][j] = 0;
        }
    }
}

int tablero_leer(int fila, int columna)
{
    return tablero[fila][columna];
}

void tablero_escribir(int fila, int columna, int valor)
{
    tablero[fila][columna] = valor;
}
