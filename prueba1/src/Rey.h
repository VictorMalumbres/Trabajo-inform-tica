#pragma once
#include "Pieza.h"

class Rey : public Pieza {
public:
    Rey(float x, float y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    void mueve();            // a�ade m�todo mueve para que el pe�n se mueva
};
