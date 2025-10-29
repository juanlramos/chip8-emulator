#pragma once
#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>
#include <SDL2/SDL.h>

class Timers {
public:
    Timers();
    ~Timers();

    void start();   // inicia loop de atualização
    void stop();    // para o loop
    void reset();

    std::atomic<uint8_t> delayTimer;
    std::atomic<uint8_t> soundTimer;

private:
    bool running;
    std::thread timerThread;

    void runLoop();
};
