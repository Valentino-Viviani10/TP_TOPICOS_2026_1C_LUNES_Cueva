#include "juego.h"
#include "tetrominos.h"

static int pos_x;
static int pos_y;

void juego_inicializar()
{
    pos_x = JUEGO_X + 30;
    pos_y = JUEGO_Y + 1;
}

void juego_mover_izquierda()
{
    if(pos_x > JUEGO_X + 5){
        pos_x = pos_x - 10;
    }
}

void juego_mover_derecha()
{
    if(pos_x < JUEGO_X + JUEGO_ANCHO - 15){
        pos_x = pos_x + 10;
    }
}

void juego_caer(int alto)
{
    pos_y = pos_y + 1;

    if(pos_y > JUEGO_Y + JUEGO_ALTO - 4){
        pos_y = JUEGO_Y + 1;
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
