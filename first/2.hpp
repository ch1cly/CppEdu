
#ifndef __hpp
#define __hpp

#include <stdio.h>
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::endl;


// Prakticheskoe zadanie nomer 2
namespace z2{
    void test2_0();
    void test2_1();
    void test2_2();
    void test2_3();
    void test2_4();
    void test2_5();
};

void fz2();

template <class t1>
void show(t1 o){
    cout << o << ' ';
};

template <class t1>
void showWtxt(t1 o){
    cout << "elem: " << o << endl;
};

template <class t1,class t2,class t3>
void iter(t1 *m,t2 l,t3 (*f)(t1 o)){
    for(int i = 0; i < l; i++)
        (*f)(m[i]);
    cout << endl;
};

#endif /* __hpp */
