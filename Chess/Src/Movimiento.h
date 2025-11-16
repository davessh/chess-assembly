#ifndef OACPROYECTO_MOVIMIENTO_H
#define OACPROYECTO_MOVIMIENTO_H

#include "../Piezas/Pieza.h"

class Movimiento {
private:
    Posicion desde;
    Posicion hacia;
    std::shared_ptr<Pieza> piezaMovida;
    std::shared_ptr<Pieza> piezaCapturada;
    bool alPaso;
    bool enroque;
    bool promocion;
    TipoPieza tipoPromocion;

public:
    Movimiento(const Posicion& d, const Posicion& h)
        : desde(d), hacia(h), piezaMovida(nullptr), piezaCapturada(nullptr),
          alPaso(false), enroque(false), promocion(false),
          tipoPromocion(TipoPieza::REINA) {}

    Posicion obtenerDesde() const { return desde; }
    Posicion obtenerHacia() const { return hacia; }

    void establecerPiezaMovida(std::shared_ptr<Pieza> pieza) { piezaMovida = pieza; }
    void establecerPiezaCapturada(std::shared_ptr<Pieza> pieza) { piezaCapturada = pieza; }
    void establecerAlPaso(bool valor) { alPaso = valor; }
    void establecerEnroque(bool valor) { enroque = valor; }
    void establecerPromocion(bool valor, TipoPieza tipo = TipoPieza::REINA) {
        promocion = valor;
        tipoPromocion = tipo;
    }

    bool esCaptura() const { return piezaCapturada != nullptr; }
    bool esMovimientoAlPaso() const { return alPaso; }
    bool esMovimientoEnroque() const { return enroque; }
    bool esMovimientoPromocion() const { return promocion; }
};

#endif