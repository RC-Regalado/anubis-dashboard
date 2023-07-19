#include "exceptions.hpp"

socket_exception::socket_exception (const char* why) : why(why){
}

const char* socket_exception::what() const noexcept{
  return why;
}
