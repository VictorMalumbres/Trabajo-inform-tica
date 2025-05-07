#include "Pieza.h"

Pieza::Pieza(float x, float y, unsigned char r, unsigned char g, unsigned char b)
    : x(x), y(y) {
    color[0] = r;  // Componente rojo
    color[1] = g;  // Componente verde
    color[2] = b;  // Componente azul
}

float Pieza::getX() {
    return x;
}

float Pieza::getY() {
    return y;
}

