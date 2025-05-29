#include "Rey.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"

void Rey::dibuja() {
    if (resaltado);

    if (estaEnJaque()) {
        glColor3f(1.0f, 0.4f, 0.7f); // Rosa si está en jaque
    }

    glPushMatrix();
    float ajusteX = 0.1f; // Ajuste para mover la imagen

    glTranslated(getX() + 0.5f + ajusteX, getY() + 0.5f, 0);

    GLuint texID;
    if (getBando() == 0) {
        texID = ETSIDI::getTexture("imagenes/rey_blanco.png").id;
    }
    else {
        texID = ETSIDI::getTexture("imagenes/rey_negro.png").id;
    }

    if (texID == 0) {
        glPopMatrix();
        return;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texID);

    // Si tu entorno soporta mipmaps, descomenta la siguiente línea:
    // glGenerateMipmap(GL_TEXTURE_2D);

    // Configura los filtros para mejor calidad
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // o GL_LINEAR_MIPMAP_LINEAR si usas mipmaps
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glColor3f(1.0f, 1.0f, 1.0f); // Color blanco

    float size = 0.5f;
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






bool Rey::mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) {
    int origenX = getX();
    int origenY = getY();

    int dx = nuevaColumna - origenX;
    int dy = nuevaFila - origenY;

    // El rey se mueve una casilla en cualquier dirección
    if (std::abs(dx) > 1 || std::abs(dy) > 1) return false;

    // Ya no se comprueba el bando de la pieza destino
    // Puede capturar cualquier pieza (aliada o enemiga)
    return true;
}


std::vector<std::pair<int, int>> Rey::movimientosPosibles(Tablero& tablero) {
    std::vector<std::pair<int, int>> movimientos;
    int x = getX();
    int y = getY();
    int cols = tablero.getNumColumnas();
    int filas = tablero.getNumFilas();

    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < cols && ny >= 0 && ny < filas) {
                movimientos.push_back({ nx, ny });
            }
        }
    }
    return movimientos;
}
