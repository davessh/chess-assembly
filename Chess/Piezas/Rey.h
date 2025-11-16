#ifndef OACPROYECTO_REY_H
#define OACPROYECTO_REY_H

#include "Pieza.h"

class Rey : public Pieza {
public:
    Rey(Color c, Posicion pos) : Pieza(TipoPieza::REY, c, pos) {}
    
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
        return color == Color::BLANCO ? 'R' : 'r';
    }
    
    bool puedeEnrocar(const Tablero& tablero, bool ladoRey) const {
        // Implementar lógica para enroque
        return false;
    }
};

#endif