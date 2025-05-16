#include "Caballo.h"
#include <freeglut.h>

void Caballo::dibuja() {
    glColor3ub(color[0], color[1], color[2]);
    glPushMatrix();
    glTranslated(getX(), getY(), 0);
    glutSolidSphere(0.3, 20, 20);  // Tamaño diferente para distinguir
    glPopMatrix();
}
