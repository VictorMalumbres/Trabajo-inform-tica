#pragma once
#ifndef IA_H
#define IA_H
#include <random>
#include <vector>

//Adelanto de clases
class Tablero;
class Pieza;

class IA {
public:
    //bando = 0 (blancas) o 1 (negras)
    explicit IA(int bando);

    //Para movimientos aleatorio sobre el tablero
    void jugar(Tablero& tablero);

private:
    int bando_;

    //Estructura para el movimiento
    struct Movimiento {
        Pieza* pieza;
        int col;
        int fil;
    };
};

#endif