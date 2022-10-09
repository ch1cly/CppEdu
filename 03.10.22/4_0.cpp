//
//  4_0.cpp
//  playground
//
//  Created by Timur Bikbulatov on 09.10.2022.
//  Copyright © 2022 Timur Bikbulatov. All rights reserved.
//

#include "4_0.hpp"
#include <string>
#include <iostream>

void zad4_0(){
    
    using is = Stack<int>;//использование псевдонима
    is ints;
    Stack<string> ss;
    ints.push(5);

    cout << ints.top() << endl;
    ss.push("hello");
    cout << ss.top() << endl;
    ss.pop();
    Stack<int> msi1[10];//такой же типа как все
    is msi2[20];
    Stack<float*> FloatPtrStack;
    Stack<Stack<int>> intStackStack;//настолько гибкое использование типов
    
    
    Stack<pair<int,int>>ps;
    ps.push({2,4});
    ps.push({3,6});
    cout << ps.top().first<<endl;//так нормально
    cout << ps.top().second<<endl;
    
    ints.push(43);
    ints.push(23);
    ints.printOn(cout);//для инта определено
    
    //ps.printOn(cout); //not ok!
};
