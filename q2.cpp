//
// Created by rui on 9/28/18.
//
#include <iostream>
#include <cmath>
#include <chrono>
#include <math.h>

#include "q2.h"
#include "LCRND.h"

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

const double C = 8 / (pow(M_PI, 3.0) + 8);

double method1() {
    // composite with inverse method
    auto lcGenerator = LinearCongruentRND(123);
    double temp;

    if (lcGenerator.rUnif() < C) {
        temp = lcGenerator.rUnif();
        return (acos(temp));
    } else {
        temp = lcGenerator.rUnif();
        return (M_PI / 2.0 * pow(temp, 1.0 / 3.0));
    }
}

double fDensity(double x) {
    return (C * (3 * pow(x, 2.0) + sin(x)));
}

double method2() {
    // acceptance rejection method
    auto lcGenerator = LinearCongruentRND(2431);
    double max_f = fDensity(M_PI / 2.0);
    double temp;
    double acceptThreshold;
    while (true) {
        temp = lcGenerator.rUnif() * M_PI / 2.0;
        acceptThreshold = fDensity(temp) / (max_f);
        if (lcGenerator.rUnif() < acceptThreshold) {
            return temp;
        }
    }
}

void q2() {
    std::cout << "q2:" << std::endl;
    time_point<Clock> start = Clock::now();
    for (int i = 0; i < 500000; i++) {
        method1();
    }
    time_point<Clock> end = Clock::now();
    milliseconds diff = duration_cast<milliseconds>(end - start);
    std::cout << "composition with inverse method:\t" << diff.count() << "ms" << std::endl;

    start = Clock::now();
    for (int i = 0; i < 500000; i++) {
        method2();
    }
    end = Clock::now();
    diff = duration_cast<milliseconds>(end - start);
    std::cout << "acceptance rejection method:\t" << diff.count() << "ms" << std::endl;
}
