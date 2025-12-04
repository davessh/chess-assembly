// Rey.cpp
#include "Rey.h"
#include "Casilla.h"
#include "Tablero.h"

bool Rey::movimientoValido(Casilla origen, Casilla destino, Tablero* tablero)
{
	Pieza* piezaDestino = destino.getPieza();
	Pieza* piezaOrigen = origen.getPieza();

	__asm {
		cmp piezaOrigen, 0
		je falso
		jmp noFalso
		falso :
	}
	return false;

	__asm {
	noFalso:
		cmp piezaDestino, 0
			je continua
	}

	Color colorOrigen = piezaOrigen->getColor();
	Color colorDestino = piezaDestino->getColor();
	__asm {
		mov eax, colorOrigen
		cmp eax, colorDestino
		je falso

		continua :

	}


	int difFila = abs(destino.getFila() - origen.getFila());
	int difCol = abs(destino.getColumna() - origen.getColumna());

	bool seHaMovido = origen.getPieza()->getSeHaMovido();

	__asm {
		mov eax, difFila
		cmp eax, 1
		jg enroque
		mov eax, difCol
		cmp eax, 1
		jg enroque
	}
	return true;

	__asm {
	enroque:
		mov al, seHaMovido
			cmp al, 0
			jne falso
			mov eax, difFila
			cmp eax, 0
			jne falso
			cmp difCol, 2
			jne falso
	}

	int fila = origen.getFila();
	int colOrigen = origen.getColumna();
	int colDestino = destino.getColumna();

	__asm {
		mov eax, colDestino
		cmp eax, colOrigen
		jg enroque_derecha
		jl enroque_izquierda
		jmp falso
		enroque_derecha :

	}

	Casilla* cTorre = tablero->getCasilla(fila, 7);
	Pieza* piezaTorre = cTorre->getPieza();

	__asm {
		cmp piezaTorre, 0
		je falso
	}

	TipoPieza tipo = piezaTorre->getTipo();
	bool seMovioTorre = piezaTorre->getSeHaMovido();

	__asm {

		mov eax, tipo
		cmp eax, 1
		jne falso
		movzx eax, seMovioTorre
		cmp eax, 0
		jne falso


	}

	if (tablero->getCasilla(fila, 5)->getPieza() != nullptr) return false;
	if (tablero->getCasilla(fila, 6)->getPieza() != nullptr) return false;


	for (int c = colOrigen; c <= colDestino; c++)
	{
		Pieza* rey = origen.getPieza();

		tablero->setCasilla(fila, colOrigen, nullptr);
		tablero->setCasilla(fila, c, rey);

		int i = 0, j = 0;

	asm_loop_i:
		__asm {
			cmp i, 8
			jge finFor
			mov j, 0
		}

	asm_loop_j:
		__asm {
			cmp j, 8
			jge finFila
		}

		Casilla* casilla = tablero->getCasilla(i, j);
		Pieza* p = casilla->getPieza();


		__asm {
			cmp p, 0
			je incJ_D
		}
		Color colorPieza = p->getColor();
		Color colorRey = rey->getColor();
		__asm {
			mov eax, colorPieza
			cmp eax, colorRey
			je incJ_D
		}

		if (p->movimientoValido(*casilla,
			*tablero->getCasilla(fila, c), tablero))
		{
			tablero->setCasilla(fila, c, nullptr);
			tablero->setCasilla(fila, colOrigen, rey);
			return false;
		}

		__asm {
		incJ_D:
			inc j
				jmp asm_loop_j

				finFila :
			inc i
				jmp asm_loop_i

				finFor :
		}

		tablero->setCasilla(fila, c, nullptr);
		tablero->setCasilla(fila, colOrigen, rey);
	}
	return true;


	__asm {
	enroque_izquierda:
	}

	Casilla* cTorre2 = tablero->getCasilla(fila, 0);
	Pieza* piezaTorre2 = cTorre2->getPieza();

	__asm {
		cmp piezaTorre2, 0
		je falso
	}

	TipoPieza tipo2 = piezaTorre2->getTipo();
	bool seMovioTorre2 = piezaTorre2->getSeHaMovido(); 

	__asm {

		mov eax, tipo2
		cmp eax, 1
		jne falso
		movzx eax, seMovioTorre2 
		cmp eax, 0
		jne falso


	}

	if (tablero->getCasilla(fila, 1)->getPieza() != nullptr) return false;
	if (tablero->getCasilla(fila, 2)->getPieza() != nullptr) return false;
	if (tablero->getCasilla(fila, 3)->getPieza() != nullptr) return false;

	for (int c = colOrigen; c >= colDestino; c--)
	{


		Pieza* rey = origen.getPieza();

		tablero->setCasilla(fila, colOrigen, nullptr);
		tablero->setCasilla(fila, c, rey);

		int i2 = 0, j2 = 0;

	asm_loop_i_L:
		__asm {
			cmp i2, 8
			jge finFor_L
			mov j2, 0
		}

	asm_loop_j_L:
		__asm {
			cmp j2, 8
			jge finFila_L
		}

		Casilla* casilla2 = tablero->getCasilla(i2, j2); 
		Pieza* p2 = casilla2->getPieza(); 

		__asm {
			cmp p2, 0 
			je incJ_L
		}

		Color colorPieza2 = p2->getColor(); 
		Color colorRey2 = rey->getColor(); 
		__asm {
			mov eax, colorPieza2 
			cmp eax, colorRey2 
			je incJ_L
		}

		if (p2->movimientoValido(*casilla2,
			*tablero->getCasilla(fila, c), tablero))
		{
			tablero->setCasilla(fila, c, nullptr);
			tablero->setCasilla(fila, colOrigen, rey);
			return false;
		}

		__asm {
		incJ_L:
			inc j2
				jmp asm_loop_j_L

				finFila_L :
			inc i2 
				jmp asm_loop_i_L

				finFor_L :
		}

		tablero->setCasilla(fila, c, nullptr);
		tablero->setCasilla(fila, colOrigen, rey);
	}
	return true;

	return false;
}