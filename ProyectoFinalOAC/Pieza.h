#ifndef OACPROYECTO_PIEZA_H
#define OACPROYECTO_PIEZA_H

#include <cmath>

// Forward declarations en vez de includes pesados
class Casilla;
class Tablero;

enum class TipoPieza {
    PEON, // 0
    TORRE, // 1
    CABALLO, // 2
    ALFIL, // 3
    REINA, // 4
    REY // 5
};

enum class Color {
    BLANCO, // 0
    NEGRO // 1
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


    virtual bool movimientoValido(Casilla origen, Casilla destino, Tablero* tablero);
    virtual void setAlPaso(bool valor) {}
    virtual bool getAlPaso() const { return false; }
    virtual bool getLlegoAlFinal() const { return false; }
    virtual void setLlegoAlFinal(bool valor) {}

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