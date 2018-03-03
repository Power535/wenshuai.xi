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


//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
#include "MsCommon.h"
#include "regCHIP.h"
#include "halCHIP.h"
#include "drvSYS.h"
#include "halSYS.h"
#include "drvMMIO.h"

#ifdef MSOS_TYPE_LINUX
#include "drvSYS_priv.h"
#endif

#ifdef CONFIG_MSTAR_DVFS_KERNEL_SUPPORT
#include "halSYS_DVFS.h"
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
#endif

#include "ULog.h"
//-------------------------------------------------------------------------------------------------
//  Driver Compiler Options
//-------------------------------------------------------------------------------------------------
#define REG_EFUSE_OUTC_15_00    0x202CUL
#define REG_EFUSE_OUTC_31_16    0x202EUL
#define REG_EFUSE_OUTC_47_32    0x2030UL
#define REG_EFUSE_OUTC_63_48    0x2032UL
#define REG_EFUSE_OUTD_15_00    0x2034UL
#define REG_EFUSE_OUTD_31_16    0x2036UL
#define REG_EFUSE_OUTD_47_32    0x2038UL
#define REG_EFUSE_OUTD_63_48    0x203AUL

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define BIT0    (0x0001UL)
#define BIT1    (0x0002UL)
#define BIT2    (0x0004UL)
#define BIT3    (0x0008UL)
#define BIT4    (0x0010UL)
#define BIT5    (0x0020UL)
#define BIT6    (0x0040UL)
#define BIT7    (0x0080UL)
#define BIT8    (0x0100UL)
#define BIT9    (0x0200UL)
#define BIT10   (0x0400UL)
#define BIT11   (0x0800UL)
#define BIT12   (0x1000UL)
#define BIT13   (0x2000UL)
#define BIT14   (0x4000UL)
#define BIT15   (0x8000UL)

#define SYS_READ_BYTE(addr)         ( READ_BYTE( u32hal_sys_baseaddr + (addr) ) )
#define SYS_WRITE_BYTE(addr, val)   { WRITE_BYTE( u32hal_sys_baseaddr + (addr), val) }

#define TAG_SYS "SYS"
//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------
static MS_VIRT _gMIO_efuse_MapBase = 0;

//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static SYS_Info       sysInfo;

static MS_VIRT u32hal_sys_baseaddr=0;

extern MS_U32  g_bDvfsInitFlag;

#ifdef MSOS_TYPE_LINUX
extern SYS_IO_PROC  g_SysIoProc;
#endif
//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------
static MS_U8 HAL_SYS_ReadByte(MS_U32 u32RegAddr);
static void HAL_SYS_WriteByte(MS_U32 u32RegAddr, MS_U8 u8Val);
static MS_U16 HAL_SYS_Read2Byte(MS_U32 u32RegAddr);
static void HAL_SYS_Write2Byte(MS_U32 u32RegAddr, MS_U16 u16Val);

MS_U8 HAL_SYS_ReadByte(MS_U32 u32RegAddr)
{
    MS_U8 u8Val = 0;

    if ((u32RegAddr == 0) || (u32hal_sys_baseaddr == 0))
    {
        ULOGD(TAG_SYS, "[SYS]%s access RIU register error!!\r\n",__FUNCTION__);
    }
    else
    {
        u8Val = SYS_READ_BYTE(((u32RegAddr) << 1) - ((u32RegAddr) & 1));
    }
    return u8Val;
}

void HAL_SYS_WriteByte(MS_U32 u32RegAddr, MS_U8 u8Val)
{
    if ((u32RegAddr == 0) || (u32hal_sys_baseaddr == 0))
    {
        ULOGD(TAG_SYS, "[SYS]%s access RIU register error!!\r\n",__FUNCTION__);
    }
    else
    {
        SYS_WRITE_BYTE(((u32RegAddr) << 1) - ((u32RegAddr) & 1), u8Val);
    }
}

MS_U16 HAL_SYS_Read2Byte(MS_U32 u32RegAddr)
{
    MS_U16 u16Val=0;

    if ((u32RegAddr == 0) || (u32hal_sys_baseaddr == 0))
    {
        ULOGD(TAG_SYS, "drvSYS access RIU register error!!\r\n");
    }
    else
    {
        u16Val = ((volatile MS_U16*)(u32hal_sys_baseaddr))[u32RegAddr];
    }
    return u16Val;
}

void HAL_SYS_Write2Byte(MS_U32 u32RegAddr, MS_U16 u16Val)
{
    if ((u32RegAddr == 0) || (u32hal_sys_baseaddr == 0))
    {
        ULOGD(TAG_SYS, "drvSYS access RIU register error!!\r\n");
    }
    else
    {
        ((volatile MS_U16*)(u32hal_sys_baseaddr))[u32RegAddr] = u16Val;
    }
}

void XIU_TimeOutINTHandler(InterruptNum eIntNum)
{
    MsOS_DisableInterrupt(eIntNum);
    ULOGD(TAG_SYS, "XIU Time Out Occurred!\n");
    ULOGD(TAG_SYS, "Address is 0x%x%x\n",HAL_SYS_Read2Byte(0x100113),HAL_SYS_Read2Byte(0x100112));
    ULOGD(TAG_SYS, "Address is 0x%x%x\n",HAL_SYS_Read2Byte(0x101276),HAL_SYS_Read2Byte(0x101274));
    MsOS_EnableInterrupt(eIntNum);
}
//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------
void SYS_Init(MS_PHY phy64baseaddr)
{
    u32hal_sys_baseaddr=phy64baseaddr;

    sysInfo.Chip.DeviceId = HAL_SYS_Read2Byte(0x001E00);
    sysInfo.Chip.Version  = (HAL_SYS_Read2Byte(0x001E02) & CHIP_VERSION_MASK)  >> CHIP_VERSION_SHFT;
    sysInfo.Chip.Revision = (HAL_SYS_Read2Byte(0x001E02) & CHIP_REVISION_MASK) >> CHIP_REVISION_SHFT;
    sysInfo.Chip.MIU1Base = HAL_MIU1_BASE;
    sysInfo.Chip.MIU1BusBase = HAL_MIU1_BUS_BASE;

    //HAL_SYS_SetTSOutClockPhase(0);

    // Enable XIU timeout
    HAL_SYS_Write2Byte(0x100100, 0x0001);
    HAL_SYS_Write2Byte(0x100128, 0xFFFF);
    HAL_SYS_Write2Byte(0x10012A, 0xFFFF);
    #if defined(CONFIG_FRC)
    MsOS_AttachInterrupt(E_FRCINT_IRQ_FRC_XIU_TIMEOUT, (InterruptCb)XIU_TimeOutINTHandler);
    MsOS_EnableInterrupt(E_FRCINT_IRQ_FRC_XIU_TIMEOUT);
    #else
    MsOS_AttachInterrupt(E_INT_FIQ_XIU_TIMEOUT, (InterruptCb)XIU_TimeOutINTHandler);
    MsOS_EnableInterrupt(E_INT_FIQ_XIU_TIMEOUT);
    #endif

    // 40nm MCP demod issue
    HAL_SYS_Write2Byte(0x11280E, (HAL_SYS_Read2Byte(0x11280E) | (BIT4)));

#ifdef CONFIG_MSTAR_DVFS_KERNEL_SUPPORT
    if(g_bDvfsInitFlag == 0)
    {
        SysDvfsProc();
        g_bDvfsInitFlag = 1;
    }
#endif

}


MS_U8 SYS_GetChipRev(void)
{
    return sysInfo.Chip.Revision;
}

MS_U16 SYS_GetChipID(void)
{
    return sysInfo.Chip.DeviceId;
}

const SYS_Info* SYS_GetInfo(void)
{
    return (const SYS_Info*)&sysInfo;
}


void SYS_ResetCPU(void)
{
/*
    // Switch CPU to XTAL clk
    TOP_REG(REG_TOP_MCU_USB_STC0) = (TOP_REG(REG_TOP_MCU_USB_STC0) & ~(TOP_MCU_CLK_MASK)) | TOP_MCU_CLK_DFT;

    // Reset CPU
    TOP_REG(REG_TOP_RESET_CPU0) = 0x029F;
    TOP_REG(REG_TOP_RESET_CPU0) = 0x029F | TOP_RESET_CPU0;
*/
}

void HAL_SYS_RFAGC_Tristate(MS_BOOL bEnable)
{
    MS_BOOL     bDmdAccessPreEnabled = TRUE;
    MS_U16      wReadRegisterData = 0;

    wReadRegisterData = HAL_SYS_Read2Byte(0x101E38);

    if((wReadRegisterData & (BIT9 | BIT8)) != 0)
    {
        HAL_SYS_Write2Byte(0x101E38, (wReadRegisterData & ~(BIT9 | BIT8)));
        bDmdAccessPreEnabled = FALSE;
    }

    if (bEnable)
    {
        HAL_SYS_Write2Byte(0x11286C, (HAL_SYS_Read2Byte(0x11286C) & ~(BIT0)));
    }
    else
    {
        HAL_SYS_Write2Byte(0x11286C, (HAL_SYS_Read2Byte(0x11286C) | (BIT0)));
    }

    if(bDmdAccessPreEnabled == FALSE)
    {
        HAL_SYS_Write2Byte(0x101E38, wReadRegisterData);
    }
}

void HAL_SYS_IFAGC_Tristate(MS_BOOL bEnable)
{
    MS_BOOL     bDmdAccessPreEnabled = TRUE;
    MS_U16      wReadRegisterData = 0;

    wReadRegisterData = HAL_SYS_Read2Byte(0x101E38);

    if((wReadRegisterData & (BIT9 | BIT8)) != 0)
    {
        HAL_SYS_Write2Byte(0x101E38, (wReadRegisterData & ~(BIT9 | BIT8)));
        bDmdAccessPreEnabled = FALSE;
    }

    if (bEnable)
    {
        HAL_SYS_Write2Byte(0x11286C, (HAL_SYS_Read2Byte(0x11286C) & ~(BIT4)));
    }
    else
    {
        HAL_SYS_Write2Byte(0x11286C, (HAL_SYS_Read2Byte(0x11286C) | (BIT4)));
    }

    if(bDmdAccessPreEnabled == FALSE)
    {
        HAL_SYS_Write2Byte(0x101E38, wReadRegisterData);
    }
}

void HAL_SYS_SetAGCPadMux(SYS_AGC_PAD_SET eAgcPadMux)
{
    MS_BOOL     bDmdAccessPreEnabled = TRUE;
    MS_U16      wReadRegisterData = 0;

    wReadRegisterData = HAL_SYS_Read2Byte(0x101E38);

    if((wReadRegisterData & (BIT9 | BIT8)) != 0)
    {
        HAL_SYS_Write2Byte(0x101E38, (wReadRegisterData & ~(BIT9 | BIT8)));
        bDmdAccessPreEnabled = FALSE;
    }

    if(eAgcPadMux == E_SYS_ATV_AGC_PAD_SET)         // ATV Mode
    {
        HAL_SYS_RFAGC_Tristate(TRUE);
        HAL_SYS_IFAGC_Tristate(TRUE);
    }
    else if(eAgcPadMux == E_SYS_DTV_AGC_PAD_SET)    // DTV Mode
    {
        HAL_SYS_RFAGC_Tristate(TRUE);
        HAL_SYS_IFAGC_Tristate(FALSE);
    }
    else if(eAgcPadMux == E_SYS_DTV_AGC_PAD_SET_ALL_OFF)    // DTV Mode
    {
        HAL_SYS_RFAGC_Tristate(TRUE);
        HAL_SYS_IFAGC_Tristate(TRUE);
    }
    else
    {
        ULOGD(TAG_SYS, "[ERROR] HAL_SYS_SetAGCPadMux: Invalid AGC Pad Selection\r\n");
    }

    if(bDmdAccessPreEnabled == FALSE)
    {
        HAL_SYS_Write2Byte(0x101E38, wReadRegisterData);
    }

}

MS_BOOL HAL_SYS_SetPCMCardDetectMode(SYS_PCM_CD_MODE ePCMCDMode)
{
    MS_BOOL ret = TRUE;

    if(ePCMCDMode >= E_PCM_CD_MAX)
    {
        ret = FALSE;
        return ret;
    }

    if(ePCMCDMode == E_PCM_CD_SINGLE)
    {
        HAL_SYS_Write2Byte(0x102A04, (HAL_SYS_Read2Byte(0x102A04) & ~(BIT13)));
    }
    else if(ePCMCDMode == E_PCM_CD_OR)
    {
        HAL_SYS_Write2Byte(0x102A04, (HAL_SYS_Read2Byte(0x102A04) | BIT13));
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

MS_BOOL HAL_SYS_DisableDebugPort(void)
{
    return FALSE;
}

MS_BOOL HAL_SYS_EnableDebugPort(void)
{
    return FALSE;
}


MS_BOOL HAL_SYS_SetPadMux(SYS_PAD_MUX_SET ePadMuxType,SYS_PAD_SEL ePadSel)
{
    MS_BOOL ret = TRUE;
    MS_U16  u16data=0, u16data1 = 0;

    if((ePadMuxType >= E_PAD_SET_MAX) || (ePadSel >= E_PAD_SEL_MAX))
    {
        ret = FALSE;
        return ret;
    }

    if(ePadMuxType == E_TS0_PAD_SET)
    {
        u16data =  HAL_SYS_Read2Byte(0x101EAE) & ~(BIT10|BIT9|BIT8);

        if(ePadSel == E_PARALLEL_IN)
        {
            u16data |= BIT8;
            HAL_SYS_Write2Byte(0x101EAE, u16data);
        }
        else if(ePadSel == E_SERIAL_IN)
        {
            u16data |= BIT9;
            HAL_SYS_Write2Byte(0x101EAE, u16data);
        }
        else if(ePadSel == E_SERIAL_IN_3_WIRE)
        {
            u16data |= BIT10;
            HAL_SYS_Write2Byte(0x101EAE, u16data);
        }
        else if(ePadSel == E_PARALLEL_IN_2nd_PORT) // PARALLEL_2nd_PORT
        {
            ret = FALSE;
        }
        else
        {
           ret = FALSE;
        }
    }
    else if(ePadMuxType == E_TS1_PAD_SET)
    {
        u16data = HAL_SYS_Read2Byte(0x101EAE) & ~(BIT13|BIT12|BIT11);
        u16data1 = HAL_SYS_Read2Byte(0x101E80) & ~(BIT6|BIT5|BIT4);

        switch(ePadSel)
        {
            case E_PARALLEL_IN:
                u16data |= BIT11;
                break;
            case E_PARALLEL_OUT:
            case E_PARALLEL_OUT_INTDMD:
                u16data |= BIT12;
                break;
            case E_SERIAL_IN:
                u16data |= (BIT11|BIT12);
                break;
            case E_PARALLEL_OUT_TSO:
                u16data1 |= (BIT4|BIT5);
                break;
            case E_PARALLEL_OUT_SER2PAR:
                u16data1 |= BIT6;
                break;
            case E_PARALLEL_OUT_SER2PAR1:
                u16data1 |= (BIT4|BIT6);
                break;
            case E_SERIAL_IN_3_WIRE:
                u16data |= BIT13;
                break;
            default:
                return FALSE;
        }
        HAL_SYS_Write2Byte(0x101EAE, u16data);
        HAL_SYS_Write2Byte(0x101E80, u16data1);
    }
    else if(ePadMuxType == E_TS2_PAD_SET)
    {
        u16data = HAL_SYS_Read2Byte(0x101EB4) & ~(BIT12|BIT13|BIT14);

        if(ePadSel == E_SERIAL_IN)
        {
            HAL_SYS_Write2Byte(0x101EB4, u16data|BIT12);
        }
        else if(ePadSel == E_PARALLEL_IN)
        {
            HAL_SYS_Write2Byte(0x101EB4, u16data|BIT13);
        }
        else
        {
            ret = FALSE;
        }
    }
    else if(ePadMuxType == E_TS3_PAD_SET)
    {
        u16data = HAL_SYS_Read2Byte(0x101ECE) & ~(BIT12|BIT13|BIT14|BIT15);
        u16data1 = HAL_SYS_Read2Byte(0x101E20) & ~(BIT9|BIT10);

        switch(ePadSel)
        {
            case E_PARALLEL_IN:
                u16data |= BIT13;
                break;
            case E_PARALLEL_OUT:
            case E_PARALLEL_OUT_INTDMD:
                u16data |= (BIT12|BIT14);
                break;
            case E_SERIAL_IN:
                u16data |= BIT12;
                break;
            case E_PARALLEL_OUT_TSO:
                u16data1 |= BIT10;
                break;
            case E_PARALLEL_OUT_SER2PAR:
                u16data |= (BIT12|BIT13|BIT14);
                break;
            case E_PARALLEL_OUT_SER2PAR1:
                u16data |= BIT15;
                break;
            case E_SERIAL_IN_3_WIRE:
                u16data |= (BIT13|BIT14);
                break;
            default:
                return FALSE;
        }
        HAL_SYS_Write2Byte(0x101ECE, u16data);
        HAL_SYS_Write2Byte(0x101E20, u16data1);
    }
    else if(ePadMuxType == E_TS4_PAD_SET)
    {
      u16data = HAL_SYS_Read2Byte(0x101E80) & ~(BIT9|BIT10|BIT11);
        if(ePadSel == E_SERIAL_IN)
        {
            HAL_SYS_Write2Byte(0x101E80, u16data|BIT9);
        }
        else
        {
            return FALSE;
        }
    }
    else if(ePadMuxType == E_TS5_PAD_SET)
    {
        u16data = HAL_SYS_Read2Byte(0x101E80) & ~BIT12;
        if(ePadSel == E_SERIAL_IN)
        {
            HAL_SYS_Write2Byte(0x101E80, u16data|BIT12);
        }
        else
        {
            return FALSE;
        }
    }
    else if(ePadMuxType == E_CA_CI_PAD_SET)
    {
        if(ePadSel == E_CA_CI_PAD_CI)
        {
            HAL_SYS_Write2Byte(0x101ec8, (HAL_SYS_Read2Byte(0x101ec8) | BIT5));
        }
        else if(ePadSel == E_CA_CI_PAD_NONE)
        {
            HAL_SYS_Write2Byte(0x101ec8, (HAL_SYS_Read2Byte(0x101ec8) & ~BIT5));
        }
    }
    else if(ePadMuxType == E_SC_PAD_SET)
    {
        u16data =  HAL_SYS_Read2Byte(0x101EDC) & ~(BIT5|BIT4);

        if(ePadSel == E_SC_PAD_PCM)
        {
            u16data |= BIT4;
            HAL_SYS_Write2Byte(0x101EDC, u16data);
            HAL_SYS_Write2Byte(0x101EC8, (HAL_SYS_Read2Byte(0x101EC8) & ~BIT5));
        }
        else if(ePadSel == E_SC_PAD_TS1)
        {
            u16data |= BIT5;
            HAL_SYS_Write2Byte(0x101EDC, u16data);
            HAL_SYS_Write2Byte(0x101E0C, (HAL_SYS_Read2Byte(0x101E0C) | (BIT3|BIT6)));
            HAL_SYS_Write2Byte(0x101E24, (HAL_SYS_Read2Byte(0x101E24) & ~(BIT0|BIT1|BIT2)));
            HAL_SYS_Write2Byte(0x101EAE, (HAL_SYS_Read2Byte(0x101EAE) & ~(BIT11|BIT12|BIT13)));
        }
    }
    else if(ePadMuxType == E_MSPI_PAD_SET)
    {
        if(ePadSel == E_MSPI_PAD_ON)
        {
            u16data |= BIT2;
            HAL_SYS_Write2Byte(0x101EB4, u16data);
        }
        else if(ePadSel == E_MSPI_PAD_GPIO)
        {
            u16data = HAL_SYS_Read2Byte(0x101EB4) & ~(BIT10|BIT1|BIT2|BIT3);
            HAL_SYS_Write2Byte(0x101EB4, u16data);
        }
    }
    else
    {
        ret = FALSE;
    }

    return ret;
}

MS_BOOL HAL_SYS_SetTSOutClockPhase(MS_U16 u16Val)
{
    if(u16Val > 32)
    {
        return FALSE;
    }

    if(u32hal_sys_baseaddr == 0)
    {
        return FALSE;
    }

    HAL_SYS_Write2Byte(0x103300, HAL_SYS_Read2Byte(0x103300) | BIT12);
    HAL_SYS_Write2Byte(0x10330a, HAL_SYS_Read2Byte(0x10330a) & ~(BIT12|BIT11|BIT10|BIT9|BIT8));
    HAL_SYS_Write2Byte(0x10330a, HAL_SYS_Read2Byte(0x10330a) | (u16Val*0x100));

    return TRUE;
}

MS_U8 SYS_VIF_ReadByteByVDMbox(MS_U32 u32Reg)
{
    ULOGD(TAG_SYS, "%s not support!!!\n", __FUNCTION__);
    return 0;
}

void SYS_VIF_WriteByteByVDMbox(MS_U32 u32Reg, MS_U8 u8Val)
{
    ULOGD(TAG_SYS, "%s not support!!!\n", __FUNCTION__);
}

void SYS_VIF_WriteByteMaskByVDMbox(MS_U32 u32Reg, MS_U8 u8Val, MS_U8 u8Mask)
{
    ULOGD(TAG_SYS, "%s not support!!!\n", __FUNCTION__);
}

void SYS_VIF_WriteRegBitByVDMbox(MS_U32 u32Reg, MS_U8 bEnable, MS_U8 u8Mask)
{
    ULOGD(TAG_SYS, "%s not support!!!\n", __FUNCTION__);
}

MS_U16 SYS_VIF_Read2ByteByVDMbox(MS_U32 u32Reg)
{
    ULOGD(TAG_SYS, "%s not support!!!\n", __FUNCTION__);
    return 0;
}

void HAL_SYS_SetEfuseIOMapBase(MS_VIRT u32Base)
{
    _gMIO_efuse_MapBase = u32Base;
}

MS_U16 HAL_SYS_EfuseRead2Byte(MS_U32 u32RegAddr)
{
    return ((volatile MS_U16*)(_gMIO_efuse_MapBase))[u32RegAddr];
}

MS_U16 HAL_SYS_EfuseWrite2Byte(MS_U32 u32RegAddr, MS_U16 u16Val)
{
    return ((volatile MS_U16*)(_gMIO_efuse_MapBase))[u32RegAddr] = u16Val;
}

void HAL_SYS_SetOtpIOMapBase(MS_VIRT u32Base)
{
    // Not Implemented
}

MS_BOOL HAL_SYS_Query(E_SYS_QUERY id)
{
   MS_BOOL bRet = FALSE;

    //
    // get efuse settings
    //

    if(_gMIO_efuse_MapBase == 0)
    {
        MS_VIRT  dwEfuseIoBaseAddress = 0;
        MS_PHY  dwEfuseIoBaseSize = 0;

        if(MDrv_MMIO_GetBASE(&dwEfuseIoBaseAddress, &dwEfuseIoBaseSize, MS_MODULE_PM) == FALSE)
        {
            printf("[ERROR][SYS] Get IO Base Address Failed\n");
            MS_ASSERT(0);
            return FALSE;
        }

        HAL_SYS_SetEfuseIOMapBase(dwEfuseIoBaseAddress);
    }

    //
    // determine
    //
    switch (id)
    {
        case E_SYS_QUERY_TTS_SUPPORTED:
        {
            //=============================
            // xxxx-xxxx-xxxx-vmmm
            //   Valid0 : reg_efuse_128x32_6a[3]
            //   Mode0 : reg_efuse_128x32_6a[2~0]
            // xxxx-xxxx-vmmm-xxxx
            //   Valid1 : reg_efuse_128x32_6a[7]
            //   Mode1 : reg_efuse_128x32_6a[6~4]
            //=============================
            MS_U16 u16_efs128x32_rdata_lo = 0;
            MS_U16 u16_efs128x32_rdata_hi = 0;
            MS_U32 u32timeout_count = 0;
            MS_BOOL bTTSValid0=0, bTTSValid1=0;
            MS_U8 u8TTSMode0=0, u8TTSMode1=0;

            //====================
            //trigger to read efuse data
            //from 128x32 sub-bank 6a
            //====================
            HAL_SYS_EfuseWrite2Byte(REG_RESERVED4_15_0, (0x6A*0x04) | 0x2000 );
            while ((HAL_SYS_EfuseRead2Byte(REG_RESERVED4_15_0) & FLAG_EFUSE_DATA_BUSY) != 0)
            {
                if (u32timeout_count++ > MAX_TIMEOUT_COUNT)
                {
                    printf ("[Error] %s(%d) Read time out!!\n", __FUNCTION__, __LINE__);
                    return 0;
                }
                MsOS_DelayTaskUs(10);
            }

            //====================
            //read efuse data
            //====================
            u16_efs128x32_rdata_lo = HAL_SYS_EfuseRead2Byte(REG_EFUSE_128_RD_15_0);
            u16_efs128x32_rdata_hi = HAL_SYS_EfuseRead2Byte(REG_EFUSE_128_RD_31_16);

            //====================
            //judge TTS Support mode
            //====================
            bTTSValid0 = (((u16_efs128x32_rdata_lo>>0) & 0x08)!=0) ? TRUE : FALSE;
            u8TTSMode0 = (u16_efs128x32_rdata_lo>>0) & 0x07;
            bTTSValid1 = (((u16_efs128x32_rdata_lo>>4) & 0x08)!=0) ? TRUE : FALSE;
            u8TTSMode1 = (u16_efs128x32_rdata_lo>>4) & 0x07;
            bRet =(MS_BOOL)((bTTSValid1) ?  u8TTSMode1 : ((bTTSValid0)? u8TTSMode0 : 0));
        }
            break;

        case E_SYS_QUERY_SECURED_IC_SUPPORTED:
            bRet = (HAL_SYS_Read2Byte(0x0038E0) & (BIT0)) == 0x0 ? FALSE : TRUE;
            break;

        default:
            ULOGD(TAG_SYS, "[SYS] Unknown query!\n");
            bRet = TRUE;
    }

    return bRet;
}

MS_U32 HAL_SYS_ReadRSAKey(MS_U16 u16ReadAddr)
{
    //not implement yet
	return FALSE;
}

MS_BOOL HAL_SYS_PadMuxTableSuspend(void)
{
    printf("[%s]- not support\n", __func__);

    return TRUE;
}

MS_BOOL HAL_SYS_PadMuxTableResume(void)
{
    printf("[%s]- not support\n", __func__);
    return TRUE;
}

MS_BOOL HAL_SYS_SetTSClockPhase(SYS_PAD_MUX_SET ePadMuxType,MS_U16 u16Val)
{
    if(ePadMuxType >= E_PAD_SET_MAX)
    {
        return FALSE;
    }

    if(u16Val > 31)
    {
        return FALSE;
    }

    if(u32hal_sys_baseaddr == 0)
    {
        return FALSE;
    }

    MS_U16 wReadRegisterData = 0;
    if(ePadMuxType == E_TS0_PAD_SET)
    {
        wReadRegisterData = HAL_SYS_Read2Byte(0x101EAE) & (BIT10|BIT9|BIT8);
        if((wReadRegisterData) == BIT9){
            HAL_SYS_Write2Byte(0x110A00, (u16Val & 0x1F) & ~(BIT5|BIT6));
        }else{
            HAL_SYS_Write2Byte(0x110A00, (u16Val & 0x1F) | BIT5);
        }
    }
    else if(ePadMuxType == E_TS1_PAD_SET)
    {
        wReadRegisterData = HAL_SYS_Read2Byte(0x101EAE) & (BIT13|BIT12|BIT11);
        if(wReadRegisterData == (BIT11|BIT12)){
            HAL_SYS_Write2Byte(0x110A02, (u16Val & 0x1F) & ~(BIT5|BIT6));
        }else{
            HAL_SYS_Write2Byte(0x110A02, (u16Val & 0x1F) | BIT5);
        }
    }
    else if(ePadMuxType == E_TS2_PAD_SET)
    {
        wReadRegisterData = HAL_SYS_Read2Byte(0x101EAE) & (BIT14|BIT15);
        if(wReadRegisterData == BIT14){
            HAL_SYS_Write2Byte(0x110A04, (u16Val & 0x1F) & ~(BIT5|BIT6));
        }else{
            HAL_SYS_Write2Byte(0x110A04, (u16Val & 0x1F) | BIT5);
        }
    }
    else if(ePadMuxType == E_TS3_PAD_SET)
    {
        wReadRegisterData = HAL_SYS_Read2Byte(0x101ECE) & (BIT12|BIT13|BIT14|BIT15);
        if(wReadRegisterData == BIT12){
            HAL_SYS_Write2Byte(0x110A06, (u16Val & 0x1F) & ~(BIT5|BIT6));
        }else{
            HAL_SYS_Write2Byte(0x110A06, (u16Val & 0x1F) | BIT5);
        }
    }
    else if(ePadMuxType == E_TS4_PAD_SET)
    {
        wReadRegisterData = HAL_SYS_Read2Byte(0x101E80) & (BIT10|BIT11);
        if(wReadRegisterData == BIT10){
            HAL_SYS_Write2Byte(0x110A08, (u16Val & 0x1F) & ~(BIT5|BIT6));
        }else{
            HAL_SYS_Write2Byte(0x110A08, (u16Val & 0x1F) | BIT5);
        }
    }
    else if(ePadMuxType == E_TS5_PAD_SET)
    {
        wReadRegisterData = HAL_SYS_Read2Byte(0x101E80) & (BIT12|BIT13);
        if(wReadRegisterData == BIT12){
            HAL_SYS_Write2Byte(0x110A0A, (u16Val & 0x1F) & ~(BIT5|BIT6));
        }else{
            HAL_SYS_Write2Byte(0x110A0A, (u16Val & 0x1F) | BIT5);
        }
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}

MS_U32 HAL_SYS_QueryDolbyHashInfo(E_SYS_DOLBY_HASH_INFO index)
{

    MS_U16 hash_rdata_lo = 0;
    MS_U16 hash_rdata_hi = 0;
    MS_U32 u32Ret = 0;
    MS_U32 u32timeout_count = 0;

    if(_gMIO_efuse_MapBase == 0)
    {
        MS_VIRT  dwEfuseIoBaseAddress = 0;
        MS_PHY  dwEfuseIoBaseSize = 0;

        if(MDrv_MMIO_GetBASE(&dwEfuseIoBaseAddress, &dwEfuseIoBaseSize, MS_MODULE_PM) == FALSE)
        {
            ULOGD(TAG_SYS, "[ERROR][SYS] Get IO Base Address Failed\n");
            MS_ASSERT(0);
            return 0;
        }

        HAL_SYS_SetEfuseIOMapBase(dwEfuseIoBaseAddress);
    }

    //Bank 2, 0x29 = 2008
    HAL_SYS_EfuseWrite2Byte(REG_RESERVED4_31_16, (0X4*2) | 0x2000UL );

    while ((HAL_SYS_EfuseRead2Byte(REG_RESERVED4_31_16) & FLAG_EFUSE_DATA_BUSY) != 0)
    {
        if (u32timeout_count++ > MAX_TIMEOUT_COUNT)
        {
            printf ("[Error] %s(%d) Read time out!!\n", __FUNCTION__, __LINE__);
            return 0;
        }
        MsOS_DelayTaskUs(10);
    }

    hash_rdata_lo = HAL_SYS_EfuseRead2Byte(REG_EFUSE_32_RD_15_0);
    hash_rdata_hi = HAL_SYS_EfuseRead2Byte(REG_EFUSE_32_RD_31_16);

    switch(index)
    {
    case E_SYS_DOLBY_VERSION:
        //Bank 2 [12:10], [3:0],
        u32Ret = (MS_U32)(((hash_rdata_lo >> 10) & (0x7)) << 0x4);
        u32Ret = u32Ret | (MS_U32)(((hash_rdata_lo)& 0xF));
        break;

    case E_SYS_DOLBY_CONTROL_BIT:
        //Bank 2 [13]
        u32Ret = (MS_U32)((hash_rdata_lo >> 13) & (0x01)); //Bank 2 [13]
        break;

    case E_SYS_DOLBY_REVERSE_BIT:
        //Bank 2 [14]
        u32Ret = (MS_U32)((hash_rdata_lo >> 14) & (0x01)); // Bank 2 [14]
        break;

    default:
        printf ("[Error] %s(%d) Unknown Cmd: 0x%x\n", __FUNCTION__, __LINE__, index);
        break;
    }

    return u32Ret;
}

void HAL_SYS_SetChipType(E_SYS_CHIP_TYPE Type)
{

}


E_SYS_CHIP_TYPE HAL_SYS_GetChipType(void)
{
    MS_U16 hash_rdata_lo = 0;
    MS_U16 hash_rdata_hi = 0;
    MS_U32 u32timeout_count = 0;

    if(_gMIO_efuse_MapBase == 0)
    {
        MS_VIRT  dwEfuseIoBaseAddress = 0;
        MS_PHY  dwEfuseIoBaseSize = 0;

        if(MDrv_MMIO_GetBASE(&dwEfuseIoBaseAddress, &dwEfuseIoBaseSize, MS_MODULE_PM) == FALSE)
        {
            ULOGD(TAG_SYS, "[ERROR][SYS] Get IO Base Address Failed\n");
            MS_ASSERT(0);
            return 0;
        }

        HAL_SYS_SetEfuseIOMapBase(dwEfuseIoBaseAddress);
    }

    //Bank 0, 0x29 = 2000
    HAL_SYS_EfuseWrite2Byte(REG_RESERVED4_31_16, (0X4*0) | 0x2000 );

    while ((HAL_SYS_EfuseRead2Byte(REG_RESERVED4_31_16) & FLAG_EFUSE_DATA_BUSY) != 0)
    {
        if (u32timeout_count++ > MAX_TIMEOUT_COUNT)
        {
            printf ("[Error] %s(%d) Read time out!!\n", __FUNCTION__, __LINE__);
            return 0;
        }
        MsOS_DelayTaskUs(10);
    }

    hash_rdata_lo = HAL_SYS_EfuseRead2Byte(REG_EFUSE_32_RD_15_0);
    hash_rdata_hi = HAL_SYS_EfuseRead2Byte(REG_EFUSE_32_RD_31_16);

    if(((hash_rdata_lo >> 11)& 0x01) == 0x01) ////Bank 0 [11]
    {
        return E_SYS_CHIP_STB;
    }
    else
    {
        return E_SYS_CHIP_TV;
    }
}

//RTC0 Bank 0x12 : h0010 dummy register
// merge the setting from monaco, confirm with yenfu and acem ok
MS_U16 HAL_SYS_ReadBrickTerminatorStatus(void)
{
    MS_U16 u16Status = 0;

    u16Status = HAL_SYS_Read2Byte(0x001220);

	return u16Status;
}

void HAL_SYS_WriteBrickTerminatorStatus(MS_U16 u16Status)
{
    HAL_SYS_Write2Byte(0x001220, u16Status);
}

void HAL_SYS_GetEfuseDid(MS_U16 *u16efuse_did)
{
    u16efuse_did[0] = HAL_SYS_Read2Byte(0x003800);
    u16efuse_did[1] = HAL_SYS_Read2Byte(0x003802);
    u16efuse_did[2] = HAL_SYS_Read2Byte(0x003804);
    u16efuse_did[3] = HAL_SYS_Read2Byte(0x003806);
}

MS_BOOL HAL_SYS_ReadEfuseHDCPKey(MS_U16 u16ReadAddr, MS_U32 *u32HDCPKey)
{
    MS_U16 hdcp_rdata_lo = 0;
    MS_U16 hdcp_rdata_hi = 0;
    MS_U32 u32timeout_count = 0;
    if(_gMIO_efuse_MapBase == 0)
    {
        MS_VIRT  dwEfuseIoBaseAddress = 0;
        MS_PHY  dwEfuseIoBaseSize = 0;

        if(MDrv_MMIO_GetBASE(&dwEfuseIoBaseAddress, &dwEfuseIoBaseSize, MS_MODULE_PM) == FALSE)
        {
            ULOGD(TAG_SYS, "[ERROR][SYS] Get IO Base Address Failed\n");
            MS_ASSERT(0);
            return FALSE;
        }

        HAL_SYS_SetEfuseIOMapBase(dwEfuseIoBaseAddress);
    }

    if(u16ReadAddr > 75)
    {
        ULOGD(TAG_SYS, "[ERROR][SYS] Read Address overflow\n");
        MS_ASSERT(0);
        return FALSE;
    }


    HAL_SYS_EfuseWrite2Byte(REG_RESERVED4_15_0, (0X4*u16ReadAddr) | 0x2000 );

    while ((HAL_SYS_EfuseRead2Byte(REG_RESERVED4_15_0) & FLAG_EFUSE_DATA_BUSY) != 0)
    {
        if (u32timeout_count++ > MAX_TIMEOUT_COUNT)
        {
            printf ("[Error] %s(%d) Read time out!!\n", __FUNCTION__, __LINE__);
            return 0;
        }
        MsOS_DelayTaskUs(10);
    }

    hdcp_rdata_lo = HAL_SYS_EfuseRead2Byte(REG_EFUSE_128_RD_15_0);
    hdcp_rdata_hi = HAL_SYS_EfuseRead2Byte(REG_EFUSE_128_RD_31_16);

    *u32HDCPKey = (MS_U32)((hdcp_rdata_hi<<16)|hdcp_rdata_lo);
    return TRUE;
}

static void HAL_SYS_WOL_ISR(InterruptNum eIntNum)
{
    if((HAL_SYS_ReadByte(0x0e1c)&(BIT2))==(BIT2))//reg_wk_irq_final_status[2]: WOL
    {
        //step1: set WOL_WAKE_UP_SOC(PM_SPI_WPN) from High to Low to inform ext. MICOM
        HAL_SYS_WriteByte(0x0f2c, HAL_SYS_ReadByte(0x0f2c)&(~BIT1));
        //step2: clear WOL interrupt
        //2-1 WOL part
        HAL_SYS_WriteByte(0x121a46, HAL_SYS_ReadByte(0x121a46)&(~BIT7));
        HAL_SYS_WriteByte(0x121a46, HAL_SYS_ReadByte(0x121a46)|(BIT7));
        //2-2 PM part
        HAL_SYS_WriteByte(0x0e1c, HAL_SYS_ReadByte(0x0e1c)|(BIT2)); //PM
        HAL_SYS_WriteByte(0x2b38, HAL_SYS_ReadByte(0x2b38)|(BIT2)); //IRQ

        MsOS_EnableInterrupt(E_INT_IRQ_PMSLEEP);
    }
}

void HAL_SYS_EnableWkEventWOL(void)
{
    //set WOL_WAKE_UP_SOC(PM_SPI_WPN) to High
    HAL_SYS_WriteByte(0x0f2c, HAL_SYS_ReadByte(0x0f2c)|(BIT1));

    //install ISR
    MsOS_AttachInterrupt(E_INT_IRQ_PMSLEEP, HAL_SYS_WOL_ISR);
    MsOS_EnableInterrupt(E_INT_IRQ_PMSLEEP);

    // WOL enable interrupt
    HAL_SYS_WriteByte(0x0e10, HAL_SYS_ReadByte(0x0e10)&(~BIT2)); //WOL enable interrupt
    HAL_SYS_WriteByte(0x0e12, HAL_SYS_ReadByte(0x0e12)&(~BIT2)); //WOL irq polarity

    // WOL enable
    HAL_SYS_WriteByte(0x121A47, HAL_SYS_ReadByte(0x121A47) | BIT5); //avoid to wake-up in unexpect condition
    HAL_SYS_WriteByte(0x121A46, (BIT0)); // Enable WOL
}

void HAL_SYS_DisableWkEventWOL(void)
{
    //set WOL_WAKE_UP_SOC(PM_SPI_WPN) to High
    HAL_SYS_WriteByte(0x0f2c, HAL_SYS_ReadByte(0x0f2c)|(BIT1));

    HAL_SYS_WriteByte(0x0e10, HAL_SYS_ReadByte(0x0e10)|(BIT2)); //WOL disable interrupt
    HAL_SYS_WriteByte(0x121a46, HAL_SYS_ReadByte(0x121a46)&(~BIT7)); //<<WOL INT clear>>
    HAL_SYS_WriteByte(0x121a46, HAL_SYS_ReadByte(0x121a46)|(BIT7));
    HAL_SYS_WriteByte(0x121A46, HAL_SYS_ReadByte(0x121A46) & ~BIT0); // Disable WOL
}

void HAL_SYS_ResetStatusWOL(void)
{
    //step1: set WOL_WAKE_UP_SOC(PM_SPI_WPN) to High
    HAL_SYS_WriteByte(0x0f2c, HAL_SYS_ReadByte(0x0f2c)|(BIT1));

    //step2: clear WOL interrupt
    //WOL part
    HAL_SYS_WriteByte(0x121a46, HAL_SYS_ReadByte(0x121a46)&(~BIT7));
    HAL_SYS_WriteByte(0x121a46, HAL_SYS_ReadByte(0x121a46)|(BIT7));
    //PM part
    HAL_SYS_WriteByte(0x0e1c, HAL_SYS_ReadByte(0x0e1c)|(BIT2)); //PM
    HAL_SYS_WriteByte(0x2b38, HAL_SYS_ReadByte(0x2b38)|(BIT2)); //IRQ
}

MS_BOOL HAL_SYS_GetStatusWOL(void)
{
    MS_BOOL bRET = 0;

    if((HAL_SYS_ReadByte(0x121A46) & BIT0) == BIT0 )
    {
        bRET = 1;
    }

    return bRET;
}

//=================================================================================================
#ifdef CONFIG_MSTAR_DVFS_KERNEL_SUPPORT
static MS_S32 _s32SAR_Dvfs_Mutex;
static MSTAR_DVFS_INFO hMstarDvfsInfo =
{
    .bDvfsInitOk = 0,
    .dwVidSetting = 0,
    .dwPowerChipId = CONFIG_DVFS_CHIP_ID_UNKNOWN,
};

//#if (CONFIG_DVFS_CPU_POWER_I2C_ENABLE | CONFIG_DVFS_CORE_POWER_I2C_ENABLE)
//extern MS_BOOL MApi_SWI2C_ReadBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8AddrNum, MS_U8* paddr, MS_U16 u16size, MS_U8* pu8data);
//extern MS_BOOL MApi_SWI2C_WriteBytes(MS_U16 u16BusNumSlaveID, MS_U8 u8addrcount, MS_U8* pu8addr, MS_U16 u16size, MS_U8* pu8data);
//#endif

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsProc
/// @brief \b Function  \b Description: Read T-Sensor to Handle DVFS Flow
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////

static pthread_t   hDvfsThread;
static void *SysDvfsThreadProc(void *pThreadInfo)
{
    int                     hFileHandle;
    int                     dwDataLength = 0;
    unsigned int            dwLoopCounter = 0;
    char                    sFileName[48] = "/proc/on_demand_ctl\0";
    MSTAR_DVFS_READ_INFO    hMstarDvfsReadInfo;
    MSTAR_DVFS_WRITE_INFO   hMstarDvfsWriteInfo;

    while(1)
    {
        if((g_SysIoProc.SysSwI2CReadBytes != 0) && (g_SysIoProc.SysSwI2CWriteBytes != 0))
        {
            hFileHandle = open(sFileName, (O_RDWR | O_EXCL));
            if(hFileHandle == -1)
            {
                DVFS_DEBUG("\033[35m[ERROR] Cannot Open File: %s\033[m\n", sFileName);
            }
            else
            {
                while(1)
                {
                    if(hMstarDvfsInfo.bDvfsInitOk == 0)
                    {
                        SysDvfsInit();
                    }

                    dwDataLength = read(hFileHandle, (void *) &hMstarDvfsReadInfo, sizeof(hMstarDvfsReadInfo));

                    DVFS_DEBUG("\033[35m[INFO] Read Data Length: %d\033[m\n", dwDataLength);
                    DVFS_DEBUG("\033[35m[INFO] Voltage: %d0 mV\033[m\n", hMstarDvfsReadInfo.dwVoltage);
                    DVFS_DEBUG("\033[35m[INFO] dwCluster: %d \033[m\n", hMstarDvfsReadInfo.dwCluster);

                    if(hMstarDvfsReadInfo.dwVoltageType == 0)
                    {
                        DVFS_DEBUG("\033[35m[INFO] Voltage Type: CPU Power\033[m\n");
                    }
                    else if(hMstarDvfsReadInfo.dwVoltageType == 1)
                    {
                        DVFS_DEBUG("\033[35m[INFO] Voltage Type: Core Power\033[m\n");
                    }
                    else
                    {
                        DVFS_DEBUG("\033[35m[INFO] Voltage Type: Unknown\033[m\n");
                    }

                    DVFS_DEBUG("\033[35m[INFO] Data Exchange Count (Read): %d\033[m\n", hMstarDvfsReadInfo.dwDataExchangeCount);

                    if(hMstarDvfsReadInfo.dwVoltageType == CONFIG_DVFS_CPU_POWER)
                    {
                        SysDvfsCpuPowerAdjustment(hMstarDvfsReadInfo.dwVoltage, hMstarDvfsReadInfo.dwCluster);
                    }
                    else if(hMstarDvfsReadInfo.dwVoltageType == CONFIG_DVFS_CORE_POWER)
                    {
                        SysDvfsCorePowerAdjustment(hMstarDvfsReadInfo.dwVoltage, hMstarDvfsReadInfo.dwCluster);
                    }
                    else if(hMstarDvfsReadInfo.dwVoltageType == CONFIG_DVFS_STR_INIT)
                    {
                        SysDvfsInit();
                    }

                    hMstarDvfsWriteInfo.dwDataExchangeCount = hMstarDvfsReadInfo.dwDataExchangeCount;
                    hMstarDvfsWriteInfo.dwDataExchangeResult = 0;
                    hMstarDvfsWriteInfo.dwCluster = hMstarDvfsReadInfo.dwCluster;
                    dwDataLength = write(hFileHandle, (void *)&hMstarDvfsWriteInfo, sizeof(hMstarDvfsWriteInfo));

                    DVFS_DEBUG("\033[35m[INFO] Write Data Length: %d\033[m\n", dwDataLength);
                    DVFS_DEBUG("\033[35m[INFO] Data Exchange Count (Write): %d\033[m\n", hMstarDvfsWriteInfo.dwDataExchangeCount);
                    DVFS_DEBUG("\033[35m[INFO] Data Exchange Result: %d\033[m\n", hMstarDvfsWriteInfo.dwDataExchangeResult);
                }

                close(hFileHandle);
            }
        }

        dwLoopCounter ++;
        if(dwLoopCounter > 50)
        {
            pthread_exit(NULL);
            break;
        }

        MsOS_DelayTaskUs(100000);
    }

    return NULL;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsProc
/// @brief \b Function  \b Description:
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
void SysDvfsProc(void)
{
    if(*(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x100500 << 1)) == CONFIG_DVFS_ENABLE_PATTERN)
    {
        if(hMstarDvfsInfo.bDvfsInitOk == 0)
        {
            int dwErrorCode = 0;
            char sDvfsThreadName[20] = "MstarDvfsThread\0";
            pthread_attr_t attr;

            _s32SAR_Dvfs_Mutex = MsOS_CreateMutex(E_MSOS_FIFO, "Mutex SAR_DVFS", MSOS_PROCESS_SHARED);
            MS_ASSERT(_s32SAR_Dvfs_Mutex >= 0);

            if (FALSE == MsOS_ObtainMutex(_s32SAR_Dvfs_Mutex, CONFIG_DVFS_MUTEX_WAIT_TIME))
            {
                DVFS_INFO("\033[37m[DVFS] Mutex Lock Fail\033[m\n");
                MsOS_ReleaseMutex(_s32SAR_Dvfs_Mutex);
                return;
            }

            //SysDvfsInit();

            pthread_attr_init(&attr);
            pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

            dwErrorCode = pthread_create(
                                &hDvfsThread,
                                &attr,
                                SysDvfsThreadProc,
                                (void *) sDvfsThreadName);

            if(dwErrorCode)
            {
                DVFS_DEBUG("\033[33m[ERROR] Create DVFS Thread Failed\033[m\n");
                MsOS_ReleaseMutex(_s32SAR_Dvfs_Mutex);
                return;
            }

            MsOS_ReleaseMutex(_s32SAR_Dvfs_Mutex);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsInit
/// @brief \b Function  \b Description: Read T-Sensor to Handle DVFS Flow
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
void SysDvfsInit(void)
{
    SysDvfsCpuPowerInit();
    SysDvfsCorePowerInit();

    hMstarDvfsInfo.bDvfsInitOk = 1;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsCpuPowerAdjustment
/// @brief \b Function  \b Description: Update Output Voltage Level in External Power Chip
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
void SysDvfsCpuPowerAdjustment(MS_U32 dwCpuPowerVoltage, MS_U8 byCluster)
{
#if CONFIG_DVFS_CPU_POWER_I2C_ENABLE
    MS_U32  dwRegisterValue = 0;
    MS_U32  dwOriginalCpuPowerVoltage = 0;
    MS_U32  dwSourceRegisterSetting = 0;
    MS_U32  dwTargetRegisterSetting = 0;

    MS_U8   byTargetRegAddress[5] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF
            };
    MS_U8   byTargetData[5] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF
            };

    if (dwCpuPowerVoltage == 0)
        return;

    if(hMstarDvfsInfo.dwPowerChipId == CONFIG_DVFS_CHIP_ID_PRADO)
    {
        byTargetRegAddress[0] = 0x10;
        byTargetRegAddress[1] = (0x06 << 1);
        if(g_SysIoProc.SysSwI2CReadBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byCluster), 2, byTargetRegAddress, 2, byTargetData) == TRUE)
        {
            dwOriginalCpuPowerVoltage = (unsigned int) byTargetData[1] + CONFIG_DVFS_CPU_POWER_SHIFT_PRADO(byCluster);
            DVFS_DEBUG("\033[33m[INFO] Orginal CPU Power: %d0 mV\033[m\n", (unsigned int) dwOriginalCpuPowerVoltage);
        }

        dwSourceRegisterSetting = (dwOriginalCpuPowerVoltage - CONFIG_DVFS_CPU_POWER_SHIFT_PRADO(byCluster));
        dwTargetRegisterSetting = (dwCpuPowerVoltage - CONFIG_DVFS_CPU_POWER_SHIFT_PRADO(byCluster));

        if(hMstarDvfsInfo.bDvfsInitOk == 1)
        {
            if(dwCpuPowerVoltage > dwOriginalCpuPowerVoltage)
            {
                for(;dwSourceRegisterSetting <= dwTargetRegisterSetting; dwSourceRegisterSetting += CONFIG_DVFS_CPU_POWER_STEP(byCluster))
                {
                    //Set CPU Voltage
                    dwRegisterValue = dwSourceRegisterSetting;
                    byTargetRegAddress[0] = 0x10;
                    byTargetRegAddress[1] = (0x06 << 1);
                    byTargetRegAddress[2] = 0x10;
                    byTargetRegAddress[3] = dwRegisterValue;
                    if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byCluster), 4, byTargetRegAddress, 0, byTargetData) == TRUE)
                    {
                        DVFS_DEBUG("\033[37m[INFO] Change to Voltage: %d0 mV (0x%X)\033[m\n", (unsigned int) dwCpuPowerVoltage, (unsigned int) dwRegisterValue);
                    }
                    else
                    {
                        DVFS_DEBUG("\033[37m[ERROR] Software I2C Write Failed\033[m\n");
                    }
                }
            }
            else if(dwCpuPowerVoltage < dwOriginalCpuPowerVoltage)
            {
                for(;dwSourceRegisterSetting >= dwTargetRegisterSetting; dwSourceRegisterSetting -= CONFIG_DVFS_CPU_POWER_STEP(byCluster))
                {
                    //Set CPU Voltage
                    dwRegisterValue = dwSourceRegisterSetting;
                    byTargetRegAddress[0] = 0x10;
                    byTargetRegAddress[1] = (0x06 << 1);
                    byTargetRegAddress[2] = 0x10;
                    byTargetRegAddress[3] = dwRegisterValue;
                    if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byCluster), 4, byTargetRegAddress, 0, byTargetData) == TRUE)
                    {
                        DVFS_DEBUG("\033[37m[INFO] Change to Voltage: %d0 mV (0x%X)\033[m\n", (unsigned int) dwCpuPowerVoltage, (unsigned int) dwRegisterValue);
                    }
                    else
                    {
                        DVFS_DEBUG("\033[37m[ERROR] Software I2C Write Failed\033[m\n");
                    }
                }
            }
            else
            {
                DVFS_DEBUG("\033[37m[INFO] No Need to Change CPU Power\033[m\n");
                return;
            }
        }

        if(dwSourceRegisterSetting != dwTargetRegisterSetting)
        {
            //Set CPU Voltage
            dwRegisterValue = (dwCpuPowerVoltage - CONFIG_DVFS_CPU_POWER_SHIFT_PRADO(byCluster));
            byTargetRegAddress[0] = 0x10;
            byTargetRegAddress[1] = (0x06 << 1);
            byTargetRegAddress[2] = 0x10;
            byTargetRegAddress[3] = dwRegisterValue;
            if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byCluster), 4, byTargetRegAddress, 0, byTargetData) == TRUE)
            {
                DVFS_INFO("\033[37m[INFO] Change to Voltage: %d0 mV (0x%X)\033[m\n", (unsigned int) dwCpuPowerVoltage, (unsigned int) dwRegisterValue);
            }
            else
            {
                DVFS_DEBUG("\033[37m[ERROR] Software I2C Write Failed\033[m\n");
            }
        }
        else
        {
            DVFS_INFO("\033[37m[INFO] Change to Voltage: %d0 mV (0x%X)\033[m\n", (unsigned int) dwCpuPowerVoltage, (unsigned int) dwRegisterValue);
        }
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsCorePowerAdjustment
/// @brief \b Function  \b Description: Update Output Voltage Level in External Power Chip
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
void SysDvfsCorePowerAdjustment(MS_U32 dwCorePowerVoltage, MS_U8 byCluster)
{
#if CONFIG_DVFS_CORE_POWER_I2C_ENABLE
    #error "No Support Core Power Adjustment by I2C in Messi Platform"
#endif
#if CONFIG_DVFS_CORE_POWER_GPIO_ENABLE
    MS_U32  dwRegisterValue = 0;
    MS_U8   dwChipRev = 0;

    dwChipRev = SYS_GetChipRev();

    if(dwChipRev != 0)
    {
        dwRegisterValue = *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x002e84 << 1));
        if (dwCorePowerVoltage < CONFIG_DVFS_CORE_POWER_L1)
        {
            //VID = 2'b10 = Core Power is 0.85V
            dwRegisterValue &= ~0x0101;
        }
        else if(dwCorePowerVoltage < CONFIG_DVFS_CORE_POWER_DEFAULT)
        {
            //VID = 2'b10 = Core Power is 0.90V
            dwRegisterValue &= ~0x0101;
            dwRegisterValue |= 0x0001;
        }
        else if (dwCorePowerVoltage < CONFIG_DVFS_CORE_POWER_L2)
        {
           //VID = 2'b11 = Core Power is 0.95V
           dwRegisterValue &= ~0x0101;
           dwRegisterValue |= 0x0100;
        }
        else
        {
            //VID = 2'b11 = Core Power is 1.00V
            dwRegisterValue &= ~0x0101;
            dwRegisterValue |= 0x0101;
        }

        *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x002e84 << 1)) = dwRegisterValue;
        *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x100512 << 1)) = CONFIG_DVFS_DYNAMIC_POWER_ADJUST_INIT;
    }
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsCpuPowerInit
/// @brief \b Function  \b Description: The Init Flow of  External Power Chip
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
void SysDvfsCpuPowerInit(void)
{
#if CONFIG_DVFS_CPU_POWER_I2C_ENABLE
    MS_U8   byTargetRegAddress[5] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF
            };
    MS_U8   byTargetData[5] =
            {
                0xFF, 0xFF, 0xFF, 0xFF, 0xFF
            };
    MS_U8   byloop;

    for (byloop=0;byloop<2;byloop++)
    {
        byTargetRegAddress[0] = 0x53;
        byTargetRegAddress[1] = 0x45;
        byTargetRegAddress[2] = 0x52;
        byTargetRegAddress[3] = 0x44;
        byTargetRegAddress[4] = 0x42;
        if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 5, byTargetRegAddress, 0, byTargetData) != TRUE)
        {
            DVFS_DEBUG("\033[33m[ERROR] I2C_Enter_I2C Failed\033[m\n");
        }

        byTargetRegAddress[0] = 0x7F;
        if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 1, byTargetRegAddress, 0, byTargetData) != TRUE)
        {
            DVFS_DEBUG("\033[33m[ERROR] I2C_USE_CFG Failed\033[m\n");
        }

        byTargetRegAddress[0] = 0x7D;
        if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 1, byTargetRegAddress, 0, byTargetData) != TRUE)
        {
            DVFS_DEBUG("\033[33m[ERROR] I2C_OUT_NO_DELAY Failed\033[m\n");
        }

        byTargetRegAddress[0] = 0x50;
        if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 1, byTargetRegAddress, 0, byTargetData) != TRUE)
        {
            DVFS_DEBUG("\033[33m[ERROR] I2C_AD_BYTE_EN0 Failed\033[m\n");
        }

        byTargetRegAddress[0] = 0x55;
        if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 1, byTargetRegAddress, 0, byTargetData) != TRUE)
        {
            DVFS_DEBUG("\033[33m[ERROR] I2C_DA_BYTE_EN1 Failed\033[m\n");
        }

        byTargetRegAddress[0] = 0x35;
        if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 1, byTargetRegAddress, 0, byTargetData) != TRUE)
        {
            DVFS_DEBUG("\033[33m[ERROR] I2C_USE Failed\033[m\n");
        }

        byTargetRegAddress[0] = 0x10;
        byTargetRegAddress[1] = 0xc0;
        if(g_SysIoProc.SysSwI2CReadBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 2, byTargetRegAddress, 2, byTargetData) == TRUE)
        {
            DVFS_DEBUG("\033[33m[INFO] MStar Power IC Chip ID: %x%x\033[m\n", (unsigned int) byTargetData[0], (unsigned int) byTargetData[1]);
            hMstarDvfsInfo.dwPowerChipId = (unsigned int) byTargetData[1];
        }

        SysDvfsCpuPowerAdjustment(CONFIG_DVFS_CPU_POWER_DEFAULT(byloop), byloop);

        if(hMstarDvfsInfo.dwPowerChipId == CONFIG_DVFS_CHIP_ID_PRADO)
        {
            //Set OTP Level
            byTargetRegAddress[0] = 0x10;
            byTargetRegAddress[1] = (0x05 << 1);
            byTargetRegAddress[2] = 0x40;
            byTargetRegAddress[3] = 0x00;
            if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 4, byTargetRegAddress, 0, byTargetData) != TRUE)
            {
                DVFS_INFO("\033[37m[ERROR] Software I2C Write Failed\033[m\n");
            }

            //Set Password
            byTargetRegAddress[0] = 0x10;
            byTargetRegAddress[1] = (0x0C << 1);
            byTargetRegAddress[2] = 0xbe;
            byTargetRegAddress[3] = 0xaf;
            if(g_SysIoProc.SysSwI2CWriteBytes(CONFIG_DVFS_POWER_SWI2C_ADDR_CPU(byloop), 4, byTargetRegAddress, 0, byTargetData) != TRUE)
            {
                DVFS_INFO("\033[37m[ERROR] Software I2C Write Failed\033[m\n");
            }
        }
    }
    *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x100510 << 1)) = CONFIG_DVFS_DYNAMIC_POWER_ADJUST_INIT;

#endif
#if CONFIG_DVFS_CPU_POWER_GPIO_ENABLE
#error "No Support CPU Power Adjustment by GPIO in Messi Platform"
#endif
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: SysDvfsCorePowerInit
/// @brief \b Function  \b Description: The Init Flow of  External Power Chip
/// @param <IN>         \b None:
/// @param <OUT>        \b None:
/// @param <RET>        \b None:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
void SysDvfsCorePowerInit(void)
{
#if CONFIG_DVFS_CORE_POWER_I2C_ENABLE
    #error "No Support Core Power Init by I2C in Messi Platform"
#endif
#if CONFIG_DVFS_CORE_POWER_GPIO_ENABLE
//    MS_U32 dwRegisterValue;

//    dwRegisterValue = *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x002e84 << 1));
//    dwRegisterValue &= ~0x0303;
//    dwRegisterValue |= 0x0101;
//    *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x002e84 << 1)) = dwRegisterValue;

//    *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x000e38 << 1)) |= 0x01 << 10;
//    *(volatile MS_U16 *)(u32hal_sys_baseaddr + (0x100512 << 1)) = CONFIG_DVFS_DYNAMIC_POWER_ADJUST_INIT;
#endif
}

#endif
////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: HAL_SYS_GetMemcConfg
/// @brief \b Function  \b Description: Query the result of config MEMC
/// @param <IN>         \b eSource:
/// @param <IN>         \b eTiming:
/// @param <OUT>        \b retEnMemc:
/// @param <RET>        \b E_SYS_ReturnValue:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
MS_U32  HAL_SYS_GetMemcConfg(MS_U32 eSource, MS_U32 eTiming, MS_BOOL *retEnMemc)
{
    return E_SYS_NOT_SUPPORT;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief \b Function  \b Name: HAL_SYS_GetXcByPartConfg
/// @brief \b Function  \b Description: Query the result of config Bypart XC
/// @param <IN>         \b eSource:
/// @param <IN>         \b eInputTiming:
/// @param <IN>         \b eOutputTiming:
/// @param <OUT>        \b retEn:
/// @param <RET>        \b E_SYS_ReturnValue:
/// @param <GLOBAL>     \b None:
////////////////////////////////////////////////////////////////////////////////
MS_U32  HAL_SYS_GetXcByPartConfg (MS_U32 eSource, MS_U32 eInputTiming, MS_U32 eOutputTiming, MS_BOOL *retEn)
{
    return E_SYS_NOT_SUPPORT;
}