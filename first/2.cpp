//
//  2.cpp
//  playground
//
//  Created by Timur Bikbulatov on 05.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "2.hpp"


using std::string;
typedef string tst;
typedef double tst2;


void z2::test2_0(){
    cout << endl << "string" << endl;
    tst s[] = {"ab","bb","cb","db","eb","fb"};
    void (*p)(tst s);
    p = showWtxt<tst>;
    iter(s,6,p);
}

void z2::test2_1(){
    cout << endl << "string" << endl;
    tst s[] = {"ab","bb","cb","db","eb","fb"};
    void (*p)(tst s);
    p = show<tst>;
    iter(s,6,p);
}

void z2::test2_2(){
    cout << endl << "string" << endl;
    tst s[] = {"ab","bb","cb","db","eb","fb"};
    void (*p)(tst s);
    p = show<tst>;
    iter(s,2,p);
}

void z2::test2_3(){
    cout << endl << "double" << endl;
    double s[] = {1.1,1.2,1.3,1.4,1.6,1.7,1.8};
    void (*p)(double s);
    p = show<double>;
    iter(s,8,p);
}

void z2::test2_4(){
    cout << endl << "double" << endl;
    double s[] = {1.1,1.2,1.3,1.4,1.6,1.7,1.8};
    void (*p)(double s);
    p = show<double>;
    iter(s,0,p);
}

void z2::test2_5(){
    cout << endl << "int" << endl;
    int s[] = {1,2,3,4,5,6,7};
    void (*p)(int s);
    p = showWtxt<int>;
    iter(s,7,p);
}

void fz2(){
    using namespace z2;
    test2_0();
    test2_1();
    test2_2();
    test2_3();
    test2_4();
    test2_5();
}
