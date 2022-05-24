/*
 * Circle.h
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#ifndef CURVES_INCLUDE_CIRCLE_H_
#define CURVES_INCLUDE_CIRCLE_H_

#include "Ellipse.h"

class Circle : public Ellipse {
public:
  Circle(double rArg);
  virtual ~Circle() = default;
  double getRadii();
};

#endif /* CURVES_INCLUDE_CIRCLE_H_ */
