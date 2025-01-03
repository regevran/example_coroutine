

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


void add_suspended_task(task&& t) {
    g_reactor.add_suspended_task(std::move(t));
}

const reactor& get_reactor() {
    return g_reactor;
}


} // coroutine_framwork
  

namespace coroutine_framework {

void reactor::add_suspended_task(task&& t) {
    suspended_tasks_.emplace_back(std::move(t));
}

void reactor::run() {

    // move suspended-tasks to ready-tasks
    for (
        auto 
            suspended_task = std::make_move_iterator(suspended_tasks_.begin()),
            end = std::make_move_iterator(suspended_tasks_.end());
        suspended_task != end;
        ++suspended_task
    ) {
        if (suspended_task->is_ready()) {
            ready_tasks.emplace_back(*suspended_task);
        }

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
        << "ready tasks:     " << r.ready_tasks.size()        << "\n";
    return o;
}    


}

