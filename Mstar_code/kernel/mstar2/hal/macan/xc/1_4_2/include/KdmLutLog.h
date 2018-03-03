/****************************************************************************
* This product contains one or more programs protected under international
* and U.S. copyright laws as unpublished works.  They are confidential and
* proprietary to Dolby Laboratories.  Their reproduction or disclosure, in
* whole or in part, or the production of derivative works therefrom without
* the express permission of Dolby Laboratories is prohibited.
*
*             Copyright 2011 - 2015 by Dolby Laboratories.
* 			              All rights reserved.
****************************************************************************/
#ifndef KDMLUTLOG_H
#define KDMLUTLOG_H

#include "KdmTypeFxpCmn.h"

const uint16_t log10Lut[DEF_DEGAMMAR_LOG_LUT_SIZE] = {
0x4d10,
0x39cc,
0x34fb,
0x322a,
0x302a,
0x2e9d,
0x2d58,
0x2c46,
0x2b59,
0x2a87,
0x29cc,
0x2922,
0x2887,
0x27f9,
0x2775,
0x26fb,
0x2688,
0x261c,
0x25b6,
0x2556,
0x24fb,
0x24a4,
0x2451,
0x2402,
0x23b6,
0x236e,
0x2328,
0x22e5,
0x22a4,
0x2266,
0x222a,
0x21ef,
0x21b7,
0x2180,
0x214b,
0x2117,
0x20e5,
0x20b4,
0x2085,
0x2057,
0x202a,
0x1ffe,
0x1fd3,
0x1fa9,
0x1f80,
0x1f58,
0x1f31,
0x1f0b,
0x1ee5,
0x1ec1,
0x1e9d,
0x1e7a,
0x1e57,
0x1e35,
0x1e14,
0x1df3,
0x1dd3,
0x1db4,
0x1d95,
0x1d76,
0x1d58,
0x1d3b,
0x1d1e,
0x1d02,
0x1ce6,
0x1cca,
0x1caf,
0x1c94,
0x1c7a,
0x1c60,
0x1c46,
0x1c2d,
0x1c14,
0x1bfc,
0x1be3,
0x1bcc,
0x1bb4,
0x1b9d,
0x1b86,
0x1b6f,
0x1b59,
0x1b43,
0x1b2d,
0x1b17,
0x1b02,
0x1aed,
0x1ad8,
0x1ac4,
0x1aaf,
0x1a9b,
0x1a87,
0x1a74,
0x1a60,
0x1a4d,
0x1a3a,
0x1a27,
0x1a14,
0x1a02,
0x19f0,
0x19de,
0x19cc,
0x19ba,
0x19a9,
0x1997,
0x1986,
0x1975,
0x1964,
0x1953,
0x1943,
0x1932,
0x1922,
0x1912,
0x1902,
0x18f2,
0x18e3,
0x18d3,
0x18c4,
0x18b5,
0x18a5,
0x1896,
0x1887,
0x1879,
0x186a,
0x185c,
0x184d,
0x183f,
0x1831,
0x1823,
0x1815,
0x1807,
0x17f9,
0x17eb,
0x17de,
0x17d0,
0x17c3,
0x17b6,
0x17a9,
0x179c,
0x178f,
0x1782,
0x1775,
0x1769,
0x175c,
0x1750,
0x1743,
0x1737,
0x172b,
0x171e,
0x1712,
0x1706,
0x16fb,
0x16ef,
0x16e3,
0x16d7,
0x16cc,
0x16c0,
0x16b5,
0x16a9,
0x169e,
0x1693,
0x1688,
0x167d,
0x1672,
0x1667,
0x165c,
0x1651,
0x1646,
0x163c,
0x1631,
0x1626,
0x161c,
0x1611,
0x1607,
0x15fd,
0x15f3,
0x15e8,
0x15de,
0x15d4,
0x15ca,
0x15c0,
0x15b6,
0x15ac,
0x15a3,
0x1599,
0x158f,
0x1585,
0x157c,
0x1572,
0x1569,
0x155f,
0x1556,
0x154d,
0x1543,
0x153a,
0x1531,
0x1528,
0x151f,
0x1516,
0x150d,
0x1504,
0x14fb,
0x14f2,
0x14e9,
0x14e0,
0x14d8,
0x14cf,
0x14c6,
0x14be,
0x14b5,
0x14ac,
0x14a4,
0x149c,
0x1493,
0x148b,
0x1482,
0x147a,
0x1472,
0x146a,
0x1461,
0x1459,
0x1451,
0x1449,
0x1441,
0x1439,
0x1431,
0x1429,
0x1421,
0x141a,
0x1412,
0x140a,
0x1402,
0x13fa,
0x13f3,
0x13eb,
0x13e3,
0x13dc,
0x13d4,
0x13cd,
0x13c5,
0x13be,
0x13b6,
0x13af,
0x13a8,
0x13a0,
0x1399,
0x1392,
0x138b,
0x1383,
0x137c,
0x1375,
0x136e,
0x1367,
0x1360,
0x1359,
0x1352,
0x134b,
0x1344,
0x133d,
0x1336,
0x132f,
0x1328,
0x1321,
0x131a,
0x1314,
0x130d,
0x1306,
0x12ff,
0x12f9,
0x12f2,
0x12ec,
0x12e5,
0x12de,
0x12d8,
0x12d1,
0x12cb,
0x12c4,
0x12be,
0x12b7,
0x12b1,
0x12ab,
0x12a4,
0x129e,
0x1298,
0x1291,
0x128b,
0x1285,
0x127f,
0x1278,
0x1272,
0x126c,
0x1266,
0x1260,
0x125a,
0x1254,
0x124d,
0x1247,
0x1241,
0x123b,
0x1235,
0x122f,
0x122a,
0x1224,
0x121e,
0x1218,
0x1212,
0x120c,
0x1206,
0x1200,
0x11fb,
0x11f5,
0x11ef,
0x11e9,
0x11e4,
0x11de,
0x11d8,
0x11d3,
0x11cd,
0x11c7,
0x11c2,
0x11bc,
0x11b7,
0x11b1,
0x11ac,
0x11a6,
0x11a1,
0x119b,
0x1196,
0x1190,
0x118b,
0x1185,
0x1180,
0x117b,
0x1175,
0x1170,
0x116b,
0x1165,
0x1160,
0x115b,
0x1155,
0x1150,
0x114b,
0x1146,
0x1140,
0x113b,
0x1136,
0x1131,
0x112c,
0x1127,
0x1121,
0x111c,
0x1117,
0x1112,
0x110d,
0x1108,
0x1103,
0x10fe,
0x10f9,
0x10f4,
0x10ef,
0x10ea,
0x10e5,
0x10e0,
0x10db,
0x10d6,
0x10d2,
0x10cd,
0x10c8,
0x10c3,
0x10be,
0x10b9,
0x10b4,
0x10b0,
0x10ab,
0x10a6,
0x10a1,
0x109d,
0x1098,
0x1093,
0x108e,
0x108a,
0x1085,
0x1080,
0x107c,
0x1077,
0x1072,
0x106e,
0x1069,
0x1065,
0x1060,
0x105b,
0x1057,
0x1052,
0x104e,
0x1049,
0x1045,
0x1040,
0x103c,
0x1037,
0x1033,
0x102e,
0x102a,
0x1025,
0x1021,
0x101c,
0x1018,
0x1014,
0x100f,
0x100b,
0x1007,
0x1002,
0xffe,
0xff9,
0xff5,
0xff1,
0xfed,
0xfe8,
0xfe4,
0xfe0,
0xfdb,
0xfd7,
0xfd3,
0xfcf,
0xfcb,
0xfc6,
0xfc2,
0xfbe,
0xfba,
0xfb6,
0xfb1,
0xfad,
0xfa9,
0xfa5,
0xfa1,
0xf9d,
0xf99,
0xf95,
0xf90,
0xf8c,
0xf88,
0xf84,
0xf80,
0xf7c,
0xf78,
0xf74,
0xf70,
0xf6c,
0xf68,
0xf64,
0xf60,
0xf5c,
0xf58,
0xf54,
0xf50,
0xf4c,
0xf48,
0xf45,
0xf41,
0xf3d,
0xf39,
0xf35,
0xf31,
0xf2d,
0xf29,
0xf26,
0xf22,
0xf1e,
0xf1a,
0xf16,
0xf12,
0xf0f,
0xf0b,
0xf07,
0xf03,
0xf00,
0xefc,
0xef8,
0xef4,
0xef1,
0xeed,
0xee9,
0xee5,
0xee2,
0xede,
0xeda,
0xed7,
0xed3,
0xecf,
0xecc,
0xec8,
0xec4,
0xec1,
0xebd,
0xeba,
0xeb6,
0xeb2,
0xeaf,
0xeab,
0xea8,
0xea4,
0xea0,
0xe9d,
0xe99,
0xe96,
0xe92,
0xe8f,
0xe8b,
0xe88,
0xe84,
0xe81,
0xe7d,
0xe7a,
0xe76,
0xe73,
0xe6f,
0xe6c,
0xe68,
0xe65,
0xe61,
0xe5e,
0xe5a,
0xe57,
0xe54,
0xe50,
0xe4d,
0xe49,
0xe46,
0xe43,
0xe3f,
0xe3c,
0xe39,
0xe35,
0xe32,
0xe2e,
0xe2b,
0xe28,
0xe24,
0xe21,
0xe1e,
0xe1b,
0xe17,
0xe14,
0xe11,
0xe0d,
0xe0a,
0xe07,
0xe04,
0xe00,
0xdfd,
0xdfa,
0xdf7,
0xdf3,
0xdf0,
0xded,
0xdea,
0xde6,
0xde3,
0xde0,
0xddd,
0xdda,
0xdd6,
0xdd3,
0xdd0,
0xdcd,
0xdca,
0xdc7,
0xdc3,
0xdc0,
0xdbd,
0xdba,
0xdb7,
0xdb4,
0xdb1,
0xdad,
0xdaa,
0xda7,
0xda4,
0xda1,
0xd9e,
0xd9b,
0xd98,
0xd95,
0xd92,
0xd8f,
0xd8c,
0xd89,
0xd86,
0xd82,
0xd7f,
0xd7c,
0xd79,
0xd76,
0xd73,
0xd70,
0xd6d,
0xd6a,
0xd67,
0xd64,
0xd61,
0xd5e,
0xd5b,
0xd58,
0xd56,
0xd53,
0xd50,
0xd4d,
0xd4a,
0xd47,
0xd44,
0xd41,
0xd3e,
0xd3b,
0xd38,
0xd35,
0xd32,
0xd2f,
0xd2d,
0xd2a,
0xd27,
0xd24,
0xd21,
0xd1e,
0xd1b,
0xd18,
0xd16,
0xd13,
0xd10,
0xd0d,
0xd0a,
0xd07,
0xd05,
0xd02,
0xcff,
0xcfc,
0xcf9,
0xcf6,
0xcf4,
0xcf1,
0xcee,
0xceb,
0xce8,
0xce6,
0xce3,
0xce0,
0xcdd,
0xcdb,
0xcd8,
0xcd5,
0xcd2,
0xcd0,
0xccd,
0xcca,
0xcc7,
0xcc5,
0xcc2,
0xcbf,
0xcbc,
0xcba,
0xcb7,
0xcb4,
0xcb2,
0xcaf,
0xcac,
0xcaa,
0xca7,
0xca4,
0xca2,
0xc9f,
0xc9c,
0xc9a,
0xc97,
0xc94,
0xc92,
0xc8f,
0xc8c,
0xc8a,
0xc87,
0xc84,
0xc82,
0xc7f,
0xc7c,
0xc7a,
0xc77,
0xc75,
0xc72,
0xc6f,
0xc6d,
0xc6a,
0xc68,
0xc65,
0xc62,
0xc60,
0xc5d,
0xc5b,
0xc58,
0xc56,
0xc53,
0xc50,
0xc4e,
0xc4b,
0xc49,
0xc46,
0xc44,
0xc41,
0xc3f,
0xc3c,
0xc3a,
0xc37,
0xc35,
0xc32,
0xc30,
0xc2d,
0xc2b,
0xc28,
0xc26,
0xc23,
0xc21,
0xc1e,
0xc1c,
0xc19,
0xc17,
0xc14,
0xc12,
0xc0f,
0xc0d,
0xc0a,
0xc08,
0xc05,
0xc03,
0xc01,
0xbfe,
0xbfc,
0xbf9,
0xbf7,
0xbf4,
0xbf2,
0xbef,
0xbed,
0xbeb,
0xbe8,
0xbe6,
0xbe3,
0xbe1,
0xbdf,
0xbdc,
0xbda,
0xbd7,
0xbd5,
0xbd3,
0xbd0,
0xbce,
0xbcc,
0xbc9,
0xbc7,
0xbc4,
0xbc2,
0xbc0,
0xbbd,
0xbbb,
0xbb9,
0xbb6,
0xbb4,
0xbb2,
0xbaf,
0xbad,
0xbab,
0xba8,
0xba6,
0xba4,
0xba1,
0xb9f,
0xb9d,
0xb9a,
0xb98,
0xb96,
0xb94,
0xb91,
0xb8f,
0xb8d,
0xb8a,
0xb88,
0xb86,
0xb83,
0xb81,
0xb7f,
0xb7d,
0xb7a,
0xb78,
0xb76,
0xb74,
0xb71,
0xb6f,
0xb6d,
0xb6b,
0xb68,
0xb66,
0xb64,
0xb62,
0xb5f,
0xb5d,
0xb5b,
0xb59,
0xb57,
0xb54,
0xb52,
0xb50,
0xb4e,
0xb4b,
0xb49,
0xb47,
0xb45,
0xb43,
0xb40,
0xb3e,
0xb3c,
0xb3a,
0xb38,
0xb36,
0xb33,
0xb31,
0xb2f,
0xb2d,
0xb2b,
0xb28,
0xb26,
0xb24,
0xb22,
0xb20,
0xb1e,
0xb1c,
0xb19,
0xb17,
0xb15,
0xb13,
0xb11,
0xb0f,
0xb0d,
0xb0a,
0xb08,
0xb06,
0xb04,
0xb02,
0xb00,
0xafe,
0xafc,
0xaf9,
0xaf7,
0xaf5,
0xaf3,
0xaf1,
0xaef,
0xaed,
0xaeb,
0xae9,
0xae7,
0xae5,
0xae2,
0xae0,
0xade,
0xadc,
0xada,
0xad8,
0xad6,
0xad4,
0xad2,
0xad0,
0xace,
0xacc,
0xaca,
0xac8,
0xac6,
0xac4,
0xac1,
0xabf,
0xabd,
0xabb,
0xab9,
0xab7,
0xab5,
0xab3,
0xab1,
0xaaf,
0xaad,
0xaab,
0xaa9,
0xaa7,
0xaa5,
0xaa3,
0xaa1,
0xa9f,
0xa9d,
0xa9b,
0xa99,
0xa97,
0xa95,
0xa93,
0xa91,
0xa8f,
0xa8d,
0xa8b,
0xa89,
0xa87,
0xa85,
0xa83,
0xa81,
0xa7f,
0xa7d,
0xa7b,
0xa79,
0xa77,
0xa76,
0xa74,
0xa72,
0xa70,
0xa6e,
0xa6c,
0xa6a,
0xa68,
0xa66,
0xa64,
0xa62,
0xa60,
0xa5e,
0xa5c,
0xa5a,
0xa58,
0xa56,
0xa55,
0xa53,
0xa51,
0xa4f,
0xa4d,
0xa4b,
0xa49,
0xa47,
0xa45,
0xa43,
0xa41,
0xa40,
0xa3e,
0xa3c,
0xa3a,
0xa38,
0xa36,
0xa34,
0xa32,
0xa30,
0xa2f,
0xa2d,
0xa2b,
0xa29,
0xa27,
0xa25,
0xa23,
0xa21,
0xa20,
0xa1e,
0xa1c,
0xa1a,
0xa18,
0xa16,
0xa14,
0xa13,
0xa11,
0xa0f,
0xa0d,
0xa0b,
0xa09,
0xa07,
0xa06,
0xa04,
0xa02,
0xa00,
0x9fe,
0x9fc,
0x9fb,
0x9f9,
0x9f7,
0x9f5,
0x9f3,
0x9f2,
0x9f0,
0x9ee,
0x9ec,
0x9ea,
0x9e8,
0x9e7,
0x9e5,
0x9e3,
0x9e1,
0x9df,
0x9de,
0x9dc,
0x9da,
0x9d8,
0x9d6,
0x9d5,
0x9d3,
0x9d1,
0x9cf,
0x9ce,
0x9cc,
0x9ca,
0x9c8,
0x9c6,
0x9c5,
0x9c3,
0x9c1,
0x9bf,
0x9be,
0x9bc,
0x9ba,
0x9b8,
0x9b7,
0x9b5,
0x9b3,
0x9b1,
0x9b0,
0x9ae,
0x9ac,
0x9aa,
0x9a9,
0x9a7,
0x9a5,
0x9a3,
0x9a2,
0x9a0,
0x99e,
0x99c,
0x99b,
0x999,
0x997,
0x995,
0x994,
0x992,
0x990,
0x98f,
0x98d,
0x98b,
0x989,
0x988,
0x986,
0x984,
0x983,
0x981,
0x97f,
0x97d,
0x97c,
0x97a,
0x978,
0x977,
0x975,
0x973,
0x972,
0x970,
0x96e,
0x96d,
0x96b,
0x969,
0x967,
0x966,
0x964,
0x962,
0x961,
0x95f,
0x95d,
0x95c,
0x95a,
0x958,
0x957,
0x955,
0x953,
0x952,
0x950,
0x94e,
0x94d,
0x94b,
0x949,
0x948,
0x946,
0x945,
0x943,
0x941,
0x940,
0x93e,
0x93c,
0x93b,
0x939,
0x937,
0x936,
0x934,
0x932,
0x931,
0x92f,
0x92e,
0x92c,
0x92a,
0x929,
0x927,
0x925,
0x924,
0x922,
0x921,
0x91f,
0x91d,
0x91c,
0x91a,
0x919,
0x917,
0x915,
0x914,
0x912,
0x911,
0x90f,
0x90d,
0x90c,
0x90a,
0x909,
0x907,
0x905,
0x904,
0x902,
0x901,
0x8ff,
0x8fd,
0x8fc,
0x8fa,
0x8f9,
0x8f7,
0x8f6,
0x8f4,
0x8f2,
0x8f1,
0x8ef,
0x8ee,
0x8ec,
0x8eb,
0x8e9,
0x8e7,
0x8e6,
0x8e4,
0x8e3,
0x8e1,
0x8e0,
0x8de,
0x8dc,
0x8db,
0x8d9,
0x8d8,
0x8d6,
0x8d5,
0x8d3,
0x8d2,
0x8d0,
0x8cf,
0x8cd,
0x8cb,
0x8ca,
0x8c8,
0x8c7,
0x8c5,
0x8c4,
0x8c2,
0x8c1,
0x8bf,
0x8be,
0x8bc,
0x8bb,
0x8b9,
0x8b8,
0x8b6,
0x8b5,
0x8b3,
0x8b1,
0x8b0,
0x8ae,
0x8ad,
0x8ab,
0x8aa,
0x8a8,
0x8a7,
0x8a5,
0x8a4,
0x8a2,
0x8a1,
0x89f,
0x89e,
0x89c,
0x89b,
0x899,
0x898,
0x896,
0x895,
0x893,
0x892,
0x890,
0x88f,
0x88d,
0x88c,
0x88a,
0x889,
0x887,
0x886,
0x885,
0x883,
0x882,
0x880,
0x87f,
0x87d,
0x87c,
0x87a,
0x879,
0x877,
0x876,
0x874,
0x873,
0x871,
0x870,
0x86e,
0x86d,
0x86c,
0x86a,
0x869,
0x867,
0x866,
0x864,
0x863,
0x861,
0x860,
0x85e,
0x85d,
0x85c,
0x85a,
0x859,
0x857,
0x856,
0x854,
0x853,
0x851,
0x850,
0x84f,
0x84d,
0x84c,
0x84a,
0x849,
0x847,
0x846,
0x845,
0x843,
0x842,
0x840,
0x83f,
0x83d,
0x83c,
0x83b,
0x839,
0x838,
0x836,
0x835,
0x834,
0x832,
0x831,
0x82f,
0x82e,
0x82c,
0x82b,
0x82a,
0x828,
0x827,
0x825,
0x824,
0x823,
0x821,
0x820,
0x81e,
0x81d,
0x81c,
0x81a,
0x819,
0x817,
0x816,
0x815,
0x813,
0x812,
0x810,
0x80f,
0x80e,
0x80c,
0x80b,
0x80a,
0x808,
0x807,
0x805,
0x804,
0x803,
0x801,
0x800,
0x7ff,
0x7fd,
0x7fc,
0x7fa,
0x7f9,
0x7f8,
0x7f6,
0x7f5,
0x7f4,
0x7f2,
0x7f1,
0x7f0,
0x7ee,
0x7ed,
0x7eb,
0x7ea,
0x7e9,
0x7e7,
0x7e6,
0x7e5,
0x7e3,
0x7e2,
0x7e1,
0x7df,
0x7de,
0x7dd,
0x7db,
0x7da,
0x7d9,
0x7d7,
0x7d6,
0x7d5,
0x7d3,
0x7d2,
0x7d0,
0x7cf,
0x7ce,
0x7cc,
0x7cb,
0x7ca,
0x7c8,
0x7c7,
0x7c6,
0x7c4,
0x7c3,
0x7c2,
0x7c1,
0x7bf,
0x7be,
0x7bd,
0x7bb,
0x7ba,
0x7b9,
0x7b7,
0x7b6,
0x7b5,
0x7b3,
0x7b2,
0x7b1,
0x7af,
0x7ae,
0x7ad,
0x7ab,
0x7aa,
0x7a9,
0x7a8,
0x7a6,
0x7a5,
0x7a4,
0x7a2,
0x7a1,
0x7a0,
0x79e,
0x79d,
0x79c,
0x79a,
0x799,
0x798,
0x797,
0x795,
0x794,
0x793,
0x791,
0x790,
0x78f,
0x78e,
0x78c,
0x78b,
0x78a,
0x788,
0x787,
0x786,
0x785,
0x783,
0x782,
0x781,
0x77f,
0x77e,
0x77d,
0x77c,
0x77a,
0x779,
0x778,
0x777,
0x775,
0x774,
0x773,
0x771,
0x770,
0x76f,
0x76e,
0x76c,
0x76b,
0x76a,
0x769,
0x767,
0x766,
0x765,
0x764,
0x762,
0x761,
0x760,
0x75f,
0x75d,
0x75c,
0x75b,
0x75a,
0x758,
0x757,
0x756,
0x755,
0x753,
0x752,
0x751,
0x750,
0x74e,
0x74d,
0x74c,
0x74b,
0x749,
0x748,
0x747,
0x746,
0x744,
0x743,
0x742,
0x741,
0x73f,
0x73e,
0x73d,
0x73c,
0x73b,
0x739,
0x738,
0x737,
0x736,
0x734,
0x733,
0x732,
0x731,
0x72f,
0x72e,
0x72d,
0x72c,
0x72b,
0x729,
0x728,
0x727,
0x726,
0x725,
0x723,
0x722,
0x721,
0x720,
0x71e,
0x71d,
0x71c,
0x71b,
0x71a,
0x718,
0x717,
0x716,
0x715,
0x714,
0x712,
0x711,
0x710,
0x70f,
0x70e,
0x70c,
0x70b,
0x70a,
0x709,
0x708,
0x706,
0x705,
0x704,
0x703,
0x702,
0x700,
0x6ff,
0x6fe,
0x6fd,
0x6fc,
0x6fb,
0x6f9,
0x6f8,
0x6f7,
0x6f6,
0x6f5,
0x6f3,
0x6f2,
0x6f1,
0x6f0,
0x6ef,
0x6ee,
0x6ec,
0x6eb,
0x6ea,
0x6e9,
0x6e8,
0x6e6,
0x6e5,
0x6e4,
0x6e3,
0x6e2,
0x6e1,
0x6df,
0x6de,
0x6dd,
0x6dc,
0x6db,
0x6da,
0x6d8,
0x6d7,
0x6d6,
0x6d5,
0x6d4,
0x6d3,
0x6d1,
0x6d0,
0x6cf,
0x6ce,
0x6cd,
0x6cc,
0x6cb,
0x6c9,
0x6c8,
0x6c7,
0x6c6,
0x6c5,
0x6c4,
0x6c2,
0x6c1,
0x6c0,
0x6bf,
0x6be,
0x6bd,
0x6bc,
0x6ba,
0x6b9,
0x6b8,
0x6b7,
0x6b6,
0x6b5,
0x6b4,
0x6b2,
0x6b1,
0x6b0,
0x6af,
0x6ae,
0x6ad,
0x6ac,
0x6ab,
0x6a9,
0x6a8,
0x6a7,
0x6a6,
0x6a5,
0x6a4,
0x6a3,
0x6a1,
0x6a0,
0x69f,
0x69e,
0x69d,
0x69c,
0x69b,
0x69a,
0x698,
0x697,
0x696,
0x695,
0x694,
0x693,
0x692,
0x691,
0x690,
0x68e,
0x68d,
0x68c,
0x68b,
0x68a,
0x689,
0x688,
0x687,
0x685,
0x684,
0x683,
0x682,
0x681,
0x680,
0x67f,
0x67e,
0x67d,
0x67c,
0x67a,
0x679,
0x678,
0x677,
0x676,
0x675,
0x674,
0x673,
0x672,
0x671,
0x66f,
0x66e,
0x66d,
0x66c,
0x66b,
0x66a,
0x669,
0x668,
0x667,
0x666,
0x664,
0x663,
0x662,
0x661,
0x660,
0x65f,
0x65e,
0x65d,
0x65c,
0x65b,
0x65a,
0x659,
0x657,
0x656,
0x655,
0x654,
0x653,
0x652,
0x651,
0x650,
0x64f,
0x64e,
0x64d,
0x64c,
0x64b,
0x649,
0x648,
0x647,
0x646,
0x645,
0x644,
0x643,
0x642,
0x641,
0x640,
0x63f,
0x63e,
0x63d,
0x63c,
0x63a,
0x639,
0x638,
0x637,
0x636,
0x635,
0x634,
0x633,
0x632,
0x631,
0x630,
0x62f,
0x62e,
0x62d,
0x62c,
0x62b,
0x62a,
0x628,
0x627,
0x626,
0x625,
0x624,
0x623,
0x622,
0x621,
0x620,
0x61f,
0x61e,
0x61d,
0x61c,
0x61b,
0x61a,
0x619,
0x618,
0x617,
0x616,
0x615,
0x614,
0x612,
0x611,
0x610,
0x60f,
0x60e,
0x60d,
0x60c,
0x60b,
0x60a,
0x609,
0x608,
0x607,
0x606,
0x605,
0x604,
0x603,
0x602,
0x601,
0x600,
0x5ff,
0x5fe,
0x5fd,
0x5fc,
0x5fb,
0x5fa,
0x5f9,
0x5f8,
0x5f7,
0x5f6,
0x5f5,
0x5f4,
0x5f3,
0x5f1,
0x5f0,
0x5ef,
0x5ee,
0x5ed,
0x5ec,
0x5eb,
0x5ea,
0x5e9,
0x5e8,
0x5e7,
0x5e6,
0x5e5,
0x5e4,
0x5e3,
0x5e2,
0x5e1,
0x5e0,
0x5df,
0x5de,
0x5dd,
0x5dc,
0x5db,
0x5da,
0x5d9,
0x5d8,
0x5d7,
0x5d6,
0x5d5,
0x5d4,
0x5d3,
0x5d2,
0x5d1,
0x5d0,
0x5cf,
0x5ce,
0x5cd,
0x5cc,
0x5cb,
0x5ca,
0x5c9,
0x5c8,
0x5c7,
0x5c6,
0x5c5,
0x5c4,
0x5c3,
0x5c2,
0x5c1,
0x5c0,
0x5bf,
0x5be,
0x5bd,
0x5bc,
0x5bb,
0x5ba,
0x5b9,
0x5b8,
0x5b7,
0x5b6,
0x5b5,
0x5b4,
0x5b3,
0x5b2,
0x5b1,
0x5b0,
0x5af,
0x5ae,
0x5ad,
0x5ac,
0x5ab,
0x5aa,
0x5a9,
0x5a8,
0x5a7,
0x5a6,
0x5a5,
0x5a4,
0x5a4,
0x5a3,
0x5a2,
0x5a1,
0x5a0,
0x59f,
0x59e,
0x59d,
0x59c,
0x59b,
0x59a,
0x599,
0x598,
0x597,
0x596,
0x595,
0x594,
0x593,
0x592,
0x591,
0x590,
0x58f,
0x58e,
0x58d,
0x58c,
0x58b,
0x58a,
0x589,
0x588,
0x587,
0x586,
0x585,
0x584,
0x584,
0x583,
0x582,
0x581,
0x580,
0x57f,
0x57e,
0x57d,
0x57c,
0x57b,
0x57a,
0x579,
0x578,
0x577,
0x576,
0x575,
0x574,
0x573,
0x572,
0x571,
0x570,
0x56f,
0x56f,
0x56e,
0x56d,
0x56c,
0x56b,
0x56a,
0x569,
0x568,
0x567,
0x566,
0x565,
0x564,
0x563,
0x562,
0x561,
0x560,
0x55f,
0x55e,
0x55e,
0x55d,
0x55c,
0x55b,
0x55a,
0x559,
0x558,
0x557,
0x556,
0x555,
0x554,
0x553,
0x552,
0x551,
0x550,
0x54f,
0x54f,
0x54e,
0x54d,
0x54c,
0x54b,
0x54a,
0x549,
0x548,
0x547,
0x546,
0x545,
0x544,
0x543,
0x542,
0x542,
0x541,
0x540,
0x53f,
0x53e,
0x53d,
0x53c,
0x53b,
0x53a,
0x539,
0x538,
0x537,
0x536,
0x536,
0x535,
0x534,
0x533,
0x532,
0x531,
0x530,
0x52f,
0x52e,
0x52d,
0x52c,
0x52b,
0x52b,
0x52a,
0x529,
0x528,
0x527,
0x526,
0x525,
0x524,
0x523,
0x522,
0x521,
0x521,
0x520,
0x51f,
0x51e,
0x51d,
0x51c,
0x51b,
0x51a,
0x519,
0x518,
0x517,
0x517,
0x516,
0x515,
0x514,
0x513,
0x512,
0x511,
0x510,
0x50f,
0x50e,
0x50e,
0x50d,
0x50c,
0x50b,
0x50a,
0x509,
0x508,
0x507,
0x506,
0x505,
0x505,
0x504,
0x503,
0x502,
0x501,
0x500,
0x4ff,
0x4fe,
0x4fd,
0x4fd,
0x4fc,
0x4fb,
0x4fa,
0x4f9,
0x4f8,
0x4f7,
0x4f6,
0x4f5,
0x4f5,
0x4f4,
0x4f3,
0x4f2,
0x4f1,
0x4f0,
0x4ef,
0x4ee,
0x4ed,
0x4ed,
0x4ec,
0x4eb,
0x4ea,
0x4e9,
0x4e8,
0x4e7,
0x4e6,
0x4e6,
0x4e5,
0x4e4,
0x4e3,
0x4e2,
0x4e1,
0x4e0,
0x4df,
0x4df,
0x4de,
0x4dd,
0x4dc,
0x4db,
0x4da,
0x4d9,
0x4d8,
0x4d8,
0x4d7,
0x4d6,
0x4d5,
0x4d4,
0x4d3,
0x4d2,
0x4d1,
0x4d1,
0x4d0,
0x4cf,
0x4ce,
0x4cd,
0x4cc,
0x4cb,
0x4cb,
0x4ca,
0x4c9,
0x4c8,
0x4c7,
0x4c6,
0x4c5,
0x4c4,
0x4c4,
0x4c3,
0x4c2,
0x4c1,
0x4c0,
0x4bf,
0x4be,
0x4be,
0x4bd,
0x4bc,
0x4bb,
0x4ba,
0x4b9,
0x4b8,
0x4b8,
0x4b7,
0x4b6,
0x4b5,
0x4b4,
0x4b3,
0x4b2,
0x4b2,
0x4b1,
0x4b0,
0x4af,
0x4ae,
0x4ad,
0x4ac,
0x4ac,
0x4ab,
0x4aa,
0x4a9,
0x4a8,
0x4a7,
0x4a7,
0x4a6,
0x4a5,
0x4a4,
0x4a3,
0x4a2,
0x4a1,
0x4a1,
0x4a0,
0x49f,
0x49e,
0x49d,
0x49c,
0x49c,
0x49b,
0x49a,
0x499,
0x498,
0x497,
0x496,
0x496,
0x495,
0x494,
0x493,
0x492,
0x491,
0x491,
0x490,
0x48f,
0x48e,
0x48d,
0x48c,
0x48c,
0x48b,
0x48a,
0x489,
0x488,
0x487,
0x487,
0x486,
0x485,
0x484,
0x483,
0x482,
0x482,
0x481,
0x480,
0x47f,
0x47e,
0x47d,
0x47d,
0x47c,
0x47b,
0x47a,
0x479,
0x478,
0x478,
0x477,
0x476,
0x475,
0x474,
0x474,
0x473,
0x472,
0x471,
0x470,
0x46f,
0x46f,
0x46e,
0x46d,
0x46c,
0x46b,
0x46a,
0x46a,
0x469,
0x468,
0x467,
0x466,
0x466,
0x465,
0x464,
0x463,
0x462,
0x461,
0x461,
0x460,
0x45f,
0x45e,
0x45d,
0x45d,
0x45c,
0x45b,
0x45a,
0x459,
0x459,
0x458,
0x457,
0x456,
0x455,
0x454,
0x454,
0x453,
0x452,
0x451,
0x450,
0x450,
0x44f,
0x44e,
0x44d,
0x44c,
0x44c,
0x44b,
0x44a,
0x449,
0x448,
0x448,
0x447,
0x446,
0x445,
0x444,
0x444,
0x443,
0x442,
0x441,
0x440,
0x440,
0x43f,
0x43e,
0x43d,
0x43c,
0x43c,
0x43b,
0x43a,
0x439,
0x438,
0x438,
0x437,
0x436,
0x435,
0x434,
0x434,
0x433,
0x432,
0x431,
0x430,
0x430,
0x42f,
0x42e,
0x42d,
0x42c,
0x42c,
0x42b,
0x42a,
0x429,
0x428,
0x428,
0x427,
0x426,
0x425,
0x425,
0x424,
0x423,
0x422,
0x421,
0x421,
0x420,
0x41f,
0x41e,
0x41d,
0x41d,
0x41c,
0x41b,
0x41a,
0x41a,
0x419,
0x418,
0x417,
0x416,
0x416,
0x415,
0x414,
0x413,
0x412,
0x412,
0x411,
0x410,
0x40f,
0x40f,
0x40e,
0x40d,
0x40c,
0x40b,
0x40b,
0x40a,
0x409,
0x408,
0x408,
0x407,
0x406,
0x405,
0x404,
0x404,
0x403,
0x402,
0x401,
0x401,
0x400,
0x3ff,
0x3fe,
0x3fe,
0x3fd,
0x3fc,
0x3fb,
0x3fa,
0x3fa,
0x3f9,
0x3f8,
0x3f7,
0x3f7,
0x3f6,
0x3f5,
0x3f4,
0x3f4,
0x3f3,
0x3f2,
0x3f1,
0x3f0,
0x3f0,
0x3ef,
0x3ee,
0x3ed,
0x3ed,
0x3ec,
0x3eb,
0x3ea,
0x3ea,
0x3e9,
0x3e8,
0x3e7,
0x3e7,
0x3e6,
0x3e5,
0x3e4,
0x3e3,
0x3e3,
0x3e2,
0x3e1,
0x3e0,
0x3e0,
0x3df,
0x3de,
0x3dd,
0x3dd,
0x3dc,
0x3db,
0x3da,
0x3da,
0x3d9,
0x3d8,
0x3d7,
0x3d7,
0x3d6,
0x3d5,
0x3d4,
0x3d4,
0x3d3,
0x3d2,
0x3d1,
0x3d1,
0x3d0,
0x3cf,
0x3ce,
0x3ce,
0x3cd,
0x3cc,
0x3cb,
0x3cb,
0x3ca,
0x3c9,
0x3c8,
0x3c8,
0x3c7,
0x3c6,
0x3c5,
0x3c5,
0x3c4,
0x3c3,
0x3c2,
0x3c2,
0x3c1,
0x3c0,
0x3bf,
0x3bf,
0x3be,
0x3bd,
0x3bc,
0x3bc,
0x3bb,
0x3ba,
0x3b9,
0x3b9,
0x3b8,
0x3b7,
0x3b6,
0x3b6,
0x3b5,
0x3b4,
0x3b3,
0x3b3,
0x3b2,
0x3b1,
0x3b1,
0x3b0,
0x3af,
0x3ae,
0x3ae,
0x3ad,
0x3ac,
0x3ab,
0x3ab,
0x3aa,
0x3a9,
0x3a8,
0x3a8,
0x3a7,
0x3a6,
0x3a5,
0x3a5,
0x3a4,
0x3a3,
0x3a3,
0x3a2,
0x3a1,
0x3a0,
0x3a0,
0x39f,
0x39e,
0x39d,
0x39d,
0x39c,
0x39b,
0x39b,
0x39a,
0x399,
0x398,
0x398,
0x397,
0x396,
0x395,
0x395,
0x394,
0x393,
0x392,
0x392,
0x391,
0x390,
0x390,
0x38f,
0x38e,
0x38d,
0x38d,
0x38c,
0x38b,
0x38b,
0x38a,
0x389,
0x388,
0x388,
0x387,
0x386,
0x385,
0x385,
0x384,
0x383,
0x383,
0x382,
0x381,
0x380,
0x380,
0x37f,
0x37e,
0x37e,
0x37d,
0x37c,
0x37b,
0x37b,
0x37a,
0x379,
0x379,
0x378,
0x377,
0x376,
0x376,
0x375,
0x374,
0x374,
0x373,
0x372,
0x371,
0x371,
0x370,
0x36f,
0x36f,
0x36e,
0x36d,
0x36c,
0x36c,
0x36b,
0x36a,
0x36a,
0x369,
0x368,
0x367,
0x367,
0x366,
0x365,
0x365,
0x364,
0x363,
0x362,
0x362,
0x361,
0x360,
0x360,
0x35f,
0x35e,
0x35e,
0x35d,
0x35c,
0x35b,
0x35b,
0x35a,
0x359,
0x359,
0x358,
0x357,
0x357,
0x356,
0x355,
0x354,
0x354,
0x353,
0x352,
0x352,
0x351,
0x350,
0x34f,
0x34f,
0x34e,
0x34d,
0x34d,
0x34c,
0x34b,
0x34b,
0x34a,
0x349,
0x349,
0x348,
0x347,
0x346,
0x346,
0x345,
0x344,
0x344,
0x343,
0x342,
0x342,
0x341,
0x340,
0x33f,
0x33f,
0x33e,
0x33d,
0x33d,
0x33c,
0x33b,
0x33b,
0x33a,
0x339,
0x339,
0x338,
0x337,
0x336,
0x336,
0x335,
0x334,
0x334,
0x333,
0x332,
0x332,
0x331,
0x330,
0x330,
0x32f,
0x32e,
0x32e,
0x32d,
0x32c,
0x32b,
0x32b,
0x32a,
0x329,
0x329,
0x328,
0x327,
0x327,
0x326,
0x325,
0x325,
0x324,
0x323,
0x323,
0x322,
0x321,
0x321,
0x320,
0x31f,
0x31f,
0x31e,
0x31d,
0x31c,
0x31c,
0x31b,
0x31a,
0x31a,
0x319,
0x318,
0x318,
0x317,
0x316,
0x316,
0x315,
0x314,
0x314,
0x313,
0x312,
0x312,
0x311,
0x310,
0x310,
0x30f,
0x30e,
0x30e,
0x30d,
0x30c,
0x30c,
0x30b,
0x30a,
0x30a,
0x309,
0x308,
0x308,
0x307,
0x306,
0x306,
0x305,
0x304,
0x303,
0x303,
0x302,
0x301,
0x301,
0x300,
0x2ff,
0x2ff,
0x2fe,
0x2fd,
0x2fd,
0x2fc,
0x2fb,
0x2fb,
0x2fa,
0x2f9,
0x2f9,
0x2f8,
0x2f7,
0x2f7,
0x2f6,
0x2f5,
0x2f5,
0x2f4,
0x2f3,
0x2f3,
0x2f2,
0x2f1,
0x2f1,
0x2f0,
0x2ef,
0x2ef,
0x2ee,
0x2ee,
0x2ed,
0x2ec,
0x2ec,
0x2eb,
0x2ea,
0x2ea,
0x2e9,
0x2e8,
0x2e8,
0x2e7,
0x2e6,
0x2e6,
0x2e5,
0x2e4,
0x2e4,
0x2e3,
0x2e2,
0x2e2,
0x2e1,
0x2e0,
0x2e0,
0x2df,
0x2de,
0x2de,
0x2dd,
0x2dc,
0x2dc,
0x2db,
0x2da,
0x2da,
0x2d9,
0x2d8,
0x2d8,
0x2d7,
0x2d6,
0x2d6,
0x2d5,
0x2d5,
0x2d4,
0x2d3,
0x2d3,
0x2d2,
0x2d1,
0x2d1,
0x2d0,
0x2cf,
0x2cf,
0x2ce,
0x2cd,
0x2cd,
0x2cc,
0x2cb,
0x2cb,
0x2ca,
0x2c9,
0x2c9,
0x2c8,
0x2c8,
0x2c7,
0x2c6,
0x2c6,
0x2c5,
0x2c4,
0x2c4,
0x2c3,
0x2c2,
0x2c2,
0x2c1,
0x2c0,
0x2c0,
0x2bf,
0x2be,
0x2be,
0x2bd,
0x2bd,
0x2bc,
0x2bb,
0x2bb,
0x2ba,
0x2b9,
0x2b9,
0x2b8,
0x2b7,
0x2b7,
0x2b6,
0x2b5,
0x2b5,
0x2b4,
0x2b4,
0x2b3,
0x2b2,
0x2b2,
0x2b1,
0x2b0,
0x2b0,
0x2af,
0x2ae,
0x2ae,
0x2ad,
0x2ad,
0x2ac,
0x2ab,
0x2ab,
0x2aa,
0x2a9,
0x2a9,
0x2a8,
0x2a7,
0x2a7,
0x2a6,
0x2a6,
0x2a5,
0x2a4,
0x2a4,
0x2a3,
0x2a2,
0x2a2,
0x2a1,
0x2a0,
0x2a0,
0x29f,
0x29f,
0x29e,
0x29d,
0x29d,
0x29c,
0x29b,
0x29b,
0x29a,
0x299,
0x299,
0x298,
0x298,
0x297,
0x296,
0x296,
0x295,
0x294,
0x294,
0x293,
0x293,
0x292,
0x291,
0x291,
0x290,
0x28f,
0x28f,
0x28e,
0x28e,
0x28d,
0x28c,
0x28c,
0x28b,
0x28a,
0x28a,
0x289,
0x288,
0x288,
0x287,
0x287,
0x286,
0x285,
0x285,
0x284,
0x283,
0x283,
0x282,
0x282,
0x281,
0x280,
0x280,
0x27f,
0x27f,
0x27e,
0x27d,
0x27d,
0x27c,
0x27b,
0x27b,
0x27a,
0x27a,
0x279,
0x278,
0x278,
0x277,
0x276,
0x276,
0x275,
0x275,
0x274,
0x273,
0x273,
0x272,
0x272,
0x271,
0x270,
0x270,
0x26f,
0x26e,
0x26e,
0x26d,
0x26d,
0x26c,
0x26b,
0x26b,
0x26a,
0x269,
0x269,
0x268,
0x268,
0x267,
0x266,
0x266,
0x265,
0x265,
0x264,
0x263,
0x263,
0x262,
0x262,
0x261,
0x260,
0x260,
0x25f,
0x25e,
0x25e,
0x25d,
0x25d,
0x25c,
0x25b,
0x25b,
0x25a,
0x25a,
0x259,
0x258,
0x258,
0x257,
0x257,
0x256,
0x255,
0x255,
0x254,
0x254,
0x253,
0x252,
0x252,
0x251,
0x250,
0x250,
0x24f,
0x24f,
0x24e,
0x24d,
0x24d,
0x24c,
0x24c,
0x24b,
0x24a,
0x24a,
0x249,
0x249,
0x248,
0x247,
0x247,
0x246,
0x246,
0x245,
0x244,
0x244,
0x243,
0x243,
0x242,
0x241,
0x241,
0x240,
0x240,
0x23f,
0x23e,
0x23e,
0x23d,
0x23d,
0x23c,
0x23b,
0x23b,
0x23a,
0x23a,
0x239,
0x238,
0x238,
0x237,
0x237,
0x236,
0x235,
0x235,
0x234,
0x234,
0x233,
0x232,
0x232,
0x231,
0x231,
0x230,
0x22f,
0x22f,
0x22e,
0x22e,
0x22d,
0x22c,
0x22c,
0x22b,
0x22b,
0x22a,
0x22a,
0x229,
0x228,
0x228,
0x227,
0x227,
0x226,
0x225,
0x225,
0x224,
0x224,
0x223,
0x222,
0x222,
0x221,
0x221,
0x220,
0x21f,
0x21f,
0x21e,
0x21e,
0x21d,
0x21d,
0x21c,
0x21b,
0x21b,
0x21a,
0x21a,
0x219,
0x218,
0x218,
0x217,
0x217,
0x216,
0x215,
0x215,
0x214,
0x214,
0x213,
0x213,
0x212,
0x211,
0x211,
0x210,
0x210,
0x20f,
0x20e,
0x20e,
0x20d,
0x20d,
0x20c,
0x20c,
0x20b,
0x20a,
0x20a,
0x209,
0x209,
0x208,
0x207,
0x207,
0x206,
0x206,
0x205,
0x205,
0x204,
0x203,
0x203,
0x202,
0x202,
0x201,
0x200,
0x200,
0x1ff,
0x1ff,
0x1fe,
0x1fe,
0x1fd,
0x1fc,
0x1fc,
0x1fb,
0x1fb,
0x1fa,
0x1fa,
0x1f9,
0x1f8,
0x1f8,
0x1f7,
0x1f7,
0x1f6,
0x1f5,
0x1f5,
0x1f4,
0x1f4,
0x1f3,
0x1f3,
0x1f2,
0x1f1,
0x1f1,
0x1f0,
0x1f0,
0x1ef,
0x1ef,
0x1ee,
0x1ed,
0x1ed,
0x1ec,
0x1ec,
0x1eb,
0x1eb,
0x1ea,
0x1e9,
0x1e9,
0x1e8,
0x1e8,
0x1e7,
0x1e7,
0x1e6,
0x1e5,
0x1e5,
0x1e4,
0x1e4,
0x1e3,
0x1e3,
0x1e2,
0x1e1,
0x1e1,
0x1e0,
0x1e0,
0x1df,
0x1df,
0x1de,
0x1dd,
0x1dd,
0x1dc,
0x1dc,
0x1db,
0x1db,
0x1da,
0x1da,
0x1d9,
0x1d8,
0x1d8,
0x1d7,
0x1d7,
0x1d6,
0x1d6,
0x1d5,
0x1d4,
0x1d4,
0x1d3,
0x1d3,
0x1d2,
0x1d2,
0x1d1,
0x1d0,
0x1d0,
0x1cf,
0x1cf,
0x1ce,
0x1ce,
0x1cd,
0x1cd,
0x1cc,
0x1cb,
0x1cb,
0x1ca,
0x1ca,
0x1c9,
0x1c9,
0x1c8,
0x1c7,
0x1c7,
0x1c6,
0x1c6,
0x1c5,
0x1c5,
0x1c4,
0x1c4,
0x1c3,
0x1c2,
0x1c2,
0x1c1,
0x1c1,
0x1c0,
0x1c0,
0x1bf,
0x1be,
0x1be,
0x1bd,
0x1bd,
0x1bc,
0x1bc,
0x1bb,
0x1bb,
0x1ba,
0x1b9,
0x1b9,
0x1b8,
0x1b8,
0x1b7,
0x1b7,
0x1b6,
0x1b6,
0x1b5,
0x1b4,
0x1b4,
0x1b3,
0x1b3,
0x1b2,
0x1b2,
0x1b1,
0x1b1,
0x1b0,
0x1af,
0x1af,
0x1ae,
0x1ae,
0x1ad,
0x1ad,
0x1ac,
0x1ac,
0x1ab,
0x1ab,
0x1aa,
0x1a9,
0x1a9,
0x1a8,
0x1a8,
0x1a7,
0x1a7,
0x1a6,
0x1a6,
0x1a5,
0x1a4,
0x1a4,
0x1a3,
0x1a3,
0x1a2,
0x1a2,
0x1a1,
0x1a1,
0x1a0,
0x1a0,
0x19f,
0x19e,
0x19e,
0x19d,
0x19d,
0x19c,
0x19c,
0x19b,
0x19b,
0x19a,
0x199,
0x199,
0x198,
0x198,
0x197,
0x197,
0x196,
0x196,
0x195,
0x195,
0x194,
0x193,
0x193,
0x192,
0x192,
0x191,
0x191,
0x190,
0x190,
0x18f,
0x18f,
0x18e,
0x18d,
0x18d,
0x18c,
0x18c,
0x18b,
0x18b,
0x18a,
0x18a,
0x189,
0x189,
0x188,
0x188,
0x187,
0x186,
0x186,
0x185,
0x185,
0x184,
0x184,
0x183,
0x183,
0x182,
0x182,
0x181,
0x180,
0x180,
0x17f,
0x17f,
0x17e,
0x17e,
0x17d,
0x17d,
0x17c,
0x17c,
0x17b,
0x17b,
0x17a,
0x17a,
0x179,
0x178,
0x178,
0x177,
0x177,
0x176,
0x176,
0x175,
0x175,
0x174,
0x174,
0x173,
0x173,
0x172,
0x171,
0x171,
0x170,
0x170,
0x16f,
0x16f,
0x16e,
0x16e,
0x16d,
0x16d,
0x16c,
0x16c,
0x16b,
0x16b,
0x16a,
0x169,
0x169,
0x168,
0x168,
0x167,
0x167,
0x166,
0x166,
0x165,
0x165,
0x164,
0x164,
0x163,
0x163,
0x162,
0x161,
0x161,
0x160,
0x160,
0x15f,
0x15f,
0x15e,
0x15e,
0x15d,
0x15d,
0x15c,
0x15c,
0x15b,
0x15b,
0x15a,
0x15a,
0x159,
0x159,
0x158,
0x157,
0x157,
0x156,
0x156,
0x155,
0x155,
0x154,
0x154,
0x153,
0x153,
0x152,
0x152,
0x151,
0x151,
0x150,
0x150,
0x14f,
0x14f,
0x14e,
0x14d,
0x14d,
0x14c,
0x14c,
0x14b,
0x14b,
0x14a,
0x14a,
0x149,
0x149,
0x148,
0x148,
0x147,
0x147,
0x146,
0x146,
0x145,
0x145,
0x144,
0x144,
0x143,
0x143,
0x142,
0x141,
0x141,
0x140,
0x140,
0x13f,
0x13f,
0x13e,
0x13e,
0x13d,
0x13d,
0x13c,
0x13c,
0x13b,
0x13b,
0x13a,
0x13a,
0x139,
0x139,
0x138,
0x138,
0x137,
0x137,
0x136,
0x136,
0x135,
0x134,
0x134,
0x133,
0x133,
0x132,
0x132,
0x131,
0x131,
0x130,
0x130,
0x12f,
0x12f,
0x12e,
0x12e,
0x12d,
0x12d,
0x12c,
0x12c,
0x12b,
0x12b,
0x12a,
0x12a,
0x129,
0x129,
0x128,
0x128,
0x127,
0x127,
0x126,
0x126,
0x125,
0x125,
0x124,
0x124,
0x123,
0x123,
0x122,
0x121,
0x121,
0x120,
0x120,
0x11f,
0x11f,
0x11e,
0x11e,
0x11d,
0x11d,
0x11c,
0x11c,
0x11b,
0x11b,
0x11a,
0x11a,
0x119,
0x119,
0x118,
0x118,
0x117,
0x117,
0x116,
0x116,
0x115,
0x115,
0x114,
0x114,
0x113,
0x113,
0x112,
0x112,
0x111,
0x111,
0x110,
0x110,
0x10f,
0x10f,
0x10e,
0x10e,
0x10d,
0x10d,
0x10c,
0x10c,
0x10b,
0x10b,
0x10a,
0x10a,
0x109,
0x109,
0x108,
0x108,
0x107,
0x107,
0x106,
0x106,
0x105,
0x105,
0x104,
0x104,
0x103,
0x103,
0x102,
0x102,
0x101,
0x101,
0x100,
0x100,
0xff,
0xff,
0xfe,
0xfe,
0xfd,
0xfd,
0xfc,
0xfc,
0xfb,
0xfb,
0xfa,
0xfa,
0xf9,
0xf9,
0xf8,
0xf8,
0xf7,
0xf7,
0xf6,
0xf6,
0xf5,
0xf5,
0xf4,
0xf4,
0xf3,
0xf3,
0xf2,
0xf2,
0xf1,
0xf1,
0xf0,
0xf0,
0xef,
0xef,
0xee,
0xee,
0xed,
0xed,
0xec,
0xec,
0xeb,
0xeb,
0xea,
0xea,
0xe9,
0xe9,
0xe8,
0xe8,
0xe7,
0xe7,
0xe6,
0xe6,
0xe5,
0xe5,
0xe4,
0xe4,
0xe3,
0xe3,
0xe2,
0xe2,
0xe1,
0xe1,
0xe0,
0xe0,
0xdf,
0xdf,
0xde,
0xde,
0xdd,
0xdd,
0xdc,
0xdc,
0xdb,
0xdb,
0xda,
0xda,
0xd9,
0xd9,
0xd8,
0xd8,
0xd7,
0xd7,
0xd6,
0xd6,
0xd5,
0xd5,
0xd4,
0xd4,
0xd3,
0xd3,
0xd2,
0xd2,
0xd2,
0xd1,
0xd1,
0xd0,
0xd0,
0xcf,
0xcf,
0xce,
0xce,
0xcd,
0xcd,
0xcc,
0xcc,
0xcb,
0xcb,
0xca,
0xca,
0xc9,
0xc9,
0xc8,
0xc8,
0xc7,
0xc7,
0xc6,
0xc6,
0xc5,
0xc5,
0xc4,
0xc4,
0xc3,
0xc3,
0xc2,
0xc2,
0xc1,
0xc1,
0xc0,
0xc0,
0xc0,
0xbf,
0xbf,
0xbe,
0xbe,
0xbd,
0xbd,
0xbc,
0xbc,
0xbb,
0xbb,
0xba,
0xba,
0xb9,
0xb9,
0xb8,
0xb8,
0xb7,
0xb7,
0xb6,
0xb6,
0xb5,
0xb5,
0xb4,
0xb4,
0xb3,
0xb3,
0xb3,
0xb2,
0xb2,
0xb1,
0xb1,
0xb0,
0xb0,
0xaf,
0xaf,
0xae,
0xae,
0xad,
0xad,
0xac,
0xac,
0xab,
0xab,
0xaa,
0xaa,
0xa9,
0xa9,
0xa8,
0xa8,
0xa8,
0xa7,
0xa7,
0xa6,
0xa6,
0xa5,
0xa5,
0xa4,
0xa4,
0xa3,
0xa3,
0xa2,
0xa2,
0xa1,
0xa1,
0xa0,
0xa0,
0x9f,
0x9f,
0x9e,
0x9e,
0x9e,
0x9d,
0x9d,
0x9c,
0x9c,
0x9b,
0x9b,
0x9a,
0x9a,
0x99,
0x99,
0x98,
0x98,
0x97,
0x97,
0x96,
0x96,
0x95,
0x95,
0x95,
0x94,
0x94,
0x93,
0x93,
0x92,
0x92,
0x91,
0x91,
0x90,
0x90,
0x8f,
0x8f,
0x8e,
0x8e,
0x8d,
0x8d,
0x8d,
0x8c,
0x8c,
0x8b,
0x8b,
0x8a,
0x8a,
0x89,
0x89,
0x88,
0x88,
0x87,
0x87,
0x86,
0x86,
0x85,
0x85,
0x85,
0x84,
0x84,
0x83,
0x83,
0x82,
0x82,
0x81,
0x81,
0x80,
0x80,
0x7f,
0x7f,
0x7e,
0x7e,
0x7e,
0x7d,
0x7d,
0x7c,
0x7c,
0x7b,
0x7b,
0x7a,
0x7a,
0x79,
0x79,
0x78,
0x78,
0x77,
0x77,
0x77,
0x76,
0x76,
0x75,
0x75,
0x74,
0x74,
0x73,
0x73,
0x72,
0x72,
0x71,
0x71,
0x71,
0x70,
0x70,
0x6f,
0x6f,
0x6e,
0x6e,
0x6d,
0x6d,
0x6c,
0x6c,
0x6b,
0x6b,
0x6b,
0x6a,
0x6a,
0x69,
0x69,
0x68,
0x68,
0x67,
0x67,
0x66,
0x66,
0x65,
0x65,
0x65,
0x64,
0x64,
0x63,
0x63,
0x62,
0x62,
0x61,
0x61,
0x60,
0x60,
0x5f,
0x5f,
0x5f,
0x5e,
0x5e,
0x5d,
0x5d,
0x5c,
0x5c,
0x5b,
0x5b,
0x5a,
0x5a,
0x5a,
0x59,
0x59,
0x58,
0x58,
0x57,
0x57,
0x56,
0x56,
0x55,
0x55,
0x55,
0x54,
0x54,
0x53,
0x53,
0x52,
0x52,
0x51,
0x51,
0x50,
0x50,
0x50,
0x4f,
0x4f,
0x4e,
0x4e,
0x4d,
0x4d,
0x4c,
0x4c,
0x4b,
0x4b,
0x4b,
0x4a,
0x4a,
0x49,
0x49,
0x48,
0x48,
0x47,
0x47,
0x46,
0x46,
0x46,
0x45,
0x45,
0x44,
0x44,
0x43,
0x43,
0x42,
0x42,
0x41,
0x41,
0x41,
0x40,
0x40,
0x3f,
0x3f,
0x3e,
0x3e,
0x3d,
0x3d,
0x3d,
0x3c,
0x3c,
0x3b,
0x3b,
0x3a,
0x3a,
0x39,
0x39,
0x38,
0x38,
0x38,
0x37,
0x37,
0x36,
0x36,
0x35,
0x35,
0x34,
0x34,
0x34,
0x33,
0x33,
0x32,
0x32,
0x31,
0x31,
0x30,
0x30,
0x30,
0x2f,
0x2f,
0x2e,
0x2e,
0x2d,
0x2d,
0x2c,
0x2c,
0x2c,
0x2b,
0x2b,
0x2a,
0x2a,
0x29,
0x29,
0x28,
0x28,
0x28,
0x27,
0x27,
0x26,
0x26,
0x25,
0x25,
0x24,
0x24,
0x24,
0x23,
0x23,
0x22,
0x22,
0x21,
0x21,
0x20,
0x20,
0x20,
0x1f,
0x1f,
0x1e,
0x1e,
0x1d,
0x1d,
0x1c,
0x1c,
0x1c,
0x1b,
0x1b,
0x1a,
0x1a,
0x19,
0x19,
0x18,
0x18,
0x18,
0x17,
0x17,
0x16,
0x16,
0x15,
0x15,
0x15,
0x14,
0x14,
0x13,
0x13,
0x12,
0x12,
0x11,
0x11,
0x11,
0x10,
0x10,
0xf,
0xf,
0xe,
0xe,
0xe,
0xd,
0xd,
0xc,
0xc,
0xb,
0xb,
0xa,
0xa,
0xa,
0x9,
0x9,
0x8,
0x8,
0x7,
0x7,
0x7,
0x6,
0x6,
0x5,
0x5,
0x4,
0x4,
0x3,
0x3,
0x3,
0x2,
0x2,
0x1,
0x1,
0x0,
0x0
};

#endif