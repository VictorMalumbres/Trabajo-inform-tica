#include "Tablero.h"
#include <freeglut.h>
#include "Mundo.h"

Mundo mundo;

void displayCallback() {
    mundo.dibuja();
}

void keyboardCallback(unsigned char key, int x, int y) {
    if (mundo.estaEnMenu()) return; // Ignorar teclado si estás en menú
    mundo.manejarTeclado(key, x, y); // Solo responder en el juego o instrucciones
}

void manejarClicRaton(int boton, int estado, int x, int y) {  //para detectar el raton
    if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
        mundo.procesarClick(x, y);
        glutPostRedisplay(); // Redibuja
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(800, 600);
    glutCreateWindow("MiniAjedrez");

    mundo.inicializarTableros();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro

    glutDisplayFunc(displayCallback);
    glutKeyboardFunc(keyboardCallback);

    glutMouseFunc(manejarClicRaton);
    
    glutMainLoop();

    return 0;
}