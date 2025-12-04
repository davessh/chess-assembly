// Reina.cpp
#include "Reina.h"
#include "Casilla.h"

bool Reina::movimientoValido(Casilla origen, Casilla destino, Tablero * tablero) {
    if (origen.getPieza() == nullptr) return false;

    //bool sonIguales = (origen.getFila() == destino.getFila()) &&
       // (origen.getColumna() == destino.getColumna());
    //if (sonIguales) return false;
    bool sonIguales = false;
    int filaOri = origen.getFila();
    int filaDes = destino.getFila();
    int colOri = origen.getColumna();
    int colDes = destino.getColumna();
    __asm {
        mov eax, filaOri;
        cmp eax, filaDes;
        jne no_iguales;

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

    //int difFila = abs(destino.getFila() - origen.getFila());
    //int difCol = abs(destino.getColumna() - origen.getColumna());
    int difFila, difCol;
    int filaTemp = destino.getFila() - origen.getFila();
    int colaTemp = destino.getColumna() - origen.getColumna();
    __asm {
        mov eax, filaTemp
        cmp eax, 0
        jge sin_cambio
        neg eax
        sin_cambio :
        mov difFila, eax
    }
    __asm {
        mov eax, colaTemp
        cmp eax, 0
        jge sin_cambioC
        neg eax
        sin_cambioC :
        mov difCol, eax
    }


    //if (!(difFila == 0 || difCol == 0 || difFila == difCol)) {
      //  return false;
    //}

    bool movimientoValido = false;
    __asm {
        mov eax, difFila
        mov ebx, difCol
        cmp eax, 0
        je es_valido

        cmp ebx, 0
        je es_valido

        cmp eax, ebx
        je es_valido

        mov movimientoValido, 0
        jmp fin_validacion

        es_valido :
        mov movimientoValido, 1
            fin_validacion :
            nop
    }

    if (!movimientoValido) {
        return false;
    }

    int pasoFila = 0;
    //if (destino.getFila() > origen.getFila()) pasoFila = 1;
    //else if (destino.getFila() < origen.getFila()) pasoFila = -1;
    int destinoFila = destino.getFila();
    int origenFila = origen.getFila();
    __asm {
        mov eax, destinoFila
        sub eax, origenFila
        cmp eax, 0
        jg hacer_positivoF
        jl hacer_negativoF
        mov pasoFila, 0
        jmp finF

        hacer_positivoF :
        mov pasoFila, 1
            jmp finF

            hacer_negativoF :
        mov pasoFila, -1

            finF :
            nop

    }

    int pasoCol = 0;
    //if (destino.getColumna() > origen.getColumna()) pasoCol = 1;
    //else if (destino.getColumna() < origen.getColumna()) pasoCol = -1;
    int destinoCol = destino.getColumna();
    int origenCol = origen.getColumna();
    __asm {
        mov eax, destinoCol
        sub eax, origenCol
        cmp eax, 0
        jg hacer_positivoC
        jl hacer_negativoC
        mov pasoCol, 0
        jmp finC

        hacer_positivoC :
        mov pasoCol, 1
            jmp finC

            hacer_negativoC :
        mov pasoCol, -1

            finC :
            nop
    }

    int filaActual = origen.getFila() + pasoFila;
    int colActual = origen.getColumna() + pasoCol;

    //while (filaActual != destino.getFila() || colActual != destino.getColumna())
    while (true)
    {
        int filaD = destino.getFila();
        int colD = destino.getColumna();
        int salir = 0;

        __asm {
            mov eax, filaActual
            cmp eax, filaD
            jne continuar

            mov eax, colActual
            cmp eax, colD
            jne continuar

            mov salir, 1
            continuar:
        }

        if (salir == 1) {
            break;
        }


        if (tablero->getCasilla(filaActual, colActual)->getPieza() != nullptr) {
            return false;
        }
        //filaActual += pasoFila;
        //colActual += pasoCol;
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