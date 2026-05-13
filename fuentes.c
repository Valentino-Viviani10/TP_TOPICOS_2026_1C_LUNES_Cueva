#include "fuentes.h"
#include "GBT/gbt.h"

static const char FUENTE_ESPACIO_MAT[7][6] = {
    "00000",
    "00000",
    "00000",
    "00000",
    "00000",
    "00000",
    "00000"
};

static const char FUENTE_A[7][6] = {
    "01110",
    "10001",
    "10001",
    "11111",
    "10001",
    "10001",
    "10001"
};

/*static const char FUENTE_A[7][6] = {
    "11111",
    "11111",
    "11111",
    "11111",
    "11111",
    "11111",
    "11111"
}; PRUEBA PARA CONFIRMAR QUE ESTA USANDO ESTA FUENTE*/

static const char FUENTE_B[7][6] = {
    "11110",
    "10001",
    "10001",
    "11110",
    "10001",
    "10001",
    "11110"
};

static const char FUENTE_C[7][6] = {
    "01111",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "01111"
};

static const char FUENTE_D[7][6] = {
    "11110",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "11110"
};

static const char FUENTE_E[7][6] = {
    "11111",
    "10000",
    "10000",
    "11110",
    "10000",
    "10000",
    "11111"
};

static const char FUENTE_F[7][6] = {
    "11111",
    "10000",
    "10000",
    "11110",
    "10000",
    "10000",
    "10000"
};

static const char FUENTE_G[7][6] = {
    "01111",
    "10000",
    "10000",
    "10111",
    "10001",
    "10001",
    "01111"
};

static const char FUENTE_H[7][6] = {
    "10001",
    "10001",
    "10001",
    "11111",
    "10001",
    "10001",
    "10001"
};

static const char FUENTE_I[7][6] = {
    "11111",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100",
    "11111"
};

static const char FUENTE_J[7][6] = {
    "00111",
    "00010",
    "00010",
    "00010",
    "10010",
    "10010",
    "01100"
};

static const char FUENTE_K[7][6] = {
    "10001",
    "10010",
    "10100",
    "11000",
    "10100",
    "10010",
    "10001"
};

static const char FUENTE_L[7][6] = {
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "10000",
    "11111"
};

static const char FUENTE_M[7][6] = {
    "10001",
    "11011",
    "10101",
    "10101",
    "10001",
    "10001",
    "10001"
};

static const char FUENTE_N[7][6] = {
    "10001",
    "11001",
    "10101",
    "10011",
    "10001",
    "10001",
    "10001"
};

static const char FUENTE_O[7][6] = {
    "01110",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "01110"
};

static const char FUENTE_P[7][6] = {
    "11110",
    "10001",
    "10001",
    "11110",
    "10000",
    "10000",
    "10000"
};

static const char FUENTE_Q[7][6] = {
    "01110",
    "10001",
    "10001",
    "10001",
    "10101",
    "10010",
    "01101"
};

static const char FUENTE_R[7][6] = {
    "11110",
    "10001",
    "10001",
    "11110",
    "10100",
    "10010",
    "10001"
};

static const char FUENTE_S[7][6] = {
    "01111",
    "10000",
    "10000",
    "01110",
    "00001",
    "00001",
    "11110"
};

static const char FUENTE_T[7][6] = {
    "11111",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100"
};

static const char FUENTE_U[7][6] = {
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "01110"
};

static const char FUENTE_V[7][6] = {
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "01010",
    "00100"
};

static const char FUENTE_W[7][6] = {
    "10001",
    "10001",
    "10001",
    "10101",
    "10101",
    "10101",
    "01010"
};

static const char FUENTE_X[7][6] = {
    "10001",
    "10001",
    "01010",
    "00100",
    "01010",
    "10001",
    "10001"
};

static const char FUENTE_Y[7][6] = {
    "10001",
    "10001",
    "01010",
    "00100",
    "00100",
    "00100",
    "00100"
};

static const char FUENTE_Z[7][6] = {
    "11111",
    "00001",
    "00010",
    "00100",
    "01000",
    "10000",
    "11111"
};

static const char FUENTE_0[7][6] = {
    "01110",
    "10001",
    "10011",
    "10101",
    "11001",
    "10001",
    "01110"
};

static const char FUENTE_1[7][6] = {
    "00100",
    "01100",
    "00100",
    "00100",
    "00100",
    "00100",
    "01110"
};

static const char FUENTE_2[7][6] = {
    "01110",
    "10001",
    "00001",
    "00010",
    "00100",
    "01000",
    "11111"
};

static const char FUENTE_3[7][6] = {
    "11110",
    "00001",
    "00001",
    "01110",
    "00001",
    "00001",
    "11110"
};

static const char FUENTE_4[7][6] = {
    "10010",
    "10010",
    "10010",
    "11111",
    "00010",
    "00010",
    "00010"
};

static const char FUENTE_5[7][6] = {
    "11111",
    "10000",
    "10000",
    "11110",
    "00001",
    "00001",
    "11110"
};

static const char FUENTE_6[7][6] = {
    "01111",
    "10000",
    "10000",
    "11110",
    "10001",
    "10001",
    "01110"
};

static const char FUENTE_7[7][6] = {
    "11111",
    "00001",
    "00010",
    "00100",
    "01000",
    "01000",
    "01000"
};

static const char FUENTE_8[7][6] = {
    "01110",
    "10001",
    "10001",
    "01110",
    "10001",
    "10001",
    "01110"
};

static const char FUENTE_9[7][6] = {
    "01110",
    "10001",
    "10001",
    "01111",
    "00001",
    "00001",
    "11110"
};

static const char FUENTE_DOS_PUNTOS[7][6] = {
    "00000",
    "00100",
    "00100",
    "00000",
    "00100",
    "00100",
    "00000"
};

static const char FUENTE_GUION[7][6] = {
    "00000",
    "00000",
    "00000",
    "11111",
    "00000",
    "00000",
    "00000"
};

static const char FUENTE_PUNTO[7][6] = {
    "00000",
    "00000",
    "00000",
    "00000",
    "00000",
    "01100",
    "01100"
};

static const char (*obtener_matriz_caracter(char caracter))[6]
{
    switch(caracter)
    {
        case 'A': case 'a': return FUENTE_A;
        case 'B': case 'b': return FUENTE_B;
        case 'C': case 'c': return FUENTE_C;
        case 'D': case 'd': return FUENTE_D;
        case 'E': case 'e': return FUENTE_E;
        case 'F': case 'f': return FUENTE_F;
        case 'G': case 'g': return FUENTE_G;
        case 'H': case 'h': return FUENTE_H;
        case 'I': case 'i': return FUENTE_I;
        case 'J': case 'j': return FUENTE_J;
        case 'K': case 'k': return FUENTE_K;
        case 'L': case 'l': return FUENTE_L;
        case 'M': case 'm': return FUENTE_M;
        case 'N': case 'n': return FUENTE_N;
        case 'O': case 'o': return FUENTE_O;
        case 'P': case 'p': return FUENTE_P;
        case 'Q': case 'q': return FUENTE_Q;
        case 'R': case 'r': return FUENTE_R;
        case 'S': case 's': return FUENTE_S;
        case 'T': case 't': return FUENTE_T;
        case 'U': case 'u': return FUENTE_U;
        case 'V': case 'v': return FUENTE_V;
        case 'W': case 'w': return FUENTE_W;
        case 'X': case 'x': return FUENTE_X;
        case 'Y': case 'y': return FUENTE_Y;
        case 'Z': case 'z': return FUENTE_Z;

        case '0': return FUENTE_0;
        case '1': return FUENTE_1;
        case '2': return FUENTE_2;
        case '3': return FUENTE_3;
        case '4': return FUENTE_4;
        case '5': return FUENTE_5;
        case '6': return FUENTE_6;
        case '7': return FUENTE_7;
        case '8': return FUENTE_8;
        case '9': return FUENTE_9;

        case ':': return FUENTE_DOS_PUNTOS;
        case '-': return FUENTE_GUION;
        case '.': return FUENTE_PUNTO;
        case ' ': return FUENTE_ESPACIO_MAT;

        default:
            return FUENTE_ESPACIO_MAT;
    }
}

static void dibujar_caracter_5x7(char caracter, uint16_t x, uint16_t y, uint8_t color)
{
    int fila;
    int col;
    const char (*matriz)[6];

    matriz = obtener_matriz_caracter(caracter);

    for(fila = 0; fila < FUENTE_ALTO; fila++)
    {
        for(col = 0; col < FUENTE_ANCHO; col++)
        {
            if(matriz[fila][col] == '1')
            {
                gbt_dibujar_pixel(x + col, y + fila, color);
            }
        }
    }
}

void dibujar_texto_5x7(const char texto[], uint16_t x, uint16_t y, uint8_t color)
{
    int i;

    i = 0;

    while(texto[i] != '\0')
    {
        dibujar_caracter_5x7(texto[i], x + i * FUENTE_AVANCE, y, color);
        i++;
    }
}

int calcular_ancho_texto_5x7(const char texto[])
{
    int cantidad;

    cantidad = 0;

    while(texto[cantidad] != '\0')
    {
        cantidad++;
    }

    return cantidad * FUENTE_AVANCE;
}
