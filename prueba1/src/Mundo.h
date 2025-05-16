#pragma once
#include "Tablero.h"
#include <freeglut.h>

class Mundo {
private:
    Tablero tablero;  // Tablero
    Tablero tablero2; //2do juego

public:
    Mundo(); 
    void inicializa();  // Inicializar el mundo (tablero, piezas, etc.)
    void dibuja();  // Dibuja el tablero y las piezas
};
