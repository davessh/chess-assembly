#ifndef OACPROYECTO_ALFIL_H
#define OACPROYECTO_ALFIL_H

#include "Pieza.h"

class Alfil : public Pieza {
public:
    Alfil(Color c, Posicion pos) : Pieza(TipoPieza::ALFIL, c, pos) {}
    
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
        return color == Color::BLANCO ? 'A' : 'a';
    }
};

#endif