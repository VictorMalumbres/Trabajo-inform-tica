#pragma once
#include "Tablero.h"

enum EstadoMundo {
    MENU,
    JUEGO,
    INSTRUCCIONES,
    CONFIRMAR_MENU,
    CONFIRMAR_SALIR 
};



class Mundo {
private:
    Tablero tablero;
    Tablero tablero2;
    int modoJuego; // 1 para 4x5, 2 para 4x8

    int seleccionX = -1;
    int seleccionY = -1;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente); //texto
    void renderizarTextoGrande(const char* texto, float x, float y, float escala); //tamaño texto
    EstadoMundo estadoActual;

public:
    Mundo();
    void setModoJuego(int modo) { modoJuego = modo; } //modo de juego
    void setEstadoActual(EstadoMundo estado) { estadoActual = estado; }
    void mostrarConfirmacionSalir();


    void mostrarMenuEnVentana(); //menú texto
    void manejarEntradaMenu(unsigned char key, int x, int y); //menú switch
    void mostrarInstruccionesEnVentana(); //instrucciones juego

    void iniciarJuego(); //silverman
    void iniciar2dojuego(); //demi
    void cerrarAplicacion(); //salir
    void mostrarPausa(); //pausa en el juego (menú)
    
    void dibuja();
    void inicializaModo1();  // Para Silverman 4x5
    void inicializaModo2();  // Para Demi 4x8
    void procesarClick(int x, int y);  //Procesar el movimiento de raton
    bool estaEnMenu() const;
    void mostrarConfirmacionMenu();


};
