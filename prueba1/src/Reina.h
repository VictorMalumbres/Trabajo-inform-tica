#pragma once
#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    //void mueve();            // a�ade m�todo mueve para que el pe�n se mueva

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

};
