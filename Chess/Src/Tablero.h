#ifndef OACPROYECTO_TABLERO_H
#define OACPROYECTO_TABLERO_H


#include "../Piezas/Pieza.h"
#include "../Piezas/Casilla.h"

class Tablero {
private:
    Casilla* peonPasoDos = nullptr;
    Casilla* tablero[8][8];

public:
    Tablero();

 void inicializar() const;
    void mostrarTablero();

    void setCasilla(int fila, int columna, Pieza* pieza);

    Casilla* getCasilla(int fila, int columna) const;


    Casilla* buscarRey(Color turno) const;

    Casilla* getPeonPasoDos (){return peonPasoDos;}

    void setPeonPasoDos(Casilla* casilla){peonPasoDos = casilla;}
};


#endif
