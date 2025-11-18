// Alfil.h
#ifndef OACPROYECTO_ALFIL_H
#define OACPROYECTO_ALFIL_H

#include "Pieza.h"
#include "Casilla.h"
#include <cmath>


class Alfil : public Pieza {
public:
    Alfil(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::ALFIL, colorJugador, fila, columna) {}

    bool movimientoValido(Casilla origen, Casilla destino) const override;
};

#endif
