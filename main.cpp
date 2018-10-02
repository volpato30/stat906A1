#include <iostream>
#include <cmath>

#include "q2.h"
#include "q3.h"
#include "q5.h"
#include "LCRND.h"
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;


void scatter(std::vector<double> a, const std::string& output_file) {
    std::vector<double> x(&a[0], &a[999]);
    std::vector<double> y(&a[1], &a[1000]);
    plt::plot(x, y, "r.");
    plt::save(output_file);
}



int main() {
    // q1
    LinearCongruentRND lcGenerator = LinearCongruentRND(1234);
    std::vector<double> a(1000);
    for (double &i : a) {
        i = double(lcGenerator.rUnif());
    }

    // figure 1
    scatter(a, "a1q1figure1.png");

    LinearCongruentRND auxillary_lc_generator = LinearCongruentRND(13412);
    auxillary_lc_generator.setA(4124);
    auto m2 = static_cast<unsigned int>(451224867);
    auxillary_lc_generator.setM(m2);

    std::vector<double> b(1000);
    int index;
    double temp;
    for (double &i : b) {
        temp = auxillary_lc_generator.rUnif();
        index = int(ceil(temp * 1000));
        i = a[index];
    }

    // figure 2
    scatter(b, "a1q1figure2.png");

    //q2
    q2();

    //q3
    q3();

    //q5
    q5();
    return 0;
}