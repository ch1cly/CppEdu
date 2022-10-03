//
//  3_2.cpp
//  playground
//
//  Created by Timur Bikbulatov on 02.10.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "3_2.hpp"

Matrix::Matrix(double m00,double m01,double m10,double m11){
    m[0][0]=m00;
    m[0][1]=m01;
    m[1][0]=m10;
    m[1][1]=m11;
};
Matrix::Matrix(){};

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <class t>
t sum(t q,t w){
    t r;
    r.r = q.r + w.r;
    return r;
}

template <class t>
t sum(t *q,t *w){
    t r;
    r.r = q->r + w->r;
    return r;
}


template<>//?
Matrix sum<Matrix>(Matrix q, Matrix w){
    Matrix m;
    m.m[0][0] = q.m[0][0]+w.m[0][0];
    m.m[0][1] = q.m[0][1]+w.m[0][1];
    m.m[1][0] = q.m[1][0]+w.m[1][0];
    m.m[1][1] = q.m[1][1]+w.m[1][1];
    return m;
}


template<>
Complex sum<Complex>(Complex q, Complex w){
    Complex c;
    c.r = q.r + w.r;
    c.i = q.i + w.i;
    return c;
}


template<>
char *sum<char*>(char*s1,char*s2){
    return std::strcat(s1,s2);
}


template<>
string sum<string>(string s1, string s2){
    return s1+s2;
}



template<>//?
Matrix sum<Matrix>(Matrix *q, Matrix *w){
    Matrix m;
    m.m[0][0] = q->m[0][0]+w->m[0][0];
    m.m[0][1] = q->m[0][1]+w->m[0][1];
    m.m[1][0] = q->m[1][0]+w->m[1][0];
    m.m[1][1] = q->m[1][1]+w->m[1][1];
    return m;
}


template<>
Complex sum<Complex>(Complex *q, Complex *w){
    Complex c;
    c.r = q->r + w->r;
    c.i = q->i + w->i;
    return c;
}


template<>
string sum<string>(string *s1, string *s2){
    return *s1+*s2;
}

void test1(){
    string s1("strings1"), s2("strings1");
    char c1[] = "cstring1", c2[] = "cstring2";
    Matrix m1(1,2,3,4),m2(5,6,7,8),m(0,0,0,0);
    Complex co1 = {1,-3},co2={5,2},co;
    Real r1={5},r2={13},r;
    
    cout << sum(s1,s2)<<endl;
    cout << sum(&s1,&s2)<<endl;
    cout << sum<char*>(c1,c2) <<endl;
   
    m = sum(m1, m2);
    cout << m.m[0][0] << ' ' << m.m[0][1] << ' '<< m.m[1][0] << ' '<< m.m[1][1] << endl;
    m = sum(&m1,&m2);
    cout << m.m[0][0] << ' ' << m.m[0][1] << ' '<< m.m[1][0] << ' '<< m.m[1][1] << endl;
    
    co = sum(co1,co2);
    cout << co.r << "+i" << co.i <<endl;
    co = sum(&co1,&co2);
    cout << co.r << "+i" << co.i <<endl;
    
    r = sum(r1, r2);
    cout << r.r <<endl;
    r = sum(&r1, &r2);
    cout << r.r <<endl;
}
