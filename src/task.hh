

#pragma once

class task {
    
public:
    struct promise_type {
        task get_return_object() {
            return task{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { return {}; }
        std::suspend_always final_suspend() noexcept { return {}; }
        void unhandled_exception() {}
        void return_void() {}
    };

public:
    task(std::coroutine_handle<promise_type> handle)
        : handle_(handle) {}

    std::coroutine_handle<promise_type> get_handle() const {
        return handle_;
    }

private:
    std::coroutine_handle<promise_type> handle_;
};

