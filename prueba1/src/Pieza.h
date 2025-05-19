#pragma once
#include <freeglut.h>

class Pieza {
protected:
    float x, y;
    int bando;  // 0 para blanco, 1 para negro

public:
    Pieza(float x, float y, int bando);
    virtual ~Pieza() {}

    int getBando();
    float getX();
    float getY();

    virtual void dibuja() = 0;
};