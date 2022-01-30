#pragma once

namespace Misc
{
bool randBool(double probabilityOfTrue = 0.5);
int randInt(int lowerBound = 0, int upperBound = RAND_MAX);
double randDouble(double lowerBound, double upperBound);
double diceThrows(double max, int dice);    //used by diceDistribution

//returns a random number between lower and upperBound
//the probability distribution is the same as that of the specified amount of dice throws
//the mode can also be manipulated
double diceDistribution(double lowerBound, double upperBound, double mode, int throws);
double bound(double n, double lowerBound, double upperBound);   //if n is outside the specified bounds it returns either lower or upperBound
void shuffle(int arr[], int len);   //shuffles an array of integers
}