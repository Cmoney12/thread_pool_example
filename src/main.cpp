#include "thread_pool.h"

int main() {

    auto *pool_ = new thread_pool();

    pool_->allocate_pool();

    std::function<void()> func_ = [&]() {for(int i = 0; i < 100; i++) { std::cout << i << std::endl; }};

    pool_->add_job(func_);

    pool_->add_job(func_);

    delete pool_;

    return 0;
}
