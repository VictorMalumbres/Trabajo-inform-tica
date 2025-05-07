#include "Peon.h"
#include <freeglut.h>

void Peon::dibuja() {
    glColor3ub(color[0], color[1], color[2]);  
    glPushMatrix();
    glTranslated(getX(), getY(), 0);  
    glutSolidSphere(0.3, 20, 20); 
    glPopMatrix();
}
