#pragma once

namespace Misc
{
bool randBool(double probabilityOfTrue = 0.5);
int randInt(int lowerBound = 0, int upperBound = RAND_MAX);
double randDouble(double lowerBound, double upperBound);
double diceThrows(double max, int dice);
double diceDistribution(double lowerBound, double upperBound, double mode, int throws);
double bound(double n, double lowerBound, double upperBound);
void shuffle(int arr[], int len);
}