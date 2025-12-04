#include "Caballo.h"
#include <cmath>
#include <iostream>
#include "Tablero.h"

#include "Casilla.h"

bool Caballo::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    Pieza* piezaOrigen = origen.getPieza();
    Pieza* piezaDestino = destino.getPieza();

    __asm {
        cmp piezaOrigen, 0
        jne continua
        falso :
    }
    return false;
    __asm {
    continua:
        cmp piezaDestino, 0
            je sigue
    }
    Color colorOrigen = piezaOrigen->getColor();
    Color colorDestino = piezaDestino->getColor();
    __asm {
        mov esi, piezaDestino
        mov edi, piezaOrigen
        mov eax, colorOrigen;
        mov ebx, colorDestino;
        cmp eax, ebx
            je falso
            sigue :
    }


    int filaOrigen = origen.getFila();
    int filaDestino = destino.getFila();
    int columnaOrigen = origen.getColumna();
    int columnaDestino = destino.getColumna();
    unsigned char esValido = 0;

    __asm {
        mov eax, filaDestino
        sub eax, filaOrigen
        cdq
        xor eax, edx
        sub eax, edx
        mov ebx, eax

        mov eax, columnaDestino
        sub eax, columnaOrigen
        cdq
        xor eax, edx
        sub eax, edx
        mov ecx, eax

        cmp ebx, 2
        jne prueba
        cmp ecx, 1
        je valido
        jmp invalido

        prueba :
        cmp ebx, 1
            jne invalido
            cmp ecx, 2
            je valido

            invalido :
        mov byte ptr[esValido], 0
            jmp fin

            valido :
        mov byte ptr[esValido], 1

            fin :
            nop
    }
    return esValido;
}


