#pragma once
#include <string>
#include <vector>

using namespace std;

struct Partida {
    string fechaHora;
    string modoJuego;
    string ganador;
    string oponente;
    int movimientos;
};

class Historial {
private:
    vector<Partida> ultimas5;

public:
    void agregarPartida(const string& fechaHora,
        const string& modoJuego,
        const string& ganador,
        const string& oponente,
        int movimientos);

    bool estaVacio() const;
    int getCantidad() const;
    Partida getPartida(int i) const;
};
