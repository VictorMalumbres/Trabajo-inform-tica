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

    // Elige la jugada con mayor puntuación (si hay empate, elige aleatoria entre las mejores)
    int maxScore = *std::max_element(puntuaciones.begin(), puntuaciones.end());
    std::vector<int> mejores;
    for (size_t i = 0; i < puntuaciones.size(); ++i)
        if (puntuaciones[i] == maxScore) mejores.push_back(i);

    int idx = mejores[std::rand() % mejores.size()];
    Movimiento m = jugadas[idx];
    tablero.colocarPieza(m.pieza, m.col, m.fil);
}

// Devuelve true si la casilla (col, fil) está amenazada por alguna pieza del oponente
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

    // Penaliza si la pieza queda amenazada tras mover
    if (IA::estaAmenazada(tablero, col, fil, bando)) {
        score -= pieza->getValor();
    }

    // Si la pieza es el rey, penaliza si se mueve a una casilla amenazada
    if (pieza->getValor() >= 1000 && IA::estaAmenazada(tablero, col, fil, bando)) {
        score -= 1000;
    }

    // Penaliza si deja al rey propio en jaque
    if (tablero.estaEnJaque(bando)) {
        score -= 1000;
    }
	// Bonifica si mueve a una casilla segura (no amenazada)

    // Bonifica si tras mover, una pieza rival queda amenazada
    for (Pieza* rival : tablero.getPiezas()) {
        if (rival->getBando() != bando && IA::estaAmenazada(tablero, rival->getX(), rival->getY(), bando)) {
            score += rival->getValor();
        }
    }

    // Bonifica si tras mover, el rey está más protegido
    int proteccionAntes = contarProteccionRey(tablero, bando);

    // Si la jugada mueve una pieza a una casilla adyacente al rey, bonifica si esa casilla estaba amenazada
    Rey* rey = tablero.getRey(bando);

    int rx = rey->getX();
    int ry = rey->getY();
    if (std::abs(col - rx) <= 1 && std::abs(fil - ry) <= 1 && !(col == rx && fil == ry)) {
        if (IA::estaAmenazada(tablero, col, fil, bando)) {
            score += 5; // Bonificación por proteger al rey
        }
    }

    // (Opcional) Si la pieza que se mueve es el rey, bonifica si se mueve a una casilla no amenazada
    if (pieza == rey && !IA::estaAmenazada(tablero, col, fil, bando)) {
        score += 10; // Bonificación por mover el rey a una casilla segura
    }


    // Bonifica si la jugada protege una pieza propia valiosa
    // (Por ejemplo, si tras mover, una pieza propia amenazada ya no lo está)
    // Esto requiere simular el movimiento y comprobar amenazas antes y después


    return score;
}

// Función auxiliar para contar piezas que protegen al rey
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

Pieza* IA::elegirPiezaCoronacion(int x, int y) {
    //de momento siempre Torre:
    return new Torre(x, y, bando_);
}