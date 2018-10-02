//
// Created by rui on 30/09/18.
//
#include <iostream>
#include <cmath>
#include <random>

#include "q5.h"

using std::default_random_engine;
using std::uniform_real_distribution;

double phi(double x) {
    return 2 * x / (1 + 1.0 / 3 * pow(x, 4));
}

double computeVariance(std::vector<double> x_array) {
    double mean = 0, variance = 0;
    unsigned long number_of_experiments = x_array.size();
    for (double &x : x_array) {
        mean += x;
    }
    mean = mean / number_of_experiments;
    for (double &x : x_array) {
        variance += pow(x - mean, 2);
    }

    variance = variance / (number_of_experiments - 1);
    return variance;
}

ExpResult _getResult(std::vector<double> r_unif_array) {
    double mean = 0, variance = 0;
    unsigned long n = r_unif_array.size();
    for (double &x : r_unif_array) {
        mean += phi(x);
    }
    mean = mean / n;
    for (double &x : r_unif_array) {
        variance += pow(phi(x) - mean, 2);
    }

    variance = variance / (n - 1);
    ExpResult result = {
            mean,
            variance,
            n};
    return result;
}

ExpResult antitheticMethod(unsigned long n) {
    std::vector<double> r_unif_array(n);
    //mercene twister generator
    std::mt19937 rng;
    rng.seed(std::random_device()());
    uniform_real_distribution<double> rGen(0.0, 1.0);
    double temp;
    for (int i = 0; i < int(n / 2); i++) {
        temp = rGen(rng);
        r_unif_array[2 * i] = 2 * temp;
        r_unif_array[2 * i + 1] = 2 * (1 - temp);
    }
    return _getResult(r_unif_array);
}

ExpResult crudeMethod(unsigned long n) {
    std::vector<double> r_unif_array(n);
    std::mt19937 rng;
    rng.seed(std::random_device()());
    uniform_real_distribution<double> rGen(0.0, 1.0);
    for (double &x : r_unif_array) {
        x = 2 * rGen(rng);
    }
    return _getResult(r_unif_array);
};

void q5() {
    unsigned long n = 100;
    unsigned long number_of_experiments = 10000;
    std::vector<double> crudeMC(number_of_experiments);
    std::vector<double> antitheticMC(number_of_experiments);

    for (int i=0; i < int(number_of_experiments); i++) {
        crudeMC[i] = crudeMethod(n).mean;
        antitheticMC[i] = antitheticMethod(n).mean;
    }

    double c_mean = 0, a_mean = 0;

    std::cout << "q5:" << std::endl;

    std::cout << c_mean / number_of_experiments << std::endl;
    std::cout << a_mean / number_of_experiments << std::endl;

    std::cout << "number of experiments:\t" << number_of_experiments << std::endl;
    std::cout << "Crude MC variance:\t" << computeVariance(crudeMC) << std::endl;
    std::cout << "Antithetic MC variance:\t" << computeVariance(antitheticMC) << std::endl;

    n = 1000000;
    auto result1 = crudeMethod(n);
    auto result2 = antitheticMethod(n);
    std::cout << "sample size:\t" << n << std::endl;
    std::cout << "Crude MC:\t" << "mean:\t" << result1.mean << "\tvariance:\t" << result1.variance << std::endl;
    std::cout << "Antithetic MC:\t" << "mean:\t" << result2.mean << "\tvariance:\t" << result2.variance << std::endl;
}