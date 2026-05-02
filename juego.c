#include "juego.h"
#include "tetrominos.h"

static int marco_x;
static int marco_y;

static int pos_x;
static int pos_y;

void juego_inicializar(int ancho, int alto)
{
    marco_x = (ancho / 2) - (JUEGO_ANCHO / 2);
    marco_y = (alto / 2) - (JUEGO_ALTO / 2);

    pos_x = marco_x + 30;
    pos_y = marco_y + 1;
}

void juego_mover_izquierda()
{
    if(pos_x > marco_x + 5){
        pos_x = pos_x - 10;
    }
}

void juego_mover_derecha()
{
    if(pos_x < marco_x + JUEGO_ANCHO - 15){
        pos_x = pos_x + 10;
    }
}

void juego_caer(int alto)
{
    pos_y = pos_y + 1;

    if(pos_y > marco_y + JUEGO_ALTO - 4){
    pos_y = marco_y + 1;
    }

}

int juego_obtener_x()
{
    return pos_x;
}

int juego_obtener_y()
{
    return pos_y;
}

int juego_obtener_marco_x()
{
    return marco_x;
}

int juego_obtener_marco_y()
{
    return marco_y;
}
