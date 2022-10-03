//
//  3_1.cpp
//  playground
//
//  Created by Timur Bikbulatov on 02.10.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "3_1.hpp"


/*
 В первую очередь хотелось бы уделить внимание проблеме разрешимости.
 Зачастую может получиться так, что компилятор не может понять, какую именно функцию использовать.
 Так например, это может происходить, когда в "иерархии" сразу две специализации функции подходят на роль
 */

template <class t>
void ab(t * q){
    cout << "void ab(t *q)" << endl;
}

void ab(int a){
    cout << "void ab(int a)" << endl;
}

void ab(float a){
    cout << "void ab(double a)" << endl;
}

void g1(){
    //ab(5.0);//Call to 'ab' is ambiguous
}


/*
 на уровне преобразований в аргумента с различного рода классификаторами. по ссылке, константной и тп

*/

template <class t>
void abb(t const q){//эта функция конфликтует с остальными
    cout << "void abb(t const q)" << endl;
}

template <class t>
void abb(t const& q){//эта только с нижней
    cout << "void abb(t const& q)" << endl;
}

template <class t>
void abb(t & q){
    cout << "void abb(t & q)" << endl;
}



void g3(){
    int a;
    //abb(a);//Call to 'abb' is ambiguous
}


/*
 Неявные случаи бывают, когда компилятор не может решить, как передавать параметр
 */


template <class t>
void abc(t q){
    cout << "void abc(t q)" << endl;
}

template <class t>
void abc(t && q){
    cout << "void abc(t && q)" << endl;
}

void g4(){
    int a;
    //abc(a);//Call to 'abc' is ambiguous
}


/*
 Также могут быть проблемы с возвращаемым типом, когда из-за возвращаемого значения непонятно, какую функцию применять
 */


template <class t>
t ab(t q){
    cout << "t ab(t q)" << endl;
    return q;
}

template <class t>
void ab(t q){
    cout << "void ab(t q)" << endl;
}

void g2(){
  // ab('b');//Call to 'ab' is ambiguous
}


/*
    Проблемы с временной ссылкой. То есть при вызове abd создается временный объект, который не может быть передан в качестве аргумента
 */
/*
template<class t>
t const &abd(t &a, t &b) {
    cout << "&&&" << endl;
    return (b < a ? a : b);
}

template<class t>
t &abd(t &a, t &b,t &c) {
    cout << "The 1st template is used" << endl;
    return abd(abd(a,b),c); //No matching function for call to 'abd'
}

void g5(){
    int a,a1,a2;
    abd(a,a2,a2);
}
*/


void ff(){
    g4();
}
