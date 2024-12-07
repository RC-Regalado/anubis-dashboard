#ifndef __UTILS_HPP_
#define __UTILS_HPP_
#include <string>

#define debug(x) std::cout << "DEBUG: " << x << std::endl

inline bool strcontains(const std::string &str, const char *substr) {
  return str.find(substr) != std::string::npos;
}

#endif
