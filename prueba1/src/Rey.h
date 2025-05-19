#pragma once
#include "Pieza.h"

class Rey : public Pieza {
public:
<<<<<<< Updated upstream
    Rey(float x, float y, int bando)
        : Pieza(x, y, bando) {
=======
    Rey(int x, int y, unsigned char r, unsigned char g, unsigned char b)
        : Pieza(x, y, r, g, b) {
>>>>>>> Stashed changes
    }

    void dibuja() override;  // marca override para mayor claridad
    void mueve();            // añade método mueve para que el peón se mueva
};
