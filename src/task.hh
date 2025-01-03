

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
    task(promise_type* owned);
    task(task&) = delete;
    task(task&&);

public:
    std::coroutine_handle<promise_type> get_handle() const; 
    void set_ready();
    bool is_ready() const;

private:
    promise_type* owned_ = nullptr;
    bool ready_ = false;
};


