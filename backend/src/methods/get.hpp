#ifndef __GET_HPP_
#define __GET_HPP_
#include "task.hpp"
#include <string>

namespace methods {
class get_task : public task {
  std::string resource;

public:
  get_task(std::string resource);
  void execute() override;
};
} // namespace methods
#endif
