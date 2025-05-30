#pragma once
#include "Pieza.h"

class Caballo : public Pieza {
public:
    Caballo(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    //void mueve();            // añade método mueve para que el peón se mueva

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

    int getValor() const override { return 3; } // Valor típico del caballo

	Pieza* clonar() const override {
		return new Caballo(*this);  // usa el constructor copia predeterminado
	}

};