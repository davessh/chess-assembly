#ifndef OACPROYECTO_PIEZA_H
#define OACPROYECTO_PIEZA_H

#include <cmath>

// Forward declarations en vez de includes pesados
class Casilla;
class Tablero;

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

// ... existing code ...

class Pieza {
protected:
    TipoPieza tipo;
    Color color;
    bool puedeJugarse;
    bool seHaMovido;
    int fila;
    int columna;

public:
    Pieza(TipoPieza tipo, Color colorJugador, int fila, int columna,
          bool puedeJugarse = true, bool seHaMovido = false);

    // Aquí ya puedes usar Casilla y Tablero gracias al forward declaration
    virtual bool movimientoValido(Casilla origen, Casilla destino, Tablero& tablero);

    void setMovido(bool valor) { seHaMovido = valor; }
    void setColor(Color color) { this->color = color; }
    void setFila(int fila) { this->fila = fila; }
    void setColumna(int columna) { this->columna = columna; }
    void setTipo(TipoPieza tipo) { this->tipo = tipo; }
    void setPuedeJugarse(bool valor) { this->puedeJugarse = valor; }

    Color getColor() const { return color; }
    int getFila() const { return fila; }
    int getColumna() const { return columna; }
    TipoPieza getTipo() const { return tipo; }
    bool getSeHaMovido() const { return seHaMovido; }
};

#endif