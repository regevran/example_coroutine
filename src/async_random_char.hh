

#pragma once

#include "ranged_char.hh"
#include <aio.h>
#include <chrono>
#include <cstdio>
#include <functional>
#include <iostream>
#include <print>
#include <signal.h>

class async_random_char {
    public:
        using read_callback = std::function<void(unsigned char)>;
public:
    async_random_char() { 
        FILE* file_ = fopen("/dev/urandom", "r");
        if (not file_) {
            std::print("null fd");
            return;
        }

        fd_ = fileno(file_);
        std::print("fd_: {0}\n", fd_);
    }

    ~async_random_char() {
        if (file_) {
            fclose(file_);
        } else {
            std::println("file_ is null can't close it");
        }
    }

    void async_read(read_callback callback) {
        // save the callback
        callback_ = std::move(callback);

        // initiate async read
        cb_.aio_fildes = fd_; 
        cb_.aio_offset = 0;
        cb_.aio_buf = &value_;
        cb_.aio_nbytes = 1;
        cb_.aio_sigevent.sigev_notify = SIGEV_THREAD;
        cb_.aio_sigevent.sigev_notify_function = random_read_from_dev;
        cb_.aio_sigevent.sigev_value.sival_ptr = this;

        int k = aio_read(&cb_);

        std::print("aio_read returned with: {0}\n", errno);
    }

private:
    static void random_read_from_dev(sigval val)
    {
        std::println("reached asyc callback");
        auto self = reinterpret_cast<async_random_char*>(val.sival_ptr);

        self->callback_(self->value_);
    }

private:
    aiocb cb_ {};
    FILE* file_ {nullptr};
    int fd_ {-1};
    char value_;

    read_callback callback_;
};

