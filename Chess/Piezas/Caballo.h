#ifndef OACPROYECTO_CABALLO_H
#define OACPROYECTO_CABALLO_H

#include "Pieza.h"

class Caballo : public Pieza {
public:
    Caballo(Color c, Posicion pos) : Pieza(TipoPieza::CABALLO, c, pos) {}
    
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
        return color == Color::BLANCO ? 'C' : 'c';
    }
};

#endif