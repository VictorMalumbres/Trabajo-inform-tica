#include "Tablero.h"
#include <freeglut.h>

Tablero::Tablero() {
    // Constructor de Tablero, inicializa el vector de piezas
}

void Tablero::inicializa() {
    // Primer jugador 
    piezas.push_back(new Torre(0.5f, 0.5f, 0, 255, 0));  // Torre verde
    piezas.push_back(new Reina(1.5f, 0.5f, 0, 255, 0));  // Reina verde
    piezas.push_back(new Rey(2.5f, 0.5f, 0, 255, 0));    // Rey verde
    piezas.push_back(new Torre(3.5f, 0.5f, 0, 255, 0));  // Torre verde

    piezas.push_back(new Peon(0.5f, 1.5f, 0, 255, 0));   // Peón verde
    piezas.push_back(new Peon(1.5f, 1.5f, 0, 255, 0));   // Peón verde
    piezas.push_back(new Peon(2.5f, 1.5f, 0, 255, 0));   // Peón verde
    piezas.push_back(new Peon(3.5f, 1.5f, 0, 255, 0));   // Peón verde

    // Segundo jugador 
    piezas.push_back(new Torre(0.5f, 4.5f, 255, 0, 0));  // Torre roja
    piezas.push_back(new Reina(1.5f, 4.5f, 255, 0, 0));  // Reina roja
    piezas.push_back(new Rey(2.5f, 4.5f, 255, 0, 0));    // Rey rojo
    piezas.push_back(new Torre(3.5f, 4.5f, 255, 0, 0));  // Torre roja

    piezas.push_back(new Peon(0.5f, 3.5f, 255, 0, 0));   // Peón rojo
    piezas.push_back(new Peon(1.5f, 3.5f, 255, 0, 0));   // Peón rojo
    piezas.push_back(new Peon(2.5f, 3.5f, 255, 0, 0));   // Peón rojo
    piezas.push_back(new Peon(3.5f, 3.5f, 255, 0, 0));   // Peón rojo
}


void Tablero::dibuja() {
    float casillaSizeX = 1.0f;
    float casillaSizeY = 1.0f;

    for (int i = 0; i < 5; ++i) {  // 5 filas
        for (int j = 0; j < 4; ++j) {  // 4 columnas
            if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);  // Blanco
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);  // Negro
            }

            glBegin(GL_QUADS);
            glVertex3f(j * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glVertex3f(j * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glEnd();
        }
    }

    // Dibujar las piezas
    for (Pieza* pieza : piezas) {
        pieza->dibuja();
    }
}

