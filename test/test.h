//
// Created by corey on 9/26/21.
//

#ifndef THREAD_POOL_TEST_H
#define THREAD_POOL_TEST_H

#include <gtest/gtest.h>
#include "../src/thread_pool.h"

class test : public ::testing::Test {
public:

    test() {

    }

    virtual ~test() {

    }

    virtual void SetUp() {
        thread_pool_ = new thread_pool();
        //thread_pool_->allocate_pool();
    }

    virtual void TearDown() {
        delete thread_pool_;
    }



private:
    thread_pool *thread_pool_;

};

TEST_F(test, job) {
    testing::internal::CaptureStdout();
    job();
    std::string output = testing::internal::GetCapturedStdout();
}


#endif //THREAD_POOL_TEST_H
