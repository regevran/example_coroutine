

#include "task.hh"
#include "reactor.hh"

// promise type - start //

task task::promise_type::get_return_object() {
    return task{this};
}

std::suspend_always task::promise_type::initial_suspend() { 
    // note - after this call this is empty, it was moved
    // to the responsibility of coroutine_framwork
    coroutine_framework::add_suspended_task(task(this));
    
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

task::task(promise_type* owned) {
}

task::task(task&& t) 
    : owned_(t.owned_)
{
    t.owned_ = nullptr;
}

std::coroutine_handle<task::promise_type> task::get_handle() const {
    return std::coroutine_handle<promise_type>::from_promise(*owned_);
}

void task::set_ready() {
    ready_ = true;
}

bool task::is_ready() const {
    return ready_;
}

