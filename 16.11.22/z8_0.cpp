//
// Created by Timur Bikbulatov on 22.11.2022.
//

#include "z8_0.h"
#include <iostream>



void zad8(){
    const unsigned N = 2;
    const double a = 2.3, b = 5.2;
    const double bi = binom<N,N>(a, b); // вычисление интеграла std::cout << bi << '\n';
    std::cout << bi << std::endl;
    return;
}