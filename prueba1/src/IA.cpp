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
            Pieza* objetivo = tablero.obtenerPieza(col, fil);
            int score = 0;
            if (objetivo && objetivo->getBando() != bando_) {
                score += objetivo->getValor() * 10; // Prioriza capturas valiosas
            }
            // Penaliza si la pieza queda amenazada tras mover (opcional, requiere funci�n extra)
            // score -= estaAmenazada(tablero, p, col, fil) ? p->getValor() : 0;

            // Bonus por mover piezas valiosas fuera de peligro (opcional)
            // if (p->getValor() >= 5 && estaAmenazada(tablero, p, p->getX(), p->getY()))
            //     score += 5;

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
