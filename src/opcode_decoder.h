#pragma once
#include <cstdint>
#include <string>

// ---------------------------------------------------------------------
// Estrutura auxiliar para representar um opcode decodificado
// ---------------------------------------------------------------------
struct DecodedOpcode {
    uint16_t raw;  // valor original (2 bytes)
    uint8_t n1;    // nibble mais alto
    uint8_t n2;
    uint8_t n3;
    uint8_t n4;
    uint8_t X;     // registrador X
    uint8_t Y;     // registrador Y
    uint8_t N;     // 4 bits inferiores
    uint8_t NN;    // 8 bits inferiores
    uint16_t NNN;  // 12 bits inferiores
};

// ---------------------------------------------------------------------
// Funções utilitárias
// ---------------------------------------------------------------------
namespace OpcodeDecoder {
    // Função para decodificar um opcode em seus campos
    DecodedOpcode decode(uint16_t opcode);

    // (opcional) converte opcode para string (para debug)
    std::string toString(const DecodedOpcode& d);
}
