

#pragma once

class basic_coroutine {
public:
    struct promise_type {
        basic_coroutine get_return_object() { return basic_coroutine{}; }

        void unhandled_exception() noexcept {}

        void return_void() noexcept {}

        std::suspend_never initial_suspend() noexcept { return {}; }
        std::suspend_never final_suspend() noexcept { return {}; }
    };
};
