#include "thread_pool.h"

int main() {

    auto *pool_ = new thread_pool();

    pool_->allocate_pool();

    std::function<void()> func_ = job;

    pool_->add_job(func_);

    pool_->add_job(func_);

    delete pool_;

    return 0;
}
