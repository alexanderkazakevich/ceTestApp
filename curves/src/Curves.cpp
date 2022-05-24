/*
 * Curves.cpp
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#include "Curves.h"
#include "Utils.h"
#include <string>
#include "Circle.h"
#include "Ellipse.h"
#include "Helix.h"

const static std::vector<std::pair<CurveType, std::string>>
PAIRS_CURVE_TYPE_2_STR =
{
    {CurveType::UNKNOWN, "unknown"},
    {CurveType::CIRCLE, "circle"},
    {CurveType::ELLIPSE, "ellipse"},
    {CurveType::HELIX, "helix"},
};

const static std::map<CurveType, std::string>
MAP_CURVE_TYPE_2_STR = Utils::mapIntType2ExtType(PAIRS_CURVE_TYPE_2_STR);

const static std::map<std::string, CurveType>
MAP_STR_2_CURVE_TYPE = Utils::mapExtType2IntType(PAIRS_CURVE_TYPE_2_STR);

std::string Curves::toString(const CurveType curveTypeEnum)
{
  auto it = MAP_CURVE_TYPE_2_STR.find(curveTypeEnum);
  if (it != MAP_CURVE_TYPE_2_STR.end()) {
    return it->second;
  }
  return "unknown";
}

CurveType Curves::toType(const std::string& curveTypeStr)
{
  auto it = MAP_STR_2_CURVE_TYPE.find(curveTypeStr);
  if (it != MAP_STR_2_CURVE_TYPE.end()) {
    return it->second;
  }
  return CurveType::UNKNOWN;
}

CurveType Curves::getType(const ArgParse& argParse)
{
  if (argParse.isArgOptionExists("-t")) {

    auto curveTypeStr = argParse.getArgOptionValue("-t");

    CurveType curveType = Curves::toType(curveTypeStr);

    switch (curveType) {
    case CurveType::UNKNOWN: {
      printf("unknown curve type:%s\n", curveTypeStr.c_str());
      return curveType;
    }
    }

    return curveType;

  } else {

  }
  return CurveType::UNKNOWN;
}

static std::shared_ptr<Circle> createHelix(const ArgParse& argParse)
{
  if (argParse.isArgOptionExists("-rx") == false) {
    printf("eclipse requires \"-rx\" param\n");
    return nullptr;
  }

  auto rxStr = argParse.getArgOptionValue("-rx");
  double rx = 1.;

  if (Utils::str2(rxStr, rx) == false ) {
    printf("helix -rx: invalid value\n");
    return nullptr;
  }

  if (argParse.isArgOptionExists("-zs") == false) {
    printf("helix requires \"-zs\" param\n");
    return nullptr;
  }

  auto zsStr = argParse.getArgOptionValue("-zs");
  double zs = 1.;

  if (Utils::str2(zsStr, zs) == false ) {
    printf("eclipse -zs: invalid value\n");
    return nullptr;
  }

  std::shared_ptr<Circle> circle = std::make_shared<Helix>(rx, zs);
  return circle;
}

static std::shared_ptr<Circle> createCircle(const ArgParse& argParse)
{
  if (argParse.isArgOptionExists("-rx") == false) {
    printf("eclipse requires \"-rx\" param\n");
    return nullptr;
  }
  auto rxStr = argParse.getArgOptionValue("-rx");
  double rx = 1.;

  if (Utils::str2(rxStr, rx) == false ) {
    printf("eclipse -rx: invalid value\n");
    return nullptr;
  }

  std::shared_ptr<Circle> circle = std::make_shared<Circle>(rx);
  return circle;
}

static std::shared_ptr<Ellipse> createEllipse(const ArgParse& argParse)
{
  if (argParse.isArgOptionExists("-rx") == false) {
    printf("eclipse requires \"-rx\" param\n");
    return nullptr;
  }
  if (argParse.isArgOptionExists("-ry") == false) {
    printf("eclipse requires \"-ry\" param\n");
    return nullptr;
  }
  auto rxStr = argParse.getArgOptionValue("-rx");
  auto ryStr = argParse.getArgOptionValue("-ry");

  double rx = 1.;
  double ry = 1.;

  if (Utils::str2(rxStr, rx) == false ) {
    printf("eclipse -rx: invalid value\n");
    return nullptr;
  }

  if (Utils::str2(ryStr, ry) == false ) {
    printf("eclipse -ry: invalid value\n");
    return nullptr;
  }

  std::shared_ptr<Ellipse> ellipse = std::make_shared<Ellipse>(rx, ry);
  return ellipse;
}

std::shared_ptr<Curve> Curves::create(const ArgParse& argParse)
{
  CurveType curveType = getType(argParse);
  std::shared_ptr<Curve> curve = nullptr;
  switch (curveType) {
  case CurveType::ELLIPSE: {
    curve = createEllipse(argParse);
    break;
  }
  case CurveType::CIRCLE: {
    curve = createCircle(argParse);
    break;
  }
  case CurveType::HELIX: {
    curve = createHelix(argParse);
    break;
  }
  default: {
    break;
  }
  }
  return curve;
}

std::shared_ptr<Curve> Curves::create(CurveType curveType, std::vector<double>& params)
{
  std::shared_ptr<Curve> curve = nullptr;
  switch (curveType) {
  case CurveType::ELLIPSE: {
    if (params.size() >= 2) {
      curve = std::make_shared<Ellipse>(params[0], params[1]);
    }
    break;
  }
  case CurveType::CIRCLE: {
    if (params.size() >= 1) {
      curve = std::make_shared<Circle>(params[0]);
    }
    break;
  }
  case CurveType::HELIX: {
    if (params.size() >= 2) {
      curve = std::make_shared<Helix>(params[0], params[1]);
    }
    break;
  }
  default: {
    break;
  }
  }
  return curve;

}
