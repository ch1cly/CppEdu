//
//  5_0.cpp
//  cppedu
//
//  Created by Timur Bikbulatov on 20.10.2022.
//

#include "5_0.hpp"

void pseudomain(){
    Stack<int*> s;
    s.push(new int{42});
    cout << *s.top() <<std::endl;
    delete s.pop();
    s.kwmek();
    Stack<int> qwer;
}
