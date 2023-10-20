#pragma once
#include <chrono>
#include <ctime>

namespace GameEngine {

    class Timeout
    {
    public:
        Timeout(){timeout_ = 1, wasStarted_ = false, startTime_ = std::chrono::steady_clock::now();}
        Timeout(float timeout)
        {
            Start();
            timeout_ = timeout;
        }
        void Start()
        {
            startTime_ = std::chrono::steady_clock::now();
            wasStarted_ = true;
        }
        bool can_execute()
        {
            auto current_time = std::chrono::steady_clock::now();
            elapsed_seconds_ = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - startTime_).count();
            if (elapsed_seconds_ >= timeout_)
                return true;
            return false;

        }

        void setTimeout(double new_time) {timeout_ = new_time;}

        bool isStarted(){return wasStarted_;}

        double getElapsedSeconds() const
        {
            auto current_time = std::chrono::steady_clock::now();
            double newTime = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - startTime_).count();
            return newTime;
        }

        // ~Timeout();
        double timeout_;
        std::string _name;
        std::chrono::steady_clock::time_point startTime_;
        double elapsed_seconds_;
        bool wasStarted_;
    };
}