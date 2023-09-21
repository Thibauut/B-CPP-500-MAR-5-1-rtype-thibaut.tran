/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Thread.hpp
*/

#pragma once
#include <pthread.h>

enum Status {
    STARTED,
    RUNNING,
    STOPPED
};

class Thread {
    public:
        Thread();
        ~Thread();

        void create(void *(*startRoutine)(void *), void *arg);
        void join();

        Status getStatus() const;
        void setStatus(Status status);

        void wait();

    private:
        pthread_t *_thread;
        Status _status;
};