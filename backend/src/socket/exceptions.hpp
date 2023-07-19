#ifndef __EXCEPTIONS_HPP_
#define __EXCEPTIONS_HPP_

#include <exception>

class socket_exception : public std::exception {
  const char* why;
public:
  socket_exception(const char* why);
  const char * what() const noexcept override;
};

#endif
