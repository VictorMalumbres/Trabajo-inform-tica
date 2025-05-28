#pragma once
#include "Tablero.h"
#include "IA.h"

enum EstadoMundo {
    MENU,
    JUEGO,
    INSTRUCCIONES,
    CONFIRMAR_MENU,
    CONFIRMAR_SALIR,
    VICTORIA,
    EMPATE,
    CORONACION,
    OPONENTE
};

class Mundo {
private:
    Tablero tablero;
    Tablero tablero2;
    int modoJuego; // 1 para 4x5, 2 para 4x8
    int volumen = 2;  //0-> No hay musica   1->Musica 15%   2->Musica 50%   3->Musica 100%

    bool enJuego = false;
    bool activarIA = false;

    int seleccionX = -1;
    int seleccionY = -1;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente); //texto
    void renderizarTextoGrande(const char* texto, float x, float y, float escala); //tama�o texto
    EstadoMundo estadoActual;

    IA iaNegras{ 1 };

public:
    Mundo();

    std::string musicaActual;
    int getVolumen() const { return volumen; };  //Para manejar volumen como private;
    void decrementoVolumen() { volumen--; };
    void incrementoVolumen() { volumen++; };

    void setModoJuego(int modo) { modoJuego = modo; } //modo de juego
    void setEstadoActual(EstadoMundo estado); // Declaraci�n sin cuerpo

    void mostrarConfirmacionSalir();
    void mostrarMenuEnVentana(); //men� texto
    void mostrarInstruccionesEnVentana(); //instrucciones juego

    void iniciarJuego(); //silverman
    void iniciar2dojuego(); //demi
    void cerrarAplicacion(); //salir
    void mostrarPausa(); //pausa en el juego (men�)

    void dibuja();
    void inicializaModo1();  // Para Silverman 4x5
    void inicializaModo2();  // Para Demi 4x8
    void procesarClick(int x, int y);  //Procesar el movimiento de raton
    bool estaEnMenu() const;
    void mostrarConfirmacionMenu();

    EstadoMundo getEstadoActual() const { return estadoActual; }

    void volverAlMenu();
    void inicializarTableros();

    // ** Declaraci�n de la funci�n manejarTeclado **
    static void manejarTeclado(unsigned char key, int x, int y);
    int jugadorGanador = -1; // 0 = blancas, 1 = negras
    void mostrarMenuVictoria();
    void mostrarMenuEmpate();

    int coronacionX = -1;
    int coronacionY = -1;
    int colorCoronacion = 0; // 0 = blanco, 1 = negro
    void mostrarMenuCoronacion();
    Pieza* peonACoronarse = nullptr;

    void volumenMusica();
    void mostrarMenuOponente();

    bool isIAActiva() const { return activarIA; };
    int getModoJuego() const { return modoJuego; };
    IA& getIA() { return iaNegras; };
};
