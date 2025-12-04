#include <iostream>
#include "Tablero.h"
#include "../Piezas/Torre.h"
#include "../Piezas/Caballo.h"
#include "../Piezas/Alfil.h"
#include "../Piezas/Reina.h"
#include "../Piezas/Rey.h"
#include "../Piezas/Peon.h"

Tablero::Tablero()
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tablero[i][j] = new Casilla(i, j, nullptr);
        }
    }
}

void Tablero::inicializar() const{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pieza* p = tablero[i][j]->getPieza();
            if (p != nullptr) {

                tablero[i][j]->setPieza(nullptr);
            }
        }
    }

    tablero[0][0]->setPieza(new Torre(Color::NEGRO, 0, 0));
    tablero[0][1]->setPieza(new Caballo(Color::NEGRO, 0, 1));
    tablero[0][2]->setPieza(new Alfil(Color::NEGRO, 0, 2));
    tablero[0][3]->setPieza(new Reina(Color::NEGRO, 0, 3));
    tablero[0][4]->setPieza(new Rey(Color::NEGRO, 0, 4));
    tablero[0][5]->setPieza(new Alfil(Color::NEGRO, 0, 5));
    tablero[0][6]->setPieza(new Caballo(Color::NEGRO, 0, 6));
    tablero[0][7]->setPieza(new Torre(Color::NEGRO, 0, 7));

    for (int j = 0; j < 8; j++) {
        tablero[1][j]->setPieza(new Peon(Color::NEGRO, 1, j));
    }

    for (int j = 0; j < 8; j++) {
        tablero[6][j]->setPieza(new Peon(Color::BLANCO, 6, j));
    }

    tablero[7][0]->setPieza(new Torre(Color::BLANCO, 7, 0));
    tablero[7][1]->setPieza(new Caballo(Color::BLANCO, 7, 1));
    tablero[7][2]->setPieza(new Alfil(Color::BLANCO, 7, 2));
    tablero[7][3]->setPieza(new Reina(Color::BLANCO, 7, 3));
    tablero[7][4]->setPieza(new Rey(Color::BLANCO, 7, 4));
    tablero[7][5]->setPieza(new Alfil(Color::BLANCO, 7, 5));
    tablero[7][6]->setPieza(new Caballo(Color::BLANCO, 7, 6));
    tablero[7][7]->setPieza(new Torre(Color::BLANCO, 7, 7));
}
void Tablero::setCasilla(int fila, int columna, Pieza* pieza)
{
    tablero[fila][columna]->setPieza(pieza);

    if (pieza != nullptr) {
        pieza->setFila(fila);
        pieza->setColumna(columna);
    }
}


void Tablero::mostrarTablero()
{
    std::cout << "\n   a b c d e f g h\n";
    std::cout << "  -----------------\n";

    for (int fila = 7; fila >= 0; --fila) {
        std::cout << (fila + 1) << " |";
        for (int col = 0; col < 8; ++col) {
            Casilla* casilla = tablero[fila][col];
            Pieza* pieza = casilla->getPieza();

            char simbolo = '.';

            if (pieza != nullptr) {
                switch (pieza->getTipo()) {
                    case TipoPieza::PEON:    simbolo = 'P'; break;
                    case TipoPieza::TORRE:   simbolo = 'R'; break; 
                    case TipoPieza::CABALLO: simbolo = 'N'; break; 
                    case TipoPieza::ALFIL:   simbolo = 'B'; break; 
                    case TipoPieza::REINA:   simbolo = 'Q'; break;
                    case TipoPieza::REY:     simbolo = 'K'; break;
                }

                if (pieza->getColor() == Color::NEGRO) {
                    simbolo = static_cast<char>(std::tolower(simbolo));
                }
            }

            std::cout << simbolo << ' ';
        }
        std::cout << "|" << (fila + 1) << '\n';
    }

    std::cout << "  -----------------\n";
    std::cout << "   a b c d e f g h\n\n";
}

Casilla* Tablero::getCasilla(int fila, int columna) const
{
    return tablero[fila][columna];
}


Casilla* Tablero::buscarRey(Color actual) const
{
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pieza* pieza = tablero[i][j]->getPieza();

            if (pieza != nullptr &&
                pieza->getTipo() == TipoPieza::REY &&
                pieza->getColor() == actual) {
                return tablero[i][j];
                }
        }
    }
    return nullptr;
}