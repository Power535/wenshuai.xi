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
#define _RV32_2(a, b)    { (a) << 1, b }

#if defined(MIU1_LEN) && (MIU1_LEN != 0)
#define ENABLE_MIU1 1
#else
#define ENABLE_MIU1 0
#endif

    // MIU0 Software reset
    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x121e, 0x0c00),
    _RV32_2(0x121e, 0x0c00),
    _RV32_2(0x121e, 0x0c00),
    _RV32_2(0x121e, 0x0c01),
    //_RV32_2(0x121e, 0x0c00),

    // MIU0 Request mask
    _RV32_2(0x1246, 0xFFFE),
    _RV32_2(0x1266, 0xFFFF),
    _RV32_2(0x1286, 0xFFFF),
    _RV32_2(0x12A6, 0xFFFF),
    {CHIPCFG_CMD_BASE, 0x1f2C},
    _RV32_2(0x1506, 0xFFFF),
    _RV32_2(0x1526, 0xFFFF),
    _RV32_2(0x15E6, 0xFFFE),

    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d78, 0x0001),
    _RV32_2(0x0d24, 0x1000),
    _RV32_2(0x0d24, 0x0000),
#if (ENABLE_MEM1866MHz)
    _RV32_2(0x0d28, 0xc011),
    _RV32_2(0x0d2a, 0x0482),
    _RV32_2(0x0d36, 0x0400),
    _RV32_2(0x0d34, 0x2004),
    _RV32_2(0x0d30, 0xf45a),
    _RV32_2(0x0d32, 0x001d),
#elif (ENABLE_MEM1600MHz)
    _RV32_2(0x0d36, 0x0404),
    _RV32_2(0x0d34, 0x2004),
    _RV32_2(0x0d30, 0x8f5c),
    _RV32_2(0x0d32, 0x0023),
#else
    #error "Invalid DRAM Setting"
#endif
    {CHIPCFG_CMD_WAIT, 10},       // delay 1ms

    // DDR LDO power down off
    _RV32_2(0x0d8a, 0x0001),

    _RV32_2(0x0d22, 0x0004),
    _RV32_2(0x0d2c, 0x0114),

    {CHIPCFG_CMD_WAIT, 30},       // delay 1ms

    {CHIPCFG_STR_IFAC,0x0},
    {CHIPCFG_CMD_BASE, 0x1f20},
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x1202, 0x02a7),
    _RV32_2(0x1204, 0x0052),
#if (ENABLE_MEM1600MHz)
    _RV32_2(0x1206, 0x1560),
#else
    _RV32_2(0x1206, 0x1571),
#endif
#else
    _RV32_2(0x1202, 0x03a7),
    _RV32_2(0x1204, 0x000c),
    _RV32_2(0x1206, 0x1530),
#endif
    {CHIPCFG_STR_IFAC_END,0x0},

#if CONFIG_MSTAR_STR_ENABLE
    {CHIPCFG_STR_IFDC,0x0},
    {CHIPCFG_CMD_BASE, 0x1f20},
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x1202, 0xf2a7),
    _RV32_2(0x1204, 0x0052),
#if (ENABLE_MEM1600MHz)
    _RV32_2(0x1206, 0x1560),
#else
    _RV32_2(0x1206, 0x1571),
#endif
#else
    _RV32_2(0x1202, 0xf3a7),
    _RV32_2(0x1204, 0x000c),
    _RV32_2(0x1206, 0x1530),
#endif
    {CHIPCFG_STR_IFDC_END,0x0},
#endif //CONFIG_MSTAR_STR_ENABLE

    _RV32_2(0x1208, 0x20dd),
    _RV32_2(0x120a, 0x2d77),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x120c, 0xd7ea),
#else
    _RV32_2(0x120c, 0xd7e9),
#endif
    _RV32_2(0x120e, 0x40f5),
    _RV32_2(0x1210, 0x1f14),
    _RV32_2(0x1212, 0x4004),
    _RV32_2(0x1214, 0x8020),
    _RV32_2(0x1216, 0xc000),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x1228, 0x00a0),
#else
    _RV32_2(0x1228, 0x0040),
#endif
    _RV32_2(0x12d2, 0xa000),

    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d02, 0xaaaa),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x0d04, 0x0008),
#else
    _RV32_2(0x0d04, 0x0080),
#endif
    _RV32_2(0x0d0a, 0x1100),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x0d0e, 0x0097),
#else
    _RV32_2(0x0d0e, 0x0089),
#endif
    _RV32_2(0x0d2e, 0x4423),
    _RV32_2(0x0d38, 0x2277),
    _RV32_2(0x0d3a, 0x1010),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x0d3c, 0x9033),
    _RV32_2(0x0d3e, 0x2000),
#else
    _RV32_2(0x0d3c, 0x9455),
    _RV32_2(0x0d3e, 0x2044),
#endif
    _RV32_2(0x0d48, 0x5677),
    _RV32_2(0x0d4a, 0x1010),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x0d4c, 0x0133),
    _RV32_2(0x0d4e, 0x0033),
#else
    _RV32_2(0x0d4c, 0x0055),
    _RV32_2(0x0d4e, 0x0055),
#endif
    _RV32_2(0x0d50, 0x1111),
    _RV32_2(0x0d52, 0x3343),
    _RV32_2(0x0d6c, 0x0808),
    _RV32_2(0x0d6e, 0x0808),

    {CHIPCFG_STR_IFAC,0x0},
    _RV32_2(0x0d94, 0x0804),
    _RV32_2(0x0d96, 0x0705),
    _RV32_2(0x0da0, 0x2634),
    _RV32_2(0x0da2, 0x0a07),
    _RV32_2(0x0da4, 0x4444),
    _RV32_2(0x0da6, 0x7054),
    _RV32_2(0x0da8, 0x2021),
    _RV32_2(0x0daa, 0x1522),
    _RV32_2(0x0dac, 0x3462),
    _RV32_2(0x0dae, 0x6074),
    {CHIPCFG_STR_IFAC_END,0x0},

    _RV32_2(0x0db6, 0x0000),
#if (ENABLE_MIU_4X_MODE)
    _RV32_2(0x0db8, 0x3333),
    _RV32_2(0x0dba, 0x0333),
    _RV32_2(0x0dbc, 0x0333),
    _RV32_2(0x0dbe, 0x0333),
#else
    _RV32_2(0x0db8, 0x4444),
    _RV32_2(0x0dba, 0x0444),
    _RV32_2(0x0dbc, 0x0444),
    _RV32_2(0x0dbe, 0x0444),
#endif
    // TX DQ
    _RV32_2(0x0dd0, 0x4444),
    _RV32_2(0x0dd2, 0x4444),
    _RV32_2(0x0dd4, 0x5555),
    _RV32_2(0x0dd6, 0x5555),
    _RV32_2(0x0dd8, 0x0055),
    _RV32_2(0x0de0, 0x5555),
    _RV32_2(0x0de2, 0x5555),
    _RV32_2(0x0de4, 0x4444),
    _RV32_2(0x0de6, 0x5444),
    _RV32_2(0x0de8, 0x0055),
    _RV32_2(0x0dfc, 0x0f0f),
    _RV32_2(0x0dfe, 0x0f0f),

     // program DLL
    _RV32_2(0x0d62, 0x007f),
    _RV32_2(0x0d64, 0xf000),
    _RV32_2(0x0d60, 0x00cb),
    _RV32_2(0x0d60, 0x00cf),
    _RV32_2(0x0d60, 0x00cb),
    _RV32_2(0x0d60, 0x00c3),
    _RV32_2(0x0d60, 0x00cb),
    _RV32_2(0x0d60, 0x00c3),
    _RV32_2(0x0d60, 0x00cb),
    _RV32_2(0x0d60, 0x00c2),
    _RV32_2(0x0d60, 0x00c0),
    _RV32_2(0x0d60, 0x33c8),
    _RV32_2(0x0d70, 0x0000),
    _RV32_2(0x0d98, 0x0000),
    _RV32_2(0x0d9a, 0x0000),
    _RV32_2(0x0d90, 0xf0f1),
    _RV32_2(0x0d70, 0x0800),

    // program dig general setting
    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x122c, 0x8221),
    _RV32_2(0x12fc, 0x951a),
    _RV32_2(0x1252, 0xffff),
    _RV32_2(0x1272, 0xffff),
    _RV32_2(0x1292, 0xffff),
    _RV32_2(0x12b2, 0xffff),
    {CHIPCFG_CMD_BASE, 0x1f2C},
    _RV32_2(0x1512, 0xffff),
    _RV32_2(0x1532, 0xffff),

    // Default BW setting
    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x1240, 0x8015),
    _RV32_2(0x1260, 0x8015),
    _RV32_2(0x1280, 0x8015),
    _RV32_2(0x12a0, 0x8015),
    {CHIPCFG_CMD_BASE, 0x1f2C},
    _RV32_2(0x1500, 0x8015),
    _RV32_2(0x1520, 0x8015),

    // program ana general setting
    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d70, 0x0800),
    // driving setting
    _RV32_2(0x0d58, 0x0a0a),
    _RV32_2(0x0d5a, 0xaaaa),
    _RV32_2(0x0d5c, 0xaaaa),
    _RV32_2(0x0d5e, 0xaaaa),

    // trig. lvl setting
    {CHIPCFG_STR_IFAC,0x0},
    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d74, 0x0606),
    _RV32_2(0x0d76, 0x0606),
    _RV32_2(0x0d1a, 0x8111),
    _RV32_2(0x0d1c, 0x0020),
    _RV32_2(0x0d08, 0x003f),
    {CHIPCFG_STR_IFAC_END,0x0},

#if CONFIG_MSTAR_STR_ENABLE
    {CHIPCFG_STR_IFDC,0x0},
    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d74, 0x0606),
    _RV32_2(0x0d76, 0x0606),
    _RV32_2(0x0d1a, 0x8111),
    _RV32_2(0x0d1c, 0x0020),
    _RV32_2(0x0d08, 0x0000),
    {CHIPCFG_STR_IFDC_END,0x0},
#endif //CONFIG_MSTAR_STR_ENABLE

    // DQSM RST
    _RV32_2(0x0d1e, 0x0005),
    _RV32_2(0x0d1e, 0x000f),
    _RV32_2(0x0d1e, 0x0005),

    // Toggle reset & disable GPIO
    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x121e, 0x8c01),
    _RV32_2(0x121e, 0x8c00),

    // disable GPIO
    {CHIPCFG_STR_IFAC,0x0},
    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d00, 0x2010),
    _RV32_2(0x0d00, 0x0000),
    _RV32_2(0x0d18, 0x0000),
    _RV32_2(0x0d7c, 0x0000),
    // Release ATOP PD mode
    _RV32_2(0x0d54, 0xc000),

    // DQSM RST
    _RV32_2(0x0d1e, 0x0005),
    _RV32_2(0x0d1e, 0x000f),
    _RV32_2(0x0d1e, 0x0005),

    // select Mapping
    _RV32_2(0x0d00, 0x0000),

    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x1200, 0x0000),
    {CHIPCFG_STR_IFAC_END,0x0},

#if CONFIG_MSTAR_STR_ENABLE
    {CHIPCFG_STR_IFDC,0x0},
    // disable GPIO
    {CHIPCFG_CMD_BASE, 0x1f22},
    _RV32_2(0x0d00, 0x2018),
    _RV32_2(0x0d00, 0x0008),
    _RV32_2(0x0d18, 0x0000),
    _RV32_2(0x0d7c, 0x0000),
    // Release ATOP PD mode
    _RV32_2(0x0d54, 0xc070),
    // DQSM RST
    //_RV32_2(0x0d1e, 0x0005),
    //_RV32_2(0x0d1e, 0x000f),
    //_RV32_2(0x0d1e, 0x0005),

    // select Mapping
    _RV32_2(0x0d00, 0x0008),
    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x1200, 0x0000),
    {CHIPCFG_STR_IFDC_END,0x0},
#endif

    // MIU0 Init Cycle
    {CHIPCFG_CMD_WAIT, 1},       // delay 1ms
    _RV32_2(0x1200, 0x0008),
    _RV32_2(0x1200, 0x000c),
    {CHIPCFG_CMD_WAIT, 1},       // delay 1ms
    _RV32_2(0x1200, 0x000e),
    {CHIPCFG_CMD_WAIT, 1},       // delay 1ms
    _RV32_2(0x1200, 0x001f),
    {CHIPCFG_CMD_WAIT, 1},       // delay 1ms
    {CHIPCFG_CMD_WAIT, 10},      // delay 10ms


    {CHIPCFG_CMD_BASE, 0x1f20},
    _RV32_2(0x121e, 0x8c08),
    _RV32_2(0x12fe, 0xa0e1),

    // Mask all
    _RV32_2(0x1246, 0xfffe),
    _RV32_2(0x1266, 0xffff),
    _RV32_2(0x1286, 0xffff),
    _RV32_2(0x12a6, 0xffff),
    {CHIPCFG_CMD_BASE, 0x1f2C},
    _RV32_2(0x1506, 0x7fff),
    _RV32_2(0x1526, 0xffff),
    _RV32_2(0x15e6, 0xFFFC),
