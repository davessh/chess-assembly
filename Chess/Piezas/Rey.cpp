// Rey.cpp
#include "Rey.h"
#include "Casilla.h"
#include "../Src/Tablero.h"

bool Rey::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
    if (origen.getPieza() == nullptr) return false;

    if (destino.getPieza() != nullptr &&
        destino.getPieza()->getColor() == origen.getPieza()->getColor())
        return false;

    int difFila = abs(destino.getFila() - origen.getFila());
    int difCol = abs(destino.getColumna() - origen.getColumna());

    if (difFila <= 1 && difCol <= 1)
        return true;

    if (!seHaMovido && difFila == 0 && difCol == 2)
    {
        int fila = origen.getFila();
        int colOrigen = origen.getColumna();
        int colDestino = destino.getColumna();

        if (colDestino > colOrigen)
        {
            Casilla* cTorre = tablero->getCasilla(fila, 7);

            if (cTorre->getPieza() == nullptr) return false;
            if (cTorre->getPieza()->getTipo() != TipoPieza::TORRE) return false;
            if (cTorre->getPieza()->getSeHaMovido()) return false;

            if (tablero->getCasilla(fila, 5)->getPieza() != nullptr) return false;
            if (tablero->getCasilla(fila, 6)->getPieza() != nullptr) return false;

            for (int c = colOrigen; c <= colDestino; c++)
            {
                Pieza* rey = origen.getPieza();

                tablero->setCasilla(fila, colOrigen, nullptr);
                tablero->setCasilla(fila, c, rey);

                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        Casilla* casilla = tablero->getCasilla(i, j);
                        Pieza* p = casilla->getPieza();

                        if (p && p->getColor() != rey->getColor())
                        {
                            if (p->movimientoValido(*casilla,
                                *tablero->getCasilla(fila, c), tablero))
                            {
                                tablero->setCasilla(fila, c, nullptr);
                                tablero->setCasilla(fila, colOrigen, rey);
                                return false;
                            }
                        }
                    }
                }

                tablero->setCasilla(fila, c, nullptr);
                tablero->setCasilla(fila, colOrigen, rey);
            }
            return true;
        }

        if (colDestino < colOrigen)
        {
            Casilla* cTorre = tablero->getCasilla(fila, 0);

            if (cTorre->getPieza() == nullptr) return false;
            if (cTorre->getPieza()->getTipo() != TipoPieza::TORRE) return false;
            if (cTorre->getPieza()->getSeHaMovido()) return false;

            if (tablero->getCasilla(fila, 1)->getPieza() != nullptr) return false;
            if (tablero->getCasilla(fila, 2)->getPieza() != nullptr) return false;
            if (tablero->getCasilla(fila, 3)->getPieza() != nullptr) return false;

            for (int c = colOrigen; c >= colDestino; c--)
            {
                Pieza* rey = origen.getPieza();

                tablero->setCasilla(fila, colOrigen, nullptr);
                tablero->setCasilla(fila, c, rey);

                for (int i = 0; i < 8; i++)
                {
                    for (int j = 0; j < 8; j++)
                    {
                        Casilla* casilla = tablero->getCasilla(i, j);
                        Pieza* p = casilla->getPieza();

                        if (p && p->getColor() != rey->getColor())
                        {
                            if (p->movimientoValido(*casilla,
                                *tablero->getCasilla(fila, c), tablero))
                            {
                                tablero->setCasilla(fila, c, nullptr);
                                tablero->setCasilla(fila, colOrigen, rey);
                                return false;
                            }
                        }
                    }
                }

                tablero->setCasilla(fila, c, nullptr);
                tablero->setCasilla(fila, colOrigen, rey);
            }
            return true;
        }
    }

    return false;
}
