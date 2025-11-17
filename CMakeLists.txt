cmake_minimum_required(VERSION 3.10)
project(OACPROYECTO)

set(CMAKE_CXX_STANDARD 17)

add_executable(OACPROYECTO
        Chess/Src/main.cpp
        Chess/Src/Tablero.cpp
        Chess/Src/Tablero.h
        Chess/Piezas/Pieza.h
        Chess/Piezas/Peon.h
        Chess/Piezas/Alfil.h
        Chess/Piezas/Torre.h
        Chess/Piezas/Reina.h
        Chess/Piezas/Rey.h
        Chess/Piezas/Caballo.h
        Chess/Src/Movimiento.h
        Chess/Src/Movimiento.h
        Chess/Src/Juego.h
        Chess/Piezas/Alfil.cpp
        Chess/Piezas/Pieza.cpp
        Chess/Piezas/Torre.cpp
        Chess/Piezas/Rey.cpp
        Chess/Piezas/Reina.cpp
        Chess/Piezas/Caballo.cpp
        Chess/Piezas/Peon.cpp
        Chess/GUI/TableroInterfaz.h
        Chess/Piezas/Casilla.h
        Chess/Piezas/Casilla.cpp
        Chess/Piezas/Pieza.cpp

)