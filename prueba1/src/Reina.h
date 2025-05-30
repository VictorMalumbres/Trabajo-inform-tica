#pragma once
#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

    int getValor() const override { return 9; } // Valor t�pico de la reina

    Pieza* clonar() const {
        return new Reina(*this);  // usa el constructor copia predeterminado
    }
};