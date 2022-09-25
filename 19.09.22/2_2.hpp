//
//  2_2.hpp
//  playground
//
//  Created by Timur Bikbulatov on 25.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#ifndef __2_hpp
#define __2_hpp

#include <stdio.h>
#include <cmath>
#include <iostream>
#include "2_1.hpp"

using std::cout,std::endl;

class Vec1d{
public:
    double v[1]={1};
    static const int size = 1;
};

class Vec2d{
public:
    double v[2]={1,2};
    static const int size = 2;
};

class Vec3d{
public:
    double v[3]={1,2,3};
    static const int size = 3;
};


template <class T>
double norm(T o){//evlk
    double a;
    for(int i = 0; i < o.size; i++)
        a += o.v[i]*o.v[i];
    a = sqrt(a);
    cout << "norm(T o)//evlk = " << a <<endl;
    return a;
}



template <class T>
double norm(T *o){//manhat
    double a;
    for(int i = 0; i < o->size; i++)
        a += sgn(o->v[i])*o->v[i];
    
    cout << "norm(T *o)//manhat = " << a <<endl;
    return a;
}


template <>
double norm<Vec2d>(Vec2d *o);

template <>
double norm<Matrix>(Matrix o);

template <>
double norm<Matrix>(Matrix* o);

void test2();

#endif /* __2_hpp */
