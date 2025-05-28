#pragma once
#include "Pieza.h"

class Torre : public Pieza {
public:
    Torre(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    //void mueve();            // añade método mueve para que el peón se mueva

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;
	// Implementación del método mueve para la Torre

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

    int getValor() const override { return 5; } // Valor típico de la torre

    Pieza* clonar() const {
        return new Torre(*this);  // usa el constructor copia predeterminado
    }

};
