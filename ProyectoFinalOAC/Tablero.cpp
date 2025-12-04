#include <iostream>
#include "Tablero.h"
#include "Torre.h"
#include <iostream>
#include "Tablero.h"
#include "Torre.h"
#include "Caballo.h"
#include "Alfil.h"
#include "Reina.h"
#include "Rey.h"
#include "Peon.h"

Tablero::Tablero()


{
    int i = 0;
    int j = 0;

    __asm {
        mov i, 0; i = 0

        for_i:
        mov eax, i
            cmp eax, 8
            jge finConstructor;

        mov j, 0; j = 0

            for_j:
        mov ebx, j
            cmp ebx, 8
            jge sig_i;
    }

    tablero[i][j] = new Casilla(i, j, nullptr);
    __asm {
        inc j
        jmp for_j
    }
    __asm {
    sig_i:
        inc i
            jmp for_i
    }

    __asm {
    finConstructor:
        nop
    }

}

void Tablero::inicializar() const {
    //for (int i = 0; i < 8; i++) {
       // for (int j = 0; j < 8; j++) {
           // Pieza* p = tablero[i][j]->getPieza();
           // if (p != nullptr) {

              //  tablero[i][j]->setPieza(nullptr);
           // }
       // }
   // }

    //tablero[0][0]->setPieza(new Torre(Color::NEGRO, 0, 0));
    //tablero[0][1]->setPieza(new Caballo(Color::NEGRO, 0, 1));
    //tablero[0][2]->setPieza(new Alfil(Color::NEGRO, 0, 2));
   // tablero[0][3]->setPieza(new Reina(Color::NEGRO, 0, 3));
   // tablero[0][4]->setPieza(new Rey(Color::NEGRO, 0, 4));
   // tablero[0][5]->setPieza(new Alfil(Color::NEGRO, 0, 5));
    //tablero[0][6]->setPieza(new Caballo(Color::NEGRO, 0, 6));
    //tablero[0][7]->setPieza(new Torre(Color::NEGRO, 0, 7));

   // for (int j = 0; j < 8; j++) {
       // tablero[1][j]->setPieza(new Peon(Color::NEGRO, 1, j));
   // }

    //for (int j = 0; j < 8; j++) {
       // tablero[6][j]->setPieza(new Peon(Color::BLANCO, 6, j));
   // }

   // tablero[7][0]->setPieza(new Torre(Color::BLANCO, 7, 0));
    //tablero[7][1]->setPieza(new Caballo(Color::BLANCO, 7, 1));
   // tablero[7][2]->setPieza(new Alfil(Color::BLANCO, 7, 2));
   // tablero[7][3]->setPieza(new Reina(Color::BLANCO, 7, 3));
    //tablero[7][4]->setPieza(new Rey(Color::BLANCO, 7, 4));
   // tablero[7][5]->setPieza(new Alfil(Color::BLANCO, 7, 5));
   // tablero[7][6]->setPieza(new Caballo(Color::BLANCO, 7, 6));
   // tablero[7][7]->setPieza(new Torre(Color::BLANCO, 7, 7));

    int i = 0;
    int j = 0;


    __asm {
        mov i, 0; i = 0

        inicio_for_i:
        mov eax, i
            cmp eax, 8
            jge fin_for
            mov j, 0; j = 0

            inicio_for_j:
        mov ebx, j
            cmp ebx, 8
            jge siguiente_i

    }

    {
        Pieza* p = tablero[i][j]->getPieza();
        if (p != nullptr) {
            tablero[i][j]->setPieza(nullptr);
        }
    }

    __asm {
        inc j; j++
        jmp inicio_for_j

        siguiente_i :
        inc i; i++
            jmp inicio_for_i

            fin_for :
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