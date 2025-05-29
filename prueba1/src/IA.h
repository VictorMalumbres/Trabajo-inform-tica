#pragma once
#ifndef IA_H
#define IA_H

#include <utility>
#include <vector>
#include <climits>

class Tablero;
class Pieza;

class IA {
public:
    // bando: 0 = blancas, 1 = negras
    // profundidad: número de plies a explorar
    explicit IA(int bando, int profundidad = 3);

    // Calcula la mejor jugada y la ejecuta sobre 'tablero'
    void jugar(Tablero& tablero);

    static bool estaAmenazada(Tablero& tablero, int col, int fil, int bandoPropio);

    Pieza* elegirPiezaCoronacion(int x, int y);

private:
    int bando_;
    int maxDepth_;

    // Representa un movimiento: from (x,y) to (x',y')
    struct Movimiento {
        int origX, origY;
        int destX, destY;
    };

    // Minimax con poda alpha-beta. Devuelve {evaluación, mejorMovimiento}
    std::pair<int, Movimiento>
        minimax(Tablero* tablero, int depth, int alpha, int beta, bool maximizingPlayer);

    // Heurística simple: diferencia de material
    int evaluarTablero(Tablero& tablero) const;
};

#endif // IA_H
