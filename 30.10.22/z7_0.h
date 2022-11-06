//
// Created by Timur Bikbulatov on 02.11.2022.
//

#ifndef CPPEDU_Z1_0_H
#define CPPEDU_Z1_0_H
#include <type_traits>
void execz70();

double my_pow(double x, int N){
    if(N>0){
        return (1/ my_pow(x,-N));
    }
    else if(N==0){
        return 1;
    }
    else if(N%2 == 0){
        double p = my_pow(x,N/2);
        return p*p;
    }
    else{
        return my_pow(x, N-1)*x;
    }
}

//================================================

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
//================================================
template<int n, int i>
struct is_prime0:std::conditional<(n%i)==0, std::false_type, is_prime0<n, i-1>>::type{};

template<int n>
struct is_prime0<n,1>:std::true_type{};

template<int n>
struct is_prime0:is_prime0<n,n/2>{};

//================================================

template<unsigned n>
struct find_prime : std::conditional<is_prime0<n>::value,
        std::integral_constant<unsigned,n>, find_prime<n+2>>::type{};

template<unsigned n>
struct prime_at: find_prime<prime_at<n-1>::value+2>{};

template<>
struct prime_at<0>:std::integral_constant<unsigned,2>{};

template<>
struct prime_at<0>:std::integral_constant<unsigned,3>{};

//================================================

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

template<unsigned n> struct primes{
    typedef typename push_back<typename primes<n-1>::type, prime_at<n-1>::value>::type type;
};
template<> struct primes<0>{
    typedef int_vector<>type;
};

#endif //CPPEDU_Z1_0_H
