#ifndef __POOL_HPP
#define __POOL_HPP
#include <condition_variable>
#include <mutex>
#include <queue>
#include <thread>

#include "../methods/task.hpp"

class thread_pool {
  std::vector<std::thread> threads;
  std::queue<std::shared_ptr<methods::task>> tasks;
  std::mutex task_mutex;
  std::condition_variable condition;
  bool stop;

public:
  thread_pool(size_t numThreads);
  void add_task(std::shared_ptr<methods::task> task);
  ~thread_pool();
};

#endif
