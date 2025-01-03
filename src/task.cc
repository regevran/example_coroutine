

#include "task.hh"
#include "reactor.hh"
#include <iostream>

// promise type - start //

task task::promise_type::get_return_object() {
    return task{std::coroutine_handle<promise_type>::from_promise(*this)};
}

std::suspend_always task::promise_type::initial_suspend() { 
    return {}; 
}

std::suspend_always task::promise_type::final_suspend() noexcept {
    return {};
}

void task::promise_type::unhandled_exception() {
}

void task::promise_type::return_void() {
    owner_->set_ready();
}

// promise type - end //


// task - start //

task::task(std::coroutine_handle<promise_type> coro_handle) 
    : coro_handle_(coro_handle) {
    coroutine_framework::add_suspended_task(*this);
}

task::task(const task& rhs)
    : coro_handle_(rhs.coro_handle_),
      ready_(rhs.ready_) {
}

task::~task()
{
}

void task::resume() {
    std::cout << "going to resume a task\n";
    if (not coro_handle_.done())
    {
        coro_handle_.resume();
    }
}

void task::set_ready() {
    ready_ = true;
}

bool task::is_ready() const {
    return ready_;
}
//
// task - end //

