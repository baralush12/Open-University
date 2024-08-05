// This file, 'crc.cpp', provides the implementation of CRC (Cyclic Redundancy Check) functionalities.
// It includes the generation of a CRC lookup table and a function to calculate the CRC32 checksum.
// CRC is used for detecting errors in data transmission or storage.

#include <vector>
#include <cstdint>
#include "crc.h"

// Global array to hold the precomputed CRC table.
uint32_t crc_table[256];

void generate_crc_table() {
    // Generate the CRC lookup table used in the CRC32 calculation.
    // This function populates the crc_table with precomputed values for efficient CRC calculation.
    for (uint32_t i = 0; i < 256; i++) {
        uint32_t crc = i;
        for (uint32_t j = 8; j > 0; j--) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            }
            else {
                crc >>= 1;
            }
        }
        crc_table[i] = crc;
    }
}

uint32_t crc32(const std::vector<uint8_t>& data) {
    // Calculate the CRC32 checksum for the given data.
    // This function iterates through each byte of the data, computing the CRC32 checksum using the precomputed table.
    uint32_t crc = 0xFFFFFFFF;
    for (auto byte : data) {
        uint8_t lookup = (crc ^ byte) & 0xFF;
        crc = (crc >> 8) ^ crc_table[lookup];
    }
    return ~crc;
}
