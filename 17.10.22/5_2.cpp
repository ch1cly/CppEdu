//
//  5_2.cpp
//  cppedu
//
//  Created by Timur Bikbulatov on 20.10.2022.
//

#include "5_2.hpp"
#include <string>
#include <iostream>

void zad5_2(){
    using std::make_pair;
    using is = Stack<pair<int,char>>;//использование псевдонима
    is isp;
    for(int i = 1; i <10; ++i)
        isp.push(make_pair(0+i,'a'+i));
    cout << isp.top().first << isp.top().second  << endl;
    isp.pop();
    cout << isp.top().first << isp.top().second  << endl;
    cout << (isp.empty() ? "empty" : "not empty") << endl;
    isp.printOn(cout);
    cout << isp << endl;
    for(int i = 1; i <9; ++i)
        isp.pop();
    cout << (isp.empty() ? "empty" : "not empty") << endl;
    
    //ps.printOn(cout); //not ok!
};
