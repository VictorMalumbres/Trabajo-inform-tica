#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "Pieza.h"
#include "Alfil.h"
#include "Caballo.h"

#include "Torre.h"
#include "Reina.h"
#include "Rey.h"
#include "Peon.h"

class Tablero {
private:
    std::vector<Pieza*> piezas;
    int seleccionX = -1; // Columna seleccionada, -1 si ninguna
    int seleccionY = -1; // Fila seleccionada, -1 si ninguna
    //int filas;
    //int columnas;
    int turno; // 0 = blanco, 1 = negro
    Rey* reyBlanco;
    Rey* reyNegro;
   
    //void renderizarTexto(const std::string& texto, float x, float y, void* fuente);

public:
    Tablero();
    //void mostrarMenuEnVentana(); //menú texto
    //void manejarEntradaMenu(unsigned char key, int x, int y); //menú switch
    //void mostrarInstruccionesEnVentana(); //instrucciones juego
    void iniciarPartida(int modoJuego); //correr el juego

 

    //void iniciarJuego(); //silverman
    //void iniciar2dojuego(); //demi
    //void cerrarAplicacion();
    //void mostrarPausa();
   
    void dibuja();
    void dibuja2();
    void inicializaSilverman();
    void inicializaDemi();

    Pieza* obtenerPieza(int columna, int fila) const;
    void colocarPieza(Pieza* pieza, int nuevaColumna, int nuevaFila);
    void anadirPieza(Pieza* pieza);  // Para inicializar el tablero

    void setSeleccion(int x, int y) { seleccionX = x; seleccionY = y; }
    void limpiarSeleccion() { seleccionX = -1; seleccionY = -1; }

    int getSeleccionX() const { return seleccionX; }
    int getSeleccionY() const { return seleccionY; }

    int getTurno() const { return turno; }
    void reiniciarTurno() { turno = 0; }  // Comenzar con blanco

    void reiniciarTablero();


    std::vector<Pieza*>& getPiezas() { return piezas; }
    
};

#endif // TABLERO_H

