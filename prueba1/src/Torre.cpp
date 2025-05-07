#include "Torre.h"
#include <freeglut.h>

void Torre::dibuja() {
    glColor3ub(color[0], color[1], color[2]);  // Usamos el color asignado
    glPushMatrix();
    glTranslated(getX(), getY(), 0);  // Usamos las coordenadas de la pieza
    glutSolidSphere(0.4, 20, 20);  // Círculo con un radio de 0.4
    glPopMatrix();
}
