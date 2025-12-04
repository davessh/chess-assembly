#include "Torre.h"
#include <cmath>
#include "Casilla.h"
#include "Tablero.h"
bool Torre::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero) {
    if (origen.getPieza() == nullptr) return false;
    //bool sonIguales = (destino.getPieza() != nullptr &&
      //destino.getPieza()->getColor() == origen.getPieza()->getColor());
    int igualesInt = 0;
    Pieza* pOri = origen.getPieza();
    Pieza* pDes = destino.getPieza();
    __asm {
        mov eax, pDes
        test eax, eax
        je finIguales;
        mov ebx, pOri
            test ebx, ebx
            je finIguales;
        mov edx, [eax]Pieza.color;
        mov ecx, [ebx]Pieza.color;
        cmp edx, ecx
            jne finIguales
            mov igualesInt, 1
            finIguales:
    }
    bool sonIguales = igualesInt;
    //bool filaRecta = origen.getFila() == destino.getFila();
    //bool columnaRecta = origen.getColumna() == destino.getColumna();
    int filaRectaInt = 0;
    int colRectaInt = 0;
    int fila1 = origen.getFila();
    int fila2 = destino.getFila();
    int columna1 = origen.getColumna();
    int columna2 = destino.getColumna();
    __asm {
        mov eax, fila1
        mov ebx, fila2
        cmp eax, ebx
        jne noFila
        mov filaRectaInt, 1
        noFila:
        mov eax, columna1
            mov ebx, columna2
            cmp eax, ebx
            jne noCol
            mov colRectaInt, 1
            noCol :
            nop
    }
    bool filaRecta = filaRectaInt;
    bool columnaRecta = colRectaInt;

    if (!filaRecta && !columnaRecta) {
        return false;
    }

    if (filaRecta) {
        int casilla1 = origen.getColumna();
        int casilla2 = destino.getColumna();
        int paso;
        __asm {
            mov eax, casilla2
            mov ebx, casilla1
            cmp eax, ebx
            jg mayor
            mov paso, -1
            jmp fin
            mayor :
            mov paso, 1
                fin :
        }
        //if (casilla2 > casilla1) {
          //  paso = 1;
        //}
        //else {
          //  paso = -1;
        //}
        for (int casilla = casilla1 + paso; casilla != casilla2;) {
            if (tablero->getCasilla(origen.getFila(), casilla)->getPieza() != nullptr)
                return false;
            __asm {
                mov eax, casilla
                add eax, paso
                mov casilla, eax
            }
        }
    }
    else {
        int fila1 = origen.getFila();
        int fila2 = destino.getFila();
        int paso;
        __asm {
            mov eax, fila2
            mov ebx, fila1
            cmp eax, ebx
            jg mayorFila
            mov paso, -1
            jmp finFila
            mayorFila :
            mov paso, 1
                finFila :
        }
        //if (fila2 > fila1) {
          //  paso = 1;
        //}
        //else {
          //  paso = -1;
        //}
        for (int fila = fila1 + paso; fila != fila2;) {
            if (tablero->getCasilla(fila, origen.getColumna())->getPieza() != nullptr)
                return false;
            __asm {
                mov eax, fila
                add eax, paso
                mov fila, eax
            }
        }

    }
    if (sonIguales) {
        return false;
    }
    return true;
}