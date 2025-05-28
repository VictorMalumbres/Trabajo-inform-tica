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

class Mundo;
class Tablero {
private:
    std::vector<Pieza*> piezas;
    int seleccionX = -1; // Columna seleccionada, -1 si ninguna
    int seleccionY = -1; // Fila seleccionada, -1 si ninguna
    int numFilas;
    int numColumnas;
    int turno; // 0 = blanco, 1 = negro
    Rey* reyBlanco;
    Rey* reyNegro;

    int ultimoPeonDobleX = -1;  // columna del peón que avanzó dos casillas
    int ultimoPeonDobleY = -1;  // fila intermedia (no la final)
    int turnoPeonDoble = -1;    // qué bando movió ese peón (0 o 1)

    int contadorMovimiento = 0;  //Contar movimientos realizados sin comer piezas (para las tablas)

public:
    Tablero();

    void iniciarPartida(int modoJuego); //correr el juego

    int getNumFilas() const;
    int getNumColumnas() const;

    void cambiarTurno() { turno = 1 - turno; }

    void dibuja();
    void dibuja2();
    void inicializaSilverman();
    void inicializaDemi();

    Pieza* obtenerPieza(int columna, int fila) const;
    void colocarPieza(Pieza* pieza, int nuevaColumna, int nuevaFila, bool simular = false); //simular para evitar overflow en tablas
    void anadirPieza(Pieza* pieza);  // Para inicializar el tablero

    int getSeleccionX() const { return seleccionX; }
    int getSeleccionY() const { return seleccionY; }

    int getTurno() const { return turno; }
    void reiniciarTurno() { turno = 0; }  // Comenzar con blanco

    void reiniciarTablero();

    std::vector<Pieza*>& getPiezas() { return piezas; }

    void setSeleccion(int x, int y);

    void limpiarSeleccion();
    
    std::vector<std::pair<int, int>> casillasResaltadas;

    Mundo* mundo;
    void setMundo(Mundo* m) { mundo = m; }

    bool esCapturaAlPaso(int col, int fila, int bando) const;

    bool estaEnJaque(int bando) const;
    void actualizarEstadoJaque();

    std::vector<std::pair<int, int>> casillasEnJaque;

    Tablero* clonar() const;

    Rey* getRey(int bando) const {
        return (bando == 0) ? reyBlanco : reyNegro;
    }

    bool esStalemate(int bando);  //Rey ahogado
    bool materialInsuficiente() const;  //Material insuficiente (Rey o Rey+Alfil o Rey+Caballo)

};
#endif // TABLERO_H

