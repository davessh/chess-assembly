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

bool Juego::realizarMovimiento()
{
    // Aquí iría la lógica real del movimiento:
    // - seleccionar origen/destino
    // - validar movimiento según la pieza
    // - actualizar tablero, etc.
    // De momento devolvemos false como placeholder.
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

bool Juego::estaReyEnJaque(Color /*color*/)
{
    // Lógica real pendiente de implementar
    return false;
}

bool Juego::esJaqueMate(Color /*color*/)
{
    // Lógica real pendiente de implementar
    return false;
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

const Tablero& Juego::obtenerTablero()
{
    return tablero;
}

void Juego::mostrar()
{

}