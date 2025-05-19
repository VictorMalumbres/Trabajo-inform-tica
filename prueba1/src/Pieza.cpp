#include "Pieza.h"

<<<<<<< Updated upstream
Pieza::Pieza(float x, float y, int bando)
    : x(x), y(y), bando(bando) {
=======
Pieza::Pieza(int x, int y, unsigned char r, unsigned char g, unsigned char b)
    : x(x), y(y) {
    color[0] = r;  // Componente rojo
    color[1] = g;  // Componente verde
    color[2] = b;  // Componente azul
>>>>>>> Stashed changes
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

