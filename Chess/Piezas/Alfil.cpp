#include "Alfil.h"

    bool Alfil::movimientoValido(Casilla origen, Casilla destino, Tablero& tablero) {
    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());
    if (sonIguales) return false;

    // El alfil se mueve en diagonal
    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());

    return difFila == difCol && difFila > 0;
};

