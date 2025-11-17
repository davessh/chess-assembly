#ifndef OACPROYECTO_CASILLA_H
#define OACPROYECTO_CASILLA_H
#include "Pieza.h"

class Casilla
{
private:
    int fila;
    int columna;
    Pieza* pieza;
public:

    Casilla(int fila, int columna, Pieza* pieza)
    {
        this->fila = fila;
        this->columna = columna;
        this->pieza = pieza;
    };

    void setFila(int fila){ this->fila = fila;};
    void setColumna(int columna);
    void setPieza(Pieza* pieza);
    int getFila();
    int getColumna();
    Pieza* getPieza();

};
#endif //OACPROYECTO_CASILLA_H