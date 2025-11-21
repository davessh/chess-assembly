#include "Juego.h"
#include <QDebug>

Juego::Juego()
    : tablero(), jugadorActual(Color::BLANCO), estado(EstadoJuego::JUGANDO)
{
}

void Juego::iniciar()
{
    tablero.inicializar();
    tablero.mostrarTablero();
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

    if (pieza == nullptr) return false;
    if (pieza->getColor() != jugadorActual) return false;

    Pieza* piezaDestino = destino->getPieza();
    if (piezaDestino != nullptr && piezaDestino->getColor() == jugadorActual) {
        return false;
    }

    if (!pieza->movimientoValido(*origen, *destino, &tablero) || generaJacke(origen, destino))
        return false;

    if (pieza->getTipo() == TipoPieza::REY &&
        abs(destino->getColumna() - origen->getColumna()) == 2)
    {
        int fila = origen->getFila();

        if (destino->getColumna() == 6)
        {
            Pieza* torre = tablero.getCasilla(fila, 7)->getPieza();
            tablero.setCasilla(fila, 5, torre);
            tablero.setCasilla(fila, 7, nullptr);
            torre->setMovido(true);
        }

        if (destino->getColumna() == 2)
        {
            Pieza* torre = tablero.getCasilla(fila, 0)->getPieza();
            tablero.setCasilla(fila, 3, torre);
            tablero.setCasilla(fila, 0, nullptr);
            torre->setMovido(true);
        }
    }

    if (pieza->getTipo() == TipoPieza::PEON &&
        destino->getPieza() == nullptr &&
        abs(destino->getColumna() - origen->getColumna()) == 1)
    {
        Pieza* peonCapturado =
            tablero.getCasilla(origen->getFila(), destino->getColumna())->getPieza();

        if (peonCapturado != nullptr &&
            peonCapturado->getTipo() == TipoPieza::PEON)
        {
            tablero.setCasilla(origen->getFila(), destino->getColumna(), nullptr);
        }
    }
    
    tablero.setCasilla(destino->getFila(), destino->getColumna(), pieza);
    tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

    pieza->setMovido(true);

    //es promoción de peon
    if (pieza->getTipo() == TipoPieza::PEON) {
        int filaPromocion = (pieza->getColor() == Color::BLANCO) ? 0 : 7;
        if (destino->getFila() == filaPromocion) {
            pieza->setLlegoAlFinal(true);
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Pieza* p = tablero.getCasilla(i, j)->getPieza();
            if (p != nullptr &&
                p->getTipo() == TipoPieza::PEON &&
                p->getColor() == jugadorActual &&
                p != pieza)
            {
                p->setAlPaso(false); 
            }
        }
    }


    cambiarJugador();

    if (verificarJacke()) {
        if (esJaqueMate(jugadorActual))
            estado = EstadoJuego::JAQUE_MATE;
        else
            estado = EstadoJuego::JAQUE;
    }
    else if (esTablas()) {
        estado = EstadoJuego::TABLAS;
    }
    else {
		estado = EstadoJuego::JUGANDO;
    }
    return true;
}


bool Juego::verificarJacke()
{
    Casilla* casillaRey = tablero.buscarRey(jugadorActual);

    if (casillaRey == nullptr) {
        return false;
    }

    return hayJacke(*casillaRey);
}

bool Juego::hayJacke(Casilla direccionRey)
{

    if (direccionRey.getPieza() == nullptr) {
        return false;
    }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
            Casilla* casilla = tablero.getCasilla(i, j);
            if (pieza != nullptr && pieza->getColor() != direccionRey.getPieza()->getColor())
            {
                if (pieza->movimientoValido(*casilla, direccionRey, &tablero))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Juego::cambiarJugador()
{
    if (jugadorActual == Color::BLANCO) {
        jugadorActual = Color::NEGRO;
    } else {
        jugadorActual = Color::BLANCO;
    }
}

Color Juego::obtenerJugadorActual()
{
    return jugadorActual;
}



bool Juego::esJaqueMate(Color turno)
{
    if (!verificarJacke()) {
        return false; 
    }
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
            Casilla* casillaPieza = tablero.getCasilla(i, j);
            if (!pieza || pieza->getColor() != turno) continue;

            for (int movi = 0; movi < 8; movi++)
            {
                for (int movj = 0; movj < 8; movj++)
                {
                    Casilla* casilla = tablero.getCasilla(movi, movj);
                    if (pieza->movimientoValido(*casillaPieza, *casilla, &tablero)
                    && !generaJacke(casillaPieza, casilla))
                    {
                        return false; 
                    }
                }
            }

        }
    }
    return true;
}

bool Juego::generaJacke(Casilla* origen, Casilla* destino)
{
    Pieza* piezaCapturada = destino->getPieza();
    Pieza* piezaMovida = origen->getPieza();

    tablero.setCasilla(destino->getFila(), destino->getColumna(), origen->getPieza());
    tablero.setCasilla(origen->getFila(), origen->getColumna(), nullptr);

    Casilla* casillaRey = tablero.buscarRey(jugadorActual);

    bool enJaque = false;
    if (casillaRey != nullptr) {
        enJaque = hayJacke(*casillaRey);
    }

    tablero.setCasilla(destino->getFila(), destino->getColumna(), piezaCapturada);
    tablero.setCasilla(origen->getFila(), origen->getColumna(), piezaMovida);

    return enJaque;
}

bool Juego::esAhogado(Color turno)
{
    Casilla* rey = tablero.buscarRey(turno);

    if (rey == nullptr) return false;

    if (!hayMovimientosDisponibles(turno) && !hayJacke(*rey)) {
        return true;
    }

    return false;
}



bool Juego::hayMovimientosDisponibles(Color turno) {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            Pieza* pieza = tablero.getCasilla(i, j)->getPieza();
            Casilla* casillaPieza = tablero.getCasilla(i, j);
            if (!pieza || pieza->getColor() != turno) continue;
            for (int movi = 0; movi < 8; movi++)
            {
                for (int movj = 0; movj < 8; movj++)
                {
                    Casilla* casilla = tablero.getCasilla(movi, movj);
                    if (pieza->movimientoValido(*casillaPieza, *casilla, &tablero)
                    && !generaJacke(casillaPieza, casilla))
                    {
                        return true; 
                    }
                }
            }
        }
    }
	return false;

}


bool Juego::fichasInsuficientes() {
    Casilla* tempCasilla = nullptr;
    int cantAlfiles = 0;
    int cantCaballos = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            Casilla* casilla = tablero.getCasilla(i, j);
            Pieza* pieza = casilla->getPieza();

            if (pieza == nullptr) {
                continue;
            }

            if (pieza->getTipo() == TipoPieza::REY ||
                pieza->getTipo() == TipoPieza::CABALLO ||
                pieza->getTipo() == TipoPieza::ALFIL) {

                if (pieza->getTipo() == TipoPieza::CABALLO) {
                    cantCaballos += 1;
                    if (cantCaballos > 1) return false;
                }

                if (pieza->getTipo() == TipoPieza::ALFIL) {
                    cantAlfiles += 1;

                    if (cantAlfiles > 2) return false;

                    if (tempCasilla != nullptr) {
                        if (tempCasilla->getPieza()->getColor() == pieza->getColor()) {
                            return false;
                        }

                        int filaTemp = tempCasilla->getFila();
                        int colTemp = tempCasilla->getColumna();
                        int filaActual = casilla->getFila();
                        int colActual = casilla->getColumna();

                        if (!((((filaTemp + colTemp) % 2 == 0) && ((filaActual + colActual) % 2 == 0))
                            || (((filaTemp + colTemp) % 2 != 0) && ((filaActual + colActual) % 2 != 0)))) {
                            return false;
                        }
                    }

                    tempCasilla = casilla;
                }
            }
            else {
                return false;
            }
        }
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

        //Verifica AMBAS condiciones: la bandera Y la posición actual
        if (pieza->getLlegoAlFinal() && casilla->getFila() == filaPromocion) {
            pieza->setLlegoAlFinal(false);
            return true;
        }

        // Si no está en la fila correcta pero tenía la bandera, la reseteas
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
