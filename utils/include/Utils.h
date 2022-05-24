/*
 * Utils.h
 *
 *  Created on: 2022-05-22
 *      Author: akazakevich.nn@gmail.com
 */

#ifndef UTILS_INCLUDE_UTILS_H_
#define UTILS_INCLUDE_UTILS_H_

#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>     // std::cout
#include <iterator>
#include <map>
#include <sstream>      // std::istringstream
#include <string>
#include <vector>

class Utils {
public:
  template <typename OutType>
  static bool str2(std::string& inStr, OutType& outValue)
  {
    std::istringstream iss(inStr);
    iss >> std::noskipws >> outValue; // noskipws considers leading whitespace invalid
    // Check the entire string was consumed and if either failbit or badbit is set
    return iss.eof() && !iss.fail();
  }

  template <typename InType>
  static std::ostringstream toStreamBuf(std::vector<InType>& inVector, int widthArg, int precisionArg)
  {
    std::ostringstream oss;
    oss << std::fixed;
    oss << std::setprecision(precisionArg);

      if (!inVector.empty())
      {
        for (auto it = inVector.begin(); it != (inVector.end()-1); it++) {
          oss.width(widthArg);
          oss << *it;
          oss << ", ";
        }
//        // Convert all but the last element to avoid a trailing ","
//        std::copy(inVector.begin(), inVector.end()-1,
//            std::ostream_iterator<InType>(oss, ", "));
//
//        // Now add the last element with no delimiter
        oss.width(widthArg);
        oss << inVector.back();
      }
      return oss;
  }

  /**
   * creates map : external type to internal type
   */
  template<typename INT_TYPE, typename EXT_TYPE>
  static std::map<EXT_TYPE, INT_TYPE> mapExtType2IntType(
          const std::vector<std::pair<INT_TYPE, EXT_TYPE>>& pairsArg)
  {
      std::map<EXT_TYPE, INT_TYPE> mapValues;
      for (auto& it : pairsArg) {
          mapValues[it.second] = it.first;
      }
      return mapValues;

  }

  /**
   * creates map : internal type to external type
   */
  template<typename INT_TYPE, typename EXT_TYPE>
  static std::map<INT_TYPE, EXT_TYPE> mapIntType2ExtType(
          const std::vector<std::pair<INT_TYPE, EXT_TYPE>>& pairsArg)
  {
      std::map<INT_TYPE, EXT_TYPE> mapValues;
      for (auto& it : pairsArg) {
          mapValues[it.first] = it.second;
      }
      return mapValues;
  }

  static double fRand(double minRandm, double maxRand);
};

template<typename ENUM, typename U = typename std::underlying_type<ENUM>::type>
inline constexpr U toInt(ENUM const value) {
    return static_cast<U>(value);
}

#endif /* UTILS_INCLUDE_UTILS_H_ */
