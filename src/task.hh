

#pragma once

#include <coroutine>

class task {
    
public:
    struct promise_type {
        task get_return_object(); 
        std::suspend_always initial_suspend(); 
        std::suspend_always final_suspend() noexcept; 
        void unhandled_exception();
        void return_void();  

        private:
            task* owner_ = nullptr;
    };

public:
    task(std::coroutine_handle<promise_type>);
    task(const task& rhs);
    task& operator=(const task&) = delete;
    ~task();

public:
    void resume();
    void set_ready();
    bool is_ready() const;

private:
    std::coroutine_handle<promise_type> coro_handle_;
    bool ready_ = false;
};


