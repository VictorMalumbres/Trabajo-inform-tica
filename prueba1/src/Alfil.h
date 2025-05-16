#pragma once
#include "Pieza.h"

class Alfil : public Pieza {
public:
    Alfil(float x, float y, unsigned char r, unsigned char g, unsigned char b)
        : Pieza(x, y, r, g, b) {
    }

    void dibuja();
};

