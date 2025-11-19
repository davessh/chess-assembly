#ifndef OACPROYECTO_PEON_H
#define OACPROYECTO_PEON_H

#include "Pieza.h"
#include <vector>

class Peon : public Pieza {
private:
    bool alPaso;
    bool llegoAlFinal;
public:
    Peon(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::PEON, colorJugador, fila, columna),
          alPaso(false), llegoAlFinal(false) {}

    bool movimientoValido(Casilla origen, Casilla destino, Tablero* tablero);

};


#endif
