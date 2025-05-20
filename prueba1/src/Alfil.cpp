#include "Alfil.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"
#include <cmath>

void Alfil::dibuja() {
    if (resaltado)glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para resaltado

    if (getBando() == 0)
    {
        // Dibujo del fondo con textura
        glPushMatrix();  // Guardamos la matriz actual

        // Posicionamos la imagen centrada en la celda
        glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/alfil_blanco.png").id);
        // Dibujamos un cuadrado centrado con tamaño 0.6x0.6 (como el cubo anterior)
        float size = 0.3f;  // Mitad del tamaño total (0.6 / 2)
        glBegin(GL_QUADS);
        colorR = 1.0f;
        colorG = 1.0f;
        colorB = 1.0f;  // blanco
        glColor3f(colorR, colorG, colorB);  // blanco
        glTexCoord2d(0, 1); glVertex3f(-size, -size, 0);  // esquina inferior izquierda
        glTexCoord2d(1, 1); glVertex3f(size, -size, 0);  // esquina inferior derecha
        glTexCoord2d(1, 0); glVertex3f(size, size, 0);  // esquina superior derecha
        glTexCoord2d(0, 0); glVertex3f(-size, size, 0);  // esquina superior izquierda
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();  // Restauramos la matriz original
    }
    else
    {
        // Dibujo del fondo con textura
        glPushMatrix();  // Guardamos la matriz actual

        // Posicionamos la imagen centrada en la celda
        glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/alfil_negro.png").id);
        // Dibujamos un cuadrado centrado con tamaño 0.6x0.6 (como el cubo anterior)
        float size = 0.3f;  // Mitad del tamaño total (0.6 / 2)
        glBegin(GL_QUADS);
        colorR = 1.0f;
        colorG = 1.0f;
        colorB = 1.0f; //negro
        glColor3f(colorR, colorG, colorB);  // negro
        glTexCoord2d(0, 1); glVertex3f(-size, -size, 0);  // esquina inferior izquierda
        glTexCoord2d(1, 1); glVertex3f(size, -size, 0);  // esquina inferior derecha
        glTexCoord2d(1, 0); glVertex3f(size, size, 0);  // esquina superior derecha
        glTexCoord2d(0, 0); glVertex3f(-size, size, 0);  // esquina superior izquierda
        glEnd();
        glDisable(GL_TEXTURE_2D);
        glPopMatrix();  // Restauramos la matriz original
    }
}

bool Alfil::mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) {
    int origenX = getX();
    int origenY = getY();
    int dx = nuevaColumna - origenX;
    int dy = nuevaFila - origenY;

    // Movimiento diagonal: |dx| == |dy|
    if (std::abs(dx) != std::abs(dy) || dx == 0) return false;

    int stepX = dx / std::abs(dx);
    int stepY = dy / std::abs(dy);
    int x = origenX + stepX;
    int y = origenY + stepY;
    while (x != nuevaColumna && y != nuevaFila) {
        if (tablero.obtenerPieza(x, y) != nullptr) return false; // Hay pieza en el camino
        x += stepX;
        y += stepY;
    }
    return true;
}
