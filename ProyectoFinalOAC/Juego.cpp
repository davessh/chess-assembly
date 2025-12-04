#include "Juego.h"
#include <QDebug>






Juego::Juego()
    : tablero(), jugadorActual(Color::BLANCO), estado(EstadoJuego::JUGANDO)
{
}

void Juego::iniciar()
{
    tablero.inicializar();
    jugadorActual = Color::BLANCO;
    estado = EstadoJuego::JUGANDO;
}

void Juego::reiniciar()
{
    iniciar();
}

bool Juego::realizarMovimiento(Casilla* origen, Casilla* destino)
{
    Pieza* pieza = origen->getPieza();

    __asm {

        cmp pieza, 0
        jne noNull

        falso :
    }
    return false;


    __asm {
    noNull:
    }
    Color colorPieza = pieza->getColor();
    Color jugador = jugadorActual;
    __asm {
        mov eax, colorPieza
        mov ebx, jugador
        cmp eax, ebx
        jne falso


    }




    Pieza* piezaDestino = destino->getPieza();

    __asm {
        cmp pieza, 0
        je falso
    }

    Color colorActual = pieza->getColor();
    __asm {
        mov eax, colorActual
        cmp eax, jugador
        jne falso

    }



    if (!pieza->movimientoValido(*origen, *destino, &tablero) || generaJaque(origen, destino))
        return false;

    TipoPieza tipoPieza = pieza->getTipo();
    int colDestino = destino->getColumna();
    int colOrigen = origen->getColumna();

    __asm {
        cmp tipoPieza, 5
        jne pasoPeon

        mov eax, colDestino
        sub eax, colOrigen

        jns noNegativo
        neg eax

        noNegativo :
        cmp eax, 2
            jne pasoPeon
    }

    int fila = origen->getFila();

    __asm {
        cmp colDestino, 6
        jne noTorreDerecha
    }

    Pieza* torre = tablero.getCasilla(fila, 7)->getPieza();
    tablero.setCasilla(fila, 5, torre);
    tablero.setCasilla(fila, 7, nullptr);
    torre->setMovido(true);

    __asm {
    noTorreDerecha:
        cmp colDestino, 2
            jne pasoPeon
    }
    Pieza* torre2 = tablero.getCasilla(fila, 0)->getPieza();
    tablero.setCasilla(fila, 3, torre2);
    tablero.setCasilla(fila, 0, nullptr);
    torre2->setMovido(true);





    __asm {
    pasoPeon:
        cmp tipoPieza, 0
            jne realizar
            cmp piezaDestino, 0
            jne realizar
            mov eax, colDestino
            sub eax, colOrigen
            jns noAbs
            neg eax
            noAbs :
        cmp eax, 1
            jne realizar

    }
    Pieza* peonCapturado =
        tablero.getCasilla(origen->getFila(), destino->getColumna())->getPieza();
    __asm {
        cmp peonCapturado, 0
        je realizar
    }
    TipoPieza tipoPeonCapturado = peonCapturado->getTipo();
    __asm {
        cmp tipoPeonCapturado, 0
        jne realizar
    }
    tablero.setCasilla(origen->getFila(), destino->getColumna(), nullptr);



    __asm {
    realizar:
    }

    tablero.setCasilla(destino->getFila(), destino->getColumna(), pieza);
    tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

    pieza->setMovido(true);

    __asm {
        cmp tipoPieza, 0
        jne noPromocion
    }

    int filaPromocion = (pieza->getColor() == Color::BLANCO) ? 0 : 7;
    int filaDestino = destino->getFila();

    __asm {
        mov eax, destino
        mov ebx, filaDestino
        cmp ebx, filaPromocion
        jne noPromocion
    }

    pieza->setLlegoAlFinal(true);


    __asm {
    noPromocion:
    }

    int i = 0, j = 0;

    __asm {
    loopFila:
        cmp i, 8
            jge finFor

            mov j, 0

            loopColumna :
            cmp j, 8
            jge finFila
    }

    Pieza* p = tablero.getCasilla(i, j)->getPieza();

    __asm {
        cmp p, 0
        je incJ
    }

    Color colorP = p->getColor();
    TipoPieza tipoP = p->getTipo();

    __asm {
        mov eax, colorP
        cmp eax, jugador
        je incJ
        cmp tipoP, 0
        jne incJ
        mov eax, p
        cmp eax, pieza
        je incJ
    }

    p->setAlPaso(false);

    __asm {
    incJ:
        inc j
            mov ebx, j
            jmp loopColumna

            finFila :
        inc i
            mov ecx, i
            jmp loopFila

            finFor :
    }

    cambiarJugador();

    EstadoJuego estadoPrevio = estado;

    if (verificarJaque()) {
        if (esJaqueMate(jugadorActual)) {
            __asm {
                mov estadoPrevio, 2
            }
        }
        else {
            __asm {
                mov estadoPrevio, 1
            }
        }
    }
    else if (esTablas()) {
        __asm {
            mov estadoPrevio, 4
        }
    }
    else {
        __asm {
            mov estadoPrevio, 0
        }
    }
    estado = estadoPrevio;
    return true;
}


bool Juego::verificarJaque()
{
    Casilla* casillaRey = tablero.buscarRey(jugadorActual);

    if (casillaRey == nullptr) {
        return false;
    }

    return hayJaque(*casillaRey);
}


bool Juego::hayJaque(Casilla direccionRey)
{
    Pieza* piezaRey = direccionRey.getPieza();
    __asm {
        cmp piezaRey, 0
        jne noNull
    }
    return false;

    __asm {
    noNull:
    }

    int i = 0, j = 0;

    __asm {
    loopFila:
        cmp i, 8
            jge finFor

            mov j, 0

            loopColumna :
            cmp j, 8
            jge finFila
    }
    Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
    Casilla* casilla = tablero.getCasilla(i, j);
    __asm {
        cmp pieza, 0
        je incJ
    }
    Color colorPieza = pieza->getColor();
    Color colorRey = piezaRey->getColor();
    __asm {
        mov eax, colorPieza
        cmp eax, colorRey
        je incJ
    }

    if (pieza->movimientoValido(*casilla, direccionRey, &tablero))
        return true;


    __asm {
    incJ:
        inc j
            jmp loopColumna

            finFila :
        inc i
            mov ecx, i
            jmp loopFila

            finFor :
    }



    return false;
}

void Juego::cambiarJugador()
{
    if (jugadorActual == Color::BLANCO) {
        jugadorActual = Color::NEGRO;
    }
    else {
        jugadorActual = Color::BLANCO;
    }
}

Color Juego::obtenerJugadorActual()
{
    return jugadorActual;
}



bool Juego::esJaqueMate(Color turno)
{
    if (!verificarJaque()) {
        return false;
    }
    int i = 0, j = 0;
    __asm {
    loopFila:
        cmp i, 8
            jge finFor
            mov j, 0

            loopColumna :
            cmp j, 8
            jge finFila
    }

    Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
    Casilla* casillaPieza = tablero.getCasilla(i, j);

    __asm {
        cmp pieza, 0
        je incJ
    }

    Color colPieza = pieza->getColor();
    Color turnoActual = turno;
    __asm {
        mov eax, turnoActual
        cmp eax, colPieza
        jne incJ
    }

    int movi = 0, movj = 0;

    __asm {
        mov movi, 0

        loopFilaMov:
        cmp movi, 8
            jge incJ
            mov movj, 0

            loopColumnaMov :
            cmp movj, 8
            jge finFilaMov
    }

    Casilla* casilla = tablero.getCasilla(movi, movj);

    if (pieza->movimientoValido(*casillaPieza, *casilla, &tablero)
        && !generaJaque(casillaPieza, casilla))
    {
        return false;
    }

    __asm {
    incMovJ:
        inc movj
            jmp loopColumnaMov

            finFilaMov :
        inc movi
            jmp loopFilaMov

            incJ :
        inc j
            jmp loopColumna

            finFila :
        inc i
            jmp loopFila

            finFor :
    }

    return true;
}

bool Juego::generaJaque(Casilla* origen, Casilla* destino)
{
    Pieza* piezaCapturada = destino->getPieza();
    Pieza* piezaMovida = origen->getPieza();

    if (piezaMovida == nullptr) {
        return true; 
    }

    tablero.setCasilla(destino->getFila(), destino->getColumna(), piezaMovida);
    tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

    Casilla* casillaRey = tablero.buscarRey(jugadorActual);

    bool enJaque = false;
    if (casillaRey != nullptr) {
        enJaque = hayJaque(*casillaRey);
    }
    else {
        enJaque = true;
    }

    tablero.setCasilla(destino->getFila(), destino->getColumna(), piezaCapturada);
    tablero.setCasilla(origen->getFila(), origen->getColumna(), piezaMovida);

    return enJaque;
}

bool Juego::esAhogado(Color turno)
{
    Casilla* rey = tablero.buscarRey(turno);

    if (rey == nullptr) return false;

    if (!hayMovimientosDisponibles(turno) && !hayJaque(*rey)) {
        return true;
    }

    return false;
}



bool Juego::hayMovimientosDisponibles(Color turno) {


    int i = 0, j = 0;
    __asm {
    loopFila:
        cmp i, 8
            jge finFor
            mov j, 0

            loopColumna :
            cmp j, 8
            jge finFila
    }

    Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
    Casilla* casillaPieza = tablero.getCasilla(i, j);

    __asm {
        cmp pieza, 0
        je incJ
    }

    Color colPieza = pieza->getColor();
    Color turnoActual = turno;
    __asm {
        mov eax, turnoActual
        cmp eax, colPieza
        jne incJ
    }

    int movi = 0, movj = 0;

    __asm {
        mov movi, 0

        loopFilaMov:
        cmp movi, 8
            jge incJ
            mov movj, 0

            loopColumnaMov :
            cmp movj, 8
            jge finFilaMov
    }

    Casilla* casilla = tablero.getCasilla(movi, movj);

    if (pieza->movimientoValido(*casillaPieza, *casilla, &tablero)
        && !generaJaque(casillaPieza, casilla))
    {
        return true;
    }

    __asm {
    incMovJ:
        inc movj
            jmp loopColumnaMov

            finFilaMov :
        inc movi
            jmp loopFilaMov

            incJ :
        inc j
            jmp loopColumna

            finFila :
        inc i
            jmp loopFila

            finFor :
    }


    return false;

}


bool Juego::fichasInsuficientes() {
    Casilla* tempCasilla = nullptr;
    int cantAlfiles = 0;
    int cantCaballos = 0;

    int i = 0, j = 0;
    __asm {
    loopFila:
        cmp i, 8
            jge finFor

            mov j, 0

            loopColumna :
            cmp j, 8
            jge finFila
    }
    Casilla* casilla = tablero.getCasilla(i, j);
    Pieza* pieza = casilla->getPieza();
    __asm {
        cmp pieza, 0
        je incJ
    }


    TipoPieza tipoPieza = pieza->getTipo();

    __asm {
        cmp tipoPieza, 5
        je valido
        cmp tipoPieza, 2
        je valido
        cmp tipoPieza, 3
        je valido
        falso :
    }
    return false;

    __asm {
    valido:
        cmp tipoPieza, 2
            je esCaballo
            cmp tipoPieza, 3
            je esAlfil
            jmp finIteracion

            esCaballo :
        inc cantCaballos
            cmp cantCaballos, 1
            jg falso
            jmp finIteracion

            esAlfil :
        inc cantAlfiles
            cmp cantAlfiles, 2
            jg falso

            cmp tempCasilla, 0
            je guardarCasilla
    }

    Color colorPieza = pieza->getColor();
    Color colorTempCasilla = tempCasilla->getPieza()->getColor();

    __asm {
        mov eax, colorPieza
        cmp eax, colorTempCasilla
        je falso
    }

    int filaTemp = tempCasilla->getFila();
    int colTemp = tempCasilla->getColumna();
    int filaActual = casilla->getFila();
    int colActual = casilla->getColumna();

    __asm {
        mov eax, filaTemp
        mov ebx, colTemp
        mov ecx, filaActual
        mov edx, colActual

        mov esi, eax
        add esi, ebx
        and esi, 1

        mov edi, ecx
        add edi, edx
        and edi, 1

        cmp esi, edi
        jne falso

        guardarCasilla :
        mov eax, casilla
            mov tempCasilla, eax

            finIteracion :

    incJ:
        inc j
            jmp loopColumna

            finFila :
        inc i
            mov ecx, i
            jmp loopFila

            finFor :
    }

    return true;
}


bool Juego::esTablas() {
    if (fichasInsuficientes() || esAhogado(jugadorActual)) {
        return true;
    }
    return false;
}

bool Juego::hayPromocionPendiente(Casilla* casilla)
{
    Pieza* pieza = casilla->getPieza();

    if (pieza != nullptr && pieza->getTipo() == TipoPieza::PEON) {
        int filaPromocion = (pieza->getColor() == Color::BLANCO) ? 0 : 7;

        if (pieza->getLlegoAlFinal() && casilla->getFila() == filaPromocion) {
            pieza->setLlegoAlFinal(false);
            return true;
        }

        if (pieza->getLlegoAlFinal()) {
            pieza->setLlegoAlFinal(false);
        }
    }
    return false;
}

EstadoJuego Juego::obtenerEstadoJuego()
{
    return estado;
}

Tablero* Juego::obtenerTablero()
{
    return &tablero;
}


void Juego::setEstado(EstadoJuego nuevoEstado)
{
    estado = nuevoEstado;
}
