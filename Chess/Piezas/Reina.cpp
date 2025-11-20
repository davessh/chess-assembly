// Reina.cpp
#include "Reina.h"
#include "Casilla.h"

    bool Reina::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero) {
    if (origen.getPieza() == nullptr) return false;

    bool sonIguales = (origen.getFila() == destino.getFila()) &&
                      (origen.getColumna() == destino.getColumna());
    if (sonIguales) return false;



    // La reina se mueve como torre o alfil
    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());



        if (!(difFila == 0 || difCol == 0 || difFila == difCol)) {
            return false;
        }

        int pasoFila = 0;
        if (destino.getFila() > origen.getFila()) pasoFila = 1;
        else if (destino.getFila() < origen.getFila()) pasoFila = -1;

        int pasoCol = 0;
        if (destino.getColumna() > origen.getColumna()) pasoCol = 1;
        else if (destino.getColumna() < origen.getColumna()) pasoCol = -1;

        int filaActual = origen.getFila() + pasoFila;
        int colActual = origen.getColumna() + pasoCol;

        while (filaActual != destino.getFila() || colActual != destino.getColumna())
        {
            if (tablero->getCasilla(filaActual, colActual)->getPieza() != nullptr) {
                return false;
            }
            filaActual += pasoFila;
            colActual += pasoCol;
        }

        return true;
    }