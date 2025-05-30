#include "Historial.h"

void Historial::agregarPartida(const string& fechaHora,
    const string& modoJuego,
    const string& ganador,
    const string& oponente,
    int movimientos)
{
    if (ultimas5.size() == 5) {
        ultimas5.erase(ultimas5.begin());
    }

    Partida nueva{ fechaHora, modoJuego, ganador, oponente, movimientos };
    ultimas5.push_back(nueva);
}

bool Historial::estaVacio() const {
    return ultimas5.empty();
}

int Historial::getCantidad() const {
    return (int)ultimas5.size();
}

Partida Historial::getPartida(int i) const {
    return ultimas5[i];
}
