#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>


class thread_pool {
public:

    thread_pool() = default;

    ~thread_pool() {
        if (!stopped) {
            shut_down();
        }
    }

    void infinite_loop() {
        while (true) {
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
    std::vector<std::thread> pool;
    bool stopped = false;
    std::mutex queue_mutex;
    std::condition_variable cv;
};


void job() {
    for(int i = 0; i < 100; i++) {
        std::cout << i << std::endl;
    }
}


int main() {

    auto *pool_ = new thread_pool();

    pool_->allocate_pool();

    std::function<void()> func_ = job;

    pool_->add_job(func_);

    pool_->add_job(func_);

    delete pool_;

    return 0;
}
