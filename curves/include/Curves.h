/*
 * Curves.h
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#ifndef CURVES_SRC_CURVES_H_
#define CURVES_SRC_CURVES_H_

#include <cstdint>
#include <memory>
#include <string>

#include "ArgParse.h"
#include "Curve.h"

enum class CurveType : int8_t {
  UNKNOWN = 0,
  ELLIPSE = 1,
  CIRCLE = 2,
  HELIX = 3,
};

class Curves {
public:
  static std::string toString(const CurveType curveTypeEnum);
  static CurveType toType(const std::string& curveTypeStr);
  static std::shared_ptr<Curve> create(const ArgParse& argParse);
  static std::shared_ptr<Curve> create(CurveType curveTypeEnum, std::vector<double>& params);

private:
  static CurveType getType(const ArgParse& argParse);
};

#endif /* CURVES_SRC_CURVES_H_ */
