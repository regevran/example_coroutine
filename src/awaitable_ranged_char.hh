

#pragma once


class awaitable_ranged_char;

class awaiter_ranged_char {
public:
    awaiter_ranged_char(awaitable_ranged_char& awaitable)
        : awaitable_(awaitable) {}

    bool await_ready() const noexcept { return false; }

    void await_suspend(std::coroutine_handle<> handle) noexcept {
       // asyc logic goes here 
    }

    ranged_char await_resume() const noexcept {
        return rc_;
    }
    
// ranged char value
private:
    ranged_char rc_;

// coroutine mechanics
private:
    awaitable_ranged_char& awaitable_

};

class awaitable_ranged_char {
public:
    awaiter_ranged_char operator co_await() {
        return {*this};
    }

};
