#include "Mundo.h"
#include <freeglut.h>
#include "Mundo.h"

Mundo mundo;

void displayCallback() {
    mundo.dibuja();
}

void keyboardCallback(unsigned char key, int x, int y) {
    mundo.manejarEntradaMenu(key, x, y);
}

void manejarClicRaton(int boton, int estado, int x, int y) {
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        mundo.procesarClick(x, y);
        glutPostRedisplay(); // Redibuja
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("MiniAjedrez");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro

    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);

    glutMouseFunc(manejarClicRaton);

    glutMainLoop();
    return 0;
}
