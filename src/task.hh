

#pragma once

class task {
    
private:
    struct promise_type {
        task get_return_object(
                return task{
                    std::coroutine_handle<promise_type>::from_promise(*this)
                };
        }
        std::suspend_always initial_syspend() { return {}; }
        std::suspend_always final_syspend() { return {}; }

    };

public:
    task(std::coroutine_handle<promise_type> handle)
        : handle_(handle) {}

    std::coroutine_handle<promise_type> get_hanlde() const {
        return handle_;
    }

private:
    std::coroutine_handle<promise_type> handle_;
};

