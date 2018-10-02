//
// Created by rui on 30/09/18.
//

#ifndef STAT906_Q5_H
#define STAT906_Q5_H

#include <vector>

struct ExpResult{
    double mean;
    double variance;
    unsigned long n;
};


double phi(double);
ExpResult _getResult(std::vector<double>);

ExpResult antitheticMethod(unsigned long);
ExpResult crudeMethod(unsigned long);

void q5();

#endif //STAT906_Q5_H
