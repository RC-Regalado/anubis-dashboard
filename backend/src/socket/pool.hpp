#ifndef __POOL_HPP
#define __POOL_HPP
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

#include "client.hpp"

class thread_pool {
    std::vector<std::thread> threads;
    std::queue<std::shared_ptr<client>> clients;
    std::mutex clientsMutex;
    std::condition_variable condition;
    bool stop;

public:
    thread_pool(size_t numThreads); 
    void addClient(std::shared_ptr<client> client) ;
    ~thread_pool();
};

#endif
