#pragma once
#include "Pieza.h"

class Peon : public Pieza {
public:
<<<<<<< Updated upstream
    Peon(float x, float y, int bando)
        : Pieza(x, y, bando) {
=======
    Peon(int x, int y, unsigned char r, unsigned char g, unsigned char b)
        : Pieza(x, y, r, g, b) {
>>>>>>> Stashed changes
    }

    void dibuja() override;  // marca override para mayor claridad
    void mueve();            // a�ade m�todo mueve para que el pe�n se mueva


};
