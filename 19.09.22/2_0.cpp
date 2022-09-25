//
//  2_0.cpp
//  playground
//
//  Created by Timur Bikbulatov on 25.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "2_0.hpp"

using std::cout, std::endl;

template <class T>
T do_something(T x){
    return (++x);
}

template<>
double do_something<double>(double x){
    return (x/2);
}

void c1(){
    cout << endl << "c1" << endl;
    auto i1 = do_something(3);
    auto i2 = do_something(3.0);
}

void whatami(int x){
    cout << x << " типа int" << endl;
}

void whatami(long int x){
    cout << x << "long int" << endl;
}

void c2(){
    cout << endl << "c2" << endl;
    whatami(5);
    //whatami(5.0); //too ambigious
}

template <class T>
void whatami(T *x){
    cout << x << " указатель" << endl;
}

void c3(){
    cout << endl << "c3" << endl;
    int i = 5;
    whatami(i);
    whatami(&i);
}

template <class T>
void whatami(T &&x){
    cout << "что-то на непонятном" << endl;
}

class C{};

void c4(){
    cout << endl << "c4" << endl;
    C c;
    whatami(c);
    whatami(&c);
}

void whatami(double x){
    cout << x << "типа int" << endl;
}

void c5(){
    cout << endl << "c5" << endl;
    int i = 5;
    float x = 4.2;
    whatami(i);
    whatami(x);
}

void whatami(...){
    cout << "что угодно" << endl;
}

void zad(){
    c1();
    c2();
    c3();
    c4();
    c5();
}
