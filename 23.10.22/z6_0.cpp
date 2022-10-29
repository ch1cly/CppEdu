//
// Created by Timur Bikbulatov on 29.10.2022.
//

#include "z6_0.h"
#include <numeric>
const unsigned f5 = factorial<5>::value;
const unsigned b52 = C<5,2>::value;
const unsigned int111 = monomial_3d<1,1,1>::value;
void exec(){
    using std::cout, std::endl;
    int arr[f5];
    cout << f5 << endl;
    int arr1[b52];
    cout << b52 << endl;
    int arr2[int111];
    cout << int111 << endl;
    double a[3] = { 1.23, 2.34, 3.45 };
    double sum = std::accumulate(a, a + 3, 0);
    cout << sum << endl;
    sum = std::accumulate(a, a + 3, 0.);
    cout << sum << endl;
}