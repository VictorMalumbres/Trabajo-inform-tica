#pragma once
#include "Pieza.h"

class Rey : public Pieza {

private:
    bool enJaque = false;
public:
    Rey(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    //void mueve();            // añade método mueve para que el peón se mueva

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) override;

    std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) override;

    int getValor() const override { return 1000; } // Valor típico del rey


    
  
    void setEnJaque(bool valor) { enJaque = valor; }
    bool estaEnJaque() const { return enJaque; }


    Pieza* clonar() const {
        return new Rey(*this);  // usa el constructor copia predeterminado
    }




};
