

#include "reactor.hh"
#include "task.hh"
#include <queue>


namespace coroutine_framework {

// the one and only reactor
// shoulde thread_local
reactor g_reactor;

void run() {
    g_reactor.run();
}


void add_suspended_task(task t) {
    g_reactor.add_suspended_task(t);
}

const reactor& get_reactor() {
    return g_reactor;
}


} // coroutine_framwork
  

namespace coroutine_framework {

void reactor::add_suspended_task(task t) {
    suspended_tasks_.push_back(t);
}

void reactor::run() {

    while (not suspended_tasks_.empty()) {
        auto&& current_task = std::move(suspended_tasks_.front());
        suspended_tasks_.pop_front();
        current_task.resume();
        executing_tasks_.push_back(std::move(current_task));
    }


        /*
        auto handle = coroutines_.front();
        coroutines_.pop();

        handle.resume();

        if (handle.done()) {
            handle.destroy();
        } else {
            coroutines_.push(handle);
        }
    }
    */
}    


std::ostream& operator<<(std::ostream& o, const coroutine_framework::reactor& r){
    o 
        << "== reactor ==\n" 
        << "suspended tasks: " << r.suspended_tasks_.size()   << "\n"
        << "exeuting tasks:  " << r.executing_tasks_.size()        << "\n";
    return o;
}    


}

