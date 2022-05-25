/*
 * Ellipse.cpp
 *
 *  Created on: 2022-05-21
 *      Author: akazakevich.nn@gmail.com
 */

#include "Ellipse.h"
#include <math.h>

Ellipse::Ellipse(double rXarg, double rYarg)
: m_rX(rXarg)
, m_rY(rYarg)
{}

void Ellipse::setParam(double tParamIn)
{
  m_xNorm = cos(tParamIn);
  m_yNorm = sin(tParamIn);
}

void Ellipse::getDerivative(std::vector<double>& derivativeOut) const
{
  derivativeOut.resize(3);
  derivativeOut[0] = m_yNorm * m_rX * (-1.);
  derivativeOut[1] = m_xNorm * m_rY;
  derivativeOut[2] = 0.;
}

void Ellipse::getPosition(std::vector<double>& positionOut) const
{
  positionOut.resize(3);
  positionOut[0] = m_xNorm * m_rX;
  positionOut[1] = m_yNorm * m_rY;
  positionOut[2] = 0.;
}

double Ellipse::getRaduis() const
{
  return m_rX;
}
