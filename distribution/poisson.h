#ifndef POISSON_H
#define POISSON_H

#include <cmath>

#include "../common.h"

class Poisson {
public:
    Poisson(double lambda): lambda(lambda){}
    double operator()(int x) {
        return std::pow(lambda, x) * std::exp(-lambda) / fact(x);
    }
public:
    double lambda;
};

#endif