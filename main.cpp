#include <iostream>
#include <random>
#include <cmath>
#include <map>
#include <iomanip>

#include "binomial.h"

double gen_random(double begin, double end) {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_real_distribution<> dis(begin, end);
    return dis(rng);
}

double gen_random() {
    return gen_random(0.0, 1.0);
}


int simulate_bernoulli(double p);
void simulate_bernoulli_test();

void simulate_binomial_test();

std::vector<double> simulate_geometric(double p = 0.03);
void simulate_geometric_test();


std::vector<double> simulate_negative_binomial(int r = 5, double p = 0.03); // has some bug
void simulate_negative_binomial_test();

std::vector<double> simulate_poisson(double lamda = 3.1);
void simulate_poisson_test();


int main(int, char**) {
    //simulate_bernoulli_test();
    simulate_binomial_test();
    //simulate_geometric_test();
    // simulate_negative_binomial_test();
    //simulate_poisson_test();
    std::cout << "\nHello, world!\n";
}

int simulate_bernoulli(double p) {
    if(gen_random() > p) {
        return 1;
    } else {
        return 0;
    }
}

void simulate_bernoulli_test() {
    int zero = 0;
    int one = 0;
    for(int i = 0; i < 100000; ++i) {
        if(simulate_bernoulli(0.4) == 1)
            ++one;
        else
            ++zero;
    }
    std::cout << "zero times: " << zero << ", one times: " << one << std::endl;
}



void simulate_binomial_test() {
    std::random_device rd;
    std::mt19937 gen(rd());
    Binomial b(20, 0.4);
    std::map<int, double> hits;
    for(int i = 0; i < 10000; ++i) {
        std::uniform_real_distribution<> dis(0, 21);
        int sample = std::round(dis(gen));
        double sample_r = b(sample);
        hits[sample] += sample_r;
    }

    for(auto p: hits) {
        std::cout << std::setw(2) << p.first << " " << std::string(p.second, '*') << std::endl;
    }

}

std::vector<double> simulate_geometric(double p) {
    int n = 500;
    std::vector<double> geometric(n);
    for(int i = 0; i < n; ++i) {
        geometric[i] = std::pow(1 - p, i) * p;
    }
    return geometric;
}

void simulate_geometric_test() {
    std::vector<double> geometric = simulate_geometric();
    for(int i = 0; i < geometric.size(); ++i) {
        int starCount = 1000 * geometric[i];
        for(int j = 0; j < starCount; ++j) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

std::vector<double> simulate_negative_binomial(int r, double p) { // it's seem has some bug
    int n = 50;
    std::vector<double> nb(n);
    for(int k = r; k < r + n; ++k) {
        nb[k - r] = combination(k - 1, r - 1) * std::pow(p, r) * std::pow(1 - p, k - r);
    }
    return nb;
}

void simulate_negative_binomial_test() {
     std::vector<double> nb = simulate_negative_binomial();
    for(int i = 0; i < nb.size(); ++i) {
        int starCount = 20 * nb[i];
        for(int j = 0; j < starCount; ++j) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }
}

std::vector<double> simulate_poisson(double lamda) {
    int sample = 20;
    std::vector<double> r(sample);
    for(int x = 0; x < sample; ++x) {
        r[x] = std::pow(lamda, x) * std::exp(-lamda) / fact(x);
    }
    return r;
}

void simulate_poisson_test() {
    std::vector<double> pd = simulate_poisson();
    for(int i = 0; i < pd.size(); ++i) {
        int starCount = 100 * pd[i];
        for(int j = 0; j < starCount; ++j) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

}

