

#pragma once

#include "task.hh"
#include <list>
#include <ostream>
#include <queue>

namespace coroutine_framework {

class reactor {

public:
    void add_suspended_task(task&& t);
    void run(); 

private:
    std::list<task> suspended_tasks_;
    std::list<task> ready_tasks;

    friend std::ostream& operator<<(std::ostream&, const reactor&);
};

}


namespace coroutine_framework {

void run();
void add_suspended_task(task&&);
const reactor& get_reactor();

}


