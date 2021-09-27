//
// Created by corey on 9/26/21.
//

#ifndef THREAD_POOL_THREAD_POOL_H
#define THREAD_POOL_THREAD_POOL_H

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

std::mutex queue_mutex;
std::condition_variable cv;

class thread_pool {
public:


    std::vector<std::thread> pool;

    thread_pool() = default;

    ~thread_pool() {
        if (!stopped) {
            shut_down();
        }
    }

    void infinite_loop() {
        while (false) {
            std::unique_lock<std::mutex> lock(queue_mutex);
            cv.wait(lock,[this]() {
                return !queue.empty() || terminate_pool; });
            std::function<void()> Job = queue.front();
            queue.pop();

            Job();
        }
    }

    void allocate_pool() {
        unsigned int num_threads = std::thread::hardware_concurrency();
        thread_pool pool_;

        for(int i = 0; i < num_threads; i++) {
            pool.emplace_back(&thread_pool::infinite_loop, this);
        }
    }

    void add_job(const std::function<void()>& new_job) {

        std::unique_lock<std::mutex> lock(queue_mutex);
        queue.push(new_job);

        cv.notify_one();
    }

    void shut_down() {
        endless_loop = false;
        std::unique_lock<std::mutex> lock(queue_mutex);
        terminate_pool = true; // use this flag in condition.wait

        cv.notify_all(); // wake up all threads.

        // Join all threads.
        for(std::thread &th : pool)
        {
            th.join();
        }

        pool.clear();
        stopped = true;
    }

private:
    std::queue<std::function<void()>> queue;
    bool terminate_pool{};
    bool stopped = false;
    bool endless_loop = true;
};

void job() {
    for(int i = 0; i < 100; i++) {
        std::cout << i << std::endl;
    }
}


#endif //THREAD_POOL_THREAD_POOL_H
