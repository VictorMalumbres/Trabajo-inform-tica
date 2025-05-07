#include "Mundo.h"
#include "freeglut.h"

Mundo mundo;  

void OnDraw(void) {
    mundo.dibuja();  
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutCreateWindow("Mini Ajedrez");

    mundo.inicializa();
    glutDisplayFunc(OnDraw);

    // Iniciar el bucle de GLUT
    glutMainLoop();

    return 0;
}

