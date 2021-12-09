#pragma once
#include <iostream>
#include <cmath>

using namespace std;

bool randBool(double probabilityOfTrue = 0.5) {
    if (probabilityOfTrue > 1.0) probabilityOfTrue = 1.0;
    else if (probabilityOfTrue <= 0.0) probabilityOfTrue = -0.1;
    return rand() <= RAND_MAX * probabilityOfTrue;
}

int randInt(int lowerBound = 0, int upperBound = RAND_MAX) {
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

double randDouble(double lowerBound, double upperBound) {
    return ((double)rand() / (double)RAND_MAX) * (upperBound - lowerBound) + lowerBound;
}

double diceThrows(double max, int dice) {
    if (dice <= 1) return randDouble(0, max);
    else return randDouble(0, max/dice) + diceThrows(max/dice*(dice-1), dice-1);
}

double diceDistribution(double lowerBound, double upperBound, double mode, int throws) {
    bool probLower = randBool((mode - lowerBound) / (upperBound - lowerBound));
    double result = abs(diceThrows(2, throws) - 1);
    if (probLower) return mode - result * (mode - lowerBound);
    else return mode + result * (upperBound - mode);
}

double bound(double n, double lowerBound, double upperBound) {
    if (n < lowerBound) return lowerBound;
    else if (n > upperBound) return upperBound;
    else return n;
}