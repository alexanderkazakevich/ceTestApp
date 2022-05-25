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

#include <chrono>
#include <thread>


static void printHelp(const char *argv)
{
  printf("%s [OPTION]\n", argv);
  printf("\t[-h] Print help and exit.\n");
  printf("\t[-s] Enable silent mode.\n");
  printf("\t[-omp] Use OpenMP.\n");
  printf("\t[-omp2] Use OpenMP with another order.\n");
  printf("\t[-threads [num threads]] Separate calculation by threads.\n");
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
static void printCurvesPosAndDerivative(
    double param,
    std::vector<std::shared_ptr<CurveType>>& curves)
{
  std::vector<double> derivative;
  std::vector<double> position;
  for (auto& it: curves) {
    it->setParam(param);
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

static double sumRadiuses(const std::vector<std::shared_ptr<Circle>>& circles)
{
  double retSum = 0.;
  int arraySize = circles.size();
  for (int idx = 0; idx < arraySize; idx++) {
    retSum += circles[idx]->getRaduis();
  }
  return retSum;
}

static double sumRadiusesOMP(const std::vector<std::shared_ptr<Circle>>& circles)
{
  double retSum = 0.;
  double radius = 0.;
  int arraySize = circles.size();
#pragma omp parallel for shared(retSum)
  for (int idx = 0; idx < arraySize; idx++) {
    radius = circles[idx]->getRaduis();
#pragma omp critical
    retSum = retSum + radius;
  }
  return retSum;
}

static double sumRadiusesOMPv2(const std::vector<std::shared_ptr<Circle>>& circles)
{
  double retSum = 0.;
  int arraySize = circles.size();
  int itemSize = 4;
#pragma omp parallel for shared(retSum)
  for (int itemIdx = 0; itemIdx < itemSize; itemIdx++) {
    double lSum = 0.;
    for (int idx = itemIdx; idx < arraySize; idx+= itemSize) {
      lSum += circles[idx]->getRaduis();
    }
#pragma omp critical
    {
      retSum += lSum;
    }
  }
  return retSum;
}

static double sumRadiusesOnThreads(
    const std::vector<std::shared_ptr<Circle>>& circles,
    int threadsSize = 4)
{
  double retSum = 0.;
  int arraySize = circles.size();
  std::vector<std::shared_ptr<std::thread>> threads(threadsSize);
  std::vector<double> lSums(threadsSize);
  for (int threadIdx = 0; threadIdx < threadsSize; threadIdx++) {
    threads[threadIdx] = std::make_shared<std::thread>(
        [&circles, &threadsSize, &arraySize, threadIdx, &lSums]()
        {
          double lSum = 0.;
          for (int idx = threadIdx; idx < arraySize; idx+= threadsSize) {
            lSum += circles[idx]->getRaduis();
          }
          lSums[threadIdx] = lSum;
        }
    );
  }
  for (int threadIdx = 0; threadIdx < threadsSize; threadIdx++) {
    threads[threadIdx]->join();
    retSum += lSums[threadIdx];
  }
  return retSum;
}

int main (const int argc, const char** argv) {

  ArgParse argParser(argc, argv);

  if (argParser.isArgOptionExists("-h")) {
      printHelp(argv[0]);
      return EXIT_SUCCESS;
  }

  int randomArraySize = 0;
  int numThreads = 1;

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

  bool isSilent = argParser.isArgOptionExists("-s");
  bool useOmp = argParser.isArgOptionExists("-omp");
  bool useOmpV2 = argParser.isArgOptionExists("-omp2");
  bool useThreads = argParser.isArgOptionExists("-threads");

  if (useThreads) {
    auto numThreadsStr = argParser.getArgOptionValue("-threads");
    if (Utils::str2(numThreadsStr, numThreads) == false) {
      numThreads = 4;
    }
  }

  std::vector<std::shared_ptr<Curve>> curves;

  fillArrayWithRandomCurves(curves, 100000., randomArraySize);

  if (false == isSilent) {
    std::cout << "all curves:" << std::endl;
    printCurvesPosAndDerivative(M_PI_4, curves);
  }

  std::vector<std::shared_ptr<Circle>> circles;

  collectCircles(curves, circles);

  sortCirclesByRadius(circles);

  if (false == isSilent) {
    std::cout << "circles:" << std::endl;
    printCurvesPosAndDerivative(M_PI_4, circles);
  }

  if (false == isSilent) {
    std::cout << "circles with radiuses:" << std::endl;
    printCurvesPosAndDerivative(0., circles);
  }

  double sumOfRadiuses;

  auto t_start = std::chrono::high_resolution_clock::now();

  if (useThreads) {
    sumOfRadiuses = sumRadiusesOnThreads(circles, numThreads);
  } else if (useOmpV2) {
    sumOfRadiuses = sumRadiusesOMPv2(circles);
  } else if (useOmp) {
    sumOfRadiuses = sumRadiusesOMP(circles);
  } else {
    sumOfRadiuses = sumRadiuses(circles);
  }

  auto t_end = std::chrono::high_resolution_clock::now();

  auto timeDiff = std::chrono::duration<double, std::nano>(t_end-t_start).count();

  timeDiff /= circles.size();
  std::cout << "sum of Radiuses of circles: " << sumOfRadiuses << std::endl;
  std::cout << "count of circles: " << circles.size() << std::endl;
  std::cout << "time per circle: " << timeDiff << " ns" << std::endl;

  return EXIT_SUCCESS;
}
