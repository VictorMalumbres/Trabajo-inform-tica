#pragma once
#include "Tablero.h"

class Mundo {
private:
    Tablero tablero;
    Tablero tablero2;
    int modoJuego; // 1 para 4x5, 2 para 4x8

public:
    Mundo();
    void setModoJuego(int modo) { modoJuego = modo; }
    
    void dibuja();
    void inicializaModo1();  // Para Silverman 4x5
    void inicializaModo2();  // Para Demi 4x8

};
