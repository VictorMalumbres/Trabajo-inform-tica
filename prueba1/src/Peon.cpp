#include "Peon.h"
#include <freeglut.h>

void Peon::dibuja() {
    if (resaltado)
        glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para resaltado
    else if (getBando() == 0)
    {
        colorR = 0.0f;
        colorG = 1.0f;
		colorB = 0.0f;  // blanco
        glColor3f(colorR, colorG, colorB);  // blanco
    }
    else
    {
		colorR = 1.0f;
		colorG = 0.0f;
        colorB = 0.0f; //negro
        glColor3f(colorR, colorG, colorB);  // negro
    }
        
    glPushMatrix();
    glTranslated(getX() + 0.5f, getY() + 0.5f, 0);
    glutSolidCube(0.6);  // Dibujar un cubo para la torre
    glPopMatrix();


}

void Peon::mueve() {
    
}