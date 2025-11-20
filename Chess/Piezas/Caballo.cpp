#include "Caballo.h"
#include <cmath>
#include <iostream>

#include "Casilla.h"



bool Caballo::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    if (origen.getPieza() == nullptr) return false;


    if (destino.getPieza() != nullptr) {
        if (destino.getPieza()->getColor() == origen.getPieza()->getColor()) {
            return false;
        }
    }


    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());


    if ((difFila == 2 && difCol == 1) || (difFila == 1 && difCol == 2)) {
        return true;
    }

    return false;
}