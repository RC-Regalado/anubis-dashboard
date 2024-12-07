#include "pool.hpp"
#include "../methods/task.hpp"
#include <cstddef>
#include <memory>

thread_pool::thread_pool(size_t numThreads) : stop(false) {
  for (size_t i = 0; i < numThreads; ++i) {
    threads.emplace_back([this] {
      while (true) {
        std::shared_ptr<methods::task> task;
        {
          std::unique_lock<std::mutex> lock(task_mutex);
          condition.wait(lock, [this] { return stop || !tasks.empty(); });

          if (stop && tasks.empty()) {
            return;
          }

          task = tasks.front();
          tasks.pop();
        }
        task->execute();
      }
    });
  }
}

void thread_pool::add_task(std::shared_ptr<methods::task> task) {
  {
    std::unique_lock<std::mutex> lock(task_mutex);
    tasks.emplace(task);
  }
  condition.notify_one();
}

thread_pool::~thread_pool() {
  {
    std::unique_lock<std::mutex> lock(task_mutex);
    stop = true;
  }
  condition.notify_all();

  for (std::thread &thread : threads) {
    thread.join();
  }
}
