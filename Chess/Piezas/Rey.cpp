// Rey.cpp
#include "Rey.h"
#include "Casilla.h"

bool Rey::movimientoValido(Casilla origen, Casilla destino) const {
    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());
    if (sonIguales) return false;

    // El rey se mueve una casilla en cualquier dirección
    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());

    return (difFila <= 1 && difCol <= 1);
}