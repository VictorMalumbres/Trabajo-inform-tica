#include "Reina.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"
#include <cmath>

void Reina::dibuja() {
    if (resaltado)glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para resaltado

    if (getBando() == 0)
    {
        // Dibujo del fondo con textura
        glPushMatrix();  // Guardamos la matriz actual

        // Posicionamos la imagen centrada en la celda
        glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/reina_blanco.png").id);
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
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/reina_negro.png").id);
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

bool Reina::mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) {
    int origenX = getX();
    int origenY = getY();
    int dx = nuevaColumna - origenX;
    int dy = nuevaFila - origenY;

    // Recto o diagonal
    if (!((dx == 0 && dy != 0) || (dy == 0 && dx != 0) || (std::abs(dx) == std::abs(dy) && dx != 0))) return false;

    int stepX = (dx == 0) ? 0 : dx / std::abs(dx);
    int stepY = (dy == 0) ? 0 : dy / std::abs(dy);
    int x = origenX + stepX;
    int y = origenY + stepY;
    while (x != nuevaColumna || y != nuevaFila) {
        if (tablero.obtenerPieza(x, y) != nullptr) return false; // Hay pieza en el camino
        x += stepX;
        y += stepY;
    }
    return true;
}

std::vector<std::pair<int, int>> Reina::movimientosPosibles(Tablero& tablero) {
    std::vector<std::pair<int, int>> movimientos;
    int x = getX();
    int y = getY();
    int cols = tablero.getNumColumnas();
    int filas = tablero.getNumFilas();

    // Torre (horizontal y vertical)
    for (int nx = x + 1; nx < cols; ++nx) {
        Pieza* p = tablero.obtenerPieza(nx, y);
        if (p == nullptr) {
            movimientos.push_back({ nx, y });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ nx, y });
            }
            break;
        }
    }
    for (int nx = x - 1; nx >= 0; --nx) {
        Pieza* p = tablero.obtenerPieza(nx, y);
        if (p == nullptr) {
            movimientos.push_back({ nx, y });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ nx, y });
            }
            break;
        }
    }
    for (int ny = y + 1; ny < filas; ++ny) {
        Pieza* p = tablero.obtenerPieza(x, ny);
        if (p == nullptr) {
            movimientos.push_back({ x, ny });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ x, ny });
            }
            break;
        }
    }
    for (int ny = y - 1; ny >= 0; --ny) {
        Pieza* p = tablero.obtenerPieza(x, ny);
        if (p == nullptr) {
            movimientos.push_back({ x, ny });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ x, ny });
            }
            break;
        }
    }

    // Alfil (diagonales)
    for (int nx = x + 1, ny = y + 1; nx < cols && ny < filas; ++nx, ++ny) {
        Pieza* p = tablero.obtenerPieza(nx, ny);
        if (p == nullptr) {
            movimientos.push_back({ nx, ny });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ nx, ny });
            }
            break;
        }
    }
    for (int nx = x - 1, ny = y + 1; nx >= 0 && ny < filas; --nx, ++ny) {
        Pieza* p = tablero.obtenerPieza(nx, ny);
        if (p == nullptr) {
            movimientos.push_back({ nx, ny });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ nx, ny });
            }
            break;
        }
    }
    for (int nx = x + 1, ny = y - 1; nx < cols && ny >= 0; ++nx, --ny) {
        Pieza* p = tablero.obtenerPieza(nx, ny);
        if (p == nullptr) {
            movimientos.push_back({ nx, ny });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ nx, ny });
            }
            break;
        }
    }
    for (int nx = x - 1, ny = y - 1; nx >= 0 && ny >= 0; --nx, --ny) {
        Pieza* p = tablero.obtenerPieza(nx, ny);
        if (p == nullptr) {
            movimientos.push_back({ nx, ny });
        }
        else {
            if (p->getBando() != getBando()) {
                movimientos.push_back({ nx, ny });
            }
            break;
        }
    }
    return movimientos;
}

