#pragma once
#include "Pieza.h"

class Alfil : public Pieza {
public:
    Alfil(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

    int getValor() const override { return 3; } // Valor típico del alfil

    Pieza* clonar() const {
        return new Alfil(*this);  // usa el constructor copia predeterminado
    }

};