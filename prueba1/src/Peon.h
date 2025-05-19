#pragma once
#include "Pieza.h"

class Peon : public Pieza {
protected:
    float colorR = 1.0f;
    float colorG = 1.0f;
    float colorB = 1.0f;
public:
    Peon(int x, int y, int bando)
        : Pieza(x, y, bando) {
    }

    void dibuja() override;  // marca override para mayor claridad
    void mueve();            // añade método mueve para que el peón se mueva


};
