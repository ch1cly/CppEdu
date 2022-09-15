#ifndef __hpp
#define __hpp

#include <stdio.h>
// Prakticheskoe zadanie nomer 1
template <class t1>
void swap(t1&a,t1&b){
    t1 temp = a;
    a = b;
    b = temp;
}

template <class t1>
t1 max(t1&a,t1&b){
    if (a > b)
        return a;
    else if (b > a)
        return b;
    else if (a == b)
        return b;
    return b;
    //return (b < a ? a : b);
}

template <class t1>
t1 min(t1&a,t1&b){
    if (a < b)
        return a;
    else if (b < a)
        return b;
    else if (a == b)
        return b;
    return b;
}

#endif /* __hpp */
