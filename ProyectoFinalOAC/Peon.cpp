#include "Peon.h"
#include "Casilla.h"
#include "Tablero.h"

bool Peon::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    int filaOrigen = origen.getFila();
    int columnaOrigen = origen.getColumna();
    int filaDestino = destino.getFila();
    int columnaDestino = destino.getColumna();

    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = false;

    // ============================================================
    // C++:
    // if (filaOrigen == filaDestino && columnaOrigen == columnaDestino)
    //      sonIguales = true;
    // else sonIguales = false;
    // ============================================================
    __asm {
        mov eax, filaOrigen
        cmp eax, filaDestino
        jne no_iguales

        mov eax, columnaOrigen
        cmp eax, columnaDestino
        jne no_iguales

        mov sonIguales, 1
        jmp fin_cmp

        no_iguales :
        mov sonIguales, 0

            fin_cmp :
    }

    if (sonIguales) return false;

    int direccion;
    int filaInicial;

    // ============================================================
    // C++:
    // if (color == blanco) { direccion = -1; filaInicial = 6; }
    // else { direccion = 1; filaInicial = 1; }
    // ============================================================
    if (origen.getPieza()->getColor() == Color::BLANCO) {
        direccion = -1;
        filaInicial = 6;
    }
    else {
        direccion = 1;
        filaInicial = 1;
    }

    Pieza* piezaDestino = destino.getPieza();

    // ============================================================
    // MOVIMIENTO SIMPLE
    // C++:
    // if (colOrigen == colDestino &&
    //     filaDestino == filaOrigen + direccion &&
    //     piezaDestino == nullptr)
    //      return true;
    // ============================================================
    bool movSimple = false;
    int filaEsperada = filaOrigen + direccion;

    __asm {
        mov eax, columnaOrigen
        cmp eax, columnaDestino
        jne no_m_simple

        mov eax, filaDestino
        cmp eax, filaEsperada
        jne no_m_simple

        mov eax, piezaDestino
        cmp eax, 0
        jne no_m_simple

        mov movSimple, 1

        no_m_simple:
    }

    if (movSimple) {
        esPrimerMovimiento = false;
        return true;
    }


    // ============================================================
    // MOVIMIENTO DOBLE
    // C++:
    // if (colOrigen == colDestino &&
    //     filaOrigen == filaInicial &&
    //     filaDestino == filaOrigen + 2 * direccion &&
    //     piezaDestino == nullptr)
    // ============================================================
    bool movDoble = false;
    int filaDobleEsperada = filaOrigen + 2 * direccion;

    __asm {
        mov eax, columnaOrigen
        cmp eax, columnaDestino
        jne no_m_doble

        mov eax, filaOrigen
        cmp eax, filaInicial
        jne no_m_doble

        mov eax, filaDestino
        cmp eax, filaDobleEsperada
        jne no_m_doble

        mov eax, piezaDestino
        cmp eax, 0
        jne no_m_doble

        mov movDoble, 1

        no_m_doble:
    }

    if (movDoble) {
        int filaIntermedia = filaOrigen + direccion;
        if (tablero->getCasilla(filaIntermedia, columnaDestino)->getPieza() == nullptr)
        {
            esPrimerMovimiento = false;
            alPaso = true;
            return true;
        }
    }

    // ============================================================
    // CAPTURA NORMAL
    // C++:
    // if (abs(colDestino - colOrigen) == 1 &&
    //     filaDestino == filaOrigen + direccion &&
    //     piezaDestino != nullptr &&
    //     colores distintos)
    // ============================================================
    int diffCol = columnaDestino - columnaOrigen;
    if (diffCol < 0) diffCol = -diffCol;

    bool capturaNormal = false;

    int filaEsperadaCap = filaOrigen + direccion;

    __asm {
        mov eax, diffCol
        cmp eax, 1
        jne no_cap_norm

        mov eax, filaDestino
        cmp eax, filaEsperadaCap
        jne no_cap_norm

        mov eax, piezaDestino
        cmp eax, 0
        je no_cap_norm

        mov capturaNormal, 1

        no_cap_norm:
    }

    if (capturaNormal) {
        if (piezaDestino->getColor() != origen.getPieza()->getColor()) {
            esPrimerMovimiento = false;
            return true;
        }
    }

    // ============================================================
    // CAPTURA AL PASO
    // C++:
    // if (abs(colDest - colOrg) == 1 &&
    //     filaDest == filaOrigen + direccion &&
    //     piezaDestino == nullptr)
    //     verificar peón lateral en "al paso"
    // ============================================================
    bool movAlPaso = false;

    __asm {
        mov eax, diffCol
        cmp eax, 1
        jne no_passant

        mov eax, filaDestino
        cmp eax, filaEsperadaCap
        jne no_passant

        mov eax, piezaDestino
        cmp eax, 0
        jne no_passant

        mov movAlPaso, 1

        no_passant:
    }

    if (movAlPaso) {
        Pieza* piezaLateral = tablero->getCasilla(filaOrigen, columnaDestino)->getPieza();
        if (piezaLateral != nullptr &&
            piezaLateral->getTipo() == TipoPieza::PEON &&
            piezaLateral->getColor() != origen.getPieza()->getColor() &&
            piezaLateral->getAlPaso())
        {
            esPrimerMovimiento = false;
            return true;
        }
    }

    return false;
}