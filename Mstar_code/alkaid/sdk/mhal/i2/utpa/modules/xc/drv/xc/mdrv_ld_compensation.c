//<MStar Software>
//******************************************************************************
// MStar Software
// Copyright (c) 2010 - 2012 MStar Semiconductor, Inc. All rights reserved.
// All software, firmware and related documentation herein ("MStar Software") are
// intellectual property of MStar Semiconductor, Inc. ("MStar") and protected by
// law, including, but not limited to, copyright law and international treaties.
// Any use, modification, reproduction, retransmission, or republication of all
// or part of MStar Software is expressly prohibited, unless prior written
// permission has been granted by MStar.
//
// By accessing, browsing and/or using MStar Software, you acknowledge that you
// have read, understood, and agree, to be bound by below terms ("Terms") and to
// comply with all applicable laws and regulations:
//
// 1. MStar shall retain any and all right, ownership and interest to MStar
//    Software and any modification/derivatives thereof.
//    No right, ownership, or interest to MStar Software and any
//    modification/derivatives thereof is transferred to you under Terms.
//
// 2. You understand that MStar Software might include, incorporate or be
//    supplied together with third party`s software and the use of MStar
//    Software may require additional licenses from third parties.
//    Therefore, you hereby agree it is your sole responsibility to separately
//    obtain any and all third party right and license necessary for your use of
//    such third party`s software.
//
// 3. MStar Software and any modification/derivatives thereof shall be deemed as
//    MStar`s confidential information and you agree to keep MStar`s
//    confidential information in strictest confidence and not disclose to any
//    third party.
//
// 4. MStar Software is provided on an "AS IS" basis without warranties of any
//    kind. Any warranties are hereby expressly disclaimed by MStar, including
//    without limitation, any warranties of merchantability, non-infringement of
//    intellectual property rights, fitness for a particular purpose, error free
//    and in conformity with any international standard.  You agree to waive any
//    claim against MStar for any loss, damage, cost or expense that you may
//    incur related to your use of MStar Software.
//    In no event shall MStar be liable for any direct, indirect, incidental or
//    consequential damages, including without limitation, lost of profit or
//    revenues, lost or damage of data, and unauthorized system use.
//    You agree that this Section 4 shall still apply without being affected
//    even if MStar Software has been modified by MStar in accordance with your
//    request or instruction for your use, except otherwise agreed by both
//    parties in writing.
//
// 5. If requested, MStar may from time to time provide technical supports or
//    services in relation with MStar Software to you for your use of
//    MStar Software in conjunction with your or your customer`s product
//    ("Services").
//    You understand and agree that, except otherwise agreed by both parties in
//    writing, Services are provided on an "AS IS" basis and the warranty
//    disclaimer set forth in Section 4 above shall apply.
//
// 6. Nothing contained herein shall be construed as by implication, estoppels
//    or otherwise:
//    (a) conferring any license or right to use MStar name, trademark, service
//        mark, symbol or any other identification;
//    (b) obligating MStar or any of its affiliates to furnish any person,
//        including without limitation, you and your customers, any assistance
//        of any kind whatsoever, or any information; or
//    (c) conferring any license or right under any intellectual property right.
//
// 7. These terms shall be governed by and construed in accordance with the laws
//    of Taiwan, R.O.C., excluding its conflict of law rules.
//    Any and all dispute arising out hereof or related hereto shall be finally
//    settled by arbitration referred to the Chinese Arbitration Association,
//    Taipei in accordance with the ROC Arbitration Law and the Arbitration
//    Rules of the Association by three (3) arbitrators appointed in accordance
//    with the said Rules.
//    The place of arbitration shall be in Taipei, Taiwan and the language shall
//    be English.
//    The arbitration award shall be final and binding to both parties.
//
//******************************************************************************
//<MStar Software>
////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2008-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
/// file    Mdrv_ld_Compensation.c
/// @brief  local dimming Compensation table
/// @author MStar Semiconductor Inc.
///////////////////////////////////////////////////////////////////////////////////////////////////


#include "mdrv_ld_compensation.h"

#if  (LD_ENABLE==1)
MS_U8 Tbl_LD_Compensation_LG60inchCinema_TB32[]=
    {
    93, 0,
    186,    0,
    117,    1,
    117,    1,
    233,    2,
    233,    2,
    233,    2,
    233,    2,
    233,    2,
    233,    2,
    211,    5,
    211,    5,
    211,    5,
    211,    5,
    211,    5,
    183,    5,
    159,    5,
    134,    5,
    111,    5,
    89, 5,
    68, 5,
    48, 5,
    29, 5,
    11, 5,
    250,    4,
    233,    4,
    217,    4,
    202,    4,
    188,    4,
    173,    4,
    160,    4,
    147,    4,
    12, 9,
    244,    8,
    221,    8,
    198,    8,
    176,    8,
    155,    8,
    134,    8,
    114,    8,
    95, 8,
    76, 8,
    57, 8,
    39, 8,
    22, 8,
    5,    8,
    244,    7,
    228,    7,
    212,    7,
    198,    7,
    184,    7,
    170,    7,
    157,    7,
    144,    7,
    131,    7,
    118,    7,
    106,    7,
    93, 7,
    80, 7,
    67, 7,
    55, 7,
    43, 7,
    31, 7,
    20, 7,
    8,    7,
    254,    6,
    243,    6,
    233,    6,
    223,    6,
    213,    6,
    203,    6,
    194,    6,
    184,    6,
    175,    6,
    166,    6,
    157,    6,
    148,    6,
    140,    6,
    132,    6,
    123,    6,
    115,    6,
    107,    6,
    99, 6,
    90, 6,
    83, 6,
    75, 6,
    67, 6,
    60, 6,
    52, 6,
    90, 12,
    76, 12,
    62, 12,
    48, 12,
    35, 12,
    21, 12,
    8,    12,
    251,    11,
    238,    11,
    225,    11,
    213,    11,
    200,    11,
    188,    11,
    176,    11,
    164,    11,
    152,    11,
    140,    11,
    129,    11,
    117,    11,
    106,    11,
    95, 11,
    84, 11,
    73, 11,
    62, 11,
    52, 11,
    42, 11,
    32, 11,
    22, 11,
    12, 11,
    3,    11,
    249,    10,
    240,    10,
    230,    10,
    220,    10,
    211,    10,
    202,    10,
    193,    10,
    183,    10,
    174,    10,
    166,    10,
    157,    10,
    148,    10,
    140,    10,
    132,    10,
    123,    10,
    115,    10,
    107,    10,
    99, 10,
    91, 10,
    83, 10,
    75, 10,
    67, 10,
    59, 10,
    51, 10,
    44, 10,
    36, 10,
    29, 10,
    22, 10,
    14, 10,
    7,    10,
    0,    10,
    250,    9,
    243,    9,
    236,    9,
    229,    9,
    222,    9,
    215,    9,
    208,    9,
    202,    9,
    195,    9,
    188,    9,
    182,    9,
    176,    9,
    170,    9,
    163,    9,
    157,    9,
    151,    9,
    145,    9,
    140,    9,
    134,    9,
    128,    9,
    122,    9,
    116,    9,
    111,    9,
    105,    9,
    99, 9,
    94, 9,
    88, 9,
    83, 9,
    77, 9,
    72, 9,
    66, 9,
    61, 9,
    55, 9,
    50, 9,
    45, 9,
    39, 9,
    34, 9,
    29, 9,
    23, 9,
    18, 9,
    13, 9,
    8,    9,
    2,    9,
    253,    8,
    249,    8,
    244,    8,
    239,    8,
    234,    8,
    229,    8,
    225,    8,
    220,    8,
    215,    8,
    211,    8,
    206,    8,
    201,    8,
    197,    8,
    192,    8,
    187,    8,
    183,    8,
    178,    8,
    174,    8,
    170,    8,
    165,    8,
    161,    8,
    157,    8,
    153,    8,
    148,    8,
    144,    8,
    140,    8,
    136,    8,
    132,    8,
    128,    8,
    124,    8,
    120,    8,
    116,    8,
    112,    8,
    108,    8,
    104,    8,
    100, 8,
    96, 8,
    92, 8,
    88, 8,
    84, 8,
    80, 8,
    76, 8,
    72, 8,
    68, 8,
    64, 8,
    60, 8,
    56, 8,
    53, 8,
    49, 8,
    45, 8,
    42, 8,
    38, 8,
    35, 8,
    31, 8,
    28, 8,
    25, 8,
    21, 8,
    17, 8,
    14, 8,
    10, 8,
    7,    8,
    3,    8,
    0,    8,
    };


MS_U8 Tbl_LD_Compensation_LG37inch_LR10[] =
{
    176, 0,
    95, 1,
    190, 2,
    66, 2,
    0,5,
    124,    5,
    124,    5,
    49,    5,
    131,    4,
    131,    4,
    154,    8,
    61,    8,
    236,    7,
    163,    7,
    99,    7,
    40,    7,
    243,    6,
    195,    6,
    150,    6,
    109,    6,
    71,    6,
    36,    6,
    3,    6,
    228,    5,
    199,    5,
    172,    5,
    147,    5,
    122,    5,
    100,    5,
    78,    5,
    57,    5,
    38,    5,
    37,    10,
    1,    10,
    223,    9,
    190,    9,
    158,    9,
    127,    9,
    98,    9,
    70,    9,
    43,    9,
    17,    9,
    248,    8,
    223,    8,
    200,    8,
    177,    8,
    155,    8,
    134,    8,
    114,    8,
    93,    8,
    74,    8,
    55,    8,
    36,    8,
    19,    8,
    1,    8,
    240,    7,
    224,    7,
    208,    7,
    192,    7,
    177,    7,
    162,    7,
    147,    7,
    133,    7,
    119,    7,
    106,    7,
    93,    7,
    80,    7,
    67,    7,
    54,    7,
    42,    7,
    30,    7,
    19,    7,
    7,    7,
    252,    6,
    241,    6,
    231,    6,
    220,    6,
    210,    6,
    200,    6,
    190,    6,
    180,    6,
    170,    6,
    161,    6,
    152,    6,
    143,    6,
    134,    6,
    125,    6,
    116,    6,
    108,    6,
    199,    12,
    182,    12,
    166,    12,
    150,    12,
    135,    12,
    120,    12,
    105,    12,
    90,    12,
    75,    12,
    60,    12,
    46,    12,
    32,    12,
    18,    12,
    4,    12,
    247,    11,
    233,    11,
    220,    11,
    207,    11,
    195,    11,
    182,    11,
    170,    11,
    158,    11,
    146,    11,
    134,    11,
    122,    11,
    111,    11,
    99,    11,
    88,    11,
    77,    11,
    65,    11,
    55,    11,
    44,    11,
    33,    11,
    23,    11,
    12,    11,
    2,    11,
    248,    10,
    238,    10,
    228,    10,
    219,    10,
    209,    10,
    199,    10,
    190,    10,
    180,    10,
    171,    10,
    162,    10,
    153,    10,
    144,    10,
    135,    10,
    126,    10,
    118,    10,
    109,    10,
    101,    10,
    92,    10,
    84,    10,
    76,    10,
    68,    10,
    60,    10,
    52,    10,
    44,    10,
    36,    10,
    28,    10,
    21,    10,
    13,    10,
    6,    10,
    254,    9,
    247,    9,
    240,    9,
    232,    9,
    225,    9,
    218,    9,
    211,    9,
    204,    9,
    197,    9,
    190,    9,
    184,    9,
    177,    9,
    170,    9,
    164,    9,
    157,    9,
    151,    9,
    144,    9,
    138,    9,
    132,    9,
    125,    9,
    119,    9,
    113,    9,
    107,    9,
    101,    9,
    95,    9,
    89,    9,
    83,    9,
    77,    9,
    71,    9,
    66,    9,
    60,    9,
    54,    9,
    49,    9,
    43,    9,
    37,    9,
    32,    9,
    26,    9,
    21,    9,
    16,    9,
    10,    9,
    5,    9,
    0,    9,
    251,    8,
    246,    8,
    240,    8,
    235,    8,
    230,    8,
    225,    8,
    220,    8,
    215,    8,
    210,    8,
    206,    8,
    201,    8,
    196,    8,
    191,    8,
    186,    8,
    182,    8,
    177,    8,
    172,    8,
    168,    8,
    163,    8,
    159,    8,
    154,    8,
    150,    8,
    145,    8,
    141,    8,
    137,    8,
    132,    8,
    128,    8,
    124,    8,
    119,    8,
    115,    8,
    111,    8,
    107,    8,
    103,    8,
    98,    8,
    94,    8,
    90,    8,
    86,    8,
    82,    8,
    78,    8,
    74,    8,
    70,    8,
    66,    8,
    63,    8,
    59,    8,
    55,    8,
    51,    8,
    47,    8,
    43,    8,
    40,    8,
    36,    8,
    32,    8,
    29,    8,
    25,    8,
    21,    8,
    18,    8,
    14,    8,
    11,    8,
    7,    8,
    4,    8,
    0,    8,
};


MS_U8 Tbl_LD_Compensation_LG42inch_LR16[] =
{
    172 ,0  ,
    89  ,1  ,
    178 ,2  ,
    169 ,2  ,
    82  ,5  ,
    82  ,5  ,
    39  ,5  ,
    214 ,4  ,
    89  ,4  ,
    89  ,4  ,
    71  ,8  ,
    242 ,7  ,
    167 ,7  ,
    100 ,7  ,
    40  ,7  ,
    241 ,6  ,
    192 ,6  ,
    147 ,6  ,
    105 ,6  ,
    67  ,6  ,
    31  ,6  ,
    254 ,5  ,
    223 ,5  ,
    194 ,5  ,
    167 ,5  ,
    141 ,5  ,
    117 ,5  ,
    93  ,5  ,
    71  ,5  ,
    51  ,5  ,
    31  ,5  ,
    12  ,5  ,
    244 ,9  ,
    209 ,9  ,
    176 ,9  ,
    145 ,9  ,
    115 ,9  ,
    86  ,9  ,
    58  ,9  ,
    31  ,9  ,
    5     ,9  ,
    235 ,8  ,
    211 ,8  ,
    188 ,8  ,
    165 ,8  ,
    143 ,8  ,
    122 ,8  ,
    101 ,8  ,
    81  ,8  ,
    62  ,8  ,
    43  ,8  ,
    24  ,8  ,
    6     ,8  ,
    245 ,7  ,
    228 ,7  ,
    212 ,7  ,
    196 ,7  ,
    180 ,7  ,
    165 ,7  ,
    150 ,7  ,
    135 ,7  ,
    121 ,7  ,
    107 ,7  ,
    94  ,7  ,
    80  ,7  ,
    68  ,7  ,
    56  ,7  ,
    44  ,7  ,
    33  ,7  ,
    22  ,7  ,
    11  ,7  ,
    0     ,7  ,
    245 ,6  ,
    235 ,6  ,
    225 ,6  ,
    215 ,6  ,
    205 ,6  ,
    195 ,6  ,
    185 ,6  ,
    176 ,6  ,
    167 ,6  ,
    159 ,6  ,
    150 ,6  ,
    142 ,6  ,
    134 ,6  ,
    126 ,6  ,
    119 ,6  ,
    111 ,6  ,
    103 ,6  ,
    192 ,12 ,
    177 ,12 ,
    163 ,12 ,
    149 ,12 ,
    135 ,12 ,
    121 ,12 ,
    107 ,12 ,
    94  ,12 ,
    79  ,12 ,
    65  ,12 ,
    50  ,12 ,
    36  ,12 ,
    22  ,12 ,
    8     ,12 ,
    251 ,11 ,
    237 ,11 ,
    224 ,11 ,
    211 ,11 ,
    198 ,11 ,
    185 ,11 ,
    173 ,11 ,
    161 ,11 ,
    148 ,11 ,
    136 ,11 ,
    123 ,11 ,
    109 ,11 ,
    96  ,11 ,
    83  ,11 ,
    70  ,11 ,
    57  ,11 ,
    44  ,11 ,
    32  ,11 ,
    20  ,11 ,
    8     ,11 ,
    252 ,10 ,
    240 ,10 ,
    229 ,10 ,
    217 ,10 ,
    206 ,10 ,
    195 ,10 ,
    186 ,10 ,
    176 ,10 ,
    167 ,10 ,
    158 ,10 ,
    150 ,10 ,
    141 ,10 ,
    132 ,10 ,
    123 ,10 ,
    115 ,10 ,
    107 ,10 ,
    98  ,10 ,
    90  ,10 ,
    82  ,10 ,
    74  ,10 ,
    66  ,10 ,
    58  ,10 ,
    51  ,10 ,
    45  ,10 ,
    39  ,10 ,
    32  ,10 ,
    26  ,10 ,
    20  ,10 ,
    14  ,10 ,
    8     ,10 ,
    2     ,10 ,
    251 ,9  ,
    246 ,9  ,
    240 ,9  ,
    234 ,9  ,
    228 ,9  ,
    222 ,9  ,
    216 ,9  ,
    209 ,9  ,
    202 ,9  ,
    194 ,9  ,
    187 ,9  ,
    180 ,9  ,
    173 ,9  ,
    166 ,9  ,
    159 ,9  ,
    152 ,9  ,
    145 ,9  ,
    138 ,9  ,
    132 ,9  ,
    125 ,9  ,
    118 ,9  ,
    112 ,9  ,
    105 ,9  ,
    99  ,9  ,
    93  ,9  ,
    86  ,9  ,
    80  ,9  ,
    74  ,9  ,
    68  ,9  ,
    61  ,9  ,
    55  ,9  ,
    49  ,9  ,
    43  ,9  ,
    37  ,9  ,
    32  ,9  ,
    26  ,9  ,
    20  ,9  ,
    14  ,9  ,
    8     ,9  ,
    3     ,9  ,
    253 ,8  ,
    248 ,8  ,
    243 ,8  ,
    237 ,8  ,
    232 ,8  ,
    227 ,8  ,
    221 ,8  ,
    216 ,8  ,
    211 ,8  ,
    206 ,8  ,
    201 ,8  ,
    196 ,8  ,
    191 ,8  ,
    186 ,8  ,
    181 ,8  ,
    177 ,8  ,
    174 ,8  ,
    171 ,8  ,
    167 ,8  ,
    164 ,8  ,
    161 ,8  ,
    157 ,8  ,
    154 ,8  ,
    151 ,8  ,
    147 ,8  ,
    144 ,8  ,
    141 ,8  ,
    138 ,8  ,
    134 ,8  ,
    131 ,8  ,
    128 ,8  ,
    123 ,8  ,
    118 ,8  ,
    113 ,8  ,
    108 ,8  ,
    103 ,8  ,
    98  ,8  ,
    93  ,8  ,
    88  ,8  ,
    84  ,8  ,
    79  ,8  ,
    74  ,8  ,
    69  ,8  ,
    65  ,8  ,
    60  ,8  ,
    55  ,8  ,
    51  ,8  ,
    47  ,8  ,
    44  ,8  ,
    40  ,8  ,
    37  ,8  ,
    33  ,8  ,
    30  ,8  ,
    27  ,8  ,
    23  ,8  ,
    20  ,8  ,
    17  ,8  ,
    13  ,8  ,
    10  ,8  ,
    7     ,8  ,
    3     ,8  ,
    0     ,8

};

MS_U8 Tbl_LD_Compensation_LG55inch_LR12[] =
{
    147,    0,
    37, 1,
    74, 2,
    74, 2,
    149,    4,
    149,    4,
    149,    4,
    149,    4,
    149,    4,
    149,    4,
    42, 9,
    42, 9,
    42, 9,
    202,    8,
    94, 8,
    8,  8,
    166,    7,
    93, 7,
    45, 7,
    242,    6,
    189,    6,
    152,    6,
    107,    6,
    65, 6,
    26, 6,
    0,  6,
    222,    5,
    190,    5,
    168,    5,
    140,    5,
    114,    5,
    89, 5,
    131,    10,
    98, 10,
    55, 10,
    24, 10,
    241,    9,
    204,    9,
    169,    9,
    134,    9,
    111,    9,
    79, 9,
    48, 9,
    27, 9,
    255,    8,
    227,    8,
    202,    8,
    183,    8,
    158,    8,
    135,    8,
    118,    8,
    96, 8,
    74, 8,
    54, 8,
    34, 8,
    19, 8,
    0,  8,
    242,    7,
    223,    7,
    206,    7,
    189,    7,
    172,    7,
    173,    7,
    144,    7,
    129,    7,
    118,    7,
    103,    7,
    88, 7,
    74, 7,
    64, 7,
    50, 7,
    37, 7,
    27, 7,
    15, 7,
    249,    6,
    237,    6,
    226,    6,
    215,    6,
    206,    6,
    195,    6,
    184,    6,
    174,    6,
    163,    6,
    156,    6,
    145,    6,
    135,    6,
    129,    6,
    120,    6,
    110,    6,
    203,    12,
    186,    12,
    172,    12,
    155,    12,
    142,    12,
    125,    12,
    108,    12,
    90, 12,
    77, 12,
    64, 12,
    49, 12,
    37, 12,
    22, 12,
    6,  12,
    247,    11,
    233,    11,
    222,    11,
    208,    11,
    195,    11,
    184,    11,
    170,    11,
    157,    11,
    144,    11,
    134,    11,
    121,    11,
    109,    11,
    99, 11,
    86, 11,
    75, 11,
    63, 11,
    53, 11,
    43, 11,
    32, 11,
    19, 11,
    10, 11,
    255,    10,
    245,    10,
    236,    10,
    224,    10,
    215,    10,
    205,    10,
    202,    10,
    192,    10,
    183,    10,
    172,    10,
    164,    10,
    155,    10,
    146,    10,
    138,    10,
    129,    10,
    119,    10,
    111,    10,
    104,    10,
    95, 10,
    85, 10,
    77, 10,
    70, 10,
    62, 10,
    53, 10,
    45, 10,
    39, 10,
    31, 10,
    22, 10,
    16, 10,
    8,  10,
    0,  10,
    248,    9,
    242,    9,
    235,    9,
    227,    9,
    221,    9,
    214,    9,
    206,    9,
    199,    9,
    192,    9,
    186,    9,
    179,    9,
    172,    9,
    167,    9,
    160,    9,
    153,    9,
    147,    9,
    141,    9,
    135,    9,
    128,    9,
    122,    9,
    117,    9,
    110,    9,
    104,    9,
    99, 9,
    93, 9,
    87, 9,
    82, 9,
    75, 9,
    69, 9,
    63, 9,
    59, 9,
    53, 9,
    47, 9,
    42, 9,
    36, 9,
    31, 9,
    25, 9,
    20, 9,
    3,  9,
    255,    8,
    250,    8,
    244,    8,
    240,    8,
    235,    8,
    229,    8,
    224,    8,
    220,    8,
    215,    8,
    210,    8,
    205,    8,
    201,    8,
    196,    8,
    190,    8,
    186,    8,
    182,    8,
    177,    8,
    172,    8,
    169,    8,
    163,    8,
    159,    8,
    154,    8,
    151,    8,
    146,    8,
    141,    8,
    138,    8,
    133,    8,
    129,    8,
    125,    8,
    121,    8,
    117,    8,
    113,    8,
    109,    8,
    105,    8,
    101,    8,
    97, 8,
    93, 8,
    89, 8,
    85, 8,
    81, 8,
    77, 8,
    73, 8,
    70, 8,
    65, 8,
    62, 8,
    58, 8,
    54, 8,
    51, 8,
    47, 8,
    43, 8,
    39, 8,
    36, 8,
    32, 8,
    28, 8,
    25, 8,
    22, 8,
    18, 8,
    14, 8,
    11, 8,
    7,  8,
    3,  8,
    0,  8,

};



MS_U8 Tbl_LD_Compensation_CMO42inch_LR16[] =
{
    129,    0,
    1,    1,
    2,    2,
    2,    2,
    5,    4,
    5,    4,
    5,    4,
    5,    4,
    5,    4,
    5,    4,
    9,    8,
    9,    8,
    186,    7,
    116,    7,
    53,    7,
    253,    6,
    202,    6,
    157,    6,
    116,    6,
    79,    6,
    43,    6,
    11,    6,
    236,    5,
    207,    5,
    180,    5,
    154,    5,
    129,    5,
    106,    5,
    84,    5,
    63,    5,
    43,    5,
    24,    5,
    12,    10,
    234,    9,
    201,    9,
    169,    9,
    139,    9,
    109,    9,
    81,    9,
    54,    9,
    28,    9,
    2,    9,
    233,    8,
    209,    8,
    186,    8,
    164,    8,
    142,    8,
    121,    8,
    101,    8,
    81,    8,
    62,    8,
    43,    8,
    25,    8,
    8,    8,
    247,    7,
    230,    7,
    214,    7,
    198,    7,
    183,    7,
    168,    7,
    153,    7,
    139,    7,
    125,    7,
    111,    7,
    98,    7,
    85,    7,
    72,    7,
    60,    7,
    48,    7,
    36,    7,
    24,    7,
    13,    7,
    2,    7,
    247,    6,
    236,    6,
    225,    6,
    215,    6,
    205,    6,
    195,    6,
    185,    6,
    175,    6,
    166,    6,
    157,    6,
    147,    6,
    138,    6,
    130,    6,
    121,    6,
    112,    6,
    104,    6,
    192,    12,
    175,    12,
    159,    12,
    143,    12,
    128,    12,
    112,    12,
    97,    12,
    82,    12,
    68,    12,
    54,    12,
    39,    12,
    26,    12,
    12,    12,
    254,    11,
    241,    11,
    228,    11,
    215,    11,
    202,    11,
    189,    11,
    177,    11,
    165,    11,
    152,    11,
    140,    11,
    129,    11,
    117,    11,
    106,    11,
    94,    11,
    83,    11,
    72,    11,
    61,    11,
    51,    11,
    40,    11,
    29,    11,
    19,    11,
    9,    11,
    255,    10,
    244,    10,
    235,    10,
    225,    10,
    215,    10,
    205,    10,
    196,    10,
    186,    10,
    176,    10,
    167,    10,
    158,    10,
    149,    10,
    140,    10,
    131,    10,
    122,    10,
    114,    10,
    105,    10,
    97,    10,
    89,    10,
    80,    10,
    72,    10,
    64,    10,
    56,    10,
    48,    10,
    40,    10,
    33,    10,
    25,    10,
    17,    10,
    10,    10,
    2,    10,
    251,    9,
    244,    9,
    237,    9,
    229,    9,
    222,    9,
    215,    9,
    208,    9,
    201,    9,
    195,    9,
    188,    9,
    181,    9,
    174,    9,
    168,    9,
    161,    9,
    155,    9,
    148,    9,
    142,    9,
    136,    9,
    129,    9,
    123,    9,
    117,    9,
    111,    9,
    105,    9,
    99,    9,
    93,    9,
    87,    9,
    81,    9,
    75,    9,
    69,    9,
    63,    9,
    58,    9,
    52,    9,
    46,    9,
    41,    9,
    35,    9,
    30,    9,
    24,    9,
    19,    9,
    13,    9,
    8,    9,
    3,    9,
    254,    8,
    249,    8,
    243,    8,
    238,    8,
    233,    8,
    228,    8,
    223,    8,
    218,    8,
    213,    8,
    208,    8,
    204,    8,
    199,    8,
    194,    8,
    189,    8,
    184,    8,
    180,    8,
    175,    8,
    171,    8,
    166,    8,
    162,    8,
    157,    8,
    153,    8,
    148,    8,
    144,    8,
    139,    8,
    135,    8,
    131,    8,
    126,    8,
    122,    8,
    118,    8,
    113,    8,
    109,    8,
    105,    8,
    101,    8,
    97,    8,
    93,    8,
    89,    8,
    85,    8,
    81,    8,
    77,    8,
    73,    8,
    69,    8,
    65,    8,
    61,    8,
    57,    8,
    53,    8,
    50,    8,
    46,    8,
    42,    8,
    38,    8,
    35,    8,
    31,    8,
    27,    8,
    24,    8,
    20,    8,
    17,    8,
    14,    8,
    10,    8,
    7,    8,
    3,    8,
    0,    8,

};
#endif
