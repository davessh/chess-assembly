// Reina.cpp
#include "Reina.h"

Reina::Reina(Color c, Posicion pos) : Pieza(TipoPieza::REINA, c, pos) {}

std::vector<Posicion> Reina::obtenerMovimientosPosibles(const Tablero& tablero) const {
    std::vector<Posicion> movimientos;
    // Aquí iría la lógica real para calcular los movimientos de la reina
    return movimientos;
}

bool Reina::esMovimientoValido(const Posicion& destino, const Tablero& tablero) const {
    // Aquí iría la lógica de validación de movimiento
    return false;
}

char Reina::obtenerSimbolo() const {
    return color == Color::BLANCO ? 'D' : 'd';
}
