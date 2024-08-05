#ifndef CRC_H
#define CRC_H

#include <vector>
#include <cstdint>

// The CRCUtils header defines functions for generating a CRC lookup table
// and computing the CRC32 checksum. These functions are used for ensuring data integrity
// through CRC (Cyclic Redundancy Check) calculations.

// Generate the CRC lookup table for efficient CRC calculations.
void generate_crc_table();

// Calculate the CRC32 checksum of the given data.
uint32_t crc32(const std::vector<uint8_t>& data);

#endif // CRC_H
