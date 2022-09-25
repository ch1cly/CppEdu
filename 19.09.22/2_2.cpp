//
//  2_2.cpp
//  playground
//
//  Created by Timur Bikbulatov on 25.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "2_2.hpp"


template <>
double norm<Vec2d>(Vec2d *o){//pifag
    double a = sgn(o->v[0]) * o->v[0] > sgn(o->v[1]) * o->v[1] ? o->v[0] : o->v[1];
    cout << "(Vec2d *o)//pifag " << a <<endl;
    return a;
}

template <>
double norm<Matrix>(Matrix o){
    double a = o.m[0][0]+o.m[0][1]+o.m[1][0]+o.m[1][1];
    cout << "norm<Matrix>(Matrix o) = " << a <<endl;
    return a;
}

template <>
double norm<Matrix>(Matrix* o){
    double a = sqrt(o->m[0][0]*o->m[0][0] + o->m[0][1]*o->m[0][1] + o->m[1][0]*o->m[1][0] + o->m[1][1]*o->m[1][1]);
    cout << "norm<Matrix>(Matrix* o) " << a <<endl;
    return a;
}

void test2(){
    Matrix m(1,2,3,4);
    Vec1d v1;
    Vec2d v2;
    Vec3d v3;
    norm(m);
    norm(&m);
    norm(v1);
    norm(&v1);
    norm(v3);
    norm(&v3);
    norm(v2);
    norm(&v2);
}
