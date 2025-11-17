#include "Juego.h"
#include "../Piezas/Peon.h"
#include "../Piezas/Alfil.h"
#include "../Piezas/Torre.h"
#include "../Piezas/Reina.h"
#include "../Piezas/Rey.h"
#include "../Piezas/Caballo.h"
#include <iostream>


int main() {
    Juego juego;
    juego.iniciar();

    std::cout << "Juego de ajedrez iniciado!" << std::endl;
    juego.mostrar();

    // Aquí puedes agregar tu lógica de juego

    return 0;
}