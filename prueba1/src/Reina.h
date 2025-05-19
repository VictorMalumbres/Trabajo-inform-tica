#pragma once
#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(float x, float y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    void mueve();            // añade método mueve para que el peón se mueva
};
