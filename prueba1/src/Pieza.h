#pragma once
#include <freeglut.h>
#include <vector>
#include <utility>
//#include "Tablero.h"

class Tablero; //Declaración adelantada


class Pieza {
protected:
    int x, y;
    int bando;  // 0 para blanco, 1 para negro
    int columna, fila;
    bool resaltado = false;
    float colorR = 1.0f;
    float colorG = 1.0f;
    float colorB = 1.0f;

public:
    Pieza(int x, int y, int bando);
    virtual ~Pieza() {}

    int getBando();
    int getX();
    int getY();
    void setPosicion(int f, int c) { x = c; y = f; };  //x -> columna e y -> fila

    void setResaltado(bool r) { resaltado = r; }
    bool estaResaltado() const { return resaltado; }

    virtual void dibuja() = 0;

    virtual bool mueve(Tablero& tablero, int nuevaColumna, int nuevaFila) = 0;

    virtual std::vector<std::pair<int, int>> movimientosPosibles(Tablero& tablero) = 0;

    virtual int getValor() const = 0;

    virtual Pieza* clonar() const = 0;


};