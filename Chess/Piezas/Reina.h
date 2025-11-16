#ifndef OACPROYECTO_REINA_H
#define OACPROYECTO_REINA_H

#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(Color c, Posicion pos) : Pieza(TipoPieza::REINA, c, pos) {}

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
        return color == Color::BLANCO ? 'D' : 'd';
    }
};

#endif//OACPROYECTO_REINA_H