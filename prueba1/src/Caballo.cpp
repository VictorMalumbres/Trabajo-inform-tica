#include "Caballo.h"
#include <freeglut.h>
#include "ETSIDI.h"
#include "Tablero.h"

void Caballo::dibuja() {
    if (resaltado);

    glPushMatrix();
    glTranslated(getX() + 0.5f, getY() + 0.5f, 0);  // Centrado en la celda

    GLuint texID;
    if (getBando() == 0) {
        texID = ETSIDI::getTexture("imagenes/caballo_blanco.png").id;
    }
    else {
        texID = ETSIDI::getTexture("imagenes/caballo_negro.png").id;
    }

    if (texID == 0) {
        glPopMatrix();
        return;  // No se pudo cargar textura
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);  // Activa el blending para la transparencia
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, texID);

    // Usa filtros lineales para suavizar la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Si tu entorno soporta mipmaps, descomenta esta línea:
    // glGenerateMipmap(GL_TEXTURE_2D);

    glColor3f(1.0f, 1.0f, 1.0f);  // Usamos blanco para no interferir con la textura

    float size = 0.3f;  // Ajusta el tamaño de la textura para que no se vea demasiado estirada o pequeña
    glBegin(GL_QUADS);
    glTexCoord2d(0, 1); glVertex3f(-size, -size, 0);
    glTexCoord2d(1, 1); glVertex3f(size, -size, 0);
    glTexCoord2d(1, 0); glVertex3f(size, size, 0);
    glTexCoord2d(0, 0); glVertex3f(-size, size, 0);
    glEnd();

    glDisable(GL_BLEND);  // Desactiva el blending después de dibujar
    glDisable(GL_TEXTURE_2D);  // Desactiva la textura después de dibujar

    glPopMatrix();
}


bool Caballo::mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) {
 
        int origenX = getX();
        int origenY = getY();

        int dx = std::abs(nuevaColumna - origenX);
        int dy = std::abs(nuevaFila - origenY);

        // Movimiento típico de caballo: 2 en una dirección y 1 en la otra
        if (!((dx == 2 && dy == 1) || (dx == 1 && dy == 2))) {
            return false;
        }

        // El caballo puede saltar piezas, así que no verificamos el camino
        // Solo verificar si la casilla destino tiene una pieza del mismo bando


        return true; // Movimiento válido
   
}

std::vector<std::pair<int, int>> Caballo::movimientosPosibles(Tablero& tablero) {
    std::vector<std::pair<int, int>> movimientos;
    int x = getX();
    int y = getY();
    int dx[] = { 1, 2, 2, 1, -1, -2, -2, -1 };
    int dy[] = { 2, 1, -1, -2, -2, -1, 1, 2 };

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < tablero.getNumColumnas() && ny >= 0 && ny < tablero.getNumFilas()) {
            movimientos.push_back({ nx, ny });
        }
    }
    return movimientos;
}
