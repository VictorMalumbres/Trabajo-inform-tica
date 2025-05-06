#include "tablero.h"
#include <iostream>
#include <freeglut.h>

const int windowWidth = 600;
const int windowHeight = 600;
const int numSquares = 8;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    float squareSize = 2.0f / numSquares;  // tamaño de cada cuadrado (de -1.0 a 1.0)

    for (int row = 0; row < numSquares; ++row) {
        for (int col = 0; col < numSquares; ++col) {
            // Alternar color entre blanco y negro
            if ((row + col) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f);  // blanco
            else
                glColor3f(0.0f, 0.0f, 0.0f);  // negro

            float x = -1.0f + col * squareSize;
            float y = -1.0f + row * squareSize;

            glBegin(GL_QUADS);
            glVertex2f(x, y);
            glVertex2f(x + squareSize, y);
            glVertex2f(x + squareSize, y + squareSize);
            glVertex2f(x, y + squareSize);
            glEnd();
        }
    }

    glFlush();
}

void initialize() {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Color de fondo gris
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Tablero de Ajedrez - FreeGLUT");

    initialize();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
