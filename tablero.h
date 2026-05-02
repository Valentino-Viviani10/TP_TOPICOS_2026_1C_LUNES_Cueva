//<<<<<<< HEAD
#ifndef TABLERO_H
#define TABLERO_H

#include <stdlib.h>
/*=======
#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED
>>>>>>> origin/master */

#define FILAS 20
#define COLUMNAS 10

//<<<<<<< HEAD
int** crear_tablero(int filas, int columnas, size_t tamElem);

void destruir_tablero(int** tablero, int filas);

void eliminar_fila_y_bajar(int** tablero, int fila_a_borrar,int columnas);

#endif
/*=======
void tablero_inicializar();
int tablero_leer(int fila, int columna);
void tablero_escribir(int fila, int columna, int valor);


#endif // TABLERO_H_INCLUDED
>>>>>>> origin/master*/
