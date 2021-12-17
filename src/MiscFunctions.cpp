#include <iostream>
#include <cmath>
#include "MiscFunctions.hpp"

bool Misc::randBool(double probabilityOfTrue) {
    if (probabilityOfTrue > 1.0) probabilityOfTrue = 1.0;
    else if (probabilityOfTrue <= 0.0) probabilityOfTrue = -0.1;
    return rand() <= RAND_MAX * probabilityOfTrue;
}

int Misc::randInt(int lowerBound, int upperBound) {
    if (lowerBound > upperBound) return upperBound;
    return rand() % (upperBound - lowerBound + 1) + lowerBound;
}

double Misc::randDouble(double lowerBound, double upperBound) {
    if (lowerBound > upperBound) return upperBound;
    return ((double)rand() / (double)RAND_MAX) * (upperBound - lowerBound) + lowerBound;
}

double Misc::diceThrows(double max, int dice) {
    if (dice <= 1) return randDouble(0, max);
    else return randDouble(0, max/dice) + diceThrows(max/dice*(dice-1), dice-1);
}

double Misc::diceDistribution(double lowerBound, double upperBound, double mode, int throws) {
    if (upperBound <= lowerBound) return upperBound;
    bool probLower = randBool((mode - lowerBound) / (upperBound - lowerBound));
    double result = diceThrows(2, throws) - 1;
    if (result < 0) result = -result;
    if (probLower) return mode - result * (mode - lowerBound);
    else return mode + result * (upperBound - mode);
}

double Misc::bound(double n, double lowerBound, double upperBound) {
    if (n < lowerBound) return lowerBound;
    else if (n > upperBound) return upperBound;
    else return n;
}

void Misc::shuffle(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        int pick = Misc::randInt(i, len-1);
        if (pick != i) {
            int tmp = arr[i];
            arr[i] = arr[pick];
            arr[pick] = tmp;
        }
    }
}