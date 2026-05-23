#include "colores.h"

/*
    *Cyberpunk
    Pieza I: Coral neón (#FF5349)
    Pieza L: Amarillo flúor (#E6FF00)
    Pieza J: Morado eléctrico (#9D00FF)
    Pieza O: Fucsia (#FF0055)
    Pieza S: Turquesa brillante (#00FFC4)
    Pieza Z: Verde lima (#76FF03)
    Pieza T: Azul neón (#009FFF)
*/

/*
    *Retro Game Boy
    Pieza I: Negro oscuro (#000000)
    Pieza L: Verde oliva oscuro (#3C5E3B)
    Pieza J: Verde menta (#7C9E7D)
    Pieza O: Gris oscuro (#4A4A4A)
    Pieza S: Verde clásico (#6FA86F)
    Pieza Z: Verde claro (#9EBC9E)
    Pieza T: Blanco hueso (#D0DDC0)
*/

tGBT_ColorRGB paletaCyberpunk[CANT_COLORES] = {
    {0x08, 0x08, 0x10}, // 0: negro profundo
    {0x13, 0x1A, 0x33}, // 1: azul oscuro neón
    {0x10, 0x2B, 0x22}, // 2: verde oscuro
    {0x10, 0x2F, 0x35}, // 3: cian oscuro
    {0x2A, 0x10, 0x1D}, // 4: rojo oscuro
    {0x76, 0xFF, 0x03}, // 5: verde lima
    {0x3B, 0x22, 0x10}, // 6: marron oscuro
    {0xD8, 0xD8, 0xE0}, // 7: gris claro
    {0x4A, 0x4A, 0x58}, // 8: gris oscuro
    {0xFF, 0x53, 0x49}, // 9: coral neón
    {0xE6, 0xFF, 0x00}, // 10: amarillo flúor
    {0x00, 0xFF, 0xC4}, // 11: turquesa brillante
    {0xFF, 0x00, 0x55}, // 12: fucsia / rojo neón
    {0x9D, 0x00, 0xFF}, // 13: morado eléctrico
    {0x00, 0x9F, 0xFF}, // 14: azul neón
    {0xFF, 0xFF, 0xFF}, // 15: transparente / blanco
    {0xFF, 0x7A, 0x00}, // 16: naranja neón
    {0x2B, 0x12, 0x44}, // 17: magenta oscuro
};

tGBT_ColorRGB paletaRetroGB[CANT_COLORES] = {
    {0x0A, 0x14, 0x0A}, // 0: casi negro verdoso
    {0x0F, 0x20, 0x0F}, // 1: negro verdoso
    {0x12, 0x28, 0x12}, // 2: verde muy oscuro
    {0x30, 0x62, 0x30}, // 3:  verde medio
    {0x4A, 0x7C, 0x3F}, // 4:  verde
    {0x5A, 0x8A, 0x3A}, // 5:  verde claro
    {0x3A, 0x6B, 0x2A}, // 6:  verde oliva
    {0x2D, 0x5A, 0x1E}, // 7:  verde bosque
    {0x4F, 0x79, 0x42}, // 8:  verde grisáceo
    {0x0A, 0x0A, 0x0A}, // 9:  negro puro
    {0x8B, 0xAC, 0x0F}, // 10: verde amarillento
    {0x9B, 0xBC, 0x0F}, // 11: verde lima
    {0xC6, 0xDE, 0x8A}, // 12: verde pálido
    {0x6F, 0xA8, 0x6F}, // 13: verde claro
    {0x9E, 0xBC, 0x9E}, // 14: verde menta
    {0xFF, 0xFF, 0xFF}, // 15: transparente
    {0xB8, 0xC7, 0xA6}, // 16: verde pálido
    {0x8D, 0x9A, 0x7B}  // 17: oliva claro
};

tGBT_ColorRGB paletaCGA[CANT_COLORES] = {
    /// 0-17: Colores CGA (18 colores)
    {0x00, 0x00, 0x00}, // 0:   Negro 
    {0x00, 0x00, 0xAA}, // 1:   Azul
    {0x00, 0xAA, 0x00}, // 2:   Verde
    {0x00, 0xAA, 0xAA}, // 3:   Cian
    {0xAA, 0x00, 0x00}, // 4:   Rojo
    {0xAA, 0x00, 0xAA}, // 5:   Magenta
    {0xAA, 0x55, 0x00}, // 6:   Marron
    {0xAA, 0xAA, 0xAA}, // 7:   Gris claro
    {0x55, 0x55, 0x55}, // 8:   Gris oscuro
    {0x55, 0x55, 0xFF}, // 9:   Azul brillante
    {0x55, 0xFF, 0x55}, // 10:  Verde brillante
    {0x55, 0xFF, 0xFF}, // 11:  Cian brillante
    {0xFF, 0x55, 0x55}, // 12:  Rojo brillante
    {0xFF, 0x55, 0xFF}, // 13:  Magenta brillante
    {0xFF, 0xFF, 0x55}, // 14:  Amarillo
    {0xFF, 0xFF, 0xFF}, // 15:  Usado como transparente por GBT
    {0xFF, 0x80, 0x00}, // 16:  Naranja
    {0x4C, 0x28, 0x82} // 17:   Purpura
};

uint8_t COL_SEM_TEXTO_PRINCIPAL;
uint8_t COL_SEM_TEXTO_SECUNDARIO;
uint8_t COL_SEM_TEXTO_IMPORTANTE;
uint8_t COL_SEM_BORDE;
uint8_t COL_SEM_ACENTO;
uint8_t COL_SEM_FONDO_1;
uint8_t COL_SEM_FONDO_2;

void inicializar_colores_semanticos(int paleta_id) {
    switch(paleta_id) {
        case 1: // RetroGB
            COL_SEM_TEXTO_PRINCIPAL  = 15;
            COL_SEM_TEXTO_SECUNDARIO = 11;
            COL_SEM_TEXTO_IMPORTANTE = 14;
            COL_SEM_BORDE            = 2;
            COL_SEM_ACENTO           = 13;
            COL_SEM_FONDO_1          = 0;
            COL_SEM_FONDO_2          = 1;
            break;
        case 2: // Cyberpunk
            COL_SEM_TEXTO_PRINCIPAL  = 9;
            COL_SEM_TEXTO_SECUNDARIO = COL_CIAN_BRILL;
            COL_SEM_TEXTO_IMPORTANTE = 16;
            COL_SEM_BORDE            = 1;
            COL_SEM_ACENTO           = COL_AMARILLO;
            COL_SEM_FONDO_1          = COL_NEGRO;
            COL_SEM_FONDO_2          = COL_GRIS_OSC;
            break;
        default: // CGA
            COL_SEM_TEXTO_PRINCIPAL  = 9;
            COL_SEM_TEXTO_SECUNDARIO = COL_GRIS_CLARO;
            COL_SEM_TEXTO_IMPORTANTE = COL_ROJO_BRILL;
            COL_SEM_BORDE            = COL_AZUL;
            COL_SEM_ACENTO           = COL_AMARILLO;
            COL_SEM_FONDO_1          = COL_NEGRO;
            COL_SEM_FONDO_2          = COL_GRIS_OSC;
            break;
    }
}