#pragma once
#include <freeglut.h>

class Pieza {
protected:
    int x, y;
    int bando;  // 0 para blanco, 1 para negro
    int columna, fila;
    bool resaltado = false;

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
};