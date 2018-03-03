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
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
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

////////////////////////////////////////////////////////////////////////////////////////////////////
// file   halHDCP.c
// @brief  HDCP HAL
// @author MStar Semiconductor,Inc.
////////////////////////////////////////////////////////////////////////////////////////////////////
/*********************************************************************/
/*                                                                                                                     */
/*                                                   Includes                                                      */
/*                                                                                                                     */
/*********************************************************************/
#include <stdio.h>
#include <string.h>
#include "MsCommon.h"
#include "MsTypes.h"
#include "regHDCP.h"
#include "halHDCP.h"
#include "drvCPU.h"

#ifndef HAL_HDCP_C
#define HAL_HDCP_C

/*********************************************************************/
/*                                                                                                                     */
/*                                                      Defines                                                    */
/*                                                                                                                     */
/*********************************************************************/
#define DEF_HDCP_TX_FUNC_EN     0

#if(defined(CONFIG_MLOG))
#include "ULog.h"

#define HalHDCPLogInfo(format, args...)       ULOGI("HDCP", format, ##args)
#define HalHDCPLogWarning(format, args...)    ULOGW("HDCP", format, ##args)
#define HalHDCPLogDebug(format, args...)      ULOGD("HDCP", format, ##args)
#define HalHDCPLogError(format, args...)      ULOGE("HDCP", format, ##args)
#define HalHDCPLogFatal(format, args...)      ULOGF("HDCP", format, ##args)

#else

#define HalHDCPLogInfo(format, args...)       printf(format, ##args)
#define HalHDCPLogWarning(format, args...)    printf(format, ##args)
#define HalHDCPLogDebug(format, args...)      printf(format, ##args)
#define HalHDCPLogError(format, args...)      printf(format, ##args)
#define HalHDCPLogFatal(format, args...)      printf(format, ##args)

#endif


#define DEF_SIZE_OF_KSXORLC128  16
#define DEF_SIZE_OF_RIV         8

MS_VIRT _gHDCPRegBase = 0x00U;
MS_VIRT _gHDCPPMRegBase = 0x00U;

#define HDCPREG(bank, addr)     (*((volatile MS_U16 *)((_gHDCPRegBase + (bank << 1U)) + (addr << 2U))))
#define HDCPPMREG(bank, addr)   (*((volatile MS_U16 *)((_gHDCPPMRegBase + (bank << 1U)) + (addr << 2U))))

#define DEF_HDCP14_M0_SIZE          64U //bytes

/*********************************************************************/
/*                                                                                                                     */
/*                                                    Functions                                                    */
/*                                                                                                                     */
/*********************************************************************/
/*********************************************************************/
/*                                                                                                                     */
/*                                                    Internal                                                      */
/*                                                                                                                     */
/*********************************************************************/

MS_U16 MHalHdcpRegRead(MS_U32 bank, MS_U16 address)
{
    return HDCPREG(bank, address);
}

void MHalHdcpRegWrite(MS_U32 bank, MS_U16 address, MS_U16 reg_data)
{
    HDCPREG(bank, address) = reg_data;
}

void MHalHdcpRegMaskWrite(MS_U32 bank, MS_U16 address, MS_U16 reg_mask, MS_U16 reg_data)
{
    MS_U16 reg_value;

    reg_value = (HDCPREG(bank, address) & (~reg_mask)) | (reg_data & reg_mask);
    HDCPREG(bank, address) = reg_value;
}

MS_U16 MHalHdcpPMRegRead(MS_U32 bank, MS_U16 address)
{
    return HDCPPMREG(bank, address);
}

void MHalHdcpPMRegWrite(MS_U32 bank, MS_U16 address, MS_U16 reg_data)
{
    HDCPPMREG(bank, address) = reg_data;
}

void MHalHdcpPMRegMaskWrite(MS_U32 bank, MS_U16 address, MS_U16 reg_mask, MS_U16 reg_data)
{
    MS_U16 reg_value;

    reg_value = (HDCPPMREG(bank, address) & (~reg_mask)) | (reg_data & reg_mask);
    HDCPPMREG(bank, address) = reg_value;
}

/*********************************************************************/
/*                                                                                                                     */
/*                                                    External                                                     */
/*                                                                                                                     */
/*********************************************************************/
void MHal_HDCP_HDCP14TxInitHdcp(MS_U8 u8PortIdx)
{
    return; //this project has no tx port
}

void MHal_HDCP_HDCP14TxLoadKey(MS_U8* pu8KeyData, MS_BOOL bUseKmNewMode)
{
    return; //this project has no tx port
}

void MHal_HDCP_HDCP14TxSetAuthPass(MS_U8 u8PortIdx)
{
    return; //this project has no tx port
}

void MHal_HDCP_HDCP14TxEnableENC_EN(MS_U8 u8PortIdx, MS_BOOL bEnable)
{
    return; //this project has no tx port
}

void MHal_HDCP_HDCP14TxProcessAn(MS_U8 u8PortIdx, MS_BOOL bUseInternalAn, MS_U8* pu8An)
{
    return; //this project has no tx port
}


void MHal_HDCP_HDCP14TxGetAKSV(MS_U8 u8PortIdx, MS_U8* pu8Aksv)
{
    return; //this project has no tx port
}


MS_BOOL MHal_HDCP_HDCP14TxCompareRi(MS_U8 u8PortIdx, MS_U8* pu8SinkRi)
{
    return FALSE; //this project has no tx port
}


void MHal_HDCP_HDCP14TxConfigMode(MS_U8 u8PortIdx, MS_U8 u8Mode)
{
    return; //this project has no tx port
}


void MHal_HDCP_HDCP14TxGenerateCipher(MS_U8 u8PortIdx, MS_U8* pu8Bksv)
{
    return; //this project has no tx port


}

MS_BOOL MHal_HDCP_HDCP14TxProcessR0(MS_U8 u8PortIdx)
{
    return FALSE; //this project has no tx port
}

void MHal_HDCP_HDCP14TxGetM0(MS_U8 u8PortIdx, MS_U8* pu8M0)
{
    return;
}

void MHal_HDCP_HDCP14GetM0(MS_U8 u8PortIdx, MS_U8 *pu8Data)
{
    MS_U8 cnt = 0x00;
    MS_U16 u16BKOffset = 0x00;

    u8PortIdx &= 0x0F;
    u16BKOffset = u8PortIdx * 0x300;

    for ( cnt = 0; cnt < (DEF_HDCP14_M0_SIZE >> 4); cnt++ )
    {
        MS_U16 u16tmpData = 0x00;

        u16tmpData = MHalHdcpRegRead(DEF_HDCP14_RX_REG_BANK + u16BKOffset, 0x0E + cnt);

        *(pu8Data + cnt*2) = (MS_U8)(u16tmpData & 0x00FF);
        *(pu8Data + cnt*2 + 1) = (MS_U8)((u16tmpData & 0xFF00) >> 8);
    }
}

void MHal_HDCP_HDCP14FillBksv(MS_U8 *pu8BksvData)
{
    MS_U8 uctemp = 0;
    MS_U8 ucPortSelect = 0;
    MS_U32 ulMACBankOffset = 0;

    for(ucPortSelect = HDMI_RX_SELECT_PORTA; ucPortSelect < HDMI_RX_SELECT_MASK; ucPortSelect++)
    {
        switch(ucPortSelect)
        {
            case HDMI_RX_SELECT_PORTA:
                ulMACBankOffset = 0;
                break;

            case HDMI_RX_SELECT_PORTB:
                ulMACBankOffset = 0x300;
                break;

            case HDMI_RX_SELECT_PORTC:
                ulMACBankOffset = 0x600;
                break;

            case HDMI_RX_SELECT_PORTD:
                ulMACBankOffset = 0x900;
                break;

            default:
                break;
        };

        // Bksv
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x17, BIT(10), BIT(10));
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19, BIT(15)|BIT(14), BIT(15)); // [15]: CPU write disable, [14]: 0: 74 RAM, 1 :HDCP RAM

        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x17, BMASK(9:0), 0x00); // address
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19, BIT(5), BIT(5));

        for(uctemp = 0; uctemp < 5; uctemp++)
        {
            MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x18, BMASK(7:0), pu8BksvData[uctemp]); // data
            MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19, BIT(4), BIT(4)); // trigger latch data

            while(MHalHdcpRegRead(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19) & BIT(7)); // wait write ready
            while(MHalHdcpRegRead(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19) & BIT(7)); // wait write ready for SW patch
        }

        // Bcaps = 0x80
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x17, BMASK(9:0), 0x40); // address
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19, BIT(5), BIT(5));

        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x18, BMASK(7:0), 0x80); // data
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19, BIT(4), BIT(4)); // trigger latch data

        while(MHalHdcpRegRead(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19) & BIT(7)); // wait write ready

        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x19, BIT(15)|BIT(14), 0); // [15]: CPU write disable, [14]: 0: 74 RAM, 1 :HDCP RAM

        // [10:8]: 3'b111 determine Encrp_En during Vblank in DVI mode; [5]:HDCP enable; [0]: EESS mode deglitch Vsync mode
        MHalHdcpRegMaskWrite(DEF_HDCP14_RX_REG_BANK +ulMACBankOffset, 0x00, BIT(10)|BIT(9)|BIT(8)|BIT(5)|BIT(0), BIT(10)|BIT(9)|BIT(8)|BIT(5)|BIT(0));
    }
}

void MHal_HDCP_HDCP14FillKey(MS_U8 *pu8KeyData)
{
    MS_U16 ustemp = 0;

    MHalHdcpRegMaskWrite(DEF_HDCPKEY_REG_BANK, REG_HDCPKEY_BANK_02_L, BIT(8), BIT(8));

    // HDCP key
    MHalHdcpRegMaskWrite(DEF_COMBO_GP_TOP_REG_BANK, REG_COMBO_GP_TOP_40_L, BIT(3)|BIT(2)|BIT(0), BIT(3)|BIT(2)|BIT(0)); // [2]: CPU write enable, [3]: 0: 74 RAM, 1 :HDCP RAM
    // burst write from address 0x05
    MHalHdcpRegMaskWrite(DEF_HDCPKEY_REG_BANK, REG_HDCPKEY_BANK_00_L, BMASK(9:0), 0x05); // address

    for(ustemp = 0; ustemp < 284; ustemp++)
    {
        MHalHdcpRegMaskWrite(DEF_HDCPKEY_REG_BANK, REG_HDCPKEY_BANK_01_L, BMASK(7:0), *(pu8KeyData +ustemp)); // data
    }

    MHalHdcpRegMaskWrite(DEF_COMBO_GP_TOP_REG_BANK, REG_COMBO_GP_TOP_40_L, BIT(3)|BIT(2)|BIT(0), 0); // [2]: CPU write enable, [3]: 0: 74 RAM, 1 :HDCP RAM
}

void MHal_HDCP_SetBank(MS_U32 u32NonPmBankAddr, MS_U32 u32PmBankAddr)
{
    HalHDCPLogInfo("u32NonPmBankAddr = 0x%X, u32PmBankAddr = 0x%X\r\n", (unsigned int)u32NonPmBankAddr, (unsigned int)u32PmBankAddr);
    _gHDCPRegBase = u32NonPmBankAddr;
    _gHDCPPMRegBase = u32PmBankAddr;
}

void MHal_HDCP_HDCP2TxInit(MS_U8 u8PortIdx, MS_BOOL bEnable)
{
    return; //this project has no tx port
}

void MHal_HDCP_HDCP2TxEnableEncrypt(MS_U8 u8PortIdx, MS_BOOL bEnable)
{
    return;
}

void MHal_HDCP_HDCP2TxFillCipherKey(MS_U8 u8PortIdx, MS_U8 *pu8Riv, MS_U8 *pu8KsXORLC128)
{
    return;
}

void MHal_HDCP_HDCP2TxGetCipherState(MS_U8 u8PortIdx, MS_U8 *pu8State)
{
    return;
}

void MHal_HDCP_HDCP2TxSetAuthPass(MS_U8 u8PortIdx, MS_BOOL bEnable)
{
    return;
}

void MHal_HDCP_HDCP2RxInit(MS_U8 u8PortIdx)
{
    MS_U16 u16BKOffset = 0x00;

    u16BKOffset = u8PortIdx * 0x300;

    // [1] Enable auto-clear SKE status when receiving ake_init; [2] Enable auto-clear SKE status when no hdcp22 capability
    MHalHdcpRegMaskWrite(DEF_HDCP22_RX_REG_BANK + u16BKOffset, 0x4E, 0x0006, 0x0006);
}

void MHal_HDCP_HDCP2RxProcessCipher(MS_U8 u8PortIdx, MS_U8* pu8Riv, MS_U8 *pu8ContentKey)
{
    MS_U8 cnt = 0;
    MS_U16 u16BKOffset = 0x00;
    MS_U16 u16RegOffset = 0x00;

    u16BKOffset = u8PortIdx * 0x300;
    u16RegOffset = u8PortIdx * 0x0C;

    //Ks^LC128
    for ( cnt = 0; cnt < (DEF_SIZE_OF_KSXORLC128>>1); cnt++)
        MHalHdcpRegWrite(DEF_HDCP22_RX_KEY_REG_BANK, u16RegOffset + 0x30 + (DEF_SIZE_OF_KSXORLC128 >> 1) - 1 - cnt, *(pu8ContentKey + cnt*2 + 1)|(*(pu8ContentKey + cnt*2)<<8));

    //Riv
    for ( cnt = 0; cnt < (DEF_SIZE_OF_RIV>>1); cnt++)
        MHalHdcpRegWrite(DEF_HDCP22_RX_KEY_REG_BANK, u16RegOffset + 0x38 + (DEF_SIZE_OF_RIV >> 1) - 1 - cnt, *(pu8Riv + cnt*2 + 1)|(*(pu8Riv + cnt*2)<<8));

    //Set SKE successful
    MHalHdcpRegMaskWrite(DEF_HDCP22_RX_REG_BANK + u16BKOffset, 0x4E, 0x0001, 0x0001);
}

void MHal_HDCP_HDCP2RxSetSKEPass(MS_U8 u8PortIdx, MS_BOOL bEnable)
{
    MS_U16 u16BKOffset = 0x00;

    u16BKOffset = u8PortIdx * 0x300;
    //Set SKE successful
    MHalHdcpRegMaskWrite(DEF_HDCP22_RX_REG_BANK + u16BKOffset, 0x4E, 0x0001, bEnable ? 0x0001 : 0x0000);
}

void MHal_HDCP_HDCP2RxFillCipherKey(MS_U8 u8PortIdx, MS_U8* pu8Riv, MS_U8 *pu8ContentKey)
{
    MS_U8 cnt = 0;
    MS_U16 u16BKOffset = 0x00;
    MS_U16 u16RegOffset = 0x00;

    u16BKOffset = u8PortIdx * 0x300;
    u16RegOffset = u8PortIdx * 0x0C;

    //Ks^LC128
    for ( cnt = 0; cnt < (DEF_SIZE_OF_KSXORLC128>>1); cnt++)
        MHalHdcpRegWrite(DEF_HDCP22_RX_KEY_REG_BANK, u16RegOffset + 0x30 + (DEF_SIZE_OF_KSXORLC128 >> 1) - 1 - cnt, *(pu8ContentKey + cnt*2 + 1)|(*(pu8ContentKey + cnt*2)<<8));

    //Riv
    for ( cnt = 0; cnt < (DEF_SIZE_OF_RIV>>1); cnt++)
        MHalHdcpRegWrite(DEF_HDCP22_RX_KEY_REG_BANK, u16RegOffset + 0x38 + (DEF_SIZE_OF_RIV >> 1) - 1 - cnt, *(pu8Riv + cnt*2 + 1)|(*(pu8Riv + cnt*2)<<8));
}

void MHal_HDCP_HDCP2RxGetCipherState(MS_U8 u8PortIdx, MS_U8 *pu8State)
{
    MS_U16 u16BKOffset = 0x00;
    //MS_U16 u16RegOffset = 0x00;

    u16BKOffset = u8PortIdx * 0x300;

    *pu8State = MHalHdcpRegRead(DEF_HDCP22_RX_REG_BANK + u16BKOffset, 0x4E) & 0x01;
}

MS_U32 MHal_HDCP_HDCP1TxEncrytionStatus(MS_U8 u8PortIdx, MS_U8 u8SetStatusFlag, MS_U32 u32SetStatus)
{
    MS_U32 u32GetStatus = 0;

    if(u8SetStatusFlag) // Set HDCP1 encrytion status
    {

    }

    // Get HDCP1 encrytion status

    return u32GetStatus;
}

MS_U32 MHal_HDCP_HDCP2TxEncrytionStatus(MS_U8 u8PortIdx, MS_U8 u8SetStatusFlag, MS_U32 u32SetStatus)
{
    MS_U32 u32GetStatus = 0;

    if(u8SetStatusFlag) // Set HDCP2 encrytion status
    {

    }

    // Get HDCP2 encrytion status

    return u32GetStatus;
}

MS_U32 MHal_HDCP_HDCPTxHDMIStatus(MS_U8 u8PortIdx, MS_U8 u8SetStatusFlag, MS_U32 u32SetStatus)
{
    MS_U32 u32GetStatus = 0;

    if(u8SetStatusFlag) // Set HDNI status
    {

    }

    // Get HDNI status

    return u32GetStatus;
}

#endif //#ifndef HAL_HDCP_C