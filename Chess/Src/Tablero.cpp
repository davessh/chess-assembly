#include "Tablero.h"
#include "../Piezas/Torre.h"
#include "../Piezas/Caballo.h"
#include "../Piezas/Alfil.h"
#include "../Piezas/Reina.h"
#include "../Piezas/Rey.h"
#include "../Piezas/Peon.h"

Tablero::Tablero()
{
    // Inicializar todas las casillas vacías (sin piezas)
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j] = new Casilla(i, j, nullptr);
        }
    }
}

void Tablero::inicializar() {
    // Limpiar el tablero primero
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j]->setPieza(nullptr);
        }
    }

    // Colocar piezas negras (fila 0 y 1)
    tablero[0][0]->setPieza(new Torre(Color::NEGRO, 0, 0));
    tablero[0][1]->setPieza(new Caballo(Color::NEGRO, 0, 1));
    tablero[0][2]->setPieza(new Alfil(Color::NEGRO, 0, 2));
    tablero[0][3]->setPieza(new Reina(Color::NEGRO, 0, 3));
    tablero[0][4]->setPieza(new Rey(Color::NEGRO, 0, 4));
    tablero[0][5]->setPieza(new Alfil(Color::NEGRO, 0, 5));
    tablero[0][6]->setPieza(new Caballo(Color::NEGRO, 0, 6));
    tablero[0][7]->setPieza(new Torre(Color::NEGRO, 0, 7));

    // Peones negros
    for (int j = 0; j < 8; j++) {
        tablero[1][j]->setPieza(new Peon(Color::NEGRO, 1, j));
    }

    // Peones blancos
    for (int j = 0; j < 8; j++) {
        tablero[6][j]->setPieza(new Peon(Color::BLANCO, 6, j));
    }

    // Colocar piezas blancas (fila 7)
    tablero[7][0]->setPieza(new Torre(Color::BLANCO, 7, 0));
    tablero[7][1]->setPieza(new Caballo(Color::BLANCO, 7, 1));
    tablero[7][2]->setPieza(new Alfil(Color::BLANCO, 7, 2));
    tablero[7][3]->setPieza(new Reina(Color::BLANCO, 7, 3));
    tablero[7][4]->setPieza(new Rey(Color::BLANCO, 7, 4));
    tablero[7][5]->setPieza(new Alfil(Color::BLANCO, 7, 5));
    tablero[7][6]->setPieza(new Caballo(Color::BLANCO, 7, 6));
    tablero[7][7]->setPieza(new Torre(Color::BLANCO, 7, 7));
}