#include "Tablero.h"
#include <freeglut.h>

Tablero tablero;

void displayCallback() {
    tablero.mostrarMenuEnVentana();
}

void keyboardCallback(unsigned char key, int x, int y) {
    tablero.manejarEntradaMenu(key, x, y);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("MiniAjedrez");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro

    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);

    glutMainLoop();
    return 0;
}
