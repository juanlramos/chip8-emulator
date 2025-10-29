#pragma once
#include <SDL2/SDL.h>
#include <atomic>
#include <thread>
#include <chrono>
#include <iostream>

class Sound {
public:
    Sound();
    ~Sound();

    void startBeep();
    void stopBeep();
    void update(bool active); // ativa/desativa com base no soundTimer > 0

private:
    bool initialized;
    bool beeping;
    SDL_AudioDeviceID device;
    SDL_AudioSpec want, have;
    std::atomic<bool> activeBeep;

    static void audioCallback(void* userdata, Uint8* stream, int len);
};
