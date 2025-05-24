#pragma once
#include "Tablero.h"

enum EstadoMundo {
    MENU,
    JUEGO,
    INSTRUCCIONES,
    CONFIRMAR_MENU,
    CONFIRMAR_SALIR,
    VICTORIA 
};


class Mundo {
private:
    Tablero tablero;
    Tablero tablero2;
    int modoJuego; // 1 para 4x5, 2 para 4x8
    //int volumen = 2;

    bool enJuego = false;

    int seleccionX = -1;
    int seleccionY = -1;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente); //texto
    void renderizarTextoGrande(const char* texto, float x, float y, float escala); //tamaño texto
    EstadoMundo estadoActual;

public:
    Mundo();

    int volumen = 2;  //Habria que ponerlo en private
    std::string musicaActual;

    void setModoJuego(int modo) { modoJuego = modo; } //modo de juego
    void setEstadoActual(EstadoMundo estado); // Declaración sin cuerpo

    void mostrarConfirmacionSalir();

    void mostrarMenuEnVentana(); //menú texto
    //void manejarEntradaMenu(unsigned char key, int x, int y); //menú switch
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
    EstadoMundo getEstadoActual() const { return estadoActual; }

    void volverAlMenu();
    void inicializarTableros();


    // ** Declaración de la función manejarTeclado **
    static void manejarTeclado(unsigned char key, int x, int y);
    int jugadorGanador = -1; // 0 = blancas, 1 = negras
    void mostrarMenuVictoria();

};
