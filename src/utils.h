#pragma once
#include <chrono>
#include <thread>
#include <iostream>

namespace Utils {
    inline void sleepForMs(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    class FpsLimiter {
    public:
        FpsLimiter(double targetHz)
            : frameDuration(std::chrono::duration<double>(1.0 / targetHz)) {}

        void frameStart() { start = std::chrono::high_resolution_clock::now(); }

        void frameEnd() {
            auto end = std::chrono::high_resolution_clock::now();
            auto elapsed = end - start;
            if (elapsed < frameDuration)
                std::this_thread::sleep_for(frameDuration - elapsed);
        }

    private:
        std::chrono::high_resolution_clock::time_point start;
        std::chrono::duration<double> frameDuration;
    };
}
