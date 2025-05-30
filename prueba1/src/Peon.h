#pragma once
#include "Pieza.h"

class Peon : public Pieza 
{
public:
    Peon(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

    int getValor() const override { return 1; } // Valor típico del peón

    Pieza* clonar() const {
        return new Peon(*this);  // usa el constructor copia predeterminado
    }
};