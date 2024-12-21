

#pragma once

#include "task.hh"
#include <queue>

class reactor {

public:
    void add_task(task t) {
        coroutines_.push(t.get_handle());
    }

    void run() {
        while (not coroutines_.empty()) {
            auto handle = coroutines_.front();
            coroutines_.pop();

            handle.resume();

            if (handle.done()) {
                handle.destroy();
            } else {
                coroutines_.push(handle);
            }
        }
    }    

private:
    std::queue<std::coroutine_handle<task::promise_type>> coroutines_;
};
