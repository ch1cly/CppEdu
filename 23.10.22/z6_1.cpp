//
// Created by Timur Bikbulatov on 29.10.2022.
//

#include "z6_1.h"
#include <iostream>

#define N 21
#if N < 0
#define N 0
#endif

const int f6 = fib<N>::val;

void exec1(){
    using std::cout, std::endl;
    cout << f6 << endl;
}