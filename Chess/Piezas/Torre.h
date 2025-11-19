// Torre.hpp
#ifndef OACPROYECTO_TORRE_H
#define OACPROYECTO_TORRE_H

#include "Pieza.h"
#include "../Src/Tablero.h"

class Torre : public Pieza {

public:
    Torre(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::TORRE, colorJugador, fila, columna) {}

    bool movimientoValido(Casilla origen, Casilla destino, Tablero* tablero);
};

#endif // TORRE_HPP
