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
    int filas;
    int columnas;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente);

public:
    Tablero();
    void mostrarMenuEnVentana();
    void manejarEntradaMenu(unsigned char key, int x, int y);
    void mostrarInstruccionesEnVentana();
    void iniciarPartida(int modoJuego);

    void iniciarJuego();
    void iniciar2dojuego();
    void cerrarAplicacion();
   
    void dibuja();
    void dibuja2();
    void inicializaSilverman();
    void inicializaDemi();

};

#endif // TABLERO_H

