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
// Copyright (c) 2008-2009 MStar Semiconductor, Inc.
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
#ifndef _HWREG_UTILITY_H_
#define _HWREG_UTILITY_H_
#ifdef _DRVPNL_C_
#define INTERFACE
#else
#define INTERFACE extern
#endif

//#include "MsCommon.h"

#define _PK_L_(bank, addr)   (((MS_U16)(bank) << 8) | (MS_U16)((addr)*2))
#define _PK_H_(bank, addr)   (((MS_U16)(bank) << 8) | (MS_U16)((addr)*2+1))

//=============================================================

#define REG_SC_BK00_7F_L      _PK_L_(0x00, 0x7F)

// BK00_02 : Reset control
#define REG_SC_BK00_02_L      _PK_L_(0x00, 0x02)
#define REG_SC_BK00_02_H      _PK_H_(0x00, 0x02)

//----------------------------------------------
//  BK0D: MRQ
//----------------------------------------------
#define REG_SC_BK0D_00_L      _PK_L_(0x0D, 0x00)
#define REG_SC_BK0D_00_H      _PK_H_(0x0D, 0x00)
#define REG_SC_BK0D_01_L      _PK_L_(0x0D, 0x01)
#define REG_SC_BK0D_01_H      _PK_H_(0x0D, 0x01)
#define REG_SC_BK0D_02_L      _PK_L_(0x0D, 0x02)
#define REG_SC_BK0D_02_H      _PK_H_(0x0D, 0x02)
#define REG_SC_BK0D_03_L      _PK_L_(0x0D, 0x03)
#define REG_SC_BK0D_03_H      _PK_H_(0x0D, 0x03)
#define REG_SC_BK0D_04_L      _PK_L_(0x0D, 0x04)
#define REG_SC_BK0D_04_H      _PK_H_(0x0D, 0x04)
#define REG_SC_BK0D_05_L      _PK_L_(0x0D, 0x05)
#define REG_SC_BK0D_05_H      _PK_H_(0x0D, 0x05)
#define REG_SC_BK0D_06_L      _PK_L_(0x0D, 0x06)
#define REG_SC_BK0D_06_H      _PK_H_(0x0D, 0x06)
#define REG_SC_BK0D_07_L      _PK_L_(0x0D, 0x07)
#define REG_SC_BK0D_07_H      _PK_H_(0x0D, 0x07)
#define REG_SC_BK0D_08_L      _PK_L_(0x0D, 0x08)
#define REG_SC_BK0D_08_H      _PK_H_(0x0D, 0x08)
#define REG_SC_BK0D_09_L      _PK_L_(0x0D, 0x09)
#define REG_SC_BK0D_09_H      _PK_H_(0x0D, 0x09)
#define REG_SC_BK0D_0A_L      _PK_L_(0x0D, 0x0A)
#define REG_SC_BK0D_0A_H      _PK_H_(0x0D, 0x0A)
#define REG_SC_BK0D_0B_L      _PK_L_(0x0D, 0x0B)
#define REG_SC_BK0D_0B_H      _PK_H_(0x0D, 0x0B)
#define REG_SC_BK0D_0C_L      _PK_L_(0x0D, 0x0C)
#define REG_SC_BK0D_0C_H      _PK_H_(0x0D, 0x0C)
#define REG_SC_BK0D_0D_L      _PK_L_(0x0D, 0x0D)
#define REG_SC_BK0D_0D_H      _PK_H_(0x0D, 0x0D)
#define REG_SC_BK0D_0E_L      _PK_L_(0x0D, 0x0E)
#define REG_SC_BK0D_0E_H      _PK_H_(0x0D, 0x0E)
#define REG_SC_BK0D_0F_L      _PK_L_(0x0D, 0x0F)
#define REG_SC_BK0D_0F_H      _PK_H_(0x0D, 0x0F)
#define REG_SC_BK0D_10_L      _PK_L_(0x0D, 0x10)
#define REG_SC_BK0D_10_H      _PK_H_(0x0D, 0x10)
#define REG_SC_BK0D_11_L      _PK_L_(0x0D, 0x11)
#define REG_SC_BK0D_11_H      _PK_H_(0x0D, 0x11)
#define REG_SC_BK0D_12_L      _PK_L_(0x0D, 0x12)
#define REG_SC_BK0D_12_H      _PK_H_(0x0D, 0x12)
#define REG_SC_BK0D_13_L      _PK_L_(0x0D, 0x13)
#define REG_SC_BK0D_13_H      _PK_H_(0x0D, 0x13)
#define REG_SC_BK0D_14_L      _PK_L_(0x0D, 0x14)
#define REG_SC_BK0D_14_H      _PK_H_(0x0D, 0x14)
#define REG_SC_BK0D_15_L      _PK_L_(0x0D, 0x15)
#define REG_SC_BK0D_15_H      _PK_H_(0x0D, 0x15)
#define REG_SC_BK0D_16_L      _PK_L_(0x0D, 0x16)
#define REG_SC_BK0D_16_H      _PK_H_(0x0D, 0x16)
#define REG_SC_BK0D_17_L      _PK_L_(0x0D, 0x17)
#define REG_SC_BK0D_17_H      _PK_H_(0x0D, 0x17)
#define REG_SC_BK0D_18_L      _PK_L_(0x0D, 0x18)
#define REG_SC_BK0D_18_H      _PK_H_(0x0D, 0x18)
#define REG_SC_BK0D_19_L      _PK_L_(0x0D, 0x19)
#define REG_SC_BK0D_19_H      _PK_H_(0x0D, 0x19)
#define REG_SC_BK0D_1A_L      _PK_L_(0x0D, 0x1A)
#define REG_SC_BK0D_1A_H      _PK_H_(0x0D, 0x1A)
#define REG_SC_BK0D_1B_L      _PK_L_(0x0D, 0x1B)
#define REG_SC_BK0D_1B_H      _PK_H_(0x0D, 0x1B)
#define REG_SC_BK0D_1C_L      _PK_L_(0x0D 0x1C)
#define REG_SC_BK0D_1C_H      _PK_H_(0x0D, 0x1C)
#define REG_SC_BK0D_1D_L      _PK_L_(0x0D, 0x1D)
#define REG_SC_BK0D_1D_H      _PK_H_(0x0D, 0x1D)
#define REG_SC_BK0D_1E_L      _PK_L_(0x0D, 0x1E)
#define REG_SC_BK0D_1E_H      _PK_H_(0x0D, 0x1E)
#define REG_SC_BK0D_1F_L      _PK_L_(0x0D, 0x1F)
#define REG_SC_BK0D_1F_H      _PK_H_(0x0D, 0x1F)
#define REG_SC_BK0D_20_L      _PK_L_(0x0D, 0x20)
#define REG_SC_BK0D_20_H      _PK_H_(0x0D, 0x20)
#define REG_SC_BK0D_21_L      _PK_L_(0x0D, 0x21)
#define REG_SC_BK0D_21_H      _PK_H_(0x0D, 0x21)
#define REG_SC_BK0D_22_L      _PK_L_(0x0D, 0x22)
#define REG_SC_BK0D_22_H      _PK_H_(0x0D, 0x22)
#define REG_SC_BK0D_23_L      _PK_L_(0x0D, 0x23)
#define REG_SC_BK0D_23_H      _PK_H_(0x0D, 0x23)
#define REG_SC_BK0D_24_L      _PK_L_(0x0D, 0x24)
#define REG_SC_BK0D_24_H      _PK_H_(0x0D, 0x24)
#define REG_SC_BK0D_25_L      _PK_L_(0x0D, 0x25)
#define REG_SC_BK0D_25_H      _PK_H_(0x0D, 0x25)
#define REG_SC_BK0D_26_L      _PK_L_(0x0D, 0x26)
#define REG_SC_BK0D_26_H      _PK_H_(0x0D, 0x26)
#define REG_SC_BK0D_27_L      _PK_L_(0x0D, 0x27)
#define REG_SC_BK0D_27_H      _PK_H_(0x0D, 0x27)
#define REG_SC_BK0D_28_L      _PK_L_(0x0D, 0x28)
#define REG_SC_BK0D_28_H      _PK_H_(0x0D, 0x28)
#define REG_SC_BK0D_29_L      _PK_L_(0x0D, 0x29)
#define REG_SC_BK0D_29_H      _PK_H_(0x0D, 0x29)
#define REG_SC_BK0D_2A_L      _PK_L_(0x0D, 0x2A)
#define REG_SC_BK0D_2A_H      _PK_H_(0x0D, 0x2A)
#define REG_SC_BK0D_2B_L      _PK_L_(0x0D, 0x2B)
#define REG_SC_BK0D_2B_H      _PK_H_(0x0D, 0x2B)
#define REG_SC_BK0D_2C_L      _PK_L_(0x0D, 0x2C)
#define REG_SC_BK0D_2C_H      _PK_H_(0x0D, 0x2C)
#define REG_SC_BK0D_2D_L      _PK_L_(0x0D, 0x2D)
#define REG_SC_BK0D_2D_H      _PK_H_(0x0D, 0x2D)
#define REG_SC_BK0D_2E_L      _PK_L_(0x0D, 0x2E)
#define REG_SC_BK0D_2E_H      _PK_H_(0x0D, 0x2E)
#define REG_SC_BK0D_2F_L      _PK_L_(0x0D, 0x2F)
#define REG_SC_BK0D_2F_H      _PK_H_(0x0D, 0x2F)
#define REG_SC_BK0D_30_L      _PK_L_(0x0D, 0x30)
#define REG_SC_BK0D_30_H      _PK_H_(0x0D, 0x30)
#define REG_SC_BK0D_31_L      _PK_L_(0x0D, 0x31)
#define REG_SC_BK0D_31_H      _PK_H_(0x0D, 0x31)
#define REG_SC_BK0D_32_L      _PK_L_(0x0D, 0x32)
#define REG_SC_BK0D_32_H      _PK_H_(0x0D, 0x32)
#define REG_SC_BK0D_33_L      _PK_L_(0x0D, 0x33)
#define REG_SC_BK0D_33_H      _PK_H_(0x0D, 0x33)
#define REG_SC_BK0D_34_L      _PK_L_(0x0D, 0x34)
#define REG_SC_BK0D_34_H      _PK_H_(0x0D, 0x34)
#define REG_SC_BK0D_35_L      _PK_L_(0x0D, 0x35)
#define REG_SC_BK0D_35_H      _PK_H_(0x0D, 0x35)
#define REG_SC_BK0D_36_L      _PK_L_(0x0D, 0x36)
#define REG_SC_BK0D_36_H      _PK_H_(0x0D, 0x36)
#define REG_SC_BK0D_37_L      _PK_L_(0x0D, 0x37)
#define REG_SC_BK0D_37_H      _PK_H_(0x0D, 0x37)
#define REG_SC_BK0D_38_L      _PK_L_(0x0D, 0x38)
#define REG_SC_BK0D_38_H      _PK_H_(0x0D, 0x38)
#define REG_SC_BK0D_39_L      _PK_L_(0x0D, 0x39)
#define REG_SC_BK0D_39_H      _PK_H_(0x0D, 0x39)
#define REG_SC_BK0D_3A_L      _PK_L_(0x0D, 0x3A)
#define REG_SC_BK0D_3A_H      _PK_H_(0x0D, 0x3A)
#define REG_SC_BK0D_3B_L      _PK_L_(0x0D, 0x3B)
#define REG_SC_BK0D_3B_H      _PK_H_(0x0D, 0x3B)
#define REG_SC_BK0D_3C_L      _PK_L_(0x0D, 0x3C)
#define REG_SC_BK0D_3C_H      _PK_H_(0x0D, 0x3C)
#define REG_SC_BK0D_3D_L      _PK_L_(0x0D, 0x3D)
#define REG_SC_BK0D_3D_H      _PK_H_(0x0D, 0x3D)
#define REG_SC_BK0D_3E_L      _PK_L_(0x0D, 0x3E)
#define REG_SC_BK0D_3E_H      _PK_H_(0x0D, 0x3E)
#define REG_SC_BK0D_3F_L      _PK_L_(0x0D, 0x3F)
#define REG_SC_BK0D_3F_H      _PK_H_(0x0D, 0x3F)
#define REG_SC_BK0D_40_L      _PK_L_(0x0D, 0x40)
#define REG_SC_BK0D_40_H      _PK_H_(0x0D, 0x40)
#define REG_SC_BK0D_41_L      _PK_L_(0x0D, 0x41)
#define REG_SC_BK0D_41_H      _PK_H_(0x0D, 0x41)
#define REG_SC_BK0D_42_L      _PK_L_(0x0D, 0x42)
#define REG_SC_BK0D_42_H      _PK_H_(0x0D, 0x42)
#define REG_SC_BK0D_43_L      _PK_L_(0x0D, 0x43)
#define REG_SC_BK0D_43_H      _PK_H_(0x0D, 0x43)
#define REG_SC_BK0D_44_L      _PK_L_(0x0D, 0x44)
#define REG_SC_BK0D_44_H      _PK_H_(0x0D, 0x44)
#define REG_SC_BK0D_45_L      _PK_L_(0x0D, 0x45)
#define REG_SC_BK0D_45_H      _PK_H_(0x0D, 0x45)
#define REG_SC_BK0D_46_L      _PK_L_(0x0D, 0x46)
#define REG_SC_BK0D_46_H      _PK_H_(0x0D, 0x46)
#define REG_SC_BK0D_47_L      _PK_L_(0x0D, 0x47)
#define REG_SC_BK0D_47_H      _PK_H_(0x0D, 0x47)
#define REG_SC_BK0D_48_L      _PK_L_(0x0D, 0x48)
#define REG_SC_BK0D_48_H      _PK_H_(0x0D, 0x48)
#define REG_SC_BK0D_49_L      _PK_L_(0x0D, 0x49)
#define REG_SC_BK0D_49_H      _PK_H_(0x0D, 0x49)
#define REG_SC_BK0D_4A_L      _PK_L_(0x0D, 0x4A)
#define REG_SC_BK0D_4A_H      _PK_H_(0x0D, 0x4A)
#define REG_SC_BK0D_4B_L      _PK_L_(0x0D, 0x4B)
#define REG_SC_BK0D_4B_H      _PK_H_(0x0D, 0x4B)
#define REG_SC_BK0D_4C_L      _PK_L_(0x0D, 0x4C)
#define REG_SC_BK0D_4C_H      _PK_H_(0x0D, 0x4C)
#define REG_SC_BK0D_4D_L      _PK_L_(0x0D, 0x4D)
#define REG_SC_BK0D_4D_H      _PK_H_(0x0D, 0x4D)
#define REG_SC_BK0D_4E_L      _PK_L_(0x0D, 0x4E)
#define REG_SC_BK0D_4E_H      _PK_H_(0x0D, 0x4E)
#define REG_SC_BK0D_4F_L      _PK_L_(0x0D, 0x4F)
#define REG_SC_BK0D_4F_H      _PK_H_(0x0D, 0x4F)
#define REG_SC_BK0D_50_L      _PK_L_(0x0D, 0x50)
#define REG_SC_BK0D_50_H      _PK_H_(0x0D, 0x50)
#define REG_SC_BK0D_51_L      _PK_L_(0x0D, 0x51)
#define REG_SC_BK0D_51_H      _PK_H_(0x0D, 0x51)
#define REG_SC_BK0D_52_L      _PK_L_(0x0D, 0x52)
#define REG_SC_BK0D_52_H      _PK_H_(0x0D, 0x52)
#define REG_SC_BK0D_53_L      _PK_L_(0x0D, 0x53)
#define REG_SC_BK0D_53_H      _PK_H_(0x0D, 0x53)
#define REG_SC_BK0D_54_L      _PK_L_(0x0D, 0x54)
#define REG_SC_BK0D_54_H      _PK_H_(0x0D, 0x54)
#define REG_SC_BK0D_55_L      _PK_L_(0x0D, 0x55)
#define REG_SC_BK0D_55_H      _PK_H_(0x0D, 0x55)
#define REG_SC_BK0D_56_L      _PK_L_(0x0D, 0x56)
#define REG_SC_BK0D_56_H      _PK_H_(0x0D, 0x56)
#define REG_SC_BK0D_57_L      _PK_L_(0x0D, 0x57)
#define REG_SC_BK0D_57_H      _PK_H_(0x0D, 0x57)
#define REG_SC_BK0D_58_L      _PK_L_(0x0D, 0x58)
#define REG_SC_BK0D_58_H      _PK_H_(0x0D, 0x58)
#define REG_SC_BK0D_59_L      _PK_L_(0x0D, 0x59)
#define REG_SC_BK0D_59_H      _PK_H_(0x0D, 0x59)
#define REG_SC_BK0D_5A_L      _PK_L_(0x0D, 0x5A)
#define REG_SC_BK0D_5A_H      _PK_H_(0x0D, 0x5A)
#define REG_SC_BK0D_5B_L      _PK_L_(0x0D, 0x5B)
#define REG_SC_BK0D_5B_H      _PK_H_(0x0D, 0x5B)
#define REG_SC_BK0D_5C_L      _PK_L_(0x0D, 0x5C)
#define REG_SC_BK0D_5C_H      _PK_H_(0x0D, 0x5C)
#define REG_SC_BK0D_5D_L      _PK_L_(0x0D, 0x5D)
#define REG_SC_BK0D_5D_H      _PK_H_(0x0D, 0x5D)
#define REG_SC_BK0D_5E_L      _PK_L_(0x0D, 0x5E)
#define REG_SC_BK0D_5E_H      _PK_H_(0x0D, 0x5E)
#define REG_SC_BK0D_5F_L      _PK_L_(0x0D, 0x5F)
#define REG_SC_BK0D_5F_H      _PK_H_(0x0D, 0x5F)
#define REG_SC_BK0D_60_L      _PK_L_(0x0D, 0x60)
#define REG_SC_BK0D_60_H      _PK_H_(0x0D, 0x60)
#define REG_SC_BK0D_61_L      _PK_L_(0x0D, 0x61)
#define REG_SC_BK0D_61_H      _PK_H_(0x0D, 0x61)
#define REG_SC_BK0D_62_L      _PK_L_(0x0D, 0x62)
#define REG_SC_BK0D_62_H      _PK_H_(0x0D, 0x62)
#define REG_SC_BK0D_63_L      _PK_L_(0x0D, 0x63)
#define REG_SC_BK0D_63_H      _PK_H_(0x0D, 0x63)
#define REG_SC_BK0D_64_L      _PK_L_(0x0D, 0x64)
#define REG_SC_BK0D_64_H      _PK_H_(0x0D, 0x64)
#define REG_SC_BK0D_65_L      _PK_L_(0x0D, 0x65)
#define REG_SC_BK0D_65_H      _PK_H_(0x0D, 0x65)
#define REG_SC_BK0D_66_L      _PK_L_(0x0D, 0x66)
#define REG_SC_BK0D_66_H      _PK_H_(0x0D, 0x66)
#define REG_SC_BK0D_67_L      _PK_L_(0x0D, 0x67)
#define REG_SC_BK0D_67_H      _PK_H_(0x0D, 0x67)
#define REG_SC_BK0D_68_L      _PK_L_(0x0D, 0x68)
#define REG_SC_BK0D_68_H      _PK_H_(0x0D, 0x68)
#define REG_SC_BK0D_69_L      _PK_L_(0x0D, 0x69)
#define REG_SC_BK0D_69_H      _PK_H_(0x0D, 0x69)
#define REG_SC_BK0D_6A_L      _PK_L_(0x0D, 0x6A)
#define REG_SC_BK0D_6A_H      _PK_H_(0x0D, 0x6A)
#define REG_SC_BK0D_6B_L      _PK_L_(0x0D, 0x6B)
#define REG_SC_BK0D_6B_H      _PK_H_(0x0D, 0x6B)
#define REG_SC_BK0D_6C_L      _PK_L_(0x0D, 0x6C)
#define REG_SC_BK0D_6C_H      _PK_H_(0x0D, 0x6C)
#define REG_SC_BK0D_6D_L      _PK_L_(0x0D, 0x6D)
#define REG_SC_BK0D_6D_H      _PK_H_(0x0D, 0x6D)
#define REG_SC_BK0D_6E_L      _PK_L_(0x0D, 0x6E)
#define REG_SC_BK0D_6E_H      _PK_H_(0x0D, 0x6E)
#define REG_SC_BK0D_6F_L      _PK_L_(0x0D, 0x6F)
#define REG_SC_BK0D_6F_H      _PK_H_(0x0D, 0x6F)
#define REG_SC_BK0D_70_L      _PK_L_(0x0D, 0x70)
#define REG_SC_BK0D_70_H      _PK_H_(0x0D, 0x70)
#define REG_SC_BK0D_71_L      _PK_L_(0x0D, 0x71)
#define REG_SC_BK0D_71_H      _PK_H_(0x0D, 0x71)
#define REG_SC_BK0D_72_L      _PK_L_(0x0D, 0x72)
#define REG_SC_BK0D_72_H      _PK_H_(0x0D, 0x72)
#define REG_SC_BK0D_73_L      _PK_L_(0x0D, 0x73)
#define REG_SC_BK0D_73_H      _PK_H_(0x0D, 0x73)
#define REG_SC_BK0D_74_L      _PK_L_(0x0D, 0x74)
#define REG_SC_BK0D_74_H      _PK_H_(0x0D, 0x74)
#define REG_SC_BK0D_75_L      _PK_L_(0x0D, 0x75)
#define REG_SC_BK0D_75_H      _PK_H_(0x0D, 0x75)
#define REG_SC_BK0D_76_L      _PK_L_(0x0D, 0x76)
#define REG_SC_BK0D_76_H      _PK_H_(0x0D, 0x76)
#define REG_SC_BK0D_77_L      _PK_L_(0x0D, 0x77)
#define REG_SC_BK0D_77_H      _PK_H_(0x0D, 0x77)
#define REG_SC_BK0D_78_L      _PK_L_(0x0D, 0x78)
#define REG_SC_BK0D_78_H      _PK_H_(0x0D, 0x78)
#define REG_SC_BK0D_79_L      _PK_L_(0x0D, 0x79)
#define REG_SC_BK0D_79_H      _PK_H_(0x0D, 0x79)
#define REG_SC_BK0D_7A_L      _PK_L_(0x0D, 0x7A)
#define REG_SC_BK0D_7A_H      _PK_H_(0x0D, 0x7A)
#define REG_SC_BK0D_7B_L      _PK_L_(0x0D, 0x7B)
#define REG_SC_BK0D_7B_H      _PK_H_(0x0D, 0x7B)
#define REG_SC_BK0D_7C_L      _PK_L_(0x0D, 0x7C)
#define REG_SC_BK0D_7C_H      _PK_H_(0x0D, 0x7C)
#define REG_SC_BK0D_7D_L      _PK_L_(0x0D, 0x7D)
#define REG_SC_BK0D_7D_H      _PK_H_(0x0D, 0x7D)
#define REG_SC_BK0D_7E_L      _PK_L_(0x0D, 0x7E)
#define REG_SC_BK0D_7E_H      _PK_H_(0x0D, 0x7E)
#define REG_SC_BK0D_7F_L      _PK_L_(0x0D, 0x7F)
#define REG_SC_BK0D_7F_H      _PK_H_(0x0D, 0x7F)

//----------------------------------------------
//  BK0F: VOP
//----------------------------------------------
#define REG_SC_BK0F_18_L      _PK_L_(0x0F, 0x18)
#define REG_SC_BK0F_18_H      _PK_H_(0x0F, 0x18)
#define REG_SC_BK0F_2A_L      _PK_H_(0x0F, 0x2A)
#define REG_SC_BK0F_2A_H      _PK_H_(0x0F, 0x2A)
#define REG_SC_BK0F_55_L      _PK_H_(0x0F, 0x55)
#define REG_SC_BK0F_55_H      _PK_H_(0x0F, 0x55)

//----------------------------------------------
//  BK10: VOP
//----------------------------------------------
#define REG_SC_BK10_00_L      _PK_L_(0x10, 0x00)
#define REG_SC_BK10_00_H      _PK_H_(0x10, 0x00)
#define REG_SC_BK10_01_L      _PK_L_(0x10, 0x01)
#define REG_SC_BK10_01_H      _PK_H_(0x10, 0x01)
#define REG_SC_BK10_02_L      _PK_L_(0x10, 0x02)
#define REG_SC_BK10_02_H      _PK_H_(0x10, 0x02)
#define REG_SC_BK10_03_L      _PK_L_(0x10, 0x03)
#define REG_SC_BK10_03_H      _PK_H_(0x10, 0x03)
#define REG_SC_BK10_04_L      _PK_L_(0x10, 0x04)
#define REG_SC_BK10_04_H      _PK_H_(0x10, 0x04)
#define REG_SC_BK10_05_L      _PK_L_(0x10, 0x05)
#define REG_SC_BK10_05_H      _PK_H_(0x10, 0x05)
#define REG_SC_BK10_06_L      _PK_L_(0x10, 0x06)
#define REG_SC_BK10_06_H      _PK_H_(0x10, 0x06)
#define REG_SC_BK10_07_L      _PK_L_(0x10, 0x07)
#define REG_SC_BK10_07_H      _PK_H_(0x10, 0x07)
#define REG_SC_BK10_08_L      _PK_L_(0x10, 0x08)
#define REG_SC_BK10_08_H      _PK_H_(0x10, 0x08)
#define REG_SC_BK10_09_L      _PK_L_(0x10, 0x09)
#define REG_SC_BK10_09_H      _PK_H_(0x10, 0x09)
#define REG_SC_BK10_0A_L      _PK_L_(0x10, 0x0A)
#define REG_SC_BK10_0A_H      _PK_H_(0x10, 0x0A)
#define REG_SC_BK10_0B_L      _PK_L_(0x10, 0x0B)
#define REG_SC_BK10_0B_H      _PK_H_(0x10, 0x0B)
#define REG_SC_BK10_0C_L      _PK_L_(0x10, 0x0C)
#define REG_SC_BK10_0C_H      _PK_H_(0x10, 0x0C)
#define REG_SC_BK10_0D_L      _PK_L_(0x10, 0x0D)
#define REG_SC_BK10_0D_H      _PK_H_(0x10, 0x0D)

#define REG_SC_BK10_10_L      _PK_L_(0x10, 0x10)
#define REG_SC_BK10_10_H      _PK_H_(0x10, 0x10)

#define REG_SC_BK10_1B_L      _PK_L_(0x10, 0x1B)
#define REG_SC_BK10_1B_H      _PK_H_(0x10, 0x1B)

#define REG_SC_BK10_21_L      _PK_L_(0x10, 0x21)
#define REG_SC_BK10_21_H      _PK_H_(0x10, 0x21)
#define REG_SC_BK10_22_L      _PK_L_(0x10, 0x22)
#define REG_SC_BK10_22_H      _PK_H_(0x10, 0x22)
#define REG_SC_BK10_23_L      _PK_L_(0x10, 0x23)
#define REG_SC_BK10_23_H      _PK_H_(0x10, 0x23)
#define REG_SC_BK10_24_L      _PK_L_(0x10, 0x24)
#define REG_SC_BK10_24_H      _PK_H_(0x10, 0x24)

#define REG_SC_BK10_2F_L      _PK_L_(0x10, 0x2F)
#define REG_SC_BK10_2F_H      _PK_H_(0x10, 0x2F)

#define REG_SC_BK10_46_L      _PK_L_(0x10, 0x46)
#define REG_SC_BK10_46_H      _PK_H_(0x10, 0x46)
#define REG_SC_BK10_47_L      _PK_L_(0x10, 0x47)
#define REG_SC_BK10_47_H      _PK_H_(0x10, 0x47)

#define REG_SC_BK10_50_L      _PK_L_(0x10, 0x50)
#define REG_SC_BK10_50_H      _PK_H_(0x10, 0x50)

#define REG_SC_BK10_6C_L      _PK_L_(0x10, 0x6C)
#define REG_SC_BK10_6C_H      _PK_H_(0x10, 0x6C)
#define REG_SC_BK10_6D_L      _PK_L_(0x10, 0x6D)
#define REG_SC_BK10_6D_H      _PK_H_(0x10, 0x6D)
#define REG_SC_BK10_6E_L      _PK_L_(0x10, 0x6E)
#define REG_SC_BK10_6E_H      _PK_H_(0x10, 0x6E)

#define REG_SC_BK10_6F_L      _PK_L_(0x10, 0x6F)

#define REG_SC_BK10_70_L      _PK_L_(0x10, 0x70)

#define REG_SC_BK10_71_L      _PK_L_(0x10, 0x71)

#define REG_SC_BK10_72_L      _PK_L_(0x10, 0x72)

#define REG_SC_BK10_73_L      _PK_L_(0x10, 0x73)

#define REG_SC_BK10_74_L      _PK_L_(0x10, 0x74)
#define REG_SC_BK10_74_H      _PK_H_(0x10, 0x74)

#define REG_SC_BK10_75_L      _PK_L_(0x10, 0x75)
#define REG_SC_BK10_75_H      _PK_H_(0x10, 0x75)

#define REG_SC_BK10_76_L      _PK_L_(0x10, 0x76)
#define REG_SC_BK10_76_H      _PK_H_(0x10, 0x76)

#define REG_SC_BK10_77_L      _PK_L_(0x10, 0x77)
#define REG_SC_BK10_77_H      _PK_H_(0x10, 0x77)

#define REG_SC_BK10_78_L      _PK_L_(0x10, 0x78)

#define REG_SC_BK10_7A_L      _PK_L_(0x10, 0x7A)
#define REG_SC_BK10_7A_H      _PK_H_(0x10, 0x7A)
#define REG_SC_BK10_7B_L      _PK_L_(0x10, 0x7B)
#define REG_SC_BK10_7B_H      _PK_H_(0x10, 0x7B)
#define REG_SC_BK10_7C_L      _PK_L_(0x10, 0x7C)
#define REG_SC_BK10_7C_H      _PK_H_(0x10, 0x7C)
#define REG_SC_BK10_7D_L      _PK_L_(0x10, 0x7D)
#define REG_SC_BK10_7D_H      _PK_H_(0x10, 0x7D)
#define REG_SC_BK10_7E_L      _PK_L_(0x10, 0x7E)
#define REG_SC_BK10_7E_H      _PK_H_(0x10, 0x7E)
#define REG_SC_BK10_7F_L      _PK_L_(0x10, 0x7F)
#define REG_SC_BK10_7F_H      _PK_H_(0x10, 0x7F)

//----------------------------------------------
//  BK16: OD
//----------------------------------------------
#define REG_SC_BK16_00_L      _PK_L_(0x16, 0x00)
#define REG_SC_BK16_00_H      _PK_H_(0x16, 0x00)
#define REG_SC_BK16_01_L      _PK_L_(0x16, 0x01)
#define REG_SC_BK16_01_H      _PK_H_(0x16, 0x01)
#define REG_SC_BK16_02_L      _PK_L_(0x16, 0x02)
#define REG_SC_BK16_02_H      _PK_H_(0x16, 0x02)
#define REG_SC_BK16_03_L      _PK_L_(0x16, 0x03)
#define REG_SC_BK16_03_H      _PK_H_(0x16, 0x03)
#define REG_SC_BK16_04_L      _PK_L_(0x16, 0x04)
#define REG_SC_BK16_04_H      _PK_H_(0x16, 0x04)
#define REG_SC_BK16_05_L      _PK_L_(0x16, 0x05)
#define REG_SC_BK16_05_H      _PK_H_(0x16, 0x05)
#define REG_SC_BK16_06_L      _PK_L_(0x16, 0x06)
#define REG_SC_BK16_06_H      _PK_H_(0x16, 0x06)
#define REG_SC_BK16_07_L      _PK_L_(0x16, 0x07)
#define REG_SC_BK16_07_H      _PK_H_(0x16, 0x07)
#define REG_SC_BK16_08_L      _PK_L_(0x16, 0x08)
#define REG_SC_BK16_08_H      _PK_H_(0x16, 0x08)
#define REG_SC_BK16_09_L      _PK_L_(0x16, 0x09)
#define REG_SC_BK16_09_H      _PK_H_(0x16, 0x09)
#define REG_SC_BK16_0A_L      _PK_L_(0x16, 0x0A)
#define REG_SC_BK16_0A_H      _PK_H_(0x16, 0x0A)
#define REG_SC_BK16_0B_L      _PK_L_(0x16, 0x0B)
#define REG_SC_BK16_0B_H      _PK_H_(0x16, 0x0B)
#define REG_SC_BK16_0C_L      _PK_L_(0x16, 0x0C)
#define REG_SC_BK16_0C_H      _PK_H_(0x16, 0x0C)
#define REG_SC_BK16_0D_L      _PK_L_(0x16, 0x0D)
#define REG_SC_BK16_0D_H      _PK_H_(0x16, 0x0D)
#define REG_SC_BK16_0E_L      _PK_L_(0x16, 0x0E)
#define REG_SC_BK16_0E_H      _PK_H_(0x16, 0x0E)
#define REG_SC_BK16_0F_L      _PK_L_(0x16, 0x0F)
#define REG_SC_BK16_0F_H      _PK_H_(0x16, 0x0F)
#define REG_SC_BK16_10_L      _PK_L_(0x16, 0x10)
#define REG_SC_BK16_10_H      _PK_H_(0x16, 0x10)
#define REG_SC_BK16_11_L      _PK_L_(0x16, 0x11)
#define REG_SC_BK16_11_H      _PK_H_(0x16, 0x11)
#define REG_SC_BK16_12_L      _PK_L_(0x16, 0x12)
#define REG_SC_BK16_12_H      _PK_H_(0x16, 0x12)
#define REG_SC_BK16_13_L      _PK_L_(0x16, 0x13)
#define REG_SC_BK16_13_H      _PK_H_(0x16, 0x13)
#define REG_SC_BK16_14_L      _PK_L_(0x16, 0x14)
#define REG_SC_BK16_14_H      _PK_H_(0x16, 0x14)
#define REG_SC_BK16_15_L      _PK_L_(0x16, 0x15)
#define REG_SC_BK16_15_H      _PK_H_(0x16, 0x15)
#define REG_SC_BK16_16_L      _PK_L_(0x16, 0x16)
#define REG_SC_BK16_16_H      _PK_H_(0x16, 0x16)
#define REG_SC_BK16_17_L      _PK_L_(0x16, 0x17)
#define REG_SC_BK16_17_H      _PK_H_(0x16, 0x17)
#define REG_SC_BK16_18_L      _PK_L_(0x16, 0x18)
#define REG_SC_BK16_18_H      _PK_H_(0x16, 0x18)
#define REG_SC_BK16_19_L      _PK_L_(0x16, 0x19)
#define REG_SC_BK16_19_H      _PK_H_(0x16, 0x19)
#define REG_SC_BK16_1A_L      _PK_L_(0x16, 0x1A)
#define REG_SC_BK16_1A_H      _PK_H_(0x16, 0x1A)
#define REG_SC_BK16_1B_L      _PK_L_(0x16, 0x1B)
#define REG_SC_BK16_1B_H      _PK_H_(0x16, 0x1B)
#define REG_SC_BK16_1C_L      _PK_L_(0x16, 0x1C)
#define REG_SC_BK16_1C_H      _PK_H_(0x16, 0x1C)
#define REG_SC_BK16_1D_L      _PK_L_(0x16, 0x1D)
#define REG_SC_BK16_1D_H      _PK_H_(0x16, 0x1D)
#define REG_SC_BK16_1E_L      _PK_L_(0x16, 0x1E)
#define REG_SC_BK16_1E_H      _PK_H_(0x16, 0x1E)
#define REG_SC_BK16_1F_L      _PK_L_(0x16, 0x1F)
#define REG_SC_BK16_1F_H      _PK_H_(0x16, 0x1F)
#define REG_SC_BK16_20_L      _PK_L_(0x16, 0x20)
#define REG_SC_BK16_20_H      _PK_H_(0x16, 0x20)
#define REG_SC_BK16_21_L      _PK_L_(0x16, 0x21)
#define REG_SC_BK16_21_H      _PK_H_(0x16, 0x21)
#define REG_SC_BK16_22_L      _PK_L_(0x16, 0x22)
#define REG_SC_BK16_22_H      _PK_H_(0x16, 0x22)
#define REG_SC_BK16_23_L      _PK_L_(0x16, 0x23)
#define REG_SC_BK16_23_H      _PK_H_(0x16, 0x23)
#define REG_SC_BK16_24_L      _PK_L_(0x16, 0x24)
#define REG_SC_BK16_24_H      _PK_H_(0x16, 0x24)
#define REG_SC_BK16_25_L      _PK_L_(0x16, 0x25)
#define REG_SC_BK16_25_H      _PK_H_(0x16, 0x25)
#define REG_SC_BK16_26_L      _PK_L_(0x16, 0x26)
#define REG_SC_BK16_26_H      _PK_H_(0x16, 0x26)
#define REG_SC_BK16_27_L      _PK_L_(0x16, 0x27)
#define REG_SC_BK16_27_H      _PK_H_(0x16, 0x27)
#define REG_SC_BK16_28_L      _PK_L_(0x16, 0x28)
#define REG_SC_BK16_28_H      _PK_H_(0x16, 0x28)
#define REG_SC_BK16_29_L      _PK_L_(0x16, 0x29)
#define REG_SC_BK16_29_H      _PK_H_(0x16, 0x29)
#define REG_SC_BK16_2A_L      _PK_L_(0x16, 0x2A)
#define REG_SC_BK16_2A_H      _PK_H_(0x16, 0x2A)
#define REG_SC_BK16_2B_L      _PK_L_(0x16, 0x2B)
#define REG_SC_BK16_2B_H      _PK_H_(0x16, 0x2B)
#define REG_SC_BK16_2C_L      _PK_L_(0x16, 0x2C)
#define REG_SC_BK16_2C_H      _PK_H_(0x16, 0x2C)
#define REG_SC_BK16_2D_L      _PK_L_(0x16, 0x2D)
#define REG_SC_BK16_2D_H      _PK_H_(0x16, 0x2D)
#define REG_SC_BK16_2E_L      _PK_L_(0x16, 0x2E)
#define REG_SC_BK16_2E_H      _PK_H_(0x16, 0x2E)
#define REG_SC_BK16_2F_L      _PK_L_(0x16, 0x2F)
#define REG_SC_BK16_2F_H      _PK_H_(0x16, 0x2F)
#define REG_SC_BK16_30_L      _PK_L_(0x16, 0x30)
#define REG_SC_BK16_30_H      _PK_H_(0x16, 0x30)
#define REG_SC_BK16_31_L      _PK_L_(0x16, 0x31)
#define REG_SC_BK16_31_H      _PK_H_(0x16, 0x31)
#define REG_SC_BK16_32_L      _PK_L_(0x16, 0x32)
#define REG_SC_BK16_32_H      _PK_H_(0x16, 0x32)
#define REG_SC_BK16_33_L      _PK_L_(0x16, 0x33)
#define REG_SC_BK16_33_H      _PK_H_(0x16, 0x33)
#define REG_SC_BK16_34_L      _PK_L_(0x16, 0x34)
#define REG_SC_BK16_34_H      _PK_H_(0x16, 0x34)
#define REG_SC_BK16_35_L      _PK_L_(0x16, 0x35)
#define REG_SC_BK16_35_H      _PK_H_(0x16, 0x35)
#define REG_SC_BK16_36_L      _PK_L_(0x16, 0x36)
#define REG_SC_BK16_36_H      _PK_H_(0x16, 0x36)
#define REG_SC_BK16_37_L      _PK_L_(0x16, 0x37)
#define REG_SC_BK16_37_H      _PK_H_(0x16, 0x37)
#define REG_SC_BK16_38_L      _PK_L_(0x16, 0x38)
#define REG_SC_BK16_38_H      _PK_H_(0x16, 0x38)
#define REG_SC_BK16_39_L      _PK_L_(0x16, 0x39)
#define REG_SC_BK16_39_H      _PK_H_(0x16, 0x39)
#define REG_SC_BK16_3A_L      _PK_L_(0x16, 0x3A)
#define REG_SC_BK16_3A_H      _PK_H_(0x16, 0x3A)
#define REG_SC_BK16_3B_L      _PK_L_(0x16, 0x3B)
#define REG_SC_BK16_3B_H      _PK_H_(0x16, 0x3B)
#define REG_SC_BK16_3C_L      _PK_L_(0x16, 0x3C)
#define REG_SC_BK16_3C_H      _PK_H_(0x16, 0x3C)
#define REG_SC_BK16_3D_L      _PK_L_(0x16, 0x3D)
#define REG_SC_BK16_3D_H      _PK_H_(0x16, 0x3D)
#define REG_SC_BK16_3E_L      _PK_L_(0x16, 0x3E)
#define REG_SC_BK16_3E_H      _PK_H_(0x16, 0x3E)
#define REG_SC_BK16_3F_L      _PK_L_(0x16, 0x3F)
#define REG_SC_BK16_3F_H      _PK_H_(0x16, 0x3F)
#define REG_SC_BK16_40_L      _PK_L_(0x16, 0x40)
#define REG_SC_BK16_40_H      _PK_H_(0x16, 0x40)
#define REG_SC_BK16_41_L      _PK_L_(0x16, 0x41)
#define REG_SC_BK16_41_H      _PK_H_(0x16, 0x41)
#define REG_SC_BK16_42_L      _PK_L_(0x16, 0x42)
#define REG_SC_BK16_42_H      _PK_H_(0x16, 0x42)
#define REG_SC_BK16_43_L      _PK_L_(0x16, 0x43)
#define REG_SC_BK16_43_H      _PK_H_(0x16, 0x43)
#define REG_SC_BK16_44_L      _PK_L_(0x16, 0x44)
#define REG_SC_BK16_44_H      _PK_H_(0x16, 0x44)
#define REG_SC_BK16_45_L      _PK_L_(0x16, 0x45)
#define REG_SC_BK16_45_H      _PK_H_(0x16, 0x45)
#define REG_SC_BK16_46_L      _PK_L_(0x16, 0x46)
#define REG_SC_BK16_46_H      _PK_H_(0x16, 0x46)
#define REG_SC_BK16_47_L      _PK_L_(0x16, 0x47)
#define REG_SC_BK16_47_H      _PK_H_(0x16, 0x47)
#define REG_SC_BK16_48_L      _PK_L_(0x16, 0x48)
#define REG_SC_BK16_48_H      _PK_H_(0x16, 0x48)
#define REG_SC_BK16_49_L      _PK_L_(0x16, 0x49)
#define REG_SC_BK16_49_H      _PK_H_(0x16, 0x49)
#define REG_SC_BK16_4A_L      _PK_L_(0x16, 0x4A)
#define REG_SC_BK16_4A_H      _PK_H_(0x16, 0x4A)
#define REG_SC_BK16_4B_L      _PK_L_(0x16, 0x4B)
#define REG_SC_BK16_4B_H      _PK_H_(0x16, 0x4B)
#define REG_SC_BK16_4C_L      _PK_L_(0x16, 0x4C)
#define REG_SC_BK16_4C_H      _PK_H_(0x16, 0x4C)
#define REG_SC_BK16_4D_L      _PK_L_(0x16, 0x4D)
#define REG_SC_BK16_4D_H      _PK_H_(0x16, 0x4D)
#define REG_SC_BK16_4E_L      _PK_L_(0x16, 0x4E)
#define REG_SC_BK16_4E_H      _PK_H_(0x16, 0x4E)
#define REG_SC_BK16_4F_L      _PK_L_(0x16, 0x4F)
#define REG_SC_BK16_4F_H      _PK_H_(0x16, 0x4F)
#define REG_SC_BK16_50_L      _PK_L_(0x16, 0x50)
#define REG_SC_BK16_50_H      _PK_H_(0x16, 0x50)
#define REG_SC_BK16_51_L      _PK_L_(0x16, 0x51)
#define REG_SC_BK16_51_H      _PK_H_(0x16, 0x51)
#define REG_SC_BK16_52_L      _PK_L_(0x16, 0x52)
#define REG_SC_BK16_52_H      _PK_H_(0x16, 0x52)
#define REG_SC_BK16_53_L      _PK_L_(0x16, 0x53)
#define REG_SC_BK16_53_H      _PK_H_(0x16, 0x53)
#define REG_SC_BK16_54_L      _PK_L_(0x16, 0x54)
#define REG_SC_BK16_54_H      _PK_H_(0x16, 0x54)
#define REG_SC_BK16_55_L      _PK_L_(0x16, 0x55)
#define REG_SC_BK16_55_H      _PK_H_(0x16, 0x55)
#define REG_SC_BK16_56_L      _PK_L_(0x16, 0x56)
#define REG_SC_BK16_56_H      _PK_H_(0x16, 0x56)
#define REG_SC_BK16_57_L      _PK_L_(0x16, 0x57)
#define REG_SC_BK16_57_H      _PK_H_(0x16, 0x57)
#define REG_SC_BK16_58_L      _PK_L_(0x16, 0x58)
#define REG_SC_BK16_58_H      _PK_H_(0x16, 0x58)
#define REG_SC_BK16_59_L      _PK_L_(0x16, 0x59)
#define REG_SC_BK16_59_H      _PK_H_(0x16, 0x59)
#define REG_SC_BK16_5A_L      _PK_L_(0x16, 0x5A)
#define REG_SC_BK16_5A_H      _PK_H_(0x16, 0x5A)
#define REG_SC_BK16_5B_L      _PK_L_(0x16, 0x5B)
#define REG_SC_BK16_5B_H      _PK_H_(0x16, 0x5B)
#define REG_SC_BK16_5C_L      _PK_L_(0x16, 0x5C)
#define REG_SC_BK16_5C_H      _PK_H_(0x16, 0x5C)
#define REG_SC_BK16_5D_L      _PK_L_(0x16, 0x5D)
#define REG_SC_BK16_5D_H      _PK_H_(0x16, 0x5D)
#define REG_SC_BK16_5E_L      _PK_L_(0x16, 0x5E)
#define REG_SC_BK16_5E_H      _PK_H_(0x16, 0x5E)
#define REG_SC_BK16_5F_L      _PK_L_(0x16, 0x5F)
#define REG_SC_BK16_5F_H      _PK_H_(0x16, 0x5F)
#define REG_SC_BK16_60_L      _PK_L_(0x16, 0x60)
#define REG_SC_BK16_60_H      _PK_H_(0x16, 0x60)
#define REG_SC_BK16_61_L      _PK_L_(0x16, 0x61)
#define REG_SC_BK16_61_H      _PK_H_(0x16, 0x61)
#define REG_SC_BK16_62_L      _PK_L_(0x16, 0x62)
#define REG_SC_BK16_62_H      _PK_H_(0x16, 0x62)
#define REG_SC_BK16_63_L      _PK_L_(0x16, 0x63)
#define REG_SC_BK16_63_H      _PK_H_(0x16, 0x63)
#define REG_SC_BK16_64_L      _PK_L_(0x16, 0x64)
#define REG_SC_BK16_64_H      _PK_H_(0x16, 0x64)
#define REG_SC_BK16_65_L      _PK_L_(0x16, 0x65)
#define REG_SC_BK16_65_H      _PK_H_(0x16, 0x65)
#define REG_SC_BK16_66_L      _PK_L_(0x16, 0x66)
#define REG_SC_BK16_66_H      _PK_H_(0x16, 0x66)
#define REG_SC_BK16_67_L      _PK_L_(0x16, 0x67)
#define REG_SC_BK16_67_H      _PK_H_(0x16, 0x67)
#define REG_SC_BK16_68_L      _PK_L_(0x16, 0x68)
#define REG_SC_BK16_68_H      _PK_H_(0x16, 0x68)
#define REG_SC_BK16_69_L      _PK_L_(0x16, 0x69)
#define REG_SC_BK16_69_H      _PK_H_(0x16, 0x69)
#define REG_SC_BK16_6A_L      _PK_L_(0x16, 0x6A)
#define REG_SC_BK16_6A_H      _PK_H_(0x16, 0x6A)
#define REG_SC_BK16_6B_L      _PK_L_(0x16, 0x6B)
#define REG_SC_BK16_6B_H      _PK_H_(0x16, 0x6B)
#define REG_SC_BK16_6C_L      _PK_L_(0x16, 0x6C)
#define REG_SC_BK16_6C_H      _PK_H_(0x16, 0x6C)
#define REG_SC_BK16_6D_L      _PK_L_(0x16, 0x6D)
#define REG_SC_BK16_6D_H      _PK_H_(0x16, 0x6D)
#define REG_SC_BK16_6E_L      _PK_L_(0x16, 0x6E)
#define REG_SC_BK16_6E_H      _PK_H_(0x16, 0x6E)
#define REG_SC_BK16_6F_L      _PK_L_(0x16, 0x6F)
#define REG_SC_BK16_6F_H      _PK_H_(0x16, 0x6F)
#define REG_SC_BK16_70_L      _PK_L_(0x16, 0x70)
#define REG_SC_BK16_70_H      _PK_H_(0x16, 0x70)
#define REG_SC_BK16_71_L      _PK_L_(0x16, 0x71)
#define REG_SC_BK16_71_H      _PK_H_(0x16, 0x71)
#define REG_SC_BK16_72_L      _PK_L_(0x16, 0x72)
#define REG_SC_BK16_72_H      _PK_H_(0x16, 0x72)
#define REG_SC_BK16_73_L      _PK_L_(0x16, 0x73)
#define REG_SC_BK16_73_H      _PK_H_(0x16, 0x73)
#define REG_SC_BK16_74_L      _PK_L_(0x16, 0x74)
#define REG_SC_BK16_74_H      _PK_H_(0x16, 0x74)
#define REG_SC_BK16_75_L      _PK_L_(0x16, 0x75)
#define REG_SC_BK16_75_H      _PK_H_(0x16, 0x75)
#define REG_SC_BK16_76_L      _PK_L_(0x16, 0x76)
#define REG_SC_BK16_76_H      _PK_H_(0x16, 0x76)
#define REG_SC_BK16_77_L      _PK_L_(0x16, 0x77)
#define REG_SC_BK16_77_H      _PK_H_(0x16, 0x77)
#define REG_SC_BK16_78_L      _PK_L_(0x16, 0x78)
#define REG_SC_BK16_78_H      _PK_H_(0x16, 0x78)
#define REG_SC_BK16_79_L      _PK_L_(0x16, 0x79)
#define REG_SC_BK16_79_H      _PK_H_(0x16, 0x79)
#define REG_SC_BK16_7A_L      _PK_L_(0x16, 0x7A)
#define REG_SC_BK16_7A_H      _PK_H_(0x16, 0x7A)
#define REG_SC_BK16_7B_L      _PK_L_(0x16, 0x7B)
#define REG_SC_BK16_7B_H      _PK_H_(0x16, 0x7B)
#define REG_SC_BK16_7C_L      _PK_L_(0x16, 0x7C)
#define REG_SC_BK16_7C_H      _PK_H_(0x16, 0x7C)
#define REG_SC_BK16_7D_L      _PK_L_(0x16, 0x7D)
#define REG_SC_BK16_7D_H      _PK_H_(0x16, 0x7D)
#define REG_SC_BK16_7E_L      _PK_L_(0x16, 0x7E)
#define REG_SC_BK16_7E_H      _PK_H_(0x16, 0x7E)
#define REG_SC_BK16_7F_L      _PK_L_(0x16, 0x7F)
#define REG_SC_BK16_7F_H      _PK_H_(0x16, 0x7F)

//----------------------------------------------
//  BK19: PEAKING
//----------------------------------------------
#define REG_SC_BK19_10_L      _PK_L_(0x19, 0x10)

//----------------------------------------------
//  BK24
//----------------------------------------------
#define REG_SC_BK24_3F_L       _PK_L_(0x24, 0x3F)
#define REG_SC_BK24_3F_H       _PK_H_(0x24, 0x3F)

//----------------------------------------------
//  BK24
//----------------------------------------------
#define REG_SC_BK24_1B_L       _PK_L_(0x24, 0x1B)
#define REG_SC_BK24_1C_L       _PK_L_(0x24, 0x1C)
#define REG_SC_BK24_1D_L       _PK_L_(0x24, 0x1D)
#define REG_SC_BK24_26_L       _PK_L_(0x24, 0x26)
#define REG_SC_BK24_2C_L       _PK_L_(0x24, 0x2C)
#define REG_SC_BK24_2E_L       _PK_L_(0x24, 0x2E)
#define REG_SC_BK24_30_L       _PK_L_(0x24, 0x30)
#define REG_SC_BK2E_37_L       _PK_L_(0x2E, 0x37)
#define REG_SC_BK2E_37_H       _PK_H_(0x2E, 0x37)

//----------------------------------------------
//  BK37: OC
//----------------------------------------------
#define REG_SC_BK37_01_L      _PK_L_(0x37, 0x01)
#define REG_SC_BK37_01_H      _PK_H_(0x37, 0x01)
#define REG_SC_BK37_02_L      _PK_L_(0x37, 0x02)
#define REG_SC_BK37_02_H      _PK_H_(0x37, 0x02)
#define REG_SC_BK37_03_L      _PK_L_(0x37, 0x03)
#define REG_SC_BK37_03_H      _PK_H_(0x37, 0x03)
#define REG_SC_BK37_04_L      _PK_L_(0x37, 0x04)
#define REG_SC_BK37_04_H      _PK_H_(0x37, 0x04)
#define REG_SC_BK37_05_L      _PK_L_(0x37, 0x05)
#define REG_SC_BK37_05_H      _PK_H_(0x37, 0x05)
#define REG_SC_BK37_06_L      _PK_L_(0x37, 0x06)
#define REG_SC_BK37_06_H      _PK_H_(0x37, 0x06)
#define REG_SC_BK37_07_L      _PK_L_(0x37, 0x07)
#define REG_SC_BK37_07_H      _PK_H_(0x37, 0x07)
#define REG_SC_BK37_08_L      _PK_L_(0x37, 0x08)
#define REG_SC_BK37_08_H      _PK_H_(0x37, 0x08)
#define REG_SC_BK37_09_L      _PK_L_(0x37, 0x09)
#define REG_SC_BK37_09_H      _PK_H_(0x37, 0x09)
#define REG_SC_BK37_0A_L      _PK_L_(0x37, 0x0A)
#define REG_SC_BK37_0A_H      _PK_H_(0x37, 0x0A)
#define REG_SC_BK37_0B_L      _PK_L_(0x37, 0x0B)
#define REG_SC_BK37_0B_H      _PK_H_(0x37, 0x0B)
#define REG_SC_BK37_0C_L      _PK_L_(0x37, 0x0C)
#define REG_SC_BK37_0C_H      _PK_H_(0x37, 0x0C)
#define REG_SC_BK37_0D_L      _PK_L_(0x37, 0x0D)
#define REG_SC_BK37_0D_H      _PK_H_(0x37, 0x0D)
#define REG_SC_BK37_0E_L      _PK_L_(0x37, 0x0E)
#define REG_SC_BK37_0E_H      _PK_H_(0x37, 0x0E)
#define REG_SC_BK37_0F_L      _PK_L_(0x37, 0x0F)
#define REG_SC_BK37_0F_H      _PK_H_(0x37, 0x0F)
#define REG_SC_BK37_10_L      _PK_L_(0x37, 0x10)
#define REG_SC_BK37_10_H      _PK_H_(0x37, 0x10)
#define REG_SC_BK37_11_L      _PK_L_(0x37, 0x11)
#define REG_SC_BK37_11_H      _PK_H_(0x37, 0x11)
#define REG_SC_BK37_12_L      _PK_L_(0x37, 0x12)
#define REG_SC_BK37_12_H      _PK_H_(0x37, 0x12)
#define REG_SC_BK37_13_L      _PK_L_(0x37, 0x13)
#define REG_SC_BK37_13_H      _PK_H_(0x37, 0x13)
#define REG_SC_BK37_14_L      _PK_L_(0x37, 0x14)
#define REG_SC_BK37_14_H      _PK_H_(0x37, 0x14)
#define REG_SC_BK37_15_L      _PK_L_(0x37, 0x15)
#define REG_SC_BK37_15_H      _PK_H_(0x37, 0x15)
#define REG_SC_BK37_16_L      _PK_L_(0x37, 0x16)
#define REG_SC_BK37_16_H      _PK_H_(0x37, 0x16)
#define REG_SC_BK37_17_L      _PK_L_(0x37, 0x17)
#define REG_SC_BK37_17_H      _PK_H_(0x37, 0x17)
#define REG_SC_BK37_18_L      _PK_L_(0x37, 0x18)
#define REG_SC_BK37_18_H      _PK_H_(0x37, 0x18)
#define REG_SC_BK37_19_L      _PK_L_(0x37, 0x19)
#define REG_SC_BK37_19_H      _PK_H_(0x37, 0x19)
#define REG_SC_BK37_1A_L      _PK_L_(0x37, 0x1A)
#define REG_SC_BK37_1A_H      _PK_H_(0x37, 0x1A)
#define REG_SC_BK37_1B_L      _PK_L_(0x37, 0x1B)
#define REG_SC_BK37_1B_H      _PK_H_(0x37, 0x1B)
#define REG_SC_BK37_1C_L      _PK_L_(0x37, 0x1C)
#define REG_SC_BK37_1C_H      _PK_H_(0x37, 0x1C)
#define REG_SC_BK37_1D_L      _PK_L_(0x37, 0x1D)
#define REG_SC_BK37_1D_H      _PK_H_(0x37, 0x1D)
#define REG_SC_BK37_1E_L      _PK_L_(0x37, 0x1E)
#define REG_SC_BK37_1E_H      _PK_H_(0x37, 0x1E)
#define REG_SC_BK37_1F_L      _PK_L_(0x37, 0x1F)
#define REG_SC_BK37_1F_H      _PK_H_(0x37, 0x1F)
#define REG_SC_BK37_20_L      _PK_L_(0x37, 0x20)
#define REG_SC_BK37_20_H      _PK_H_(0x37, 0x20)
#define REG_SC_BK37_21_L      _PK_L_(0x37, 0x21)
#define REG_SC_BK37_21_H      _PK_H_(0x37, 0x21)
#define REG_SC_BK37_22_L      _PK_L_(0x37, 0x22)
#define REG_SC_BK37_22_H      _PK_H_(0x37, 0x22)
#define REG_SC_BK37_23_L      _PK_L_(0x37, 0x23)
#define REG_SC_BK37_23_H      _PK_H_(0x37, 0x23)
#define REG_SC_BK37_24_L      _PK_L_(0x37, 0x24)
#define REG_SC_BK37_24_H      _PK_H_(0x37, 0x24)
#define REG_SC_BK37_25_L      _PK_L_(0x37, 0x25)
#define REG_SC_BK37_25_H      _PK_H_(0x37, 0x25)
#define REG_SC_BK37_26_L      _PK_L_(0x37, 0x26)
#define REG_SC_BK37_26_H      _PK_H_(0x37, 0x26)
#define REG_SC_BK37_27_L      _PK_L_(0x37, 0x27)
#define REG_SC_BK37_27_H      _PK_H_(0x37, 0x27)
#define REG_SC_BK37_28_L      _PK_L_(0x37, 0x28)
#define REG_SC_BK37_28_H      _PK_H_(0x37, 0x28)
#define REG_SC_BK37_29_L      _PK_L_(0x37, 0x29)
#define REG_SC_BK37_29_H      _PK_H_(0x37, 0x29)
#define REG_SC_BK37_2A_L      _PK_L_(0x37, 0x2A)
#define REG_SC_BK37_2A_H      _PK_H_(0x37, 0x2A)
#define REG_SC_BK37_2B_L      _PK_L_(0x37, 0x2B)
#define REG_SC_BK37_2B_H      _PK_H_(0x37, 0x2B)
#define REG_SC_BK37_2C_L      _PK_L_(0x37, 0x2C)
#define REG_SC_BK37_2C_H      _PK_H_(0x37, 0x2C)
#define REG_SC_BK37_2D_L      _PK_L_(0x37, 0x2D)
#define REG_SC_BK37_2D_H      _PK_H_(0x37, 0x2D)
#define REG_SC_BK37_2E_L      _PK_L_(0x37, 0x2E)
#define REG_SC_BK37_2E_H      _PK_H_(0x37, 0x2E)
#define REG_SC_BK37_2F_L      _PK_L_(0x37, 0x2F)
#define REG_SC_BK37_2F_H      _PK_H_(0x37, 0x2F)

//----------------------------------------------
//  BK3F
//----------------------------------------------
#define REG_SC_BK3F_0B_L       _PK_L_(0x3F, 0x0B)
#define REG_SC_BK3F_0B_H       _PK_H_(0x3F, 0x0B)
#define REG_SC_BK3F_10_L       _PK_L_(0x3F, 0x10)
#define REG_SC_BK3F_10_H       _PK_H_(0x3F, 0x10)
#define REG_SC_BK3F_12_L       _PK_L_(0x3F, 0x12)
#define REG_SC_BK3F_12_H       _PK_H_(0x3F, 0x12)
#define REG_SC_BK3F_17_L       _PK_L_(0x3F, 0x17)
#define REG_SC_BK3F_17_H       _PK_H_(0x3F, 0x17)
#define REG_SC_BK3F_50_L       _PK_L_(0x3F, 0x50)
#define REG_SC_BK3F_50_H       _PK_H_(0x3F, 0x50)

//----------------------------------------------
//  BK45: FRC OP2
//----------------------------------------------
#define REG_SC_BK45_00_L      _PK_L_(0x45, 0x00)
#define REG_SC_BK45_00_H      _PK_H_(0x45, 0x00)
#define REG_SC_BK45_01_L      _PK_L_(0x45, 0x01)
#define REG_SC_BK45_01_H      _PK_H_(0x45, 0x01)
#define REG_SC_BK45_02_L      _PK_L_(0x45, 0x02)
#define REG_SC_BK45_02_H      _PK_H_(0x45, 0x02)
#define REG_SC_BK45_03_L      _PK_L_(0x45, 0x03)
#define REG_SC_BK45_03_H      _PK_H_(0x45, 0x03)
#define REG_SC_BK45_04_L      _PK_L_(0x45, 0x04)
#define REG_SC_BK45_04_H      _PK_H_(0x45, 0x04)
#define REG_SC_BK45_05_L      _PK_L_(0x45, 0x05)
#define REG_SC_BK45_05_H      _PK_H_(0x45, 0x05)
#define REG_SC_BK45_06_L      _PK_L_(0x45, 0x06)
#define REG_SC_BK45_06_H      _PK_H_(0x45, 0x06)
#define REG_SC_BK45_07_L      _PK_L_(0x45, 0x07)
#define REG_SC_BK45_07_H      _PK_H_(0x45, 0x07)
#define REG_SC_BK45_08_L      _PK_L_(0x45, 0x08)
#define REG_SC_BK45_08_H      _PK_H_(0x45, 0x08)
#define REG_SC_BK45_09_L      _PK_L_(0x45, 0x09)
#define REG_SC_BK45_09_H      _PK_H_(0x45, 0x09)
#define REG_SC_BK45_0A_L      _PK_L_(0x45, 0x0A)
#define REG_SC_BK45_0A_H      _PK_H_(0x45, 0x0A)
#define REG_SC_BK45_0B_L      _PK_L_(0x45, 0x0B)
#define REG_SC_BK45_0B_H      _PK_H_(0x45, 0x0B)
#define REG_SC_BK45_0C_L      _PK_L_(0x45, 0x0C)
#define REG_SC_BK45_0C_H      _PK_H_(0x45, 0x0C)
#define REG_SC_BK45_0D_L      _PK_L_(0x45, 0x0D)
#define REG_SC_BK45_0D_H      _PK_H_(0x45, 0x0D)
#define REG_SC_BK45_0E_L      _PK_L_(0x45, 0x0E)
#define REG_SC_BK45_0E_H      _PK_H_(0x45, 0x0E)
#define REG_SC_BK45_0F_L      _PK_L_(0x45, 0x0F)
#define REG_SC_BK45_0F_H      _PK_H_(0x45, 0x0F)
#define REG_SC_BK45_10_L      _PK_L_(0x45, 0x10)
#define REG_SC_BK45_10_H      _PK_H_(0x45, 0x10)
#define REG_SC_BK45_11_L      _PK_L_(0x45, 0x11)
#define REG_SC_BK45_11_H      _PK_H_(0x45, 0x11)
#define REG_SC_BK45_12_L      _PK_L_(0x45, 0x12)
#define REG_SC_BK45_12_H      _PK_H_(0x45, 0x12)
#define REG_SC_BK45_13_L      _PK_L_(0x45, 0x13)
#define REG_SC_BK45_13_H      _PK_H_(0x45, 0x13)
#define REG_SC_BK45_14_L      _PK_L_(0x45, 0x14)
#define REG_SC_BK45_14_H      _PK_H_(0x45, 0x14)
#define REG_SC_BK45_15_L      _PK_L_(0x45, 0x15)
#define REG_SC_BK45_15_H      _PK_H_(0x45, 0x15)
#define REG_SC_BK45_16_L      _PK_L_(0x45, 0x16)
#define REG_SC_BK45_16_H      _PK_H_(0x45, 0x16)
#define REG_SC_BK45_17_L      _PK_L_(0x45, 0x17)
#define REG_SC_BK45_17_H      _PK_H_(0x45, 0x17)
#define REG_SC_BK45_18_L      _PK_L_(0x45, 0x18)
#define REG_SC_BK45_18_H      _PK_H_(0x45, 0x18)
#define REG_SC_BK45_19_L      _PK_L_(0x45, 0x19)
#define REG_SC_BK45_19_H      _PK_H_(0x45, 0x19)
#define REG_SC_BK45_1A_L      _PK_L_(0x45, 0x1A)
#define REG_SC_BK45_1A_H      _PK_H_(0x45, 0x1A)
#define REG_SC_BK45_1B_L      _PK_L_(0x45, 0x1B)
#define REG_SC_BK45_1B_H      _PK_H_(0x45, 0x1B)
#define REG_SC_BK45_1C_L      _PK_L_(0x45, 0x1C)
#define REG_SC_BK45_1C_H      _PK_H_(0x45, 0x1C)
#define REG_SC_BK45_1D_L      _PK_L_(0x45, 0x1D)
#define REG_SC_BK45_1D_H      _PK_H_(0x45, 0x1D)
#define REG_SC_BK45_1E_L      _PK_L_(0x45, 0x1E)
#define REG_SC_BK45_1E_H      _PK_H_(0x45, 0x1E)
#define REG_SC_BK45_1F_L      _PK_L_(0x45, 0x1F)
#define REG_SC_BK45_1F_H      _PK_H_(0x45, 0x1F)
#define REG_SC_BK45_20_L      _PK_L_(0x45, 0x20)
#define REG_SC_BK45_20_H      _PK_H_(0x45, 0x20)
#define REG_SC_BK45_21_L      _PK_L_(0x45, 0x21)
#define REG_SC_BK45_21_H      _PK_H_(0x45, 0x21)
#define REG_SC_BK45_22_L      _PK_L_(0x45, 0x22)
#define REG_SC_BK45_22_H      _PK_H_(0x45, 0x22)
#define REG_SC_BK45_23_L      _PK_L_(0x45, 0x23)
#define REG_SC_BK45_23_H      _PK_H_(0x45, 0x23)
#define REG_SC_BK45_24_L      _PK_L_(0x45, 0x24)
#define REG_SC_BK45_24_H      _PK_H_(0x45, 0x24)
#define REG_SC_BK45_25_L      _PK_L_(0x45, 0x25)
#define REG_SC_BK45_25_H      _PK_H_(0x45, 0x25)
#define REG_SC_BK45_26_L      _PK_L_(0x45, 0x26)
#define REG_SC_BK45_26_H      _PK_H_(0x45, 0x26)
#define REG_SC_BK45_27_L      _PK_L_(0x45, 0x27)
#define REG_SC_BK45_27_H      _PK_H_(0x45, 0x27)
#define REG_SC_BK45_28_L      _PK_L_(0x45, 0x28)
#define REG_SC_BK45_28_H      _PK_H_(0x45, 0x28)
#define REG_SC_BK45_29_L      _PK_L_(0x45, 0x29)
#define REG_SC_BK45_29_H      _PK_H_(0x45, 0x29)
#define REG_SC_BK45_2A_L      _PK_L_(0x45, 0x2A)
#define REG_SC_BK45_2A_H      _PK_H_(0x45, 0x2A)
#define REG_SC_BK45_2B_L      _PK_L_(0x45, 0x2B)
#define REG_SC_BK45_2B_H      _PK_H_(0x45, 0x2B)
#define REG_SC_BK45_2C_L      _PK_L_(0x45, 0x2C)
#define REG_SC_BK45_2C_H      _PK_H_(0x45, 0x2C)
#define REG_SC_BK45_2D_L      _PK_L_(0x45, 0x2D)
#define REG_SC_BK45_2D_H      _PK_H_(0x45, 0x2D)
#define REG_SC_BK45_2E_L      _PK_L_(0x45, 0x2E)
#define REG_SC_BK45_2E_H      _PK_H_(0x45, 0x2E)
#define REG_SC_BK45_2F_L      _PK_L_(0x45, 0x2F)
#define REG_SC_BK45_2F_H      _PK_H_(0x45, 0x2F)
#define REG_SC_BK45_30_L      _PK_L_(0x45, 0x30)
#define REG_SC_BK45_30_H      _PK_H_(0x45, 0x30)
#define REG_SC_BK45_31_L      _PK_L_(0x45, 0x31)
#define REG_SC_BK45_31_H      _PK_H_(0x45, 0x31)
#define REG_SC_BK45_32_L      _PK_L_(0x45, 0x32)
#define REG_SC_BK45_32_H      _PK_H_(0x45, 0x32)
#define REG_SC_BK45_33_L      _PK_L_(0x45, 0x33)
#define REG_SC_BK45_33_H      _PK_H_(0x45, 0x33)
#define REG_SC_BK45_34_L      _PK_L_(0x45, 0x34)
#define REG_SC_BK45_34_H      _PK_H_(0x45, 0x34)
#define REG_SC_BK45_35_L      _PK_L_(0x45, 0x35)
#define REG_SC_BK45_35_H      _PK_H_(0x45, 0x35)
#define REG_SC_BK45_36_L      _PK_L_(0x45, 0x36)
#define REG_SC_BK45_36_H      _PK_H_(0x45, 0x36)
#define REG_SC_BK45_37_L      _PK_L_(0x45, 0x37)
#define REG_SC_BK45_37_H      _PK_H_(0x45, 0x37)
#define REG_SC_BK45_38_L      _PK_L_(0x45, 0x38)
#define REG_SC_BK45_38_H      _PK_H_(0x45, 0x38)
#define REG_SC_BK45_39_L      _PK_L_(0x45, 0x39)
#define REG_SC_BK45_39_H      _PK_H_(0x45, 0x39)
#define REG_SC_BK45_3A_L      _PK_L_(0x45, 0x3A)
#define REG_SC_BK45_3A_H      _PK_H_(0x45, 0x3A)
#define REG_SC_BK45_3B_L      _PK_L_(0x45, 0x3B)
#define REG_SC_BK45_3B_H      _PK_H_(0x45, 0x3B)
#define REG_SC_BK45_3C_L      _PK_L_(0x45, 0x3C)
#define REG_SC_BK45_3C_H      _PK_H_(0x45, 0x3C)
#define REG_SC_BK45_3D_L      _PK_L_(0x45, 0x3D)
#define REG_SC_BK45_3D_H      _PK_H_(0x45, 0x3D)
#define REG_SC_BK45_3E_L      _PK_L_(0x45, 0x3E)
#define REG_SC_BK45_3E_H      _PK_H_(0x45, 0x3E)
#define REG_SC_BK45_3F_L      _PK_L_(0x45, 0x3F)
#define REG_SC_BK45_3F_H      _PK_H_(0x45, 0x3F)
#define REG_SC_BK45_40_L      _PK_L_(0x45, 0x40)
#define REG_SC_BK45_40_H      _PK_H_(0x45, 0x40)
#define REG_SC_BK45_41_L      _PK_L_(0x45, 0x41)
#define REG_SC_BK45_41_H      _PK_H_(0x45, 0x41)
#define REG_SC_BK45_42_L      _PK_L_(0x45, 0x42)
#define REG_SC_BK45_42_H      _PK_H_(0x45, 0x42)
#define REG_SC_BK45_43_L      _PK_L_(0x45, 0x43)
#define REG_SC_BK45_43_H      _PK_H_(0x45, 0x43)
#define REG_SC_BK45_44_L      _PK_L_(0x45, 0x44)
#define REG_SC_BK45_44_H      _PK_H_(0x45, 0x44)
#define REG_SC_BK45_45_L      _PK_L_(0x45, 0x45)
#define REG_SC_BK45_45_H      _PK_H_(0x45, 0x45)
#define REG_SC_BK45_46_L      _PK_L_(0x45, 0x46)
#define REG_SC_BK45_46_H      _PK_H_(0x45, 0x46)
#define REG_SC_BK45_47_L      _PK_L_(0x45, 0x47)
#define REG_SC_BK45_47_H      _PK_H_(0x45, 0x47)
#define REG_SC_BK45_48_L      _PK_L_(0x45, 0x48)
#define REG_SC_BK45_48_H      _PK_H_(0x45, 0x48)
#define REG_SC_BK45_49_L      _PK_L_(0x45, 0x49)
#define REG_SC_BK45_49_H      _PK_H_(0x45, 0x49)
#define REG_SC_BK45_4A_L      _PK_L_(0x45, 0x4A)
#define REG_SC_BK45_4A_H      _PK_H_(0x45, 0x4A)
#define REG_SC_BK45_4B_L      _PK_L_(0x45, 0x4B)
#define REG_SC_BK45_4B_H      _PK_H_(0x45, 0x4B)
#define REG_SC_BK45_4C_L      _PK_L_(0x45, 0x4C)
#define REG_SC_BK45_4C_H      _PK_H_(0x45, 0x4C)
#define REG_SC_BK45_4D_L      _PK_L_(0x45, 0x4D)
#define REG_SC_BK45_4D_H      _PK_H_(0x45, 0x4D)
#define REG_SC_BK45_4E_L      _PK_L_(0x45, 0x4E)
#define REG_SC_BK45_4E_H      _PK_H_(0x45, 0x4E)
#define REG_SC_BK45_4F_L      _PK_L_(0x45, 0x4F)
#define REG_SC_BK45_4F_H      _PK_H_(0x45, 0x4F)
#define REG_SC_BK45_50_L      _PK_L_(0x45, 0x50)
#define REG_SC_BK45_50_H      _PK_H_(0x45, 0x50)
#define REG_SC_BK45_51_L      _PK_L_(0x45, 0x51)
#define REG_SC_BK45_51_H      _PK_H_(0x45, 0x51)
#define REG_SC_BK45_52_L      _PK_L_(0x45, 0x52)
#define REG_SC_BK45_52_H      _PK_H_(0x45, 0x52)
#define REG_SC_BK45_53_L      _PK_L_(0x45, 0x53)
#define REG_SC_BK45_53_H      _PK_H_(0x45, 0x53)
#define REG_SC_BK45_54_L      _PK_L_(0x45, 0x54)
#define REG_SC_BK45_54_H      _PK_H_(0x45, 0x54)
#define REG_SC_BK45_55_L      _PK_L_(0x45, 0x55)
#define REG_SC_BK45_55_H      _PK_H_(0x45, 0x55)
#define REG_SC_BK45_56_L      _PK_L_(0x45, 0x56)
#define REG_SC_BK45_56_H      _PK_H_(0x45, 0x56)
#define REG_SC_BK45_57_L      _PK_L_(0x45, 0x57)
#define REG_SC_BK45_57_H      _PK_H_(0x45, 0x57)
#define REG_SC_BK45_58_L      _PK_L_(0x45, 0x58)
#define REG_SC_BK45_58_H      _PK_H_(0x45, 0x58)
#define REG_SC_BK45_59_L      _PK_L_(0x45, 0x59)
#define REG_SC_BK45_59_H      _PK_H_(0x45, 0x59)
#define REG_SC_BK45_5A_L      _PK_L_(0x45, 0x5A)
#define REG_SC_BK45_5A_H      _PK_H_(0x45, 0x5A)
#define REG_SC_BK45_5B_L      _PK_L_(0x45, 0x5B)
#define REG_SC_BK45_5B_H      _PK_H_(0x45, 0x5B)
#define REG_SC_BK45_5C_L      _PK_L_(0x45, 0x5C)
#define REG_SC_BK45_5C_H      _PK_H_(0x45, 0x5C)
#define REG_SC_BK45_5D_L      _PK_L_(0x45, 0x5D)
#define REG_SC_BK45_5D_H      _PK_H_(0x45, 0x5D)
#define REG_SC_BK45_5E_L      _PK_L_(0x45, 0x5E)
#define REG_SC_BK45_5E_H      _PK_H_(0x45, 0x5E)
#define REG_SC_BK45_5F_L      _PK_L_(0x45, 0x5F)
#define REG_SC_BK45_5F_H      _PK_H_(0x45, 0x5F)
#define REG_SC_BK45_60_L      _PK_L_(0x45, 0x60)
#define REG_SC_BK45_60_H      _PK_H_(0x45, 0x60)
#define REG_SC_BK45_61_L      _PK_L_(0x45, 0x61)
#define REG_SC_BK45_61_H      _PK_H_(0x45, 0x61)
#define REG_SC_BK45_62_L      _PK_L_(0x45, 0x62)
#define REG_SC_BK45_62_H      _PK_H_(0x45, 0x62)
#define REG_SC_BK45_63_L      _PK_L_(0x45, 0x63)
#define REG_SC_BK45_63_H      _PK_H_(0x45, 0x63)
#define REG_SC_BK45_64_L      _PK_L_(0x45, 0x64)
#define REG_SC_BK45_64_H      _PK_H_(0x45, 0x64)
#define REG_SC_BK45_65_L      _PK_L_(0x45, 0x65)
#define REG_SC_BK45_65_H      _PK_H_(0x45, 0x65)
#define REG_SC_BK45_66_L      _PK_L_(0x45, 0x66)
#define REG_SC_BK45_66_H      _PK_H_(0x45, 0x66)
#define REG_SC_BK45_67_L      _PK_L_(0x45, 0x67)
#define REG_SC_BK45_67_H      _PK_H_(0x45, 0x67)
#define REG_SC_BK45_68_L      _PK_L_(0x45, 0x68)
#define REG_SC_BK45_68_H      _PK_H_(0x45, 0x68)
#define REG_SC_BK45_69_L      _PK_L_(0x45, 0x69)
#define REG_SC_BK45_69_H      _PK_H_(0x45, 0x69)
#define REG_SC_BK45_6A_L      _PK_L_(0x45, 0x6A)
#define REG_SC_BK45_6A_H      _PK_H_(0x45, 0x6A)
#define REG_SC_BK45_6B_L      _PK_L_(0x45, 0x6B)
#define REG_SC_BK45_6B_H      _PK_H_(0x45, 0x6B)
#define REG_SC_BK45_6C_L      _PK_L_(0x45, 0x6C)
#define REG_SC_BK45_6C_H      _PK_H_(0x45, 0x6C)
#define REG_SC_BK45_6D_L      _PK_L_(0x45, 0x6D)
#define REG_SC_BK45_6D_H      _PK_H_(0x45, 0x6D)
#define REG_SC_BK45_6E_L      _PK_L_(0x45, 0x6E)
#define REG_SC_BK45_6E_H      _PK_H_(0x45, 0x6E)
#define REG_SC_BK45_6F_L      _PK_L_(0x45, 0x6F)
#define REG_SC_BK45_6F_H      _PK_H_(0x45, 0x6F)
#define REG_SC_BK45_70_L      _PK_L_(0x45, 0x70)
#define REG_SC_BK45_70_H      _PK_H_(0x45, 0x70)
#define REG_SC_BK45_71_L      _PK_L_(0x45, 0x71)
#define REG_SC_BK45_71_H      _PK_H_(0x45, 0x71)
#define REG_SC_BK45_72_L      _PK_L_(0x45, 0x72)
#define REG_SC_BK45_72_H      _PK_H_(0x45, 0x72)
#define REG_SC_BK45_73_L      _PK_L_(0x45, 0x73)
#define REG_SC_BK45_73_H      _PK_H_(0x45, 0x73)
#define REG_SC_BK45_74_L      _PK_L_(0x45, 0x74)
#define REG_SC_BK45_74_H      _PK_H_(0x45, 0x74)
#define REG_SC_BK45_75_L      _PK_L_(0x45, 0x75)
#define REG_SC_BK45_75_H      _PK_H_(0x45, 0x75)
#define REG_SC_BK45_76_L      _PK_L_(0x45, 0x76)
#define REG_SC_BK45_76_H      _PK_H_(0x45, 0x76)
#define REG_SC_BK45_77_L      _PK_L_(0x45, 0x77)
#define REG_SC_BK45_77_H      _PK_H_(0x45, 0x77)
#define REG_SC_BK45_78_L      _PK_L_(0x45, 0x78)
#define REG_SC_BK45_78_H      _PK_H_(0x45, 0x78)
#define REG_SC_BK45_79_L      _PK_L_(0x45, 0x79)
#define REG_SC_BK45_79_H      _PK_H_(0x45, 0x79)
#define REG_SC_BK45_7A_L      _PK_L_(0x45, 0x7A)
#define REG_SC_BK45_7A_H      _PK_H_(0x45, 0x7A)
#define REG_SC_BK45_7B_L      _PK_L_(0x45, 0x7B)
#define REG_SC_BK45_7B_H      _PK_H_(0x45, 0x7B)
#define REG_SC_BK45_7C_L      _PK_L_(0x45, 0x7C)
#define REG_SC_BK45_7C_H      _PK_H_(0x45, 0x7C)
#define REG_SC_BK45_7D_L      _PK_L_(0x45, 0x7D)
#define REG_SC_BK45_7D_H      _PK_H_(0x45, 0x7D)
#define REG_SC_BK45_7E_L      _PK_L_(0x45, 0x7E)
#define REG_SC_BK45_7E_H      _PK_H_(0x45, 0x7E)
#define REG_SC_BK45_7F_L      _PK_L_(0x45, 0x7F)
#define REG_SC_BK45_7F_H      _PK_H_(0x45, 0x7F)

//----------------------------------------------
//  BK62: 2D TO 3D PIXEL
//----------------------------------------------
#define REG_SC_BK62_00_L      _PK_L_(0x62, 0x00)
#define REG_SC_BK62_00_H      _PK_H_(0x62, 0x00)
#define REG_SC_BK62_01_L      _PK_L_(0x62, 0x01)
#define REG_SC_BK62_01_H      _PK_H_(0x62, 0x01)
#define REG_SC_BK62_02_L      _PK_L_(0x62, 0x02)
#define REG_SC_BK62_02_H      _PK_H_(0x62, 0x02)
#define REG_SC_BK62_03_L      _PK_L_(0x62, 0x03)
#define REG_SC_BK62_03_H      _PK_H_(0x62, 0x03)
#define REG_SC_BK62_04_L      _PK_L_(0x62, 0x04)
#define REG_SC_BK62_04_H      _PK_H_(0x62, 0x04)
#define REG_SC_BK62_05_L      _PK_L_(0x62, 0x05)
#define REG_SC_BK62_05_H      _PK_H_(0x62, 0x05)
#define REG_SC_BK62_06_L      _PK_L_(0x62, 0x06)
#define REG_SC_BK62_06_H      _PK_H_(0x62, 0x06)
#define REG_SC_BK62_07_L      _PK_L_(0x62, 0x07)
#define REG_SC_BK62_07_H      _PK_H_(0x62, 0x07)
#define REG_SC_BK62_08_L      _PK_L_(0x62, 0x08)
#define REG_SC_BK62_08_H      _PK_H_(0x62, 0x08)
#define REG_SC_BK62_09_L      _PK_L_(0x62, 0x09)
#define REG_SC_BK62_09_H      _PK_H_(0x62, 0x09)
#define REG_SC_BK62_0A_L      _PK_L_(0x62, 0x0A)
#define REG_SC_BK62_0A_H      _PK_H_(0x62, 0x0A)
#define REG_SC_BK62_0B_L      _PK_L_(0x62, 0x0B)
#define REG_SC_BK62_0B_H      _PK_H_(0x62, 0x0B)
#define REG_SC_BK62_0C_L      _PK_L_(0x62, 0x0C)
#define REG_SC_BK62_0C_H      _PK_H_(0x62, 0x0C)
#define REG_SC_BK62_0D_L      _PK_L_(0x62, 0x0D)
#define REG_SC_BK62_0D_H      _PK_H_(0x62, 0x0D)
#define REG_SC_BK62_0E_L      _PK_L_(0x62, 0x0E)
#define REG_SC_BK62_0E_H      _PK_H_(0x62, 0x0E)
#define REG_SC_BK62_0F_L      _PK_L_(0x62, 0x0F)
#define REG_SC_BK62_0F_H      _PK_H_(0x62, 0x0F)
#define REG_SC_BK62_10_L      _PK_L_(0x62, 0x10)
#define REG_SC_BK62_10_H      _PK_H_(0x62, 0x10)
#define REG_SC_BK62_11_L      _PK_L_(0x62, 0x11)
#define REG_SC_BK62_11_H      _PK_H_(0x62, 0x11)
#define REG_SC_BK62_12_L      _PK_L_(0x62, 0x12)
#define REG_SC_BK62_12_H      _PK_H_(0x62, 0x12)
#define REG_SC_BK62_13_L      _PK_L_(0x62, 0x13)
#define REG_SC_BK62_13_H      _PK_H_(0x62, 0x13)
#define REG_SC_BK62_14_L      _PK_L_(0x62, 0x14)
#define REG_SC_BK62_14_H      _PK_H_(0x62, 0x14)
#define REG_SC_BK62_15_L      _PK_L_(0x62, 0x15)
#define REG_SC_BK62_15_H      _PK_H_(0x62, 0x15)
#define REG_SC_BK62_16_L      _PK_L_(0x62, 0x16)
#define REG_SC_BK62_16_H      _PK_H_(0x62, 0x16)
#define REG_SC_BK62_17_L      _PK_L_(0x62, 0x17)
#define REG_SC_BK62_17_H      _PK_H_(0x62, 0x17)
#define REG_SC_BK62_18_L      _PK_L_(0x62, 0x18)
#define REG_SC_BK62_18_H      _PK_H_(0x62, 0x18)
#define REG_SC_BK62_19_L      _PK_L_(0x62, 0x19)
#define REG_SC_BK62_19_H      _PK_H_(0x62, 0x19)
#define REG_SC_BK62_1A_L      _PK_L_(0x62, 0x1A)
#define REG_SC_BK62_1A_H      _PK_H_(0x62, 0x1A)
#define REG_SC_BK62_1B_L      _PK_L_(0x62, 0x1B)
#define REG_SC_BK62_1B_H      _PK_H_(0x62, 0x1B)
#define REG_SC_BK62_1C_L      _PK_L_(0x62, 0x1C)
#define REG_SC_BK62_1C_H      _PK_H_(0x62, 0x1C)
#define REG_SC_BK62_1D_L      _PK_L_(0x62, 0x1D)
#define REG_SC_BK62_1D_H      _PK_H_(0x62, 0x1D)
#define REG_SC_BK62_1E_L      _PK_L_(0x62, 0x1E)
#define REG_SC_BK62_1E_H      _PK_H_(0x62, 0x1E)
#define REG_SC_BK62_1F_L      _PK_L_(0x62, 0x1F)
#define REG_SC_BK62_1F_H      _PK_H_(0x62, 0x1F)
#define REG_SC_BK62_20_L      _PK_L_(0x62, 0x20)
#define REG_SC_BK62_20_H      _PK_H_(0x62, 0x20)
#define REG_SC_BK62_21_L      _PK_L_(0x62, 0x21)
#define REG_SC_BK62_21_H      _PK_H_(0x62, 0x21)
#define REG_SC_BK62_22_L      _PK_L_(0x62, 0x22)
#define REG_SC_BK62_22_H      _PK_H_(0x62, 0x22)
#define REG_SC_BK62_23_L      _PK_L_(0x62, 0x23)
#define REG_SC_BK62_23_H      _PK_H_(0x62, 0x23)
#define REG_SC_BK62_24_L      _PK_L_(0x62, 0x24)
#define REG_SC_BK62_24_H      _PK_H_(0x62, 0x24)
#define REG_SC_BK62_25_L      _PK_L_(0x62, 0x25)
#define REG_SC_BK62_25_H      _PK_H_(0x62, 0x25)
#define REG_SC_BK62_26_L      _PK_L_(0x62, 0x26)
#define REG_SC_BK62_26_H      _PK_H_(0x62, 0x26)
#define REG_SC_BK62_27_L      _PK_L_(0x62, 0x27)
#define REG_SC_BK62_27_H      _PK_H_(0x62, 0x27)
#define REG_SC_BK62_28_L      _PK_L_(0x62, 0x28)
#define REG_SC_BK62_28_H      _PK_H_(0x62, 0x28)
#define REG_SC_BK62_29_L      _PK_L_(0x62, 0x29)
#define REG_SC_BK62_29_H      _PK_H_(0x62, 0x29)
#define REG_SC_BK62_2A_L      _PK_L_(0x62, 0x2A)
#define REG_SC_BK62_2A_H      _PK_H_(0x62, 0x2A)
#define REG_SC_BK62_2B_L      _PK_L_(0x62, 0x2B)
#define REG_SC_BK62_2B_H      _PK_H_(0x62, 0x2B)
#define REG_SC_BK62_2C_L      _PK_L_(0x62, 0x2C)
#define REG_SC_BK62_2C_H      _PK_H_(0x62, 0x2C)
#define REG_SC_BK62_2D_L      _PK_L_(0x62, 0x2D)
#define REG_SC_BK62_2D_H      _PK_H_(0x62, 0x2D)
#define REG_SC_BK62_2E_L      _PK_L_(0x62, 0x2E)
#define REG_SC_BK62_2E_H      _PK_H_(0x62, 0x2E)
#define REG_SC_BK62_2F_L      _PK_L_(0x62, 0x2F)
#define REG_SC_BK62_2F_H      _PK_H_(0x62, 0x2F)
#define REG_SC_BK62_30_L      _PK_L_(0x62, 0x30)
#define REG_SC_BK62_30_H      _PK_H_(0x62, 0x30)
#define REG_SC_BK62_31_L      _PK_L_(0x62, 0x31)
#define REG_SC_BK62_31_H      _PK_H_(0x62, 0x31)
#define REG_SC_BK62_32_L      _PK_L_(0x62, 0x32)
#define REG_SC_BK62_32_H      _PK_H_(0x62, 0x32)
#define REG_SC_BK62_33_L      _PK_L_(0x62, 0x33)
#define REG_SC_BK62_33_H      _PK_H_(0x62, 0x33)
#define REG_SC_BK62_34_L      _PK_L_(0x62, 0x34)
#define REG_SC_BK62_34_H      _PK_H_(0x62, 0x34)
#define REG_SC_BK62_35_L      _PK_L_(0x62, 0x35)
#define REG_SC_BK62_35_H      _PK_H_(0x62, 0x35)
#define REG_SC_BK62_36_L      _PK_L_(0x62, 0x36)
#define REG_SC_BK62_36_H      _PK_H_(0x62, 0x36)
#define REG_SC_BK62_37_L      _PK_L_(0x62, 0x37)
#define REG_SC_BK62_37_H      _PK_H_(0x62, 0x37)
#define REG_SC_BK62_38_L      _PK_L_(0x62, 0x38)
#define REG_SC_BK62_38_H      _PK_H_(0x62, 0x38)
#define REG_SC_BK62_39_L      _PK_L_(0x62, 0x39)
#define REG_SC_BK62_39_H      _PK_H_(0x62, 0x39)
#define REG_SC_BK62_3A_L      _PK_L_(0x62, 0x3A)
#define REG_SC_BK62_3A_H      _PK_H_(0x62, 0x3A)
#define REG_SC_BK62_3B_L      _PK_L_(0x62, 0x3B)
#define REG_SC_BK62_3B_H      _PK_H_(0x62, 0x3B)
#define REG_SC_BK62_3C_L      _PK_L_(0x62, 0x3C)
#define REG_SC_BK62_3C_H      _PK_H_(0x62, 0x3C)
#define REG_SC_BK62_3D_L      _PK_L_(0x62, 0x3D)
#define REG_SC_BK62_3D_H      _PK_H_(0x62, 0x3D)
#define REG_SC_BK62_3E_L      _PK_L_(0x62, 0x3E)
#define REG_SC_BK62_3E_H      _PK_H_(0x62, 0x3E)
#define REG_SC_BK62_3F_L      _PK_L_(0x62, 0x3F)
#define REG_SC_BK62_3F_H      _PK_H_(0x62, 0x3F)
#define REG_SC_BK62_40_L      _PK_L_(0x62, 0x40)
#define REG_SC_BK62_40_H      _PK_H_(0x62, 0x40)
#define REG_SC_BK62_41_L      _PK_L_(0x62, 0x41)
#define REG_SC_BK62_41_H      _PK_H_(0x62, 0x41)
#define REG_SC_BK62_42_L      _PK_L_(0x62, 0x42)
#define REG_SC_BK62_42_H      _PK_H_(0x62, 0x42)
#define REG_SC_BK62_43_L      _PK_L_(0x62, 0x43)
#define REG_SC_BK62_43_H      _PK_H_(0x62, 0x43)
#define REG_SC_BK62_44_L      _PK_L_(0x62, 0x44)
#define REG_SC_BK62_44_H      _PK_H_(0x62, 0x44)
#define REG_SC_BK62_45_L      _PK_L_(0x62, 0x45)
#define REG_SC_BK62_45_H      _PK_H_(0x62, 0x45)
#define REG_SC_BK62_46_L      _PK_L_(0x62, 0x46)
#define REG_SC_BK62_46_H      _PK_H_(0x62, 0x46)
#define REG_SC_BK62_47_L      _PK_L_(0x62, 0x47)
#define REG_SC_BK62_47_H      _PK_H_(0x62, 0x47)
#define REG_SC_BK62_48_L      _PK_L_(0x62, 0x48)
#define REG_SC_BK62_48_H      _PK_H_(0x62, 0x48)
#define REG_SC_BK62_49_L      _PK_L_(0x62, 0x49)
#define REG_SC_BK62_49_H      _PK_H_(0x62, 0x49)
#define REG_SC_BK62_4A_L      _PK_L_(0x62, 0x4A)
#define REG_SC_BK62_4A_H      _PK_H_(0x62, 0x4A)
#define REG_SC_BK62_4B_L      _PK_L_(0x62, 0x4B)
#define REG_SC_BK62_4B_H      _PK_H_(0x62, 0x4B)
#define REG_SC_BK62_4C_L      _PK_L_(0x62, 0x4C)
#define REG_SC_BK62_4C_H      _PK_H_(0x62, 0x4C)
#define REG_SC_BK62_4D_L      _PK_L_(0x62, 0x4D)
#define REG_SC_BK62_4D_H      _PK_H_(0x62, 0x4D)
#define REG_SC_BK62_4E_L      _PK_L_(0x62, 0x4E)
#define REG_SC_BK62_4E_H      _PK_H_(0x62, 0x4E)
#define REG_SC_BK62_4F_L      _PK_L_(0x62, 0x4F)
#define REG_SC_BK62_4F_H      _PK_H_(0x62, 0x4F)
#define REG_SC_BK62_50_L      _PK_L_(0x62, 0x50)
#define REG_SC_BK62_50_H      _PK_H_(0x62, 0x50)
#define REG_SC_BK62_51_L      _PK_L_(0x62, 0x51)
#define REG_SC_BK62_51_H      _PK_H_(0x62, 0x51)
#define REG_SC_BK62_52_L      _PK_L_(0x62, 0x52)
#define REG_SC_BK62_52_H      _PK_H_(0x62, 0x52)
#define REG_SC_BK62_53_L      _PK_L_(0x62, 0x53)
#define REG_SC_BK62_53_H      _PK_H_(0x62, 0x53)
#define REG_SC_BK62_54_L      _PK_L_(0x62, 0x54)
#define REG_SC_BK62_54_H      _PK_H_(0x62, 0x54)
#define REG_SC_BK62_55_L      _PK_L_(0x62, 0x55)
#define REG_SC_BK62_55_H      _PK_H_(0x62, 0x55)
#define REG_SC_BK62_56_L      _PK_L_(0x62, 0x56)
#define REG_SC_BK62_56_H      _PK_H_(0x62, 0x56)
#define REG_SC_BK62_57_L      _PK_L_(0x62, 0x57)
#define REG_SC_BK62_57_H      _PK_H_(0x62, 0x57)
#define REG_SC_BK62_58_L      _PK_L_(0x62, 0x58)
#define REG_SC_BK62_58_H      _PK_H_(0x62, 0x58)
#define REG_SC_BK62_59_L      _PK_L_(0x62, 0x59)
#define REG_SC_BK62_59_H      _PK_H_(0x62, 0x59)
#define REG_SC_BK62_5A_L      _PK_L_(0x62, 0x5A)
#define REG_SC_BK62_5A_H      _PK_H_(0x62, 0x5A)
#define REG_SC_BK62_5B_L      _PK_L_(0x62, 0x5B)
#define REG_SC_BK62_5B_H      _PK_H_(0x62, 0x5B)
#define REG_SC_BK62_5C_L      _PK_L_(0x62, 0x5C)
#define REG_SC_BK62_5C_H      _PK_H_(0x62, 0x5C)
#define REG_SC_BK62_5D_L      _PK_L_(0x62, 0x5D)
#define REG_SC_BK62_5D_H      _PK_H_(0x62, 0x5D)
#define REG_SC_BK62_5E_L      _PK_L_(0x62, 0x5E)
#define REG_SC_BK62_5E_H      _PK_H_(0x62, 0x5E)
#define REG_SC_BK62_5F_L      _PK_L_(0x62, 0x5F)
#define REG_SC_BK62_5F_H      _PK_H_(0x62, 0x5F)
#define REG_SC_BK62_60_L      _PK_L_(0x62, 0x60)
#define REG_SC_BK62_60_H      _PK_H_(0x62, 0x60)
#define REG_SC_BK62_61_L      _PK_L_(0x62, 0x61)
#define REG_SC_BK62_61_H      _PK_H_(0x62, 0x61)
#define REG_SC_BK62_62_L      _PK_L_(0x62, 0x62)
#define REG_SC_BK62_62_H      _PK_H_(0x62, 0x62)
#define REG_SC_BK62_63_L      _PK_L_(0x62, 0x63)
#define REG_SC_BK62_63_H      _PK_H_(0x62, 0x63)
#define REG_SC_BK62_64_L      _PK_L_(0x62, 0x64)
#define REG_SC_BK62_64_H      _PK_H_(0x62, 0x64)
#define REG_SC_BK62_65_L      _PK_L_(0x62, 0x65)
#define REG_SC_BK62_65_H      _PK_H_(0x62, 0x65)
#define REG_SC_BK62_66_L      _PK_L_(0x62, 0x66)
#define REG_SC_BK62_66_H      _PK_H_(0x62, 0x66)
#define REG_SC_BK62_67_L      _PK_L_(0x62, 0x67)
#define REG_SC_BK62_67_H      _PK_H_(0x62, 0x67)
#define REG_SC_BK62_68_L      _PK_L_(0x62, 0x68)
#define REG_SC_BK62_68_H      _PK_H_(0x62, 0x68)
#define REG_SC_BK62_69_L      _PK_L_(0x62, 0x69)
#define REG_SC_BK62_69_H      _PK_H_(0x62, 0x69)
#define REG_SC_BK62_6A_L      _PK_L_(0x62, 0x6A)
#define REG_SC_BK62_6A_H      _PK_H_(0x62, 0x6A)
#define REG_SC_BK62_6B_L      _PK_L_(0x62, 0x6B)
#define REG_SC_BK62_6B_H      _PK_H_(0x62, 0x6B)
#define REG_SC_BK62_6C_L      _PK_L_(0x62, 0x6C)
#define REG_SC_BK62_6C_H      _PK_H_(0x62, 0x6C)
#define REG_SC_BK62_6D_L      _PK_L_(0x62, 0x6D)
#define REG_SC_BK62_6D_H      _PK_H_(0x62, 0x6D)
#define REG_SC_BK62_6E_L      _PK_L_(0x62, 0x6E)
#define REG_SC_BK62_6E_H      _PK_H_(0x62, 0x6E)
#define REG_SC_BK62_6F_L      _PK_L_(0x62, 0x6F)
#define REG_SC_BK62_6F_H      _PK_H_(0x62, 0x6F)
#define REG_SC_BK62_70_L      _PK_L_(0x62, 0x70)
#define REG_SC_BK62_70_H      _PK_H_(0x62, 0x70)
#define REG_SC_BK62_71_L      _PK_L_(0x62, 0x71)
#define REG_SC_BK62_71_H      _PK_H_(0x62, 0x71)
#define REG_SC_BK62_72_L      _PK_L_(0x62, 0x72)
#define REG_SC_BK62_72_H      _PK_H_(0x62, 0x72)
#define REG_SC_BK62_73_L      _PK_L_(0x62, 0x73)
#define REG_SC_BK62_73_H      _PK_H_(0x62, 0x73)
#define REG_SC_BK62_74_L      _PK_L_(0x62, 0x74)
#define REG_SC_BK62_74_H      _PK_H_(0x62, 0x74)
#define REG_SC_BK62_75_L      _PK_L_(0x62, 0x75)
#define REG_SC_BK62_75_H      _PK_H_(0x62, 0x75)
#define REG_SC_BK62_76_L      _PK_L_(0x62, 0x76)
#define REG_SC_BK62_76_H      _PK_H_(0x62, 0x76)
#define REG_SC_BK62_77_L      _PK_L_(0x62, 0x77)
#define REG_SC_BK62_77_H      _PK_H_(0x62, 0x77)
#define REG_SC_BK62_78_L      _PK_L_(0x62, 0x78)
#define REG_SC_BK62_78_H      _PK_H_(0x62, 0x78)
#define REG_SC_BK62_79_L      _PK_L_(0x62, 0x79)
#define REG_SC_BK62_79_H      _PK_H_(0x62, 0x79)
#define REG_SC_BK62_7A_L      _PK_L_(0x62, 0x7A)
#define REG_SC_BK62_7A_H      _PK_H_(0x62, 0x7A)
#define REG_SC_BK62_7B_L      _PK_L_(0x62, 0x7B)
#define REG_SC_BK62_7B_H      _PK_H_(0x62, 0x7B)
#define REG_SC_BK62_7C_L      _PK_L_(0x62, 0x7C)
#define REG_SC_BK62_7C_H      _PK_H_(0x62, 0x7C)
#define REG_SC_BK62_7D_L      _PK_L_(0x62, 0x7D)
#define REG_SC_BK62_7D_H      _PK_H_(0x62, 0x7D)
#define REG_SC_BK62_7E_L      _PK_L_(0x62, 0x7E)
#define REG_SC_BK62_7E_H      _PK_H_(0x62, 0x7E)
#define REG_SC_BK62_7F_L      _PK_L_(0x62, 0x7F)
#define REG_SC_BK62_7F_H      _PK_H_(0x62, 0x7F)

//----------------------------------------------
//  BK63: 2D TO 3D BLOCK
//----------------------------------------------
#define REG_SC_BK63_00_L      _PK_L_(0x63, 0x00)
#define REG_SC_BK63_00_H      _PK_H_(0x63, 0x00)
#define REG_SC_BK63_01_L      _PK_L_(0x63, 0x01)
#define REG_SC_BK63_01_H      _PK_H_(0x63, 0x01)
#define REG_SC_BK63_02_L      _PK_L_(0x63, 0x02)
#define REG_SC_BK63_02_H      _PK_H_(0x63, 0x02)
#define REG_SC_BK63_03_L      _PK_L_(0x63, 0x03)
#define REG_SC_BK63_03_H      _PK_H_(0x63, 0x03)
#define REG_SC_BK63_04_L      _PK_L_(0x63, 0x04)
#define REG_SC_BK63_04_H      _PK_H_(0x63, 0x04)
#define REG_SC_BK63_05_L      _PK_L_(0x63, 0x05)
#define REG_SC_BK63_05_H      _PK_H_(0x63, 0x05)
#define REG_SC_BK63_06_L      _PK_L_(0x63, 0x06)
#define REG_SC_BK63_06_H      _PK_H_(0x63, 0x06)
#define REG_SC_BK63_07_L      _PK_L_(0x63, 0x07)
#define REG_SC_BK63_07_H      _PK_H_(0x63, 0x07)
#define REG_SC_BK63_08_L      _PK_L_(0x63, 0x08)
#define REG_SC_BK63_08_H      _PK_H_(0x63, 0x08)
#define REG_SC_BK63_09_L      _PK_L_(0x63, 0x09)
#define REG_SC_BK63_09_H      _PK_H_(0x63, 0x09)
#define REG_SC_BK63_0A_L      _PK_L_(0x63, 0x0A)
#define REG_SC_BK63_0A_H      _PK_H_(0x63, 0x0A)
#define REG_SC_BK63_0B_L      _PK_L_(0x63, 0x0B)
#define REG_SC_BK63_0B_H      _PK_H_(0x63, 0x0B)
#define REG_SC_BK63_0C_L      _PK_L_(0x63, 0x0C)
#define REG_SC_BK63_0C_H      _PK_H_(0x63, 0x0C)
#define REG_SC_BK63_0D_L      _PK_L_(0x63, 0x0D)
#define REG_SC_BK63_0D_H      _PK_H_(0x63, 0x0D)
#define REG_SC_BK63_0E_L      _PK_L_(0x63, 0x0E)
#define REG_SC_BK63_0E_H      _PK_H_(0x63, 0x0E)
#define REG_SC_BK63_0F_L      _PK_L_(0x63, 0x0F)
#define REG_SC_BK63_0F_H      _PK_H_(0x63, 0x0F)
#define REG_SC_BK63_10_L      _PK_L_(0x63, 0x10)
#define REG_SC_BK63_10_H      _PK_H_(0x63, 0x10)
#define REG_SC_BK63_11_L      _PK_L_(0x63, 0x11)
#define REG_SC_BK63_11_H      _PK_H_(0x63, 0x11)
#define REG_SC_BK63_12_L      _PK_L_(0x63, 0x12)
#define REG_SC_BK63_12_H      _PK_H_(0x63, 0x12)
#define REG_SC_BK63_13_L      _PK_L_(0x63, 0x13)
#define REG_SC_BK63_13_H      _PK_H_(0x63, 0x13)
#define REG_SC_BK63_14_L      _PK_L_(0x63, 0x14)
#define REG_SC_BK63_14_H      _PK_H_(0x63, 0x14)
#define REG_SC_BK63_15_L      _PK_L_(0x63, 0x15)
#define REG_SC_BK63_15_H      _PK_H_(0x63, 0x15)
#define REG_SC_BK63_16_L      _PK_L_(0x63, 0x16)
#define REG_SC_BK63_16_H      _PK_H_(0x63, 0x16)
#define REG_SC_BK63_17_L      _PK_L_(0x63, 0x17)
#define REG_SC_BK63_17_H      _PK_H_(0x63, 0x17)
#define REG_SC_BK63_18_L      _PK_L_(0x63, 0x18)
#define REG_SC_BK63_18_H      _PK_H_(0x63, 0x18)
#define REG_SC_BK63_19_L      _PK_L_(0x63, 0x19)
#define REG_SC_BK63_19_H      _PK_H_(0x63, 0x19)
#define REG_SC_BK63_1A_L      _PK_L_(0x63, 0x1A)
#define REG_SC_BK63_1A_H      _PK_H_(0x63, 0x1A)
#define REG_SC_BK63_1B_L      _PK_L_(0x63, 0x1B)
#define REG_SC_BK63_1B_H      _PK_H_(0x63, 0x1B)
#define REG_SC_BK63_1C_L      _PK_L_(0x63, 0x1C)
#define REG_SC_BK63_1C_H      _PK_H_(0x63, 0x1C)
#define REG_SC_BK63_1D_L      _PK_L_(0x63, 0x1D)
#define REG_SC_BK63_1D_H      _PK_H_(0x63, 0x1D)
#define REG_SC_BK63_1E_L      _PK_L_(0x63, 0x1E)
#define REG_SC_BK63_1E_H      _PK_H_(0x63, 0x1E)
#define REG_SC_BK63_1F_L      _PK_L_(0x63, 0x1F)
#define REG_SC_BK63_1F_H      _PK_H_(0x63, 0x1F)
#define REG_SC_BK63_20_L      _PK_L_(0x63, 0x20)
#define REG_SC_BK63_20_H      _PK_H_(0x63, 0x20)
#define REG_SC_BK63_21_L      _PK_L_(0x63, 0x21)
#define REG_SC_BK63_21_H      _PK_H_(0x63, 0x21)
#define REG_SC_BK63_22_L      _PK_L_(0x63, 0x22)
#define REG_SC_BK63_22_H      _PK_H_(0x63, 0x22)
#define REG_SC_BK63_23_L      _PK_L_(0x63, 0x23)
#define REG_SC_BK63_23_H      _PK_H_(0x63, 0x23)
#define REG_SC_BK63_24_L      _PK_L_(0x63, 0x24)
#define REG_SC_BK63_24_H      _PK_H_(0x63, 0x24)
#define REG_SC_BK63_25_L      _PK_L_(0x63, 0x25)
#define REG_SC_BK63_25_H      _PK_H_(0x63, 0x25)
#define REG_SC_BK63_26_L      _PK_L_(0x63, 0x26)
#define REG_SC_BK63_26_H      _PK_H_(0x63, 0x26)
#define REG_SC_BK63_27_L      _PK_L_(0x63, 0x27)
#define REG_SC_BK63_27_H      _PK_H_(0x63, 0x27)
#define REG_SC_BK63_28_L      _PK_L_(0x63, 0x28)
#define REG_SC_BK63_28_H      _PK_H_(0x63, 0x28)
#define REG_SC_BK63_29_L      _PK_L_(0x63, 0x29)
#define REG_SC_BK63_29_H      _PK_H_(0x63, 0x29)
#define REG_SC_BK63_2A_L      _PK_L_(0x63, 0x2A)
#define REG_SC_BK63_2A_H      _PK_H_(0x63, 0x2A)
#define REG_SC_BK63_2B_L      _PK_L_(0x63, 0x2B)
#define REG_SC_BK63_2B_H      _PK_H_(0x63, 0x2B)
#define REG_SC_BK63_2C_L      _PK_L_(0x63, 0x2C)
#define REG_SC_BK63_2C_H      _PK_H_(0x63, 0x2C)
#define REG_SC_BK63_2D_L      _PK_L_(0x63, 0x2D)
#define REG_SC_BK63_2D_H      _PK_H_(0x63, 0x2D)
#define REG_SC_BK63_2E_L      _PK_L_(0x63, 0x2E)
#define REG_SC_BK63_2E_H      _PK_H_(0x63, 0x2E)
#define REG_SC_BK63_2F_L      _PK_L_(0x63, 0x2F)
#define REG_SC_BK63_2F_H      _PK_H_(0x63, 0x2F)
#define REG_SC_BK63_30_L      _PK_L_(0x63, 0x30)
#define REG_SC_BK63_30_H      _PK_H_(0x63, 0x30)
#define REG_SC_BK63_31_L      _PK_L_(0x63, 0x31)
#define REG_SC_BK63_31_H      _PK_H_(0x63, 0x31)
#define REG_SC_BK63_32_L      _PK_L_(0x63, 0x32)
#define REG_SC_BK63_32_H      _PK_H_(0x63, 0x32)
#define REG_SC_BK63_33_L      _PK_L_(0x63, 0x33)
#define REG_SC_BK63_33_H      _PK_H_(0x63, 0x33)
#define REG_SC_BK63_34_L      _PK_L_(0x63, 0x34)
#define REG_SC_BK63_34_H      _PK_H_(0x63, 0x34)
#define REG_SC_BK63_35_L      _PK_L_(0x63, 0x35)
#define REG_SC_BK63_35_H      _PK_H_(0x63, 0x35)
#define REG_SC_BK63_36_L      _PK_L_(0x63, 0x36)
#define REG_SC_BK63_36_H      _PK_H_(0x63, 0x36)
#define REG_SC_BK63_37_L      _PK_L_(0x63, 0x37)
#define REG_SC_BK63_37_H      _PK_H_(0x63, 0x37)
#define REG_SC_BK63_38_L      _PK_L_(0x63, 0x38)
#define REG_SC_BK63_38_H      _PK_H_(0x63, 0x38)
#define REG_SC_BK63_39_L      _PK_L_(0x63, 0x39)
#define REG_SC_BK63_39_H      _PK_H_(0x63, 0x39)
#define REG_SC_BK63_3A_L      _PK_L_(0x63, 0x3A)
#define REG_SC_BK63_3A_H      _PK_H_(0x63, 0x3A)
#define REG_SC_BK63_3B_L      _PK_L_(0x63, 0x3B)
#define REG_SC_BK63_3B_H      _PK_H_(0x63, 0x3B)
#define REG_SC_BK63_3C_L      _PK_L_(0x63, 0x3C)
#define REG_SC_BK63_3C_H      _PK_H_(0x63, 0x3C)
#define REG_SC_BK63_3D_L      _PK_L_(0x63, 0x3D)
#define REG_SC_BK63_3D_H      _PK_H_(0x63, 0x3D)
#define REG_SC_BK63_3E_L      _PK_L_(0x63, 0x3E)
#define REG_SC_BK63_3E_H      _PK_H_(0x63, 0x3E)
#define REG_SC_BK63_3F_L      _PK_L_(0x63, 0x3F)
#define REG_SC_BK63_3F_H      _PK_H_(0x63, 0x3F)
#define REG_SC_BK63_40_L      _PK_L_(0x63, 0x40)
#define REG_SC_BK63_40_H      _PK_H_(0x63, 0x40)
#define REG_SC_BK63_41_L      _PK_L_(0x63, 0x41)
#define REG_SC_BK63_41_H      _PK_H_(0x63, 0x41)
#define REG_SC_BK63_42_L      _PK_L_(0x63, 0x42)
#define REG_SC_BK63_42_H      _PK_H_(0x63, 0x42)
#define REG_SC_BK63_43_L      _PK_L_(0x63, 0x43)
#define REG_SC_BK63_43_H      _PK_H_(0x63, 0x43)
#define REG_SC_BK63_44_L      _PK_L_(0x63, 0x44)
#define REG_SC_BK63_44_H      _PK_H_(0x63, 0x44)
#define REG_SC_BK63_45_L      _PK_L_(0x63, 0x45)
#define REG_SC_BK63_45_H      _PK_H_(0x63, 0x45)
#define REG_SC_BK63_46_L      _PK_L_(0x63, 0x46)
#define REG_SC_BK63_46_H      _PK_H_(0x63, 0x46)
#define REG_SC_BK63_47_L      _PK_L_(0x63, 0x47)
#define REG_SC_BK63_47_H      _PK_H_(0x63, 0x47)
#define REG_SC_BK63_48_L      _PK_L_(0x63, 0x48)
#define REG_SC_BK63_48_H      _PK_H_(0x63, 0x48)
#define REG_SC_BK63_49_L      _PK_L_(0x63, 0x49)
#define REG_SC_BK63_49_H      _PK_H_(0x63, 0x49)
#define REG_SC_BK63_4A_L      _PK_L_(0x63, 0x4A)
#define REG_SC_BK63_4A_H      _PK_H_(0x63, 0x4A)
#define REG_SC_BK63_4B_L      _PK_L_(0x63, 0x4B)
#define REG_SC_BK63_4B_H      _PK_H_(0x63, 0x4B)
#define REG_SC_BK63_4C_L      _PK_L_(0x63, 0x4C)
#define REG_SC_BK63_4C_H      _PK_H_(0x63, 0x4C)
#define REG_SC_BK63_4D_L      _PK_L_(0x63, 0x4D)
#define REG_SC_BK63_4D_H      _PK_H_(0x63, 0x4D)
#define REG_SC_BK63_4E_L      _PK_L_(0x63, 0x4E)
#define REG_SC_BK63_4E_H      _PK_H_(0x63, 0x4E)
#define REG_SC_BK63_4F_L      _PK_L_(0x63, 0x4F)
#define REG_SC_BK63_4F_H      _PK_H_(0x63, 0x4F)
#define REG_SC_BK63_50_L      _PK_L_(0x63, 0x50)
#define REG_SC_BK63_50_H      _PK_H_(0x63, 0x50)
#define REG_SC_BK63_51_L      _PK_L_(0x63, 0x51)
#define REG_SC_BK63_51_H      _PK_H_(0x63, 0x51)
#define REG_SC_BK63_52_L      _PK_L_(0x63, 0x52)
#define REG_SC_BK63_52_H      _PK_H_(0x63, 0x52)
#define REG_SC_BK63_53_L      _PK_L_(0x63, 0x53)
#define REG_SC_BK63_53_H      _PK_H_(0x63, 0x53)
#define REG_SC_BK63_54_L      _PK_L_(0x63, 0x54)
#define REG_SC_BK63_54_H      _PK_H_(0x63, 0x54)
#define REG_SC_BK63_55_L      _PK_L_(0x63, 0x55)
#define REG_SC_BK63_55_H      _PK_H_(0x63, 0x55)
#define REG_SC_BK63_56_L      _PK_L_(0x63, 0x56)
#define REG_SC_BK63_56_H      _PK_H_(0x63, 0x56)
#define REG_SC_BK63_57_L      _PK_L_(0x63, 0x57)
#define REG_SC_BK63_57_H      _PK_H_(0x63, 0x57)
#define REG_SC_BK63_58_L      _PK_L_(0x63, 0x58)
#define REG_SC_BK63_58_H      _PK_H_(0x63, 0x58)
#define REG_SC_BK63_59_L      _PK_L_(0x63, 0x59)
#define REG_SC_BK63_59_H      _PK_H_(0x63, 0x59)
#define REG_SC_BK63_5A_L      _PK_L_(0x63, 0x5A)
#define REG_SC_BK63_5A_H      _PK_H_(0x63, 0x5A)
#define REG_SC_BK63_5B_L      _PK_L_(0x63, 0x5B)
#define REG_SC_BK63_5B_H      _PK_H_(0x63, 0x5B)
#define REG_SC_BK63_5C_L      _PK_L_(0x63, 0x5C)
#define REG_SC_BK63_5C_H      _PK_H_(0x63, 0x5C)
#define REG_SC_BK63_5D_L      _PK_L_(0x63, 0x5D)
#define REG_SC_BK63_5D_H      _PK_H_(0x63, 0x5D)
#define REG_SC_BK63_5E_L      _PK_L_(0x63, 0x5E)
#define REG_SC_BK63_5E_H      _PK_H_(0x63, 0x5E)
#define REG_SC_BK63_5F_L      _PK_L_(0x63, 0x5F)
#define REG_SC_BK63_5F_H      _PK_H_(0x63, 0x5F)
#define REG_SC_BK63_60_L      _PK_L_(0x63, 0x60)
#define REG_SC_BK63_60_H      _PK_H_(0x63, 0x60)
#define REG_SC_BK63_61_L      _PK_L_(0x63, 0x61)
#define REG_SC_BK63_61_H      _PK_H_(0x63, 0x61)
#define REG_SC_BK63_62_L      _PK_L_(0x63, 0x62)
#define REG_SC_BK63_62_H      _PK_H_(0x63, 0x62)
#define REG_SC_BK63_63_L      _PK_L_(0x63, 0x63)
#define REG_SC_BK63_63_H      _PK_H_(0x63, 0x63)
#define REG_SC_BK63_64_L      _PK_L_(0x63, 0x64)
#define REG_SC_BK63_64_H      _PK_H_(0x63, 0x64)
#define REG_SC_BK63_65_L      _PK_L_(0x63, 0x65)
#define REG_SC_BK63_65_H      _PK_H_(0x63, 0x65)
#define REG_SC_BK63_66_L      _PK_L_(0x63, 0x66)
#define REG_SC_BK63_66_H      _PK_H_(0x63, 0x66)
#define REG_SC_BK63_67_L      _PK_L_(0x63, 0x67)
#define REG_SC_BK63_67_H      _PK_H_(0x63, 0x67)
#define REG_SC_BK63_68_L      _PK_L_(0x63, 0x68)
#define REG_SC_BK63_68_H      _PK_H_(0x63, 0x68)
#define REG_SC_BK63_69_L      _PK_L_(0x63, 0x69)
#define REG_SC_BK63_69_H      _PK_H_(0x63, 0x69)
#define REG_SC_BK63_6A_L      _PK_L_(0x63, 0x6A)
#define REG_SC_BK63_6A_H      _PK_H_(0x63, 0x6A)
#define REG_SC_BK63_6B_L      _PK_L_(0x63, 0x6B)
#define REG_SC_BK63_6B_H      _PK_H_(0x63, 0x6B)
#define REG_SC_BK63_6C_L      _PK_L_(0x63, 0x6C)
#define REG_SC_BK63_6C_H      _PK_H_(0x63, 0x6C)
#define REG_SC_BK63_6D_L      _PK_L_(0x63, 0x6D)
#define REG_SC_BK63_6D_H      _PK_H_(0x63, 0x6D)
#define REG_SC_BK63_6E_L      _PK_L_(0x63, 0x6E)
#define REG_SC_BK63_6E_H      _PK_H_(0x63, 0x6E)
#define REG_SC_BK63_6F_L      _PK_L_(0x63, 0x6F)
#define REG_SC_BK63_6F_H      _PK_H_(0x63, 0x6F)
#define REG_SC_BK63_70_L      _PK_L_(0x63, 0x70)
#define REG_SC_BK63_70_H      _PK_H_(0x63, 0x70)
#define REG_SC_BK63_71_L      _PK_L_(0x63, 0x71)
#define REG_SC_BK63_71_H      _PK_H_(0x63, 0x71)
#define REG_SC_BK63_72_L      _PK_L_(0x63, 0x72)
#define REG_SC_BK63_72_H      _PK_H_(0x63, 0x72)
#define REG_SC_BK63_73_L      _PK_L_(0x63, 0x73)
#define REG_SC_BK63_73_H      _PK_H_(0x63, 0x73)
#define REG_SC_BK63_74_L      _PK_L_(0x63, 0x74)
#define REG_SC_BK63_74_H      _PK_H_(0x63, 0x74)
#define REG_SC_BK63_75_L      _PK_L_(0x63, 0x75)
#define REG_SC_BK63_75_H      _PK_H_(0x63, 0x75)
#define REG_SC_BK63_76_L      _PK_L_(0x63, 0x76)
#define REG_SC_BK63_76_H      _PK_H_(0x63, 0x76)
#define REG_SC_BK63_77_L      _PK_L_(0x63, 0x77)
#define REG_SC_BK63_77_H      _PK_H_(0x63, 0x77)
#define REG_SC_BK63_78_L      _PK_L_(0x63, 0x78)
#define REG_SC_BK63_78_H      _PK_H_(0x63, 0x78)
#define REG_SC_BK63_79_L      _PK_L_(0x63, 0x79)
#define REG_SC_BK63_79_H      _PK_H_(0x63, 0x79)
#define REG_SC_BK63_7A_L      _PK_L_(0x63, 0x7A)
#define REG_SC_BK63_7A_H      _PK_H_(0x63, 0x7A)
#define REG_SC_BK63_7B_L      _PK_L_(0x63, 0x7B)
#define REG_SC_BK63_7B_H      _PK_H_(0x63, 0x7B)
#define REG_SC_BK63_7C_L      _PK_L_(0x63, 0x7C)
#define REG_SC_BK63_7C_H      _PK_H_(0x63, 0x7C)
#define REG_SC_BK63_7D_L      _PK_L_(0x63, 0x7D)
#define REG_SC_BK63_7D_H      _PK_H_(0x63, 0x7D)
#define REG_SC_BK63_7E_L      _PK_L_(0x63, 0x7E)
#define REG_SC_BK63_7E_H      _PK_H_(0x63, 0x7E)
#define REG_SC_BK63_7F_L      _PK_L_(0x63, 0x7F)
#define REG_SC_BK63_7F_H      _PK_H_(0x63, 0x7F)
#define REG_SC_BK68_20_L      _PK_L_(0x68, 0x20)
#define REG_SC_BK68_20_H      _PK_H_(0x68, 0x20)
#define REG_SC_BK68_28_L      _PK_L_(0x68, 0x28)
#define REG_SC_BK68_28_H      _PK_H_(0x68, 0x28)
#define REG_SC_BK68_2F_L      _PK_L_(0x68, 0x2F)
#define REG_SC_BK68_2F_H      _PK_H_(0x68, 0x2F)
#define REG_SC_BK68_50_L      _PK_L_(0x68, 0x50)
#define REG_SC_BK68_50_H      _PK_H_(0x68, 0x50)
#define REG_SC_BK68_31_L      _PK_L_(0x68, 0x31)
#define REG_SC_BK68_31_H      _PK_H_(0x68, 0x31)
#define REG_SC_BK68_32_L      _PK_L_(0x68, 0x32)
#define REG_SC_BK68_32_H      _PK_H_(0x68, 0x32)
#define REG_SC_BK68_33_L      _PK_L_(0x68, 0x33)
#define REG_SC_BK68_33_H      _PK_H_(0x68, 0x33)
#define REG_SC_BK68_37_L      _PK_L_(0x68, 0x37)
#define REG_SC_BK68_37_H      _PK_H_(0x68, 0x37)
#define REG_SC_BK68_38_L      _PK_L_(0x68, 0x38)
#define REG_SC_BK68_38_H      _PK_H_(0x68, 0x38)
#define REG_SC_BK68_36_L      _PK_L_(0x68, 0x36)
#define REG_SC_BK68_36_H      _PK_H_(0x68, 0x36)
#define REG_SC_BK68_51_L      _PK_L_(0x68, 0x51)
#define REG_SC_BK68_51_H      _PK_H_(0x68, 0x51)
#define REG_SC_BK68_52_L      _PK_L_(0x68, 0x52)
#define REG_SC_BK68_52_H      _PK_H_(0x68, 0x52)

// BK77
#define REG_SC_BK77_26_L      _PK_L_(0x77, 0x26)
#define REG_SC_BK77_26_H      _PK_H_(0x77, 0x26)

// BKC9
#define REG_SC_BKC9_65_L      _PK_L_(0xC9, 0x65)
#define REG_SC_BKC9_65_H      _PK_H_(0xC9, 0x65)

// BKCE
#define REG_SC_BKCE_01_L      _PK_L_(0xCE, 0x01)
#define REG_SC_BKCE_01_H      _PK_H_(0xCE, 0x01)
#define REG_SC_BKCE_37_L      _PK_L_(0xCE, 0x37)
#define REG_SC_BKCE_37_H      _PK_H_(0xCE, 0x37)

//----------------------------------------------
//  MOD
//----------------------------------------------

#define REG_MOD_BK00_00_L      _PK_L_(0x00, 0x00)
#define REG_MOD_BK00_00_H      _PK_H_(0x00, 0x00)
#define REG_MOD_BK00_01_L      _PK_L_(0x00, 0x01)
#define REG_MOD_BK00_01_H      _PK_H_(0x00, 0x01)
#define REG_MOD_BK00_02_L      _PK_L_(0x00, 0x02)
#define REG_MOD_BK00_02_H      _PK_H_(0x00, 0x02)
#define REG_MOD_BK00_03_L      _PK_L_(0x00, 0x03)
#define REG_MOD_BK00_03_H      _PK_H_(0x00, 0x03)
#define REG_MOD_BK00_04_L      _PK_L_(0x00, 0x04)
#define REG_MOD_BK00_04_H      _PK_H_(0x00, 0x04)
#define REG_MOD_BK00_05_L      _PK_L_(0x00, 0x05)
#define REG_MOD_BK00_05_H      _PK_H_(0x00, 0x05)
#define REG_MOD_BK00_06_L      _PK_L_(0x00, 0x06)
#define REG_MOD_BK00_06_H      _PK_H_(0x00, 0x06)
#define REG_MOD_BK00_07_L      _PK_L_(0x00, 0x07)
#define REG_MOD_BK00_07_H      _PK_H_(0x00, 0x07)
#define REG_MOD_BK00_08_L      _PK_L_(0x00, 0x08)
#define REG_MOD_BK00_08_H      _PK_H_(0x00, 0x08)
#define REG_MOD_BK00_09_L      _PK_L_(0x00, 0x09)
#define REG_MOD_BK00_09_H      _PK_H_(0x00, 0x09)
#define REG_MOD_BK00_0A_L      _PK_L_(0x00, 0x0A)
#define REG_MOD_BK00_0A_H      _PK_H_(0x00, 0x0A)
#define REG_MOD_BK00_0B_L      _PK_L_(0x00, 0x0B)
#define REG_MOD_BK00_0B_H      _PK_H_(0x00, 0x0B)
#define REG_MOD_BK00_0C_L      _PK_L_(0x00, 0x0C)
#define REG_MOD_BK00_0C_H      _PK_H_(0x00, 0x0C)
#define REG_MOD_BK00_0D_L      _PK_L_(0x00, 0x0D)
#define REG_MOD_BK00_0D_H      _PK_H_(0x00, 0x0D)
#define REG_MOD_BK00_0E_L      _PK_L_(0x00, 0x0E)
#define REG_MOD_BK00_0E_H      _PK_H_(0x00, 0x0E)
#define REG_MOD_BK00_0F_L      _PK_L_(0x00, 0x0F)
#define REG_MOD_BK00_0F_H      _PK_H_(0x00, 0x0F)
#define REG_MOD_BK00_10_L      _PK_L_(0x00, 0x10)
#define REG_MOD_BK00_10_H      _PK_H_(0x00, 0x10)
#define REG_MOD_BK00_11_L      _PK_L_(0x00, 0x11)
#define REG_MOD_BK00_11_H      _PK_H_(0x00, 0x11)
#define REG_MOD_BK00_12_L      _PK_L_(0x00, 0x12)
#define REG_MOD_BK00_12_H      _PK_H_(0x00, 0x12)
#define REG_MOD_BK00_13_L      _PK_L_(0x00, 0x13)
#define REG_MOD_BK00_13_H      _PK_H_(0x00, 0x13)
#define REG_MOD_BK00_14_L      _PK_L_(0x00, 0x14)
#define REG_MOD_BK00_14_H      _PK_H_(0x00, 0x14)
#define REG_MOD_BK00_15_L      _PK_L_(0x00, 0x15)
#define REG_MOD_BK00_15_H      _PK_H_(0x00, 0x15)
#define REG_MOD_BK00_16_L      _PK_L_(0x00, 0x16)
#define REG_MOD_BK00_16_H      _PK_H_(0x00, 0x16)
#define REG_MOD_BK00_17_L      _PK_L_(0x00, 0x17)
#define REG_MOD_BK00_17_H      _PK_H_(0x00, 0x17)
#define REG_MOD_BK00_18_L      _PK_L_(0x00, 0x18)
#define REG_MOD_BK00_18_H      _PK_H_(0x00, 0x18)
#define REG_MOD_BK00_19_L      _PK_L_(0x00, 0x19)
#define REG_MOD_BK00_19_H      _PK_H_(0x00, 0x19)
#define REG_MOD_BK00_1A_L      _PK_L_(0x00, 0x1A)
#define REG_MOD_BK00_1A_H      _PK_H_(0x00, 0x1A)
#define REG_MOD_BK00_1B_L      _PK_L_(0x00, 0x1B)
#define REG_MOD_BK00_1B_H      _PK_H_(0x00, 0x1B)
#define REG_MOD_BK00_1C_L      _PK_L_(0x00, 0x1C)
#define REG_MOD_BK00_1C_H      _PK_H_(0x00, 0x1C)
#define REG_MOD_BK00_1D_L      _PK_L_(0x00, 0x1D)
#define REG_MOD_BK00_1D_H      _PK_H_(0x00, 0x1D)
#define REG_MOD_BK00_1E_L      _PK_L_(0x00, 0x1E)
#define REG_MOD_BK00_1E_H      _PK_H_(0x00, 0x1E)
#define REG_MOD_BK00_1F_L      _PK_L_(0x00, 0x1F)
#define REG_MOD_BK00_1F_H      _PK_H_(0x00, 0x1F)
#define REG_MOD_BK00_20_L      _PK_L_(0x00, 0x20)
#define REG_MOD_BK00_20_H      _PK_H_(0x00, 0x20)
#define REG_MOD_BK00_21_L      _PK_L_(0x00, 0x21)
#define REG_MOD_BK00_21_H      _PK_H_(0x00, 0x21)
#define REG_MOD_BK00_22_L      _PK_L_(0x00, 0x22)
#define REG_MOD_BK00_22_H      _PK_H_(0x00, 0x22)
#define REG_MOD_BK00_23_L      _PK_L_(0x00, 0x23)
#define REG_MOD_BK00_23_H      _PK_H_(0x00, 0x23)
#define REG_MOD_BK00_24_L      _PK_L_(0x00, 0x24)
#define REG_MOD_BK00_24_H      _PK_H_(0x00, 0x24)
#define REG_MOD_BK00_25_L      _PK_L_(0x00, 0x25)
#define REG_MOD_BK00_25_H      _PK_H_(0x00, 0x25)
#define REG_MOD_BK00_26_L      _PK_L_(0x00, 0x26)
#define REG_MOD_BK00_26_H      _PK_H_(0x00, 0x26)
#define REG_MOD_BK00_27_L      _PK_L_(0x00, 0x27)
#define REG_MOD_BK00_27_H      _PK_H_(0x00, 0x27)
#define REG_MOD_BK00_28_L      _PK_L_(0x00, 0x28)
#define REG_MOD_BK00_28_H      _PK_H_(0x00, 0x28)
#define REG_MOD_BK00_29_L      _PK_L_(0x00, 0x29)
#define REG_MOD_BK00_29_H      _PK_H_(0x00, 0x29)
#define REG_MOD_BK00_2A_L      _PK_L_(0x00, 0x2A)
#define REG_MOD_BK00_2A_H      _PK_H_(0x00, 0x2A)
#define REG_MOD_BK00_2B_L      _PK_L_(0x00, 0x2B)
#define REG_MOD_BK00_2B_H      _PK_H_(0x00, 0x2B)
#define REG_MOD_BK00_2C_L      _PK_L_(0x00, 0x2C)
#define REG_MOD_BK00_2C_H      _PK_H_(0x00, 0x2C)
#define REG_MOD_BK00_2D_L      _PK_L_(0x00, 0x2D)
#define REG_MOD_BK00_2D_H      _PK_H_(0x00, 0x2D)
#define REG_MOD_BK00_2E_L      _PK_L_(0x00, 0x2E)
#define REG_MOD_BK00_2E_H      _PK_H_(0x00, 0x2E)
#define REG_MOD_BK00_2F_L      _PK_L_(0x00, 0x2F)
#define REG_MOD_BK00_2F_H      _PK_H_(0x00, 0x2F)
#define REG_MOD_BK00_30_L      _PK_L_(0x00, 0x30)
#define REG_MOD_BK00_30_H      _PK_H_(0x00, 0x30)
#define REG_MOD_BK00_31_L      _PK_L_(0x00, 0x31)
#define REG_MOD_BK00_31_H      _PK_H_(0x00, 0x31)
#define REG_MOD_BK00_32_L      _PK_L_(0x00, 0x32)
#define REG_MOD_BK00_32_H      _PK_H_(0x00, 0x32)
#define REG_MOD_BK00_33_L      _PK_L_(0x00, 0x33)
#define REG_MOD_BK00_33_H      _PK_H_(0x00, 0x33)
#define REG_MOD_BK00_34_L      _PK_L_(0x00, 0x34)
#define REG_MOD_BK00_34_H      _PK_H_(0x00, 0x34)
#define REG_MOD_BK00_35_L      _PK_L_(0x00, 0x35)
#define REG_MOD_BK00_35_H      _PK_H_(0x00, 0x35)
#define REG_MOD_BK00_36_L      _PK_L_(0x00, 0x36)
#define REG_MOD_BK00_36_H      _PK_H_(0x00, 0x36)
#define REG_MOD_BK00_37_L      _PK_L_(0x00, 0x37)
#define REG_MOD_BK00_37_H      _PK_H_(0x00, 0x37)
#define REG_MOD_BK00_38_L      _PK_L_(0x00, 0x38)
#define REG_MOD_BK00_38_H      _PK_H_(0x00, 0x38)
#define REG_MOD_BK00_39_L      _PK_L_(0x00, 0x39)
#define REG_MOD_BK00_39_H      _PK_H_(0x00, 0x39)
#define REG_MOD_BK00_3A_L      _PK_L_(0x00, 0x3A)
#define REG_MOD_BK00_3A_H      _PK_H_(0x00, 0x3A)
#define REG_MOD_BK00_3B_L      _PK_L_(0x00, 0x3B)
#define REG_MOD_BK00_3B_H      _PK_H_(0x00, 0x3B)
#define REG_MOD_BK00_3C_L      _PK_L_(0x00, 0x3C)
#define REG_MOD_BK00_3C_H      _PK_H_(0x00, 0x3C)
#define REG_MOD_BK00_3D_L      _PK_L_(0x00, 0x3D)
#define REG_MOD_BK00_3D_H      _PK_H_(0x00, 0x3D)
#define REG_MOD_BK00_3E_L      _PK_L_(0x00, 0x3E)
#define REG_MOD_BK00_3E_H      _PK_H_(0x00, 0x3E)
#define REG_MOD_BK00_3F_L      _PK_L_(0x00, 0x3F)
#define REG_MOD_BK00_3F_H      _PK_H_(0x00, 0x3F)
#define REG_MOD_BK00_40_L      _PK_L_(0x00, 0x40)
#define REG_MOD_BK00_40_H      _PK_H_(0x00, 0x40)
#define REG_MOD_BK00_41_L      _PK_L_(0x00, 0x41)
#define REG_MOD_BK00_41_H      _PK_H_(0x00, 0x41)
#define REG_MOD_BK00_42_L      _PK_L_(0x00, 0x42)
#define REG_MOD_BK00_42_H      _PK_H_(0x00, 0x42)
#define REG_MOD_BK00_43_L      _PK_L_(0x00, 0x43)
#define REG_MOD_BK00_43_H      _PK_H_(0x00, 0x43)
#define REG_MOD_BK00_44_L      _PK_L_(0x00, 0x44)
#define REG_MOD_BK00_44_H      _PK_H_(0x00, 0x44)
#define REG_MOD_BK00_45_L      _PK_L_(0x00, 0x45)
#define REG_MOD_BK00_45_H      _PK_H_(0x00, 0x45)
#define REG_MOD_BK00_46_L      _PK_L_(0x00, 0x46)
#define REG_MOD_BK00_46_H      _PK_H_(0x00, 0x46)
#define REG_MOD_BK00_47_L      _PK_L_(0x00, 0x47)
#define REG_MOD_BK00_47_H      _PK_H_(0x00, 0x47)
#define REG_MOD_BK00_48_L      _PK_L_(0x00, 0x48)
#define REG_MOD_BK00_48_H      _PK_H_(0x00, 0x48)
#define REG_MOD_BK00_49_L      _PK_L_(0x00, 0x49)
#define REG_MOD_BK00_49_H      _PK_H_(0x00, 0x49)
#define REG_MOD_BK00_4A_L      _PK_L_(0x00, 0x4A)
#define REG_MOD_BK00_4A_H      _PK_H_(0x00, 0x4A)
#define REG_MOD_BK00_4B_L      _PK_L_(0x00, 0x4B)
#define REG_MOD_BK00_4B_H      _PK_H_(0x00, 0x4B)
#define REG_MOD_BK00_4C_L      _PK_L_(0x00, 0x4C)
#define REG_MOD_BK00_4C_H      _PK_H_(0x00, 0x4C)
#define REG_MOD_BK00_4D_L      _PK_L_(0x00, 0x4D)
#define REG_MOD_BK00_4D_H      _PK_H_(0x00, 0x4D)
#define REG_MOD_BK00_4E_L      _PK_L_(0x00, 0x4E)
#define REG_MOD_BK00_4E_H      _PK_H_(0x00, 0x4E)
#define REG_MOD_BK00_4F_L      _PK_L_(0x00, 0x4F)
#define REG_MOD_BK00_4F_H      _PK_H_(0x00, 0x4F)
#define REG_MOD_BK00_50_L      _PK_L_(0x00, 0x50)
#define REG_MOD_BK00_50_H      _PK_H_(0x00, 0x50)
#define REG_MOD_BK00_51_L      _PK_L_(0x00, 0x51)
#define REG_MOD_BK00_51_H      _PK_H_(0x00, 0x51)
#define REG_MOD_BK00_52_L      _PK_L_(0x00, 0x52)
#define REG_MOD_BK00_52_H      _PK_H_(0x00, 0x52)
#define REG_MOD_BK00_53_L      _PK_L_(0x00, 0x53)
#define REG_MOD_BK00_53_H      _PK_H_(0x00, 0x53)
#define REG_MOD_BK00_54_L      _PK_L_(0x00, 0x54)
#define REG_MOD_BK00_54_H      _PK_H_(0x00, 0x54)
#define REG_MOD_BK00_55_L      _PK_L_(0x00, 0x55)
#define REG_MOD_BK00_55_H      _PK_H_(0x00, 0x55)
#define REG_MOD_BK00_56_L      _PK_L_(0x00, 0x56)
#define REG_MOD_BK00_56_H      _PK_H_(0x00, 0x56)
#define REG_MOD_BK00_57_L      _PK_L_(0x00, 0x57)
#define REG_MOD_BK00_57_H      _PK_H_(0x00, 0x57)
#define REG_MOD_BK00_58_L      _PK_L_(0x00, 0x58)
#define REG_MOD_BK00_58_H      _PK_H_(0x00, 0x58)
#define REG_MOD_BK00_59_L      _PK_L_(0x00, 0x59)
#define REG_MOD_BK00_59_H      _PK_H_(0x00, 0x59)
#define REG_MOD_BK00_5A_L      _PK_L_(0x00, 0x5A)
#define REG_MOD_BK00_5A_H      _PK_H_(0x00, 0x5A)
#define REG_MOD_BK00_5B_L      _PK_L_(0x00, 0x5B)
#define REG_MOD_BK00_5B_H      _PK_H_(0x00, 0x5B)
#define REG_MOD_BK00_5C_L      _PK_L_(0x00, 0x5C)
#define REG_MOD_BK00_5C_H      _PK_H_(0x00, 0x5C)
#define REG_MOD_BK00_5D_L      _PK_L_(0x00, 0x5D)
#define REG_MOD_BK00_5D_H      _PK_H_(0x00, 0x5D)
#define REG_MOD_BK00_5E_L      _PK_L_(0x00, 0x5E)
#define REG_MOD_BK00_5E_H      _PK_H_(0x00, 0x5E)
#define REG_MOD_BK00_5F_L      _PK_L_(0x00, 0x5F)
#define REG_MOD_BK00_5F_H      _PK_H_(0x00, 0x5F)
#define REG_MOD_BK00_60_L      _PK_L_(0x00, 0x60)
#define REG_MOD_BK00_60_H      _PK_H_(0x00, 0x60)
#define REG_MOD_BK00_61_L      _PK_L_(0x00, 0x61)
#define REG_MOD_BK00_61_H      _PK_H_(0x00, 0x61)
#define REG_MOD_BK00_62_L      _PK_L_(0x00, 0x62)
#define REG_MOD_BK00_62_H      _PK_H_(0x00, 0x62)
#define REG_MOD_BK00_63_L      _PK_L_(0x00, 0x63)
#define REG_MOD_BK00_63_H      _PK_H_(0x00, 0x63)
#define REG_MOD_BK00_64_L      _PK_L_(0x00, 0x64)
#define REG_MOD_BK00_64_H      _PK_H_(0x00, 0x64)
#define REG_MOD_BK00_65_L      _PK_L_(0x00, 0x65)
#define REG_MOD_BK00_65_H      _PK_H_(0x00, 0x65)
#define REG_MOD_BK00_66_L      _PK_L_(0x00, 0x66)
#define REG_MOD_BK00_66_H      _PK_H_(0x00, 0x66)
#define REG_MOD_BK00_67_L      _PK_L_(0x00, 0x67)
#define REG_MOD_BK00_67_H      _PK_H_(0x00, 0x67)
#define REG_MOD_BK00_68_L      _PK_L_(0x00, 0x68)
#define REG_MOD_BK00_68_H      _PK_H_(0x00, 0x68)
#define REG_MOD_BK00_69_L      _PK_L_(0x00, 0x69)
#define REG_MOD_BK00_69_H      _PK_H_(0x00, 0x69)
#define REG_MOD_BK00_6A_L      _PK_L_(0x00, 0x6A)
#define REG_MOD_BK00_6A_H      _PK_H_(0x00, 0x6A)
#define REG_MOD_BK00_6B_L      _PK_L_(0x00, 0x6B)
#define REG_MOD_BK00_6B_H      _PK_H_(0x00, 0x6B)
#define REG_MOD_BK00_6C_L      _PK_L_(0x00, 0x6C)
#define REG_MOD_BK00_6C_H      _PK_H_(0x00, 0x6C)
#define REG_MOD_BK00_6D_L      _PK_L_(0x00, 0x6D)
#define REG_MOD_BK00_6D_H      _PK_H_(0x00, 0x6D)
#define REG_MOD_BK00_6E_L      _PK_L_(0x00, 0x6E)
#define REG_MOD_BK00_6E_H      _PK_H_(0x00, 0x6E)
#define REG_MOD_BK00_6F_L      _PK_L_(0x00, 0x6F)
#define REG_MOD_BK00_6F_H      _PK_H_(0x00, 0x6F)
#define REG_MOD_BK00_70_L      _PK_L_(0x00, 0x70)
#define REG_MOD_BK00_70_H      _PK_H_(0x00, 0x70)
#define REG_MOD_BK00_71_L      _PK_L_(0x00, 0x71)
#define REG_MOD_BK00_71_H      _PK_H_(0x00, 0x71)
#define REG_MOD_BK00_72_L      _PK_L_(0x00, 0x72)
#define REG_MOD_BK00_72_H      _PK_H_(0x00, 0x72)
#define REG_MOD_BK00_73_L      _PK_L_(0x00, 0x73)
#define REG_MOD_BK00_73_H      _PK_H_(0x00, 0x73)
#define REG_MOD_BK00_74_L      _PK_L_(0x00, 0x74)
#define REG_MOD_BK00_74_H      _PK_H_(0x00, 0x74)
#define REG_MOD_BK00_75_L      _PK_L_(0x00, 0x75)
#define REG_MOD_BK00_75_H      _PK_H_(0x00, 0x75)
#define REG_MOD_BK00_76_L      _PK_L_(0x00, 0x76)
#define REG_MOD_BK00_76_H      _PK_H_(0x00, 0x76)
#define REG_MOD_BK00_77_L      _PK_L_(0x00, 0x77)
#define REG_MOD_BK00_77_H      _PK_H_(0x00, 0x77)
#define REG_MOD_BK00_78_L      _PK_L_(0x00, 0x78)
#define REG_MOD_BK00_78_H      _PK_H_(0x00, 0x78)
#define REG_MOD_BK00_79_L      _PK_L_(0x00, 0x79)
#define REG_MOD_BK00_79_H      _PK_H_(0x00, 0x79)
#define REG_MOD_BK00_7A_L      _PK_L_(0x00, 0x7A)
#define REG_MOD_BK00_7A_H      _PK_H_(0x00, 0x7A)
#define REG_MOD_BK00_7B_L      _PK_L_(0x00, 0x7B)
#define REG_MOD_BK00_7B_H      _PK_H_(0x00, 0x7B)
#define REG_MOD_BK00_7C_L      _PK_L_(0x00, 0x7C)
#define REG_MOD_BK00_7C_H      _PK_H_(0x00, 0x7C)
#define REG_MOD_BK00_7D_L      _PK_L_(0x00, 0x7D)
#define REG_MOD_BK00_7D_H      _PK_H_(0x00, 0x7D)
#define REG_MOD_BK00_7E_L      _PK_L_(0x00, 0x7E)
#define REG_MOD_BK00_7E_H      _PK_H_(0x00, 0x7E)
#define REG_MOD_BK00_7F_L      _PK_L_(0x00, 0x7F)
#define REG_MOD_BK00_7F_H      _PK_H_(0x00, 0x7F)

//----------------------------------------------
//  MOD_A
//----------------------------------------------

#define REG_MOD_A_BK00_00_L      _PK_L_(0x00, 0x00)
#define REG_MOD_A_BK00_00_H      _PK_H_(0x00, 0x00)
#define REG_MOD_A_BK00_01_L      _PK_L_(0x00, 0x01)
#define REG_MOD_A_BK00_01_H      _PK_H_(0x00, 0x01)
#define REG_MOD_A_BK00_02_L      _PK_L_(0x00, 0x02)
#define REG_MOD_A_BK00_02_H      _PK_H_(0x00, 0x02)
#define REG_MOD_A_BK00_03_L      _PK_L_(0x00, 0x03)
#define REG_MOD_A_BK00_03_H      _PK_H_(0x00, 0x03)
#define REG_MOD_A_BK00_04_L      _PK_L_(0x00, 0x04)
#define REG_MOD_A_BK00_04_H      _PK_H_(0x00, 0x04)
#define REG_MOD_A_BK00_05_L      _PK_L_(0x00, 0x05)
#define REG_MOD_A_BK00_05_H      _PK_H_(0x00, 0x05)
#define REG_MOD_A_BK00_06_L      _PK_L_(0x00, 0x06)
#define REG_MOD_A_BK00_06_H      _PK_H_(0x00, 0x06)
#define REG_MOD_A_BK00_07_L      _PK_L_(0x00, 0x07)
#define REG_MOD_A_BK00_07_H      _PK_H_(0x00, 0x07)
#define REG_MOD_A_BK00_08_L      _PK_L_(0x00, 0x08)
#define REG_MOD_A_BK00_08_H      _PK_H_(0x00, 0x08)
#define REG_MOD_A_BK00_09_L      _PK_L_(0x00, 0x09)
#define REG_MOD_A_BK00_09_H      _PK_H_(0x00, 0x09)
#define REG_MOD_A_BK00_0A_L      _PK_L_(0x00, 0x0A)
#define REG_MOD_A_BK00_0A_H      _PK_H_(0x00, 0x0A)
#define REG_MOD_A_BK00_0B_L      _PK_L_(0x00, 0x0B)
#define REG_MOD_A_BK00_0B_H      _PK_H_(0x00, 0x0B)
#define REG_MOD_A_BK00_0C_L      _PK_L_(0x00, 0x0C)
#define REG_MOD_A_BK00_0C_H      _PK_H_(0x00, 0x0C)
#define REG_MOD_A_BK00_0D_L      _PK_L_(0x00, 0x0D)
#define REG_MOD_A_BK00_0D_H      _PK_H_(0x00, 0x0D)
#define REG_MOD_A_BK00_0E_L      _PK_L_(0x00, 0x0E)
#define REG_MOD_A_BK00_0E_H      _PK_H_(0x00, 0x0E)
#define REG_MOD_A_BK00_0F_L      _PK_L_(0x00, 0x0F)
#define REG_MOD_A_BK00_0F_H      _PK_H_(0x00, 0x0F)
#define REG_MOD_A_BK00_10_L      _PK_L_(0x00, 0x10)
#define REG_MOD_A_BK00_10_H      _PK_H_(0x00, 0x10)
#define REG_MOD_A_BK00_11_L      _PK_L_(0x00, 0x11)
#define REG_MOD_A_BK00_11_H      _PK_H_(0x00, 0x11)
#define REG_MOD_A_BK00_12_L      _PK_L_(0x00, 0x12)
#define REG_MOD_A_BK00_12_H      _PK_H_(0x00, 0x12)
#define REG_MOD_A_BK00_13_L      _PK_L_(0x00, 0x13)
#define REG_MOD_A_BK00_13_H      _PK_H_(0x00, 0x13)
#define REG_MOD_A_BK00_14_L      _PK_L_(0x00, 0x14)
#define REG_MOD_A_BK00_14_H      _PK_H_(0x00, 0x14)
#define REG_MOD_A_BK00_15_L      _PK_L_(0x00, 0x15)
#define REG_MOD_A_BK00_15_H      _PK_H_(0x00, 0x15)
#define REG_MOD_A_BK00_16_L      _PK_L_(0x00, 0x16)
#define REG_MOD_A_BK00_16_H      _PK_H_(0x00, 0x16)
#define REG_MOD_A_BK00_17_L      _PK_L_(0x00, 0x17)
#define REG_MOD_A_BK00_17_H      _PK_H_(0x00, 0x17)
#define REG_MOD_A_BK00_18_L      _PK_L_(0x00, 0x18)
#define REG_MOD_A_BK00_18_H      _PK_H_(0x00, 0x18)
#define REG_MOD_A_BK00_19_L      _PK_L_(0x00, 0x19)
#define REG_MOD_A_BK00_19_H      _PK_H_(0x00, 0x19)
#define REG_MOD_A_BK00_1A_L      _PK_L_(0x00, 0x1A)
#define REG_MOD_A_BK00_1A_H      _PK_H_(0x00, 0x1A)
#define REG_MOD_A_BK00_1B_L      _PK_L_(0x00, 0x1B)
#define REG_MOD_A_BK00_1B_H      _PK_H_(0x00, 0x1B)
#define REG_MOD_A_BK00_1C_L      _PK_L_(0x00, 0x1C)
#define REG_MOD_A_BK00_1C_H      _PK_H_(0x00, 0x1C)
#define REG_MOD_A_BK00_1D_L      _PK_L_(0x00, 0x1D)
#define REG_MOD_A_BK00_1D_H      _PK_H_(0x00, 0x1D)
#define REG_MOD_A_BK00_1E_L      _PK_L_(0x00, 0x1E)
#define REG_MOD_A_BK00_1E_H      _PK_H_(0x00, 0x1E)
#define REG_MOD_A_BK00_1F_L      _PK_L_(0x00, 0x1F)
#define REG_MOD_A_BK00_1F_H      _PK_H_(0x00, 0x1F)
#define REG_MOD_A_BK00_20_L      _PK_L_(0x00, 0x20)
#define REG_MOD_A_BK00_20_H      _PK_H_(0x00, 0x20)
#define REG_MOD_A_BK00_21_L      _PK_L_(0x00, 0x21)
#define REG_MOD_A_BK00_21_H      _PK_H_(0x00, 0x21)
#define REG_MOD_A_BK00_22_L      _PK_L_(0x00, 0x22)
#define REG_MOD_A_BK00_22_H      _PK_H_(0x00, 0x22)
#define REG_MOD_A_BK00_23_L      _PK_L_(0x00, 0x23)
#define REG_MOD_A_BK00_23_H      _PK_H_(0x00, 0x23)
#define REG_MOD_A_BK00_24_L      _PK_L_(0x00, 0x24)
#define REG_MOD_A_BK00_24_H      _PK_H_(0x00, 0x24)
#define REG_MOD_A_BK00_25_L      _PK_L_(0x00, 0x25)
#define REG_MOD_A_BK00_25_H      _PK_H_(0x00, 0x25)
#define REG_MOD_A_BK00_26_L      _PK_L_(0x00, 0x26)
#define REG_MOD_A_BK00_26_H      _PK_H_(0x00, 0x26)
#define REG_MOD_A_BK00_27_L      _PK_L_(0x00, 0x27)
#define REG_MOD_A_BK00_27_H      _PK_H_(0x00, 0x27)
#define REG_MOD_A_BK00_28_L      _PK_L_(0x00, 0x28)
#define REG_MOD_A_BK00_28_H      _PK_H_(0x00, 0x28)
#define REG_MOD_A_BK00_29_L      _PK_L_(0x00, 0x29)
#define REG_MOD_A_BK00_29_H      _PK_H_(0x00, 0x29)
#define REG_MOD_A_BK00_2A_L      _PK_L_(0x00, 0x2A)
#define REG_MOD_A_BK00_2A_H      _PK_H_(0x00, 0x2A)
#define REG_MOD_A_BK00_2B_L      _PK_L_(0x00, 0x2B)
#define REG_MOD_A_BK00_2B_H      _PK_H_(0x00, 0x2B)
#define REG_MOD_A_BK00_2C_L      _PK_L_(0x00, 0x2C)
#define REG_MOD_A_BK00_2C_H      _PK_H_(0x00, 0x2C)
#define REG_MOD_A_BK00_2D_L      _PK_L_(0x00, 0x2D)
#define REG_MOD_A_BK00_2D_H      _PK_H_(0x00, 0x2D)
#define REG_MOD_A_BK00_2E_L      _PK_L_(0x00, 0x2E)
#define REG_MOD_A_BK00_2E_H      _PK_H_(0x00, 0x2E)
#define REG_MOD_A_BK00_2F_L      _PK_L_(0x00, 0x2F)
#define REG_MOD_A_BK00_2F_H      _PK_H_(0x00, 0x2F)
#define REG_MOD_A_BK00_30_L      _PK_L_(0x00, 0x30)
#define REG_MOD_A_BK00_30_H      _PK_H_(0x00, 0x30)
#define REG_MOD_A_BK00_31_L      _PK_L_(0x00, 0x31)
#define REG_MOD_A_BK00_31_H      _PK_H_(0x00, 0x31)
#define REG_MOD_A_BK00_32_L      _PK_L_(0x00, 0x32)
#define REG_MOD_A_BK00_32_H      _PK_H_(0x00, 0x32)
#define REG_MOD_A_BK00_33_L      _PK_L_(0x00, 0x33)
#define REG_MOD_A_BK00_33_H      _PK_H_(0x00, 0x33)
#define REG_MOD_A_BK00_34_L      _PK_L_(0x00, 0x34)
#define REG_MOD_A_BK00_34_H      _PK_H_(0x00, 0x34)
#define REG_MOD_A_BK00_35_L      _PK_L_(0x00, 0x35)
#define REG_MOD_A_BK00_35_H      _PK_H_(0x00, 0x35)
#define REG_MOD_A_BK00_36_L      _PK_L_(0x00, 0x36)
#define REG_MOD_A_BK00_36_H      _PK_H_(0x00, 0x36)
#define REG_MOD_A_BK00_37_L      _PK_L_(0x00, 0x37)
#define REG_MOD_A_BK00_37_H      _PK_H_(0x00, 0x37)
#define REG_MOD_A_BK00_38_L      _PK_L_(0x00, 0x38)
#define REG_MOD_A_BK00_38_H      _PK_H_(0x00, 0x38)
#define REG_MOD_A_BK00_39_L      _PK_L_(0x00, 0x39)
#define REG_MOD_A_BK00_39_H      _PK_H_(0x00, 0x39)
#define REG_MOD_A_BK00_3A_L      _PK_L_(0x00, 0x3A)
#define REG_MOD_A_BK00_3A_H      _PK_H_(0x00, 0x3A)
#define REG_MOD_A_BK00_3B_L      _PK_L_(0x00, 0x3B)
#define REG_MOD_A_BK00_3B_H      _PK_H_(0x00, 0x3B)
#define REG_MOD_A_BK00_3C_L      _PK_L_(0x00, 0x3C)
#define REG_MOD_A_BK00_3C_H      _PK_H_(0x00, 0x3C)
#define REG_MOD_A_BK00_3D_L      _PK_L_(0x00, 0x3D)
#define REG_MOD_A_BK00_3D_H      _PK_H_(0x00, 0x3D)
#define REG_MOD_A_BK00_3E_L      _PK_L_(0x00, 0x3E)
#define REG_MOD_A_BK00_3E_H      _PK_H_(0x00, 0x3E)
#define REG_MOD_A_BK00_3F_L      _PK_L_(0x00, 0x3F)
#define REG_MOD_A_BK00_3F_H      _PK_H_(0x00, 0x3F)
#define REG_MOD_A_BK00_40_L      _PK_L_(0x00, 0x40)
#define REG_MOD_A_BK00_40_H      _PK_H_(0x00, 0x40)
#define REG_MOD_A_BK00_41_L      _PK_L_(0x00, 0x41)
#define REG_MOD_A_BK00_41_H      _PK_H_(0x00, 0x41)
#define REG_MOD_A_BK00_42_L      _PK_L_(0x00, 0x42)
#define REG_MOD_A_BK00_42_H      _PK_H_(0x00, 0x42)
#define REG_MOD_A_BK00_43_L      _PK_L_(0x00, 0x43)
#define REG_MOD_A_BK00_43_H      _PK_H_(0x00, 0x43)
#define REG_MOD_A_BK00_44_L      _PK_L_(0x00, 0x44)
#define REG_MOD_A_BK00_44_H      _PK_H_(0x00, 0x44)
#define REG_MOD_A_BK00_45_L      _PK_L_(0x00, 0x45)
#define REG_MOD_A_BK00_45_H      _PK_H_(0x00, 0x45)
#define REG_MOD_A_BK00_46_L      _PK_L_(0x00, 0x46)
#define REG_MOD_A_BK00_46_H      _PK_H_(0x00, 0x46)
#define REG_MOD_A_BK00_47_L      _PK_L_(0x00, 0x47)
#define REG_MOD_A_BK00_47_H      _PK_H_(0x00, 0x47)
#define REG_MOD_A_BK00_48_L      _PK_L_(0x00, 0x48)
#define REG_MOD_A_BK00_48_H      _PK_H_(0x00, 0x48)
#define REG_MOD_A_BK00_49_L      _PK_L_(0x00, 0x49)
#define REG_MOD_A_BK00_49_H      _PK_H_(0x00, 0x49)
#define REG_MOD_A_BK00_4A_L      _PK_L_(0x00, 0x4A)
#define REG_MOD_A_BK00_4A_H      _PK_H_(0x00, 0x4A)
#define REG_MOD_A_BK00_4B_L      _PK_L_(0x00, 0x4B)
#define REG_MOD_A_BK00_4B_H      _PK_H_(0x00, 0x4B)
#define REG_MOD_A_BK00_4C_L      _PK_L_(0x00, 0x4C)
#define REG_MOD_A_BK00_4C_H      _PK_H_(0x00, 0x4C)
#define REG_MOD_A_BK00_4D_L      _PK_L_(0x00, 0x4D)
#define REG_MOD_A_BK00_4D_H      _PK_H_(0x00, 0x4D)
#define REG_MOD_A_BK00_4E_L      _PK_L_(0x00, 0x4E)
#define REG_MOD_A_BK00_4E_H      _PK_H_(0x00, 0x4E)
#define REG_MOD_A_BK00_4F_L      _PK_L_(0x00, 0x4F)
#define REG_MOD_A_BK00_4F_H      _PK_H_(0x00, 0x4F)
#define REG_MOD_A_BK00_50_L      _PK_L_(0x00, 0x50)
#define REG_MOD_A_BK00_50_H      _PK_H_(0x00, 0x50)
#define REG_MOD_A_BK00_51_L      _PK_L_(0x00, 0x51)
#define REG_MOD_A_BK00_51_H      _PK_H_(0x00, 0x51)
#define REG_MOD_A_BK00_52_L      _PK_L_(0x00, 0x52)
#define REG_MOD_A_BK00_52_H      _PK_H_(0x00, 0x52)
#define REG_MOD_A_BK00_53_L      _PK_L_(0x00, 0x53)
#define REG_MOD_A_BK00_53_H      _PK_H_(0x00, 0x53)
#define REG_MOD_A_BK00_54_L      _PK_L_(0x00, 0x54)
#define REG_MOD_A_BK00_54_H      _PK_H_(0x00, 0x54)
#define REG_MOD_A_BK00_55_L      _PK_L_(0x00, 0x55)
#define REG_MOD_A_BK00_55_H      _PK_H_(0x00, 0x55)
#define REG_MOD_A_BK00_56_L      _PK_L_(0x00, 0x56)
#define REG_MOD_A_BK00_56_H      _PK_H_(0x00, 0x56)
#define REG_MOD_A_BK00_57_L      _PK_L_(0x00, 0x57)
#define REG_MOD_A_BK00_57_H      _PK_H_(0x00, 0x57)
#define REG_MOD_A_BK00_58_L      _PK_L_(0x00, 0x58)
#define REG_MOD_A_BK00_58_H      _PK_H_(0x00, 0x58)
#define REG_MOD_A_BK00_59_L      _PK_L_(0x00, 0x59)
#define REG_MOD_A_BK00_59_H      _PK_H_(0x00, 0x59)
#define REG_MOD_A_BK00_5A_L      _PK_L_(0x00, 0x5A)
#define REG_MOD_A_BK00_5A_H      _PK_H_(0x00, 0x5A)
#define REG_MOD_A_BK00_5B_L      _PK_L_(0x00, 0x5B)
#define REG_MOD_A_BK00_5B_H      _PK_H_(0x00, 0x5B)
#define REG_MOD_A_BK00_5C_L      _PK_L_(0x00, 0x5C)
#define REG_MOD_A_BK00_5C_H      _PK_H_(0x00, 0x5C)
#define REG_MOD_A_BK00_5D_L      _PK_L_(0x00, 0x5D)
#define REG_MOD_A_BK00_5D_H      _PK_H_(0x00, 0x5D)
#define REG_MOD_A_BK00_5E_L      _PK_L_(0x00, 0x5E)
#define REG_MOD_A_BK00_5E_H      _PK_H_(0x00, 0x5E)
#define REG_MOD_A_BK00_5F_L      _PK_L_(0x00, 0x5F)
#define REG_MOD_A_BK00_5F_H      _PK_H_(0x00, 0x5F)
#define REG_MOD_A_BK00_60_L      _PK_L_(0x00, 0x60)
#define REG_MOD_A_BK00_60_H      _PK_H_(0x00, 0x60)
#define REG_MOD_A_BK00_61_L      _PK_L_(0x00, 0x61)
#define REG_MOD_A_BK00_61_H      _PK_H_(0x00, 0x61)
#define REG_MOD_A_BK00_62_L      _PK_L_(0x00, 0x62)
#define REG_MOD_A_BK00_62_H      _PK_H_(0x00, 0x62)
#define REG_MOD_A_BK00_63_L      _PK_L_(0x00, 0x63)
#define REG_MOD_A_BK00_63_H      _PK_H_(0x00, 0x63)
#define REG_MOD_A_BK00_64_L      _PK_L_(0x00, 0x64)
#define REG_MOD_A_BK00_64_H      _PK_H_(0x00, 0x64)
#define REG_MOD_A_BK00_65_L      _PK_L_(0x00, 0x65)
#define REG_MOD_A_BK00_65_H      _PK_H_(0x00, 0x65)
#define REG_MOD_A_BK00_66_L      _PK_L_(0x00, 0x66)
#define REG_MOD_A_BK00_66_H      _PK_H_(0x00, 0x66)
#define REG_MOD_A_BK00_67_L      _PK_L_(0x00, 0x67)
#define REG_MOD_A_BK00_67_H      _PK_H_(0x00, 0x67)
#define REG_MOD_A_BK00_68_L      _PK_L_(0x00, 0x68)
#define REG_MOD_A_BK00_68_H      _PK_H_(0x00, 0x68)
#define REG_MOD_A_BK00_69_L      _PK_L_(0x00, 0x69)
#define REG_MOD_A_BK00_69_H      _PK_H_(0x00, 0x69)
#define REG_MOD_A_BK00_6A_L      _PK_L_(0x00, 0x6A)
#define REG_MOD_A_BK00_6A_H      _PK_H_(0x00, 0x6A)
#define REG_MOD_A_BK00_6B_L      _PK_L_(0x00, 0x6B)
#define REG_MOD_A_BK00_6B_H      _PK_H_(0x00, 0x6B)
#define REG_MOD_A_BK00_6C_L      _PK_L_(0x00, 0x6C)
#define REG_MOD_A_BK00_6C_H      _PK_H_(0x00, 0x6C)
#define REG_MOD_A_BK00_6D_L      _PK_L_(0x00, 0x6D)
#define REG_MOD_A_BK00_6D_H      _PK_H_(0x00, 0x6D)
#define REG_MOD_A_BK00_6E_L      _PK_L_(0x00, 0x6E)
#define REG_MOD_A_BK00_6E_H      _PK_H_(0x00, 0x6E)
#define REG_MOD_A_BK00_6F_L      _PK_L_(0x00, 0x6F)
#define REG_MOD_A_BK00_6F_H      _PK_H_(0x00, 0x6F)
#define REG_MOD_A_BK00_70_L      _PK_L_(0x00, 0x70)
#define REG_MOD_A_BK00_70_H      _PK_H_(0x00, 0x70)
#define REG_MOD_A_BK00_71_L      _PK_L_(0x00, 0x71)
#define REG_MOD_A_BK00_71_H      _PK_H_(0x00, 0x71)
#define REG_MOD_A_BK00_72_L      _PK_L_(0x00, 0x72)
#define REG_MOD_A_BK00_72_H      _PK_H_(0x00, 0x72)
#define REG_MOD_A_BK00_73_L      _PK_L_(0x00, 0x73)
#define REG_MOD_A_BK00_73_H      _PK_H_(0x00, 0x73)
#define REG_MOD_A_BK00_74_L      _PK_L_(0x00, 0x74)
#define REG_MOD_A_BK00_74_H      _PK_H_(0x00, 0x74)
#define REG_MOD_A_BK00_75_L      _PK_L_(0x00, 0x75)
#define REG_MOD_A_BK00_75_H      _PK_H_(0x00, 0x75)
#define REG_MOD_A_BK00_76_L      _PK_L_(0x00, 0x76)
#define REG_MOD_A_BK00_76_H      _PK_H_(0x00, 0x76)
#define REG_MOD_A_BK00_77_L      _PK_L_(0x00, 0x77)
#define REG_MOD_A_BK00_77_H      _PK_H_(0x00, 0x77)
#define REG_MOD_A_BK00_78_L      _PK_L_(0x00, 0x78)
#define REG_MOD_A_BK00_78_H      _PK_H_(0x00, 0x78)
#define REG_MOD_A_BK00_79_L      _PK_L_(0x00, 0x79)
#define REG_MOD_A_BK00_79_H      _PK_H_(0x00, 0x79)
#define REG_MOD_A_BK00_7A_L      _PK_L_(0x00, 0x7A)
#define REG_MOD_A_BK00_7A_H      _PK_H_(0x00, 0x7A)
#define REG_MOD_A_BK00_7B_L      _PK_L_(0x00, 0x7B)
#define REG_MOD_A_BK00_7B_H      _PK_H_(0x00, 0x7B)
#define REG_MOD_A_BK00_7C_L      _PK_L_(0x00, 0x7C)
#define REG_MOD_A_BK00_7C_H      _PK_H_(0x00, 0x7C)
#define REG_MOD_A_BK00_7D_L      _PK_L_(0x00, 0x7D)
#define REG_MOD_A_BK00_7D_H      _PK_H_(0x00, 0x7D)
#define REG_MOD_A_BK00_7E_L      _PK_L_(0x00, 0x7E)
#define REG_MOD_A_BK00_7E_H      _PK_H_(0x00, 0x7E)
#define REG_MOD_A_BK00_7F_L      _PK_L_(0x00, 0x7F)
#define REG_MOD_A_BK00_7F_H      _PK_H_(0x00, 0x7F)


#ifdef MOD_TVFRC
#define REG_MOD_BK03_00_L      _PK_L_(0x03, 0x00)
#define REG_MOD_BK03_00_H      _PK_H_(0x03, 0x00)
#define REG_MOD_BK03_01_L      _PK_L_(0x03, 0x01)
#define REG_MOD_BK03_01_H      _PK_H_(0x03, 0x01)
#define REG_MOD_BK03_02_L      _PK_L_(0x03, 0x02)
#define REG_MOD_BK03_02_H      _PK_H_(0x03, 0x02)
#define REG_MOD_BK03_03_L      _PK_L_(0x03, 0x03)
#define REG_MOD_BK03_03_H      _PK_H_(0x03, 0x03)
#define REG_MOD_BK03_04_L      _PK_L_(0x03, 0x04)
#define REG_MOD_BK03_04_H      _PK_H_(0x03, 0x04)
#define REG_MOD_BK03_05_L      _PK_L_(0x03, 0x05)
#define REG_MOD_BK03_05_H      _PK_H_(0x03, 0x05)
#endif

//-------------------------------------------------------------------------------------------------
//  Macro and Define
//-------------------------------------------------------------------------------------------------
#define _BITMASK(loc_msb, loc_lsb) ((1U << (loc_msb)) - (1U << (loc_lsb)) + (1U << (loc_msb)))
#define BITMASK(x) _BITMASK(1?x, 0?x)
#define HBMASK    0xFF00
#define LBMASK    0x00FF

#define RIU_MACRO_START     do {
#define RIU_MACRO_END       } while (0)

// Address bus of RIU is 16 bits.
#define RIU_READ_BYTE(addr)         ( READ_BYTE( g_ptr_PMRiuBaseAddr + (addr) ) )
#define RIU_READ_2BYTE(addr)        ( READ_WORD( g_ptr_PMRiuBaseAddr + (addr) ) )
#define RIU_WRITE_BYTE(addr, val)   { WRITE_BYTE( g_ptr_PMRiuBaseAddr + (addr), val) }
#define RIU_WRITE_2BYTE(addr, val)  { WRITE_WORD( g_ptr_PMRiuBaseAddr + (addr), val) }

// Address bus of RIU is 16 bits for PM //alex_tung
#define PM_RIU_READ_BYTEM(addr)        ( READ_BYTE( g_ptr_PMRiuBaseAddr + (addr) ) )
#define PM_RIU_READ_2BYTE(addr)        ( READ_WORD( g_ptr_PMRiuBaseAddr + (addr) ) )
#define PM_RIU_WRITE_BYTE(addr, val)   { WRITE_BYTE( g_ptr_PMRiuBaseAddr + (addr), val) }
#define PM_RIU_WRITE_2BYTE(addr, val)  { WRITE_WORD( g_ptr_PMRiuBaseAddr + (addr), val) }

/// Maximum xc device number
#define PNL_HWREG_MAX_SUPPORT_DEVICE_NUM      2

//Device bank offset
INTERFACE MS_U32 u32PNL_XCDeviceBankOffset[PNL_HWREG_MAX_SUPPORT_DEVICE_NUM];

//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

//=============================================================
#ifdef REG_SCRIPT

#define SC_W2BYTE( u8Id, u32Reg, u16Val)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF)), (unsigned int)((u16Val) & 0xFF)); \
                    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_SCALER_BASE + ((u32Reg +1) & 0xFFFF)), (unsigned int)(((u16Val) & 0xFF00) >> 8)); \
              }\
              else\
              {\
                  REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)((u16Val) & 0xFF)); \
                  REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_SCALER_BASE + ((u32Reg + 1) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)(((u16Val) & 0xFF00) >> 8)); \
              }})

#define SC_R2BYTE( u8Id, u32Reg ) \
            ( { ((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
            ? RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) << 1 )  \
            : RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 ); } )

#define SC_W4BYTE( u8Id, u32Reg, u32Val)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ), (unsigned int)((u32Val) & 0xFF)); \
                    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + 1 ), (unsigned int)(((u32Val) & 0x0000FF00) >> 8)); \
                    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + 2 ), (unsigned int)(((u32Val) & 0x00FF0000) >> 16)); \
                    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + 3 ), (unsigned int)(((u32Val) & 0xFF000000) >> 24)); \
              }\
              else\
              {\
                  REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg + 0) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)((u32Val) & 0xFF)); \
                  REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg + 1) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)(((u32Val) & 0x0000FF00) >> 8)); \
                  REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg + 2) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)(((u32Val) & 0x00FF0000) >> 16)); \
                  REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg + 3) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)(((u32Val) & 0xFF000000) >> 24)); \
              }})

#define SC_R4BYTE( u8Id, u32Reg )\
            ( { ((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
            ? RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF)) << 1 ) | (MS_U32)(RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + 2 ) << 1 )) << 16 \
            : RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 ) | (MS_U32)(RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) + 2 ) << 1 )) << 16 ; } )

#define SC_R2BYTEMSK( u8Id, u32Reg, u16mask)\
            ( { ((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
            ? RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) << 1 ) & (u16mask)\
            : RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 ) & (u16mask) ; } )

#define SC_W2BYTEMSK( u8Id, u32Reg, u16Val, u16Mask)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                    REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ), (unsigned int)((u16Mask) & 0xFF), (unsigned int)((u16Val) & 0xFF)); \
                    REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) +1), (unsigned int)(((u16Mask) & 0xFF00) >> 8), (unsigned int)(((u16Val) & 0xFF00) >> 8)); \
              }\
              else\
              {\
                  REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)((u16Mask) & 0xFF), (unsigned int)((u16Val) & 0xFF)); \
                  REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x \n", (unsigned int)(REG_SCALER_BASE + ((u32Reg + 1) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ), (unsigned int)(((u16Mask) & 0xFF00) >> 8), (unsigned int)(((u16Val) & 0xFF00) >> 8)); \
              }})



#define MOD_W2BYTE( u32Reg, u16Val)\
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_MOD_BASE & 0xFFFF), (unsigned int)(((u32Reg) >> 8) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_MOD_BASE + ((u32Reg) & 0xFFFF)), (unsigned int)((u16Val) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_MOD_BASE + ((u32Reg +1) & 0xFFFF)), (unsigned int)(((u16Val) & 0xFF00) >> 8));

#define MOD_R2BYTE( u32Reg ) \
                            ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                                RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) ; } )

#define MOD_R2BYTEMSK( u32Reg, u16mask)\
                            ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                                RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask); })

#define MOD_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x\n", (unsigned int)(REG_MOD_BASE & 0xFFFF), (unsigned int)(((u32Reg) >> 8) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x \n", (unsigned int)(REG_MOD_BASE + ((u32Reg) & 0xFFFF) ), (unsigned int)((u16Mask) & 0xFF), (unsigned int)((u16Val) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x \n", (unsigned int)(REG_MOD_BASE + ((u32Reg) & 0xFFFF) +1), (unsigned int)(((u16Mask) & 0xFF00) >> 8), (unsigned int)(((u16Val) & 0xFF00) >> 8));

#define W2BYTE( u32Reg, u16Val) \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(((u32Reg) & 0xFFFF) ), (unsigned int)((u16Val) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(((u32Reg+1) & 0xFFFF) ), (unsigned int)(((u16Val) & 0xFF00) >> 8));



#define R2BYTE( u32Reg ) RIU_READ_2BYTE( (u32Reg) << 1)

#define W4BYTE( u32Reg, u32Val) \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(((u32Reg) & 0xFFFF) ), (unsigned int)((u32Val) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(((u32Reg+1) & 0xFFFF) ), (unsigned int)(((u32Val) & 0x0000FF00) >> 8)); \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(((u32Reg+2) & 0xFFFF) ), (unsigned int)(((u32Val) & 0x00FF0000) >> 16)); \
    REG_DBG("wriu -b 0x%06x 0xFF 0x%02x \n", (unsigned int)(((u32Reg+3) & 0xFFFF) ), (unsigned int)(((u32Val) & 0xFF000000) >> 24));


#define R4BYTE( u32Reg )\
                ( { ((RIU_READ_2BYTE( (u32Reg) << 1)) | ((MS_U32)(RIU_READ_2BYTE( ( (u32Reg) + 2 ) << 1) ) << 16)) ; } )

#define R1BYTEMSK( u32Reg, u16mask)\
                ( { RIU_READ_BYTE(((u32Reg) << 1) - ((u32Reg) & 1)) & u16mask ; } )

#define W1BYTEMSK( u32Addr, u8Val, u8mask)     \
                REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x\n", (unsigned int)(u32Addr),  (unsigned int)((u8mask) & 0xFF), (unsigned int)((u8Val) & 0xFF))


#define R2BYTEMSK( u32Reg, u16mask)\
                ( { RIU_READ_2BYTE( (u32Reg)<< 1) & u16mask ; } )

#define W2BYTEMSK( u32Reg, u16Val, u16Mask)\
    REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x\n", (unsigned int)(u32Reg),  (unsigned int)((u16Mask) & 0xFF), (unsigned int)((u16Val) & 0xFF)); \
    REG_DBG("wriu -b 0x%06x 0x%02x 0x%02x\n", (unsigned int)(u32Reg+1),  (unsigned int)(((u16Mask) >> 8) & 0xFF), (unsigned int)(((u16Val) >> 8) & 0xFF));


#else
// Just for Scaler
#if XC_REGISTER_SPREAD

#define SC_W2BYTE( u8Id, u32Reg, u16Val)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF)) << 1 , u16Val  ) ; \
              }\
              else\
              {\
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 , u16Val  ) ; \
              }})

#define SC_R2BYTE( u8Id, u32Reg ) \
            ( { ((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
            ? RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) << 1 )  \
            : RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 ); } )

#define SC_W4BYTE( u8Id, u32Reg, u32Val)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) <<1, (MS_U16)((u32Val) & 0x0000FFFF) ) ;  \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + 2 ) << 1, (MS_U16)(((u32Val) >> 16) & 0x0000FFFF) );\
              }\
              else\
              {\
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) <<1, (MS_U16)((u32Val) & 0x0000FFFF) ) ;  \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) + 2 ) << 1, (MS_U16)(((u32Val) >> 16) & 0x0000FFFF) );\
              }})

#define SC_R4BYTE( u8Id, u32Reg )\
            ( { ((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
            ? RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF)) << 1 ) | (MS_U32)(RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + 2 ) << 1 )) << 16 \
            : RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 ) | (MS_U32)(RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) + 2 ) << 1 )) << 16 ; } )

#define SC_R2BYTEMSK( u8Id, u32Reg, u16mask)\
            ( { ((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
            ? RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) << 1 ) & (u16mask)\
            : RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1 ) & (u16mask) ; } )

#define SC_W2BYTEMSK( u8Id, u32Reg, u16Val, u16Mask)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) << 1, (RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) ) << 1) & ~(u16Mask) ) | ((u16Val) & (u16Mask)) ) ;\
              }\
              else\
              {\
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1, (RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFFFF) + (u32PNL_XCDeviceBankOffset[u8Id] << 8) ) << 1) & ~(u16Mask) ) | ((u16Val) & (u16Mask)) ) ; \
              }})

#else
#define SC_W2BYTE( u8Id, u32Reg, u16Val)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE +((u32Reg) & 0xFF) ) << 1 , u16Val  ) ;\
              }\
              else\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, (((u32Reg) >> 8) & 0x00FF) + u32PNL_XCDeviceBankOffset[u8Id] ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE +((u32Reg) & 0xFF) ) << 1 , u16Val  ) ;\
              }})

#define SC_R2BYTE( u8Id, u32Reg ) \
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ( (u32Reg) >> 8) & 0x00FF ) ; \
              }\
              else\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, (( (u32Reg) >> 8) & 0x00FF) + u32PNL_XCDeviceBankOffset[u8Id] ) ; \
              }\
              RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) )<<1 ) ;})

#define SC_W4BYTE( u8Id, u32Reg, u32Val)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE<<1, ((u32Reg) >> 8) & 0x00FF) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) <<1, (MS_U16)((u32Val) & 0x0000FFFF) ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) + 2 ) << 1, (MS_U16)(((u32Val) >> 16) & 0x0000FFFF) );\
              }\
              else\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE<<1, (((u32Reg) >> 8) & 0x00FF) + u32PNL_XCDeviceBankOffset[u8Id] ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) <<1, (MS_U16)((u32Val) & 0x0000FFFF) ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) + 2 ) << 1, (MS_U16)(((u32Val) >> 16) & 0x0000FFFF) );\
              }})

#define SC_R4BYTE( u8Id, u32Reg )\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
              }\
              else\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, (((u32Reg) >> 8) & 0x00FF) + u32PNL_XCDeviceBankOffset[u8Id] ) ; \
              }\
              RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1 ) | (MS_U32)(RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) + 2 ) << 1 )) << 16;})

#define SC_R2BYTEMSK( u8Id, u32Reg, u16mask)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ;  \
              }\
              else\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, (((u32Reg) >> 8) & 0x00FF) + u32PNL_XCDeviceBankOffset[u8Id] ) ; \
              }\
              RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask) ;})

#define SC_W2BYTEMSK( u8Id, u32Reg, u16Val, u16Mask)\
            ({if((((u32Reg) & 0xFFFF) >> 8) >= u32PNL_XCDeviceBankOffset[1])\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, ((u32Reg) >> 8) & 0x00FF ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1, (RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1) & ~(u16Mask) ) | ((u16Val) & (u16Mask)) ) ;\
              }\
              else\
              {\
                   RIU_WRITE_2BYTE(REG_SCALER_BASE << 1, (((u32Reg) >> 8) & 0x00FF) + u32PNL_XCDeviceBankOffset[u8Id] ) ; \
                   RIU_WRITE_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1, (RIU_READ_2BYTE( (REG_SCALER_BASE + ((u32Reg) & 0xFF) ) << 1) & ~(u16Mask) ) | ((u16Val) & (u16Mask)) ) ;\
              }})

#endif

//=============================================================
/// for MOD
#if (REG_MOD_BASE != 0x303200)
  #ifdef MOD_TVFRC /// The MOD sub bank is at 0x7F
#define MOD_W2BYTE( u32Reg, u16Val)\
              ( { RIU_WRITE_2BYTE((REG_MOD_BASE+0xFE) << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1, u16Val ); } )

#define MOD_R2BYTE( u32Reg ) \
              ( { RIU_WRITE_2BYTE((REG_MOD_BASE+0xFE) << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) ; } )

#define MOD_R2BYTEMSK( u32Reg, u16mask)\
              ( { RIU_WRITE_2BYTE((REG_MOD_BASE+0xFE) << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask); })

#define MOD_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
              ( { RIU_WRITE_2BYTE((REG_MOD_BASE+0xFE) << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) )<<1 , (RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1 ) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ); } )

  #else
#define MOD_W2BYTE( u32Reg, u16Val)\
              ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1, u16Val ); } )

#define MOD_R2BYTE( u32Reg ) \
              ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) ; } )

#define MOD_R2BYTEMSK( u32Reg, u16mask)\
              ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask); })

#define MOD_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
              ( { RIU_WRITE_2BYTE(REG_MOD_BASE << 1, ((u32Reg) >> 8) & 0x00FF ); \
                  RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) )<<1 , (RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1 ) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ); } )
    #endif
#else
#define MOD_W2BYTE( u32Reg, u16Val)\
            ( { RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1, u16Val ); } )

#define MOD_R2BYTE( u32Reg ) \
            ( { RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) ; } )

#define MOD_R2BYTEMSK( u32Reg, u16mask)\
            ( { RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask); })

#define MOD_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
            ( { RIU_WRITE_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) )<<1 , (RIU_READ_2BYTE( (REG_MOD_BASE + ((u32Reg) & 0xFF) ) << 1 ) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ); } )

#endif

/// new MOD bank for MOD_A, and original is fo MOD_D, from Monaco
#define MOD_A_W2BYTE( u32Reg, u16Val)\
            ( { RIU_WRITE_2BYTE( (REG_MOD_A_BASE + ((u32Reg) & 0xFF) ) << 1, u16Val ); } )

#define MOD_A_R2BYTE( u32Reg ) \
            ( { RIU_READ_2BYTE( (REG_MOD_A_BASE + ((u32Reg) & 0xFF) ) << 1) ; } )

#define MOD_A_R2BYTEMSK( u32Reg, u16mask)\
            ( { RIU_READ_2BYTE( (REG_MOD_A_BASE + ((u32Reg) & 0xFF) ) << 1) & (u16mask); })

#define MOD_A_W2BYTEMSK( u32Reg, u16Val, u16Mask)\
            ( { RIU_WRITE_2BYTE( (REG_MOD_A_BASE + ((u32Reg) & 0xFF) )<<1 , (RIU_READ_2BYTE( (REG_MOD_A_BASE + ((u32Reg) & 0xFF) ) << 1 ) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ); } )



//=============================================================
//General ( Make sure u32Reg is not ODD
#define W2BYTE( u32Reg, u16Val) RIU_WRITE_2BYTE( (u32Reg) << 1 , u16Val )


#define R2BYTE( u32Reg ) RIU_READ_2BYTE( (u32Reg) << 1)

#define W4BYTE( u32Reg, u32Val)\
            ( { RIU_WRITE_2BYTE( (u32Reg) << 1, ((u32Val) & 0x0000FFFF) ); \
                RIU_WRITE_2BYTE( ( (u32Reg) + 2) << 1 , (((u32Val) >> 16) & 0x0000FFFF)) ; } )

#define R4BYTE( u32Reg )\
            ( { ((RIU_READ_2BYTE( (u32Reg) << 1)) | ((MS_U32)(RIU_READ_2BYTE( ( (u32Reg) + 2 ) << 1) ) << 16)) ; } )

#define R1BYTEMSK( u32Reg, u16mask)\
            ( { RIU_READ_BYTE(((u32Reg) << 1) - ((u32Reg) & 1)) & u16mask ; } )

#define W1BYTEMSK( u32Addr, u8Val, u8mask)     \
            ( { RIU_WRITE_BYTE( (((u32Addr) <<1) - ((u32Addr) & 1)), (RIU_READ_BYTE((((u32Addr) <<1) - ((u32Addr) & 1))) & ~(u8mask)) | ((u8Val) & (u8mask))); })


#define R2BYTEMSK( u32Reg, u16mask)\
            ( { RIU_READ_2BYTE( (u32Reg)<< 1) & u16mask ; } )

#define W2BYTEMSK( u32Reg, u16Val, u16Mask)\
            ( { RIU_WRITE_2BYTE( (u32Reg)<< 1 , (RIU_READ_2BYTE((u32Reg) << 1) & ~(u16Mask)) | ((u16Val) & (u16Mask)) ) ; } )
#endif
//=============================================================
// Just for PM registers

/*
    R/W register forced to use 8 bit address, everytime need to r/w 2 bytes with mask

    32bit address     16 bit address        8 bit address
        0                   0                       0
        1                   x                       1
        2
        3
        4                   1                       2
        5                   x                       3
        6
        7
        8                   2                       4
        9                   x                       5
        A
        B                                                                                  */

// to read 0x2F03[3], please use R1BYTE(0x2F03, 3:3)
#define PM_R1BYTE(u32Addr, u8mask)            \
    (READ_BYTE (gu32PMRiuBaseAddr + (u32Addr << 1) - (u32Addr & 1)) & BMASK(u8mask))

// to write 0x2F02[4:3] with 2'b10, please use W1BYTE(0x2F02, 0x02, 4:3)
#define PM_W1BYTE(u32Addr, u8Val, u8mask)     \
    (WRITE_BYTE(gu32PMRiuBaseAddr + (u32Addr << 1) - (u32Addr & 1), (PM_R1BYTE(u32Addr, 7:0) & ~BMASK(u8mask)) | (BITS(u8mask, u8Val) & BMASK(u8mask))))
#if 1//alex_tung
// access PM registers
// u32Addr must be 16bit aligned
#define PM_R2BYTE( u32Reg, u16mask)\
            ( PM_RIU_READ_2BYTE( (u32Reg)<< 1) & u16mask )
    // u32Addr must be 16bit aligned
#define PM_W2BYTE( u32Reg, u16Val, u16Mask)\
            (  PM_RIU_WRITE_2BYTE( (u32Reg)<< 1 , (PM_RIU_READ_2BYTE((u32Reg) << 1) & ~(u16Mask)) | ((u16Val) & (u16Mask)) )  )
#else
// u32Addr must be 16bit aligned
#define PM_R2BYTE(u32Addr, u16mask)            \
    (READ_WORD (_PM_RIU_BASE + (u32Addr << 1)) & BMASK(u16mask))

// u32Addr must be 16bit aligned
#define PM_W2BYTE(u32Addr, u16Val, u16mask)    \
    (WRITE_WORD(_PM_RIU_BASE + (u32Addr << 1), (PM_R2BYTE(u32Addr, 15:0) & ~BMASK(u16mask)) | (BITS(u16mask, u16Val) & BMASK(u16mask))))
#endif

//-------------------------------------------------------------------------------------------------
//  Type and Structure
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Function and Variable
//-------------------------------------------------------------------------------------------------

#undef INTERFACE

#endif
