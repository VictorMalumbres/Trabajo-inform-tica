#include "Mundo.h"
#include <freeglut.h>

Mundo::Mundo() : modoJuego(1) {
    // Constructor
}

void Mundo::inicializa() {
    tablero.inicializa();
    tablero2.inicializa();
}

void Mundo::dibuja() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if (modoJuego == 1) {
        glOrtho(0.0, 4.0, 0.0, 5.0, -1.0, 1.0);
        tablero.dibuja();
    }
    else if (modoJuego == 2) {
        glOrtho(0.0, 4.0, 0.0, 8.0, -1.0, 1.0);
        tablero2.dibuja2();
    }

    glutSwapBuffers();
}








