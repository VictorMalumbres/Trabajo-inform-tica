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

    // 1. Dibuja el fondo del tablero (casillas normales)
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

    // 2. Dibuja las casillas resaltadas en rojo (AQUÍ VA EL CÓDIGO NUEVO)
    for (const auto& pos : casillasResaltadas) {
        int col = pos.first;
        int fil = pos.second;
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo
        glBegin(GL_QUADS);
        glVertex3f(col * casillaSizeX, fil * casillaSizeY, 0.1f); // 0.1f para que quede encima
        glVertex3f((col + 1) * casillaSizeX, fil * casillaSizeY, 0.1f);
        glVertex3f((col + 1) * casillaSizeX, (fil + 1) * casillaSizeY, 0.1f);
        glVertex3f(col * casillaSizeX, (fil + 1) * casillaSizeY, 0.1f);
        glEnd();
    }

    // 3. Dibuja las piezas
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

    // --- BLOQUE NUEVO PARA RESALTAR CASILLAS ---
    for (const auto& pos : casillasResaltadas) {
        int col = pos.first;
        int fil = pos.second;
        glColor3f(1.0f, 0.0f, 0.0f); // Rojo
        glBegin(GL_QUADS);
        glVertex3f(col * casillaSizeX, fil * casillaSizeY, 0.1f); // 0.1f para que quede encima
        glVertex3f((col + 1) * casillaSizeX, fil * casillaSizeY, 0.1f);
        glVertex3f((col + 1) * casillaSizeX, (fil + 1) * casillaSizeY, 0.1f);
        glVertex3f(col * casillaSizeX, (fil + 1) * casillaSizeY, 0.1f);
        glEnd();
    }
    // -------------------------------------------

    for (Pieza* pieza : piezas) {
        pieza->dibuja();
    }
}
// --- FIN DEL BLOQUE NUEVO PARA RESALTAR CASILLAS ---

void Tablero::inicializaSilverman() {
    piezas.clear();
    numFilas = 5;
    numColumnas = 4;

    // Primer jugador (blanco)
    reyBlanco = new Rey(2, 0, 0); // Asignar el rey blanco
    piezas.push_back(reyBlanco);

    piezas.push_back(new Torre(0, 0, 0));
    piezas.push_back(new Reina(1, 0,0));
    //piezas.push_back(new Rey(2, 0, 0));
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
    //piezas.push_back(new Rey(2, 4, 1));
    piezas.push_back(new Torre(3, 4, 1));

    piezas.push_back(new Peon(0, 3, 1));
    piezas.push_back(new Peon(1, 3, 1));
    piezas.push_back(new Peon(2, 3, 1));
    piezas.push_back(new Peon(3, 3, 1));
}

void Tablero::inicializaDemi() {
    piezas.clear();

    numFilas = 8;
    numColumnas = 4;

    // Primer jugador (blanco)
    reyBlanco = new Rey(0, 0, 0); // Asignar el rey blanco
    piezas.push_back(reyBlanco);

    piezas.push_back(new Torre(3, 0, 0));
    //piezas.push_back(new Rey(0, 0,  0));
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
    //piezas.push_back(new Rey(0, 7, 1));
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
            if ((*it)->getBando() == pieza->getBando() && dynamic_cast<Rey*>(*it)) {
                return; // No se mueve ni elimina nada
            }
            else {
                if (dynamic_cast<Rey*>(*it)) {
                    if (pieza->getBando() == 0) {
                        // El rey negro ha sido capturado, ganan las blancas
                        if (mundo) {
                            mundo->jugadorGanador = 0; // Blancas ganan
                            mundo->setEstadoActual(VICTORIA);
                            glutPostRedisplay();
                        }
                    }
                    else {
                        // El rey blanco ha sido capturado, ganan las negras
                        if (mundo) {
                            mundo->jugadorGanador = 1; // Negras ganan
                            mundo->setEstadoActual(VICTORIA);
                            glutPostRedisplay();
                        }
                    }
                    return;  // Salir para no seguir con el movimiento ni cambiar turno
                }

                delete* it;
                piezas.erase(it);
                capturado = true;
                break;
            }
        }
    }

    // Mover la pieza
    pieza->setPosicion(nuevaFila, nuevaColumna);

    // ----------- CORONACIÓN DEL PEÓN -----------
    Peon* peon = dynamic_cast<Peon*>(pieza); // Declaración única
    if (peon) {
        int filaCoronacion = (peon->getBando() == 0) ? (numFilas - 1) : 0;
        if (nuevaFila == filaCoronacion) {
            int bando = peon->getBando();
            auto it = std::find(piezas.begin(), piezas.end(), peon);
            if (it != piezas.end()) {
                delete* it;
                piezas.erase(it);
            }

            int opcion = 0;
            if (numFilas == 5) { // Silverman
                std::cout << "Coronación: Elige 1 para Torre, 2 para Dama: ";
                std::cin >> opcion;
                if (opcion == 1)
                    piezas.push_back(new Torre(nuevaColumna, nuevaFila, bando));
                else
                    piezas.push_back(new Reina(nuevaColumna, nuevaFila, bando));
            }
            else { // Demi
                std::cout << "Coronación: Elige 1 para Alfil, 2 para Caballo, 3 para Torre: ";
                std::cin >> opcion;
                if (opcion == 1)
                    piezas.push_back(new Alfil(nuevaColumna, nuevaFila, bando));
                else if (opcion == 2)
                    piezas.push_back(new Caballo(nuevaColumna, nuevaFila, bando));
                else
                    piezas.push_back(new Torre(nuevaColumna, nuevaFila, bando));
            }
            return; // Termina la función tras coronar
        }
    }
    // ----------- FIN CORONACIÓN DEL PEÓN -----------

    turno = 1 - turno; // Cambiar turno
}



void Tablero::anadirPieza(Pieza* pieza) {
    piezas.push_back(pieza);
}

void Tablero::reiniciarTablero() {
    for (Pieza* p : piezas) {
        delete p;
    }
    piezas.clear();
    seleccionX = -1;
    seleccionY = -1;
    turno = 0;
    reyBlanco = nullptr;
    reyNegro = nullptr;
}

void Tablero::setSeleccion(int x, int y) {
    seleccionX = x;
    seleccionY = y;
    Pieza* pieza = obtenerPieza(x, y);
    if (pieza && pieza->getBando() == turno) {
        casillasResaltadas = pieza->movimientosPosibles(*this);
    }
    else {
        casillasResaltadas.clear();
    }
}

void Tablero::limpiarSeleccion() {
    seleccionX = -1;
    seleccionY = -1;
    casillasResaltadas.clear();
}

int Tablero::getNumFilas() const {
    return numFilas;
}

int Tablero::getNumColumnas() const {
    return numColumnas;
}
