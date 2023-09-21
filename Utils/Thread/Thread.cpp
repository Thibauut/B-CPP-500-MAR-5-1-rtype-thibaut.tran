/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-maori.dino
** File description:
** Thread.cpp
*/

#pragma once

#include "Thread.hpp"

Thread::Thread() : _thread(nullptr), _status(STOPPED) {}

Thread::~Thread()
{
    if (_status == RUNNING)
        pthread_detach(*_thread);
    delete _thread;
}

void Thread::create(void *(*startRoutine)(void *), void *arg)
{
    _thread = new pthread_t;
    pthread_create(_thread, nullptr, startRoutine, arg);
    _status = RUNNING;
}

void Thread::join()
{
    pthread_join(*_thread, nullptr);
    _status = STOPPED;
}

Status Thread::getStatus() const
{
    return _status;
}

void Thread::setStatus(Status status)
{
    _status = status;
}

void Thread::wait()
{
    pthread_join(*_thread, nullptr);
}