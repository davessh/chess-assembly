// ============================================
// Pieza.hpp
// ============================================
#ifndef OACPROYECTO_PIEZA_H
#define OACPROYECTO_PIEZA_H

#include <string>
#include <vector>
#include <memory>

enum class TipoPieza {
    PEON,
    TORRE,
    CABALLO,
    ALFIL,
    REINA,
    REY
};

enum class Color {
    BLANCO,
    NEGRO
};

struct Posicion {
    int fila;
    int columna;

    Posicion(int f = 0, int c = 0) : fila(f), columna(c) {}
    bool operator==(const Posicion& otra) const {
        return fila == otra.fila && columna == otra.columna;
    }
};

class Tablero; // Forward declaration

class Pieza {
protected:
    TipoPieza tipo;
    Color color;
    Posicion posicion;
    bool seHaMovido;

public:
    Pieza(TipoPieza t, Color c, Posicion pos) : tipo(t), color(c), posicion(pos), seHaMovido(false) {}
    virtual ~Pieza() = default;

    virtual std::vector<Posicion> obtenerMovimientosPosibles(const Tablero& tablero) const = 0;
    virtual bool esMovimientoValido(const Posicion& destino, const Tablero& tablero) const = 0;
    virtual char obtenerSimbolo() const = 0;

    TipoPieza obtenerTipo() const { return tipo; }
    Color obtenerColor() const { return color; }
    Posicion obtenerPosicion() const { return posicion; }
    bool haMovido() const { return seHaMovido; }

    void establecerPosicion(const Posicion& pos) { posicion = pos; }
    void establecerSeHaMovido(bool movido) { seHaMovido = movido; }
};

#endif