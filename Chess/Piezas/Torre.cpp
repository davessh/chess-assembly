#include "Torre.h"

#include <cmath>
#include <bits/valarray_after.h>

#include "Casilla.h"
#include "../Src/Tablero.h"

bool movimientoValido(Casilla origen, Casilla destino, Tablero& tablero){

    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (destino.getPieza() != nullptr &&
            destino.getPieza()->getColor() == origen.getPieza()->getColor());

            //mismo lugar
            if(origen.getFila() == destino.getFila() &&
            origen.getColumna() == destino.getColumna()){
                return false;
            }

            bool filaRecta = origen.getFila() == destino.getFila();
            bool columnaRecta = origen.getColumna() == destino.getColumna();

            //solo puede ir en linea recta
            if(!filaRecta && !columnaRecta){
                return false;
            }

            if(filaRecta){
                int casilla1 = origen.getColumna();
                int casilla2 = destino.getColumna();
                int paso;
                if (casilla2 > casilla1){
                    paso = 1;
                } else {
                    paso = -1;
                }

                for(int casilla = casilla1 + paso; casilla != casilla2; casilla += paso){
                    if (tablero.getCasilla(origen.getFila(), casilla).getPieza() != nullptr)
                    return false;
                }
            } else {
                int fila1 = origen.getFila();
                int fila2 = destino.getFila();
                int paso;
                if (fila2 > fila1){
                    paso = 1;
                } else {
                    paso = -1;
                }

                for(int fila = fila1 + paso; fila != fila2; fila += paso){
                    if (tablero.getCasilla(fila, origen.getColumna()).getPieza() != nullptr)
                        return false;
                }
            }

            if(sonIguales){
                return false;
            }
    return true;
}
