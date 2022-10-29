//
// Created by Timur Bikbulatov on 29.10.2022.
//

#ifndef CPPEDU_Z6_0_H
#define CPPEDU_Z6_0_H
#include <iostream>

void exec();

template<unsigned N>
struct factorial{
    static const unsigned value = N * factorial<N-1>::value;
};

template<>
struct factorial<0>{
    static const unsigned value = 1;
};


template<unsigned N, unsigned K>
struct C{
    static const unsigned value =
            factorial<N>::value / factorial<K>::value/ factorial<N-K>::value;
};

template <unsigned alpha, unsigned beta, unsigned gamma>
struct monomial_3d{
    static const unsigned value = factorial<alpha +beta+gamma+3>::value / \
            (factorial<alpha>::value * factorial<beta>::value\
             * factorial<gamma>::value);
};


template<class IT>
struct get_value_type {
    typedef class IT::value_type type;
};

template<class T>
struct get_value_type<T*> {
    typedef T type;
};

template<class T>
struct get_value_type<const T*> {
    typedef T type;
};

template<class IT, class T>
typename  get_value_type<IT>::type my_accumulate(
        IT f, IT l, T init)
{
    typename get_value_type<IT>::type result = init;
    for(;f!=l;++f)
        result += *f;
    return result;
}
/*
template<>
struct get_value_type<new_iterator> {
    typedef typename new_iterator::data_type type; };
*/


#endif //CPPEDU_Z6_0_H

