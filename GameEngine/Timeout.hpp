#pragma once
#include <chrono>
#include <ctime>
class Timeout
{
public:
    Timeout(){timeout_ = 1;};
    Timeout(int timeout){timeout_ = timeout;}
    void Start()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(now);
        startTime_ = current_time;
    }
    bool can_execute()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t current_time = std::chrono::system_clock::to_time_t(now);
        double elapsed_seconds = std::difftime(current_time, startTime_);
        if (elapsed_seconds >= timeout_)
            return true;
        return false;

    }
    ~Timeout();
    int timeout_;
     std::time_t startTime_;
};