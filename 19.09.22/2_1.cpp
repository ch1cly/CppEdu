//
//  2_1.cpp
//  playground
//
//  Created by Timur Bikbulatov on 25.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "2_1.hpp"

using std::cout,std::endl;

Matrix::Matrix(double m00,double m01,double m10,double m11){
    m[0][0]=m00;
    m[0][1]=m01;
    m[1][0]=m10;
    m[1][1]=m11;
};

template <>
double absol<Matrix>(Matrix o){
    return (o.m[0][0]*o.m[1][1] - o.m[0][1]*o.m[1][0]);
}

template <>
double absol<Complex>(Complex o){
    return (o.r*o.r + o.i*o.i);
}

void test1(){
    Real r = {5};
    Complex c = {8,-6};
    Matrix m(1,2,3,4);
    cout << "Real = " << absol(r) <<endl;
    cout << "Complex = " << absol(c) <<endl;
    cout << "Matrix = " << absol(m) <<endl;
}

