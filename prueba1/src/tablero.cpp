#include "Tablero.h"
#include <freeglut.h>
#include <iostream>
#include <string>
//#include "Mundo.h"
//#pragma warning(disable : 4996) //deshabilita el error por unsafe 
//Mundo mundo;

Tablero::Tablero() {
    // Constructor de Tablero, inicializa el vector de piezas
}

void Tablero::iniciarPartida(int modoJuego) {
    if (modoJuego == 1) {
        inicializaSilverman();
    }
    else if (modoJuego == 2) {
        inicializaDemi();
    }
    //glutDisplayFunc([]() { mundo.dibuja(); });
    glutPostRedisplay();
}

void Tablero::dibuja() {
    float casillaSizeX = 1.0f;
    float casillaSizeY = 1.0f;

    for (int i = 0; i < 5; ++i) {  // 5 filas
        for (int j = 0; j < 4; ++j) {  // 4 columnas

            // Si la casilla es la seleccionada, la resaltamos
            if (i == seleccionY && j == seleccionX) {
                glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
            }
            else if ((i + j) % 2 == 0) {
                glColor3f(1.0f, 1.0f, 1.0f);  // Blanco
            }
            else {
                glColor3f(0.0f, 0.0f, 0.0f);  // Negro
            }

            glBegin(GL_QUADS);
            glVertex3f(j * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glVertex3f(j * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glEnd();
        }
    }

    // Dibujar las piezas
    for (Pieza* pieza : piezas) {
        pieza->dibuja();
    }
}

void Tablero::dibuja2() {
    float casillaSizeX = 1.0f;
    float casillaSizeY = 1.0f;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            // Si la casilla es la seleccionada, la resaltamos
            if (i == seleccionY && j == seleccionX) {
                glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
            }
            else if ((i + j) % 2 == 0)
                glColor3f(1.0f, 1.0f, 1.0f);
            else
                glColor3f(0.0f, 0.0f, 0.0f);

            glBegin(GL_QUADS);
            glVertex3f(j * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, i * casillaSizeY, 0.0f);
            glVertex3f((j + 1) * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glVertex3f(j * casillaSizeX, (i + 1) * casillaSizeY, 0.0f);
            glEnd();
        }
    }

    for (Pieza* pieza : piezas) {
        pieza->dibuja();
    }

}

void Tablero::inicializaSilverman() {
    piezas.clear();

    // Primer jugador (blanco)
    piezas.push_back(new Torre(0, 0, 0));
    piezas.push_back(new Reina(1, 0,0));
    piezas.push_back(new Rey(2, 0, 0));
    piezas.push_back(new Torre(3, 0, 0));

    piezas.push_back(new Peon(0, 1, 0));
    piezas.push_back(new Peon(1, 1, 0));
    piezas.push_back(new Peon(2, 1, 0));
    piezas.push_back(new Peon(3, 1, 0));

    // Segundo jugador (negro)
    piezas.push_back(new Torre(0, 4, 1));
    piezas.push_back(new Reina(1, 4, 1));
    piezas.push_back(new Rey(2, 4, 1));
    piezas.push_back(new Torre(3, 4, 1));

    piezas.push_back(new Peon(0, 3, 1));
    piezas.push_back(new Peon(1, 3, 1));
    piezas.push_back(new Peon(2, 3, 1));
    piezas.push_back(new Peon(3, 3, 1));
}

void Tablero::inicializaDemi() {
    piezas.clear();

    // Primer jugador (blanco)
    piezas.push_back(new Torre(3, 0, 0));
    piezas.push_back(new Rey(0, 0,  0));
    piezas.push_back(new Caballo(2, 0, 0));

    piezas.push_back(new Alfil(1, 0, 0));      // Alfil blanco
    piezas.push_back(new Peon(0, 1, 0));    
    piezas.push_back(new Peon(1, 1, 0));    
    piezas.push_back(new Peon(2, 1, 0));
    piezas.push_back(new Peon(3, 1, 0));

    // Segundo jugador (negro)
    piezas.push_back(new Torre(3, 7, 1));
    piezas.push_back(new Rey(0, 7, 1));
    piezas.push_back(new Caballo(2, 7, 1));

    piezas.push_back(new Alfil(1, 7, 1));      // Alfil negro
    piezas.push_back(new Peon(0, 6, 1));    
    piezas.push_back(new Peon(1, 6, 1));    
    piezas.push_back(new Peon(2, 6, 1));
    piezas.push_back(new Peon(3, 6, 1));
}

Pieza* Tablero::obtenerPieza(int columna, int fila) const {
    for (Pieza* p : piezas) {
        if (p->getX() == columna && p->getY() == fila) {
            return p;
        }
    }
    //std::cout << "No pieza" << std::endl;
    return nullptr; // No hay pieza ah�
}

void Tablero::colocarPieza(Pieza* pieza, int nuevaColumna, int nuevaFila) {
    // Validar movimiento usando la pieza
    if (!pieza->mueve(*this, nuevaColumna, nuevaFila)) {
        return;
    }

    // Comprobar si hay otra pieza en destino y eliminarla
    for (auto it = piezas.begin(); it != piezas.end(); ++it) {
        if ((*it)->getX() == nuevaColumna && (*it)->getY() == nuevaFila) {
            delete* it;
            piezas.erase(it);
            break;
        }
    }
    // Mover la pieza
    pieza->setPosicion(nuevaFila, nuevaColumna);
}

void Tablero::anadirPieza(Pieza* pieza) {
    piezas.push_back(pieza);
}

