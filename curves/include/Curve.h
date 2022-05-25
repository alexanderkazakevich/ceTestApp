/*
 * Curve.h
 *
 *  Created on: 2022-05-21
 *      Author: akazakevich.nn@gmail.com
 */
#include <string>
#include <vector>

#ifndef INCLUDE_CURVE_H_
#define INCLUDE_CURVE_H_

class Curve {
public:
  virtual ~Curve() = default;
  virtual void setParam(double tParamIn) = 0;
  virtual void getDerivative(std::vector<double>& derivativeOut) const = 0;
  virtual void getPosition(std::vector<double>& derivativeOut) const = 0;
  virtual double getRaduis() const = 0;
protected:
  double m_param = 0.;
};

#endif /* INCLUDE_CURVE_H_ */
