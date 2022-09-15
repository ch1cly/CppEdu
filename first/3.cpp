//
//  3.cpp
//  playground
//
//  Created by Timur Bikbulatov on 05.09.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "3.hpp"

void z3::test2_0(){
    Qeq<double> d(1,-1,-3);
    d.solve();
    cout << endl;
}
void z3::test2_1(){
    Qeq<double> d(0,0,0);
    d.solve();
    cout << endl;
}
void z3::test2_2(){
    Qeq<double> d(1,0,0);
    d.solve();
    cout << endl;
}
void z3::test2_3(){
    Qeq<double> d(0,1,0);
    d.solve();
    cout << endl;
}
void z3::test2_4(){
    Qeq<double> d(0,0,1);
    d.solve();
    cout << endl;
}
void z3::test2_5(){
    Qeq<double> d(1,1,0);
    d.solve();
    cout << endl;
}

void z3::test2_6(){
    Qeq<double> d(1,0,1);
    d.solve();
    cout << endl;
}

void z3::test2_7(){
    Qeq<double> d(0,1,1);
    d.solve();
    cout << endl;
}

void z3::test2_8(){
    Qeq<double> d(1,1,1);
    d.solve();
    cout << endl;
}

void z3::test2_9(){
    Qeq<double> d(-1,6,-5);
    d.solve();
    cout << endl;
}

void z3::test2_10(){
    Qeq<double> d(6,3,3);
    d.solve();
    cout << endl;
}

void z3::test2_11(){
    Qeq<double> d(1324,1234,120);
    d.solve();
    cout << endl;
}


void fz3(){
    using namespace z3;
    test2_0();
    test2_1();
    test2_2();
    test2_3();
    test2_4();
    test2_5();
    test2_6();
    test2_7();
    test2_8();
    test2_9();
    test2_10();
    test2_11();
}
