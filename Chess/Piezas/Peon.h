#ifndef OACPROYECTO_PEON_H
#define OACPROYECTO_PEON_H

#include "Pieza.h"
#include <vector>

class Peon : public Pieza {
private:
    bool alPaso;
    bool llegoAlFinal;
    bool esPrimerMovimiento = true;
public:
    Peon(Color colorJugador, int fila, int columna)
        : Pieza(TipoPieza::PEON, colorJugador, fila, columna),
        alPaso(false), llegoAlFinal(false) {
    }

    bool movimientoValido(Casilla origen, Casilla destino, Tablero* tablero);
    bool getAlPaso() const { return alPaso; }
    void setAlPaso(bool valor) { alPaso = valor; }

    bool getLlegoAlFinal() const { return llegoAlFinal; }
    void setLlegoAlFinal(bool valor) { llegoAlFinal = valor; }

};


#endif