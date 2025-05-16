#include "Alfil.h"
#include <freeglut.h>

void Alfil::dibuja() {
    glColor3ub(color[0], color[1], color[2]);
    glPushMatrix();
    glTranslated(getX(), getY(), 0);
    glutSolidSphere(0.35, 20, 20);  // Tamaño intermedio
    glPopMatrix();
}
