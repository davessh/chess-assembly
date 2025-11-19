#include "Caballo.h"
#include <cmath>
#include <iostream>

#include "Casilla.h"

// No necesitas incluir "Pieza.h" y "Casilla.h" si ya están en Caballo.h,
// pero si los necesitas, déjalos.

bool Caballo::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    // 1. Verificar que hay alguien moviendo
    if (origen.getPieza() == nullptr) return false;

    // 2. Verificar que no nos comamos a nosotros mismos (Fuego amigo)
    // Si hay pieza en destino Y es de mi mismo color -> Movimiento inválido
    if (destino.getPieza() != nullptr) {
        if (destino.getPieza()->getColor() == origen.getPieza()->getColor()) {
            return false;
        }
    }

    // 3. Calcular geometría del movimiento (La "L")
    // El caballo se mueve si:
    // (dx es 2 y dy es 1) O (dx es 1 y dy es 2)
    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());

    // std::cout << "Fila: " << difFila << " Col: " << difCol << std::endl; // Debug

    if ((difFila == 2 && difCol == 1) || (difFila == 1 && difCol == 2)) {
        return true;
    }

    return false;
}