#include "Peon.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"

void Peon::dibuja() {
    glPushMatrix();
    glTranslated(getX() + 0.5f, getY() + 0.5f, 0);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    if (getBando() == 0) {
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/minions.png").id);
    }
    else {
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/peon_negro.png").id);
    }

    glColor3f(1.0f, 1.0f, 1.0f);  // Color blanco para no modificar la textura

    float size = 0.3f;
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


bool Peon::mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) {
    int origenX = getX();
    int origenY = getY();

    int dx = nuevaColumna - origenX;
    int dy = nuevaFila - origenY;

    int direccion;
    if (getBando() == 0) {
        direccion = 1;  // Peón blanco avanza hacia arriba (incremento en fila)
    }
    else {
        direccion = -1; // Peón negro avanza hacia abajo (decremento en fila)
    }

    // Movimiento hacia adelante sin captura
    if (dx == 0) {
        if (dy == direccion) { // Un paso
            if (tablero.obtenerPieza(nuevaColumna, nuevaFila) == nullptr) {
                return true;
            }
            return false;
        }
        if (dy == 2 * direccion) { // Dos pasos desde fila inicial
            int filaInicial = (getBando() == 0) ? 1 : 6;
            if (origenY == filaInicial) {
                // Comprobar que no haya pieza en la casilla destino
                if (tablero.obtenerPieza(nuevaColumna, nuevaFila) != nullptr) {
                    return false;
                }
                // Comprobar que no haya pieza del bando contrario en la casilla intermedia
                Pieza* piezaIntermedia = tablero.obtenerPieza(nuevaColumna, origenY + direccion);
                if (piezaIntermedia != nullptr && piezaIntermedia->getBando() != getBando()) {
                    return false;
                }
                // Comprobar que no haya pieza del bando contrario en la casilla destino
                Pieza* piezaDestino = tablero.obtenerPieza(nuevaColumna, nuevaFila);
                if (piezaDestino != nullptr && piezaDestino->getBando() != getBando()) {
                    return false;
                }
                return true;
            }
            return false;
        }
        return false;
    }

    // Movimiento diagonal para captura (normal o al paso)
    if (std::abs(dx) == 1 && dy == direccion) {
        Pieza* destino = tablero.obtenerPieza(nuevaColumna, nuevaFila);
        if (destino != nullptr && destino->getBando() != bando) {
            return true;  // Captura normal
        }
        // Captura al paso: casilla vacía pero permitido
        if (destino == nullptr && tablero.esCapturaAlPaso(nuevaColumna, nuevaFila, bando)) {
             return true;
        }
    }

    return false; // Movimiento inválido

}


std::vector<std::pair<int, int>> Peon::movimientosPosibles(Tablero& tablero) {
    std::vector<std::pair<int, int>> movimientos;
    int x = getX();
    int y = getY();
    int cols = tablero.getNumColumnas();
    int filas = tablero.getNumFilas();
    int dir = (getBando() == 0) ? 1 : -1; // 0: blanco sube, 1: negro baja

    // Movimiento hacia adelante (1 casilla)
    int ny = y + dir;
    if (ny >= 0 && ny < filas && !tablero.obtenerPieza(x, ny)) {
        movimientos.push_back({ x, ny });

        // Movimiento de 2 casillas desde la fila inicial
        int filaInicial = (getBando() == 0) ? 1 : filas - 2;
        int ny2 = y + 2 * dir;
        if (y == filaInicial && ny2 >= 0 && ny2 < filas &&
            !tablero.obtenerPieza(x, ny2) && !tablero.obtenerPieza(x, ny)) {
            movimientos.push_back({ x, ny2 });
        }
    }

    // Captura diagonal izquierda
    if (x - 1 >= 0 && ny >= 0 && ny < filas) {
        Pieza* pIzq = tablero.obtenerPieza(x - 1, ny);
        if (pIzq != nullptr) {
            movimientos.push_back({ x - 1, ny });
        }
        else if (tablero.esCapturaAlPaso(x - 1, ny, getBando())) {
            movimientos.push_back({ x - 1, ny }); // Para la captura al paso
        }
    }
    // Captura diagonal derecha
    if (x + 1 < cols && ny >= 0 && ny < filas) {
        Pieza* pDer = tablero.obtenerPieza(x + 1, ny);
        if (pDer != nullptr) {
            movimientos.push_back({ x + 1, ny });
        }
        else if (tablero.esCapturaAlPaso(x + 1, ny, getBando())) {
            movimientos.push_back({ x + 1, ny }); // Para la captura al paso
        }
    }
    return movimientos;
}
