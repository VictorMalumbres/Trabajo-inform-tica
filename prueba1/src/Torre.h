#pragma once
#include "Pieza.h"


class Torre : public Pieza {
public:
<<<<<<< Updated upstream
    Torre(float x, float y, int bando)
        : Pieza(x, y, bando) {
=======
    Torre(int x, int y, unsigned char r, unsigned char g, unsigned char b)
        : Pieza(x, y, r, g, b) {
>>>>>>> Stashed changes
    }

    void dibuja() override;  // marca override para mayor claridad
    void mueve();            // añade método mueve para que el peón se mueva
};
