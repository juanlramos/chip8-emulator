#pragma once
#include <cstdint>
#include <array>
#include "memory.h"
#include "opcode_decoder.h"
#include "display.h"
#include "input.h"
#include "timers.h"

class CPU {
public:
    CPU(Memory& memory, Display& display, Input& input, Timers& timers);
    ~CPU();

    void reset();
    void step();
    void setProgramCounter(uint16_t address);
    uint16_t getProgramCounter() const;

private:
    Memory& mem;
    Display& display;
    Input& input;
    Timers& timers;

    std::array<uint8_t, 16> V;
    uint16_t I;
    uint16_t PC;
    uint8_t SP;
    std::array<uint16_t, 16> stack;

    uint16_t fetchOpcode();
    void executeOpcode(uint16_t opcode);
};
