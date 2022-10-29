//
// Created by Timur Bikbulatov on 29.10.2022.
//

#ifndef CPPEDU_Z6_2_H
#define CPPEDU_Z6_2_H
#include "z6_0.h"

template<unsigned alpha, unsigned beta>
struct monomial2d {
    static const unsigned value =
            factorial<alpha+beta+2>::value
            / factorial<alpha>::value / factorial<beta>::value;
};

void exec3();

#endif //CPPEDU_Z6_2_H
