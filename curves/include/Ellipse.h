/*
 * Ellipse.h
 *
 *  Created on: 2022-05-21
 *      Author: akazakevich.nn@gmail.com
 */

#ifndef INCLUDE_ELLIPSE_H_
#define INCLUDE_ELLIPSE_H_

#include "Curve.h"
#include "ArgParse.h"

class Ellipse : public Curve {
public:
  Ellipse(double rXarg, double rYarg);
  virtual ~Ellipse() = default;
  virtual void setParam(double tParamIn) override;
  virtual void getDerivative(std::vector<double>& derivativeOut) const override;
  virtual void getPosition(std::vector<double>& derivativeOut) const override;

protected:
  double m_rX;
  double m_rY;
  double m_xNorm = 1.0;
  double m_yNorm = 0.f;
};

#endif /* INCLUDE_ELLIPSE_H_ */
