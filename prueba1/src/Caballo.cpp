#include "Caballo.h"
#include <freeglut.h>

void Caballo::dibuja() {
    if (getBando() == 0)
        glColor3f(0.0f, 1.0f, 0.0f);  // blanco
    else
        glColor3f(1.0f, 0.0f, 0.0f);  // negro

    glPushMatrix();
    glTranslated(getX(), getY(), 0);
    glutSolidCube(0.6);  // Dibujar un cubo para la torre
    glPopMatrix();
}
