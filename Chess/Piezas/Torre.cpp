#include "Torre.h"

#include <cmath>

#include "Casilla.h"
#include "../Src/Tablero.h"

bool Torre::movimientoValido(Casilla origen, Casilla destino) const
{

    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());


    if (destino.getPieza() != nullptr && origen.getPieza() != nullptr)
    {
        if (origen.getPieza()->getColor() != destino.getPieza()->getColor() && !sonIguales)
        {
            if (origen.getFila() == destino.getFila()){
                int colOrigen = origen.getColumna();
                while (colOrigen != destino.getColumna())
                {
                    if (origen.getColumna() < destino.getColumna())
                    {
                        colOrigen += 1;
                    }
                    else {
                        colOrigen -= 1;
                    }
                    //if(tablero[origen.getFila()][colOrigen].getPieza() != nullptr)
                    //{
                    // return false;
                    //}
                }
            }
            else if (origen.getColumna() == destino.getColumna()){
                int filaOrigen = origen.getFila();
                while (filaOrigen != destino.getColumna())
                {
                    if (origen.getFila() < destino.getFila())
                    {
                        filaOrigen += 1;
                    }
                    else {
                        filaOrigen -= 1;
                    }

                    //if(tablero[filaOrigen][origen.getColumna()].getPieza() != nullptr)
                    //{
                    // return false;
                    //}


                }
            }
        }
    }
    return false;
}
