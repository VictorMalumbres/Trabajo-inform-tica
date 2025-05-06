#include "Tablero.h"

Tablero::Tablero(int f, int c) : filas(f), columnas(c) {
    // Constructor donde se inicializan las filas y columnas del tablero
}

void Tablero::inicializa() {
    // Por ahora no inicializamos nada en particular en el tablero
}

void Tablero::dibuja() {
    // Establecer el tamaño de las casillas (puedes ajustar este valor si lo prefieres)
    float casillaSizeX = 1.0f; // Tamaño de cada casilla en el eje X
    float casillaSizeY = 1.0f; // Tamaño de cada casilla en el eje Y

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            // Alternar colores entre blanco y negro
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);  // Blanco
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);  // Negro
            }

            // Dibujar un cuadrado por casilla
            glBegin(GL_QUADS);
            glVertex3f(j * casillaSizeX, i * casillaSizeY, 0.0f);  // Esquina inferior izquierda
            glVertex3f((j + 1) * casillaSizeX, i * casillaSizeY, 0.0f);  // Esquina inferior derecha
            glVertex3f((j + 1) * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);  // Esquina superior derecha
            glVertex3f(j * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);  // Esquina superior izquierda
            glEnd();
        }
    }
}
