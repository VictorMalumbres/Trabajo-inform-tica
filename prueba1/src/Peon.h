#pragma once
#include "Pieza.h"

class Peon : public Pieza 
{
public:
    Peon(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    //void mueve();            // añade método mueve para que el peón se mueva

    bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila);

};
