#ifndef OACPROYECTO_JUEGO_H
#define OACPROYECTO_JUEGO_H

#include "Tablero.h"
#include "Pieza.h"   
#include "Casilla.h"

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

    bool realizarMovimiento(Casilla* origen, Casilla* destino);

    void cambiarJugador();

    Color obtenerJugadorActual();

    void setEstado(EstadoJuego nuevoEstado);

    bool esJaqueMate(Color color);
    bool generaJaque(Casilla* origen, Casilla* destino);

    bool esAhogado(Color color);

    EstadoJuego obtenerEstadoJuego();

    Tablero* obtenerTablero();

    bool hayJaque(Casilla direccionRey);

    bool verificarJaque();

    bool esTablas();

    bool fichasInsuficientes();

    bool hayMovimientosDisponibles(Color turno);

    bool hayPromocionPendiente(Casilla* casilla);

    void mostrar();
};

#endif