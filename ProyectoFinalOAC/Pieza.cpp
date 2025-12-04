// Pieza.cpp
#include "Pieza.h"
#include "Casilla.h"
// (y los includes necesarios para Casilla y Tablero)

// Constructor
Pieza::Pieza(TipoPieza tipo, Color colorJugador, int fila, int columna,
    bool puedeJugarse, bool seHaMovido)
    : tipo(tipo),
    color(colorJugador),
    puedeJugarse(puedeJugarse),
    seHaMovido(seHaMovido),
    fila(fila),
    columna(columna)
{
}

// Implementación por defecto
bool Pieza::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    // Lógica genérica o simplemente:
    return false;
}