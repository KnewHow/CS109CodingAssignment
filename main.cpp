#include <iostream>
#include <random>
#include <cmath>
#include <map>
#include <iomanip>

#include "distribution/binomial.h"
#include "distribution/geometric.h"
#include "distribution/negative_binomial.h"
#include "distribution/poisson.h"
#include "distribution/exponential.h"


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
void simulate_geometric_test();
void simulate_negative_binomial_test();
void simulate_poisson_test();
void simulate_exponential_test();


int main(int, char**) {
    //simulate_bernoulli_test();
    //simulate_binomial_test();
    //simulate_geometric_test();
    //simulate_negative_binomial_test();
    //simulate_poisson_test();
    simulate_exponential_test();
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

void simulate_geometric_test() {
    Geometric g(0.03);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<int, double> hits;
    for(int i = 0; i < 10000; ++i) {
        std::uniform_real_distribution<> dis(1, 60);
        int sample = std::round(dis(gen));
        double sample_r = g(sample);
        hits[sample] += sample_r;
    }

    for(auto p: hits) {
        std::cout << std::setw(2) << p.first << " " << std::string(p.second * 10, '*') << std::endl;
    }

}


void simulate_negative_binomial_test() {
    NegativeBinomial nb(5, 0.03);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<int, double> hits;

    for(int i = 0; i < 10000; ++i) {
        std::uniform_real_distribution<> dis(0, 40);
        int sample = std::round(dis(gen));
        double sample_r = nb(sample);
        if(hits.find(sample) != hits.end()) {
            hits[sample] += sample_r;
        } else {
            hits[sample] = sample_r;
        }
        
    }

    for(auto p: hits) {
        int str_length = (int)(p.second * 600.0);
        if(str_length < 0) str_length = 0;
        std::cout << std::setw(2) << p.first << " " << std::string(str_length, '*') << std::endl;
    }

}



void simulate_poisson_test() {
    Poisson p(3.1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<int, double> hits;
    for(int i = 0; i < 10000; ++i) {
        std::uniform_real_distribution<> dis(0, 20);
        int sample = std::round(dis(gen));
        double sample_r = p(sample);
        hits[sample] += sample_r;
    }

    for(auto p: hits) {
        int str_length = p.second;
        if(str_length < 0) str_length = 0;
        std::cout << std::setw(2) << p.first << " " << std::string(str_length, '*') << std::endl;
    }
}


void simulate_exponential_test() {
    Exponential e(3.1);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::map<double, double> hits;
    std::vector<double> indices(21);
    int i = 0;
    for(double a = 0.0; a <= 2.0; a += 0.1) {
        hits[a] = 0.0;
        indices[i++] = a;
    }

    for(int i = 0; i < 10000; ++i) {
        std::uniform_real_distribution<> dis(0, 20);
        int index = std::round(dis(gen));
        if(index < 0) index = 0;
        if(index > 20) index = 20;
        double key = indices[index];
        double sample_r = e(key);
        hits[key] += sample_r;
     
    }

    for(auto p: hits) {
        int str_length = p.second / 15;
        if(str_length < 0) str_length = 0;
        std::cout << std::fixed << std::setprecision(1) << p.first << " " << std::string(str_length, '*') << std::endl;
    }

}

