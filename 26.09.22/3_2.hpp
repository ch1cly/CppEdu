//
//  3_2.hpp
//  playground
//
//  Created by Timur Bikbulatov on 02.10.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#ifndef __2_hpp
#define __2_hpp

#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>

using std::cout, std::endl, std::string;

class Complex{
public:
    double r,i;
};

class Matrix{
public:
    Matrix();
    Matrix(double m00,double m01,double m10,double m11);
    double m[2][2];
};

class Real{
public:
    double r;
};


void test1();
#endif /* __2_hpp */
