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

			//vamos a pintar de rosa si hay un rey en jaque

            Pieza* p = obtenerPieza(j, i);
            bool pintarRosa = false;

            if (p != nullptr) {
                Rey* rey = dynamic_cast<Rey*>(p);
                if (rey && rey->estaEnJaque()) {
                    pintarRosa = true;
                }
            }

            // Si la casilla es la del rey en jaque, pintar rosa
            if (pintarRosa) {
                glColor3f(1.0f, 0.4f, 0.7f); // Rosa claro
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

            //vamos a pintar de rosa si hay un rey en jaque

            Pieza* p = obtenerPieza(j, i);
            bool pintarRosa = false;

            if (p != nullptr) {
                Rey* rey = dynamic_cast<Rey*>(p);
                if (rey && rey->estaEnJaque()) {
                    pintarRosa = true;
                }
            }

            // Si la casilla es la del rey en jaque, pintar rosa
            if (pintarRosa) {
                glColor3f(1.0f, 0.4f, 0.7f); // Rosa claro
            }


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

bool Tablero::esCapturaAlPaso(int col, int fila, int bando) const {
    return (turnoPeonDoble != -1 &&
        turnoPeonDoble != bando &&
        col == ultimoPeonDobleX &&
        fila == ultimoPeonDobleY);
}


void Tablero::actualizarEstadoJaque() {
    for (Pieza* p : piezas) {
        Rey* rey = dynamic_cast<Rey*>(p);
        if (rey) {
            bool enJaque = estaEnJaque(rey->getBando());
            rey->setEnJaque(enJaque);
        }
    }
}

bool Tablero::estaEnJaque(int bando) const {
    Pieza* rey = nullptr;
    for (Pieza* p : piezas) {
        Rey* r = dynamic_cast<Rey*>(p);
        if (r && p->getBando() == bando) {
            rey = p;
            break;
        }
    }
    if (!rey) return false;

    int reyX = rey->getX();
    int reyY = rey->getY();

    for (Pieza* p : piezas) {
        if (p->getBando() != bando) {
            auto movs = p->movimientosPosibles(const_cast<Tablero&>(*this));
            for (auto& m : movs) {
                if (m.first == reyX && m.second == reyY) {
                    return true;
                }
            }
        }
    }
    return false;
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

    Peon* peonMovido = dynamic_cast<Peon*>(pieza);
    bool esAvanceDoble = false;

    // Detectar si es un avance doble de peón
    if (peonMovido) {
        int deltaFila = nuevaFila - pieza->getY();
        if (abs(deltaFila) == 2) {
            // Peón avanzó dos casillas
            ultimoPeonDobleX = nuevaColumna;
            ultimoPeonDobleY = nuevaFila - (deltaFila / 2);  // casilla intermedia
            turnoPeonDoble = pieza->getBando();
            esAvanceDoble = true;
        }
    }

    // --- Captura al paso ---
    if (peonMovido && abs(nuevaColumna - pieza->getX()) == 1 &&
        nuevaFila - pieza->getY() == (pieza->getBando() == 0 ? 1 : -1)) {

        if (!obtenerPieza(nuevaColumna, nuevaFila) &&
            turnoPeonDoble != -1 &&
            turnoPeonDoble != pieza->getBando() &&
            nuevaColumna == ultimoPeonDobleX &&
            pieza->getY() == (pieza->getBando() == 0 ? (nuevaFila - 1) : (nuevaFila + 1))) {

            // Aquí eliminamos el peón
            int filaPeonCapturado = (pieza->getBando() == 0) ? nuevaFila - 1 : nuevaFila + 1;

            for (auto it = piezas.begin(); it != piezas.end(); ++it) {
              
                if ((*it)->getX() == nuevaColumna && (*it)->getY() == filaPeonCapturado &&
                    dynamic_cast<Peon*>(*it)) {
                     // compruebo posicion peon capturado--->std::cout << "Peón capturado encontrado en (" << (*it)->getX() << "," << (*it)->getY() << ")" << std::endl;
                    delete* it;
                    piezas.erase(it);
                   
                    glutPostRedisplay();
	
                    break;
                }
            }
        }
    }

 

    bool capturado = false;

    // Buscar si hay una pieza en la casilla destino
    for (auto it = piezas.begin(); it != piezas.end(); ++it) {
        if ((*it)->getX() == nuevaColumna && (*it)->getY() == nuevaFila) {

            // Si la pieza en destino es del mismo bando, no mover ni eliminar nada
            if ((*it)->getBando() == pieza->getBando()) {
                return; // Movimiento inválido, cancela el movimiento
			}
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

    // Actualizar estado de jaque tras mover
    actualizarEstadoJaque();

    glutPostRedisplay();

    // ----------- CORONACIÓN DEL PEÓN -----------
    Peon* peon = dynamic_cast<Peon*>(pieza);
    if (peon) {
        int filaCoronacion = (peon->getBando() == 0) ? (numFilas - 1) : 0;
        if (nuevaFila == filaCoronacion) {
            int bando = peon->getBando();
            auto it = std::find(piezas.begin(), piezas.end(), peon);
            if (it != piezas.end()) {
                delete* it;
                piezas.erase(it);
            }

            // Guardar la posición y el bando para la coronación
            if (mundo) {
                mundo->coronacionX = nuevaColumna;
                mundo->coronacionY = nuevaFila;
                mundo->colorCoronacion = bando;
                mundo->peonACoronarse = nullptr; // Ya lo eliminaste, pero puedes guardar nullptr o la info
                mundo->setEstadoActual(CORONACION);
                glutPostRedisplay();
            }
            return; // Termina la función tras coronar
        }
    }

    
    // ----------- FIN CORONACIÓN DEL PEÓN -----------
    // 
    // Si no hubo avance doble, resetea la oportunidad de captura al paso
    if (!esAvanceDoble) {
        ultimoPeonDobleX = -1;
        ultimoPeonDobleY = -1;
        turnoPeonDoble = -1;
    }


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

/*const std::vector<Pieza*>& Tablero::getPiezas() const {
    return piezas;
}*/