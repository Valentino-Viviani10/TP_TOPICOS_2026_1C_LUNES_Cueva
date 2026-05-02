#ifndef JUEGO_H_INCLUDED
#define JUEGO_H_INCLUDED

#define JUEGO_X 120
#define JUEGO_Y 20
#define JUEGO_ANCHO 80
#define JUEGO_ALTO 160

void juego_inicializar(int ancho, int alto);

void juego_mover_izquierda();
void juego_mover_derecha();
void juego_caer();

int juego_obtener_x();
int juego_obtener_y();

int juego_obtener_marco_x();
int juego_obtener_marco_y();


#endif // JUEGO_H_INCLUDED
