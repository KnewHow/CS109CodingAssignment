#ifndef GEOMETRIC_H
#define GEOMETRIC_H


#include <cmath>

class Geometric {
public:
Geometric(double p): p(p){}
double operator()(int x) {
    return std::pow(1 - p, x - 1) * p;
}

public:
    double p;


};

#endif