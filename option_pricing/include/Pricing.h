//
// Created by Daniel Huang on 2024/3/10.
//

#ifndef PRICING_H
#define PRICING_H
class Pricing {

public:
    Pricing(double mu, double sigma);

    double A(double stockPrice, double time) const;

    double B(double stockPrice, double time) const;

    double monteCarloOptionPrice(double initialPrice, double strikePrice, double maturity, int numPaths,
                                 int numThreads);
private:
    double drift;
    double volatility;
};
#endif
