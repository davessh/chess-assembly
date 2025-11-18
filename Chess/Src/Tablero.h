#ifndef OACPROYECTO_TABLERO_H
#define OACPROYECTO_TABLERO_H


#include "../Piezas/Pieza.h"
#include "../Piezas/Casilla.h"

class Tablero {
private:

    Casilla* tablero[8][8];

public:
    Tablero();

 void inicializar() const;
    void mostrarTablero();

    Casilla* getCasilla(int fila, int columna) const;


};


#endif
