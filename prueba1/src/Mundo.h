#pragma once
#include "tablero.h"
#include <freeglut.h>

class Mundo {
private:
    Tablero tablero;  // Tablero 
	Tablero tablero2; // Tablero 2

public:
    Mundo();
    void inicializa();  // Inicializar el mundo (tablero, piezas, etc.)
    void dibuja();  // Dibuja el tablero y las piezas
};