//
// Created by Timur Bikbulatov on 02.11.2022.
//

#include "z7_0.h"
#include <iostream>

using std::cout,std::endl;

void execz70(){
    cout << is_prime0<12>::value << endl;
    cout << prime_at<9>::value << endl;
    //========================
    typedef primes<20>::type p20;
    static_assert(prime_at<5>::value==13,"p5 == 13");
    static_assert(prime_at<9>::value==13,"p9 == 29");

    //typedef  primes<20>::type p20;
    //p20 p;
    //p = 5;

}