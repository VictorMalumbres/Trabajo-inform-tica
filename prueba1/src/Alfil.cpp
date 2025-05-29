#include "Alfil.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"
#include <cmath>
void Alfil::dibuja() {
    if (resaltado);

    if (getBando() == 0)
    {
        // Dibujo del fondo con textura
        glPushMatrix();  // Guardamos la matriz actual

        // Posicionamos la imagen centrada en la celda
        glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);  // <-- Activa blending para transparencia
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // <-- Función de mezcla correcta

        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/alfil_blanco.png").id);

        // Filtros lineales para mejor calidad
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float size = 0.3f;  // Mitad del tamaño total (0.6 / 2)

        glBegin(GL_QUADS);
        glColor3f(colorR, colorG, colorB);  // blanco
        glTexCoord2d(0, 1); glVertex3f(-size, -size, 0);
        glTexCoord2d(1, 1); glVertex3f(size, -size, 0);
        glTexCoord2d(1, 0); glVertex3f(size, size, 0);
        glTexCoord2d(0, 0); glVertex3f(-size, size, 0);
        glEnd();

        glDisable(GL_BLEND);  // <-- Desactiva blending
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
        glEnable(GL_BLEND);  // <-- Activa blending para transparencia
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  // <-- Función de mezcla correcta

        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/alfil_negro.png").id);

        // Filtros lineales para mejor calidad
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        float size = 0.4f;  // Mitad del tamaño total (0.6 / 2)

        glBegin(GL_QUADS);
        glColor3f(colorR, colorG, colorB);  // negro
        glTexCoord2d(0, 1); glVertex3f(-size, -size, 0);
        glTexCoord2d(1, 1); glVertex3f(size, -size, 0);
        glTexCoord2d(1, 0); glVertex3f(size, size, 0);
        glTexCoord2d(0, 0); glVertex3f(-size, size, 0);
        glEnd();

        glDisable(GL_BLEND);  // <-- Desactiva blending
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

std::vector<std::pair<int, int>> Alfil::movimientosPosibles(Tablero& tablero) {
    std::vector<std::pair<int, int>> movimientos;
    int x = getX();
    int y = getY();
    int cols = tablero.getNumColumnas();
    int filas = tablero.getNumFilas();

    // Cuatro diagonales
    const int dx[] = { 1, 1, -1, -1 };
    const int dy[] = { 1, -1, 1, -1 };

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        while (nx >= 0 && nx < cols && ny >= 0 && ny < filas) {
            Pieza* destino = tablero.obtenerPieza(nx, ny);
            if (destino == nullptr) {
                movimientos.push_back({ nx, ny });
            }
            else {
                if (!(destino->getBando() == getBando() && destino->getValor() >= 1000)) {
                    movimientos.push_back({ nx, ny });
                }
                break;
            }
            nx += dx[dir];
            ny += dy[dir];
        }
    }
    return movimientos;
}


