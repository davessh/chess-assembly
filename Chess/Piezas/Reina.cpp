// Reina.cpp
#include "Reina.h"
#include "Casilla.h"

    bool Reina::movimientoValido(Casilla origen, Casilla destino, Tablero& tablero) {
    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());
    if (sonIguales) return false;

    // La reina se mueve como torre o alfil
    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());

    return (difFila == 0 || difCol == 0 || difFila == difCol);
}