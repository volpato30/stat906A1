//
// Created by rui on 9/28/18.
//

#ifndef STAT906_LCRND_H
#define STAT906_LCRND_H

#include <cmath>

class RND{
protected:
    unsigned int seed_;
public:
    virtual float rUnif() = 0;
    void setSeed(unsigned int seed = 0){
        seed_ = seed;
    }
};

class LinearCongruentRND: public RND {
private:
    int a_, c_;
    unsigned int m_;
public:
    explicit LinearCongruentRND(unsigned int seed = 0): m_(2147483399), a_(40692), c_(3) {
        seed_ = seed;
    }

    float rUnif() override {
        seed_ = (a_ * seed_ + c_) % m_;
        return float(seed_) / m_;
    }

    void setM(unsigned m){
        m_ = m;
    }

    void setA(int a){
        a_ = a;
    }
};

#endif //STAT906_LCRND_H
