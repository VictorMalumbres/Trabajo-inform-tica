#pragma once
#ifndef MACHINE_H
#define MACHINE_H
#include <random>
#include <vector>

// Adelanto de clases
class Tablero;
class Pieza;

class IA {
public:
    /// bando = 0 (blancas) o 1 (negras)
    explicit IA(int bando);

    /// Genera y ejecuta un movimiento aleatorio sobre el tablero
    void jugar(Tablero& tablero);

private:
    int bando_;

    // Estructura local para representar un movimiento
    struct Movimiento {
        Pieza* pieza;
        int col;
        int fil;
    };
};

#endif