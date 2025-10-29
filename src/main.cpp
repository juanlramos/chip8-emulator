#include "memory.h"
#include "display.h"
#include "input.h"
#include "timers.h"
#include "sound.h"
#include "cpu.h"
#include "utils.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Uso: ./chip8 [--clock <Hz>] [--scale <fator>] caminho_para_rom.ch8\n";
        return 1;
    }

    int clockSpeed = 500;   // padrão 500 Hz
    int scale = 10;         // padrão 10x (640x320)
    std::string romPath;

    // 🔹 Lê parâmetros da linha de comando
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--clock" && i + 1 < argc) {
            clockSpeed = std::stoi(argv[++i]);
        } else if (arg == "--scale" && i + 1 < argc) {
            scale = std::stoi(argv[++i]);
        } else {
            romPath = arg; // considera o último argumento como ROM
        }
    }

    if (romPath.empty()) {
        std::cerr << "Erro: caminho da ROM não fornecido.\n";
        return 1;
    }

    Memory mem;
    Display display(scale);
    Input input;
    Timers timers;
    Sound sound;
    CPU cpu(mem, display, input, timers);

    if (!mem.loadROM(romPath)) {
        std::cerr << "Falha ao carregar ROM: " << romPath << std::endl;
        return 1;
    }

    timers.start();

    const int frameRate = 60;
    Utils::FpsLimiter cpuLimiter(clockSpeed);
    Utils::FpsLimiter frameLimiter(frameRate);

    int cyclesPerFrame = clockSpeed / frameRate;
    bool running = true;

    std::cout << "Executando ROM: " << romPath
              << " | Clock: " << clockSpeed << " Hz"
              << " | Escala: " << scale << "x\n";

    while (running) {
        frameLimiter.frameStart();
        input.update();

        for (int i = 0; i < cyclesPerFrame; ++i)
            cpu.step();

        sound.update(timers.soundTimer > 0);
        frameLimiter.frameEnd();
    }

    timers.stop();
    return 0;
}
