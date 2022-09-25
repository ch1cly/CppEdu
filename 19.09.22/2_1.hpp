//
//  2_1.hpp
//  playground
//
//  Created by Timur Bikbulatov on 25.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#ifndef __1_hpp
#define __1_hpp

#include <stdio.h>
#include <iostream>

class Complex{
public:
    double r,i;
};

class Matrix{
public:
    Matrix(double m00,double m01,double m10,double m11);
    double m[2][2];
};

class Real{
public:
    double r;
};




template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <class T>
double absol(T o){
    return sgn(o.r) * o.r;
}

template <>
double absol<Matrix>(Matrix o);

template <>
double absol<Complex>(Complex o);


void test1();

#endif /* __1_hpp */
