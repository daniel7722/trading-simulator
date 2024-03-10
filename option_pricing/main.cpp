#include <iostream>
#include "include/Pricing.h"

int main() {
    double mu = 0.05;
    double sigma = 0.2;
    double initialPrice = 100.0;
    double strikePrice = 110.0;
    double maturity = 1.0;
    int numPaths = 1000000;
    int numThreads = 2000;

    Pricing model(mu, sigma);
    double optionPrice = model.monteCarloOptionPrice(initialPrice, strikePrice, maturity, numPaths, numThreads);

    std::cout << "Option price using Monte Carlo simulation with " << numThreads << " threads: " << optionPrice << std::endl;
    return 0;
}
