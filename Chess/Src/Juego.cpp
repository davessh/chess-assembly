#include "Juego.h"

Juego::Juego()
    : tablero(), jugadorActual(Color::BLANCO), estado(EstadoJuego::JUGANDO)
{
}

void Juego::iniciar()
{
    tablero.inicializar();
    tablero.mostrarTablero();
    jugadorActual = Color::BLANCO;
    estado = EstadoJuego::JUGANDO;
}

void Juego::reiniciar()
{
    iniciar();
}

bool Juego::realizarMovimiento(Casilla* origen, Casilla* destino)
{
    Pieza* pieza = origen->getPieza();

    if (pieza == nullptr) return false;
    if (pieza->getColor() != jugadorActual) return false; // NUEVO: verificar turno

    Pieza* piezaDestino = destino->getPieza();
    if (piezaDestino != nullptr && piezaDestino->getColor() == jugadorActual) {
        return false; // NUEVO
    }

    if (estado != EstadoJuego::JAQUE && estado != EstadoJuego::JAQUE_MATE)
    {
        if (pieza->movimientoValido(*origen, *destino, &tablero) && !generaJacke(origen, destino))
        {
            tablero.setCasilla(destino->getFila(), destino->getColumna(), pieza);
            tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

            if (!pieza->getSeHaMovido()) {
                pieza->setMovido(true);
            }

            cambiarJugador();

            if (verificarJacke()) {
                if (esJaqueMate(jugadorActual)) {
                    estado = EstadoJuego::JAQUE_MATE;
                } else {
                    estado = EstadoJuego::JAQUE;
                }
            }

            return true;
        }
    }
    else if (estado == EstadoJuego::JAQUE)
    {
        if (pieza->movimientoValido(*origen, *destino, &tablero) && !generaJacke(origen, destino))
        {
            tablero.setCasilla(destino->getFila(), destino->getColumna(), pieza);
            tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

            if (!pieza->getSeHaMovido()) {
                pieza->setMovido(true);
            }

            cambiarJugador();

            if (verificarJacke()) {
                if (esJaqueMate(jugadorActual)) {
                    estado = EstadoJuego::JAQUE_MATE;
                } else {
                    estado = EstadoJuego::JAQUE;
                }
            } else {
                estado = EstadoJuego::JUGANDO; // Ya no hay jaque
            }

            return true;
        }
        else
        {
            if (esJaqueMate(jugadorActual)) {
                estado = EstadoJuego::JAQUE_MATE;
            }
        }
    }
    else if (estado == EstadoJuego::JAQUE_MATE)
    {
        return false; // El juego ya terminó
    }

    return false;
}

bool Juego::verificarJacke()
{
    Casilla* casillaRey = tablero.buscarRey(jugadorActual);
    return hayJacke(*casillaRey);
}

bool Juego::hayJacke(Casilla direccionRey)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
            Casilla* casilla = tablero.getCasilla(i, j);
            if (pieza != nullptr && pieza->getColor() != direccionRey.getPieza()->getColor())
            {
                if (pieza->movimientoValido(*casilla, direccionRey, &tablero))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Juego::cambiarJugador()
{
    if (jugadorActual == Color::BLANCO) {
        jugadorActual = Color::NEGRO;
    } else {
        jugadorActual = Color::BLANCO;
    }
}

Color Juego::obtenerJugadorActual()
{
    return jugadorActual;
}



bool Juego::esJaqueMate(Color turno)
{
    if (!verificarJacke()) {
        return false; // No está en jaque, no puede ser mate
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
            Casilla* casillaPieza = tablero.getCasilla(i, j);
            if (!pieza || pieza->getColor() != turno) continue;

            for (int movi = 0; movi < 8; movi++)
            {
                for (int movj = 0; movj < 8; movj++)
                {
                    Casilla* casilla = tablero.getCasilla(movi, movj);
                    if (pieza->movimientoValido(*casillaPieza, *casilla, &tablero)
                    && !generaJacke(casillaPieza, casilla))
                    {
                        return false; // Encontramos un movimiento legal que salva al rey
                    }
                }
            }

        }
    }
    return true;
}

bool Juego::generaJacke(Casilla* origen, Casilla* destino)
{
    Pieza* piezaCapturada = destino->getPieza();
    Pieza* piezaMovida = origen->getPieza();

    tablero.setCasilla(destino->getFila(), destino->getColumna(), origen->getPieza());
    tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

    Casilla* casillaRey = tablero.buscarRey(jugadorActual);
    bool enJaque = hayJacke(*casillaRey);

    tablero.setCasilla(destino->getFila(), destino->getColumna(), piezaCapturada);
    tablero.setCasilla(origen->getFila(), origen->getColumna(), piezaMovida);

    return enJaque;
}

bool Juego::esAhogado(Color /*color*/)
{
    // Lógica real pendiente de implementar
    return false;
}

EstadoJuego Juego::obtenerEstadoJuego()
{
    return estado;
}

Tablero* Juego::obtenerTablero()
{
    return &tablero;
}

void Juego::mostrar()
{

}