#include "Pieza.h"

Pieza::Pieza(float x, float y, int bando)
    : x(x), y(y), bando(bando) {
}

float Pieza::getX() {
    return x;
}

float Pieza::getY() {
    return y;
}
int Pieza::getBando() {
	return bando;
}

