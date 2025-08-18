/*
 * crc32.h
 *
 *  Created on: Aug 17, 2025
 *      Author: malya
 */

#ifndef INC_CRC32_H_
#define INC_CRC32_H_

#pragma once
#include "main.h"
#include <array>
#include <cstdint>

#define  CRC32K9_POLYNOMIAL   0x6938392D
#define   TABLE_SIZE  256
#define  START_POLYNOMIAL  0xFFFFFFFF


// Fuktion zur Initialisierung der CRC-32K/9-Tabelle
/*
 * Function for FLASH Memory
constexpr  std::array<uint32_t, 256> crc32k9_init_table()
{
    std::array<uint32_t, 256> table{};


    for (uint32_t i = 0; i < 256; i++)
    {
        uint32_t crc = (i << 24);							// Index
        for (int j = 0; j < 8; j++) {
            if((crc & 0x80000000) != 0)
            {
                crc = (crc << 1) ^ CRC32K9_POLYNOMIAL;
            }
            else {
                crc <<= 1;		// oder Bitverschiebung
            }
        }
        table[i] = crc;
    }
    return table;

}

constexpr auto CRC32_TABLE = crc32k9_init_table();*/

void crc32k9_init_table_ram(uint32_t arr[TABLE_SIZE], uint32_t polynomial);
uint32_t crc32_calc(const uint8_t data[8], const uint32_t crc32_array[256]);


#endif /* INC_CRC32_H_ */



