#pragma once
#include <cstdint>
#include <string>
#include <vector>

class Memory {
public:
    static constexpr std::size_t SIZE = 4096;
    static constexpr uint16_t DEFAULT_LOAD_ADDRESS = 0x200;

    Memory();
    ~Memory();

    void reset();
    bool loadROM(const std::string& filePath, uint16_t load_address = DEFAULT_LOAD_ADDRESS);
    uint8_t read8(uint16_t address) const;
    void write8(uint16_t address, uint8_t value);
    uint16_t read16(uint16_t address) const;

    const std::vector<uint8_t>& raw() const; // 🔹 ADICIONE ESTA LINHA

private:
    std::vector<uint8_t> mem;
    void loadBuiltinSprites();
    bool addressValid(uint16_t address) const;
};