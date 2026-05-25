#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

typedef struct {
    int velocidad_caida_ms;
    int paleta_id;
    int resolucion;
    int escala;
} Config;

extern int escala_ui;

int guardar_config(const Config *config, const char *nomArch);

int cargar_config(Config *config, const char *nomArch);

int parsearResolucion(int argc, char *argv[], int *ancho, int *alto, int *escala);

#endif // CONFIG_H_INCLUDED
