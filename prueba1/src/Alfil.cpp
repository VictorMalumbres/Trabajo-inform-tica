#include "Alfil.h"
#include <freeglut.h>


void Alfil::dibuja() {
    if (resaltado)
        glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para resaltado
    else if (getBando() == 0)
        glColor3f(0.0f, 1.0f, 0.0f);  // blanco
    else
        glColor3f(1.0f, 0.0f, 0.0f);  // negro

    glPushMatrix();
    glTranslated(getX() + 0.5f, getY() + 0.5f, 0);
    glutSolidCube(0.6);  // Dibujar un cubo para la torre
    glPopMatrix();
}
