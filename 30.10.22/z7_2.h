//
// Created by Timur Bikbulatov on 06.11.2022.
//

#ifndef DOMASHKAE_Z7_2_H
#define DOMASHKAE_Z7_2_H

#include <type_traits>

void exec7_2();

template<unsigned N>
struct factorial{
    static const unsigned value = N * factorial<N-1>::value;
};

template<>
struct factorial<0>{
    static const unsigned value = 1;
};
//==================================================

template<int N, typename T>
typename std::enable_if<(N>0),T>::type meta_pow(T x){
    return (1/metapow<-N>(x));
}

template<int N, typename T>
typename std::enable_if<(N==0),T>::type meta_pow(T x){
    return (1);
}
template<int N, typename T>
typename std::enable_if<(N==1),T>::type meta_pow(T x){
    return (x);
}
template<int N, typename T>
typename std::enable_if<(N>0) && (N%2==0),T>::type meta_pow(T x){
    T p = meta_pow<N / 2>(x);
    return (p*p);
}
template<int N, typename T>
typename std::enable_if<(N>0)&&(N%2==1),T>::type meta_pow(T x){
    return (metapow<N-1>(x) * x);
}

template<class T>
inline constexpr T rpow(const T base, unsigned const exponent)
{
    // (parentheses not required in next line)
    return (exponent == 0) ? 1 : (base * rpow(base, exponent-1));
}

#endif //DOMASHKAE_Z7_2_H
