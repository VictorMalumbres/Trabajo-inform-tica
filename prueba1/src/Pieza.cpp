#include "Pieza.h"

Pieza::Pieza(int x, int y, int bando)
    : x(x), y(y), bando(bando) {
}

int Pieza::getX() {
    return x;
}

int Pieza::getY() {
    return y;
}
int Pieza::getBando() {
	return bando;
}