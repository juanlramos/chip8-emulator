# CHIP-8 Emulator

Emulador simples do CHIP-8 implementado em C++ usando SDL2 para renderização, entrada e som.

Este repositório contém a implementação do CPU, memória, decodificador de opcodes, display, som e entrada para executar ROMs clássicas do CHIP-8.

## Documentação

- Compilação: `docs/README_COMPILAR.md`
- Uso / execução: `docs/README_USAR.md`

## Estrutura do projeto

Principais arquivos e pastas:

- `src/` — fontes C++ (ex.: `cpu.cpp`, `display.cpp`, `input.cpp`, etc.)
- `roms/` — ROMs de exemplo (ex.: `TETRIS`, `PONG`...)
- `docs/` — documentação (compilação e uso)

## Compilar e executar (resumo rápido)

1. Instale dependências do SDL2 (Ubuntu/Debian):

```bash
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
```

2. Compile:

```bash
g++ src/*.cpp -I src -lSDL2 -pthread -o chip8 -lm
```

3. Execute uma ROM de exemplo:

```bash
./chip8 roms/TETRIS
```

Ou use o `Makefile` para simplificar:

```bash
make build
make run ROM=roms/TETRIS
```
