/*
 * main.cpp
 *
 *  Created on: 2022-05-22
 *      Author: akazakevich.nn@gmail.com
 */

#include "ArgParse.h"
#include "Curves.h"
#include "Utils.h"
#include <iostream>
#include <memory>
#include <math.h>

static void printHelp(const char *argv)
{
  printf("%s [OPTION]\n", argv);
  printf("\t[-h] Print help and exit.\n");
  printf("\t<-t> <circle|ellipse|helix>\n");
  printf("\t<-rx> <radius along the x-axis>.\n");
  printf("\t<-ry> <radius along the y-axis> applicable only for ellipse.\n");
  printf("\t<-sz> <step along the z-axis>. applicable only for helix\n");
  printf("\t<-p> <parameter which will be multiplied by Pi (3.14159...) and used as angle>.\n");
};

int main (const int argc, const char** argv) {

  ArgParse argParser(argc, argv);

  if (argParser.isArgOptionExists("-h")) {
      printHelp(argv[0]);
      return EXIT_SUCCESS;
  }

  if (argParser.isArgOptionExists("-p") == false) {
    printf("\"-p\" parameter is required\n");
    printHelp(argv[0]);
    return EXIT_FAILURE;
  }

  double param;
  auto paramStr = argParser.getArgOptionValue("-p");

  if(Utils::str2(paramStr, param) == false) {
    printf("\"-p\" parameter \"%s\" is invalid\n", paramStr.c_str());
    printHelp(argv[0]);
    return EXIT_FAILURE;
  }

  param *= M_PI;

  std::shared_ptr<Curve> curve = Curves::create(argParser);

  if (nullptr != curve) {
    std::vector<double> derivative;
    std::vector<double> position;
    curve->setParam(param);
    curve->getPosition(position);
    curve->getDerivative(derivative);

    std::cout << "  position: {" << Utils::toStreamBuf(position, 20, 7).str() << "};" << std::endl;
    std::cout << "derivative: {" << Utils::toStreamBuf(derivative, 20, 7).str() << "};" << std::endl;
  } else {
    printHelp(argv[0]);
  }

  return 0;
}
