#include "opcode_decoder.h"
#include <sstream>
#include <iomanip>

// ---------------------------------------------------------------------
// decode() - separa os campos do opcode
// ---------------------------------------------------------------------
DecodedOpcode OpcodeDecoder::decode(uint16_t opcode) {
    DecodedOpcode d{};

    d.raw = opcode;

    // Cada nibble (4 bits)
    d.n1 = (opcode & 0xF000) >> 12;
    d.n2 = (opcode & 0x0F00) >> 8;
    d.n3 = (opcode & 0x00F0) >> 4;
    d.n4 = (opcode & 0x000F);

    // Campos derivados
    d.X = d.n2;
    d.Y = d.n3;
    d.N = d.n4;
    d.NN = opcode & 0x00FF;
    d.NNN = opcode & 0x0FFF;

    return d;
}

// ---------------------------------------------------------------------
// toString() - retorna string formatada para debug
// ---------------------------------------------------------------------
std::string OpcodeDecoder::toString(const DecodedOpcode& d) {
    std::ostringstream oss;
    oss << "Opcode 0x" << std::hex << std::setw(4) << std::setfill('0') << d.raw
        << " | n1:" << std::hex << (int)d.n1
        << " n2:" << (int)d.n2
        << " n3:" << (int)d.n3
        << " n4:" << (int)d.n4
        << " X:" << (int)d.X
        << " Y:" << (int)d.Y
        << " N:" << (int)d.N
        << " NN:" << std::setw(2) << (int)d.NN
        << " NNN:" << std::setw(3) << (int)d.NNN;
    return oss.str();
}