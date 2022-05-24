/*
 * Helix.h
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#ifndef CURVES_INCLUDE_HELIX_H_
#define CURVES_INCLUDE_HELIX_H_

#include "Circle.h"

class Helix : public Circle {
public:
  /**
   * Creates Helix object
   * @param rArg     : radius of helix
   * @param zStepArg : distance between two points on the helix with param T and (T + 2. * M_PI)
   */
  Helix(double rArg, double zStepArg);
  virtual ~Helix() = default;
  virtual void setParam(double tParamIn) override;
  virtual void getDerivative(std::vector<double>& derivativeOut) const override;
  virtual void getPosition(std::vector<double>& derivativeOut) const override;
protected:
  /*
   * it will be multiplied by (1/(2. * M_PI))
   * so no need to multiply by (1/(2. * M_PI)) when calculate z coordinate
   */
  double m_zStep;
  double m_z = 0.;
};

#endif /* CURVES_INCLUDE_HELIX_H_ */
