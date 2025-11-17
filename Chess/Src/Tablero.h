#ifndef OACPROYECTO_TABLERO_H
#define OACPROYECTO_TABLERO_H

#include <array>
#include <memory>
#include "../Piezas/Pieza.h"

class Tablero {
private:
    std::array<std::array<std::shared_ptr<Pieza>, 8>, 8> tablero;

public:
    Tablero();

    void inicializar();
    void limpiar();

    std::shared_ptr<Pieza> obtenerPiezaEn(const Posicion& pos) const;
    void establecerPiezaEn(const Posicion& pos, std::shared_ptr<Pieza> pieza);
    void eliminarPiezaEn(const Posicion& pos);

    bool esPosicionValida(const Posicion& pos) const;
    bool esPosicionVacia(const Posicion& pos) const;
    bool esPosicionOcupadaPorColor(const Posicion& pos, Color color) const;

    void mostrar() const;
};

#endif
