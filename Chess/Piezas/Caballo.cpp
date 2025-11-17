#include "Caballo.h"

#include <cmath>
#include <bits/valarray_after.h>

#include "Pieza.h"
#include "Casilla.h"


bool movimientoValido(Casilla origen, Casilla destino)
{

    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                  (origen.getColumna() == destino.getColumna());

    if (destino.getPieza() != nullptr && origen.getPieza() != nullptr)
    {
        if (origen.getPieza()->getColor() != destino.getPieza()->getColor() && !sonIguales)
        {
            int filaOrigen = origen.getFila();
            int columnaOrigen = origen.getColumna();
            int filaDestino = destino.getFila();
            int columnaDestino = destino.getColumna();

            return (abs(filaDestino - filaOrigen) == 2 && abs(columnaDestino - columnaOrigen) == 1);

        }
    }
    return false;
}

