#ifndef OACPROYECTO_JUEGO_H
#define OACPROYECTO_JUEGO_H

#include "Tablero.h"
#include "Movimiento.h"
#include <vector>

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
    std::vector<Movimiento> historialMovimientos;
    EstadoJuego estado;
    
public:
    Juego() : jugadorActual(Color::BLANCO), estado(EstadoJuego::JUGANDO) {}
    
    void iniciar() {
        tablero.inicializar();
        jugadorActual = Color::BLANCO;
        estado = EstadoJuego::JUGANDO;
        historialMovimientos.clear();
    }
    
    void reiniciar() {
        iniciar();
    }
    
    bool realizarMovimiento(const Posicion& desde, const Posicion& hacia) {
        // Implementar lógica de movimiento
        return false;
    }
    
    bool esMovimientoValido(const Posicion& desde, const Posicion& hacia) const {
        // Implementar validación de movimiento
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
    
    std::vector<Posicion> obtenerMovimientosLegales(const Posicion& pos) const {
        std::vector<Posicion> movimientos;
        // Implementar obtención de movimientos legales
        return movimientos;
    }
    
    EstadoJuego obtenerEstadoJuego() const {
        return estado;
    }
    
    const Tablero& obtenerTablero() const {
        return tablero;
    }
    
    const std::vector<Movimiento>& obtenerHistorialMovimientos() const {
        return historialMovimientos;
    }
    
    void mostrar() const {
        tablero.mostrar();
    }
};

#endif