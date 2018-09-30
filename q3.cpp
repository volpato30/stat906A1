//
// Created by rui on 29/09/18.
//

#include <iostream>
#include <cmath>
#include <chrono>
#include <cmath>

#include "q3.h"

using Clock = std::chrono::steady_clock;
using std::chrono::time_point;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using namespace std::literals::chrono_literals;

double AcceptRejectGenerator::rnd(double (*gQuasiDensity)(double), double (*gGenerate)(LinearCongruentRND *)) {
    double x, threshold, p;
    while (true) {
        x = gGenerate(&this->rUnifGenerator);
        threshold = this->_fDensity(x) / gQuasiDensity(x);
        p = this->rUnifGenerator.rUnif();
        if (p < threshold) {
            return x;
        }
    }
}

double fLinearK2(double x) {
    if (x < 0.5) {
        return 6 * x;
    } else {
        return -6 * x + 6;
    }
}

double generateLinearK2(LinearCongruentRND *pRND) {
    // inverse method to generate from generate LinearK2 distribution
    double y = pRND->rUnif();
    if (y < 0.5) {
        return sqrt(y / 2.0);
    } else {
        return 1.0 - sqrt((1.0 - y) / 2.0);
    }
}

double fLinearK3(double x) {
    if (x < 0.25) {
        return 6 * x;
    } else if(x < 0.75) {
        return 1.5;
    } else {
        return -6 * x + 6;
    }
}

double generateLinearK3(LinearCongruentRND *pRND) {
    // inverse method to generate from generate LinearK3 distribution
    double y = pRND->rUnif();
    if (y < 1.0 / 6.0) {
        return sqrt(y / 8.0 * 3);
    } else if (y < 5.0 / 6) {
        return y * 3.0 / 4 + 1.0 / 8;
    } else {
        return 1.0 - sqrt((1.0 - y) * 3.0 / 8.0);
    }
}

double fConstantK2(double x) {
    if (x < 1.0 / 4) {
        return 9.0 / 8;
    } else {
        return 1.5;
    }
}

double generateConstantK2(LinearCongruentRND *pRND) {
    // inverse method to generate from generate constantK2 distribution
    double y = pRND->rUnif();
    if (y < 0.2) {
        return y * 5 / 4;
    } else {
        return y * 15 / 16 + 1.0 / 16;
    }
}

double fConstantK3(double x) {
    if (x < 1.0 / 4) {
        return 9.0 / 8;
    } else if (x < 3.0 / 4) {
        return 1.5;
    } else {
        return 9.0 / 8;
    }
}

double generateConstantK3(LinearCongruentRND *pRND) {
    double y = pRND->rUnif();
    if (y < 3.0 / 14) {
        return y * 7 / 6;
    } else if (y < 33.0 / 42) {
        return 7.0 / 8 * (y + 1.0 / 14);
    }
    else {
        return 7.0 / 6 * (y - 1.0 / 7);
    }
}

// first define density for Beta(2, 2) distribution
double q3fDensity(double x) {
    return 6 * x * (1 - x);
}

void q3() {
    AcceptRejectGenerator ARRND = AcceptRejectGenerator(q3fDensity);

    std::cout << "q3:" << std::endl;

    time_point<Clock> start = Clock::now();
    for (int i = 0; i < 500000; i++) {
        ARRND.rnd(&fConstantK2, &generateConstantK2);
    }
    time_point<Clock> end = Clock::now();
    milliseconds diff = duration_cast<milliseconds>(end - start);
    std::cout << "constant K2:\t" << diff.count() << "ms" << std::endl;

    start = Clock::now();
    for (int i = 0; i < 500000; i++) {
        ARRND.rnd(&fConstantK3, &generateConstantK3);
    }
    end = Clock::now();
    diff = duration_cast<milliseconds>(end - start);
    std::cout << "constant K3:\t" << diff.count() << "ms" << std::endl;

    start = Clock::now();
    for (int i = 0; i < 500000; i++) {
        ARRND.rnd(&fLinearK2, &generateLinearK2);
    }
    end = Clock::now();
    diff = duration_cast<milliseconds>(end - start);
    std::cout << "Linear K2:\t" << diff.count() << "ms" << std::endl;

    start = Clock::now();
    for (int i = 0; i < 500000; i++) {
        ARRND.rnd(&fLinearK3, &generateLinearK3);
    }
    end = Clock::now();
    diff = duration_cast<milliseconds>(end - start);
    std::cout << "Linear K3:\t" << diff.count() << "ms" << std::endl;
}