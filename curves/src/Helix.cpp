/*
 * Helix.cpp
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#include "Helix.h"
#include <math.h>

const static double M_1_PI_2 = M_1_PI * 0.5;

Helix::Helix(double rArg, double zStepArg)
: Circle(rArg)
, m_zStep(zStepArg * M_1_PI_2)
{}

void Helix::setParam(double tParamIn)
{
  Ellipse::setParam(tParamIn);
  m_z = m_zStep * tParamIn;
}

void Helix::getDerivative(std::vector<double>& derivativeOut) const
{
  Ellipse::getDerivative(derivativeOut);
  derivativeOut[2] = m_zStep;
}

void Helix::getPosition(std::vector<double>& positionOut) const
{
  Ellipse::getPosition(positionOut);
  positionOut[2] = m_z;

}
