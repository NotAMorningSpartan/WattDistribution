//Tyler Kness-Miller

using namespace std;
#include <cmath>
#include <functional>
#include <iostream>
#include <boost/math/tools/roots.hpp>
#include <vector>
#include <random>
#include <utility>
namespace tools = boost::math::tools;

/// Function for the Probability Distribution of the Energy.
/// \param E to be passed to the function P(E)
/// \return The value P(E)
double fx(double E){
    double result = 0;
    result = 0.4865 * sinh(sqrt(2 * E)) * exp(-1 * E);
    return result;
}

double getRandomNumber(double lower, double upper){
    //return 1 + ( rand() % ( 100 - 1 + 1 ) );
    //return rand() % 100;
    random_device generator;
    mt19937 mt(generator());
    uniform_real_distribution<double> dist(lower, upper);
    return dist(mt);
}

pair<double, double> getRandomPoint(int max){
    return pair<double, double>(getRandomNumber(0,8), getRandomNumber(0, max));
}

bool termination_function(double min, double max){
    return abs(max - min) <= 0.00001; //1e-5 precision
}

/// Method that integrates a given function over a given range using the Trapezoid method.
/// \param a The start of the range.
/// \param b The end of the range.
/// \param n The number of sections.
/// \param f The function to be numerically integrated.
/// \return The calculated value from the integration.
double trap_int(double a, double b, int n, function<double(double x)> f){
    //Grid spacing/segment size
    double h = (b - a) / n;

    double s = f(a) + f(b);
    for(int i = 0; i < n; i++){
        s += 2 * f(a + i * h);
    }
    return (h / 2) * s;
}

int main(){
    //Verify function is working correctly.
    cout << "Verification of fx accuracy: " << to_string(trap_int(0,10,100,fx)) << endl;


    return 0;
}

