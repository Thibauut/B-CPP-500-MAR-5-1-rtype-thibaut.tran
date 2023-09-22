/*
** EPITECH PROJECT, 2023
** Client
** File description:
** TreadHandler.cpp
*/

#include "ThreadHandler.hpp"

ThreadHandler::ThreadHandler() : running_(false)
{
}

void ThreadHandler::start()
{
    running_ = true;
    thread_ = std::thread(&ThreadHandler::run, this);
}

void ThreadHandler::stop()
{
    running_ = false;
    if (thread_.joinable())
        thread_.join();
}