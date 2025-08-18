/*
 * crc32.cpp
 *
 *  Created on: Aug 17, 2025
 *      Author: malya
 */
#include "crc32.h"


void crc32k9_init_table_ram(uint32_t table[TABLE_SIZE], uint32_t polynomial)
{
	   for (uint32_t i = 0; i < TABLE_SIZE; i++)
	   {
	       uint32_t crc = (i << 24);							// Index
	       for (int j = 0; j < 8; j++)
	       {   if((crc & 0x80000000) != 0)
	           {
	               crc = (crc << 1) ^ CRC32K9_POLYNOMIAL;
	           }
	           else
	           {
	               crc <<= 1;		// oder Bitverschiebung
	           }
	       }
	       table[i] = crc;
	   }
}

uint32_t crc32_calc(const uint8_t data[8], const uint32_t crc32_array[256])
{

	uint32_t crc32_sum	= START_POLYNOMIAL;

	for(int n_byte = 0; n_byte < 8; n_byte++)
	{
		uint8_t pos = (uint8_t)((crc32_sum ^ ((uint32_t)data[n_byte] << 24 )) >> 24);

		crc32_sum = (uint32_t)((crc32_sum << 8) ^ (uint32_t)(crc32_array[pos]));

	}
	return crc32_sum;
}
