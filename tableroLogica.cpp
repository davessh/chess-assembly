#include "tableroLogica.h"
#include <iostream>

tableroLogica::tableroLogica(int valor){
    datos = valor;
}

void tableroLogica::setValor(int valor){
    datos = valor;
}

int tableroLogica::getValor() const {
    return datos;
    //prueba
}
