#include "fuentes_7x9.h"
#include "GBT/gbt.h"

static const int  F79_ESPACIO_ANCHO = 3;

// A - ancho 5
static const char FP_A[9][6] = {
    "01110",
    "10001",
    "10001",
    "10001",
    "11111",
    "10001",
    "10001",
    "10001",
    "10001"
};
static const int FP_A_ANCHO = 5;

// B - ancho 4
static const char FP_B[9][6] = {
    "1111",
    "1001",
    "1001",
    "1111",
    "1001",
    "1001",
    "1001",
    "1001",
    "1111"
};
static const int FP_B_ANCHO = 4;

// C - ancho 4
static const char FP_C[9][6] = {
    "0111",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "0111"
};
static const int FP_C_ANCHO = 4;

// D - ancho 4
static const char FP_D[9][6] = {
    "1110",
    "1001",
    "1001",
    "1001",
    "1001",
    "1001",
    "1001",
    "1001",
    "1110"
};
static const int FP_D_ANCHO = 4;

// E - ancho 4
static const char FP_E[9][6] = {
    "1111",
    "1000",
    "1000",
    "1110",
    "1000",
    "1000",
    "1000",
    "1000",
    "1111"
};
static const int FP_E_ANCHO = 4;

// F - ancho 4
static const char FP_F[9][6] = {
    "1111",
    "1000",
    "1000",
    "1110",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000"
};
static const int FP_F_ANCHO = 4;

// G - ancho 4
static const char FP_G[9][6] = {
    "0111",
    "1000",
    "1000",
    "1000",
    "1011",
    "1001",
    "1001",
    "1001",
    "0111"
};
static const int FP_G_ANCHO = 4;

// H - ancho 5
static const char FP_H[9][6] = {
    "10001",
    "10001",
    "10001",
    "11111",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001"
};
static const int FP_H_ANCHO = 5;

// I - ancho 1
static const char FP_I[9][2] = {
    "1",
    "1",
    "1",
    "1",
    "1",
    "1",
    "1",
    "1",
    "1"
};
static const int FP_I_ANCHO = 1;

// J - ancho 3
static const char FP_J[9][4] = {
    "001",
    "001",
    "001",
    "001",
    "001",
    "001",
    "101",
    "101",
    "010"
};
static const int FP_J_ANCHO = 3;

// K - ancho 4
static const char FP_K[9][6] = {
    "1001",
    "1001",
    "1010",
    "1100",
    "1100",
    "1010",
    "1001",
    "1001",
    "1001"
};
static const int FP_K_ANCHO = 4;

// L - ancho 4
static const char FP_L[9][6] = {
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000",
    "1111"
};
static const int FP_L_ANCHO = 4;

// M - ancho 7
static const char FP_M[9][8] = {
    "1000001",
    "1100011",
    "1010101",
    "1001001",
    "1000001",
    "1000001",
    "1000001",
    "1000001",
    "1000001"
};
static const int FP_M_ANCHO = 7;

// N - ancho 5
static const char FP_N[9][6] = {
    "10001",
    "11001",
    "10101",
    "10011",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001"
};
static const int FP_N_ANCHO = 5;

// O - ancho 5
static const char FP_O[9][6] = {
    "01110",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "01110"
};
static const int FP_O_ANCHO = 5;

// P - ancho 4
static const char FP_P[9][6] = {
    "1111",
    "1001",
    "1001",
    "1111",
    "1000",
    "1000",
    "1000",
    "1000",
    "1000"
};
static const int FP_P_ANCHO = 4;

// Q - ancho 5
static const char FP_Q[9][6] = {
    "01110",
    "10001",
    "10001",
    "10001",
    "10001",
    "10101",
    "10011",
    "10001",
    "01110"
};
static const int FP_Q_ANCHO = 5;

// R - ancho 4
static const char FP_R[9][6] = {
    "1111",
    "1001",
    "1001",
    "1110",
    "1100",
    "1010",
    "1001",
    "1001",
    "1001"
};
static const int FP_R_ANCHO = 4;

// S - ancho 4
static const char FP_S[9][6] = {
    "0111",
    "1000",
    "1000",
    "0110",
    "0001",
    "0001",
    "0001",
    "0001",
    "1110"
};
static const int FP_S_ANCHO = 4;

// T - ancho 5
static const char FP_T[9][6] = {
    "11111",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100"
};
static const int FP_T_ANCHO = 5;

// U - ancho 5
static const char FP_U[9][6] = {
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "01110"
};
static const int FP_U_ANCHO = 5;

// V - ancho 5
static const char FP_V[9][6] = {
    "10001",
    "10001",
    "10001",
    "10001",
    "10001",
    "01010",
    "01010",
    "00100",
    "00100"
};
static const int FP_V_ANCHO = 5;

// W - ancho 7
static const char FP_W[9][8] = {
    "1000001",
    "1000001",
    "1000001",
    "1000001",
    "1001001",
    "1001001",
    "1010101",
    "1100011",
    "1000001"
};
static const int FP_W_ANCHO = 7;

// X - ancho 5
static const char FP_X[9][6] = {
    "10001",
    "10001",
    "01010",
    "01010",
    "00100",
    "01010",
    "01010",
    "10001",
    "10001"
};
static const int FP_X_ANCHO = 5;

// Y - ancho 5
static const char FP_Y[9][6] = {
    "10001",
    "10001",
    "01010",
    "01010",
    "00100",
    "00100",
    "00100",
    "00100",
    "00100"
};
static const int FP_Y_ANCHO = 5;

// Z - ancho 5
static const char FP_Z[9][6] = {
    "11111",
    "00001",
    "00001",
    "00010",
    "00100",
    "01000",
    "10000",
    "10000",
    "11111"
};
static const int FP_Z_ANCHO = 5;

// 0 - ancho 5
static const char FP_0[9][6] = {
    "01110",
    "10001",
    "10001",
    "10011",
    "10101",
    "11001",
    "10001",
    "10001",
    "01110"
};
static const int FP_0_ANCHO = 5;

// 1 - ancho 3
static const char FP_1[9][4] = {
    "010",
    "110",
    "010",
    "010",
    "010",
    "010",
    "010",
    "010",
    "111"
};
static const int FP_1_ANCHO = 3;

// 2 - ancho 4
static const char FP_2[9][6] = {
    "0111",
    "1001",
    "0001",
    "0010",
    "0100",
    "1000",
    "1000",
    "1000",
    "1111"
};
static const int FP_2_ANCHO = 4;

// 3 - ancho 4
static const char FP_3[9][6] = {
    "1110",
    "0001",
    "0001",
    "1110",
    "0001",
    "0001",
    "0001",
    "0001",
    "1110"
};
static const int FP_3_ANCHO = 4;

// 4 - ancho 4
static const char FP_4[9][6] = {
    "1001",
    "1001",
    "1001",
    "1111",
    "0001",
    "0001",
    "0001",
    "0001",
    "0001"
};
static const int FP_4_ANCHO = 4;

// 5 - ancho 4
static const char FP_5[9][6] = {
    "1111",
    "1000",
    "1000",
    "1110",
    "0001",
    "0001",
    "0001",
    "0001",
    "1110"
};
static const int FP_5_ANCHO = 4;

// 6 - ancho 4
static const char FP_6[9][6] = {
    "0111",
    "1000",
    "1000",
    "1110",
    "1001",
    "1001",
    "1001",
    "1001",
    "0111"
};
static const int FP_6_ANCHO = 4;

// 7 - ancho 4
static const char FP_7[9][6] = {
    "1111",
    "0001",
    "0001",
    "0010",
    "0100",
    "0100",
    "0100",
    "0100",
    "0100"
};
static const int FP_7_ANCHO = 4;

// 8 - ancho 4
static const char FP_8[9][6] = {
    "0110",
    "1001",
    "1001",
    "0110",
    "1001",
    "1001",
    "1001",
    "1001",
    "0110"
};
static const int FP_8_ANCHO = 4;

// 9 - ancho 4
static const char FP_9[9][6] = {
    "0110",
    "1001",
    "1001",
    "1001",
    "0111",
    "0001",
    "0001",
    "0001",
    "0110"
};
static const int FP_9_ANCHO = 4;

// : - ancho 2
static const char FP_DOS_PUNTOS[9][4] = {
    "00",
    "11",
    "11",
    "00",
    "00",
    "11",
    "11",
    "00",
    "00"
};
static const int FP_DOS_PUNTOS_ANCHO = 2;

// - - ancho 3
static const char FP_GUION[9][4] = {
    "000",
    "000",
    "000",
    "111",
    "000",
    "000",
    "000",
    "000",
    "000"
};
static const int FP_GUION_ANCHO = 3;

// . - ancho 2
static const char FP_PUNTO[9][4] = {
    "00",
    "00",
    "00",
    "00",
    "00",
    "00",
    "00",
    "11",
    "11"
};
static const int FP_PUNTO_ANCHO = 2;

// < - ancho 3
static const char FP_MENOR[9][4] = {
    "001",
    "010",
    "100",
    "100",
    "100",
    "010",
    "001",
    "000",
    "000"
};
static const int FP_MENOR_ANCHO = 3;

// > - ancho 3
static const char FP_MAYOR[9][4] = {
    "100",
    "010",
    "001",
    "001",
    "001",
    "010",
    "100",
    "000",
    "000"
};
static const int FP_MAYOR_ANCHO = 3;

// + - ancho 3
static const char FP_MAS[9][4] = {
    "000",
    "010",
    "010",
    "111",
    "010",
    "010",
    "000",
    "000",
    "000"
};
static const int FP_MAS_ANCHO = 3;

// / - ancho 3
static const char FP_BARRA[9][4] = {
    "001",
    "001",
    "010",
    "010",
    "010",
    "100",
    "100",
    "000",
    "000"
};
static const int FP_BARRA_ANCHO = 3;

// % - ancho 5
static const char FP_PORCENTAJE[9][6] = {
    "10010",
    "10010",
    "00010",
    "00100",
    "00100",
    "01000",
    "01011",
    "00001",
    "00001"
};
static const int FP_PORCENTAJE_ANCHO = 5;

typedef struct {
    const char (*matriz)[8];
    int ancho;
} tCaracter7x9;

static tCaracter7x9 obtener_caracter_7x9(char caracter)
{
    tCaracter7x9 car;

    switch(caracter)
    {
        case 'A': case 'a': car.matriz = (const char (*)[8])FP_A;
                            car.ancho = FP_A_ANCHO;
                            break;
        case 'B': case 'b': car.matriz = (const char (*)[8])FP_B;
                            car.ancho = FP_B_ANCHO;
                            break;
        case 'C': case 'c': car.matriz = (const char (*)[8])FP_C;
                            car.ancho = FP_C_ANCHO;
                            break;
        case 'D': case 'd': car.matriz = (const char (*)[8])FP_D;
                            car.ancho = FP_D_ANCHO;
                            break;
        case 'E': case 'e': car.matriz = (const char (*)[8])FP_E;
                            car.ancho = FP_E_ANCHO;
                            break;
        case 'F': case 'f': car.matriz = (const char (*)[8])FP_F;
                            car.ancho = FP_F_ANCHO;
                            break;
        case 'G': case 'g': car.matriz = (const char (*)[8])FP_G;
                            car.ancho = FP_G_ANCHO;
                            break;
        case 'H': case 'h': car.matriz = (const char (*)[8])FP_H;
                            car.ancho = FP_H_ANCHO;
                            break;
        case 'I': case 'i': car.matriz = (const char (*)[8])FP_I;
                            car.ancho = FP_I_ANCHO;
                            break;
        case 'J': case 'j': car.matriz = (const char (*)[8])FP_J;
                            car.ancho = FP_J_ANCHO;
                            break;
        case 'K': case 'k': car.matriz = (const char (*)[8])FP_K;
                            car.ancho = FP_K_ANCHO;
                            break;
        case 'L': case 'l': car.matriz = (const char (*)[8])FP_L;
                            car.ancho = FP_L_ANCHO;
                            break;
        case 'M': case 'm': car.matriz = (const char (*)[8])FP_M;
                            car.ancho = FP_M_ANCHO;
                            break;
        case 'N': case 'n': car.matriz = (const char (*)[8])FP_N;
                            car.ancho = FP_N_ANCHO;
                            break;
        case 'O': case 'o': car.matriz = (const char (*)[8])FP_O;
                            car.ancho = FP_O_ANCHO;
                            break;
        case 'P': case 'p': car.matriz = (const char (*)[8])FP_P;
                            car.ancho = FP_P_ANCHO;
                            break;
        case 'Q': case 'q': car.matriz = (const char (*)[8])FP_Q;
                            car.ancho = FP_Q_ANCHO;
                            break;
        case 'R': case 'r': car.matriz = (const char (*)[8])FP_R;
                            car.ancho = FP_R_ANCHO;
                            break;
        case 'S': case 's': car.matriz = (const char (*)[8])FP_S;
                            car.ancho = FP_S_ANCHO;
                            break;
        case 'T': case 't': car.matriz = (const char (*)[8])FP_T;
                            car.ancho = FP_T_ANCHO;
                            break;
        case 'U': case 'u': car.matriz = (const char (*)[8])FP_U;
                            car.ancho = FP_U_ANCHO;
                            break;
        case 'V': case 'v': car.matriz = (const char (*)[8])FP_V;
                            car.ancho = FP_V_ANCHO;
                            break;
        case 'W': case 'w': car.matriz = (const char (*)[8])FP_W;
                            car.ancho = FP_W_ANCHO;
                            break;
        case 'X': case 'x': car.matriz = (const char (*)[8])FP_X;
                            car.ancho = FP_X_ANCHO;
                            break;
        case 'Y': case 'y': car.matriz = (const char (*)[8])FP_Y;
                            car.ancho = FP_Y_ANCHO;
                            break;
        case 'Z': case 'z': car.matriz = (const char (*)[8])FP_Z;
                            car.ancho = FP_Z_ANCHO;
                            break;
        case '0': car.matriz = (const char (*)[8])FP_0;
                  car.ancho = FP_0_ANCHO;
                  break;
        case '1': car.matriz = (const char (*)[8])FP_1;
                  car.ancho = FP_1_ANCHO;
                  break;
        case '2': car.matriz = (const char (*)[8])FP_2;
                  car.ancho = FP_2_ANCHO;
                  break;
        case '3': car.matriz = (const char (*)[8])FP_3;
                  car.ancho = FP_3_ANCHO;
                  break;
        case '4': car.matriz = (const char (*)[8])FP_4;
                  car.ancho = FP_4_ANCHO;
                  break;
        case '5': car.matriz = (const char (*)[8])FP_5;
                  car.ancho = FP_5_ANCHO;
                  break;
        case '6': car.matriz = (const char (*)[8])FP_6;
                  car.ancho = FP_6_ANCHO;
                  break;
        case '7': car.matriz = (const char (*)[8])FP_7;
                  car.ancho = FP_7_ANCHO;
                  break;
        case '8': car.matriz = (const char (*)[8])FP_8;
                  car.ancho = FP_8_ANCHO;
                  break;
        case '9': car.matriz = (const char (*)[8])FP_9;
                  car.ancho = FP_9_ANCHO;
                  break;
        case ':': car.matriz = (const char (*)[8])FP_DOS_PUNTOS;
                  car.ancho = FP_DOS_PUNTOS_ANCHO;
                  break;
        case '-': car.matriz = (const char (*)[8])FP_GUION;
                  car.ancho = FP_GUION_ANCHO;
                  break;
        case '.': car.matriz = (const char (*)[8])FP_PUNTO;
                  car.ancho = FP_PUNTO_ANCHO;
                  break;
        case '<': car.matriz = (const char (*)[8])FP_MENOR;
                  car.ancho = FP_MENOR_ANCHO;
                  break;
        case '>': car.matriz = (const char (*)[8])FP_MAYOR;
                  car.ancho = FP_MAYOR_ANCHO;
                  break;
        case '+': car.matriz = (const char (*)[8])FP_MAS;
                  car.ancho = FP_MAS_ANCHO;
                  break;
        case '/': car.matriz = (const char (*)[8])FP_BARRA;
                  car.ancho = FP_BARRA_ANCHO;
                  break;
        case '%': car.matriz = (const char (*)[8])FP_PORCENTAJE;
                  car.ancho = FP_PORCENTAJE_ANCHO;
                  break;
        default:  car.matriz = NULL;
                  car.ancho = F79_ESPACIO_ANCHO;
                  break;
    }

    return car;
}

static void dibujar_caracter_7x9(char caracter, uint16_t x, uint16_t y, uint8_t color)
{
    int fila;
    int col;
    tCaracter7x9 car;

    car = obtener_caracter_7x9(caracter);

    if(car.matriz == NULL){
        return;
    }

    for(fila = 0; fila < F79_ALTO; fila++){
        for(col = 0; col < car.ancho; col++)
        {
            if(car.matriz[fila][col] == '1')
            {
                gbt_dibujar_pixel(x + col, y + fila, color);
            }
        }
    }
}

void dibujar_texto_7x9(const char texto[], uint16_t x, uint16_t y, uint8_t color){
    int i;
    uint16_t cursor_x;
    tCaracter7x9 car;

    i = 0;
    cursor_x = x;

    while(texto[i] != '\0'){
        car = obtener_caracter_7x9(texto[i]);
        dibujar_caracter_7x9(texto[i], cursor_x, y, color);
        cursor_x += car.ancho + F79_ESPACIO;
        i++;
    }
}

int calcular_ancho_texto_7x9(const char texto[]){
    int i;
    int ancho_total;
    tCaracter7x9 car;

    i = 0;
    ancho_total = 0;

    while(texto[i] != '\0'){
        car = obtener_caracter_7x9(texto[i]);
        ancho_total += car.ancho + F79_ESPACIO;
        i++;
    }

    if(ancho_total > 0){
        ancho_total -= F79_ESPACIO;
    }

    return ancho_total;
}
