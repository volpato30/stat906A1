#include <utility>

//
// Created by rui on 29/09/18.
//

#ifndef STAT906_Q3_H
#define STAT906_Q3_H

#include <functional>
#include "LCRND.h"
// define an interface for acceptance rejection method

class AcceptRejectGenerator{
private:
    std::function<double(double)> _fDensity;
    LinearCongruentRND rUnifGenerator;
public:
    double rnd(double (*gQuasiDensity)(double), double (*gGenerate)(LinearCongruentRND *pRND));
    explicit AcceptRejectGenerator(std::function<double(double)> fDensity): _fDensity(std::move(fDensity)) {
        rUnifGenerator = LinearCongruentRND(1234);
    }
};

double fLinearK2(double x);
double generateLinearK2(LinearCongruentRND *);
double fLinearK3(double x);
double generateLinearK3(LinearCongruentRND *);

double fConstantK2(double x);
double generateConstantK2(LinearCongruentRND *);
double fConstantK3(double x);
double generateConstantK3(LinearCongruentRND *);
void q3();

#endif //STAT906_Q3_H
