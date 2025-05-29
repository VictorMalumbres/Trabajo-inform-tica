#include "IA.h"
#include "tablero.h"
#include "Pieza.h"

#include <algorithm>
#include <iostream>

IA::IA(int bando, int profundidad)
    : bando_(bando)
    , maxDepth_(profundidad)
{
}

void IA::jugar(Tablero& tablero) {
    if (tablero.getTurno() != bando_) {
        // No es nuestro turno, no hacemos nada
        return;
    }

    tablero.limpiarSeleccion();

    // Hacemos una copia para la búsqueda
    Tablero* copia = tablero.clonar();
    std::pair<int, Movimiento> resultado =
        minimax(copia, maxDepth_, INT_MIN, INT_MAX, true);
    int eval = resultado.first;
    Movimiento mov = resultado.second;
    delete copia;

    std::cout << "[IA] eval=" << eval
        << " mueve (" << mov.origX << "," << mov.origY << ")->("
        << mov.destX << "," << mov.destY << ")\n";

    // Aplica el movimiento **real** con colocarPieza
    Pieza* p = tablero.obtenerPieza(mov.origX, mov.origY);
    if (p) {
        tablero.colocarPieza(p, mov.destX, mov.destY);
    }
    else {
        std::cerr << "[IA] ERROR: no hay pieza en origen\n";
    }
}

std::pair<int, IA::Movimiento>

IA::minimax(Tablero* tablero, int depth, int alpha, int beta, bool maximizingPlayer) {

    if (depth == 0) {
        return { evaluarTablero(*tablero), {0,0,0,0} };
    }

    int jugador = maximizingPlayer ? bando_ : (1 - bando_);
    std::vector<std::pair<int, Movimiento>> candidatos;
    std::vector<std::pair<int, Movimiento>> propios;

    // Recorremos todas las piezas de `jugador`
    for (Pieza* p : tablero->getPiezas()) {
        if (p->getBando() != jugador) continue;
        int x = p->getX(), y = p->getY();

        for (auto& mv : p->movimientosPosibles(*tablero)) {
            int nx = mv.first, ny = mv.second;

            // Simulamos en un clon
            Tablero* hijo = tablero->clonar();
            Pieza* ph = hijo->obtenerPieza(x, y);
            if (!ph) {
                delete hijo;
                continue;
            }

            hijo->colocarPieza(ph, nx, ny, true);

            // 2) Si dejamos al propio rey en jaque => descartamos
            if (hijo->estaEnJaque(jugador)) {
                delete hijo;
                continue;
            }

            // 3) Llamada recursiva
            int score = minimax(hijo, depth - 1, alpha, beta,
                !maximizingPlayer).first;
            delete hijo;

            Pieza* destino = tablero->obtenerPieza(nx, ny);
            bool selfCapture = destino && destino->getBando() == jugador;
            Movimiento mov{ x, y, nx, ny };
            if (selfCapture) {
                propios.emplace_back(score, mov);
            }
            else {
                candidatos.emplace_back(score, mov);
            }
        }
    }

    // Si no hay movimientos “no‐propios” pero sí “propios”, los usamos
    if (candidatos.empty() && !propios.empty()) {
        candidatos = std::move(propios);
    }

    // Si no hay movimientos legales, devolvemos jaque mate o tablas
    if (candidatos.empty()) {
        // Si el rey está en jaque, es mate; si no, tablas (0)
        bool jaque = tablero->estaEnJaque(jugador);
        int val;
        if (jaque) {
            val = maximizingPlayer ? INT_MIN / 2 : INT_MAX / 2;
        }
        else {
            val = 0;
        }

        /*if (depth == maxDepth_) {
            // Recorremos sin filtros y devolvemos la primera válida
            for (Pieza* p : tablero->getPiezas()) {
                if (p->getBando() != jugador) continue;
                int x = p->getX(), y = p->getY();
                for (auto& mv : p->movimientosPosibles(*tablero)) {
                    Tablero* hijo = tablero->clonar();
                    Pieza* ph = hijo->obtenerPieza(x, y);
                    if (!ph) { delete hijo; continue; }
                    hijo->colocarPieza(ph, mv.first, mv.second, true);
                    // Solo aceptamos si no deja al rey en jaque
                    if (!hijo->estaEnJaque(jugador)) {
                        Movimiento mov{ x, y, mv.first, mv.second };
                        delete hijo;
                        return { evaluarTablero(*tablero), mov };
                    }
                    delete hijo;
                }
            }
        }
        // Subniveles o fallo absoluto: devolvemos jaque o tablas
        return { val, {0,0,0,0} };*/

        if (depth == maxDepth_) {
            for (Pieza* p : tablero->getPiezas()) {
                if (p->getBando() != jugador) continue;
                int x = p->getX(), y = p->getY();
                for (auto& mv : p->movimientosPosibles(*tablero)) {
                    Tablero* hijo = tablero->clonar();
                    Pieza* ph = hijo->obtenerPieza(x, y);
                    if (!ph) { delete hijo; continue; }
                    hijo->colocarPieza(ph, mv.first, mv.second, /*simular=*/true);
                    if (!hijo->estaEnJaque(jugador)) {
                        Movimiento m{ x,y,mv.first,mv.second };
                        int matEval = evaluarTablero(*tablero);
                        delete hijo;
                        return { matEval, m };
                    }
                    delete hijo;
                }
            }
        }

        // Jaque mate o tablas (sin movimientos legales)
        return { val, {0,0,0,0} };
    }

    // Seleccionamos mejor o peor según maximizingPlayer
    int mejorScore = candidatos[0].first;
    for (auto& par : candidatos) {
        if (maximizingPlayer && par.first > mejorScore)
            mejorScore = par.first;
        if (!maximizingPlayer && par.first < mejorScore)
            mejorScore = par.first;
    }

    // Poda alpha-beta
    if (maximizingPlayer) alpha = std::max(alpha, mejorScore);
    else              beta = std::min(beta, mejorScore);
    if (beta <= alpha) {
        // En poda podemos devolver un mov cualquiera con ese score
        for (auto& c : candidatos) {
            if (c.first == mejorScore)
                return c;
        }
    }

    // Recolectamos todos los movimientos que empatan con mejorScore
    std::vector<Movimiento> empates;
    for (auto& c : candidatos)
        if (c.first == mejorScore)
            empates.push_back(c.second);

    // Escogemos uno al azar para no repetir siempre el mismo
    Movimiento elegido = empates[std::rand() % empates.size()];
    return { mejorScore, elegido };
}

int IA::evaluarTablero(Tablero& tablero) const {
    int score = 0;
    for (Pieza* p : tablero.getPiezas()) {
        int v = p->getValor();
        score += (p->getBando() == bando_) ? v : -v;
    }
    return score;
}

bool IA::estaAmenazada(Tablero& tablero, int col, int fil, int bandoPropio) {
    for (Pieza* p : tablero.getPiezas()) {
        if (p->getBando() == bandoPropio) continue;
        for (auto& mv : p->movimientosPosibles(tablero)) {
            if (mv.first == col && mv.second == fil)
                return true;
        }
    }
    return false;
}

Pieza* IA::elegirPiezaCoronacion(int x, int y) {  //Aqui se puede añadir si la IA quiere una u otra pieza
    //de momento siempre Torre:
    return new Torre(x, y, bando_);
}
