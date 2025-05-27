#include "Peon.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"

void Peon::dibuja() {
    if (resaltado)glColor3f(1.0f, 1.0f, 0.0f); // Amarillo para resaltado
    
    if (getBando() == 0)
    {
        // Dibujo del fondo con textura
        glPushMatrix();  // Guardamos la matriz actual

        // Posicionamos la imagen centrada en la celda
        glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/peon_blanco.png").id);
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
        glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("imagenes/peon_negro.png").id);
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
        if (tablero.obtenerPieza(x - 1, ny))
            movimientos.push_back({ x - 1, ny });
    }
    // Captura diagonal derecha
    if (x + 1 < cols && ny >= 0 && ny < filas) {
        if (tablero.obtenerPieza(x + 1, ny))
            movimientos.push_back({ x + 1, ny });
    }
    return movimientos;
}
