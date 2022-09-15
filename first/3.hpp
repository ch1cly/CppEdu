#ifndef __hpp
#define __hpp

#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

namespace z3{
    void test2_0();
    void test2_1();
    void test2_2();
    void test2_3();
    void test2_4();
    void test2_5();
    void test2_6();
    void test2_7();
    void test2_8();
    void test2_9();
    void test2_10();
    void test2_11();
};

void fz3();

constexpr double eps = 1e-6;

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <class t>
class Qeq{
    t a,b,c;
public:
    Qeq(t a1,t b1,t c1);
    void solve();
};

template <class t>
double sqrt(const t fg){
    double n = fg / 2.0;
    double lstX = 0.0;
    while(n != lstX){
        lstX = n;
        n = (n + fg/n) / 2.0;
    }
    return n;
}

template <class t>
bool isz(t f){
    return sgn(f)*f < eps;
}

template <class t>
Qeq<t>::Qeq(t a1,t b1,t c1):a(a1),b(b1),c(c1){};


template <class t>
void Qeq<t>:: solve(){
    if (isz(a) && isz(b) && !isz(c)) {
        cout << "корней нет" << endl;
        return;
    }
    else if (isz(a) && isz(b) && isz(c)) {
        cout << "уравнение имеет бесконечное множество решений" << endl;
        return;
    }
    else if (isz(a) && !isz(b)){
        cout << "x1 = x2 = " << -c/b << endl;
        return;
    }
    else if (isz(a) && !isz(b)){
        cout << "x1 = x2 = " << -c/b << endl;
        return;
    }
    else if (!isz(a) && !isz(b) && isz(c)){
        cout << "x1 = " << 0 << endl;
        cout << "x2 = " << -b/a << endl;
        return;
    }

    t dis = b*b - 4*a*c;
  
    if (isz(dis)){
        cout << "x1 = x2 = " << -b/(2*a) << endl;
        return;
    }
    else if(dis < 0){
        double d = sqrt(-dis);
        cout << "x1 = " << -b/(2*a) << " + i" << d/(2*a) << endl;
        cout << "x2 = " << -b/(2*a) << " - i" << d/(2*a) << endl;
        return;
    }
    else if(dis > 0){
        double d = sqrt(dis);
        cout << "x1 = " << (-b+d)/(2*a) << endl;
        cout << "x2 = " << (-b-d)/(2*a) << endl;
        return;
    }
    return;
}



#endif /* __hpp */
