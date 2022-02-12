#ifndef EXPONENTIAL_H
#define EXPONENTIAL_H

#include <cmath>

class Exponential {
public:
    Exponential(double lambda): lambda(lambda){}
    double operator()(double x) {
        return lambda * std::exp(-lambda * x);
    }
public:
    double lambda;
};

#endif