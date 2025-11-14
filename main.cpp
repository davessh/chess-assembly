#include <iostream>
#include "tableroLogica.h"

int main(){
    tableroLogica obj(10);
    std::cout << obj.getValor() << std::endl;

    obj.setValor(24);
    std::cout << obj.getValor() << std::endl;

    return 0;

}