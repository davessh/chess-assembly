#ifndef OACPROYECTO_TORRE_H
#define OACPROYECTO_TORRE_H

#include "Pieza.h"

class Torre : public Pieza {
public:
    Torre(Color c, Posicion pos) : Pieza(TipoPieza::TORRE, c, pos) {}
    
    std::vector<Posicion> obtenerMovimientosPosibles(const Tablero& tablero) const override {
        std::vector<Posicion> movimientos;
        // Implementar lógica
        return movimientos;
    }
    
    bool esMovimientoValido(const Posicion& destino, const Tablero& tablero) const override {
        // Implementar lógica
        return false;
    }
    
    char obtenerSimbolo() const override {
        return color == Color::BLANCO ? 'T' : 't';
    }
};

#endif