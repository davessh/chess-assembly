#ifndef OACPROYECTO_TABLERO_H
#define OACPROYECTO_TABLERO_H

#include <array>
#include <memory>
#include <iostream>

#include "../Piezas/Pieza.h"

class Tablero {
private:
    std::array<std::array<std::shared_ptr<Pieza>, 8>, 8> tablero;

public:
    Tablero() {
        limpiar();
    }

    void inicializar() {
        // Implementar inicialización del tablero con las piezas
    }

    void limpiar() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                tablero[i][j] = nullptr;
            }
        }
    }

    std::shared_ptr<Pieza> obtenerPiezaEn(const Posicion& pos) const {
        if (!esPosicionValida(pos)) return nullptr;
        return tablero[pos.fila][pos.columna];
    }

    void establecerPiezaEn(const Posicion& pos, std::shared_ptr<Pieza> pieza) {
        if (esPosicionValida(pos)) {
            tablero[pos.fila][pos.columna] = pieza;
        }
    }

    void eliminarPiezaEn(const Posicion& pos) {
        if (esPosicionValida(pos)) {
            tablero[pos.fila][pos.columna] = nullptr;
        }
    }

    bool esPosicionValida(const Posicion& pos) const {
        return pos.fila >= 0 && pos.fila < 8 && pos.columna >= 0 && pos.columna < 8;
    }

    bool esPosicionVacia(const Posicion& pos) const {
        return esPosicionValida(pos) && tablero[pos.fila][pos.columna] == nullptr;
    }

    bool esPosicionOcupadaPorColor(const Posicion& pos, Color color) const {
        if (!esPosicionValida(pos) || esPosicionVacia(pos)) return false;
        return tablero[pos.fila][pos.columna]->obtenerColor() == color;
    }

    void mostrar() const {
        // Implementar visualización del tablero
    }
};

#endif
