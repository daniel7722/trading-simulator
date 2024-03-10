//
// Created by Daniel Huang on 2024/3/10.
//
#include <iostream>
#include <chrono>
#include <random>
#include <future>
#include <vector>
#include "../include/Pricing.h"

Pricing::Pricing(double mu, double sigma) : drift(mu), volatility(sigma) {}


double Pricing::A(double stockPrice, double time) const {
    return drift * stockPrice;
}


double Pricing::B(double stockPrice, double time) const {
    static std::mt19937 generator(std::random_device{}());
    static std::normal_distribution<double> distribution(0, 1);
    double dW = distribution(generator);
    return volatility * stockPrice * dW;
}

double
Pricing::monteCarloOptionPrice(double initialPrice, double strikePrice, double maturity, int numPaths, int numThreads) {
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    int pathsPerThread = numPaths / numThreads;
    std::vector<std::future<double>> futures;

    for (int i = 0; i < numThreads; i++) {
        futures.push_back(
                std::async(std::launch::async, [this, initialPrice, strikePrice, maturity, pathsPerThread]() {
                    double sumPayoff = 0.0;
                    for (int j = 0; j < pathsPerThread; j++) {
                        double stockPrice = initialPrice;
                        double dt = maturity / 365.0;
                        for (double t = 0; t < maturity; t += dt) {
                            stockPrice += A(stockPrice, t) * dt + B(stockPrice, t) * std::sqrt(dt);
                        }
                        double payoff = std::max(0.0, stockPrice - strikePrice);
                        sumPayoff += payoff;
                    }
                    return sumPayoff;
                }));
    }


    double totalPayoff = 0.0;
    for (auto &future: futures) {
        totalPayoff += future.get();
    }

    double optionPrice = totalPayoff / numPaths;
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
    return optionPrice;
}

