/*
 * ArgParse.h
 *
 *  Created on: 2022-05-22
 *      Author: akazakevich.nn@gmail.com
 */

#pragma once

#include <algorithm>
#include <string>
#include <vector>

class ArgParse {
public:
  ArgParse(int argc, const char *argv[]);

  const std::string getArgOptionValue(const std::string &option) const;

  bool isArgOptionExists(const std::string &option) const;

private:
  std::vector<std::string> m_arguments;
};
