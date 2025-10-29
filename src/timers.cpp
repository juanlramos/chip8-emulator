#include "timers.h"

Timers::Timers() : running(false), delayTimer(0), soundTimer(0) {}

Timers::~Timers() {
    stop();
}

void Timers::start() {
    running = true;
    timerThread = std::thread(&Timers::runLoop, this);

    // Aguarda o loop ativar (máx. 50ms)
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Timers::stop() {
    running = false;
    if (timerThread.joinable())
        timerThread.join();
}

void Timers::reset() {
    delayTimer = 0;
    soundTimer = 0;
}

void Timers::runLoop() {
    const int frameTime = 1000 / 60; // 60 Hz
    std::cout << "[TIMER] Loop iniciado" << std::endl;

    while (running) {
        if (delayTimer > 0) {
            delayTimer--;
            std::cout << "[TIMER] DT=" << (int)delayTimer << std::endl;
        }

        if (soundTimer > 0) {
            soundTimer--;
            std::cout << "[TIMER] ST=" << (int)soundTimer << std::endl;
            if (soundTimer == 1) {
                std::cout << "\a";
                std::cout.flush();
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(frameTime));
    }

    std::cout << "[TIMER] Loop encerrado" << std::endl;
}

