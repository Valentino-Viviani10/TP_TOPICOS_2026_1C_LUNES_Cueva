#include "juego.h"
#include "tetrominos.h"

static int pos_x;
static int pos_y;

void juego_inicializar()
{
    pos_x = 150;
    pos_y = 40;
}

void juego_mover_izquierda()
{
    pos_x = pos_x - 10;
}

void juego_mover_derecha()
{
    pos_x = pos_x + 10;
}

int juego_obtener_x()
{
    return pos_x;
}

int juego_obtener_y()
{
    return pos_y;
}
