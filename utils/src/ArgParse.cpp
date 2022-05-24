/*
 * ArgParse.cpp
 *
 *  Created on: 2022-05-24
 *      Author: akazakevich.nn@gmail.com
 */

#include "ArgParse.h"

ArgParse::ArgParse(int argc, const char *argv[]) {
  for (int i = 1; i < argc; ++i) {
    m_arguments.push_back(std::string(argv[i]));
  }
}

const std::string ArgParse::getArgOptionValue(const std::string &option) const {
  auto it = std::find(m_arguments.begin(), m_arguments.end(), option);
  if (it != m_arguments.end() && ++it != m_arguments.end()) {
    return *it;
  }
  return "";
}

bool ArgParse::isArgOptionExists(const std::string &option) const {
  return std::find(m_arguments.begin(),
      m_arguments.end(),
      option) != m_arguments.end();
}

