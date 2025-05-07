#pragma once
#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(float x, float y, unsigned char r, unsigned char g, unsigned char b)
        : Pieza(x, y, r, g, b) {
    }

    void dibuja(); 
};
