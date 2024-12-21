
/*
#include "ran_random_reader.hh"
#include "ranged_char.hh"
#include "stricked_rgb.hh"
*/

#include "async_random_char.hh"
#include "awaitable_random_char.hh"
#include "basic_coroutine.hh"
#include "reactor.hh"
#include <chrono>
#include <iostream>
#include <thread>

void print_char(unsigned char c) {
    std::println(
        "read a char with value {:0<#{}X}", 
        c,
        std::numeric_limits<decltype(c)>::digits / 4 
    );
}

void random_read() {

    async_random_char arc;
    arc.async_read(print_char);

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
}

basic_coroutine coro_read()
{
    ////////
    // to be called like this:
    //  coro_read();
    //  std::this_thread::sleep_for(std::chrono::milliseconds(250));
    ////////

    unsigned char c = co_await awitable_random_char{};
    print_char(c);
}

int main()
{

    return 0;
}

