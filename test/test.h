//
// Created by corey on 9/26/21.
//

#ifndef THREAD_POOL_TEST_H
#define THREAD_POOL_TEST_H

#include <gtest/gtest.h>
#include "../src/thread_pool.h"

class test : public ::testing::Test {
public:
    thread_pool *thread_pool_;

    test() {

    }

    virtual ~test() {

    }

    void SetUp() override {
        thread_pool_ = new thread_pool();
        //thread_pool_->allocate_pool();
    }

    void TearDown() override {
        delete thread_pool_;
    }

};

TEST_F(test, job) {
    /* Tests the job output to see if both equal 100*/
    testing::internal::CaptureStdout();
    job();
    std::string job_output = testing::internal::GetCapturedStdout();
    testing::internal::CaptureStdout();
    for(int i = 0; i < 100; i++)
        std::cout << i << std::endl;

    std::string test_output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(job_output, test_output);
}


TEST_F(test, allocate_pool) {
    /*Test size of thread pool */

    thread_pool_->allocate_pool();

    unsigned int num_threads = std::thread::hardware_concurrency();
    unsigned int thread_pool_size = thread_pool_->pool.size();

    EXPECT_EQ(num_threads, thread_pool_size);

    thread_pool_->shut_down();

}

#endif //THREAD_POOL_TEST_H
