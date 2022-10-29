//
// Created by Timur Bikbulatov on 29.10.2022.
//

#ifndef CPPEDU_Z6_1_H
#define CPPEDU_Z6_1_H


template<unsigned N>
class fib{
public:
    static const unsigned val = fib<N-1>::val + fib<N-2>::val;
};

template<>
class fib<0>{
public:
    static const unsigned val = 0;
};

template<>
class fib<1>{
public:
    static const unsigned val = 1;
};

void exec1();



#endif //CPPEDU_Z6_1_H
