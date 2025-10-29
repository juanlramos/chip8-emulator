#pragma once
#include <array>
#include <cstdint>
#include <SDL2/SDL.h>

class Input {
public:
    Input();
    ~Input();

    void update();  // lê eventos do SDL (chamado a cada frame)

    bool isKeyPressed(uint8_t chip8Key) const;
    uint8_t waitForKeyPress(); // bloqueia até tecla ser pressionada

private:
    std::array<uint8_t, 16> keys; // 1 = pressionada, 0 = solta

    int mapSDLKey(SDL_Keycode key) const; // converte tecla física em tecla CHIP-8
};
