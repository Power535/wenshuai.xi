#ifndef _SI2151_FIRMWARE_1_1_BUILD_2_H_
#define _SI2151_FIRMWARE_1_1_BUILD_2_H_

#define FIRMWARE_MAJOR        1
#define FIRMWARE_MINOR        1
#define BUILD_VERSION         2

#ifndef __FIRMWARE_STRUCT__
#define __FIRMWARE_STRUCT__
typedef struct firmware_struct {
	unsigned char firmware_len;
	unsigned char firmware_table[16];
} firmware_struct;
#endif /* __FIRMWARE_STRUCT__ */

firmware_struct Si2151_FW_1_1b2[] = {
{ 8 , { 0x05,0x11,0x69,0x62,0x2C,0xE5,0x01,0xC7 } },
{ 16 , { 0x0C,0x82,0x99,0xD0,0xF2,0x3C,0x86,0xC1,0x09,0x50,0xEE,0x98,0xB9,0x4B,0xE6,0xBB } },
{ 11 , { 0x0C,0x96,0x02,0x16,0xA2,0xBB,0xF7,0xF3,0x4A,0x1C,0xC0 } },
{ 8 , { 0x0C,0xA3,0x6A,0x94,0x81,0x27,0xA0,0x1F } },
{ 12 , { 0x33,0xDB,0x7E,0x12,0xF9,0x3C,0x4C,0xC3,0x21,0xE9,0x99,0x74 } },
{ 16 , { 0x09,0xBA,0x44,0x92,0x62,0x1A,0x97,0x77,0x09,0x26,0xAF,0xC1,0xCB,0x41,0x91,0xD4 } },
{ 16 , { 0x08,0x2F,0xAF,0x6E,0x85,0xB7,0x01,0xB7,0x0C,0x8A,0x7A,0x18,0x4F,0xEA,0x94,0x83 } }
};

#define FIRMWARE_LINES_1_1b2 (sizeof(Si2151_FW_1_1b2)/(sizeof(firmware_struct)))
#define RAM_SIG_1_1b2 0xA7ECE04E
#define RAM_CRC_1_1b2 0xD1F0

#endif /* _SI2151_FIRMWARE_1_1_BUILD_2_H_ */
