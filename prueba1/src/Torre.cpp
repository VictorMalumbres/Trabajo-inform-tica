#include "Torre.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"
#include <cmath>

void Torre::dibuja() {
    if (resaltado);

    glPushMatrix();

    glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

    GLuint texID;
    float size;
    if (getBando() == 0) {
        texID = ETSIDI::getTexture("imagenes/torre_blanco.png").id;
        size = 0.3f;
    }
    else {
        texID = ETSIDI::getTexture("imagenes/torre_negro.png").id;
        size = 0.45f;
    }

    if (texID == 0) {
        glPopMatrix();
        return;  // No se pudo cargar textura
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);  // Activa blending para transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texID);

    // Filtros lineales para suavizar la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Usa color blanco para no modificar la textura
    glColor3f(1.0f, 1.0f, 1.0f);

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

bool Torre::mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) {
    int origenX = getX();
    int origenY = getY();

    // Solo permite movimiento en l�nea recta
    if (origenX != nuevaColumna && origenY != nuevaFila) {
        return false;
    }

    int dx = (nuevaColumna - origenX) == 0 ? 0 : (nuevaColumna - origenX) / abs(nuevaColumna - origenX);
    int dy = (nuevaFila - origenY) == 0 ? 0 : (nuevaFila - origenY) / abs(nuevaFila - origenY);

    int x = origenX + dx;
    int y = origenY + dy;
    while (x != nuevaColumna || y != nuevaFila) {
        if (tablero.obtenerPieza(x, y) != nullptr) {
            return false; // Hay una pieza en el camino
        }
        x += dx;
        y += dy;
    }
    return true; // Movimiento v�lido
}

std::vector<std::pair<int, int>> Torre::movimientosPosibles(Tablero& tablero) {
    std::vector<std::pair<int, int>> movimientos;
    int x = getX();
    int y = getY();
    int cols = tablero.getNumColumnas();
    int filas = tablero.getNumFilas();

    // Cuatro direcciones ortogonales
    const int dx[] = { 1, -1, 0, 0 };
    const int dy[] = { 0, 0, 1, -1 };

    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir];
        int ny = y + dy[dir];
        while (nx >= 0 && nx < cols && ny >= 0 && ny < filas) {
            Pieza* destino = tablero.obtenerPieza(nx, ny);
            if (destino == nullptr) {
                movimientos.push_back({ nx, ny });
            }
            else {
                // Si es aliado y es el rey, no a�adir
                if (!(destino->getBando() == getBando() && destino->getValor() >= 1000)) {
                    movimientos.push_back({ nx, ny });
                }
                break; // No puede saltar piezas
            }
            nx += dx[dir];
            ny += dy[dir];
        }
    }
    return movimientos;
}