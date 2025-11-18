#ifndef OACPROYECTO_JUEGO_H
#define OACPROYECTO_JUEGO_H

#include "Tablero.h"
#include "../Piezas/Pieza.h"   // Necesario para el enum Color

enum class EstadoJuego {
    JUGANDO,
    JAQUE,
    JAQUE_MATE,
    AHOGADO,
    TABLAS
};

class Juego {
private:
    Tablero tablero;
    Color jugadorActual;
    EstadoJuego estado;

public:
    Juego();

    void iniciar();

    void reiniciar();

    bool realizarMovimiento();

    void cambiarJugador();

    Color obtenerJugadorActual();

    bool estaReyEnJaque(Color color);

    bool esJaqueMate(Color color);

    bool esAhogado(Color color);

    EstadoJuego obtenerEstadoJuego();

    const Tablero& obtenerTablero();

    void mostrar();
};

#endif