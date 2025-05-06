#include "Tablero.h"
#include "freeglut.h"

// Crear un objeto Tablero de 4x5
Tablero tablero(5, 4);

// Funci�n que se llama para dibujar en cada fotograma
void OnDraw(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Limpiar la pantalla

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();  // Reiniciar la matriz de vista

    // Configurar la vista para 2D (cambiar a proyecci�n ortogr�fica)
    glOrtho(0.0, 0.0, 0.0, 0.0, 0.0, 0.0);  // Establecer la proyecci�n ortogr�fica centrada

    // Dibujar el tablero
    tablero.dibuja();

    glutSwapBuffers();  // Intercambiar los buffers de la ventana para mostrar lo dibujado
}

// Funci�n que se ejecuta cada vez que se pulsa una tecla
void OnKeyboardDown(unsigned char key, int x, int y) {
    // Aqu� puedes agregar c�digo para manejar teclas, pero por ahora est� vac�o
    glutPostRedisplay();  // Redibujar la pantalla
}

int main(int argc, char* argv[]) {
    // Inicializar GLUT y la ventana
    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);  // Tama�o de la ventana
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // Configurar la visualizaci�n
    glutCreateWindow("Tablero 5x4");

    // Configuraci�n b�sica de OpenGL para dibujar en 2D
    glMatrixMode(GL_PROJECTION);  // Usar proyecci�n
    glLoadIdentity();  // Reiniciar la matriz de proyecci�n
    glOrtho(-1.0, 5.0, 0.0, 5.0, -1.0, 1.0);  // Establecer la proyecci�n ortogr�fica centrada

    // Registrar los callbacks
    glutDisplayFunc(OnDraw);
    glutKeyboardFunc(OnKeyboardDown);

    // Inicializar el tablero
    tablero.inicializa();

    // Iniciar el bucle principal de GLUT
    glutMainLoop();

    return 0;
}
