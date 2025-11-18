cmake_minimum_required(VERSION 3.16)
project(OACPROYECTO)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# IMPORTANTE: ruta Qt con MinGW
set(CMAKE_PREFIX_PATH "C:/Qt/6.10.0/mingw_64")
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(OACPROYECTO
        Chess/Src/main.cpp
        Chess/Src/Tablero.cpp
        Chess/Piezas/Alfil.cpp
        Chess/Piezas/Torre.cpp
        Chess/Piezas/Rey.cpp
        Chess/Piezas/Reina.cpp
        Chess/Piezas/Caballo.cpp
        Chess/Piezas/Peon.cpp
        Chess/Piezas/Pieza.cpp
        Chess/Piezas/Casilla.cpp
        Chess/Src/Juego.cpp
        Chess/GUI/MainWindow.cpp

        Chess/Src/Tablero.h
        Chess/Piezas/Pieza.h
        Chess/Piezas/Peon.h
        Chess/Piezas/Alfil.h
        Chess/Piezas/Torre.h
        Chess/Piezas/Reina.h
        Chess/Piezas/Rey.h
        Chess/Piezas/Caballo.h
        Chess/Piezas/Casilla.h
        Chess/Src/Juego.h
        Chess/GUI/MainWindow.h

        Chess/GUI/_ui/recursos.qrc
        Chess/GUI/Tablero.ui
)

target_link_libraries(OACPROYECTO PRIVATE Qt6::Widgets)
