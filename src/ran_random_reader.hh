
#include <aio.h>
#include <cstdio>
#include <print>
#include <signal.h>
#include <iostream>

class ran_random_reader
{
};

static void random_read_from_dev(sigval val)
{
    char c = 0xef;
    std::print(
        "a char with value {:0<#{}X}", 
        c,
        std::numeric_limits<decltype(c)>::digits / 4 
    );
}

void my_reader()
{
    FILE* file = fopen("/dev/urandom", "r");
    if (not file) {
        std::print("null fd");
        return;
    }

    int fd = fileno(file);
    char c;
    void* pc = &c;

    aiocb cb{};
    cb.aio_fildes = fd; 
    cb.aio_offset = 0;
    cb.aio_buf = pc;
    cb.aio_nbytes = 1;
    cb.aio_sigevent.sigev_notify = SIGEV_THREAD;
    cb.aio_sigevent.sigev_notify_function = random_read_from_dev;

    int k = aio_read(&cb);

    if (k != 0) {
        std::print("aio_read returned with: {0}\n", errno);
    }
}

