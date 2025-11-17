#ifndef OACPROYECTO_JUEGO_H
#define OACPROYECTO_JUEGO_H

#include "Tablero.h"

enum class EstadoJuego {
    JUGANDO,
    JAQUE,
    JAQUE_MATE,
    AHOGADO,
    TABLAS
};

class Juego {
private:
    Tablero tablero = Tablero();
    Color jugadorActual;
    EstadoJuego estado;

public:

    Juego() : jugadorActual(Color::BLANCO), estado(EstadoJuego::JUGANDO) {}

    void iniciar() {
        tablero.inicializar();
        jugadorActual = Color::BLANCO;
        estado = EstadoJuego::JUGANDO;
    }

    void reiniciar() {
        iniciar();
    }

    bool realizarMovimiento() {
        // Implementar lógica de movimiento
        return false;
    }

    void cambiarJugador() {
        jugadorActual = (jugadorActual == Color::BLANCO) ? Color::NEGRO : Color::BLANCO;
    }

    Color obtenerJugadorActual() const {
        return jugadorActual;
    }

    bool estaReyEnJaque(Color color) const {
        // Implementar detección de jaque
        return false;
    }

    bool esJaqueMate(Color color) const {
        // Implementar detección de jaque mate
        return false;
    }

    bool esAhogado(Color color) const {
        // Implementar detección de tablas por ahogado
        return false;
    }


    EstadoJuego obtenerEstadoJuego() const {
        return estado;
    }

    const Tablero& obtenerTablero() const {
        return tablero;
    }

    void mostrar() const {
        //tablero.mostrar();
    }
};

#endif