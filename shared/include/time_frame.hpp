#ifndef TIME_FRAME_HPP_
#define TIME_FRAME_HPP_

#include <chrono>
#include <logger.hpp>
#include <thread>

class TimeFrame {
public:
    void set_frame_duration(int duration_in_ms) {
        this->frame_duration = std::chrono::milliseconds(duration_in_ms);
    }
    void start_frame()
    {
        this->frame_start_time = std::chrono::system_clock::now();
    }
    void sleep_until_frame_is_over()
    {
        auto dt = this->frame_duration - (std::chrono::system_clock::now() - this->frame_start_time);
        Logger::debug("Sleeping for {}", dt);
        std::this_thread::sleep_for(dt);
    }
private:
    std::chrono::milliseconds frame_duration;
    std::chrono::_V2::system_clock::time_point frame_start_time;
};

#endif // TIME_FRAME_HPP_
