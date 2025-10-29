#include "input.h"
#include <iostream>
#include <thread>
#include <chrono>

Input::Input() {
    keys.fill(0);
}

Input::~Input() {}

// -----------------------------------------------------------
void Input::update() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            std::exit(0);
        } else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            int mapped = mapSDLKey(e.key.keysym.sym);
            if (mapped != -1)
                keys[mapped] = (e.type == SDL_KEYDOWN) ? 1 : 0;
        }
    }
}

// -----------------------------------------------------------
bool Input::isKeyPressed(uint8_t chip8Key) const {
    if (chip8Key < 16)
        return keys[chip8Key] == 1;
    return false;
}

// -----------------------------------------------------------
uint8_t Input::waitForKeyPress() {
    SDL_Event e;
    while (true) {
        if (SDL_WaitEvent(&e)) {
            if (e.type == SDL_KEYDOWN) {
                int mapped = mapSDLKey(e.key.keysym.sym);
                if (mapped != -1)
                    return static_cast<uint8_t>(mapped);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

// -----------------------------------------------------------
int Input::mapSDLKey(SDL_Keycode key) const {
    switch (key) {
        case SDLK_1: return 0x1;
        case SDLK_2: return 0x2;
        case SDLK_3: return 0x3;
        case SDLK_4: return 0xC;
        case SDLK_q: return 0x4;
        case SDLK_w: return 0x5;
        case SDLK_e: return 0x6;
        case SDLK_r: return 0xD;
        case SDLK_a: return 0x7;
        case SDLK_s: return 0x8;
        case SDLK_d: return 0x9;
        case SDLK_f: return 0xE;
        case SDLK_z: return 0xA;
        case SDLK_x: return 0x0;
        case SDLK_c: return 0xB;
        case SDLK_v: return 0xF;
        default: return -1;
    }
}
