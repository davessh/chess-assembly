#include "Pieza.h"

// Constructor de Pieza
Pieza::Pieza(TipoPieza tipo, Color colorJugador, int fila, int columna, bool puedeJugarse, bool seHaMovido)
    : tipo(tipo), color(colorJugador), fila(fila), columna(columna), 
      puedeJugarse(puedeJugarse), seHaMovido(seHaMovido) {
}