
#pragma once

struct promise_type;

class future_rgb {
public:
    future_rgb(std::coroutine_handle<promise_type> handle)
        : handle_(handle)
    {}

private:
    struct promise_type {
        future_rgb get_return_object() { 
            return futur_rgb{std::coroutine_handle<promise_type>::from_promise(*this)};
        }

        std::suspend_always initial_suspend() { 
            return {}; 
        }

        std::suspend_always final_suspend() noexcept { 
            return {}; 
        }

        void unhandled_exception() {}
    };

    std::coroutine_handle<promise_type> handle_;
    strict_rgb val_;
}


class random_rgb {

public:
    random_rgb(
        ranged_char r,
        ranged_char g,
        ranged_char b
    )

    future_strict_rgb get_rgb() {
        return rgb_;
    }


private:
    strict_rgb rgb_

};
