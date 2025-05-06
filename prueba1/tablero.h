#pragma once
#include <freeglut.h>  // Necesario para OpenGL

class Tablero {
public:
    Tablero(int filas, int columnas);
    void inicializa();  // Inicializa el tablero (vac�o por ahora)
    void dibuja();      // M�todo para dibujar el tablero con OpenGL

private:
    int filas;      // N�mero de filas del tablero
    int columnas;   // N�mero de columnas del tablero
};

