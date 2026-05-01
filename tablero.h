#ifndef TABLERO_H_INCLUDED
#define TABLERO_H_INCLUDED

#define FILAS 20
#define COLUMNAS 10

void tablero_inicializar();
int tablero_leer(int fila, int columna);
void tablero_escribir(int fila, int columna, int valor);


#endif // TABLERO_H_INCLUDED
