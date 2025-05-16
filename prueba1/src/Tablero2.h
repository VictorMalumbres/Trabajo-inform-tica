#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>
#include "Pieza.h"
#include "Torre.h"
#include "Reina.h"
#include "Rey.h"
#include "Peon.h"

class Tablero2 {
private:
    std::vector<Pieza*> piezas;

    void renderizarTexto(const std::string& texto, float x, float y, void* fuente);

public:
    Tablero2();
    void mostrarMenuEnVentana();
    void manejarEntradaMenu(unsigned char key, int x, int y);
    void mostrarInstruccionesEnVentana();
    void iniciarPartida();
    void iniciarJuego();
    void cerrarAplicacion();
    void inicializa();
    void dibuja();
};

#endif // TABLERO_H

