#include "Peon.h"
#include "Casilla.h"
#include "../Src/Tablero.h"

bool Peon::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    int filaOrigen = origen.getFila();
    int columnaOrigen = origen.getColumna();
    int filaDestino = destino.getFila();
    int columnaDestino = destino.getColumna();

    if (origen.getPieza() == nullptr) return false;

    if (filaOrigen == filaDestino && columnaOrigen == columnaDestino) {
        return false;
    }

    int direccion;
    int filaInicial;

    if (origen.getPieza()->getColor() == Color::BLANCO) {
        direccion = -1;
        filaInicial = 6;
    }
    else {
        direccion = 1;
        filaInicial = 1;
    }

    Pieza* piezaDestino = destino.getPieza();


    // === MOVIMIENTO SIMPLE (1 casilla adelante) ===
    if (columnaOrigen == columnaDestino &&
        filaDestino == filaOrigen + direccion &&
        piezaDestino == nullptr)
    {
        esPrimerMovimiento = false;
        return true;
    }
    if (columnaOrigen == columnaDestino &&
        filaOrigen == filaInicial &&
        filaDestino == filaOrigen + 2 * direccion &&
        piezaDestino == nullptr)
    {
        int filaIntermedia = filaOrigen + direccion;
        if (tablero->getCasilla(filaIntermedia, columnaDestino)->getPieza() == nullptr)
        {
            esPrimerMovimiento = false;
            alPaso = true;
            return true;
        }
    }

    if (abs(columnaDestino - columnaOrigen) == 1 &&
        filaDestino == filaOrigen + direccion &&
        piezaDestino != nullptr &&
        piezaDestino->getColor() != origen.getPieza()->getColor())
    {
        esPrimerMovimiento = false;
        return true;
    }

    // Implementacion al paso
    if (abs(columnaDestino - columnaOrigen) == 1 &&
        filaDestino == filaOrigen + direccion &&
        piezaDestino == nullptr)
    {
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