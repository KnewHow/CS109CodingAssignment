#ifndef NEGATIVE_BINOMIAL_H
#define NEGATIVE_BINOMIAL_H

#include "../common.h"

class NegativeBinomial {
public:
    NegativeBinomial(int r, double p): r(r), p(p){}
    double operator()(int x) {
        return combination(x + r - 1, r - 1) * std::pow(p, r) * std::pow(1 - p, x);
    }
public:
    int r;
    double p;
};

#endif