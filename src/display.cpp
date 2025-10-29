#include "display.h"
#include <iostream>

// ---------------------------------------------------------------------
// Construtor
// ---------------------------------------------------------------------
Display::Display(int scale)
    : scale(scale), window(nullptr), renderer(nullptr) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Erro ao inicializar SDL2: " << SDL_GetError() << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        "CHIP-8 Emulator",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH * scale,
        HEIGHT * scale,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Erro ao criar janela SDL2: " << SDL_GetError() << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Erro ao criar renderer SDL2: " << SDL_GetError() << std::endl;
        return;
    }

    clear();
}

// ---------------------------------------------------------------------
Display::~Display() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// ---------------------------------------------------------------------
void Display::clear() {
    for (auto& row : pixels)
        row.fill(0);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

// ---------------------------------------------------------------------
// Desenha sprite e retorna se houve colisão
// ---------------------------------------------------------------------
bool Display::drawSprite(uint8_t x, uint8_t y, const uint8_t* sprite, uint8_t height) {
    bool collision = false;

    for (int row = 0; row < height; ++row) {
        uint8_t byte = sprite[row];
        for (int col = 0; col < 8; ++col) {
            // bit mais significativo primeiro
            if ((byte & (0x80 >> col)) != 0) {
                int px = (x + col) % WIDTH;
                int py = (y + row) % HEIGHT;

                // XOR pixel
                if (pixels[py][px] == 1)
                    collision = true;

                pixels[py][px] ^= 1;
            }
        }
    }

    render(); // atualiza janela
    return collision;
}

// ---------------------------------------------------------------------
// Atualiza o SDL com o conteúdo do framebuffer
// ---------------------------------------------------------------------
void Display::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (pixels[y][x]) {
                SDL_Rect r{ x * scale, y * scale, scale, scale };
                SDL_RenderFillRect(renderer, &r);
            }
        }
    }

    SDL_RenderPresent(renderer);
}