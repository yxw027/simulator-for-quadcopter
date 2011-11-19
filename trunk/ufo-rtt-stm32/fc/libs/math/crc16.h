/**
 * @file crc16.h
 * CRC-16 interface
 */

#ifndef _CRC16_H
#define _CRC16_H

/**
 * @addtogroup ufo
 * @{
 */

/**
 * @addtogroup math
 * @{
 */

/**
 * @defgroup crc16
 * crc16 support
 * @{
 */

/**
 * Generator Polynomial
 */
#define CRC-16  0x8005  /* x^16 + x^15 + x^2 + 1 */

/**
 * compute the CRC-16 for the data buffer
 *
 * @param crc previous CRC value
 * @param buffer data pointer
 * @param len number of bytes in the buffer
 * @return the updated CRC value
 */
uint16_t crc16(uint16_t crc, const uint8_t *buffer, int len);

/** 
 * @deprecated crc16 check only for VisualScope debug 
 */
unsigned short CRC_CHECK(unsigned char *Buf, unsigned char CRC_CNT);

/** @} */

/** @} */

/** @} */

#endif /* _CRC16_H */ 
