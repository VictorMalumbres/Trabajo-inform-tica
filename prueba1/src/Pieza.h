#pragma once
#include <freeglut.h>

class Pieza {
protected:
    float x, y;  // Coordenadas de la pieza
    unsigned char color[3];  // Color de la pieza (RGB)

public:
    Pieza(float x, float y, unsigned char r, unsigned char g, unsigned char b);  
    virtual void dibuja() = 0;  // Método virtual para dibujar la pieza

    float getX();
    float getY();
};

