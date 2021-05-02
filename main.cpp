//Tyler Kness-Miller
//6 May 2021

using namespace std;
#include <cmath>
#include <functional>
#include <iostream>
#include <boost/math/tools/roots.hpp>
#include <boost/math/tools/minima.hpp>
#include <boost/math/differentiation/finite_difference.hpp>
#include <vector>
#include <random>
#include <utility>
namespace tools = boost::math::tools;

//Vector holding the random sample obtained through the rejection method.
vector<double> sample;

//The size of the sample to be generated.
int numPoints = 100000;

/// Function for the Probability Distribution of the Energy.
/// \param E to be passed to the function P(E)
/// \return The value P(E)
double fx(double E){
    return (0.4865 * sinh(sqrt(2 * E)) * exp(-1 * E));
}

/// Function that calculates the derivative of fx at a given x.
/// \param x The x coordinate that the derivative is calculated at.
/// \return The derivative of fx at x.
double dfx(double x){
    return boost::math::differentiation::finite_difference_derivative(fx, x);
}

/// A function that generates a random number within a range.
/// \param lower The lower limit of what the random number can be.
/// \param upper The upper limit of what the random number can be.
/// \return The generated random number.
double getRandomNumber(double lower, double upper){
    //return 1 + ( rand() % ( 100 - 1 + 1 ) );
    //return rand() % 100;
    random_device generator;
    mt19937 mt(generator());
    uniform_real_distribution<double> dist(lower, upper);
    return dist(mt);
}

/// A function that generates a random point.
/// \param max The max of the function.
/// \return The generated point.
pair<double, double> getRandomPoint(double max){
    return pair<double, double>(getRandomNumber(0,8), getRandomNumber(0, max));
}

/// The termination function, used with bisect.
/// \param min The minimum.
/// \param max The maximum.
/// \return A bool, signaling that the result has the desired precision and calculations are over.
bool termination_function(double min, double max){
    return abs(min - max) <= 0.00001; //1e-5 precision
}

/// A function that generates a series of points, and if they are under or equal to the curve, add them to the sample.
/// \param max The max of the function.
void generatePoints(double max){
    while (sample.size() != numPoints){
        pair<double, double> point = getRandomPoint(max);
        if(point.second <= fx(point.first)){
            sample.push_back(point.first);
        }
    }
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

/// Function that generates "bins" from the sample and outputs their values to the user.
void genBins(){
    vector<long double> bins(100,0);
    for(int i = 0; i < sample.size(); i++){
        int index = static_cast<int>((sample[i] / 8) * 100);
        bins[index]++;
    }
    for(int i = 0; i < bins.size(); i++){
        //Add tab in-between bin index and value for easy import into Excel.
        cout << i << "\t" << bins.at(i) << endl;
    }
}

/// Function that returns the local maximum of the function used in this project.
/// \return The local maximum of the function.
double genMax(){
    pair<double, double> result = tools::bisect(dfx, 0.1, 1.0, termination_function);
    return (result.first + result.second) / 2.0;
}

/// The main function.
/// \return The return code of the program.
int main(){
    srand(time(NULL));
    //Verify function is working correctly.
    cout << "Verification of fx accuracy: " << to_string(trap_int(0,10,100,fx)) << endl;

    generatePoints(genMax());

    cout << "Generated Bins: " << endl;
    genBins();

    return 0;
}

