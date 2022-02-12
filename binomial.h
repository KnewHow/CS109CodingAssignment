#ifndef BINOMIAL_H
#define BINOMIAL_H

#include "common.h"


class Binomial {
public:
    Binomial(int n, double p): n(n), p(p){}
    double operator()(int x) {
        return 1.0 * combination(n, x) * std::pow(p, x) * std::pow(1 - p, n - x);
    }
public:
    int n;
    double p;

};

#endif