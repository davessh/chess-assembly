// Rey.cpp
#include "Rey.h"
#include "Casilla.h"

bool Rey::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    if (origen.getPieza() == nullptr) return false;

    if (destino.getPieza() != nullptr) {
        if (destino.getPieza()->getColor() == origen.getPieza()->getColor()) {
            return false;
        }
    }

    int difFila = std::abs(destino.getFila() - origen.getFila());
    int difCol = std::abs(destino.getColumna() - origen.getColumna());

    if (difFila <= 1 && difCol <= 1) {
        return true;
    }

    // LOGICA DE ENROQUE (OPCIONAL - Comenta esto si no lo usas aún o si causa el crash)
    /*
    if (!this->seHaMovido && difFila == 0 && difCol == 2) {
        // Verificar lógica de enroque aquí con cuidado de punteros nulos
        // ...
    }
    */

    return false;
}