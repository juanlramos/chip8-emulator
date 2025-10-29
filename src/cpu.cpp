#include "cpu.h"
#include <iostream>
#include <iomanip>
#include <random>

CPU::CPU(Memory& memory, Display& disp, Input& in, Timers& t)
    : mem(memory), display(disp), input(in), timers(t) {
    reset();
}

CPU::~CPU() {}

void CPU::reset() {
    V.fill(0);
    I = 0;
    PC = Memory::DEFAULT_LOAD_ADDRESS;
    SP = 0;
    stack.fill(0);
    timers.delayTimer = 0;
    timers.soundTimer = 0;
}

void CPU::setProgramCounter(uint16_t address) { PC = address; }
uint16_t CPU::getProgramCounter() const { return PC; }

uint16_t CPU::fetchOpcode() { return mem.read16(PC); }

void CPU::step() {
    uint16_t opcode = fetchOpcode();
    PC += 2;
    executeOpcode(opcode);
}

void CPU::executeOpcode(uint16_t opcode) {
    std::cout << "[EXEC] 0x" << std::hex << opcode 
          << " PC=0x" << std::hex << PC 
          << std::endl;

    DecodedOpcode d = OpcodeDecoder::decode(opcode);
    switch (d.n1) {

    // -------------------------------------------------------------
    case 0x0:
        switch (opcode) {
        case 0x00E0: // CLS
            display.clear();
            break;
        case 0x00EE: // RET
            SP--;
            PC = stack[SP];
            break;
        default:     // SYS addr (ignorado)
            break;
        }
        break;

    // -------------------------------------------------------------
    case 0x1: // JP addr
        PC = d.NNN;
        break;

    case 0x2: // CALL addr
        stack[SP] = PC;
        SP++;
        PC = d.NNN;
        break;

    case 0x3: // SE VX, NN
        if (V[d.X] == d.NN)
            PC += 2;
        break;

    case 0x4: // SNE VX, NN
        if (V[d.X] != d.NN)
            PC += 2;
        break;

    case 0x5: // SE VX, VY
        if (d.n4 == 0x0 && V[d.X] == V[d.Y])
            PC += 2;
        break;

    case 0x6: // LD VX, NN
        V[d.X] = d.NN;
        break;

    case 0x7: // ADD VX, NN
        V[d.X] += d.NN;
        break;

    // -------------------------------------------------------------
    case 0x8:
        switch (d.n4) {
        case 0x0: // LD VX, VY
            V[d.X] = V[d.Y];
            break;
        case 0x1: // OR
            V[d.X] |= V[d.Y];
            break;
        case 0x2: // AND
            V[d.X] &= V[d.Y];
            break;
        case 0x3: // XOR
            V[d.X] ^= V[d.Y];
            break;
        case 0x4: { // ADD VX, VY (com carry)
            uint16_t sum = V[d.X] + V[d.Y];
            V[0xF] = (sum > 0xFF);
            V[d.X] = sum & 0xFF;
            break;
        }
        case 0x5: // SUB VX, VY
            V[0xF] = (V[d.X] > V[d.Y]) ? 1 : 0;
            V[d.X] = V[d.X] - V[d.Y];
            break;
        case 0x6: // SHR VX
            V[0xF] = V[d.X] & 0x01;
            V[d.X] >>= 1;
            break;
        case 0x7: // SUBN VX, VY
            V[0xF] = (V[d.Y] > V[d.X]) ? 1 : 0;
            V[d.X] = V[d.Y] - V[d.X];
            break;
        case 0xE: // SHL VX
            V[0xF] = (V[d.X] & 0x80) >> 7;
            V[d.X] <<= 1;
            break;
        }
        break;

    // -------------------------------------------------------------
    case 0x9: // SNE VX, VY
        if (d.n4 == 0x0 && V[d.X] != V[d.Y])
            PC += 2;
        break;

    case 0xA: // LD I, NNN
        I = d.NNN;
        break;

    case 0xB: // JP V0, addr
        PC = d.NNN + V[0];
        break;

    case 0xC: { // RND VX, NN
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<uint16_t> dist(0, 255);
        V[d.X] = (dist(gen) & d.NN);
        break;
    }

    // -------------------------------------------------------------
    case 0xD: { // DRW VX, VY, N
        uint8_t x = V[d.X];
        uint8_t y = V[d.Y];
        uint8_t height = d.N;
        const uint8_t* sprite = &mem.raw()[I];
        bool collision = display.drawSprite(x, y, sprite, height);
        V[0xF] = collision ? 1 : 0;
        break;
    }

    // -------------------------------------------------------------
    case 0xE:
        switch (d.NN) {
        case 0x9E: // SKP VX
            if (input.isKeyPressed(V[d.X]))
                PC += 2;
            break;
        case 0xA1: // SKNP VX
            if (!input.isKeyPressed(V[d.X]))
                PC += 2;
            break;
        }
        break;

    // -------------------------------------------------------------
    case 0xF:
        switch (d.NN) {
        case 0x07: // LD VX, DT
            V[d.X] = timers.delayTimer;
            break;
        case 0x0A: // LD VX, K
            V[d.X] = input.waitForKeyPress();
            break;
        case 0x15: // LD DT, VX
        std::cout << "[FX15] Setando delayTimer = " << std::dec << (int)V[d.X] << std::endl;
        timers.delayTimer = V[d.X];
        break;
        case 0x18: // LD ST, VX
            timers.soundTimer = V[d.X];
            break;
        case 0x1E: // ADD I, VX
            I += V[d.X];
            break;
        case 0x29: // LD F, VX
            I = V[d.X] * 5; // cada fonte ocupa 5 bytes
            break;
        case 0x33: { // LD B, VX
            uint8_t value = V[d.X];
            mem.write8(I, value / 100);
            mem.write8(I + 1, (value / 10) % 10);
            mem.write8(I + 2, value % 10);
            break;
        }
        case 0x55: // LD [I], VX
            for (int i = 0; i <= d.X; ++i)
                mem.write8(I + i, V[i]);
            break;
        case 0x65: // LD VX, [I]
            for (int i = 0; i <= d.X; ++i)
                V[i] = mem.read8(I + i);
            break;
        }
        break;

    // -------------------------------------------------------------
    default:
        std::cerr << "[CPU] Opcode desconhecido: 0x"
                  << std::hex << std::setw(4) << std::setfill('0') << opcode
                  << std::endl;
        break;
    }
}