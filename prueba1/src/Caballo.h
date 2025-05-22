#pragma once
#include "Pieza.h"

class Caballo : public Pieza {
public:
    Caballo(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    //void mueve();            // a�ade m�todo mueve para que el pe�n se mueva

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

};
