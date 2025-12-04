#ifndef OACPROYECTO_CABALLO_H
#define OACPROYECTO_CABALLO_H

#include "Pieza.h"
#include <vector>

class Caballo : public Pieza {
public:
    Caballo(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::CABALLO, colorJugador, fila, columna) {
    }

    bool movimientoValido(Casilla origen, Casilla destino, Tablero* tablero);


};

#endif
