#pragma once
#include <freeglut.h>  // Necesario para OpenGL

class Tablero {
public:
    Tablero(int filas, int columnas);
    void inicializa();  // Inicializa el tablero (vacío por ahora)
    void dibuja();      // Método para dibujar el tablero con OpenGL

private:
    int filas;      // Número de filas del tablero
    int columnas;   // Número de columnas del tablero
};

