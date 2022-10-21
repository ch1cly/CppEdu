//
//  5_1.cpp
//  cppedu
//
//  Created by Timur Bikbulatov on 20.10.2022.
//

#include "5_1.hpp"
#include <iostream>
using namespace::std;

void test51(){
    queue<int*> q,w;
    if(q.empty())
        cout << "empty1" << endl;
    
    q.push(new int{1});
    q.push(new int{2});
    w = q;
    if(!q.empty())
        cout << "size = "  << q.size() << endl;
    delete q.pop();
    delete q.pop();
    q.push(new int{3});
    q.push(new int{4});
    q.push(new int{5});
    cout << *q.front() << ' ' << *q.back() << endl;
    q.swap(w);
    int* i = w.emplace(new int{6});
    cout << "int i = " << *i << endl;
    
    cout << *w.front() << ' ' << *w.back() << endl;
}
