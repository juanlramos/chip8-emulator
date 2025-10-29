#pragma once
#include <array>
#include <cstdint>
#include <SDL2/SDL.h>

// ---------------------------------------------------------------------
// Classe responsável pelo vídeo do CHIP-8 (64x32 pixels)
// ---------------------------------------------------------------------
class Display {
public:
    static constexpr int WIDTH = 64;
    static constexpr int HEIGHT = 32;

    Display(int scale = 10); // construtor com fator de escala
    ~Display();

    // Limpa o framebuffer
    void clear();

    // Desenha sprite de N bytes a partir de (x, y)
    // Retorna true se houve colisão (para VF)
    bool drawSprite(uint8_t x, uint8_t y, const uint8_t* sprite, uint8_t height);

    // Atualiza a janela (mostra o framebuffer)
    void render();

private:
    int scale;
    std::array<std::array<uint8_t, WIDTH>, HEIGHT> pixels; // framebuffer
    SDL_Window* window;
    SDL_Renderer* renderer;

    void drawPixel(int x, int y, bool on);
};