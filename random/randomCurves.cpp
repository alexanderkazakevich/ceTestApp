/*
 * randomCurves.cpp
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#include <math.h>

#include "Curves.h"
#include "Helix.h"
#include "Utils.h"

/*
 * https://habr.com/ru/company/intel/blog/85273/
 */

static void printHelp(const char *argv)
{
  printf("%s [OPTION]\n", argv);
  printf("\t[-h] Print help and exit.\n");
  printf("\t<-n> <number of curves>\n");
};

static void fillArrayWithRandomCurves(
    std::vector<std::shared_ptr<Curve>>& curves,
    double maxRadius,
    int requiredArraySize)
{
  std::shared_ptr<Curve> itemCurve;

  std::vector<double> params(2);
  do {
    CurveType curveType = static_cast<CurveType> ((rand() % toInt(CurveType::HELIX)) + 1);
    params[0] = Utils::fRand(0., maxRadius);
    params[1] = Utils::fRand(0., maxRadius);
    if ((params[0] > 0.) && (params[1] > 0.)){
      itemCurve = Curves::create(curveType, params);
    }
    if (itemCurve != nullptr) {
      curves.push_back(itemCurve);
    }
  } while (curves.size() < requiredArraySize);

}

template <typename CurveType>
static void printCurvesPosAndDerivative(std::vector<std::shared_ptr<CurveType>>& curves)
{
  std::vector<double> derivative;
  std::vector<double> position;
  for (auto& it: curves) {
    it->setParam(M_PI_4);
    it->getPosition(position);
    it->getDerivative(derivative);

    std::cout.width(10);
    std::cout << typeid(*it).name() << ":";
    std::cout << " position: {" << Utils::toStreamBuf(position, 20, 7).str() << "};";
    std::cout << " derivative: {" << Utils::toStreamBuf(derivative, 20, 7).str() << "};" << std::endl;
  }
}

static void collectCircles(
    std::vector<std::shared_ptr<Curve>>& curves,
    std::vector<std::shared_ptr<Circle>>& circles) {
  circles.clear();
  for (auto& it : curves) {
    if (typeid(*it) == typeid(Circle)) {
      std::shared_ptr<Circle> circleItem = std::dynamic_pointer_cast<Circle>(it);
      circles.push_back(circleItem);
    }
  }
}

static void sortCirclesByRadius(std::vector<std::shared_ptr<Circle>>& circles)
{
  std::sort(
      circles.begin(), circles.end(),
      []
       (
          const std::shared_ptr<Circle>& circleL ,
          const std::shared_ptr<Circle>& circleR
       )
       {
          return circleL->getRadii() <= circleR->getRadii();
       }
  );

}

int main (const int argc, const char** argv) {

  ArgParse argParser(argc, argv);

  if (argParser.isArgOptionExists("-h")) {
      printHelp(argv[0]);
      return EXIT_SUCCESS;
  }

  int randomArraySize = 0;

  if (argParser.isArgOptionExists("-n") == false) {
    printf("\"-n\" <number of curves> is required\n");
    printHelp(argv[0]);
    return EXIT_FAILURE;
  }

  auto strRandomArraySize = argParser.getArgOptionValue("-n");
  if (Utils::str2(strRandomArraySize, randomArraySize) == false) {
    printf("\"-n\" invalid value\n");
    printHelp(argv[0]);
    return EXIT_FAILURE;
  }

  std::vector<std::shared_ptr<Curve>> curves;

  fillArrayWithRandomCurves(curves, 100000., randomArraySize);

  std::cout << "all curves:" << std::endl;

  printCurvesPosAndDerivative(curves);

  std::vector<std::shared_ptr<Circle>> circles;

  collectCircles(curves, circles);

  sortCirclesByRadius(circles);

  std::cout << "circles:" << std::endl;

  printCurvesPosAndDerivative(circles);

  return EXIT_SUCCESS;
}
