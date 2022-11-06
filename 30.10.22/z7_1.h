//
// Created by Timur Bikbulatov on 06.11.2022.
//

#ifndef DOMASHKAE_Z7_1_H
#define DOMASHKAE_Z7_1_H
#include <type_traits>


void exec7_1();

template<unsigned N>
class fib{
public:
    static const unsigned value = fib<N-1>::value + fib<N-2>::value;
};

template<>
class fib<0>{
public:
    static const unsigned value = 0;
};

template<>
class fib<1>{
public:
    static const unsigned value = 1;
};


template<int...I> struct int_vector{};
template<class IntVector, int i> struct push_back;


template<int...I, int i>
struct push_back<int_vector<I...>,i>{
    typedef int_vector<I...,i> type;
};

template<class IntVector, int n> struct at;

template<int i,int...I, int n>
struct at<int_vector<i,I...>,n>:at<int_vector<I...>,n-1>{};

template<int i, int...I>
struct at<int_vector<i,I...>,0>:std::integral_constant<int,i>{};

template<unsigned n> struct fibss{
    typedef typename push_back<typename fibss<n-1>::type, fib<n-1>::value>::type type;
};
template<> struct fibss<0>{
    typedef int_vector<>type;
};

#endif //DOMASHKAE_Z7_1_H
