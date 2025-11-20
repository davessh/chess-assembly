// Peon.cpp
#include "Peon.h"
#include "Casilla.h"
#include "../Src/Tablero.h"

bool Peon::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    int filaOrigen = origen.getFila();
    int columnaOrigen = origen.getColumna();
    int filaDestino = destino.getFila();
    int columnaDestino = destino.getColumna();
    int direccion;
    int filaInicial;
    Pieza* piezaDestino = destino.getPieza();
    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());
    if (sonIguales) return false;

    if (origen.getPieza()->getColor() == Color::BLANCO) {
        direccion = -1;
        filaInicial = 6;
    } else {
        direccion = 1;
        filaInicial = 1;
    }
    if (columnaOrigen == columnaDestino &&
        filaDestino == filaOrigen + direccion && piezaDestino == nullptr)
    {
        esPrimerMovimiento = false;
        return true;
    }

    if (columnaOrigen == columnaDestino && filaOrigen == filaInicial &&
        filaDestino == filaOrigen + 2 * direccion && piezaDestino == nullptr)
    {
        int filaIntermedia = filaOrigen + direccion;
        if (tablero->getCasilla(filaIntermedia, columnaDestino)->getPieza() == nullptr)
        {
            esPrimerMovimiento = false;
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

    if (abs(columnaDestino - columnaOrigen) == 1 && filaDestino == filaOrigen + direccion && piezaDestino == nullptr)
    {
        Pieza* pieza = tablero->getCasilla(filaOrigen,columnaDestino)->getPieza();

        if (pieza != nullptr &&
            pieza->getTipo() == TipoPieza::PEON &&
            pieza->getColor() != origen.getPieza()->getColor())
        {
            Peon* peon = (Peon*)pieza;
            if (peon -> alPaso)
            {
                esPrimerMovimiento = false;
                return true;
            }
        }


        {

        }
    }

    return false;
}

