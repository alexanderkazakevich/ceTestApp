/*
 * Circle.cpp
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#include "Circle.h"

Circle::Circle(double rArg)
: Ellipse(rArg, rArg)
{}

double Circle::getRadii()
{
  return m_rX;
}
