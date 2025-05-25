#include "Machine.h"
#include "tablero.h"
#include "Pieza.h"
#include <cstdlib>

IA::IA(int bando)
    : bando_(bando)
{
}

void IA::jugar(Tablero& tablero) {
    // 1) Recolectar todas las jugadas legales
    std::vector<Movimiento> jugadas;
    for (Pieza* p : tablero.getPiezas()) {
        if (p->getBando() != bando_) continue;
        auto movs = p->movimientosPosibles(tablero);
        for (auto& mv : movs) {
            int col = mv.first, fil = mv.second;
            if (p->mueve(tablero, col, fil))
                jugadas.push_back(Movimiento{ p, col, fil });
        }
    }
    if (jugadas.empty()) return;

    // 2) Selección aleatoria
    int idx = std::rand() % static_cast<int>(jugadas.size());
    Movimiento m = jugadas[idx];

    // 3) Ejecutar la jugada
    tablero.colocarPieza(m.pieza, m.col, m.fil);
}