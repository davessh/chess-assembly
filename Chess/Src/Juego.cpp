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
    if (pieza->movimientoValido(*origen, *destino, &tablero) && estado != EstadoJuego::JAQUE)
    {
        //Agregar si se hace un movimiento que genera jacke no se pueda realizar

        tablero.setCasilla(destino->getFila(), destino->getColumna(), pieza);
        tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);
        if (verificarJacke())
        {
            estado = EstadoJuego::JAQUE;
        }
        cambiarJugador();
        return true;
    }
    else if (estado == EstadoJuego::JAQUE && verificarJacke())
    {
        //Si se mueve se puede mover una ficha y quita el hacke, no hay hacke y te permite buscar la jugada por tu cuenta
    }
    // Aquí iría la lógica real del movimiento:
    // - seleccionar origen/destino

    // - validar movimiento según la pieza
    // - actualizar tablero, etc.
    // De momento devolvemos false como placeholder.
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



bool Juego::esJaqueMate(Color /*color*/)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
            if (pieza != nullptr && pieza->getColor() == jugadorActual)
            {
                return false;
            }
        }
    }
    return true;
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