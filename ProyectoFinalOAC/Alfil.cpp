#include "Alfil.h"
#include "Casilla.h"
#include "Tablero.h"

bool Alfil::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = false;
    int filaOri = origen.getFila();
    int filaDes = destino.getFila();
    int colOri = origen.getColumna();
    int colDes = destino.getColumna();


    __asm {
        mov eax, filaOri
        cmp eax, filaDes
        jne no_iguales

        mov eax, colOri
        cmp eax, colDes
        jne no_iguales

        mov sonIguales, 1
        jmp fin_cmp

        no_iguales :
        mov sonIguales, 0

            fin_cmp :
    }

    if (sonIguales) return false;


    if (destino.getPieza() != nullptr) {
        if (origen.getPieza()->getColor() == destino.getPieza()->getColor()) {
            return false;
        }
    }

    int filaTemp = filaDes - filaOri;
    int colTemp = colDes - colOri;
    int difFila = 0, difCol = 0;

    __asm {
        mov eax, filaTemp
        cmp eax, 0
        jge abs_fila
        neg eax
        abs_fila :
        mov difFila, eax
    }

    __asm {
        mov eax, colTemp
        cmp eax, 0
        jge abs_col
        neg eax
        abs_col :
        mov difCol, eax
    }


    bool movimientoDiagonal = false;

    __asm {
        mov eax, difFila
        cmp eax, 0
        jle no_diag

        mov ebx, difCol
        cmp eax, ebx
        jne no_diag

        mov movimientoDiagonal, 1
        jmp fin_diag

        no_diag :
        mov movimientoDiagonal, 0

            fin_diag :
    }

    if (!movimientoDiagonal) return false;


    int pasoFila = 0;
    __asm {
        mov eax, filaDes
        sub eax, filaOri
        cmp eax, 0
        jg posF
        jl negF
        mov pasoFila, 0
        jmp finF

        posF :
        mov pasoFila, 1
            jmp finF

            negF :
        mov pasoFila, -1

            finF :
    }


    int pasoCol = 0;
    __asm {
        mov eax, colDes
        sub eax, colOri
        cmp eax, 0
        jg posC
        jl negC
        mov pasoCol, 0
        jmp finC

        posC :
        mov pasoCol, 1
            jmp finC

            negC :
        mov pasoCol, -1

            finC :
    }


    int filaActual = filaOri + pasoFila;
    int colActual = colOri + pasoCol;

    while (true)
    {
        int filaD = filaDes;
        int colD = colDes;
        int salir = 0;

        __asm {
            mov eax, filaActual
            cmp eax, filaD
            jne cont_loop

            mov eax, colActual
            cmp eax, colD
            jne cont_loop

            mov salir, 1

            cont_loop:
        }


        if (salir == 1) break;


        if (tablero->getCasilla(filaActual, colActual)->getPieza() != nullptr)
            return false;


        __asm {
            mov eax, filaActual
            add eax, pasoFila
            mov filaActual, eax

            mov eax, colActual
            add eax, pasoCol
            mov colActual, eax
        }
    }

    return true;
}