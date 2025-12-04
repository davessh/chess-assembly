#include "Casilla.h"

void Casilla::setColumna(int columna) {
    this->columna = columna;
}

void Casilla::setPieza(Pieza* pieza) {
    this->pieza = pieza;
}

int Casilla::getFila() {
    return this->fila;
}

int Casilla::getColumna() {
    return this->columna;
}

Pieza* Casilla::getPieza() {
    return this->pieza;
}