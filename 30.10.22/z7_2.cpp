//
// Created by Timur Bikbulatov on 06.11.2022.
//

#include "z7_2.h"
#define N 9
//сначала просходит ассиптотическое схождение
//затем переполнение в N=10

#include <cmath>
#include <iostream>
const unsigned Nf  = factorial<N>::value;
const unsigned Nn  = rpow<unsigned long int>(N,N);
//const unsigned En  = pow(M_E,-N);


void exec7_2(){
    using std::cout,std::endl;
    const double En = pow(M_E,-N);
    const double den = sqrt(2*M_PI*N);
    printf("l = %f ~= %f = r", Nf/den, Nn*En);

}