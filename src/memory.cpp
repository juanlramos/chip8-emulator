#include "memory.h"
#include <fstream>    // lê arquivos binários
#include <iostream>   // mensagens de erro


// Construtor
Memory::Memory() {
    // Cria um vetor de 4096 bytes inicializados em zero
    mem.assign(SIZE, 0);

    // Carrega os sprites padrão na área 0x000
    loadBuiltinSprites();
}

// Destrutor
Memory::~Memory() {}

// Reset da memória
void Memory::reset() {
    // Zera todos os 4096 bytes
    mem.assign(SIZE, 0);

    // Recarrega os sprites padrão
    loadBuiltinSprites();
}

// Carregar ROM a partir de um arquivo binário
bool Memory::loadROM(const std::string& filePath, uint16_t load_address) {
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Erro: nao foi possivel abrir o arquivo ROM: " << filePath << std::endl;
        return false;
    }

    // Obtém tamanho do arquivo
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Verifica se cabe na memória
    if (load_address + size > SIZE) {
        std::cerr << "Erro: ROM muito grande (nao cabe na memoria)." << std::endl;
        return false;
    }

    // Lê o conteúdo para um buffer temporário
    std::vector<char> buffer(size);
    if (!file.read(buffer.data(), size)) {
        std::cerr << "Erro: falha ao ler ROM." << std::endl;
        return false;
    }

    // Copia o conteúdo do buffer para a memória
    for (std::size_t i = 0; i < static_cast<std::size_t>(size); ++i) {
        mem[load_address + i] = static_cast<uint8_t>(buffer[i]);
    }

    return true;
}

// Leitura de 1 byte
uint8_t Memory::read8(uint16_t address) const {
    if (!addressValid(address)) {
        std::cerr << "Aviso: tentativa de leitura fora da memoria (" << address << ")" << std::endl;
        return 0;
    }
    return mem[address];
}

// Escrita de 1 byte
void Memory::write8(uint16_t address, uint8_t value) {
    if (!addressValid(address)) {
        std::cerr << "Aviso: tentativa de escrita fora da memoria (" << address << ")" << std::endl;
        return;
    }
    mem[address] = value;
}


// Leitura de 2 bytes consecutivos (big-endian)
uint16_t Memory::read16(uint16_t address) const {
    if (!addressValid(address) || !addressValid(address + 1)) {
        std::cerr << "Aviso: leitura invalida de 16 bits na posicao " << address << std::endl;
        return 0;
    }
    // Combina dois bytes (big-endian: o mais significativo vem primeiro)
    return (mem[address] << 8) | mem[address + 1];
}

// permite acesso somente leitura à memória
const std::vector<uint8_t>& Memory::raw() const {
    return mem;
}

// Função auxiliar para verificar endereço válido
bool Memory::addressValid(uint16_t address) const {
    return address < SIZE;
}


// Carrega os 16 sprites padrão (0x0 a 0xF) na memória
// Cada caractere ocupa 5 bytes (total 80 bytes)
void Memory::loadBuiltinSprites() {
    static const uint8_t sprites[80] = {
        // 0
        0xF0, 0x90, 0x90, 0x90, 0xF0,
        // 1
        0x20, 0x60, 0x20, 0x20, 0x70,
        // 2
        0xF0, 0x10, 0xF0, 0x80, 0xF0,
        // 3
        0xF0, 0x10, 0xF0, 0x10, 0xF0,
        // 4
        0x90, 0x90, 0xF0, 0x10, 0x10,
        // 5
        0xF0, 0x80, 0xF0, 0x10, 0xF0,
        // 6
        0xF0, 0x80, 0xF0, 0x90, 0xF0,
        // 7
        0xF0, 0x10, 0x20, 0x40, 0x40,
        // 8
        0xF0, 0x90, 0xF0, 0x90, 0xF0,
        // 9
        0xF0, 0x90, 0xF0, 0x10, 0xF0,
        // A
        0xF0, 0x90, 0xF0, 0x90, 0x90,
        // B
        0xE0, 0x90, 0xE0, 0x90, 0xE0,
        // C
        0xF0, 0x80, 0x80, 0x80, 0xF0,
        // D
        0xE0, 0x90, 0x90, 0x90, 0xE0,
        // E
        0xF0, 0x80, 0xF0, 0x80, 0xF0,
        // F
        0xF0, 0x80, 0xF0, 0x80, 0x80
    };

    for (int i = 0; i < 80; ++i) {
        mem[i] = sprites[i];
    }
}
