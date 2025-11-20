#include "Alfil.h"

bool Alfil::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());

    if (destino.getPieza() != nullptr && origen.getPieza() != nullptr)
    {
        if (origen.getPieza()->getColor() != destino.getPieza()->getColor() && !sonIguales)
        {
            int difFila = abs(destino.getFila() - origen.getFila());
            int difCol = abs(destino.getColumna() - origen.getColumna());

            if (difFila == difCol && difFila > 0)
            {

            }
        }
    }
    return false;
}


