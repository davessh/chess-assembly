// Torre.hpp
#ifndef TORRE_HPP
#define TORRE_HPP

#include "Pieza.h"
#include <vector>

class Torre : public Pieza {

public:
    Torre(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::TORRE, colorJugador, fila, columna) {}
};

#endif // TORRE_HPP
