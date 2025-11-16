#ifndef OACPROYECTO_PEON_H
#define OACPROYECTO_PEON_H

#include "Pieza.h"

class Peon : public Pieza {
public:
    Peon(Color c, Posicion pos) : Pieza(TipoPieza::PEON, c, pos) {}

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
        return color == Color::BLANCO ? 'P' : 'p';
    }
};

#endif