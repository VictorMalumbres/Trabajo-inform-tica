#include "Reina.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"
#include <cmath>

void Reina::dibuja() {
    if (resaltado);

    glPushMatrix();
    glTranslated(getX() + 0.5f, getY() + 0.5f, 0);

    GLuint texID = (getBando() == 0) ? ETSIDI::getTexture("imagenes/ReinaBlanca.png").id
        : ETSIDI::getTexture("imagenes/ReinaNegro.png").id;

    if (texID == 0) {
        glPopMatrix();
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texID);

    // Filtros sin suavizado para nitidez
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glColor3f(1, 1, 1);

    float size = 0.4f;  // Ajusta según resolución imagen y espacio
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-size, -size, 0);
    glTexCoord2d(1, 1); glVertex3f(size, -size, 0);
    glTexCoord2d(1, 0); glVertex3f(size, size, 0);
    glTexCoord2d(0, 0); glVertex3f(-size, size, 0);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
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
        movimientos.push_back({ nx, y });
        if (tablero.obtenerPieza(nx, y)) break;
    }
    for (int nx = x - 1; nx >= 0; --nx) {
        movimientos.push_back({ nx, y });
        if (tablero.obtenerPieza(nx, y)) break;
    }
    for (int ny = y + 1; ny < filas; ++ny) {
        movimientos.push_back({ x, ny });
        if (tablero.obtenerPieza(x, ny)) break;
    }
    for (int ny = y - 1; ny >= 0; --ny) {
        movimientos.push_back({ x, ny });
        if (tablero.obtenerPieza(x, ny)) break;
    }

    // Alfil (diagonales)
    for (int nx = x + 1, ny = y + 1; nx < cols && ny < filas; ++nx, ++ny) {
        movimientos.push_back({ nx, ny });
        if (tablero.obtenerPieza(nx, ny)) break;
    }
    for (int nx = x - 1, ny = y + 1; nx >= 0 && ny < filas; --nx, ++ny) {
        movimientos.push_back({ nx, ny });
        if (tablero.obtenerPieza(nx, ny)) break;
    }
    for (int nx = x + 1, ny = y - 1; nx < cols && ny >= 0; ++nx, --ny) {
        movimientos.push_back({ nx, ny });
        if (tablero.obtenerPieza(nx, ny)) break;
    }
    for (int nx = x - 1, ny = y - 1; nx >= 0 && ny >= 0; --nx, --ny) {
        movimientos.push_back({ nx, ny });
        if (tablero.obtenerPieza(nx, ny)) break;
    }
    return movimientos;
}

