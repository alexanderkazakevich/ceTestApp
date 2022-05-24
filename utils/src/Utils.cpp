/*
 * Utils.cpp
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#include "Utils.h"

double Utils::fRand(double minRandm, double maxRand)
{
  double f = (double)rand() / RAND_MAX;
  return minRandm + f * (maxRand - minRandm);
}

