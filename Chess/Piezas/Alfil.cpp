#include "Alfil.h"
#include "Casilla.h"
#include "../Src/Tablero.h"
#include <QDebug>

bool Alfil::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    bool sonIguales = (origen.getFila() == destino.getFila()) &&
        (origen.getColumna() == destino.getColumna());
    if (origen.getPieza() != nullptr)
    {
        if (destino.getPieza() == nullptr ||
            origen.getPieza()->getColor() != destino.getPieza()->getColor())
        {
            if (!sonIguales)
            {
                int difFila = abs(destino.getFila() - origen.getFila());
                int difCol = abs(destino.getColumna() - origen.getColumna());
                if (difFila == difCol && difFila > 0)
                {
                    int pasoColumna = (destino.getColumna() < origen.getColumna()) ? -1 : 1;
                    int pasoFila = (destino.getFila() < origen.getFila()) ? -1 : 1;

                    int columnaActual = origen.getColumna() + pasoColumna;
                    int filaActual = origen.getFila() + pasoFila;

                    while (filaActual != destino.getFila() || columnaActual != destino.getColumna())
                    {
                        if (tablero->getCasilla(filaActual, columnaActual)->getPieza() != nullptr)
                        {
                            return false;
                        }
                        filaActual += pasoFila;
                        columnaActual += pasoColumna;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}