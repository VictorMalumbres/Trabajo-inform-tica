#include "Tablero.h"
#include <freeglut.h>
#include <iostream>
#include <string>
#include "Mundo.h"
//#pragma warning(disable : 4996) //deshabilita el error por unsafe 
//Mundo mundo;

Tablero::Tablero() {
    // Constructor de Tablero, inicializa el vector de piezas
    turno = 0;
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
    reyBlanco = new Rey(2, 0, 0); // Asignar el rey blanco
    piezas.push_back(reyBlanco);

    piezas.push_back(new Torre(0, 0, 0));
    piezas.push_back(new Reina(1, 0,0));
    piezas.push_back(new Rey(2, 0, 0));
    piezas.push_back(new Torre(3, 0, 0));

    piezas.push_back(new Peon(0, 1, 0));
    piezas.push_back(new Peon(1, 1, 0));
    piezas.push_back(new Peon(2, 1, 0));
    piezas.push_back(new Peon(3, 1, 0));

    // Segundo jugador (negro)
    reyNegro = new Rey(2, 4, 1); // Asignar el rey negro
    piezas.push_back(reyNegro);

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
    reyBlanco = new Rey(0, 0, 0); // Asignar el rey blanco
    piezas.push_back(reyBlanco);

    piezas.push_back(new Torre(3, 0, 0));
    piezas.push_back(new Rey(0, 0,  0));
    piezas.push_back(new Caballo(2, 0, 0));
    piezas.push_back(new Alfil(1, 0, 0));      // Alfil blanco

    piezas.push_back(new Peon(0, 1, 0));    
    piezas.push_back(new Peon(1, 1, 0));    
    piezas.push_back(new Peon(2, 1, 0));
    piezas.push_back(new Peon(3, 1, 0));

    // Segundo jugador (negro)
    reyNegro = new Rey(0, 7, 1); // Asignar el rey negro
    piezas.push_back(reyNegro);

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

    // Comprobar que es el turno de la pieza
    if (pieza->getBando() != turno) {
        return; // No es turno de esta pieza
    }
    // Validar movimiento usando la pieza
    if (!pieza->mueve(*this, nuevaColumna, nuevaFila)) {
        return; // Movimiento inválido
    }

    bool capturado = false;

    // Buscar si hay una pieza en la casilla destino
    for (auto it = piezas.begin(); it != piezas.end(); ++it) {
        if ((*it)->getX() == nuevaColumna && (*it)->getY() == nuevaFila) {
            // Si la pieza en destino es del mismo bando, no mover
            if ((*it)->getBando() == pieza->getBando()) {
                return; // No se mueve ni elimina nada
            }
            else {
                               
				// Comprobar si es un rey
                if (dynamic_cast<Rey*>(*it)) { // Si es un rey
                    if (pieza->getBando() == 0) {
                        std::cout << "El rey negro ha sido capturado. ¡El jugador blanco gana!" << std::endl;
                    }
                    else {
                        std::cout << "El rey blanco ha sido capturado. ¡El jugador negro gana!" << std::endl;
                    }

                  

                    // Puedes añadir un mensaje o cualquier otra acción al cambiar al menú
                    std::cout << "Volviendo al menú..." << std::endl;
                
                }

                // Es del bando contrario, eliminarla (capturar)
                delete* it;
                piezas.erase(it);
                capturado = true; // Marcamos que se ha capturado una pieza
                break;
            }
        }
    }

    // Mover la pieza
    pieza->setPosicion(nuevaFila, nuevaColumna);

	if (!capturado) {
        turno = 1 - turno; // Cambiar turno
	}
	
}

void Tablero::anadirPieza(Pieza* pieza) {
    piezas.push_back(pieza);
}

