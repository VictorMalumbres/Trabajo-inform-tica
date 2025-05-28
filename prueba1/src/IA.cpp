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

    // Bonifica si tras mover, una pieza rival queda amenazada
    for (Pieza* rival : tablero.getPiezas()) {
        if (rival->getBando() != bando && IA::estaAmenazada(tablero, rival->getX(), rival->getY(), bando)) {
            score += rival->getValor();
        }
    }

    // Bonifica si la jugada protege una pieza propia valiosa
    // (Por ejemplo, si tras mover, una pieza propia amenazada ya no lo está)
    // Esto requiere simular el movimiento y comprobar amenazas antes y después

    // Penaliza si deja al rey propio en jaque
    // (Requiere simular el movimiento y comprobar si el rey está en jaque)

    return score;
}