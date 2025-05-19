#pragma once
#include <freeglut.h>

class Pieza {
protected:
<<<<<<< Updated upstream
    float x, y;
    int bando;  // 0 para blanco, 1 para negro

public:
    Pieza(float x, float y, int bando);
    virtual ~Pieza() {}

    int getBando();
    float getX();
    float getY();
=======
    int x, y;  // Coordenadas de la pieza
    unsigned char color[3];  // Color de la pieza (RGB)

public:
    Pieza(int x, int y, unsigned char r, unsigned char g, unsigned char b);  
    virtual void dibuja() = 0;  // Método virtual para dibujar la pieza

    int getX();
    int getY();
    void setPosicion(int f, int c) { x = c; y = f; };  //x -> columna e y -> fila
};
>>>>>>> Stashed changes

    virtual void dibuja() = 0;
};