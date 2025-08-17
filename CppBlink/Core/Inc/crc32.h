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

constexpr uint32_t CRC32K9_POLYNOMIAL =  0x6938392D;
constexpr  uint32_t TABLE_SIZE = 256;

//CRC-Tabelle für schnelle Berechnung
//uint32_t crc32k9_table[256];

// Fuktion zur Initialisierung der CRC-32K/9-Tabelle
constexpr std::array<uint32_t, TABLE_SIZE> crc32k9_init_table()
{
	  std::array<uint32_t, 256> table{};

	for (uint32_t i = 0; i < 256; i++)
	{
		uint32_t crc = i;							// Index
		for (int j = 0; j < 8; j++){
			if(crc & 1){
				crc = (crc >> 1)^ CRC32K9_POLYNOMIAL;
			} else {
				crc >>= 1;		// oder Bitverschiebung
			}
		}
		table[i] = crc;
	}
	 return table;
}



constexpr auto CRC32_TABLE = crc32k9_init_table();
#endif /* INC_CRC32_H_ */

/*
constexpr std::array<uint32_t, 256> make_crc32_table() {
    std::array<uint32_t, 256> table{};
    for (size_t i = 0; i < 256; ++i) {
        uint32_t crc = i;
        for (int j = 0; j < 8; ++j) {
            crc = (crc & 1) ? (crc >> 1) ^ 0xEDB88320 : crc >> 1;
        }
        table[i] = crc;
    }
    return table;
}*/


/*
 * void crc32k9_init_table(uint32_t table[TABLE_SIZE])
{

	for (uint32_t i = 0; i < TABLE_SIZE; i++)
	{
		uint32_t crc = i;							// Index
		for (int j = 0; j < 8; j++){
			if(crc & 1){
				crc = (crc >> 1)^ CRC32K9_POLYNOMIAL;
			} else {
				crc >>= 1;		// oder Bitverschiebung
			}
		}
		table[i] = crc;
	}
}
 */
