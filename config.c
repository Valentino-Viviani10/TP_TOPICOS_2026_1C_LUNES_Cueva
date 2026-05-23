#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

#define CGA_ANCHO 320
#define CGA_ALTO  200
#define VGA_ANCHO 640
#define VGA_ALTO  480

int guardar_config(Config *config, const char *nomArch) {
    FILE *arch = fopen(nomArch, "wb");
    if (!arch) return 0;

    int ok = fwrite(config, sizeof(Config), 1, arch) == 1;

    fclose(arch);

    return ok;
}

int cargar_config(Config *config, const char *nomArch) {
    FILE *arch = fopen(nomArch, "rb");
    if (!arch) return 0;

    int ok = fread(config, sizeof(Config), 1, arch) == 1;

    fclose(arch);

    return ok;
}

// Devuelve 1 si encontró argumentos válidos, 0 si no había args
int parsearResolucion(int argc, char *argv[], int *ancho, int *alto, int *escala) {
    if (argc < 2) return 0;  // sin args, no hace nada

    // Resolución (obligatoria si hay args)
    if (strcmp(argv[1], "VGA") == 0 || strcmp(argv[1], "vga") == 0) {
        *ancho = VGA_ANCHO;
        *alto  = VGA_ALTO;
    } else if (strcmp(argv[1], "CGA") == 0 || strcmp(argv[1], "cga") == 0) {
        *ancho = CGA_ANCHO;
        *alto  = CGA_ALTO;
    } else {
        fprintf(stderr, "Resolucion invalida '%s'. Use CGA o VGA.\n", argv[1]);
        return -1;  // error
    }

    // Escala (opcional)
    if (argc > 2) {
        int e = atoi(argv[2]);
        int maxEscala = (*ancho == VGA_ANCHO) ? 2 : 4;
        if (e <= 0 || e > maxEscala) {
            fprintf(stderr, "Escala invalida '%s'. Ajustando al maximo (%d).\n", argv[2], maxEscala);
            e = maxEscala;
        }
        *escala = e;
    }

    return 1;
}