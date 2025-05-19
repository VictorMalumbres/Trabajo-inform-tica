#pragma once
#include "Tablero.h"

enum EstadoMundo {
    MENU,
    JUEGO,
    INSTRUCCIONES
};

class Mundo {
private:
<<<<<<< Updated upstream
    Tablero tablero;
    Tablero tablero2;
    int modoJuego; // 1 para 4x5, 2 para 4x8

public:
    Mundo();
    void setModoJuego(int modo) { modoJuego = modo; }
    
    void dibuja();
    void inicializaModo1();  // Para Silverman 4x5
    void inicializaModo2();  // Para Demi 4x8

=======
    Tablero tablero;  // Tablero 
    int seleccionX = -1;
    int seleccionY = -1;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente);
    EstadoMundo estadoActual;

public:
    Mundo();
    void mostrarMenuEnVentana();
    void manejarEntradaMenu(unsigned char key, int x, int y);
    void mostrarInstruccionesEnVentana();
    void iniciarJuego();
    void cerrarAplicacion();
    void inicializa();  // Inicializar el mundo (tablero, piezas, etc.)
    void dibuja();  // Dibuja el tablero y las piezas
    void procesarClick(int x, int y);  //Procesar el movimiento de raton
>>>>>>> Stashed changes
};
