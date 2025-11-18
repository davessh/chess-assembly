// Peon.cpp
#include "Peon.h"
#include "Casilla.h"

bool Peon::movimientoValido(Casilla origen, Casilla destino) const {
    // Implementación básica del movimiento del peón
    if (origen.getPieza() == nullptr) return false;
    
    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());
    if (sonIguales) return false;
    
    // Implementación simplificada - puedes expandirla
    return true;
}