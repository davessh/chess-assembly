// Reina.h
#ifndef OACPROYECTO_REINA_H
#define OACPROYECTO_REINA_H

#include "Pieza.h"

class Reina : public Pieza {
public:
    Reina(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::REINA, colorJugador, fila, columna) {}

    bool movimientoValido(Casilla origen, Casilla destino) const override;
};

#endif