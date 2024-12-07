#ifndef __TASK_HPP_
#define __TASK_HPP_

namespace methods {
class task {
public:
  virtual void execute() = 0;
  virtual ~task() = default;
};
} // namespace methods

#endif
