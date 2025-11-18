#ifndef OACPROYECTO_REY_H
#define OACPROYECTO_REY_H

#include "Pieza.h"
#include <vector>

class Rey : public Pieza {
public:
    Rey(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::REY, colorJugador, fila, columna) {}

    bool movimientoValido(Casilla origen, Casilla destino) const override;
};

#endif
