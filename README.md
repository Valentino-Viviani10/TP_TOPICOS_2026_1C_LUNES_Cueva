# TP_TOPICOS_2026_1C_LUNES_CUEVA — Tetris

Trabajo Práctico de Tópicos de Programación — 1er cuatrimestre 2026  
Grupo: **CUEVA** | Integrantes: Viviani Valentino, Bestene Valentin Ezequiel, Fernandez Sergio Gabriel

---

## Requisitos previos

- [Code::Blocks 25.03](https://www.codeblocks.org/downloads/binaries/) —
elige su sistema operativo y elige la opción con compilador MinGW incluido
- [Biblioteca GBT](https://gitlab.com/RodrigoMaranzana/libgbt-dist ) — descargar el release correspondiente desde el repositorio

---

## Paso 1 — Descomprimir la biblioteca GBT

Descomprimir el archivo de GBT usando **7-Zip** con la opción **Extract Here**.  
Dentro encontrarás en la sección `\release` la biblioteca GBT.

---

## Paso 2 — Crear el proyecto en Code::Blocks

1. Abrir Code::Blocks
2. Ir a **File → New → Project**
3. Seleccionar **Console application**, lenguaje **C**
4. Elegir un nombre y directorio para el proyecto
5. Copiar la carpeta de la biblioteca GBT a la sección lib\ de su proyecto.

---

## Paso 3 — Configurar el linker

1. Click derecho sobre el nombre del proyecto → **Build options**
2. Asegurarse de estar en el **Build target: Debug**
3. Ir a la solapa **Linker settings**
4. En **Other linker options** agregar: `-lgbt`

---

## Paso 4 — Configurar los directorios de búsqueda

1. Ir a la solapa **Search Directories**
2. En el tab **Compiler** → botón **Add** → agregar la ruta a la carpeta `include/` de GBT
3. En el tab **Linker** → botón **Add** → agregar la ruta a la carpeta `lib/` de GBT
4. Presionar **OK**

---

## Paso 5 — Agregar los archivos del proyecto

Copiar todos los archivos `.c` y `.h` del grupo dentro de la carpeta del proyecto.  
Desde Code::Blocks, click derecho sobre el proyecto → **Add files** → seleccionar todos los `.c`.

La estructura esperada es:

```
proyecto/
├── main.c
├── colores.c / colores.h
├── config.c  / config.h
├── dibujar.c / dibujar.h
├── fuentes.c / fuentes.h
├── fuentes_7x9.c / fuentes_7x9.h
├── instrucciones.c / instrucciones.h
├── juego.c   / juego.h
├── puntuaciones.c  / puntuaciones.h
├── tablero.c / tablero.h
├── tetrominos.c / tetrominos.h
├── tetris.c / tetris.h
├── GBT/
│   └── gbt.h
├── doc/
└── img/
```

---

## Paso 6 — Copiar el DLL

Copiar el archivo `gbt.dll` a la carpeta donde Code::Blocks genera el ejecutable, normalmente:
```
proyecto/bin/Debug/
```
Sin este paso el programa compila pero no ejecuta.

---

## Paso 7 — Compilar y ejecutar

Presionar **F9** (Build and run) o el botón correspondiente.  
El juego debe abrir una ventana gráfica.

---

## Argumentos de línea de comandos

El juego acepta argumentos opcionales para definir resolución y escala al iniciar:

```
tetris.exe -r [CGA|VGA] -e [escala]
```

Ejemplos:

```
tetris.exe -r CGA -e 2      → resolución 320x200, escala 2x
tetris.exe -r VGA -e 1      → resolución 640x480, escala 1x
tetris.exe                  → usa la configuración guardada (o defaults)
```

Resoluciones disponibles:

| Resolución | Tamaño   |
|------------|----------|
| CGA        | 320×200  |
| VGA        | 640×480  |

Escalas válidas: 1 a 4 para CGA, 1 a 2 para VGA.

---

## Controles

| Tecla         | Acción                        |
|---------------|-------------------------------|
| ← →           | Mover pieza                   |
| ↓             | Bajar pieza manualmente       |
| Z             | Rotar izquierda               |
| X             | Rotar derecha                 |
| P             | Pausar / reanudar             |
| ESC           | Menú de pausa (guardar/salir) |

---

## Menú de configuración

Desde el menú principal → **CONFIGURACION**:

- **← →** sobre una opción para cambiar su valor
- **↑ ↓** para moverse entre opciones
- **Enter** para guardar y volver al menú

Opciones configurables:

- Velocidad de caída inicial (100 ms a 2000 ms, de a 50 ms)
- Resolución lógica (CGA / VGA)
- Paleta de colores (CGA / Retro GB / Cyberpunk)

La configuración se guarda en `config.cfg` y se carga automáticamente al iniciar.

---

## Modos de juego

**Tetris Clásico** — tablero de 10×20, reglas estándar.  
**Tetris DX** — tablero de ancho variable (8 a 16 columnas), tablero circular en los bordes, piezas adicionales.