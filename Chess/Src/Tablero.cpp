#ifndef OACPROYECTO_TABLERO_H
#define OACPROYECTO_TABLERO_H

#include <array>
#include <memory>
#include <iostream>

#include "../Piezas/Pieza.h"
#include "../Piezas/Peon.h"
#include "../Piezas/Torre.h"
#include "../Piezas/Caballo.h"
#include "../Piezas/Alfil.h"
#include "../Piezas/Reina.h"
#include "../Piezas/Rey.h"

class Tablero {
private:
    std::array<std::array<std::shared_ptr<Pieza>, 8>, 8> tablero;

public:
    Tablero() {
        limpiar();
        inicializar();
    }

    void inicializar() {
        //Poner piezas en el tablero

        //peon blanco en fila 6
        for(int columna = 0; columna < 8; columna++) {
            establecerPiezaEn(Posicion(6,columna),
                 std::make_shared<Peon>(Color::BLANCO, Posicion(6, columna)));
        }

        //peon negro en fila 1
        for(int columna = 0; columna < 8; columna++){
            establecerPiezaEn(Posicion(1,columna),
            std::make_shared<Peon>(Color::NEGRO, Posicion(1,columna)));
        }

        //Piezas blancas
        establecerPiezaEn(Posicion(7, 0), std::make_shared<Torre>(Color::BLANCO, Posicion(7, 0)));
        establecerPiezaEn(Posicion(7, 1), std::make_shared<Caballo>(Color::BLANCO, Posicion(7, 1)));
        establecerPiezaEn(Posicion(7, 2), std::make_shared<Alfil>(Color::BLANCO, Posicion(7, 2)));
        establecerPiezaEn(Posicion(7, 3), std::make_shared<Reina>(Color::BLANCO, Posicion(7, 3)));
        establecerPiezaEn(Posicion(7, 4), std::make_shared<Rey>(Color::BLANCO, Posicion(7, 4)));
        establecerPiezaEn(Posicion(7, 5), std::make_shared<Alfil>(Color::BLANCO, Posicion(7, 5)));
        establecerPiezaEn(Posicion(7, 6), std::make_shared<Caballo>(Color::BLANCO, Posicion(7, 6)));
        establecerPiezaEn(Posicion(7, 7), std::make_shared<Torre>(Color::BLANCO, Posicion(7, 7)));

        //Piezas negras
        establecerPiezaEn(Posicion(0, 0), std::make_shared<Torre>(Color::NEGRO, Posicion(0, 0)));
        establecerPiezaEn(Posicion(0, 1), std::make_shared<Caballo>(Color::NEGRO, Posicion(0, 1)));
        establecerPiezaEn(Posicion(0, 2), std::make_shared<Alfil>(Color::NEGRO, Posicion(0, 2)));
        establecerPiezaEn(Posicion(0, 3), std::make_shared<Reina>(Color::NEGRO, Posicion(0, 3)));
        establecerPiezaEn(Posicion(0, 4), std::make_shared<Rey>(Color::NEGRO, Posicion(0, 4)));
        establecerPiezaEn(Posicion(0, 5), std::make_shared<Alfil>(Color::NEGRO, Posicion(0, 5)));
        establecerPiezaEn(Posicion(0, 6), std::make_shared<Caballo>(Color::NEGRO, Posicion(0, 6)));
        establecerPiezaEn(Posicion(0, 7), std::make_shared<Torre>(Color::NEGRO, Posicion(0, 7)));
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
