#include "Mundo.h"
#include <freeglut.h>

Mundo::Mundo() {
    // Constructor de Mundo, inicializa el tablero y las piezas
}

void Mundo::inicializa() {
    tablero.inicializa();
	tablero2.inicializa();
}
void Mundo::dibuja() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(0.0, 4.0, 0.0, 5.0, -1.0, 1.0);  

    tablero.dibuja();
	tablero2.dibuja();

    glutSwapBuffers();
}






