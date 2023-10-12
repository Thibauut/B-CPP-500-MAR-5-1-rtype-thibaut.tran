#pragma once
#include <chrono>
#include <ctime>

namespace GameEngine {

    class Timeout
    {
    public:
        Timeout(){timeout_ = 1;};
        Timeout(float timeout)
        {
            Start();
            timeout_ = timeout;
        }
        void Start()
        {
            startTime_ = std::chrono::steady_clock::now();
        }
        bool can_execute()
        {
            auto current_time = std::chrono::steady_clock::now();
            elapsed_seconds_ = std::chrono::duration_cast<std::chrono::duration<double>>(current_time - startTime_).count();
            if (elapsed_seconds_ >= timeout_)
                return true;
            return false;

        }
        // ~Timeout();
        double timeout_;
        std::chrono::_V2::steady_clock::time_point startTime_;
        double elapsed_seconds_;
    };
}