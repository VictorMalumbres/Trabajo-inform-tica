#include "Reina.h"
#include <freeglut.h>

void Reina::dibuja() {
    glColor3ub(color[0], color[1], color[2]); 
    glPushMatrix();
    glTranslated(getX(), getY(), 0);  
    glutSolidSphere(0.4, 20, 20);  
    glPopMatrix();
}
