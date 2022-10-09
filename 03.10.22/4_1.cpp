//
//  4_1.cpp
//  cppedu
//
//  Created by Timur Bikbulatov on 09.10.2022.
//

#include "4_1.hpp"
#include <iostream>
using namespace::std;

void test(){
    queue<int> q,w;
    if(q.empty())
        cout << "empty1" << endl;
    
    q.push(1);
    q.push(2);
    w = q;
    if(!q.empty())
        cout << "size = "  << q.size() << endl;
    q.pop();
    q.pop();
    q.push(3);
    q.push(4);
    q.push(5);
    cout << q.front() << ' ' << q.back() << endl;
    q.swap(w);
    int i = w.emplace(6);
    cout << "int i = " << i << endl;
    
    cout << w.front() << ' ' << w.back() << endl;
    
    
    
}
