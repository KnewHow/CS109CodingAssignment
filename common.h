#ifndef COMMON_H
#define COMMON_H

#include <cmath>

inline long fact(int n){
    long r = 1;
    while(n > 0) {
        r *= n;
        --n;
    }
    return r;
}

inline long combination(int n, int r) {
    return fact(n) / (fact(r) * fact(n - r));
}


#endif