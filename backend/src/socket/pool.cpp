#include "pool.hpp"
#include <cstddef>
#include <functional>
#include <memory>

thread_pool::thread_pool(size_t numThreads) : stop(false) {
  for (size_t i = 0; i < numThreads; ++i) {
    threads.emplace_back([this] {
      while (true) {
        std::shared_ptr<client> _client;
        {
          std::unique_lock<std::mutex> lock(clientsMutex);
          condition.wait(lock, [this] { return stop || !clients.empty(); });

          if (stop && clients.empty()) {
            return;
          }

          _client = clients.front();
          _client->handle_connection();
          clients.pop();
        }
      }
    });
  }
}

void thread_pool::addClient(std::shared_ptr<client> client) {
        {
            std::unique_lock<std::mutex> lock(clientsMutex);
            clients.emplace(client);
        }
        condition.notify_one();
}


thread_pool::~thread_pool() {
  {
    std::unique_lock<std::mutex> lock(clientsMutex);
    stop = true;
  }
  condition.notify_all();

  for (std::thread &thread : threads) {
    thread.join();
  }
}
