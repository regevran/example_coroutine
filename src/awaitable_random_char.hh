

#pragma once

#include "async_random_char.hh"
#include <coroutine>


class awitable_random_char;


class awitable_random_char {

private:
    unsigned char value_;

private:
    class awiter_random_char {

    public:
        awiter_random_char(awitable_random_char& awaitable)
            : awaitable_(awaitable) {}

        bool await_ready() {return false;}

        void await_suspend(std::coroutine_handle<> handle) noexcept {
            arc_.async_read(
                [this, handle](unsigned char c){
                    awaitable_.value_ = c;
                    handle.resume();
                });
        }

        unsigned char await_resume() const noexcept {
            return awaitable_.value_;
        }

    private:
        async_random_char arc_;
        awitable_random_char& awaitable_;
    };

public:
    awiter_random_char operator co_await() {
        return awiter_random_char(*this);
    }

};
