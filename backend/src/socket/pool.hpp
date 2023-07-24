#ifndef __POOL_HPP
#define __POOL_HPP
#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class thread_pool {
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;

public:
    thread_pool(size_t numThreads); 
    template<typename F>
    void addTask(F&& task); 
    ~thread_pool();
};

#endif
