#include "IA.h"
#include "tablero.h"
#include "Pieza.h"
#include <cstdlib>

IA::IA(int bando)
    : bando_(bando)
{
}

void IA::jugar(Tablero& tablero) {
    std::vector<Movimiento> jugadas;
    std::vector<int> puntuaciones;

    for (Pieza* p : tablero.getPiezas()) {
        if (p->getBando() != bando_) continue;
        auto movs = p->movimientosPosibles(tablero);
        for (auto& mv : movs) {
            int col = mv.first, fil = mv.second;
            int score = IA::evaluarJugada(tablero, p, col, fil, bando_);
            if (p->mueve(tablero, col, fil))
                jugadas.push_back(Movimiento{ p, col, fil }), puntuaciones.push_back(score);
        }
    }
    if (jugadas.empty()) return;

    // Elige la jugada con mayor puntuaci�n (si hay empate, elige aleatoria entre las mejores)
    int maxScore = *std::max_element(puntuaciones.begin(), puntuaciones.end());
    std::vector<int> mejores;
    for (size_t i = 0; i < puntuaciones.size(); ++i)
        if (puntuaciones[i] == maxScore) mejores.push_back(i);

    int idx = mejores[std::rand() % mejores.size()];
    Movimiento m = jugadas[idx];
    tablero.colocarPieza(m.pieza, m.col, m.fil);
}

// Devuelve true si la casilla (col, fil) est� amenazada por alguna pieza del oponente
bool IA::estaAmenazada( Tablero& tablero, int col, int fil, int bandoPropio) {
    for (Pieza* p : tablero.getPiezas()) {
        if (p->getBando() == bandoPropio) continue; // Solo piezas del oponente
        auto movs = p->movimientosPosibles(tablero);
        for (const auto& mv : movs) {
            if (mv.first == col && mv.second == fil)
                return true;
        }
    }
    return false;
}

int IA::evaluarJugada(Tablero& tablero, Pieza* pieza, int col, int fil, int bando) {
    int score = 0;
    Pieza* objetivo = tablero.obtenerPieza(col, fil);

    // Captura valiosa
    if (objetivo && objetivo->getBando() != bando) {
        score += objetivo->getValor() * 10;
    }

    // Penaliza si la pieza que se mueve queda amenazada tras mover
    if (IA::estaAmenazada(tablero, col, fil, bando)) {
        score -= pieza->getValor() * 2;
    }

    // Penaliza si hay otras piezas propias valiosas amenazadas
    for (Pieza* aliada : tablero.getPiezas()) {
        if (aliada->getBando() != bando || aliada == pieza) continue;
        if (aliada->getValor() >= 5 && IA::estaAmenazada(tablero, aliada->getX(), aliada->getY(), bando)) {
            score -= aliada->getValor();
        }
    }

    // Si la pieza es el rey, penaliza si se mueve a una casilla amenazada
    if (pieza->getValor() >= 1000 && IA::estaAmenazada(tablero, col, fil, bando)) {
        score -= 1000;
    }

    // Penaliza si deja al rey propio en jaque (solo si ya est� en jaque)
    if (tablero.estaEnJaque(bando)) {
        score -= 1000;
    }

    // Bonifica si tras mover, una pieza rival queda amenazada
    for (Pieza* rival : tablero.getPiezas()) {
        if (rival->getBando() != bando && IA::estaAmenazada(tablero, rival->getX(), rival->getY(), bando)) {
            score += rival->getValor();
        }
    }

    if (objetivo && objetivo->getBando() != bando) {
        score += objetivo->getValor() * 5; // Bonificaci�n proporcional al valor
    }

    // Bonifica si la jugada mueve una pieza aliada a una casilla adyacente al rey y esa casilla estaba amenazada
    Rey* rey = tablero.getRey(bando);
    int rx = rey->getX();
    int ry = rey->getY();
    if (std::abs(col - rx) <= 1 && std::abs(fil - ry) <= 1 && !(col == rx && fil == ry)) {
        if (IA::estaAmenazada(tablero, col, fil, bando)) {
            score += 5; // Bonificaci�n por proteger al rey
        }
    }

    // Bonifica si la pieza que se mueve es el rey y va a una casilla segura
    if (pieza == rey && !IA::estaAmenazada(tablero, col, fil, bando)) {
        score += 5;
    }

    // Eval�a la seguridad del rey: penaliza amenazas alrededor del rey
    int amenazasAlrededor = IA::contarAmenazasAlrededorRey(tablero, bando);
    score -= amenazasAlrededor * 3;

    // Bonifica la movilidad de piezas aliadas cerca del rey (m�s movilidad, mejor defensa)
    int movilidad = IA::movilidadCercaDelRey(tablero, bando);
    score += movilidad;

    // Bonifica si la jugada protege una pieza propia valiosa
    for (Pieza* aliada : tablero.getPiezas()) {
        if (aliada->getBando() != bando) continue;
        // Considera valiosa si su valor es alto
        if (aliada->getValor() >= 5 && aliada != pieza) {
            // Si la pieza aliada est� amenazada
            if (IA::estaAmenazada(tablero, aliada->getX(), aliada->getY(), bando)) {
                // �La jugada mueve una pieza a una casilla desde la que podr�a defender a la valiosa?
                auto movs = pieza->movimientosPosibles(tablero);
                for (const auto& mv : movs) {
                    if (mv.first == aliada->getX() && mv.second == aliada->getY()) {
                        score += aliada->getValor(); // Bonifica por proteger
                        break;
                    }
                }
            }
        }
    }

    // Bonifica si mueve a una casilla segura (no amenazada), priorizando piezas de mayor valor
    if (!IA::estaAmenazada(tablero, col, fil, bando)) {
        // Bonificaci�n proporcional al valor de la pieza
        score += pieza->getValor() * 5; // Ajusta el multiplicador seg�n lo que valores
    }

    return score;
}


// Funci�n auxiliar para contar piezas que protegen al rey
int IA::contarProteccionRey(Tablero& tablero, int bando) {
    Rey* rey = tablero.getRey(bando);
    int x = rey->getX();
    int y = rey->getY();
    int proteccion = 0;
    for (Pieza* aliada : tablero.getPiezas()) {
        if (aliada->getBando() == bando && aliada != rey) {
            auto movs = aliada->movimientosPosibles(tablero);
            for (const auto& mv : movs) {
                if (mv.first == x && mv.second == y) {
                    proteccion++;
                    break;
                }
            }
        }
    }
    return proteccion;
}

int IA::contarAmenazasAlrededorRey(Tablero& tablero, int bando) {
    Rey* rey = tablero.getRey(bando);
    int x = rey->getX();
    int y = rey->getY();
    int amenazas = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;
            int nx = x + dx;
            int ny = y + dy;
            if (nx >= 0 && nx < tablero.getNumColumnas() && ny >= 0 && ny < tablero.getNumFilas()) {
                if (IA::estaAmenazada(tablero, nx, ny, bando))
                    amenazas++;
            }
        }
    }
    return amenazas;
}

int IA::movilidadCercaDelRey(Tablero& tablero, int bando) {
    Rey* rey = tablero.getRey(bando);
    int rx = rey->getX();
    int ry = rey->getY();
    int movilidad = 0;
    for (Pieza* aliada : tablero.getPiezas()) {
        if (aliada->getBando() != bando || aliada == rey) continue;
        int ax = aliada->getX();
        int ay = aliada->getY();
        // Considera piezas en casillas adyacentes al rey
        if (std::abs(ax - rx) <= 1 && std::abs(ay - ry) <= 1) {
            movilidad += aliada->movimientosPosibles(tablero).size();
        }
    }
    return movilidad;
}

Pieza* IA::elegirPiezaCoronacion(int x, int y) {  //Aqui se puede a�adir si la IA quiere una u otra pieza
    //de momento siempre Torre:
    return new Torre(x, y, bando_);
}

