#pragma once
#include "Tablero.h"

enum EstadoMundo {
    MENU,
    JUEGO,
    INSTRUCCIONES
};


class Mundo {
private:
    Tablero tablero;
    Tablero tablero2;
    int modoJuego; // 1 para 4x5, 2 para 4x8

    int seleccionX = -1;
    int seleccionY = -1;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente);
    EstadoMundo estadoActual;

public:
    Mundo();
    void setModoJuego(int modo) { modoJuego = modo; }

    void mostrarMenuEnVentana(); //menú texto
    void manejarEntradaMenu(unsigned char key, int x, int y); //menú switch
    void mostrarInstruccionesEnVentana(); //instrucciones juego

    void iniciarJuego(); //silverman
    void iniciar2dojuego(); //demi
    void cerrarAplicacion();
    void mostrarPausa();
    
    void dibuja();
    void inicializaModo1();  // Para Silverman 4x5
    void inicializaModo2();  // Para Demi 4x8
    void procesarClick(int x, int y);  //Procesar el movimiento de raton

};
