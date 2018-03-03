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
//==============================================================================
// [mhal_sc.c]
// Date: 20081203
// Descriptions: Add a new layer for HW setting
//==============================================================================
#define  MHAL_SC_C

#ifdef MSOS_TYPE_LINUX_KERNEL
#include <asm/div64.h>
#else
#define do_div(x,y) ((x)/=(y))
#endif
#include "UFO.h"

// Common Definition
#include "MsCommon.h"
#include "MsIRQ.h"
#include "MsOS.h"
#include "mhal_xc_chip_config.h"
#include "utopia.h"
#include "utopia_dapi.h"
#include "xc_hwreg_utility2.h"
#include "xc_Analog_Reg.h"
#include "drvXC_IOPort.h"
#include "apiXC.h"
#include "drv_sc_display.h"
#include "drv_sc_isr.h"
#include "apiXC_Adc.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_ModeParse.h"
#include "apiXC_Auto.h"
#include "drvXC_HDMI_if.h"
#include "mvideo_context.h"
#include "drv_sc_ip.h"
#include "mhal_dynamicscaling.h"
#include "mdrv_sc_dynamicscaling.h"
#include "drvMVOP.h"

#if (LD_ENABLE==1)
#include "mdrv_ld.h"
#include "mdrv_ldalgo.h"
#endif
#include "mdrv_sc_3d.h"
#include "drv_sc_menuload.h"
#include "drvXC_ADC_Internal.h"
#include "mhal_sc.h"
#if FRC_INSIDE
#include "mdrv_frc.h"
#include "mhal_frc.h"
#endif
#include "XC_private.h"
#include "mhal_menuload.h"
#include "halCHIP.h"
#include "drvSYS.h"
#include "drv_sc_scaling.h"

#ifndef DONT_USE_CMA
#if (XC_SUPPORT_CMA ==TRUE)
#include "drvCMAPool.h"
#include "msos/linux/ion_uapi.h"
#include "msos/linux/mdrv_cma_pool_st.h"
#endif
#endif

#include <assert.h>
#ifdef ANDROID
#include <cutils/log.h>
#ifndef LOGE
#define printf(format, args...)          ALOGE(format, ##args);
#else
#define printf(format, args...)          LOGE(format, ##args);
#endif
#endif

#define DBG_EN  0
#if DBG_EN
#define SC_DBG(x)   x
#define FPLL_DBG(x) x
#else
#define SC_DBG(x)
#define FPLL_DBG(x)
#endif
#define new_chakra

//==============================================================================
//==============================================================================
MS_VIRT _XC_RIU_BASE;
MS_VIRT _PM_RIU_BASE;

MS_VIRT _DVI_ATOP_RIU_BASE;
MS_VIRT _DVI_DTOP_RIU_BASE;
MS_VIRT _HDCP_RIU_BASE;
MS_VIRT _DVI_EQ_RIU_BASE;
MS_VIRT _ADC_DTOPB_RIU_BASE;

MS_VIRT _DDC_RIU_BASE;
MS_VIRT _PM_SLEEP_RIU_BASE;

MS_U32 u32DTVPatchTimer;
MS_BOOL bPreFDMaskStatse;
MS_U16 u16FDMaskCount;

#ifndef DONT_USE_CMA
#if (XC_SUPPORT_CMA ==TRUE)
MS_U32 u32CMAPatchTimer_Main ;
#endif
#endif

static MS_U16 u16RegForceMryValue = 0;
static void MHal_XC_SetForceCurrentReadBankInterrupt(SC_INT_SRC eIntNum, void *pParam);

// Put this function here because hwreg_utility2 only for hal.
void Hal_SC_init_riu_base(MS_VIRT u32riu_base, MS_VIRT u32PMriu_base)
{
    _XC_RIU_BASE = u32PMriu_base;
    _PM_RIU_BASE = u32PMriu_base;


    _DVI_ATOP_RIU_BASE = u32PMriu_base;
    _DVI_DTOP_RIU_BASE = u32PMriu_base;
    _HDCP_RIU_BASE = u32PMriu_base;
    _DVI_EQ_RIU_BASE = u32PMriu_base;
    _ADC_DTOPB_RIU_BASE = u32PMriu_base;

    _DDC_RIU_BASE =u32PMriu_base;
    _PM_SLEEP_RIU_BASE =u32PMriu_base;

}

//=========================================================//
// Function : Hal_SC_setfield
// Description:
//=========================================================//
void Hal_SC_setfield(void *pInstance, MS_U16 reg_1D, MS_U16 reg_21, MS_U16 reg_23, SCALER_WIN eWindow )
{
    //printf("reg_1D=%x, reg_21=%x, reg_23=%x\n", reg_1D, reg_21, reg_23);
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_1D_L, (reg_1D<<8), 0xEF00);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_21_L, reg_21, 0x3FFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_23_L, (reg_23<<8), HBMASK);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_1D_L, (reg_1D<<8), 0xEF00);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_21_L, reg_21, 0x3FFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_23_L, (reg_23<<8), HBMASK);
    }
//    printf("%x ",SC_R2BYTEMSK(REG_SC_BK01_1D_L, HBMASK));
//    printf("%x ",SC_R2BYTEMSK(REG_SC_BK01_21_L, 0x3FFF));
//    printf("%x ",SC_R2BYTEMSK(REG_SC_BK01_23_L, HBMASK));

//    printf("%x ",SC_R4BYTE(REG_SC_BK01_21_L));
//    printf("%x ",SC_R4BYTE(REG_SC_BK01_23_L));
}

//=========================================================//
// Function : Hal_SC_de_only_en
// Description: DE Only. HSYNC and VSYNC are ignored.
//#0: Disable.
//#1: Enable.
//=========================================================//
void Hal_SC_de_only_en(void *pInstance, MS_BOOL benable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_03_L, (benable ? BIT(6):0), BIT(6));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_2F_L, (benable ? BIT(4):0), BIT(4)); // SW patch for HDMI switch, Auto search HST jistter mask filter force off
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_03_L, (benable ? BIT(6):0), BIT(6));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_2F_L, (benable ? BIT(4):0), BIT(4)); // SW patch for HDMI switch, Auto search HST jistter mask filter force off
    }
}

//=========================================================//
// Function : Hal_SC_de_direct_en
// Description: Digital Input Horizontal Sample Range
//#0: Use DE as sample range, only V position can be adjusted.
//#1: Use SPRHST and SPRHDC as sample range, both H and V position can be adjusted.
//=========================================================//
void Hal_SC_de_direct_en(void *pInstance, MS_BOOL benable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_03_L, (benable ? BIT(7):0), BIT(7));
    else
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_03_L, (benable ? BIT(7):0), BIT(7));

}

void Hal_SC_set_ficlk(void *pInstance, MS_BOOL bPreDown, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    //messi must set FCLK at RFBL mode
    if (gSrcInfo[eWindow].bR_FBL)
    {
        bPreDown = FALSE;
    }

    if(E_XC_DEVICE0 == psXCInstPri->u32DeviceID)
    {
        if( eWindow == MAIN_WINDOW )
        {
            if (bPreDown)
            {
                MDrv_WriteByteMask(REG_CKG_FICLK_F2, CKG_FICLK_F2_IDCLK2, CKG_FICLK_F2_MASK); // clk_idclk2
            }
            else
            {
                MDrv_WriteByteMask(REG_CKG_FICLK_F2, CKG_FICLK_F2_FLK, CKG_FICLK_F2_MASK); // clk_fclk
            }
        }
    }
    else //E_XC_DEVICE1 == psXCInstPri->u32DeviceID
    {
        if (bPreDown)
        {
            MDrv_WriteByteMask(REG_CKG_S2_FICLK2_F2, CKG_S2_FICLK2_F2_IDCLK2, CKG_S2_FICLK2_F2_MASK); // clk_edclk
        }
        else
        {
            MDrv_WriteByteMask(REG_CKG_S2_FICLK2_F2, CKG_S2_FICLK2_F2_FCLK, CKG_S2_FICLK2_F2_MASK); // clk_fclk
        }
    }
}

void Hal_SC_set_shiftline(void *pInstance, MS_U8 u8Val, SCALER_WIN eWindow )
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_2F_L, (u8Val & 0x07)<<8, (BIT(10)|BIT(9)|BIT(8)));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_2F_L, (u8Val & 0x03)<<13, (BIT(14)|BIT(13)));
    }
}

void Hal_SC_set_422_cbcr_swap(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_0A_L, bEnable ? BIT(6) : 0, BIT(6));
    }
    else
    {
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_0A_L, bEnable ? BIT(6) : 0, BIT(6));
    }
}

void Hal_SC_set_pre_align_pixel(void *pInstance, MS_BOOL bEnable, MS_U16 pixels, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (bEnable)
    {
        if ( eWindow == MAIN_WINDOW )
        {
            // Enable pre align pixel for mirror mode.
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_2A_L, BIT(15), BIT(15));

            // Number of pixels need to be inserted. (U3 has 15 pixels)
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_2A_L, pixels << 8 , 0x1F00);
        }
        else
        {
            // Enable pre align pixel for mirror mode.
            //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_2A_L, BIT(15), BIT(15));

            // Number of pixels need to be inserted. (U3 has 15 pixels)
            //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_2A_L, pixels << 8 , 0x1F00);
        }

    }
    else
    {
        if ( eWindow == MAIN_WINDOW )
        {
            // Disable pre align pixel for mirror mode.
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_2A_L, 0x00 , BIT(15));
        }
        else
        {
            // Disable pre align pixel for mirror mode.
            //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_2A_L, 0x00 , BIT(15));
        }
    }
}

void Hal_XC_Set_FreeFRCMD(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_05_L, bEnable? BIT(5) : 0, BIT(5));
}

// Obsolete in M10/J2/A5
void Hal_SC_set_linearmem_mode(MS_BOOL bEnable, SCALER_WIN eWindow)
{
}

// This function will return 8/10/12/14/16 field mode or 8 frame mode.
// Otherwise it return IMAGE_STORE_2_FRAMES
XC_FRAME_STORE_NUMBER Hal_SC_GetFrameStoreMode(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16FrameCount = 0x00;
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    if (eWindow == MAIN_WINDOW)
    {
        u16FrameCount = 0x1F & SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_19_L);
    }
    else
    {
        u16FrameCount = 0x1F & SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_59_L);
    }

    switch( u16FrameCount) // Get field type.
    {
        default:
            if (gSrcInfo[MAIN_WINDOW].bInterlace)
            {
                return IMAGE_STORE_4_FIELDS;
            }
            else
            {
                return IMAGE_STORE_2_FRAMES;
            }
        case 3:
            return IMAGE_STORE_3_FRAMES;
        case 4:
            if (gSrcInfo[MAIN_WINDOW].bInterlace)
            {
                return IMAGE_STORE_4_FIELDS;
            }
            else
            {
                return IMAGE_STORE_4_FRAMES;
            }
        case 6:
            if (gSrcInfo[MAIN_WINDOW].bInterlace)
            {
                return IMAGE_STORE_6_FIELDS;
            }
            else
            {
                return IMAGE_STORE_6_FRAMES;
            }
        case 8:
            if (gSrcInfo[MAIN_WINDOW].bInterlace)
            {
                return IMAGE_STORE_8_FIELDS;
            }
            else
            {
                return IMAGE_STORE_8_FRAMES;
            }
        case 10:
            return IMAGE_STORE_10_FIELDS;
        case 12:
            if (gSrcInfo[MAIN_WINDOW].bInterlace)
            {
                return IMAGE_STORE_12_FIELDS;
            }
            else
            {
                return IMAGE_STORE_12_FRAMES;
            }
        case 14:
            return IMAGE_STORE_14_FIELDS;
        case 16:
            return IMAGE_STORE_16_FIELDS;

    }

    return IMAGE_STORE_UNDEFINE;
}

void Hal_SC_set_wr_bank_mapping(void *pInstance, MS_U8 u8val, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_DBG(printf("Set WR bank mapping SC_BK12_07/47_L[15:13]= 0x%x\n", ((MS_U16)u8val)<<13));

    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, ((MS_U16)u8val)<<13, BIT(15)|BIT(14)|BIT(13));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, ((MS_U16)u8val)<<13, BIT(15)|BIT(14)|BIT(13));
    }
}

void Hal_SC_set_frcm_wr_bank_mapping(void *pInstance, MS_U8 u8val, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_DBG(printf("Set WR bank mapping SC_BK12_07/47_L[15:13]= 0x%x\n", ((MS_U16)u8val)<<13));

    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK32_07_L, ((MS_U16)u8val)<<13, BIT(15)|BIT(14)|BIT(13));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK32_47_L, ((MS_U16)u8val)<<13, BIT(15)|BIT(14)|BIT(13));
    }
}

void Hal_SC_set_wr_bank_mapping_num(void *pInstance, MS_U8 u8Val, SCALER_WIN eWindow)
{
    Hal_SC_set_wr_bank_mapping(pInstance, u8Val, eWindow);
}

MS_U8 Hal_SC_Get_WR_Bank_Mapping(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U8 u8val = 0;

    if( eWindow == MAIN_WINDOW )
    {
        u8val = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, BIT(15)|BIT(14)|BIT(13)) >> 13;
    }
    else
    {
        u8val = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, BIT(15)|BIT(14)|BIT(13)) >> 13;
    }
    SC_DBG(printf("Get WR bank mapping SC_BK12_07/47_L[15:13]= 0x%x\n", ((MS_U16)u8val)<<13));
    return u8val;
}

MS_U8 Hal_SC_Get_WR_Bank_Mapping_Num(void *pInstance, SCALER_WIN eWindow)
{
    return Hal_SC_Get_WR_Bank_Mapping(pInstance, eWindow);
}

void Hal_SC_set_csc(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow )
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_40_L, (bEnable ? BIT(3):0), BIT(3));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_01_L, (bEnable ? BIT(2):0), BIT(2));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_40_L, (bEnable ? BIT(3):0), BIT(3));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_01_L, (bEnable ? BIT(2):0), BIT(2));
    }
}

MS_BOOL Hal_SC_get_ip2_csc(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_BOOL bYUVInput;
    if(eWindow == MAIN_WINDOW)
    {
        // If it has CSC, it shows it must be RGB input.
        // Because in scaler, it must be YUV. So if input is RGB, then we need to do CSC
        bYUVInput = ( SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_40_L, BIT(3) ))? FALSE:TRUE;
    }
    else
    {
        bYUVInput = ( SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_40_L, BIT(3) ))? FALSE:TRUE;
    }
    return bYUVInput;
}

void Hal_SC_set_delayline(void *pInstance, MS_U8 u8DelayLines, SCALER_WIN eWindow )
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    //skip bit7, which is other usage
    MS_U16 u16DelayLines = ((MS_U16)u8DelayLines) & 0xFF;
    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_1C_L, (u16DelayLines<<4), (BIT(9)|BIT(8)|BIT(7)|BIT(6)|BIT(5)|BIT(4)));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_1C_L, (u16DelayLines<<4), (BIT(9)|BIT(8)|BIT(7)|BIT(6)|BIT(5)|BIT(4)));
    }
}

void Hal_SC_set_write_limit(void *pInstance, MS_PHY u32WritelimitAddrBase, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    MS_PHY u32MinLimitAddress = 0;
    MS_PHY u32MaxLimitAddress = 0;

#ifndef DONT_USE_CMA
#if (XC_SUPPORT_CMA ==TRUE)
#if ((HW_DESIGN_4K2K_VER == 4)||(HW_DESIGN_4K2K_VER == 6))
    #if (defined (ANDROID))
    UNUSED(u32WritelimitAddrBase);
    UNUSED(eWindow);
    return;
    #endif
#endif
#endif
#endif

#if (HW_DESIGN_4K2K_VER == 4)
    // in Monaco, the 4K data path need to setup the IPM write on the FRCM base, and the max/min limit region also need to change
    if(gSrcInfo[eWindow].stCapWin.width > 3800)
    {
        u32MinLimitAddress = MHal_XC_GetFRCMBufAddress(pInstance, eWindow)/BYTE_PER_WORD ;
        if((MHal_XC_GetFRCMBufAddress(pInstance, eWindow) + MHal_XC_GetFRCMBufSize(pInstance, eWindow))!=0)
            u32MaxLimitAddress = (MHal_XC_GetFRCMBufAddress(pInstance, eWindow) + MHal_XC_GetFRCMBufSize(pInstance, eWindow))/BYTE_PER_WORD - 1;
        else
            u32MaxLimitAddress = u32MinLimitAddress;
    }
    //monaco mm DS VB size always be 4k2k , mvop timing is 4k2k , 2p mode
    else if ((pXCResourcePrivate->sthal_SC.bDynamicScalingEnable || pXCResourcePrivate->stdrvXC_Dynamicscaling._bDSForceIndexEnable[eWindow] ) &&
            (gSrcInfo[eWindow].Status2.u16VirtualBox_Width >= 0xF00) && (gSrcInfo[eWindow].Status2.u16VirtualBox_Height>= 0x870))
    {
        u32MinLimitAddress = MHal_XC_GetFRCMBufAddress(pInstance, eWindow)/BYTE_PER_WORD ;
        if((MHal_XC_GetFRCMBufAddress(pInstance, eWindow) + MHal_XC_GetFRCMBufSize(pInstance, eWindow))!=0)
            u32MaxLimitAddress = (MHal_XC_GetFRCMBufAddress(pInstance, eWindow) + MHal_XC_GetFRCMBufSize(pInstance, eWindow))/BYTE_PER_WORD - 1;
        else
            u32MaxLimitAddress = u32MinLimitAddress;
    }
    else
#endif
    {
        u32MinLimitAddress = MHal_XC_GetDNRBufAddress(pInstance, eWindow)/BYTE_PER_WORD ;
        if((MHal_XC_GetDNRBufAddress(pInstance, eWindow) + MHal_XC_GetDNRBufSize(pInstance, eWindow))!=0)
            u32MaxLimitAddress = (MHal_XC_GetDNRBufAddress(pInstance, eWindow) + MHal_XC_GetDNRBufSize(pInstance, eWindow))/BYTE_PER_WORD - 1;
        else
            u32MaxLimitAddress = u32MinLimitAddress;
    }
    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"eWindow=%x, MHal_XC_GetDNRBufAddress=%llx, MHal_XC_GetDNRBufSize=%llx\n", eWindow, (MHal_XC_GetDNRBufAddress(pInstance, eWindow)/BYTE_PER_WORD ), (MHal_XC_GetDNRBufSize(pInstance, eWindow))/BYTE_PER_WORD);
    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"eWindow=%x, u32MinLimitAddress=%llx, u32MaxLimitAddress=%llx\n", eWindow, u32MinLimitAddress, u32MaxLimitAddress);

    if(eWindow == MAIN_WINDOW)
    {
        /// need to disable the r/w request, when change the write limit base
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, BIT(0)|BIT(1), BIT(0)|BIT(1));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0D_38_L, ((u32WritelimitAddrBase&BIT(31))?(BIT(0)|BIT(6)):0),BIT(0)|BIT(6)); //F2 memory address limit enable
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_40_L, u32MinLimitAddress); //F2 memory min address
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_42_L, u32MaxLimitAddress); //F2 memory max address
        /// need to enable the r/w request
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, 0x00, BIT(0)|BIT(1));
              }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, BIT(0)|BIT(1), BIT(0)|BIT(1));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0D_38_L, ((u32WritelimitAddrBase&BIT(31))?BIT(1):0),BIT(1)); //F1 memory address limit enable
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_44_L, u32MinLimitAddress); //F1 memory min address
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_46_L, u32MaxLimitAddress); //F1 memory max address
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, 0x00, BIT(0)|BIT(1));
    }
}

void Hal_SC_set_frcm_write_limit(void *pInstance, MS_PHY u32WritelimitAddrBase, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32WritelimitAddrBase);
    UNUSED(eWindow);
}

void Hal_SC_set_dual_write_limit(void *pInstance, MS_PHY u32WritelimitAddrBase, SCALER_WIN eWindow)
{
#ifdef SUPPORT_DUAL_MIU
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    MS_PHY u32MinLimitAddress = 0;
    MS_PHY u32MaxLimitAddress = 0;

    u32MinLimitAddress = MHal_XC_GetDualDNRBufSize(pInstance, eWindow)/BYTE_PER_WORD ;
    if((MHal_XC_GetDualDNRBufAddress(pInstance, eWindow) + MHal_XC_GetDualDNRBufSize(pInstance, eWindow))!=0)
        u32MaxLimitAddress = (MHal_XC_GetDualDNRBufAddress(pInstance, eWindow) + MHal_XC_GetDualDNRBufSize(pInstance, eWindow))/BYTE_PER_WORD - 1;
    else
        u32MaxLimitAddress = u32MinLimitAddress;

    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"eWindow=%x, MHal_XC_GetDNRBufAddress=%llx, MHal_XC_GetDNRBufSize=%llx\n", eWindow, (MHal_XC_GetDNRBufAddress(pInstance, eWindow)/BYTE_PER_WORD ), (MHal_XC_GetDNRBufSize(pInstance, eWindow))/BYTE_PER_WORD);
    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"eWindow=%x, u32MinLimitAddress=%llx, u32MaxLimitAddress=%llx\n", eWindow, u32MinLimitAddress, u32MaxLimitAddress);

    if(eWindow == MAIN_WINDOW)
    {
        /// need to disable the r/w request, when change the write limit base
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, BIT(0)|BIT(1), BIT(0)|BIT(1));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0D_38_L, ((u32WritelimitAddrBase&BIT(31))?BIT(4):0),BIT(4)); //F2 memory address limit enable
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_48_L, u32MinLimitAddress); //F2 memory min address
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_4A_L, u32MaxLimitAddress); //F2 memory max address
        /// need to enable the r/w request
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, 0x00, BIT(0)|BIT(1));
    }
#endif
}

void Hal_SC_set_opm_write_limit(void *pInstance, MS_BOOL bEnable, MS_BOOL bFlag, MS_U32 u32OPWlimitAddr, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
    UNUSED(bFlag);
    UNUSED(u32OPWlimitAddr);
    UNUSED(eWindow);
}

MS_BOOL Hal_SC_is_extra_req_en(void *pInstance,
    MS_U16 *pu16MainHStart, MS_U16 *pu16MainHEnd,
    MS_U16 *pu16SubHStart,  MS_U16 *pu16SubHEnd)
{
    MS_BOOL bEn = FALSE;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    MS_U16 u16MainHStart, u16SubHStart;
    MS_U16 u16MainHEnd, u16SubHEnd;

    u16MainHStart = pu16MainHStart == NULL ? SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_08_L) : *pu16MainHStart;
    u16MainHEnd   = pu16MainHEnd   == NULL ? SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_09_L) : *pu16MainHEnd;
    u16SubHStart  = pu16SubHStart  == NULL ? SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_07_L) : *pu16SubHStart;
    u16SubHEnd    = pu16SubHEnd    == NULL ? SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_08_L) : *pu16SubHEnd;

    if( SC_R2BYTEMSK( psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, BIT(1))
        &&(((psXCInstPri->u32DeviceID == 0) && (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_Init_Misc.u32MISC_A & E_XC_INIT_MISC_A_LEGACY_MODE))
             ||(psXCInstPri->u32DeviceID == 1))
      ) // Only Legacy mode use old rule for extra enable
    {
        if(u16MainHStart > u16SubHStart || u16MainHEnd < u16SubHEnd)
        {
            bEn = FALSE;
        }
        else
        {
            bEn = TRUE;
        }
    }
    else
    {
        bEn = FALSE;
    }
#if DBG_EN
    SC_DBG(printf("Sub=%d, MainHs=%d, SubHs=%d, MainHe=%d, SubHe=%d :: Extra=%d\n",
     SC_R2BYTEMSK( psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, BIT(1)),
     u16MainHStart, u16SubHStart, u16MainHEnd, u16SubHEnd, bEn));
#endif
    return bEn;

}

static void _Hal_SC_fill_main_sw_db_burst(void *pInstance, P_SC_SWDB_INFO pDBreg)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(Hal_SC_is_extra_req_en(pInstance, &pDBreg->u16H_DisStart, &pDBreg->u16H_DisEnd, NULL, NULL))
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_11_L, BIT(15), BIT(15));
    }
    else
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_11_L, 0, BIT(15));
    }

    //H pre-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK02_04_L, (MS_U16)(pDBreg->u32H_PreScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK02_05_L, (MS_U16)(pDBreg->u32H_PreScalingRatio>>16), 0xFFFF);
    //V pre-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK02_08_L, (MS_U16)(pDBreg->u32V_PreScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK02_09_L, (MS_U16)(pDBreg->u32V_PreScalingRatio>>16), 0xFFFF);
    //H post-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_07_L, (MS_U16)(pDBreg->u32H_PostScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_08_L, (MS_U16)(pDBreg->u32H_PostScalingRatio>>16), 0xFFFF);
    //V post-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_09_L, (MS_U16)(pDBreg->u32V_PostScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_0A_L, (MS_U16)(pDBreg->u32V_PostScalingRatio>>16), 0xFFFF);

    //SCMI: vertical limitation
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_18_L, (MS_U16)(pDBreg->u16VWritelimit), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1A_L, (MS_U16)(pDBreg->u32DNRBase1>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1B_L, (MS_U16)(pDBreg->u32DNRBase1>>16), 0xFFFF);

    //SCMI: IPM address 0
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_08_L, (MS_U16)(pDBreg->u32DNRBase0>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_09_L, (MS_U16)(pDBreg->u32DNRBase0>>16), 0xFFFF);
    //SCMI: DNR address 1
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1A_L, (MS_U16)(pDBreg->u32DNRBase1>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1B_L, (MS_U16)(pDBreg->u32DNRBase1>>16), 0xFFFF);
    //SCMI: DNR address 2
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_0C_L, (MS_U16)(pDBreg->u32DNRBase2>>00), 0xFFFF);
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_0D_L, (MS_U16)(pDBreg->u32DNRBase2>>16), 0xFFFF);

    //SCMI: DNR offset
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_0E_L, (MS_U16)(pDBreg->u16DNROffset>>00), 0xFFFF);
    //SCMI: DNR fetch
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_0F_L, (MS_U16)(pDBreg->u16DNRFetch>>00), 0xFFFF);

    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1C_L, 0x0, 0xFFFF); //always disable IP H mirror line offset note:ds will enable this register at vdec firmware

    //SCMI: OPM address 0
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_10_L, (MS_U16)(pDBreg->u32OPMBase0>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_11_L, (MS_U16)(pDBreg->u32OPMBase0>>16), 0xFFFF);
    //SCMI: OPM address 1
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_12_L, (MS_U16)(pDBreg->u32OPMBase1>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_13_L, (MS_U16)(pDBreg->u32OPMBase1>>16), 0xFFFF);
    //SCMI: OPM address 2
    //    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_14_L, (MS_U16)(pDBreg->u32OPMBase2>>00), 0xFFFF);
    //    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_15_L, (MS_U16)(pDBreg->u32OPMBase2>>16), 0xFFFF);
    //SCMI: OPM offset
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_16_L, (MS_U16)(pDBreg->u16OPMOffset>>00), 0xFFFF);
    //SCMI: OPM fetch
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_17_L, (MS_U16)(pDBreg->u16OPMFetch>>00), 0xFFFF);

    //PIP
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_15_L, (MS_U16)(pDBreg->u16VLen>>00), 0xFFFF); // Write V length
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_1D_L, (MS_U16)(pDBreg->u16LBOffset&0xFF), 0x00FF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_1C_L, (MS_U16)(pDBreg->u16DispOffset&0xFF), 0x00FF);
    // if LB Offset > externded pixels of bottom A session,
    // there would be garbage on the left side of sub video
    if (pDBreg->u16LBOffset > SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_14_L, 0x00FF))
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_14_L, (pDBreg->u16LBOffset&0xFF), 0x00FF);
    }

    /// before enable ML bit mask feature, the capture size for 2P setting BK01_07[15] need to be considered
    if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, BIT(15)))
        pDBreg->u16H_CapSize |= 0x8000;
    else
        pDBreg->u16H_CapSize |= 0x0000;

        //capture window
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK01_04_L, (MS_U16)(pDBreg->u16V_CapStart>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK01_05_L, (MS_U16)(pDBreg->u16H_CapStart>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK01_06_L, (MS_U16)(pDBreg->u16V_CapSize>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK01_07_L, (MS_U16)(pDBreg->u16H_CapSize>>00), 0xFFFF);

        //Display window
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_08_L, (MS_U16)(pDBreg->u16H_DisStart>>00), VOP_DISPLAY_HSTART_MASK);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_09_L, (MS_U16)(pDBreg->u16H_DisEnd>>00), VOP_DISPLAY_HEND_MASK);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_0A_L, (MS_U16)(pDBreg->u16V_DisStart>>00), VOP_DISPLAY_VSTART_MASK);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_0B_L, (MS_U16)(pDBreg->u16V_DisEnd>>00), VOP_DISPLAY_VEND_MASK);

  //  MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1C_L, 0x0, 0xFFFF); //always disable IP H mirror line offset note:ds will enable this register at vdec firmware

#if SUPPORT_2_FRAME_MIRROR

    if( (gSrcInfo[MAIN_WINDOW].Status2.eFrameStoreNumber == IMAGE_STORE_2_FRAMES) && (!gSrcInfo[MAIN_WINDOW].bInterlace) && (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK2A_02_L, BIT(15)) == 0))
    {
        // 2_frmae_mirror cannot work when UC on

        //SCMI: DNR address 1
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1A_L, (MS_U16)(pDBreg->u32DNRBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_1B_L, (MS_U16)(pDBreg->u32DNRBase1>>16), 0xFFFF);

        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_30_L, 0x4000,0xFFFF);// enable two frame mirror

        if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_01_L, 0x0001) == 0 )//compress mode
        {
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK08_32_L, 0x20,0x00F0); // opm_ce_lcnt_inv
        }
    }
    else
    {
        if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK2A_02_L, BIT(15)) == BIT(15))
        {
            printf("@@ [%s,%5d] 2_frmae_mirror cannot work when UC on  \n",__func__,__LINE__);
        }

        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_30_L, 0x0000,0xFFFF);// disable two frame mirror
    }
#endif

    MS_U16 u16reg = 0;

    u16reg = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK08_32_L);

    if(pDBreg->bOpmLcntInv_En)
    {
        u16reg |= BIT(5);
    }
    else
    {
        u16reg &= ~ BIT(5);
    }


    //monaco/muji 3D mode need control sub for some output format, or else the edge of object in the image may shake
#if (HW_DESIGN_4K2K_VER == 4)
    E_XC_3D_OUTPUT_MODE e3DOutputFormat = MDrv_XC_Get_3D_Output_Mode(pInstance);
    if((e3DOutputFormat == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)
        || (e3DOutputFormat == E_XC_3D_OUTPUT_TOP_BOTTOM) || (e3DOutputFormat == E_XC_3D_OUTPUT_TOP_BOTTOM_HW)
        || (e3DOutputFormat == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF) || (e3DOutputFormat == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF_HW)
        || (e3DOutputFormat == E_XC_3D_OUTPUT_FRAME_PACKING))
    {
        //Hal_SC_set_opm_lcnt_inv(pInstance, bopm_lcnt_inv, SUB_WINDOW);
        if(pDBreg->bOpmLcntInv_En)
        {
            u16reg |= BIT(4);
        }
        else
        {
            u16reg &= ~ BIT(4);
        }
    }
#endif

    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK08_32_L, u16reg, 0xFFFF);
}

static void _Hal_SC_fill_sub_sw_db_burst(void *pInstance, P_SC_SWDB_INFO pDBreg)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(Hal_SC_is_extra_req_en(pInstance, NULL, NULL, &pDBreg->u16H_DisStart, &pDBreg->u16H_DisEnd))
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_11_L, BIT(15), BIT(15));
    }
    else
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_11_L, 0, BIT(15));
    }

    //H pre-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK04_04_L, (MS_U16)(pDBreg->u32H_PreScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK04_05_L, (MS_U16)(pDBreg->u32H_PreScalingRatio>>16), 0xFFFF);
    //V pre-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK04_08_L, (MS_U16)(pDBreg->u32V_PreScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK04_09_L, (MS_U16)(pDBreg->u32V_PreScalingRatio>>16), 0xFFFF);

    //H post-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_27_L, (MS_U16)(pDBreg->u32H_PostScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_28_L, (MS_U16)(pDBreg->u32H_PostScalingRatio>>16), 0xFFFF);
    //V post-scaling
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_29_L, (MS_U16)(pDBreg->u32V_PostScalingRatio>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK23_2A_L, (MS_U16)(pDBreg->u32V_PostScalingRatio>>16), 0xFFFF);

    //SCMI: vertical limitation
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_58_L, (MS_U16)(pDBreg->u16VWritelimit), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_5A_L, (MS_U16)(pDBreg->u32WritelimitBase>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_5B_L, (MS_U16)(pDBreg->u32WritelimitBase>>16), 0xFFFF);
    //SCMI: IPM address 0
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_48_L, (MS_U16)(pDBreg->u32DNRBase0>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_49_L, (MS_U16)(pDBreg->u32DNRBase0>>16), 0xFFFF);
    //SCMI: DNR address 1
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_4A_L, (MS_U16)(pDBreg->u32DNRBase1>>00), 0xFFFF);
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_4B_L, (MS_U16)(pDBreg->u32DNRBase1>>16), 0xFFFF);
    //SCMI: DNR address 2
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_4C_L, (MS_U16)(pDBreg->u32DNRBase2>>00), 0xFFFF);
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_4D_L, (MS_U16)(pDBreg->u32DNRBase2>>16), 0xFFFF);
    //SCMI: DNR offset
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_4E_L, (MS_U16)(pDBreg->u16DNROffset>>00), 0xFFFF);
    //SCMI: DNR fetch
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_4F_L, (MS_U16)(pDBreg->u16DNRFetch>>00), 0xFFFF);
    //SCMI: OPM address 0
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_50_L, (MS_U16)(pDBreg->u32OPMBase0>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_51_L, (MS_U16)(pDBreg->u32OPMBase0>>16), 0xFFFF);
    //SCMI: OPM address 1
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_52_L, (MS_U16)(pDBreg->u32OPMBase1>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_53_L, (MS_U16)(pDBreg->u32OPMBase1>>16), 0xFFFF);
    //SCMI: OPM address 2
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_54_L, (MS_U16)(pDBreg->u32OPMBase2>>00), 0xFFFF);
    //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_55_L, (MS_U16)(pDBreg->u32OPMBase2>>16), 0xFFFF);
    //SCMI: OPM offset
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_56_L, (MS_U16)(pDBreg->u16OPMOffset>>00), 0xFFFF);
    //SCMI: OPM fetch
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_57_L, (MS_U16)(pDBreg->u16OPMFetch>>00), 0xFFFF);
    //PIP
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_16_L, (MS_U16)(pDBreg->u16VLen>>00), 0xFFFF); // Write V length
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_1D_L, (MS_U16)((pDBreg->u16LBOffset&0xFF)<<8), 0xFF00);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_1C_L, (MS_U16)((pDBreg->u16DispOffset&0xFF)<<8), 0xFF00);

    /// before enable ML bit mask feature, the capture size for 2P setting BK03_07[15] need to be considered
    if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_07_L, BIT(15)))
        pDBreg->u16H_CapSize |= 0x8000;
    else
        pDBreg->u16H_CapSize |= 0x0000;

    // capture window
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_04_L, (MS_U16)(pDBreg->u16V_CapStart>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_05_L, (MS_U16)(pDBreg->u16H_CapStart>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_06_L, (MS_U16)(pDBreg->u16V_CapSize>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_07_L, (MS_U16)(pDBreg->u16H_CapSize>>00), 0xFFFF);

    //Display window
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_07_L, (MS_U16)(pDBreg->u16H_DisStart>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_08_L, (MS_U16)(pDBreg->u16H_DisEnd>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_09_L, (MS_U16)(pDBreg->u16V_DisStart>>00), 0xFFFF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_0A_L, (MS_U16)(pDBreg->u16V_DisEnd>>00), 0xFFFF);

    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_5C_L, 0x0, 0x1FFF); //always disable IP H mirror line offset note:ds will enable this register at vdec firmware

    MS_U16 u16reg = 0;
    u16reg = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK08_32_L);


    if(pDBreg->bOpmLcntInv_En)
    {
        u16reg |= BIT(4);
    }
    else
    {
        u16reg &= ~ BIT(4);
    }


    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK08_32_L, u16reg, 0xFFFF);

}

void Hal_SC_sw_db_burst(void *pInstance, P_SC_SWDB_INFO pDBreg, SCALER_WIN eWindow )
{
    _MLOAD_ENTRY(pInstance);

    if( eWindow == MAIN_WINDOW )
    {
        _Hal_SC_fill_main_sw_db_burst(pInstance, pDBreg);
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
    }
    else
    {
        _Hal_SC_fill_sub_sw_db_burst(pInstance, pDBreg);
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
    }

    _MLOAD_RETURN(pInstance);
}

void Hal_SC_dual_sw_db_burst(void *pInstance, P_SC_SWDB_INFO pMainDBreg, P_SC_SWDB_INFO pSubDBreg)
{
    _MLOAD_ENTRY(pInstance);

    _Hal_SC_fill_main_sw_db_burst(pInstance, pMainDBreg);
    _Hal_SC_fill_sub_sw_db_burst(pInstance, pSubDBreg);
    MDrv_XC_MLoad_Fire(pInstance, TRUE);

    _MLOAD_RETURN(pInstance);
}

void Hal_SC_sw_db(void *pInstance, P_SC_SWDB_INFO pDBreg, SCALER_WIN eWindow )
{
    MS_U32 u32LcentInvReg = 0;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] bDynamicScalingEnable%d  \n",__func__,__LINE__,pXCResourcePrivate->sthal_SC.bDynamicScalingEnable);

    if( eWindow == MAIN_WINDOW )
    {
        if(Hal_SC_is_extra_req_en(pInstance, &pDBreg->u16H_DisStart, &pDBreg->u16H_DisEnd, NULL, NULL))
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_11_L, BIT(15), BIT(15));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_11_L, 0, BIT(15));
        }

        // H pre-scaling
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_04_L, pDBreg->u32H_PreScalingRatio);
        // V pre-scaling
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_08_L, pDBreg->u32V_PreScalingRatio);
        // H post-scaling
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_07_L, pDBreg->u32H_PostScalingRatio);
        // V post-scaling
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_09_L, pDBreg->u32V_PostScalingRatio);

        //SCMI
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_18_L, pDBreg->u16VWritelimit); // Set vertical limitation
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_1A_L, pDBreg->u32DNRBase1);

        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_08_L, pDBreg->u32DNRBase0);     // input address0
        //SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0A_L, pDBreg->u32DNRBase1);     // input address1
        //SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0C_L, pDBreg->u32DNRBase2);     // input address2

        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0E_L, pDBreg->u16DNROffset);// input Offset
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0F_L, pDBreg->u16DNRFetch); // input fetch
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_1C_L, 0x0, 0xFFFF);         //always disable IP H mirror line offset note:ds will enable this register at vdec firmware


        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_10_L, pDBreg->u32OPMBase0); // output address0
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_12_L, pDBreg->u32OPMBase1); // output address1
//      SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_14_L, pDBreg->u32OPMBase2); // output address2
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_16_L, pDBreg->u16OPMOffset); // output offset
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_17_L, pDBreg->u16OPMFetch);  // output fetch

        //PIP
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK20_15_L, pDBreg->u16VLen); // Write V length
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_1D_L, (pDBreg->u16LBOffset&0xFF), 0xFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_1C_L, (pDBreg->u16DispOffset&0xFF), 0xFF);
        // if LB Offset > externded pixels of bottom A session,
        // there would be garbage on the left side of sub video
        if (pDBreg->u16LBOffset > SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_14_L, 0xFF))
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_14_L, (pDBreg->u16LBOffset&0xFF), 0xFF);
        }

        /// before enable ML bit mask feature, the capture size for 2P setting BK01_07[15] need to be considered
        if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, BIT(15)))
            pDBreg->u16H_CapSize |= 0x8000;
        else
            pDBreg->u16H_CapSize |= 0x0000;

        // capture window
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_04_L, pDBreg->u16V_CapStart); // Capture V start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_05_L, pDBreg->u16H_CapStart); // Capture H start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_06_L, pDBreg->u16V_CapSize);  // Capture V size
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, pDBreg->u16H_CapSize);  // Capture H size

        //Display window
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_08_L, pDBreg->u16H_DisStart); // Display H start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_09_L, pDBreg->u16H_DisEnd);   // Display H end
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_0A_L, pDBreg->u16V_DisStart); // Display V start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_0B_L, pDBreg->u16V_DisEnd);   // Display V end

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_1C_L, 0x0, 0xFFFF);         //always disable IP H mirror line offset note:ds will enable this register at vdec firmware

// 2_frame_mirror setting
#if SUPPORT_2_FRAME_MIRROR
        // 2_frmae_mirror cannot work when UC on
        if( (gSrcInfo[eWindow].Status2.eFrameStoreNumber == IMAGE_STORE_2_FRAMES) && (!gSrcInfo[eWindow].bInterlace) && (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK2A_02_L, BIT(15)) == 0))
        {
            //SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_1A_L, pDBreg->u32DNRBase1);  // IPM base1
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_30_L, 0x4000, BIT(14));   // enable two frame mirror

            if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_01_L, 0x0001) == 0 )//compress mode
            {
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_32_L, 0X20 ,0x00F0 );   // opm_ce_lcnt_inv
            }
        }
        else
        {
            if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK2A_02_L, BIT(15)) == BIT(15))
            {
                printf("@@ [%s,%5d] 2_frmae_mirror cannot work when UC on  \n",__func__,__LINE__);
            }

            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_30_L, 0x00 , BIT(14)); // disable two frame mirror
        }
#endif
        if (((psXCInstPri->u32DeviceID == 0) && (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_Init_Misc.u32MISC_A & E_XC_INIT_MISC_A_LEGACY_MODE))
            ||(psXCInstPri->u32DeviceID == 1))
        {
            u32LcentInvReg = REG_SC_BK08_32_L;
        }
        else
        {
            u32LcentInvReg = REG_SC_BK33_32_L;
        }

        if(pDBreg->bOpmLcntInv_En)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32LcentInvReg, BIT(5), BIT(5));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32LcentInvReg, 0x00, BIT(5));
        }

        //monaco/muji 3D mode need control sub for some output format, or else the edge of object in the image may shake
#if (HW_DESIGN_4K2K_VER == 4)
        E_XC_3D_OUTPUT_MODE e3DOutputFormat = MDrv_XC_Get_3D_Output_Mode(pInstance);
        if((e3DOutputFormat == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)
            || (e3DOutputFormat == E_XC_3D_OUTPUT_TOP_BOTTOM) || (e3DOutputFormat == E_XC_3D_OUTPUT_TOP_BOTTOM_HW)
            || (e3DOutputFormat == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF) || (e3DOutputFormat == E_XC_3D_OUTPUT_SIDE_BY_SIDE_HALF_HW)
            || (e3DOutputFormat == E_XC_3D_OUTPUT_FRAME_PACKING))
        {
            //Hal_SC_set_opm_lcnt_inv(pInstance, bopm_lcnt_inv, SUB_WINDOW);
            if(pDBreg->bOpmLcntInv_En)
            {
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32LcentInvReg, BIT(4), BIT(4));
            }
            else
            {
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32LcentInvReg, 0x00, BIT(4));
            }
        }
#endif
    }
    else
    {
        if(Hal_SC_is_extra_req_en(pInstance, NULL, NULL, &pDBreg->u16H_DisStart, &pDBreg->u16H_DisEnd))
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_11_L, BIT(15), BIT(15));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_11_L, 0, BIT(15));
        }

        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK04_04_L, pDBreg->u32H_PreScalingRatio);   // H pre-scaling
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK04_08_L, pDBreg->u32V_PreScalingRatio);   // V pre-scaling

        //HVSP
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_27_L, pDBreg->u32H_PostScalingRatio);  // H post-scaling
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_29_L, pDBreg->u32V_PostScalingRatio);  // V post-scaling

        //SCMI
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_58_L, pDBreg->u16VWritelimit); // Set vertical limitation
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_5A_L, pDBreg->u32WritelimitBase);
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_48_L, pDBreg->u32DNRBase0);     // input address0
        //SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4A_L, pDBreg->u32DNRBase1); // input address1
        //SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4C_L, pDBreg->u32DNRBase2); // input address2
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4E_L, pDBreg->u16DNROffset);// input Offset
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4F_L, pDBreg->u16DNRFetch); // input fetch
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_50_L, pDBreg->u32OPMBase0); // output address0
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_52_L, pDBreg->u32OPMBase1); // output address1
        //SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_54_L, pDBreg->u32OPMBase2); // output address2
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_56_L, pDBreg->u16OPMOffset); // output offset
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_57_L, pDBreg->u16OPMFetch);  // output fetch
        //PIP
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK20_16_L, pDBreg->u16VLen); // Write V length
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_1D_L, (pDBreg->u16LBOffset&0xFF)<<8, 0xFF00);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_1C_L, (pDBreg->u16DispOffset&0xFF)<<8, 0xFF00);

        // capture window
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_04_L, pDBreg->u16V_CapStart); // Capture V start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_05_L, pDBreg->u16H_CapStart); // Capture H start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_06_L, pDBreg->u16V_CapSize);  // Capture V size
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_07_L, pDBreg->u16H_CapSize);  // Capture H size

        //Display window
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_07_L, pDBreg->u16H_DisStart); // Display H start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_08_L, pDBreg->u16H_DisEnd);   // Display H end
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_09_L, pDBreg->u16V_DisStart); // Display V start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_0A_L, pDBreg->u16V_DisEnd);   // Display V end

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_5C_L, 0x0, 0x1FFF);         //always disable IP H mirror line offset note:ds will enable this register at vdec firmware

        if (((psXCInstPri->u32DeviceID == 0) && (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_Init_Misc.u32MISC_A & E_XC_INIT_MISC_A_LEGACY_MODE))
            ||(psXCInstPri->u32DeviceID == 1))
        {
            u32LcentInvReg = REG_SC_BK08_32_L;
        }
        else
        {
            u32LcentInvReg = REG_SC_BK33_32_L;
        }

        if(pDBreg->bOpmLcntInv_En)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32LcentInvReg, BIT(4), BIT(4));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32LcentInvReg, 0x00, BIT(4));
        }
    }
}

void Hal_SC_SWDS_AddCmd(void *pInstance, P_SC_SWDB_INFO pDBreg, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] eWindow:%d bDynamicScalingEnable%d  \n",__func__,__LINE__,eWindow,pXCResourcePrivate->sthal_SC.bDynamicScalingEnable);

    XC_DS_CMDCNT PSTXC_DS_CMDCNT;

    PSTXC_DS_CMDCNT.u16CMDCNT_IPM =0;
    PSTXC_DS_CMDCNT.u16CMDCNT_IPS =0;
    PSTXC_DS_CMDCNT.u16CMDCNT_OPM =0;
    PSTXC_DS_CMDCNT.u16CMDCNT_OPS =0;

    if(eWindow == MAIN_WINDOW)
    {
        if(pXCResourcePrivate->sthal_SC.bDynamicScalingEnable)
        {
            pXCResourcePrivate->sthal_SC.u8DynamicScalingNextIndex[MAIN_WINDOW] = pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[MAIN_WINDOW];

//Command Priority:
//1.GOP
//2.MVOP
//3.XC

            MS_U32 ActiveSWClearEn = 0;
            MS_U32 u32SW_Reset_Enable = 0;
            //ActiveSWClearEn enable in first DS IP command ;
            u32SW_Reset_Enable = 0x0400; // bit10: reg_ds_ipm_active_sel: 0:HW 1:SW
            ActiveSWClearEn = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_17_L, 0xFFFF);
            ActiveSWClearEn |= u32SW_Reset_Enable;

            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK1F_17_L,(MS_U16)(ActiveSWClearEn),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);

            //XC_PRINTF("[%s,%5d] bR_FBL:%d bFBL:%d  \n",__func__,__LINE__,gSrcInfo[MAIN_WINDOW].bR_FBL,gSrcInfo[MAIN_WINDOW].bFBL);
            //XC_PRINTF("[%s,%5d] Crop(x,y,w,h)=(%d,%d,%d,%d) \n",__func__,__LINE__,gSrcInfo[eWindow].stCropWin.x,gSrcInfo[eWindow].stCropWin.y,gSrcInfo[eWindow].stCropWin.width,gSrcInfo[eWindow].stCropWin.height);

            if(IsSrcTypeStorage(gSrcInfo[MAIN_WINDOW].enInputSourceType))
            {
                if((gSrcInfo[MAIN_WINDOW].bR_FBL) || (gSrcInfo[MAIN_WINDOW].bFBL))//set MVOP crop info
                {
                    MVOP_Handle stHdl = { E_MVOP_MODULE_MAIN };
                    MVOP_XCGetCropMirAdd stCropADD;

                    stCropADD.u16XCap = pDBreg->u16H_CapSize;
                    stCropADD.u16YCap = pDBreg->u16V_CapSize;

                    stCropADD.stXCCrop.u16XStart = gSrcInfo[eWindow].stCropWin.x;
                    stCropADD.stXCCrop.u16YStart = gSrcInfo[eWindow].stCropWin.y;
                    stCropADD.stXCCrop.u16XSize = gSrcInfo[eWindow].stCropWin.width;
                    stCropADD.stXCCrop.u16YSize = gSrcInfo[eWindow].stCropWin.height;
                    stCropADD.stXCCrop.reserve[1] = gSrcInfo[eWindow].Status2.u32MFCodecInfo;


                    // GET MVOP crop info
                    MDrv_MVOP_GetCommand(&stHdl, E_MVOP_CMD_GET_CROP_FOR_XC, &stCropADD.stXCCrop, sizeof(MVOP_XCGetCrop));

                    //ds write crop
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_FORCE_WR,0x0012,DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_CROP_H_START,stCropADD.stXCCrop.u16XStart,DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_CROP_V_START,/*0x2000| not work in messi*/stCropADD.stXCCrop.u16YStart,DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_CROP_H_SIZE,stCropADD.stXCCrop.u16XSize,DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_CROP_V_SIZE,stCropADD.stXCCrop.u16YSize,DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_VOFFSET0,stCropADD.stXCCrop.reserve[0],DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_SKIPSIZE,stCropADD.stXCCrop.reserve[1],DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);
                    Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_MVOP_FORCE_WR,0x0002,DS_IP,DS_MVOP,&PSTXC_DS_CMDCNT);

                    pDBreg->u16LBOffset = 0; // mvop do crop, align in 2pixel, so xc don't need crop
                }
            }

            //H pre-scaling
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_04_L,(MS_U16)(pDBreg->u32H_PreScalingRatio>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8104XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_05_L,(MS_U16)(pDBreg->u32H_PreScalingRatio>>16),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8105XXXX
            //V pre-scaling
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_08_L,(MS_U16)(pDBreg->u32V_PreScalingRatio>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8108XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_09_L,(MS_U16)(pDBreg->u32V_PreScalingRatio>>16),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8109XXXX
            //H post-scaling
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK23_07_L,(MS_U16)(pDBreg->u32H_PostScalingRatio>>00),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 9187XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK23_08_L,(MS_U16)(pDBreg->u32H_PostScalingRatio>>16),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 9188XXXX
            //V post-scaling
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK23_09_L,(MS_U16)(pDBreg->u32V_PostScalingRatio>>00),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 9189XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK23_0A_L,(MS_U16)(pDBreg->u32V_PostScalingRatio>>16),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 918AXXXX

            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_18_L,(MS_U16)(pDBreg->u16VWritelimit>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8918XXXX

            if(IsVMirrorMode(MAIN_WINDOW))
            {
                Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_08_L,(MS_U16)(pDBreg->u32DNRBase0>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);
                Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_09_L,(MS_U16)(pDBreg->u32DNRBase0>>16),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);
            }
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_0F_L,(MS_U16)(pDBreg->u16DNRFetch>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 890FXXXX

            //H_mirror_offset
            if(IsHMirrorMode(MAIN_WINDOW)||IsVMirrorMode(MAIN_WINDOW))
            {
                XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] VB_width:%d framNum:%d u8BitPerPixel:%d  \n",__func__,__LINE__,gSrcInfo[MAIN_WINDOW].Status2.u16VirtualBox_Width,MDrv_XC_TransFrameNumToFactor(pInstance,gSrcInfo[MAIN_WINDOW].Status2.eFrameStoreNumber, gSrcInfo[MAIN_WINDOW].bLinearMode, _FIELD_PACKING_MODE_SUPPORTED),gSrcInfo[MAIN_WINDOW].u8BitPerPixel);

                MS_U32 H_mirror_offset;
                H_mirror_offset = (gSrcInfo[MAIN_WINDOW].Status2.u16VirtualBox_Width * gSrcInfo[MAIN_WINDOW].u8BitPerPixel / 8 * MDrv_XC_TransFrameNumToFactor(pInstance,gSrcInfo[MAIN_WINDOW].Status2.eFrameStoreNumber, gSrcInfo[MAIN_WINDOW].bLinearMode, _FIELD_PACKING_MODE_SUPPORTED)) / BYTE_PER_WORD;

                Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_1C_L,H_mirror_offset,DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 891CXXXX
            }
            else
            {
                Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_1C_L,0x0000,DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 891CXXXX
            }

            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_10_L, (MS_U16)(pDBreg->u32OPMBase0>>00),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); // OPM base0  //0xFFFF0009 8910XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_11_L,(MS_U16)(pDBreg->u32OPMBase0>>16),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); // OPM base0   //0xFFFF0009 8911XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK12_17_L,(MS_U16)(pDBreg->u16OPMFetch>>00),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); // OPM fetch   //0xFFFF0009 8917XXXX
            //Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK20_15_L, (MS_U16)(pDBreg->u16VLen>>00),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); // V Len
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK20_1D_L,(MS_U16)(pDBreg->u16LBOffset&0xFF),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); //LBOffset    //0xFFFF0009 901DXXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK20_1D_L,(MS_U16)(pDBreg->u16LBOffset&0xFF),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); //LBOffset    //0xFFFF0009 901DXXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK20_15_L, (MS_U16)(pDBreg->u16VLen>>00),DS_OP,DS_XC,&PSTXC_DS_CMDCNT); // V Len          //0xFFFF0009 9015XXXX
            //Cap info
            /// before enable ML bit mask feature, the capture size for 2P setting BK01_07[15] need to be considered
            if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, BIT(15)))
                pDBreg->u16H_CapSize |= 0x8000;
            else
                pDBreg->u16H_CapSize |= 0x0000;

            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK01_06_L,(MS_U16)(pDBreg->u16V_CapSize>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8086XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK01_07_L,(MS_U16)(pDBreg->u16H_CapSize>>00),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);//0xFFFF0009 8087XXXX

            //Disp info
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK10_08_L,(MS_U16)(pDBreg->u16H_DisStart),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);  //0xFFFF0009 8808XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK10_09_L,(MS_U16)(pDBreg->u16H_DisEnd),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);    //0xFFFF0009 8809XXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK10_0A_L,(MS_U16)(pDBreg->u16V_DisStart),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);  //0xFFFF0009 880AXXXX
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK10_0B_L,(MS_U16)(pDBreg->u16V_DisEnd),DS_OP,DS_XC,&PSTXC_DS_CMDCNT);    //0xFFFF0009 880BXXXX

            //toggle reg_ds_ipm_active_set in last DS IP command
            MS_U32 u32SW_Reset_IPM = 0;
            u32SW_Reset_IPM = 0x0100 ;//bit8 : reg_ds_ipm_active_set
            ActiveSWClearEn |= u32SW_Reset_IPM;
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK1F_17_L,(MS_U16)(ActiveSWClearEn),DS_IP,DS_XC,&PSTXC_DS_CMDCNT);

            MS_U8 u8MaxCmdCnt = pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * 2;// It has two 64bit commands per MIU bus width

            //XC_PRINTF("[%s,%5d] u16CMDCNT_IPM:%d   u8MaxCnt:%d \n",__func__,__LINE__,PSTXC_DS_CMDCNT.u16CMDCNT_IPM,u8MaxCmdCnt);
            //XC_PRINTF("[%s,%5d] u16CMDCNT_OPM:%d   u8MaxCnt:%d \n",__func__,__LINE__,PSTXC_DS_CMDCNT.u16CMDCNT_OPM,u8MaxCmdCnt);
            if(PSTXC_DS_CMDCNT.u16CMDCNT_IPM < u8MaxCmdCnt)
            {
                Hal_SC_Add_NullCommand(pInstance,MAIN_WINDOW,DS_IP,&PSTXC_DS_CMDCNT);
            }
            if(PSTXC_DS_CMDCNT.u16CMDCNT_OPM < u8MaxCmdCnt)
            {
                Hal_SC_Add_NullCommand(pInstance,MAIN_WINDOW,DS_OP,&PSTXC_DS_CMDCNT);
            }

        }
    }
}

void Hal_SC_SWDS_Fire(void *pInstance, P_SC_SWDB_INFO pDBreg, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow]++;
    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] CurIdx:%d  \n",__func__,__LINE__,(int)pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow]);

    pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] = pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow] % DS_BUFFER_NUM_EX;
    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] CurIdx_Ring:%d  \n",__func__,__LINE__,(int)pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow])
}

E_APIXC_ReturnValue Hal_SC_VIP_Peaking_Setting(void *pInstance, SCALER_WIN eWindow)
{
    UNUSED(eWindow);
    return E_APIXC_RET_FAIL_FUN_NOT_SUPPORT;
}

E_APIXC_ReturnValue Hal_SC_support_source_to_ve(void *pInstance, MS_U16* pOutputCapability)
{
    *pOutputCapability = E_XC_IP | E_XC_OP2 | E_XC_OVERLAP;
    return E_APIXC_RET_OK;
}

E_APIXC_ReturnValue Hal_SC_set_output_capture_enable(void *pInstance, MS_BOOL bEnable,E_XC_SOURCE_TO_VE eSourceToVE)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_BOOL bCaptureEna;
    MS_U16 u16CaptureSrc;
    // Current only support IP and OP2
    bCaptureEna = bEnable;
    switch(eSourceToVE)
    {
	    case E_XC_OP2:
            u16CaptureSrc = 8;
	        break;
	    case E_XC_GAM:
            u16CaptureSrc = 5;
	        break;
	    case E_XC_DITHER:
            u16CaptureSrc = 6;
	        break;
	    case E_XC_OVERLAP:
            u16CaptureSrc = 7;
	        break;
        default:
            u16CaptureSrc = 0;
            bCaptureEna = FALSE;
            break;
    }

    if(bCaptureEna)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, BIT(11), BIT(11));    // Disable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_46_L, u16CaptureSrc<<4, BMASK(7:4));            // Disable
    }
    else
    {
        //DIP and VE Opcapture both need enable this bit, so dont disable it.
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, 0, BIT(11));   // Disable
    }
    return E_APIXC_RET_OK; // Support Scaler OP -> VE
}

/******************************************************************************/
///Set output DE window size
///@param pstWindow \b IN
///-  pointer to window information
/******************************************************************************/
void Hal_SC_set_de_window(void *pInstance, XC_PANEL_INFO *pPanel_Info)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
#ifdef new_chakra
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_04_L, pPanel_Info->u16HStart);                                // DE H start
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_05_L, pPanel_Info->u16HStart + pPanel_Info->u16Width - 1);    // DE H end
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_06_L, pPanel_Info->u16VStart);                                // DE V start
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_07_L, pPanel_Info->u16VStart + pPanel_Info->u16Height - 1);   // DE V end
#else
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_04_L, pPanel_Info->u16HStart);                                // DE H start
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_05_L, pPanel_Info->u16HStart + pPanel_Info->u16Width - 1);    // DE H end
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_06_L, pSrcInfo->u8DE_V_Start);                                // DE V start
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_07_L, pSrcInfo->u16DE_V_End);   // DE V end
#endif
}

void Hal_SC_get_disp_de_window(void *pInstance, MS_WINDOW_TYPE *pWin)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    pWin->x = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_04_L);
    pWin->y = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_06_L);
    pWin->width = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_05_L) - pWin->x + 1;
    pWin->height= SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_07_L) - pWin->y + 1;
}

MS_PHY Hal_SC_Get_DNRBase0(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_08_L);     // input address0
    }
    else
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_48_L);     // input address0
    }
}

MS_PHY Hal_SC_Get_DNRBase1(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0A_L);     // input address1
    }
    else
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4A_L);     // input address1
    }
}

MS_PHY Hal_SC_Get_OPMBase0(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_10_L);     // output address0
    }
    else
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_50_L);     // output address0
    }
}

MS_PHY Hal_SC_Get_OPMBase1(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_12_L);     // output address1
    }
    else
    {
        return SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_52_L);     // output address1
    }
}

MS_PHY Hal_SC_Get_FRCMBaseAddr(void *pInstance, MS_U8 u8id,SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(eWindow);
    return 0;
}

MS_U8 Hal_SC_Get_LBOffset(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        return SC_R2BYTEMSK(0, REG_SC_BK20_1D_L, 0x00FF);
    }
    else
    {
        return (SC_R2BYTEMSK(0, REG_SC_BK20_1D_L, 0xFF00) >> 8);
    }
}

void Hal_SC_Set_LBOffset(void *pInstance, MS_U8 u8LBOffset, SCALER_WIN eWindow)
{
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(0, REG_SC_BK20_1D_L, u8LBOffset, 0x00FF);
    }
    else
    {
        SC_W2BYTEMSK(0, REG_SC_BK20_1D_L, u8LBOffset << 8, 0xFF00);
    }
}

void Hal_SC_set_DNRBase0(void *pInstance, MS_PHY u32DNRBase0, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_08_L, u32DNRBase0 / BYTE_PER_WORD);     // input address0
    }
    else
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_48_L, u32DNRBase0 / BYTE_PER_WORD);     // input address0
    }
}

void Hal_SC_set_DNRBase1(void *pInstance, MS_PHY u32DNRBase1, SCALER_WIN eWindow)
{
    UNUSED(u32DNRBase1);
    UNUSED(eWindow);
}

void Hal_SC_set_DNRBase2(void *pInstance, MS_PHY u32DNRBase2, SCALER_WIN eWindow)
{
    UNUSED(u32DNRBase2);
    UNUSED(eWindow);
}

void Hal_SC_set_OPMBase0(void *pInstance, MS_PHY u32OPMBase0, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_10_L, u32OPMBase0 / BYTE_PER_WORD);     // input address0
    }
    else
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_50_L, u32OPMBase0 / BYTE_PER_WORD);     // input address0
    }
}

void Hal_SC_set_OPMBase1(void *pInstance, MS_PHY u32OPMBase1, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_12_L, u32OPMBase1 / BYTE_PER_WORD);     // input address1
    }
    else
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_52_L, u32OPMBase1 / BYTE_PER_WORD);     // input address1
    }
}

void Hal_SC_set_OPMBase2(void *pInstance, MS_PHY u32OPMBase2, SCALER_WIN eWindow)
{
    UNUSED(u32OPMBase2);
    UNUSED(eWindow);
}

void Hal_SC_set_FRCM_WBase0(void *pInstance, MS_PHY u32FRCM_WBase0, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32FRCM_WBase0);
    UNUSED(eWindow);
}

void Hal_SC_set_FRCM_WBase1(void *pInstance, MS_PHY u32FRCM_WBase1, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32FRCM_WBase1);
    UNUSED(eWindow);
}

void Hal_SC_set_FRCM_WBase2(void *pInstance, MS_PHY u32FRCM_WBase2, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32FRCM_WBase2);
    UNUSED(eWindow);
}

void Hal_SC_set_FRCM_RBase0(void *pInstance, MS_PHY u32FRCM_RBase0, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32FRCM_RBase0);
    UNUSED(eWindow);
}

void Hal_SC_set_FRCM_RBase1(void *pInstance, MS_PHY u32FRCM_RBase1, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32FRCM_RBase1);
    UNUSED(eWindow);
}

void Hal_SC_set_FRCM_RBase2(void *pInstance, MS_PHY u32FRCM_RBase2, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32FRCM_RBase2);
    UNUSED(eWindow);
}

void Hal_SC_set_Dual_DNRBase0(void *pInstance, MS_PHY u32DNRBase0, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32DNRBase0);
    UNUSED(eWindow);
}

void Hal_SC_set_Dual_DNRBase1(void *pInstance, MS_PHY u32DNRBase1, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32DNRBase1);
    UNUSED(eWindow);

}

void Hal_SC_set_Dual_DNRBase2(void *pInstance, MS_PHY u32DNRBase2, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32DNRBase2);
    UNUSED(eWindow);
}

void Hal_SC_set_Dual_OPMBase0(void *pInstance, MS_PHY u32OPMBase0, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32OPMBase0);
    UNUSED(eWindow);
}

void Hal_SC_set_Dual_OPMBase1(void *pInstance, MS_PHY u32OPMBase1, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(u32OPMBase1);
    UNUSED(eWindow);
}

void Hal_SC_set_Dual_OPMBase2(void *pInstance, MS_PHY u32OPMBase2, SCALER_WIN eWindow)
{
    UNUSED(u32OPMBase2);
    UNUSED(eWindow);
}

void Hal_SC_set_WriteVLength(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK20_15_L, 0x0);     // Write V length
    }
    else
    {
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK20_16_L, 0x0);     // Write V length
    }
}

void Hal_SC_set_memoryaddress(void *pInstance, MS_PHY u32DNRBase0, MS_PHY u32DNRBase1, MS_PHY u32DNRBase2, MS_PHY u32OPMBase0, MS_PHY u32OPMBase1, MS_PHY u32OPMBase2, SCALER_WIN eWindow)
{
    Hal_SC_set_DNRBase0(pInstance, u32DNRBase0, eWindow);
    Hal_SC_set_DNRBase1(pInstance, u32DNRBase1, eWindow);
    Hal_SC_set_DNRBase2(pInstance, u32DNRBase2, eWindow);
    Hal_SC_set_OPMBase0(pInstance, u32OPMBase0, eWindow);
    Hal_SC_set_OPMBase1(pInstance, u32OPMBase1, eWindow);
    Hal_SC_set_OPMBase2(pInstance, u32OPMBase2, eWindow);
    Hal_SC_set_WriteVLength(pInstance, eWindow); // Write V length
}

void Hal_SC_set_frcm_memoryaddress(void *pInstance, MS_PHY u32FRCM_WBase0, MS_PHY u32FRCM_WBase1, MS_PHY u32FRCM_WBase2, MS_PHY u32FRCM_RBase0, MS_PHY u32FRCM_RBase1, MS_PHY u32FRCM_RBase2, SCALER_WIN eWindow)
{
    Hal_SC_set_FRCM_WBase0(pInstance, u32FRCM_WBase0, eWindow);
    Hal_SC_set_FRCM_WBase1(pInstance, u32FRCM_WBase1, eWindow);
    Hal_SC_set_FRCM_WBase2(pInstance, u32FRCM_WBase2, eWindow);
    Hal_SC_set_FRCM_RBase0(pInstance, u32FRCM_RBase0, eWindow);
    Hal_SC_set_FRCM_RBase1(pInstance, u32FRCM_RBase1, eWindow);
    Hal_SC_set_FRCM_RBase2(pInstance, u32FRCM_RBase2, eWindow);
}

void Hal_SC_set_dual_memoryaddress(void *pInstance, MS_PHY u32DNRBase0, MS_PHY u32DNRBase1, MS_PHY u32DNRBase2, MS_PHY u32OPMBase0, MS_PHY u32OPMBase1, MS_PHY u32OPMBase2, SCALER_WIN eWindow)
{
    Hal_SC_set_Dual_DNRBase0(pInstance, u32DNRBase0, eWindow);
    Hal_SC_set_Dual_DNRBase1(pInstance, u32DNRBase1, eWindow);
    Hal_SC_set_Dual_DNRBase2(pInstance, u32DNRBase2, eWindow);
    Hal_SC_set_Dual_OPMBase0(pInstance, u32OPMBase0, eWindow);
    Hal_SC_set_Dual_OPMBase1(pInstance, u32OPMBase1, eWindow);
    Hal_SC_set_Dual_OPMBase2(pInstance, u32OPMBase2, eWindow);
}

static SC_MIUMASK_t Hal_SC_get_miu0mask(void)
{
    SC_MIUMASK_t mask;

    mask.u16MiuG0Mask = MDrv_Read2Byte(MIU0_G0_REQUEST_MASK);
    mask.u16MiuG1Mask = MDrv_Read2Byte(MIU0_G1_REQUEST_MASK);
    mask.u16MiuG2Mask = MDrv_Read2Byte(MIU0_G2_REQUEST_MASK);
    mask.u16MiuG3Mask = MDrv_Read2Byte(MIU0_G3_REQUEST_MASK);
    mask.u16MiuG4Mask = MDrv_Read2Byte(MIU0_G4_REQUEST_MASK);

    return mask;
}

static SC_MIUMASK_t Hal_SC_get_miu1mask(void)
{
    SC_MIUMASK_t mask;

    mask.u16MiuG0Mask = MDrv_Read2Byte(MIU1_G0_REQUEST_MASK);
    mask.u16MiuG1Mask = MDrv_Read2Byte(MIU1_G1_REQUEST_MASK);
    mask.u16MiuG2Mask = MDrv_Read2Byte(MIU1_G2_REQUEST_MASK);
    mask.u16MiuG3Mask = MDrv_Read2Byte(MIU1_G3_REQUEST_MASK);
    mask.u16MiuG4Mask = MDrv_Read2Byte(MIU1_G4_REQUEST_MASK);

    return mask;
}

static void Hal_SC_set_miu0mask(SC_MIUMASK_t mask)
{
    MDrv_Write2Byte(MIU0_G0_REQUEST_MASK, mask.u16MiuG0Mask);
    MDrv_Write2Byte(MIU0_G1_REQUEST_MASK, mask.u16MiuG1Mask);
    MDrv_Write2Byte(MIU0_G2_REQUEST_MASK, mask.u16MiuG2Mask);
    MDrv_Write2Byte(MIU0_G3_REQUEST_MASK, mask.u16MiuG3Mask);
}

static void Hal_SC_set_miu1mask(SC_MIUMASK_t mask)
{
    MDrv_Write2Byte(MIU1_G0_REQUEST_MASK, mask.u16MiuG0Mask);
    MDrv_Write2Byte(MIU1_G1_REQUEST_MASK, mask.u16MiuG1Mask);
    MDrv_Write2Byte(MIU1_G2_REQUEST_MASK, mask.u16MiuG2Mask);
    MDrv_Write2Byte(MIU1_G3_REQUEST_MASK, mask.u16MiuG3Mask);
}

void Hal_SC_Enable_MiuMask(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->sthal_SC.Miu0MaskOld = Hal_SC_get_miu0mask();
    pXCResourcePrivate->sthal_SC.Miu1MaskOld = Hal_SC_get_miu1mask();

    pXCResourcePrivate->sthal_SC.Miu0Mask = pXCResourcePrivate->sthal_SC.Miu0MaskOld;
    pXCResourcePrivate->sthal_SC.Miu1Mask = pXCResourcePrivate->sthal_SC.Miu1MaskOld;

    pXCResourcePrivate->sthal_SC.Miu0Mask.u16MiuG0Mask |= MIU_SC_G0REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu0Mask.u16MiuG1Mask |= MIU_SC_G1REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu0Mask.u16MiuG2Mask |= MIU_SC_G2REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu0Mask.u16MiuG3Mask |= MIU_SC_G3REQUEST_MASK;


    pXCResourcePrivate->sthal_SC.Miu1Mask.u16MiuG0Mask |= MIU_SC_G0REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu1Mask.u16MiuG1Mask |= MIU_SC_G1REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu1Mask.u16MiuG2Mask |= MIU_SC_G2REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu1Mask.u16MiuG3Mask |= MIU_SC_G3REQUEST_MASK;

    pXCResourcePrivate->sthal_SC.Miu2Mask.u16MiuG0Mask |= MIU_SC_G0REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu2Mask.u16MiuG1Mask |= MIU_SC_G1REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu2Mask.u16MiuG2Mask |= MIU_SC_G2REQUEST_MASK;
    pXCResourcePrivate->sthal_SC.Miu2Mask.u16MiuG3Mask |= MIU_SC_G3REQUEST_MASK;

    Hal_SC_set_miu0mask(pXCResourcePrivate->sthal_SC.Miu0Mask);
    Hal_SC_set_miu1mask(pXCResourcePrivate->sthal_SC.Miu1Mask);
}

void Hal_SC_Disable_MiuMask(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    Hal_SC_set_miu0mask(pXCResourcePrivate->sthal_SC.Miu0MaskOld);
    Hal_SC_set_miu1mask(pXCResourcePrivate->sthal_SC.Miu1MaskOld);
}

void Hal_SC_set_miusel(void *pInstance, MS_U8 u8MIUSel)
{
    // Scaler control MIU by itself
    // So MIU1 IP-select is set to 1. At this moment, MIU0 Miu select is not working.
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK7F_11_L, BIT(0)| BIT(1)| BIT(7))==0)
    {
        // When MIU select controlled by XC internal via BK12_05, IPM/OPM just access the same MIU only.
        // For monet Mirror under enbale dual MIU, IPM/OPM need access different miu,
        // so miu select must be controlled by MIU (BK7F_10[1..0]).
        //BK7F_10[10] is menuload MIU select from Hal_XC_MLoad_set_miusel
        if (u8MIUSel == 0)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK7F_10_L, BIT(10), BIT(0) | BIT(1)| BIT(7)|BIT(10));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK7F_10_L, BIT(0) | BIT(1)| BIT(7)|BIT(10), BIT(0) | BIT(1)| BIT(7)|BIT(10));
        }

    }
    else
    {
        if (u8MIUSel==0)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_05_L, 0x0000, 0x0010);     // reg_miu_select_f2 to MIU0
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_44_L, 0x0000, 0x4000);     // reg_miu_select_f1 to MIU0
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_05_L, 0x0010, 0x0010);     // reg_miu_select_f2 to MIU1
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_44_L, 0x4000, 0x4000);     // reg_miu_select_f1 to MIU1
        }
        MDrv_Write2ByteMask((REG_MIU0_BASE + 0xF0), 0x00, MIU_SC_G0REQUEST_MASK); // MIU select (Group0)
        MDrv_Write2ByteMask((REG_MIU0_BASE + 0xF2), 0x00, MIU_SC_G1REQUEST_MASK); // MIU select (Group1)
        MDrv_Write2ByteMask((REG_MIU0_BASE + 0xF4), 0x00, MIU_SC_G2REQUEST_MASK); // MIU select (Group2)
        MDrv_Write2ByteMask((REG_MIU0_BASE + 0xF6), 0x00, MIU_SC_G3REQUEST_MASK); // MIU select (Group3)

        MDrv_Write2ByteMask((REG_MIU1_BASE + 0xF0), MIU_SC_G0REQUEST_MASK, MIU_SC_G0REQUEST_MASK); // MIU select (Group0)
        MDrv_Write2ByteMask((REG_MIU1_BASE + 0xF2), MIU_SC_G1REQUEST_MASK, MIU_SC_G1REQUEST_MASK); // MIU select (Group1)
        MDrv_Write2ByteMask((REG_MIU1_BASE + 0xF4), MIU_SC_G2REQUEST_MASK, MIU_SC_G2REQUEST_MASK); // MIU select (Group2)
        MDrv_Write2ByteMask((REG_MIU1_BASE + 0xF6), MIU_SC_G3REQUEST_MASK, MIU_SC_G3REQUEST_MASK); // MIU select (Group3)

    }
}

void Hal_SC_get_miusel(void *pInstance, SC_MIUSEL_t* stMIUSel)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK7F_11_L, BIT(0)| BIT(1)| BIT(7))==0)
    {
        if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK7F_10_L,  BIT(0) | BIT(1)| BIT(7)|BIT(10)) == BIT(10))
        {
            stMIUSel-> u8MainFBSel = 0;
            stMIUSel-> u8SubFBSel = 0;
        }

        if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK7F_10_L, BIT(0) | BIT(1)| BIT(7)|BIT(10)) == (BIT(0) | BIT(1)| BIT(7)|BIT(10)))
        {
            stMIUSel-> u8MainFBSel = 1;
            stMIUSel-> u8SubFBSel = 1;
        }
    }
    else
    {
        if(SC_R2BYTEMSK(0, REG_SC_BK12_05_L, BIT(4)))
        {
            stMIUSel-> u8MainFBSel = 1;
        }
        else
        {
            stMIUSel-> u8MainFBSel = 0;
        }

        if(SC_R2BYTEMSK(0, REG_SC_BK12_44_L, BIT(14)))
        {
            stMIUSel-> u8SubFBSel = 1;
        }
        else
        {
            stMIUSel-> u8SubFBSel = 0;
        }
    }
}

void Hal_SC_set_dual_miusel(void *pInstance, MS_U8 u8MIUSel)
{
    UNUSED(pInstance);
    UNUSED(u8MIUSel);
}

void Hal_SC_set_dual_disable(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK11_29_L, 0, BIT(15)); // reg_miu_select_f1 to MIU1
}

void Hal_SC_get_dual_miusel(void *pInstance, SC_MIUSEL_t* stMIUSel)
{
    UNUSED(pInstance);
    UNUSED(stMIUSel);
}

void Hal_SC_set_blsk(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_21_L, bEn ? BIT(12) : 0, BIT(12));
}

void Hal_SC_set_blsk_burst(void *pInstance, MS_BOOL bEn)
{
    _MLOAD_ENTRY(pInstance);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_21_L, bEn ? BIT(12) : 0, BIT(12));
    MDrv_XC_MLoad_Fire(pInstance, TRUE);
    _MLOAD_RETURN(pInstance);
}

void Hal_SC_set_main_black_screen_burst(void *pInstance, MS_BOOL bEn)
{
    _MLOAD_ENTRY(pInstance);

    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_19_L, bEn ? BIT(1) : 0, BIT(1));
    MDrv_XC_MLoad_Fire(pInstance, TRUE);

    _MLOAD_RETURN(pInstance);
}

void Hal_SC_set_main_sub_black_screen_burst(void *pInstance, MS_BOOL bEn)
{
    _MLOAD_ENTRY(pInstance);

    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_19_L, bEn ? (BIT(5)|BIT(1)) : 0, (BIT(6)|BIT(5)|BIT(1)));
    MDrv_XC_MLoad_Fire(pInstance, TRUE);

    _MLOAD_RETURN(pInstance);
}

void Hal_SC_set_main_black_screen(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_19_L, bEn ? BIT(1) : 0, BIT(1));
}

void Hal_SC_set_main_sub_black_screen(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_19_L, bEn ? (BIT(5)|BIT(1)) : 0, (BIT(6)|BIT(5)|BIT(1)));
}

void Hal_SC_set_sub_blue_screen_burst(void *pInstance, MS_BOOL bEn, MS_BOOL bBlue)
{
    _MLOAD_ENTRY(pInstance);

    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_19_L, bBlue ? BIT(6) : 0, BIT(6));
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_19_L, bEn ? BIT(5) : 0, BIT(5));
    MDrv_XC_MLoad_Fire(pInstance, TRUE);

    _MLOAD_RETURN(pInstance);
}

void Hal_SC_set_sub_blue_screen(void *pInstance, MS_BOOL bEn, MS_BOOL bBlue)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_19_L, bBlue ? BIT(6) : 0, BIT(6));
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_19_L, bEn ? BIT(5) : 0, BIT(5));
}

E_APIXC_ReturnValue Hal_SC_IP_Memory_Write_Request(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    if(MAIN_WINDOW == eWindow)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, bEnable? 0 : BIT(0) , BIT(0));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, bEnable? 0 : BIT(0) , BIT(0));
    }

    return E_APIXC_RET_OK;
}

E_APIXC_ReturnValue Hal_SC_IP_Memory_Read_Request(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    if(MAIN_WINDOW == eWindow)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_02_L, bEnable? 0 : BIT(14) , BIT(14));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_42_L, bEnable? 0 : BIT(14) , BIT(14));
    }
    return E_APIXC_RET_OK;
}

E_APIXC_ReturnValue Hal_SC_OP_Memory_Write_Request(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_67_L, bEnable? 0 : BIT(1) , BIT(1));//This will stop OPW and OP memory write request
    return E_APIXC_RET_OK;
}

E_APIXC_ReturnValue Hal_SC_frcmw_Memory_Write_Request(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
    UNUSED(eWindow);
    return E_APIXC_RET_OK;
}

E_APIXC_ReturnValue Hal_SC_frcmr_Memory_Read_Request(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    return E_APIXC_RET_OK;
}

void Hal_SC_disable_inputsource_burst(void *pInstance, MS_BOOL bDisable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    _MLOAD_ENTRY(pInstance);

    // HW PIP architeucture
    // Becasue BK3_02[8] and BK20_11[15] can not be enabled toghter,
    // otherwise garbage will be showed,we need to use BK12_47[0] to instead.
    if( eWindow == MAIN_WINDOW )
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK01_02_L, (bDisable ? BIT(7):0), BIT(7));
    }
    else
    {
        //MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_02_L, (bDisable ? BIT(7):0), BIT(7));
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_47_L, (bDisable ? BIT(0) : 0), BIT(0));
    }
    MDrv_XC_MLoad_Fire(pInstance, TRUE);
    _MLOAD_RETURN(pInstance);
}

void Hal_SC_disable_inputsource(void *pInstance, MS_BOOL bDisable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_02_L, (bDisable ? BIT(7):0), BIT(7));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_02_L, (bDisable ? BIT(7):0), BIT(7));
    }
}


MS_U16 Hal_SC_Is_InputSource_Disable(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
        return (SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_02_L)&0x80);
    else
    {
        if((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L)&0x01) == 0)
        {
            return (SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_02_L)&0x80);
        }
        else
        {
            return TRUE;
        }
    }
}


void Hal_SC_set_nosignal_color(void *pInstance, MS_U8 u8Color,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
    {
        _MLOAD_ENTRY(pInstance);
        if ( eWindow == MAIN_WINDOW )
        {
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_24_L, u8Color, LBMASK);
        }
        else
        {
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_17_L, ((MS_U16)u8Color)<<8, HBMASK);
        }
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
        _MLOAD_RETURN(pInstance);
    }
    else
    {
        if ( eWindow == MAIN_WINDOW )
        {
#ifdef new_chakra
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_24_L, u8Color, LBMASK);
#else
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_24_L, u8Color, LBMASK);
#endif
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_17_L, ((MS_U16)u8Color)<<8, HBMASK);
        }
    }
}

void Hal_SC_set_fbl(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_01_L, (bEn ? BIT(7): 0), BIT(7));  //Enable/Disable FBL
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_02_L, (bEn ? BIT(14):0), BIT(14)); //F2 force IP read request disable

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, (bEn ? 0x3:0), 0x3); //F2 IP read/write request disable
}

MS_BOOL Hal_SC_get_fbl(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    return SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_01_L, BIT(7));  //Enable/Disable FBL
}

void Hal_SC_set_freezeimg_burst(void *pInstance, MS_BOOL bEn, SCALER_WIN eWindow)
{
    _MLOAD_ENTRY(pInstance);

    if( eWindow == MAIN_WINDOW )
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_01_L, (bEn<<11), BIT(11));
    }
    else
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_41_L, (bEn<<11), BIT(11));
    }

    MDrv_XC_MLoad_Fire(pInstance, TRUE);
    _MLOAD_RETURN(pInstance);
}


void Hal_SC_set_freezeimg(void *pInstance, MS_BOOL bEn, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if( eWindow == MAIN_WINDOW )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_01_L, (bEn<<11), BIT(11));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_41_L, (bEn<<11), BIT(11));
    }
}

void Hal_SC_set_frcm_freezeimg(void *pInstance, MS_BOOL bEn, SCALER_WIN eWindow)
{
    UNUSED(pInstance);
    UNUSED(bEn);
    UNUSED(eWindow);
}

MS_BOOL Hal_SC_get_freezeimg(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if( eWindow == MAIN_WINDOW )
    {
        return (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_01_L, BIT(11)) ? TRUE: FALSE);
    }
    else
    {
        return (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_41_L, BIT(11)) ? TRUE: FALSE);
    }

}

void Hal_SC_exwith_miuprotect_swreset(void *pInstance, MS_U8 x)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    //reset IP1F2
    //select pattern generator source
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK00_02_L, x, x);
    //MsOS_DelayTask(2);

    //select pattern generator source
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK00_02_L, 0, x);
    //MsOS_DelayTask(2);
}

void Hal_SC_ip_Init_for_internal_timing(void *pInstance, XC_Internal_TimingType timingtype, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == SUB_WINDOW)
    {
        if(Hal_SC_ip_get_IPAutoNoSignal(pInstance, eWindow)) Hal_SC_ip_set_IPAutoNoSignal(pInstance, DISABLE, eWindow);

        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_02_L, 0x104) ;  //Video source
        Hal_SC_exwith_miuprotect_swreset(pInstance, REST_IP_F1);  //when source is changed, we must reset it to make it work
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_03_L, 0x890);

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_21_L, 0x01, 0x03);   //force progressive mode
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_0E_L, BIT(15), BIT(15));   //auto gain 10bit

        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_04_L, 0x020);  //capture V start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_05_L, 0x50) ;  //capture H start

        switch (timingtype)
        {
            case E_XC_480P:
            default:

                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_06_L, 0x1c0) ; // V size
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_07_L, 0x280) ; // h size

                break;
            case E_XC_720P:
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_06_L, 0x290) ; // V size (720 - 64) = 656 = 0x290
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_07_L, 0x460) ; // h size (1280 - 160) = 1120 = 0x460

                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4E_L, 0x0800); //DNR Offset
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4F_L, 0x0460); //DNR Fetch
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_56_L, 0x0800); //OPM Offsest
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_57_L, 0x0460); //OPM Fetch

                break;
            case E_XC_1080P:
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_06_L, 0x3F8) ; // V size (1080 - 64) = 1016 = 0x3F8
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_07_L, 0x6E0) ; // h size (1920 - 160) = 1760 = 0x6E0

                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4E_L, 0x0800); //DNR Offset
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_4F_L, 0x06E0); //DNR Fetch
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_56_L, 0x0800); //OPM Offsest
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_57_L, 0x06E0); //OPM Fetch
                break;
        }
    }
    else
    {
        if(Hal_SC_ip_get_IPAutoNoSignal(pInstance, eWindow)) Hal_SC_ip_set_IPAutoNoSignal(pInstance, DISABLE, eWindow);

        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_02_L, 0x104) ;  //Video source
        Hal_SC_exwith_miuprotect_swreset(pInstance, REST_IP_F2);  //when source is changed, we must reset it to make it work
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_03_L, 0x890);

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_21_L, 0x01, 0x03);   //force progressive mode
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_0E_L, BIT(15), BIT(15));   //auto gain 10bit

        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_04_L, 0x020);  //capture V start
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_05_L, 0x50) ;  //capture H start

        switch (timingtype)
        {
            case E_XC_480P:
            default:

                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_06_L, 0x1c0) ; // V size
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, 0x280) ; // h size

                break;
            case E_XC_720P:
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_06_L, 0x290) ; // V size (720 - 64) = 656 = 0x290
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, 0x460) ; // h size (1280 - 160) = 1120 = 0x460

                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0E_L, 0x0800); //DNR Offset
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0F_L, 0x0460); //DNR Fetch
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_16_L, 0x0800); //OPM Offsest
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_17_L, 0x0460); //OPM Fetch

                break;
            case E_XC_1080P:
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_06_L, 0x3F8) ; // V size (1080 - 64) = 1016 = 0x3F8
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_07_L, 0x6E0) ; // h size (1920 - 160) = 1760 = 0x6E0

                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0E_L, 0x0800); //DNR Offset
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0F_L, 0x06E0); //DNR Fetch
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_16_L, 0x0800); //OPM Offsest
                SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_17_L, 0x06E0); //OPM Fetch
                break;
        }

    }
}

MS_U16 Hal_SC_rgb_average_info(void *pInstance, MS_U16 u16mask, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16value;

    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_0F_L, u16mask, 0x0F);
        u16value=SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_11_L);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_0F_L, u16mask, 0x0F);
        u16value=SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_11_L);
    }

    return u16value;
}


void Hal_SC_autogain_enable(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    //auto gain enable
    if(eWindow == MAIN_WINDOW)
    {
        if(bEnable)
            W2BYTEMSK(REG_SC_BK01_0E_L, 0x11, 0x11);
        else
            W2BYTEMSK(REG_SC_BK01_0E_L, 0x00, 0x11);
    }
    else
    {
        if(bEnable)
            W2BYTEMSK(REG_SC_BK03_0E_L, 0x11, 0x11);
        else
            W2BYTEMSK(REG_SC_BK03_0E_L, 0x00, 0x11);
    }
}

MS_BOOL Hal_SC_autogain_status(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_BOOL bvalue;
    if(eWindow == MAIN_WINDOW)
        bvalue = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_0E_L, BIT(1));
    else
        bvalue = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_0E_L, BIT(1));

    return bvalue;

}

void Hal_SC_set_mirror(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U32 u32NoSigReg, u32MirrorReg;

    if(eWindow == MAIN_WINDOW)
    {
        u32NoSigReg = REG_SC_BK01_02_L;
        u32MirrorReg = REG_SC_BK12_03_L;
    }
    else
    {
        u32NoSigReg = REG_SC_BK03_02_L;
        u32MirrorReg = REG_SC_BK12_43_L;

    }

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32NoSigReg, BIT(7), BIT(7));

    if( bEnable )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32MirrorReg, (BIT(12)|BIT(13)), (BIT(12)|BIT(13)));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32MirrorReg, 0x0, (BIT(12)|BIT(13)));
    }
}

void Hal_SC_set_frcm_mirror(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U32 u32NoSigReg = 0, u32MirrorReg = 0;

    if(eWindow == MAIN_WINDOW)
    {
        u32NoSigReg = REG_SC_BK01_02_L;
        u32MirrorReg = REG_SC_BK32_03_L;
    }
    else
    {
        u32NoSigReg = REG_SC_BK03_02_L;
        u32MirrorReg = REG_SC_BK32_43_L;
    }

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32NoSigReg, BIT(7), BIT(7));

    if( bEnable )
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32MirrorReg, (BIT(12)|BIT(13)), (BIT(12)|BIT(13)));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, u32MirrorReg, 0x0, (BIT(12)|BIT(13)));
    }
}

MS_U16 Hal_SC_GetAVDStatus(void)
{
    return MDrv_Read2Byte(L_BK_AFEC(0x66));
}

void Hal_SC_set_rep_window(void *pInstance, MS_BOOL bEnable,MS_U16 x,MS_U16 y,MS_U16 w,MS_U16 h,MS_U8 u8Color)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, bEnable?BIT(9):0x0, BIT(9));
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_42_L,x);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_43_L,x + w);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_44_L,y);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_45_L,y + h);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_46_L, (~u8Color)<<8, 0xFF00);
}

//--------------------------------------------------
//update display window registers with input window
//IN:
//   pdspwin: input window info
//--------------------------------------------------
void Hal_SC_set_disp_window(void *pInstance, SCALER_WIN eWindow, MS_WINDOW_TYPE *pdspwin)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
    {
        _MLOAD_ENTRY(pInstance);

        if(eWindow == MAIN_WINDOW)
        {
            //Display window
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_08_L, pdspwin->x,VOP_DISPLAY_HSTART_MASK);                  // Display H start
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_09_L, pdspwin->x+pdspwin->width-1,VOP_DISPLAY_HEND_MASK);   // Display H end
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_0A_L, pdspwin->y,VOP_DISPLAY_VSTART_MASK);                  // Display V start
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK10_0B_L, pdspwin->y+pdspwin->height-1,VOP_DISPLAY_VEND_MASK);  // Display V end
        }
        else
        {
            //Display window
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_07_L, pdspwin->x,0xFFF);                  // Display H start
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_08_L, pdspwin->x+pdspwin->width-1,0xFFF);   // Display H end
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_09_L, pdspwin->y,0xFFF);                  // Display V start
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK0F_0A_L, pdspwin->y+pdspwin->height-1,0xFFF);  // Display V end
        }

        MDrv_XC_MLoad_Fire(pInstance, TRUE);
        _MLOAD_RETURN(pInstance);
    }
    else
    {
        if(eWindow == MAIN_WINDOW)
        {
            //Display window
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_08_L, pdspwin->x);                  // Display H start
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_09_L, pdspwin->x+pdspwin->width-1);   // Display H end
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_0A_L, pdspwin->y);                  // Display V start
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_0B_L, pdspwin->y+pdspwin->height-1);  // Display V end
        }
        else
        {
            //Display window
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_07_L, pdspwin->x);                  // Display H start
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_08_L, pdspwin->x+pdspwin->width-1);   // Display H end
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_09_L, pdspwin->y);                  // Display V start
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_0A_L, pdspwin->y+pdspwin->height-1);  // Display V end
        }
    }
}

//--------------------------------------------------
//get display window registers setting
//OUT:
//   pdspwin: Pointer for ouput disp window register
//--------------------------------------------------
void Hal_SC_get_disp_window(void *pInstance, SCALER_WIN eWindow, MS_WINDOW_TYPE *pdspwin)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        //Display window
        pdspwin->x = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_08_L);                   // Display H start
        pdspwin->width  = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_09_L) - pdspwin->x + 1; // Display H end
        pdspwin->y = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_0A_L);                   // Display V start
        pdspwin->height = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_0B_L) - pdspwin->y + 1; // Display V end
    }
    else
    {
        //Display window
        pdspwin->x = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_07_L);                   // Display H start
        pdspwin->width  = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_08_L) - pdspwin->x + 1; // Display H end
        pdspwin->y = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_09_L);                   // Display V start
        pdspwin->height = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_0A_L) - pdspwin->y + 1; // Display V end
    }
}

void Hal_SC_set_Fclk(void *pInstance, EN_SET_FCLK_CASE enCase)
{
    if (enCase == EN_FCLK_FBL)
        MDrv_WriteByteMask(REG_CKG_FCLK, CKG_FCLK_216MHZ, CKG_FCLK_MASK);
    else
        MDrv_WriteByteMask(REG_CKG_FCLK, CKG_FCLK_216MHZ, CKG_FCLK_MASK);
}

void Hal_SC_get_framebuf_Info(void *pInstance, SC_FRAMEBUF_INFO_t *pFrameBufInfo, SCALER_WIN eWindow)
{
    MS_U8 u8Reg;

    if (!pFrameBufInfo) return;

    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    pFrameBufInfo->u32IPMBase0 = ((SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_09_L:REG_SC_BK12_49_L, 0x00FF)<<16) |
                                    (SC_R2BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_08_L:REG_SC_BK12_48_L))) * BYTE_PER_WORD;
    pFrameBufInfo->u32IPMBase1 = ((SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_0B_L:REG_SC_BK12_4B_L, 0x00FF)<<16) |
                                    (SC_R2BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_0A_L:REG_SC_BK12_4A_L))) * BYTE_PER_WORD;
    pFrameBufInfo->u32IPMBase2 = ((SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_0D_L:REG_SC_BK12_4D_L, 0x00FF)<<16) |
                                    (SC_R2BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_0C_L:REG_SC_BK12_4C_L))) * BYTE_PER_WORD;
    pFrameBufInfo->u16IPMOffset = SC_R2BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_0E_L:REG_SC_BK12_4E_L);
    pFrameBufInfo->u16IPMFetch = SC_R2BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_0F_L:REG_SC_BK12_4F_L);
    pFrameBufInfo->u16VLength = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_18_L:REG_SC_BK12_58_L, 0x0FFF);
    pFrameBufInfo->bLinearAddrMode = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_03_L:REG_SC_BK12_43_L, BIT(4));
    pFrameBufInfo->bYCSeparate = ( SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_02_L:REG_SC_BK12_42_L, BIT(10)) )?TRUE:FALSE;
    pFrameBufInfo->u32WriteLimitBase = SC_R4BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK0D_42_L:REG_SC_BK0D_44_L);

    pFrameBufInfo->u8BitPerPixel = 24;//default

    u8Reg = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_01_L:REG_SC_BK12_41_L, 0x00FF);
    if (u8Reg & 0x30)
    {//444
        pFrameBufInfo->bMemFormat422 = FALSE;
        if (u8Reg & 0x10)
        { // 444 8BIT
            pFrameBufInfo->u8BitPerPixel = 24;
        }
        else
        { // 444 10BIT
            pFrameBufInfo->u8BitPerPixel = 32;
        }
        pFrameBufInfo->bInterlace = FALSE;
    }
    else
    {//422
        pFrameBufInfo->bMemFormat422 = TRUE;

        if((BIT(8)|BIT(9)) == SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_02_L:REG_SC_BK12_42_L, BIT(8)|BIT(9))) //user mode
        {
            MS_U8 u8MemFmt = SC_R2BYTE(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_02_L:REG_SC_BK12_42_L) & 0x0F;
            if((4 == u8MemFmt) || (5 == u8MemFmt) || (6 == u8MemFmt))
            {
                pFrameBufInfo->u8BitPerPixel = 20;
            }
            else if((8 == u8MemFmt) || (9 == u8MemFmt) || (10 == u8MemFmt) || (11 == u8MemFmt))
            {
                pFrameBufInfo->u8BitPerPixel = 24;
            }
        }
        else
        {
            u8Reg = (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_01_L:REG_SC_BK12_41_L, 0xFF00)) >> 8;

            switch(u8Reg & 0x77)
            {
                case 0x25:
                    pFrameBufInfo->u8BitPerPixel = 24;
                    pFrameBufInfo->bInterlace = TRUE;
                    break;
                case 0x24:
                    pFrameBufInfo->u8BitPerPixel = 20;
                    pFrameBufInfo->bInterlace = TRUE;
                    break;
                case 0x27:
                    pFrameBufInfo->u8BitPerPixel = 16;
                    pFrameBufInfo->bInterlace = TRUE;
                    break;
                case 0x21:
                    if(BIT(1) == SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_04_L:REG_SC_BK12_44_L, BIT(0)|BIT(1)))
                    {
                        pFrameBufInfo->u8BitPerPixel = 24;
                    }
                    else
                    {
                        pFrameBufInfo->u8BitPerPixel = 20;
                    }
                    pFrameBufInfo->bInterlace = FALSE;
                    break;
                case 0x20:
                    pFrameBufInfo->u8BitPerPixel = 16;
                    pFrameBufInfo->bInterlace = FALSE;
                    break;
                case 0x00:
                default:
                    pFrameBufInfo->u8BitPerPixel = 16;
                    pFrameBufInfo->bInterlace = FALSE;
                    break;
            }
        }
    }

    //In M10/J2/A5/A6/A3, New SCMI
    pFrameBufInfo->u8FBNum = (MS_U8)(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, (eWindow == MAIN_WINDOW)?REG_SC_BK12_19_L:REG_SC_BK12_59_L, 0x1F));

#if 0
    printf("base0=0x%x, base1=0x%x, base2=0x%x, offset=%u, 422=%u, i=%u, bpp=%u, fbnum=%u\n",
        (unsigned int)pFrameBufInfo->u32IPMBase0,
        (unsigned int)pFrameBufInfo->u32IPMBase1,
        (unsigned int)pFrameBufInfo->u32IPMBase2,
        pFrameBufInfo->u16IPMOffset,
        pFrameBufInfo->bMemFormat422,
        pFrameBufInfo->bInterlace,
        pFrameBufInfo->u8BitPerPixel,
        pFrameBufInfo->u8FBNum);
#endif
}
void Hal_SC_set_framebuf_Info(void *pInstance, SC_FRAMEBUF_INFO_t pFrameBufInfo)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_PHY u32IPMBase0, u32IPMBase1, u32IPMBase2;
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    u32IPMBase0=pFrameBufInfo.u32IPMBase0/BYTE_PER_WORD;
    u32IPMBase1=pFrameBufInfo.u32IPMBase1/BYTE_PER_WORD;
    u32IPMBase2=pFrameBufInfo.u32IPMBase2/BYTE_PER_WORD;

    //Step 5.4, Memory Limit V : BK12_18[15] = 1, BK12_18[12:0] to the real V line number
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_18_L, (pFrameBufInfo.u16VLength|0x8000),0x8FFF);

//    u32WritelimitBase = ((u32IPMBase0 + u32MemSize) / BYTE_PER_WORD - 1) | 0x2000000;
    SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_1A_L, pFrameBufInfo.u32IPMBase1);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_09_L, (MS_U16)(u32IPMBase0 & 0xFF0000)>>16,0x00FF);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_08_L, (MS_U16)(u32IPMBase0 & 0xFFFF));

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_0B_L, (MS_U16)(u32IPMBase1 & 0xFF0000)>>16,0x00FF);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0A_L, (MS_U16)(u32IPMBase1 & 0xFFFF));

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_0D_L, (MS_U16)(u32IPMBase2 & 0xFF0000)>>16,0x00FF);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0C_L, (MS_U16)(u32IPMBase2 & 0xFFFF));


    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0E_L, pFrameBufInfo.u16IPMOffset);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_0F_L, pFrameBufInfo.u16IPMFetch);
//    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_18_L, (pFrameBufInfo.u16VLength|0x1000),0x1FFF);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_03_L, ((pFrameBufInfo.bLinearAddrMode)?BIT(4):0),BIT(4));

}

MS_U8 Hal_SC_get_cs_det_cnt(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U8 u8val;

    if(eWindow == MAIN_WINDOW)
    {
        u8val = ((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_0C_L) & 0xFF00) >> 8);
    }
    else
    {
        u8val = ((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_0C_L) & 0xFF00) >> 8);
    }
    return u8val;
}

void Hal_SC_set_cs_det_cnt(void *pInstance, MS_U8 u8val, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_0C_L, (((MS_U16)u8val)<<8), 0xFF00);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_0C_L, (((MS_U16)u8val)<<8), 0xFF00);
    }
}

MS_U8 Hal_SC_get_plus_width(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U8 u8val;

    if(eWindow == MAIN_WINDOW)
    {
        u8val = (SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_22_L) & 0x00FF);
    }
    else
    {
        u8val = (SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK03_22_L) & 0x00FF);
    }
    return u8val;
}

void Hal_SC_set_opm_fetch(void *pInstance, SCALER_WIN eWindow, MS_U16 u16OPMFetch)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_17_L, u16OPMFetch, 0x0FFF);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_57_L, u16OPMFetch, 0x0FFF);
    }
}

MS_U16 Hal_SC_get_opm_fetch(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16Val = 0;
    if(eWindow == MAIN_WINDOW)
    {
        u16Val = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_17_L) & 0x0FFF;
    }
    else
    {
        u16Val = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_57_L) & 0x0FFF;
    }
    return u16Val;
}

MS_U8 HAL_SC_get_dnr_setting(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
        return (MS_U8)SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK06_21_L, BIT(1)|BIT(0));
    else
        return (MS_U8)SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK06_01_L, BIT(1)|BIT(0));
}

void HAL_SC_enable_field_avg_y(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_21_L, bEnable ? BIT(6) : 0, BIT(6));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_01_L, bEnable ? BIT(6) : 0, BIT(6));
    }

}

void HAL_SC_enable_field_avg_c(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_21_L, bEnable ? BIT(7) : 0, BIT(7));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_01_L, bEnable ? BIT(7) : 0, BIT(7));
    }
}

void HAL_SC_enable_dnr(void *pInstance, MS_U8 u8Val, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK06_21_L, u8Val, BIT(1)|BIT(0));
    else
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK06_01_L, u8Val, BIT(1)|BIT(0));
}

void HAL_SC_VOP_Set_Contrast_En(void *pInstance, MS_BOOL bEenable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_53_L, (MS_U16)(bEenable?BIT(0):0), BIT(0));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_53_L, (MS_U16)(bEenable?BIT(8):0), BIT(8));
    }
}
void HAL_SC_VOP_Set_Contrast_Value(void *pInstance, MS_XC_VOP_CHANNEL_t eVop_Channel, MS_U16 u16Val, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        switch(eVop_Channel)
        {
            default:
            case XC_VOP_CHR:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_47_L, u16Val, 0x0FFF);
                break;
            case XC_VOP_CHG:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_48_L, u16Val, 0x0FFF);
                break;
            case XC_VOP_CHB:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_49_L, u16Val, 0x0FFF);
                break;
            case XC_VOP_ALL:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_47_L, u16Val, 0x0FFF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_48_L, u16Val, 0x0FFF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_49_L, u16Val, 0x0FFF);
                break;
        }
    }
    else
    {
        switch(eVop_Channel)
        {
            default:
            case XC_VOP_CHR:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4A_L, u16Val, 0x0FFF);
                break;
            case XC_VOP_CHG:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4B_L, u16Val, 0x0FFF);
                break;
            case XC_VOP_CHB:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4C_L, u16Val, 0x0FFF);
                break;
            case XC_VOP_ALL:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4A_L, u16Val, 0x0FFF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4B_L, u16Val, 0x0FFF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4C_L, u16Val, 0x0FFF);
                break;
        }
    }
}

void HAL_SC_VOP_Set_Brightness_En(void *pInstance, MS_BOOL bEenable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_53_L, (MS_U16)(bEenable?BIT(1):0), BIT(1));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_53_L, (MS_U16)(bEenable?BIT(9):0), BIT(9));
    }
}
void HAL_SC_VOP_Set_Brightness_Value(void *pInstance, MS_XC_VOP_CHANNEL_t eVop_Channel, MS_U16 u16Val, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(eWindow == MAIN_WINDOW)
    {
        switch(eVop_Channel)
        {
            default:
            case XC_VOP_CHR:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4D_L, u16Val, 0x07FF);
                break;
            case XC_VOP_CHG:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4E_L, u16Val, 0x07FF);
                break;
            case XC_VOP_CHB:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4F_L, u16Val, 0x07FF);
                break;
            case XC_VOP_ALL:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4D_L, u16Val, 0x07FF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4E_L, u16Val, 0x07FF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_4F_L, u16Val, 0x07FF);
                break;
        }
    }
    else
    {
        switch(eVop_Channel)
        {
            default:
            case XC_VOP_CHR:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_50_L, u16Val, 0x07FF);
                break;
            case XC_VOP_CHG:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_51_L, u16Val, 0x07FF);
                break;
            case XC_VOP_CHB:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_52_L, u16Val, 0x07FF);
                break;
            case XC_VOP_ALL:
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_50_L, u16Val, 0x07FF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_51_L, u16Val, 0x07FF);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_52_L, u16Val, 0x07FF);
                break;
        }
    }
}

void HAL_SC_Set_FB_Num(void *pInstance, SCALER_WIN eWindow, XC_FRAME_STORE_NUMBER enFBType, MS_BOOL bInterlace)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U8 u8FrameCount = 2;

    switch( enFBType )
    {
        case IMAGE_STORE_2_FRAMES:
            u8FrameCount = 2;
            break;
        case IMAGE_STORE_3_FRAMES:
            u8FrameCount = 3;
            break;
        case IMAGE_STORE_4_FRAMES:
            u8FrameCount = 4;
            break;
        case IMAGE_STORE_6_FRAMES:
            u8FrameCount = 6;
            break;
        case IMAGE_STORE_8_FRAMES:
            u8FrameCount = 8;
            break;
        case IMAGE_STORE_12_FRAMES:
            u8FrameCount = 12;
            break;
        default:
            break;
    }

    if (!bInterlace)
    {
        if (eWindow == MAIN_WINDOW)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_19_L, u8FrameCount , BITMASK(4:0) );
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_59_L, u8FrameCount , BITMASK(4:0) );
        }
    }
}

void HAL_SC_Enable_VInitFactor(void *pInstance, MS_BOOL bEnable,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK23_13_L, (MS_U16)(bEnable?BIT(0):0), BIT(0));
    else
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK23_33_L, (MS_U16)(bEnable?BIT(0):0), BIT(0));
}

void HAL_SC_Set_VInitFactorOne(void *pInstance, MS_U32 u32Value,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_03_L, u32Value);
    else
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_23_L, u32Value);
}

void HAL_SC_Set_VInitFactorTwo(void *pInstance, MS_U32 u32Value,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_05_L, u32Value);
    else
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_25_L, u32Value);
}

void HAL_SC_Set_vsd_output_line_count(void *pInstance, MS_BOOL bEnable,MS_U32 u32LineCount,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16OutputLineCount = 0x00;

    if (bEnable)
    {
        u16OutputLineCount = BIT(15);
        u16OutputLineCount |= (MS_U16)(u32LineCount & 0x1FFF);
    }

    if (eWindow == MAIN_WINDOW)
    {
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_37_L, u16OutputLineCount);
    }
    else
    {
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK04_37_L, u16OutputLineCount);
    }

}

/*
 bEnable : Enable input line count.
 bUserMode : 1 -> the input line count will ref u32UserLineCount
                   0 -> the input line count will ref V capture win
*/
void HAL_SC_Set_vsd_input_line_count(void *pInstance, MS_BOOL bEnable,MS_BOOL bUserMode,MS_U32 u32UserLineCount,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16InputLineCount = 0x00;

    if (bEnable)
    {
        u16InputLineCount = BIT(15);

        if (bUserMode)
        {
            u16InputLineCount |= BIT(14);
            u16InputLineCount |= (MS_U16)(u32UserLineCount & 0x1FFF);
        }
    }

    if (eWindow == MAIN_WINDOW)
    {
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_36_L, u16InputLineCount);
    }
    else
    {
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK04_36_L, u16InputLineCount);
    }

}

MS_U32 Hal_SC_CheckSubWinPreScaling(MS_U16 u16ScaleDst,MS_BOOL bInterlace)
{
    UNUSED(u16ScaleDst);
    UNUSED(bInterlace);
    //New chip sub window unnecessary to the same with the main window's pre scaling setting.
    return 0;
}

void HAL_SC_FilmMode_Patch1(void *pInstance)
{
#if 1
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16Value;
    MS_U16 u16RegValue;
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    u16RegValue = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK22_7D_L, 0xFF);
    if(pXCResourcePrivate->sthal_SC.g_bCntFlg)
        pXCResourcePrivate->sthal_SC.g_u16TmpValue = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_02_L, 0xFF);

    if(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_21_L, BIT(6)))
    {
        //Counter
        if(pXCResourcePrivate->sthal_SC.u8Time_count != 0xFF)
            pXCResourcePrivate->sthal_SC.u8Time_count ++;

        if(pXCResourcePrivate->sthal_SC.u8Time_count < u16RegValue)  // fake out duration
           u16Value = 0x06;      // madi fake out enable
        else
           u16Value = 0x00;      // madi fake out disable

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_25_L, (0x10<<8), 0xFF00);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_02_L, 0x22, 0xFF);
        pXCResourcePrivate->sthal_SC.g_bCntFlg = 0;
    }
    else
    {
        pXCResourcePrivate->sthal_SC.u8Time_count = 0;
        u16Value = 0x00;      // madi fake out disable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_25_L, (0x08<<8), 0xFF00);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_02_L, pXCResourcePrivate->sthal_SC.g_u16TmpValue, 0xFF);
        pXCResourcePrivate->sthal_SC.g_bCntFlg = 1;
    }
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0A_21_L, u16Value, BIT(2)|BIT(1));

#else
    MS_U8 u8Bank, u8Value;
    MS_U8 u8RegValue;

    static MS_U8 u8Time_count = 0;

    MDrv_WriteByte(BK_SELECT_00, REG_BANK_MADI); //bk22
    u8RegValue = MDrv_ReadByte(L_BK_MADI(0x7D));

    MDrv_WriteByte(BK_SELECT_00, REG_BANK_FILM);


    if(MDrv_ReadRegBit(L_BK_FILM(0x21), BIT(6)))
    {
        //Counter
        if(u8Time_count != 0xFF)
            u8Time_count ++;

        if(u8Time_count < u8RegValue)  // fake out duration
           u8Value = 0x06;      // madi fake out enable
        else
           u8Value = 0x00;      // madi fake out disable

        MDrv_WriteByte(H_BK_FILM(0x25), 0x10);

    }
    else
    {
        u8Time_count = 0;
        u8Value = 0x00;      // madi fake out disable
        MDrv_WriteByte(H_BK_FILM(0x25), 0x08);
    }

    MDrv_WriteByteMask(L_BK_FILM(0x21), u8Value, BIT(2)|BIT(1));
    MDrv_WriteByte(BK_SELECT_00, u8Bank);
#endif
}

void HAL_SC_EnableFPLL(void)
{
    MDrv_WriteByteMask(L_BK_LPLL(0x0C), BIT(3), BIT(3));
    MDrv_WriteByteMask(L_BK_LPLL(0x0C),      0, BIT(6));
}


static void _HAL_SC_GetFPLLPhaseDiffISR(SC_INT_SRC eIntNum, void *pParam)
{
    volatile MS_XC_GET_FPLL_PHASEDIFF * pFpllPhaseDiff = (volatile MS_XC_GET_FPLL_PHASEDIFF *) pParam;

    pFpllPhaseDiff->u16PhaseDiff = MDrv_Read2Byte(L_BK_LPLL(0x11));
    pFpllPhaseDiff->eFpllDir = (MDrv_Read2Byte(L_BK_LPLL(0x12)) & BIT(0)) == BIT(0) ? E_XC_FPLL_DIR_UP : E_XC_FPLL_DIR_DOWN;
    pFpllPhaseDiff->u8Debounce++;

    if(pFpllPhaseDiff->u8Debounce > 3)
    {
        if(pFpllPhaseDiff->u16PhaseDiff < 0x200)
        {
            pFpllPhaseDiff->eFpllResult = E_XC_FPLL_RES_FINISHED;
        }
        else
        {
            if(pFpllPhaseDiff->u8Debounce > 90)
            {
                pFpllPhaseDiff->eFpllResult = E_XC_FPLL_RES_TIMEOUT;
            }
        }
    }
}

MS_BOOL HAL_SC_WaitFPLLDone(void *pInstance)
{
    MS_XC_GET_FPLL_PHASEDIFF stGetFpllPhaseDiff = {0, 0, E_XC_FPLL_DIR_UNKNOWN, E_XC_FPLL_RES_WAITING};

    MDrv_XC_InterruptAttach(pInstance, SC_INT_VSINT, _HAL_SC_GetFPLLPhaseDiffISR, (void *) &stGetFpllPhaseDiff);
    while(*(volatile MS_BOOL*)(&(stGetFpllPhaseDiff.eFpllResult)) == E_XC_FPLL_RES_WAITING);
    MDrv_XC_InterruptDeAttach(pInstance, SC_INT_VSINT, _HAL_SC_GetFPLLPhaseDiffISR, (void *) &stGetFpllPhaseDiff);

    if(stGetFpllPhaseDiff.eFpllResult == E_XC_FPLL_RES_FINISHED)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

MS_U16 HAL_SC_GetOutputVFreqX100(MS_U32 u32XTAL_Clock)
{
    return ((MS_U16) ((u32XTAL_Clock * 100) / MDrv_Read4Byte(L_BK_LPLL(0x23))));
}

//Line buffer offset between Main and Sub, MAX(Main+Sub) = 1920+960
//Main Win Line buffer offset , start from max size of main's
void HAL_SC_SetMainLineBufferOffset(void *pInstance, MS_U16 u16Linebuffer)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK20_12_L, u16Linebuffer);
}

//Line buffer offset between Main and Sub, MAX(Main+Sub) = 1920+960
//Sub Win Line buffer offset , start from max size of main's
void HAL_SC_SetSubLineBufferOffset(void *pInstance, MS_U16 u16Linebuffer)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK20_13_L, u16Linebuffer);
}

//Select the trig mode
//0: Line base(Line Buffer Mode)
//1: Fill line buffer(Ring Buffer Mode)
void HAL_SC_SetDisplay_LineBuffer_Mode(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_1F_L, (bEnable ? BIT(4) : 0), BIT(4));
}

//Select the start mode
//0: start at advance 1 display line
//1: start at faling edge of Vsync_init
void HAL_SC_SetDisplay_Start_Mode(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_1F_L, (bEnable ? BIT(5) : 0), BIT(5));
}

//bk20_10[10]: Fill the main window's line buffer in vertical blanking for pip left and up corner
//bk20_10[11]: Fill the sub window's line buffer in vertical blanking for pip left and down corner
void HAL_SC_FillLineBuffer(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(bEnable)
    {
        if(eWindow == MAIN_WINDOW)
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, BIT(10), BIT(10));
        else
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, BIT(11), BIT(11));
    }
    else
    {
        if(eWindow == MAIN_WINDOW)
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, 0, BIT(10));
        else
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, 0, BIT(11));
    }
}

void Hal_SC_enable_window(void *pInstance, MS_BOOL bEn,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if (eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, bEn ? BIT(0) : 0, BIT(0));
    }
    else
    {
        // Sub prefill line must be enable, when PIP on (enable input source of sub win)
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, BIT(11) , BIT(11));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, bEn ? BIT(1) : 0, BIT(1));
    }
}

static MS_U16 _Hal_SC_GetInputVPeriod(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    MS_U16 u16VFreq = gSrcInfo[eWindow].u16InputVFreq * 10;
    SC_DBG(printf("(100000+u16VFreq/2)/u16VFreq)=%u, u16VFreq=%u\n",((100000+u16VFreq/2)/u16VFreq), u16VFreq));
    if(u16VFreq == 0)
    {
        return 0;
    }
    else
    {
        return ((100000+u16VFreq/2)/u16VFreq); //Period = 1000/(vfreq/100)
    }
}

void Hal_SC_enable_window_burst(void *pInstance, MS_BOOL bEn,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    _MLOAD_ENTRY(pInstance);
    if (eWindow == MAIN_WINDOW)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_10_L, bEn ? BIT(0) : 0, BIT(0));
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
    }
    else
    {
        if(bEn == TRUE)
        {
            MS_U16 u16extra_req = 0;
            MS_U16 u16Delaytime = 0;

            // When Main is foreground, sub is background, extra must enable.
            u16extra_req = 0x01;

            if(Hal_SC_is_extra_req_en(pInstance, NULL, NULL , NULL , NULL))
            {
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_11_L, BIT(15), BIT(15));
                u16extra_req = u16extra_req | 0x8000;
            }

            // HW PIP architeucture
            // Becasue BK3_02[8] and BK20_11[15] should enable together, otherwise garbage will be showed,
            // we need to use BK12_47[0] to instead. And the default value of BK3_02[8] is 1. So, we need
            // to set it to 0 in this function.
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_11_L, u16extra_req , 0x800F);
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_02_L, 0, 0x0080);

            // Sub prefill line must be enable, when PIP on (enable input source of sub win)
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_10_L, BIT(11), BIT(11) );
            MDrv_XC_MLoad_Fire(pInstance, TRUE);
            //if we let REG_SC_BK20_10_L[1] to enable with other register settings in the same menuload fire
            //it will produce a rectangular horizontal noise. so we move outside to let those register settings
            //to be set first then let REG_SC_BK20_10_L[1] on.

            //betwen REG_SC_BK03_02_L[7] and REG_SC_BK20_10_L[1], we need to delay time of wr mapping mode,
            // to let the data fill in xc sub buffer
            u16Delaytime = _Hal_SC_GetInputVPeriod(pInstance, eWindow) * (Hal_SC_Get_WR_Bank_Mapping(pInstance, eWindow) + 1);
            MsOS_DelayTask(u16Delaytime);

            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_10_L, BIT(1), BIT(1));
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK58_10_L, BIT(0), BIT(0));

            MDrv_XC_MLoad_Fire(pInstance, TRUE);
        }
        else
        {
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_10_L, 0, BIT(1));
            MDrv_XC_MLoad_Fire(pInstance, TRUE);
            MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK03_02_L, 0x0080, 0x0080);
            MDrv_XC_MLoad_Fire(pInstance, TRUE);
        }
    }
    _MLOAD_RETURN(pInstance);
}

void Hal_SC_set_trigger_signal(void)
{
    // only used in U4
}

void Hal_SC_Set_OSD2VE(void *pInstance, EN_VOP_SEL_OSD_XC2VE_MUX  eVOPSelOSD_MUX)
{
    UNUSED(eVOPSelOSD_MUX);
}

MS_BOOL Hal_SC_IsOPMFetchPatch_Enable(void)
{
    //Patch for Janus u01 and T4 U01/02: OPMFetch need +2
    return FALSE;
}
MS_BOOL Hal_SC_Check_HNonLinearScaling(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U16 u16Offset = (SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_15_L)>>8);
    MS_U16 u16MaxOffset = ((SC_R4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_07_L) & 0xFFFFFF)>>12);
    //Non-Linear scaling Postive offset, the maximum offset is HPstRatio[23:12]
    if(((u16Offset & BIT(7)) == 0) && (u16Offset > u16MaxOffset))
    {
        return FALSE;
    }
    return TRUE;
}

//IP2 Pre-Filter enable
void Hal_SC_IP2_PreFilter_Enable(void* pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_48_L, (bEnable?BIT(15):0), BIT(15));
}

void Hal_SC_Set_extra_fetch_line(void *pInstance, MS_U8 u8val)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_17_L, ((MS_U16)(u8val & 0x0F))<<8, 0x0F00);
}

void Hal_SC_Set_extra_adv_line(void *pInstance, MS_U8 u8val)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_17_L, ((MS_U16)(u8val & 0x0F))<<12, 0xF000);
}

void HAL_SC_Set_FPLL_Limit(void *pInstance, MS_U32 *u32PllSet, MS_U32 u32LowBound, MS_U32 u32UpBound, MS_BOOL _bInFPLLDbgMode, MS_U32 _U32LimitD5D6D7)
{
    MS_U32 u32LpllLimitLow, u32LpllLimitHigh;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    //printf("Fpll_Limit: Set %lx, bound (%lx -> %lx)\n", *u32PllSet, u32UpBound, u32LowBound);

    if(_bInFPLLDbgMode)
    {
        MDrv_WriteByteMask(L_BK_LPLL(0x0D), 0x00, BIT(4));          // turn off 2 limit
        if(!pXCResourcePrivate->stdrvXC_MVideo._SContext.bEnableFPLLManualDebug)
        {
            MDrv_Write3Byte(L_BK_LPLL(0x06), _U32LimitD5D6D7);
        }
    }
    else
    {
        MDrv_WriteByteMask(L_BK_LPLL(0x0D), BIT(4), BIT(4));        // turn on 2 limit

        // check if u32PllSet out of range and also the FPLL limit
        if (*u32PllSet <= u32LowBound)
        {
            *u32PllSet = u32LowBound;
            gSrcInfo[MAIN_WINDOW].bEnableFPLL = FALSE;
        }
        else if (*u32PllSet >= u32UpBound)
        {
            *u32PllSet = u32UpBound;
            gSrcInfo[MAIN_WINDOW].bEnableFPLL = FALSE;
        }

        u32LpllLimitHigh = u32UpBound - *u32PllSet;
        u32LpllLimitLow = *u32PllSet - u32LowBound - 1;

        //printf("Fpll set %lx, limit (high %lx, low %lx)\n", *u32PllSet, u32LpllLimitHigh, u32LpllLimitLow);

        if(!pXCResourcePrivate->stdrvXC_MVideo._SContext.bEnableFPLLManualDebug)
        {
            MDrv_Write3Byte(L_BK_LPLL(0x06), u32LpllLimitHigh);
            MDrv_Write3Byte(L_BK_LPLL(0x08), u32LpllLimitLow);
        }

        //printf("Fpll limit reg (high %lx, low %lx)\n", MDrv_Read4Byte(L_BK_LPLL(0x06)), MDrv_Read4Byte(L_BK_LPLL(0x08)));
    }
}

E_XC_3D_OUTPUT_MODE Hal_XC_Get_3D_Output_Mode(void *pInstance)
{
#ifndef DISABLE_3D_FUNCTION
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->stdrvXC_3D._eOutput3DMode;
#else
	return E_XC_3D_OUTPUT_MODE_NONE;
#endif
}

void Hal_XC_H3D_Enable(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_70_L, (bEn<<15), (BIT(15)));
}

void Hal_XC_H3D_Input3DType(void *pInstance, E_XC_3D_INPUT_MODE e3DType)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_7B_L, (e3DType), (BIT(1) | BIT(0)));
}

void Hal_XC_H3D_Breakline_Enable(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_7B_L, (bEn<<7), (BIT(7)));
    if(bEn)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_7B_L, (8<<8), HBMASK);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_7B_L, (0<<8), HBMASK);
    }
}

void Hal_XC_H3D_HDE(void *pInstance, MS_U16 u16Hde)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_71_L, (u16Hde), 0x0FFF);
}

void Hal_XC_H3D_VDE_F0(MS_U16 u16Vde)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_73_L, (u16Vde), 0x0FFF);
}

void Hal_XC_H3D_VDE_F2(MS_U16 u16Vde)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_77_L, (u16Vde), 0x0FFF);
}

void Hal_XC_H3D_HBLANK(MS_U16 u16Hblank)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_70_L, (u16Hblank), 0x03FF);
}

void Hal_XC_H3D_INIT_VBLANK(MS_U8 u8Vblank)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_72_L, (u8Vblank), LBMASK);
}

void Hal_XC_H3D_VBLANK0(MS_U8 u8Vblank)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_74_L, (u8Vblank), LBMASK);
}

void Hal_XC_H3D_VBLANK1(MS_U8 u8Vblank)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_76_L, (u8Vblank), LBMASK);
}

void Hal_XC_H3D_VBLANK2(MS_U8 u8Vblank)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_78_L, (u8Vblank), LBMASK);
}

void Hal_XC_H3D_VSYNC_WIDTH(MS_U8 u8Width)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_7A_L, (u8Width), 0x001F);
}

void Hal_XC_H3D_VSYNC_POSITION(MS_U16 u16Position)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_7A_L, (u16Position), HBMASK);
}

void Hal_XC_H3D_SELECT_REGEN_TIMING(MS_BOOL bEn)
{
    SC_W2BYTEMSK(0, REG_SC_BK01_7B_L, (bEn<<4), (BIT(4)));
}

void Hal_XC_H3D_LR_Toggle_Enable(void *pInstance, MS_BOOL bEn, MS_BOOL b2DTo3D, MS_BOOL bSkipDefaultLRFlag)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(!bSkipDefaultLRFlag)
    {
        if(bEn)
        {
            //Enanble I2S_IN_SD to send out lr flag
            MDrv_WriteByteMask(0x101EAE, 0x00, 0x04);
            MDrv_WriteByteMask(0x101EB3, 0xC0, 0xC0);
        }
        else
        {
            MDrv_WriteByteMask(0x101EB3, 0x00, 0xC0);
        }
    }

    if(!b2DTo3D)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_33_L, (bEn<<1), (BIT(1)));
    }
}

void HAL_XC_H3D_OPM_SBYS_PIP_Enable(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_34_L, (bEn<<7), (BIT(7)));
}

void Hal_SC_enable_cursor_report(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(bEn)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, BIT(8) | BIT(10), BIT(8) | BIT(10));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, 0x00 , BIT(8) | BIT(10));
    }
}

MS_BOOL Hal_SC_get_pixel_rgb(void *pInstance, XC_Get_Pixel_RGB *pData)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_BOOL bret = TRUE;

    switch(pData->enStage)
    {
    case E_XC_GET_PIXEL_STAGE_AFTER_DLC:
        //SC_W2BYTEMSK(0, REG_SC_BK0F_46_L, 0x00 , BMASK(3:0));
        bret = FALSE;//Not support, Must set to stage C for HW issue
        break;
    case E_XC_GET_PIXEL_STAGE_PRE_GAMMA:
        //SC_W2BYTEMSK(0, REG_SC_BK0F_46_L, 0x08, BMASK(3:0));
        bret = FALSE;//Not support, Must set to stage C for HW issue
        break;
    case E_XC_GET_PIXEL_STAGE_AFTER_OSD:
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_18_L, 0x0D, 0xFF);
        break;
    default:
        bret = FALSE;
        break;
    }
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    if(bret)
    {
        // Enable
        if(!pXCResourcePrivate->stdrvXC_MVideo.s_bKeepPixelPointerAppear)
        {
            Hal_SC_enable_cursor_report(pInstance, TRUE);
        }

        // Initial position (x,y)  Set point you want to read.
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_19_L, pData->u16x);
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_1A_L, pData->u16y);

        //SW trigger for reading
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_18_L, BIT(8), BIT(8));
        MsOS_DelayTask(5);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_18_L, 0, BIT(8));
        MsOS_DelayTask(32);  // Must wait .

        pData->u32r = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_2D_L);
        pData->u32g = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_2E_L);
        pData->u32b = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_2F_L);

        // Disable
        if(!pXCResourcePrivate->stdrvXC_MVideo.s_bKeepPixelPointerAppear)
        {
            Hal_SC_enable_cursor_report(pInstance, FALSE);
        }
    }
    return bret;
}

void Hal_SC_SetOPWriteOff(void *pInstance, MS_BOOL bEna)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    MS_BOOL u16OldReg = (MS_BOOL)(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_27_L, BIT(0)));

    #if (HW_DESIGN_4K2K_VER == 4)
    // For monaco new chip design, only Legacy mode need to control OPW
    // If Monaco mode, always keep OPW is on
    if ((psXCInstPri->u32DeviceID==0)
       && !(pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_Init_Misc.u32MISC_A & E_XC_INIT_MISC_A_LEGACY_MODE))
    {
        bEna = FALSE;
    }
    #endif

    if(u16OldReg != bEna)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_27_L, bEna, BIT(0));//This will stop OPW only, OP memory write request still on
    }
}


MS_BOOL Hal_SC_GetOPWriteOff(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    return (MS_BOOL)SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_27_L, BIT(0));
}

MS_BOOL Hal_SC_Detect_RequestFBL_Mode(void *pInstance)
{
    UNUSED(pInstance);
    return ENABLE_REQUEST_FBL;
}

MS_BOOL Hal_SC_Set_RequestFBL_Mode(void *pInstance, MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(IsSrcTypeDTV(gSrcInfo[MAIN_WINDOW].enInputSourceType) || (IsSrcTypeStorage(gSrcInfo[MAIN_WINDOW].enInputSourceType)))//MVOP source
    {
        gSrcInfo[MAIN_WINDOW].Status2.bMVOPHSKMode = bEn;

    	//SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_1C_L, bEn?BIT(14):0 , BIT(14)); //reg_short_1line_disable  1:Disable 0:Enable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_10_L, bEn?(BIT(0)|BIT(2)):0 , BIT(0)|BIT(2)); // Bit0: Enable HSK mode Bit2:reg_ip2_vs_sel 0:ip1 1:mvop

        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_5D_L, 0x0828 , 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_1F_L, 0xC008, 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_20_L, 0xC020, 0xFFFF);

        Hal_XC_MLoad_set_trig_p(pInstance, 0x14, 0x18);

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_68_L, 0x0, BIT(9));

        //this feature conflicts with HSK mode
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_45_L, 0x0000, 0x9FFF); // edclk pd control start and edclk pd control enable
    }
    else
    {
        gSrcInfo[MAIN_WINDOW].Status2.bMVOPHSKMode = FALSE;

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_68_L, BIT(9), BIT(9));

        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_1C_L, 0x0 , BIT(14)); //reg_short_1line_disable  1:Disable 0:Enable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_10_L, 0x0 , BIT(0)|BIT(2)); // Disable HSK mode Bit2:reg_ip2_vs_sel 0:ip1 1:mvop
    }

    return ENABLE_REQUEST_FBL;
}

void Hal_XC_SetFrameColor(void *pInstance, MS_U32 u32aRGB)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_19_L,  (u32aRGB >> 8),0xFF00);            ///< R
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_1A_L,  (u32aRGB >> 8),0x00FF);            ///< G
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_1A_L,  (u32aRGB << 8),0xFF00);            ///< B
}
MS_U8 Hal_SC_getVSyncWidth(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_U8 u8val = 0;

    if(eWindow == MAIN_WINDOW)
    {
        u8val = ((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_22_L) & 0xFF00) >> 8);
    }
    else
    {
    }
    return u8val;
}

E_APIXC_ReturnValue Hal_SC_Set_OSDLayer(void *pInstance, E_VOP_OSD_LAYER_SEL  eVOPOSDLayer, SCALER_WIN eWindow)
{
    return E_APIXC_RET_FAIL;
}

E_VOP_OSD_LAYER_SEL Hal_SC_Get_OSDLayer(void *pInstance, SCALER_WIN eWindow)
{
    //do nothing
    return E_VOP_LAYER_RESERVED;
}

E_APIXC_ReturnValue Hal_SC_Set_VideoAlpha(void *pInstance, MS_U8 u8Val, SCALER_WIN eWindow)
{
    //do nothing
    return E_APIXC_RET_FAIL;
}

E_APIXC_ReturnValue Hal_SC_Get_VideoAlpha(void *pInstance, MS_U8 *pu8Val, SCALER_WIN eWindow)
{
    *pu8Val += 0;

    //do nothing
    return E_APIXC_RET_FAIL;
}

void Hal_XC_ClearScalingFactorForInternalCalib(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    //MDrv_WriteRegBit(H_BK_SCMI(0x09), FALSE, BIT(7));
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_04_L, 0x0000);   // H pre-scaling
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_05_L, 0xC010);   // H pre-scaling
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_08_L, 0x0000);   // V pre-scaling
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK02_09_L, 0x0000);   // V pre-scaling

    //HVSP
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_07_L, 0x0000);  // H post-scaling
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_08_L, 0x0100);  // H post-scaling
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_09_L, 0x0000);  // V post-scaling
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_0A_L, 0x0100);  // V post-scaling
}

MS_U8 MHal_SC_cal_usedgain_to_reggain(MS_U32 u16UsedGain_x32)
{
    MS_U8 u8Value = 0;

    if      (u16UsedGain_x32 >=65536) u8Value = 16;
    else if (u16UsedGain_x32 >=32768) u8Value = 15;
    else if (u16UsedGain_x32 >=16384) u8Value = 14;
    else if (u16UsedGain_x32 >= 8192) u8Value = 13;
    else if (u16UsedGain_x32 >= 4096) u8Value = 12;
    else if (u16UsedGain_x32 >= 2048) u8Value = 11;
    else if (u16UsedGain_x32 >= 1024) u8Value = 10;
    else if (u16UsedGain_x32 >=  512) u8Value = 9;
    else if (u16UsedGain_x32 >=  256) u8Value = 8;
    else if (u16UsedGain_x32 >=  128) u8Value = 7;
    else if (u16UsedGain_x32 >=   64) u8Value = 6;
    else if (u16UsedGain_x32 >=   32) u8Value = 5;
    else if (u16UsedGain_x32 >=   16) u8Value = 4;
    else if (u16UsedGain_x32 >=    8) u8Value = 3;
    else if (u16UsedGain_x32 >=    4) u8Value = 2;
    else if (u16UsedGain_x32 >=    2) u8Value = 1;
    else if (u16UsedGain_x32 >=    1) u8Value = 0;
    else {
        u8Value = 0;
    }

    u8Value += IPGAIN_REFACTOR;

    return u8Value;
}

E_APIXC_ReturnValue Hal_SC_OP2VOPDESel(void *pInstance, E_OP2VOP_DE_SEL eVopDESel)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    //Select op2vop de, for DWIN capture etc
    if(eVopDESel == E_OP2VOPDE_WHOLEFRAME_WITHOSD)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_6B_L, ((MS_U16)(E_OP2VOPDE_WHOLEFRAME) << 12), (BIT(12)+BIT(13)));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_23_L, BIT(15), BIT(15));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_23_L, 0, BIT(15));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_6B_L, (eVopDESel << 12), (BIT(12)+BIT(13)));
    }
    return E_APIXC_RET_OK;
}

MS_BOOL Hal_XC_SVOutput_GetCaps(void *pInstance)
{
    return FALSE;
}

/////Add for FRC
void _MHal_SC_Flock_Caculate_LPLLSet(MS_U32 u32Dclk)
{
    MS_U64 ldPllSet = 0xff;

    ldPllSet = ((MS_U64)320 * 524288 * 10000000 + (u32Dclk>>1));  // LPLL BK01 LPLL Set
    do_div(ldPllSet, u32Dclk);

    LPLL_BK_STORE;
    LPLL_BK_SWITCH(0x01);
    W4BYTE(L_BK_LPLL(0x0F), (MS_U32)ldPllSet);
    LPLL_BK_RESTORE;
}

void _MHal_SC_Set_LPLL_Limit(MS_U32 u32LpllLimitHigh, MS_U32 u32LpllLimitLow, MS_U8 u8Lpll_bank)
{
    //printf("Fpll_Limit: Set %lx, bound (%lx -> %lx)\n", *u32PllSet, u32UpBound, u32LowBound);
    LPLL_BK_STORE;
    LPLL_BK_SWITCH(u8Lpll_bank);


    MDrv_WriteByteMask(L_BK_LPLL(0x0D), BIT(4), BIT(4));        // turn on 2 limit

    //printf("Fpll set %lx, limit (high %lx, low %lx)\n", *u32PllSet, u32LpllLimitHigh, u32LpllLimitLow);
    MDrv_Write3Byte(L_BK_LPLL(0x06), u32LpllLimitHigh);
    MDrv_Write3Byte(L_BK_LPLL(0x08), u32LpllLimitLow);

    //printf("Fpll limit reg (high %lx, low %lx)\n", MDrv_Read4Byte(L_BK_LPLL(0x06)), MDrv_Read4Byte(L_BK_LPLL(0x08)));

    LPLL_BK_RESTORE;
}
#define LVDS_FRC_CLOCK_MHZ  320
void _MHal_SC_Flock_Set_IGainPGain(void *pInstance, MS_U8 u8FRC_Out, MS_U16 u16OutputVfreqAfterFRC, MS_U16 u16Htt, MS_U16 u16Vtt)
{
    MS_U32  u32dclk=0;
    MS_U8   u8GainI, u8GainP;
    MS_U64  u64Div_Factor;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    //check parameter valid, avoiding the diving zero failure
    if(0 == u8FRC_Out)
    {
        u8FRC_Out = 1;
    }

    u32dclk = (MS_U32)(u16Vtt * u16Htt * u8FRC_Out);
    //u64Div_Factor = (MS_U64)LVDS_FRC_CLOCK_MHZ*524288*1000000/pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.u32XTAL_Clock;
    u64Div_Factor = (MS_U64)LVDS_FRC_CLOCK_MHZ*524288*1000000;
    do_div(u64Div_Factor, pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.u32XTAL_Clock);
    do_div(u64Div_Factor, (MS_U32)u32dclk * 8);

    u8GainI = MHal_SC_cal_usedgain_to_reggain(u64Div_Factor);

    if((u8FRC_Out == 5)&&(u64Div_Factor==0))
    {
        //24 to 60Hz, because the SW can't get the real value by log table
        u8GainI = 1;

        u8GainI += 2;
    }

    u8GainP = u8GainI+1;
    if((u8FRC_Out >= 2) && (u8GainP == u8GainI))
    {
        u8GainP++;
    }

    LPLL_BK_STORE;
    LPLL_BK_SWITCH(0x01);
    MDrv_WriteByte(H_BK_LPLL(0x0B), (u8GainP<<4)|u8GainI);  //Gain
    LPLL_BK_RESTORE;
    XC_LOG_TRACE(XC_DBGLEVEL_SETTIMING, "i_Gain= 0x%x (%u)\n", (MS_U32)u64Div_Factor, (MS_U32)u64Div_Factor)
    XC_LOG_TRACE(XC_DBGLEVEL_SETTIMING, "REG_IGain= 0x%x (%u)\n", u8GainI, u8GainI)
    XC_LOG_TRACE(XC_DBGLEVEL_SETTIMING, "REG_PGain= 0x%x (%u)\n", u8GainP, u8GainP)
}


void _MHal_SC_Flock_Set_LPLL_Enable(E_XC_FLOCK_TYPE eFlock_type)
{
    MS_BOOL bDiv_en = DISABLE;

    switch(eFlock_type)
    {
        case E_XC_FLOCK_DIV_ON:
            bDiv_en = ENABLE;
        break;

        case E_XC_FLOCK_FPLL_ON:
        case E_XC_FLOCK_DIV_OFF:
        default:
        break;
    }

    LPLL_BK_STORE;
    LPLL_BK_SWITCH(0x01);
    MDrv_Write2ByteMask(L_BK_LPLL(0x7F), bDiv_en?BIT(8):0, BIT(8));
    LPLL_BK_RESTORE;

}

void MHal_CLKGEN_FRC_Init(MS_U8 u8LPLL_Mode)
{
    UNUSED(u8LPLL_Mode);
}

void MHal_CLKGEN_FRC_Bypass_Enable(MS_BOOL bEnable)
{

    W2BYTEMSK(L_CLKGEN0(0x53),0x00,0x02); // Not Invert
    W2BYTEMSK(L_CLKGEN0(0x53),0x00,0x01); // Enable clock

    if (bEnable)
    {
        // Enable CLK_ODCLK
        W2BYTEMSK(L_CLKGEN0(0x53),0xC0C,0xC0C);   // LPLL output clock
        // Disable CLK_R2_FRC
        W2BYTEMSK(L_CLKGEN1(0x30), 0x00, 0xFFFF); // turn-on clk_mcu_frc
        // Enable CLK_SPI_M_FRC
        W2BYTEMSK(L_CLKGEN1(0x31), 0x00, 0x01);   // Disable clock
    }
    else
    {
        // Enable CLK_ODCLK
        W2BYTEMSK(L_CLKGEN0(0x53), 0x00, 0xC0C); // synthetic clock out
        // Enable CLK_R2_FRC
        W2BYTEMSK(L_CLKGEN1(0x30), 0x00, 0x0C); // 216 MHz
        W2BYTEMSK(L_CLKGEN1(0x30), 0x00, 0x02); // Not Invert
        W2BYTEMSK(L_CLKGEN1(0x30), 0x00, 0x01); // Enable clock
        // Enable CLK_SPI_M_FRC
        W2BYTEMSK(L_CLKGEN1(0x31), 0x00, 0x1C); // 27  MHz
        W2BYTEMSK(L_CLKGEN1(0x31), 0x00, 0x02); // Not Invert
        W2BYTEMSK(L_CLKGEN1(0x31), 0x00, 0x01); // Enable clock
    }
}


E_APIXC_ReturnValue Hal_XC_IsForcePrescaling(void *pInstance, const XC_InternalStatus *pSrcInfo, MS_BOOL *pbForceV, MS_BOOL *pbForceH, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    *pbForceV = FALSE;
    *pbForceH = FALSE;

    //-----------------------------------------
    // Vertical
    //-----------------------------------------

    //FHD case. FHD has tight bandwidth in FCLK (post scaling), so force pre-scaling if disp.v size > 80% of crop.v size.
    if ( (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16Height > 1000) &&
         (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16Width > 1600) ) //consider 1680x1050 into this case
    {
        // 80%
        if ( ( pSrcInfo->stDispWin.height * 10 ) <  ( pSrcInfo->stCropWin.height * 8 ) )
        {
            *pbForceV = TRUE;
        }
    }
    else // SD, HD panel.
    {
        // 60%
        if ( ( pSrcInfo->stDispWin.height * 10 ) <  ( pSrcInfo->stCropWin.height * 6 ) )
        {
            *pbForceV = TRUE;
        }
    }

    //-----------------------------------------
    // Horizontal
    //-----------------------------------------

    if ( (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16Height > 1000)
        && (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16Width > 1600) ) //consider 1680x1050 into this case
    {
        // 80% ( SEC using 80% for HD panel ). Increase % if meet FCLK bandwidth issue in the future.
        if ( ( pSrcInfo->stDispWin.width * 10 ) < ( pSrcInfo->stCropWin.width * 8 ) )
        {
            *pbForceH = TRUE;
        }
    }
    else // SD panel.
    {
        // 60%
        if ( ( pSrcInfo->stDispWin.width * 10 ) < ( pSrcInfo->stCropWin.width * 6 ) )
        {
            *pbForceH = TRUE;
        }
    }

    return E_APIXC_RET_OK;
}

MS_BOOL Hal_SC_IsHW2Dto3DPatch_Enable(void)
{
    MS_BOOL bRet = FALSE;

    return bRet;
}

MS_U32 MHal_SC_Get_LpllSet_Factor(void *pInstance, MS_U8 u8LPLL_Mode, MS_U8 u8LPLL_Type,MS_U32 u32DefaultDClk)
{
    MS_U32 u32Factor = 0;
    UNUSED(u8LPLL_Type);
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    u32Factor  = LPLL_LOOPGAIN/8/2;

    if ((pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16HTotal> 3000) && (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16VTotal > 2000) && (pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16DefaultVFreq > 500))
    {
        //printf("\033[0;31m [%s][%d] enter For 4K2K used!!!  \033[0m\n", __FUNCTION__, __LINE__);
        u32Factor = 1;
    }

    if (u8LPLL_Type == E_XC_PNL_LPLL_LVDS)
    {
        u32Factor = 3;
    }

    // for the WUXGA 1920x1200 case
    if((u8LPLL_Mode==E_XC_MOD_OUTPUT_DUAL)&&(u32DefaultDClk > 1500000000)
        &&(pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16Height > 1100)
        &&(pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.stPanelInfo.u16Width < 2000))
    {
        u32Factor  = LPLL_LOOPGAIN/8;
    }

    if((u8LPLL_Type >= E_XC_PNL_LPLL_VBY1_10BIT_4LANE)&&(u8LPLL_Type <= E_XC_PNL_LPLL_VBY1_8BIT_8LANE))
    {
        u32Factor = 1;
    }

    return u32Factor;
}

MS_U32 MHal_SC_Get_LpllSet_Div(void *pInstance, MS_U8 u8LPLL_Mode, MS_U8 u8LPLL_Type,MS_U32 u32DefaultDClk)
{
    MS_U32 u32Div = 1;

    if (u8LPLL_Type == E_XC_PNL_LPLL_LVDS)
    {
        u32Div = 2;
    }

    return u32Div;
}

E_APIXC_ReturnValue Hal_SC_Enable_AVMute(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
    {
        //HDMI V-mute detect enable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_34_L, BIT(9), BIT(9));
        //force IPM enable at av-mute case
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_19_L, BIT(5), BIT(5));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK32_19_L, BIT(5), BIT(5));

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_01_L, BIT(13) | BIT(15), BIT(13) | BIT(15));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_23_L, BIT(9) | BIT(11), BIT(9) | BIT(11));
    }
    else
    {
        //HDMI V-mute detect enable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_34_L, BIT(9), BIT(9));
        //force IPM enable at av-mute case
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_59_L, BIT(5), BIT(5));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK32_59_L, BIT(5), BIT(5));

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_01_L, BIT(12) | BIT(14), BIT(12) | BIT(14));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_23_L, BIT(8) | BIT(10), BIT(8) | BIT(10));
    }

    return E_APIXC_RET_OK;
}

MS_BOOL Hal_XC_ReportPixelInfo(void *pInstance, MS_XC_REPORT_PIXELINFO *pstRepPixInfo)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    MS_BOOL bret = TRUE;

    switch(pstRepPixInfo->enStage)
    {
    case E_XC_GET_PIXEL_STAGE_AFTER_DLC:
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_46_L, 0x00 , BMASK(3:0));
        break;
    case E_XC_GET_PIXEL_STAGE_PRE_GAMMA:
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_46_L, 0x08, BMASK(3:0));
        break;
    case E_XC_GET_PIXEL_STAGE_AFTER_OSD:
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_46_L, 0x0C, BMASK(3:0));
        break;
    default:
        bret = FALSE;
        break;
    }

    if(bret)
    {
        // Enable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, BIT(8), BIT(8));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_30_L, BIT(12), BIT(12)); //HW suggest  need not to divide 4096.if bit12=1,HW do not divide 4096
                                                                                    //otherwise,HW divide 4096.
        if(pstRepPixInfo->bShowRepWin)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, BIT(9), BIT(9));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_46_L, pstRepPixInfo->u16RepWinColor<<8, 0xFF00);
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_1A_L, BIT(0), BIT(0));
        }

        // Set Report Window
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_42_L, pstRepPixInfo->u16XStart);
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_43_L, pstRepPixInfo->u16XEnd);
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_44_L, pstRepPixInfo->u16YStart);
        SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_45_L, pstRepPixInfo->u16YEnd);

        MsOS_DelayTask(50);  // Must wait .

        pstRepPixInfo->u16RCrMin = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_64_L);
        pstRepPixInfo->u16RCrMax = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_65_L);
        pstRepPixInfo->u16GYMin  = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_66_L);
        pstRepPixInfo->u16GYMax  = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_67_L);
        pstRepPixInfo->u16BCbMin = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_68_L);
        pstRepPixInfo->u16BCbMax = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0F_69_L);
        pstRepPixInfo->u32RCrSum = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_01_L)|(SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_02_L)<<16);
        pstRepPixInfo->u32GYSum  = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_03_L)|(SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_04_L)<<16);
        pstRepPixInfo->u32BCbSum = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_05_L)|(SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_06_L)<<16);

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_30_L, 0x00, BIT(12));

        //[messi]HW limit.if sum > 0xFFFFFF,it will disable  high-precision mode,use bit[12~31] *4096 to report
        if((pstRepPixInfo->u32RCrSum >= 0xFFFFFF) ||(pstRepPixInfo->u32GYSum >= 0xFFFFFF) || (pstRepPixInfo->u32BCbSum >= 0xFFFFFF))
        {
            MsOS_DelayTask(50);
            if(pstRepPixInfo->u32RCrSum >= 0xFFFFFF)
            {
                pstRepPixInfo->u32RCrSum = (((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_01_L)|(SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_02_L)<<16))&0x7FFFFFFF)>>12)*4096;
            }
            if(pstRepPixInfo->u32GYSum >= 0xFFFFFF)
            {
                pstRepPixInfo->u32GYSum = (((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_03_L)|(SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_04_L)<<16))&0x7FFFFFFF)>>12)*4096;
            }
            if(pstRepPixInfo->u32BCbSum >= 0xFFFFFF)
            {
                pstRepPixInfo->u32BCbSum = (((SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_05_L)|(SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK2D_06_L)<<16))&0x7FFFFFFF)>>12)*4096;
            }
        }
        if(pstRepPixInfo->bShowRepWin)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_1A_L, 0x00, BIT(0));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, 0x00, BIT(9));
        }
        // Disable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0F_57_L, 0x00, BIT(8)| BIT(9));
    }

    return bret;
}

void Hal_SC_set_mrq_miusel(void *pInstance, MS_U8 u8MIUSel)
{
    UNUSED(pInstance);
    UNUSED(u8MIUSel);
}

void Hal_SC_set_mcdi_memoryaddress(void *pInstance, MS_PHY u32FBAddress, E_XC_MCDI_TYPE eType)
{
    UNUSED(pInstance);
    UNUSED(u32FBAddress);
    UNUSED(eType);
}

void Hal_SC_set_mcdi_write_limit(void *pInstance, MS_BOOL bEn, MS_PHY u32LimitAddress, E_XC_MCDI_TYPE eType)
{
    UNUSED(pInstance);
    UNUSED(bEn);
    UNUSED(u32LimitAddress);
    UNUSED(eType);
}
void Hal_SC_enable_mcdi(void *pInstance, MS_BOOL bEn, E_XC_MCDI_TYPE eType)
{
    UNUSED(pInstance);
    UNUSED(bEn);
    UNUSED(eType);
}

/// bandwidth saving Mode
void Hal_SC_set_bws_mode(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        //ipm Main
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_01_L, (bEnable? 0x00:BIT(0)), BIT(0));
    }
    else
    {
        //ipm Sub
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_01_L, (bEnable? 0x00:BIT(1)), BIT(1));
    }
}

void Hal_SC_sw_lcnt_en(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        //ipm Main
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_11_L, (bEnable? BIT(0):0x00), BIT(0));
    }
    else
    {
        //ipm Sub
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_21_L, (bEnable? BIT(0):0x00), BIT(0));
    }
}

void Hal_SC_set_sw_lcnt(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        //ipm Main
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_11_L, (bEnable? BIT(1):0x00), BIT(1));
    }
    else
    {
        //ipm Sub
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_21_L, (bEnable? BIT(1):0x00), BIT(1));
    }
}

void Hal_SC_set_ipmw_lcnt_inv(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        //ipm Main
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_12_L, (bEnable? BIT(4):0x00), BIT(4));
    }
    else
    {
        //ipm Sub
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_22_L, (bEnable? BIT(4):0x00), BIT(4));
    }
}

void Hal_SC_set_ipmr_lcnt_inv(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        //ipm Main
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_12_L, (bEnable? BIT(12):0x00), BIT(12));
    }
    else
    {
        //ipm Sub
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_22_L, (bEnable? BIT(12):0x00), BIT(12));
    }
}

void Hal_SC_set_opm_lcnt_inv(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(eWindow == MAIN_WINDOW)
    {
            //opm Main
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_32_L, (bEnable? BIT(5):0x00), BIT(5));
    }
    else
    {
            //opm Sub
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK08_32_L, (bEnable? BIT(4):0x00), BIT(4));
    }

}

void MHal_XC_Calc_IGainPGain(void *pInstance, MS_U8 *u8GainI, MS_U8 *u8GainP, MS_U32 u32XTAL_Clock, MS_U8 u8LGain, MS_U8 u8Vco, MS_U16 u16HTotal, MS_U16 u16VTotal, MS_U8 u8FRC_Out)
{
    MS_U32 u32Factor, u32Temp;
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[E_XC_POOL_ID_INTERNAL_VARIABLE],(void**)(&pXCResourcePrivate));
    u32Temp = (MS_U32)(u16VTotal*u16HTotal*u8FRC_Out);
    u32Factor = ((LVDS_MPLL_CLOCK_MHZ*1000000UL/u32XTAL_Clock)*524288*u8LGain)/((MS_U32)(u32Temp*u8Vco/2*8));

    XC_LOG_TRACE(XC_DBGLEVEL_SETTIMING, "MM=%ld,u8LGain1=%d,Htt=%d,Vtt=%d,Ovs=%d,Vco=%d,i_gain=%d,REGIg=%d,u32XTAL_Clock=%u\n",
    (LVDS_MPLL_CLOCK_MHZ*1000000UL/pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_InitData.u32XTAL_Clock),u8LGain,
    u16HTotal,u16VTotal,u8FRC_Out,u8Vco/2,u32Factor,MHal_SC_cal_usedgain_to_reggain(u32Factor),u32XTAL_Clock);

    *u8GainI = MHal_SC_cal_usedgain_to_reggain(u32Factor);
    *u8GainP = *u8GainI+1;

    XC_LOG_TRACE(XC_DBGLEVEL_SETTIMING, "==>LG1=%d,iGain=%d,I=%d,P=%d\n",u8LGain,u32Factor,*u8GainI,*u8GainP);
}

void MHAL_SC_set_osdc_tgen_hsync_start(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_hsync_end(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_hframe_de_start(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_hframe_de_end(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_htotal(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_vtotal(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_vframe_de_start(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_vframe_de_end(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_vsync_start(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_vsync_end(void *pInstance, MS_U16 u16Value)
{
    UNUSED(pInstance);
    UNUSED(u16Value);
}

void MHAL_SC_set_osdc_tgen_reset_enable(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}

void MHAL_SC_set_osdc_swreset_enable(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}

void MHAL_SC_set_osdc_mixer_bypass_enable(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}

void MHAL_SC_set_osdc_mixer_inv_alpha_enable(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}
//1:hs_out = hs&vfde
void MHAL_SC_set_osdc_mixer_hs_n_vfde_enable(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}
//1:de(hfde)_out = de(hfde)&vfde
void MHAL_SC_set_osdc_mixer_hfde_n_vfde_enable(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}

void MHAL_SC_set_osdc_clk_mux(void *pInstance, MS_U8 u8Clk_Mux)
{
    UNUSED(pInstance);
    UNUSED(u8Clk_Mux);
}

void MHAL_SC_enable_osdc(void *pInstance, MS_BOOL bEnable)
{

    UNUSED(pInstance);
    UNUSED(bEnable);
}

MS_U16 MHAL_SC_get_osdc_tgen_hsync_start(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_hsync_end(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_hframe_de_start(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_hframe_de_end(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_htotal(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_vtotal(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_vframe_de_start(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_vframe_de_end(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_vsync_start(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_U16 MHAL_SC_get_osdc_tgen_vsync_end(void *pInstance)
{
    UNUSED(pInstance);
    return 0;
}

MS_BOOL MHAL_SC_get_osdc_mixer_bypass_status(void *pInstance)
{
    UNUSED(pInstance);
    return FALSE;
}

MS_BOOL MHAL_SC_get_osdc_mixer_inv_alpha_status(void *pInstance)
{
    UNUSED(pInstance);
    return FALSE;
}
//1:hs_out = hs&vfde
MS_BOOL MHAL_SC_get_osdc_mixer_hs_n_vfde_status(void *pInstance)
{
    UNUSED(pInstance);
    return FALSE;
}
//1:de(hfde)_out = de(hfde)&vfde
MS_BOOL MHAL_SC_get_osdc_mixer_hfde_n_vfde_status(void *pInstance)
{
    UNUSED(pInstance);
    return FALSE;
}

MS_BOOL MHAL_SC_get_osdc_onoff_status(void *pInstance)
{
    UNUSED(pInstance);
    return FALSE;
}

void MHal_XC_SetForceCurrentReadBank(void *pInstance,MS_BOOL bEnable, SCALER_WIN eWindow)
{
    static SC_SET_FORCE_CURRENT_READ_BANK_t stSetForceReadBank;
    stSetForceReadBank.pInstance = pInstance;
    stSetForceReadBank.bEnable = bEnable;
    stSetForceReadBank.eWindow = eWindow;

    //color team suggest setting
    //film mode setting
    if(bEnable)
    {
        u16RegForceMryValue = SC_R2BYTEMSK(0, REG_SC_BK22_78_L, 0xffff);
        //SC_W2BYTEMSK(0,REG_SC_BK22_78_L, 0x8080, 0xffff);
    }
    else
    {
        SC_W2BYTEMSK(0,REG_SC_BK22_78_L, u16RegForceMryValue, 0xffff);
        u16RegForceMryValue = 0;
    }
    MDrv_XC_InterruptAttachWithoutMutex(pInstance, SC_INT_F2_IPVS_SB, MHal_XC_SetForceCurrentReadBankInterrupt, (void*)&stSetForceReadBank);
}



static void MHal_XC_SetForceCurrentReadBankInterrupt(SC_INT_SRC eIntNum, void *pParam)
{
    volatile SC_SET_FORCE_CURRENT_READ_BANK_t *pstSetForceCurrentReadBank = (volatile SC_SET_FORCE_CURRENT_READ_BANK_t *)pParam;

    volatile MS_U16 u16Bank = 0;
    volatile MS_U8 u8Bank = 0;

    if(pstSetForceCurrentReadBank->bEnable)
    {
        if (pstSetForceCurrentReadBank->eWindow == MAIN_WINDOW)
        {
            u16Bank = SC_R2BYTEMSK(0, REG_SC_BK12_3A_L, BIT(7)|BIT(6)|BIT(5)|BIT(4));
        }
        else
        {
            u16Bank = SC_R2BYTEMSK(0, REG_SC_BK12_7A_L, BIT(7)|BIT(6)|BIT(5)|BIT(4));
        }
    }

    u8Bank = (MS_U8)u16Bank >> 4;

    MHal_XC_SetForceReadBank(pstSetForceCurrentReadBank->pInstance, pstSetForceCurrentReadBank->bEnable, u8Bank, pstSetForceCurrentReadBank->eWindow);

    MDrv_XC_InterruptDeAttachWithoutMutex(pstSetForceCurrentReadBank->pInstance, SC_INT_F2_IPVS_SB, MHal_XC_SetForceCurrentReadBankInterrupt, pParam);
}

void MHal_XC_SetForceReadBank(void *pInstance, MS_BOOL bEnable, MS_U8 u8Bank, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
    {
        if (bEnable)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, BIT(11), BIT(11));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, (u8Bank & 0x7) << 8, BIT(10)|BIT(9)|BIT(8));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_06_L, ((u8Bank & 0x8) >> 3) << 14, BIT(14));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, 0, BIT(11));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, 0, BIT(10)|BIT(9)|BIT(8));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_06_L, 0, BIT(14));
        }
    }
    else
    {
        if (bEnable)
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, BIT(11), BIT(11));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, (u8Bank & 0x7) << 8, BIT(10)|BIT(9)|BIT(8));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_46_L, ((u8Bank & 0x8) >> 3) << 14, BIT(14));
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, 0, BIT(11));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_47_L, 0, BIT(10)|BIT(9)|BIT(8));
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_46_L, 0, BIT(14));
        }
    }
}

MS_BOOL MHal_XC_SetDNRBufAddress(void *pInstance, MS_PHY u32DNRBaseAddr, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->sthal_SC._u32DNRBaseAddress[eWindow] = u32DNRBaseAddr;
    return TRUE;
}

MS_PHY MHal_XC_GetDNRBufAddress(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->sthal_SC._u32DNRBaseAddress[eWindow] ;
}

MS_BOOL MHal_XC_SetDNRBufSize(void *pInstance, MS_PHY u32DNRBufSize, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->sthal_SC._u32DNRBufferSize[eWindow] = u32DNRBufSize;
    return TRUE;
}

MS_PHY MHal_XC_GetDNRBufSize(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->sthal_SC._u32DNRBufferSize[eWindow] ;
}

MS_BOOL MHal_XC_SetFRCMBufAddress(void *pInstance, MS_PHY u32BaseAddr, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->sthal_SC._u32FRCBaseAddress[eWindow] = u32BaseAddr;
    return TRUE;
}

MS_PHY MHal_XC_GetFRCMBufAddress(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->sthal_SC._u32FRCBaseAddress[eWindow] ;
}

MS_BOOL MHal_XC_SetFRCMBufSize(void *pInstance, MS_PHY u32BufSize, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->sthal_SC._u32FRCBufferSize[eWindow] = u32BufSize;
    return TRUE;
}

MS_PHY MHal_XC_GetFRCMBufSize(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->sthal_SC._u32FRCBufferSize[eWindow] ;
}

MS_BOOL MHal_XC_SetDualDNRBufAddress(void *pInstance, MS_PHY u32DNRBaseAddr, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->_u32DualDNRBaseAddress[eWindow] = u32DNRBaseAddr;
    return TRUE;
}

MS_PHY MHal_XC_GetDualDNRBufAddress(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->_u32DualDNRBaseAddress[eWindow];
}

MS_BOOL MHal_XC_SetDualDNRBufSize(void *pInstance, MS_PHY u32DNRBufSize, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->_u32DualDNRBufferSize[eWindow] = u32DNRBufSize;
    return TRUE;
}

MS_PHY MHal_XC_GetDualDNRBufSize(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->_u32DualDNRBufferSize[eWindow] ;
}

MS_BOOL MHal_XC_Init_Patch(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    if (eWindow >= MAX_WINDOW)
    {
        printf("[%s,%5d] maximum window exceeded",__FUNCTION__,__LINE__);
        return FALSE;
    }

    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK23_6F_L, 0x20, 0x3F); // by HW RD's request, for BB section offset issue

    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_20_L, 0x2020); // by HW RD's request
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_21_L, 0x1818); // by HW RD's request
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_22_L, 0xFF30); // by HW RD's request
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_23_L, 0x3030); // by HW RD's request
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_24_L, 0x0060); // by HW RD's request
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_25_L, 0x1414); // by HW RD's request, for HDMI 4K BW issue, adjust R/W line buffer length

#ifdef SUPPORT_DUAL_MIU
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK52_25_L, 0x3030); // by HW RD's request, for HDMI 4K BW issue, adjust R/W line buffer length
#endif
    // SW patch for Monaco
    // by HW RD's request, to fix HDMI 1080i pink garbage line at bottom side
    // for edclk power saving using

        if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
        {
            // disable edclk power saving using (main window)
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_44_L, 0x0000, 0x9FFF); // Memory control Switch Method by Vcnt
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_45_L, 0x0000, 0x9FFF); // edclk pd control start and edclk pd control enable
        }
        else
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_44_L, 0x8004, 0x9FFF); // Memory control Switch Method by Vcnt
            // enable edclk power saving using (main window)
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_45_L, 0x8004, 0x9FFF); // edclk pd control start and edclk pd control enable
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_47_L, 0x0008, 0x1FFF); // IPM trigger by Vcnt (reset by SPRV_Ed_p_d1L) enable
        }

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_44_L, 0x8004, 0x9FFF); // Memory control Switch Method by Vcnt
    // disable edclk power saving using (sub window)
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_45_L, 0x0000, 0x9FFF); // edclk pd control start and edclk pd control enable (original setting 0x8004)
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK03_47_L, 0x0000, 0x1FFF); // IPM trigger by Vcnt (reset by SPRV_Ed_p_d1L) enable (original setting 0x0010)

    // SW patch for Monaco
    // by HW RD's request, to fix HDMI 1080i repeat garbage at left side
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK12_37_L, 0x20); // bypass main line buffer length setting
    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK11_37_L, 0x20); // bypass sub line buffer length setting

    // ECO item for Monaco: hvsp PIP B section last flag error
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK23_5F_L, BIT(14), BIT(14));

    // ECO item for Monaco: ip2ve 4K path Vsync need inverse
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_7F_L, BIT(14), BIT(14));
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK04_7F_L, BIT(14), BIT(14));

    // SW patch for muji : 4k2k 3D LA out show garbage on the top, issue with BW
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK58_10_L, 0x0000, BIT(0));//disable SCM sub OP

    // BK00_03[13] conflict with compression mode (patch for HW issue)
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK00_03_L, 0x0000, 0x2000);


    //U03 compatible setting
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK32_66_L, BIT(13), BIT(13));

    ///Patch here ////
    #if (FRC_INSIDE)
    MHal_FRC_interrupt_mask(pInstance, 0xFF);
    #endif

    // SW patch for Eisntein
    // With HW Auto no signal case,  sub video source change would causes OP1 broken, looks like main video broken
    Hal_SC_ip_enable_turnoff_OP1_for_AutoNoSignal(pInstance, DISABLE);

   // SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_61_L, 0x01, 0x03); // for HDMI 2.0, always receive 444 format
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID,REG_SC_BK01_63_L, 0x01, 0x01); // for HDMI odd Htt support

    return TRUE;
}
MS_BOOL MHal_XC_IsPNLYUVOutput(void *pInstance)
{
    MS_BOOL bIsPNLYUVOutput = TRUE;
#if 0//below is logic from TV, need box RD's confirm, disable it temporary
    MS_BOOL bIsY2REnable = FALSE, bIsR2YEnable = FALSE;
    SCALER_WIN eWindow = MAIN_WINDOW;
    MS_U16 u16Temp = 0;
    //Get CSC state before OP2
    if(gSrcInfo[MAIN_WINDOW].bBlackscreenEnabled || gSrcInfo[MAIN_WINDOW].bBluescreenEnabled)
    {
        //Main is mute, so check sub
        if(Hal_SC_Is_subwindow_enable())
        {
            if(!(gSrcInfo[SUB_WINDOW].bBlackscreenEnabled || gSrcInfo[SUB_WINDOW].bBluescreenEnabled))
            {
                eWindow = SUB_WINDOW;
            }
        }
    }

    if(eWindow == MAIN_WINDOW)
    {
        u16Temp = SC_R2BYTE(REG_SC_BK10_2F_L);
        if((u16Temp & ( BIT(0) | BIT(2) | BIT(4))) == ( BIT(0) | BIT(2) | BIT(4)))
        {
            bIsY2REnable =  TRUE;
        }
    }
    else
    {
        u16Temp = SC_R2BYTE(REG_SC_BK0F_26_L);
        if((u16Temp & ( BIT(0) | BIT(2) | BIT(4))) == ( BIT(0) | BIT(2) | BIT(4)))
        {
            bIsY2REnable =  TRUE;
        }
    }

    if(bIsY2REnable)
    {
        bIsPNLYUVOutput = FALSE;
    }
    else
    {
        //OP Y2R disable, so check op input
        if(eWindow == MAIN_WINDOW)
        {
            bIsR2YEnable = (MS_BOOL)(SC_R2BYTEMSK(REG_SC_BK02_40_L, BIT(3)) || SC_R2BYTEMSK(REG_SC_BK18_06_L, BIT(0)));

        }
        else
        {
            bIsR2YEnable = (MS_BOOL)(SC_R2BYTEMSK(REG_SC_BK04_40_L, BIT(3)) || SC_R2BYTEMSK(REG_SC_BK18_76_L, BIT(0)));
        }

        if(bIsR2YEnable)
        {
            //Y2R enable
            bIsPNLYUVOutput = TRUE;
        }
        else
        {
            //All Csc is off, so check input
            //VGA/DVI/rgb HDMI is rgb input
            if(  IsSrcTypeVga(gSrcInfo[eWindow].enInputSourceType) //VGA
               ||IsSrcTypeDVI(gSrcInfo[eWindow].enInputSourceType) //DVI
               ||(  IsSrcTypeHDMI(gSrcInfo[eWindow].enInputSourceType)
                  &&(g_HdmiPollingStatus.bIsHDMIMode == TRUE)
                  &&(g_HdmiPollingStatus.u8ColorFormat == MS_HDMI_COLOR_RGB))//HDMI RGB
               ||(  IsSrcTypeHDMI(gSrcInfo[eWindow].enInputSourceType)
                  &&(g_HdmiPollingStatus.bIsHDMIMode == FALSE)) //HDMI_DVI
              )
            {
                bIsPNLYUVOutput = FALSE;
            }
            else
            {
                bIsPNLYUVOutput = TRUE;
            }
        }
    }
#endif
    return bIsPNLYUVOutput;
}

MS_BOOL Hal_SC_Init(void *pInstance)
{
    return TRUE;
}

MS_U32 Hal_SC_Get_Device_Offset(MS_U8 deviceIdx)
{
	MS_U32 ret_U32 = 0 ;
	if(deviceIdx == 0 )
	{
		ret_U32 = MAX_XC_DEVICE0_OFFSET;
	}
	else if(deviceIdx == 1)
	{
		ret_U32 = MAX_XC_DEVICE1_OFFSET;
	}
	return ret_U32;
}

void HAL_SC_Set_LB_MergeAddress(void *pInstance)
{
    return;
}

void Hal_SC_set_edclk(void *pInstance, MS_U8 u8Clk_Mux, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    if(eWindow==MAIN_WINDOW)
    {
        MDrv_WriteByteMask(REG_CKG_EDCLK_F2, (bEnable? 0x00 : CKG_EDCLK_F2_GATED), CKG_EDCLK_F2_GATED);
        if(bEnable)
            MDrv_WriteByteMask(REG_CKG_EDCLK_F2, u8Clk_Mux, CKG_EDCLK_F2_MASK);
    }
    else if(eWindow==SUB_WINDOW)
    {
        MDrv_WriteByteMask(REG_CKG_EDCLK_F1, (bEnable? 0x00 : CKG_EDCLK_F1_GATED), CKG_EDCLK_F1_GATED);
        if(bEnable)
            MDrv_WriteByteMask(REG_CKG_EDCLK_F1, u8Clk_Mux, CKG_EDCLK_F1_MASK);
    }
}

void Hal_SC_set_ficlk2(void *pInstance, MS_U8 u8Clk_Mux, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    if(eWindow==MAIN_WINDOW)
    {
        MDrv_WriteByteMask(REG_CKG_FICLK2_F2, (bEnable? 0x00 : CKG_FICLK2_F2_GATED), CKG_FICLK2_F2_GATED);
        if(bEnable)
            MDrv_WriteByteMask(REG_CKG_FICLK2_F2, u8Clk_Mux, CKG_FICLK2_F2_MASK);
    }
    else if(eWindow==SUB_WINDOW)
    {
        printf("[%s,%5d] ficlk2_f2 not support sub!",__FUNCTION__,__LINE__);// no ficlk2_f1 for sub window
    }
}

void Hal_SC_set_fmclk(void *pInstance, MS_BOOL bEnable)
{
    UNUSED(pInstance);
    UNUSED(bEnable);
}

void HAL_SC_EnableLegacyMode(void *pInstance, MS_BOOL bEnable)
{
#if (HW_DESIGN_4K2K_VER == 4)
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if (psXCInstPri->u32DeviceID == 0)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_01_L, (bEnable<<0), BIT(0));
    }
    else
    {
        // do nothing, because there is only legacy mode in SC2, we don't have to do any switch
    }
#endif
}

static void  MHal_XC_DTVPatchISR(SC_INT_SRC eIntNum, void * pParam)
{
    void *pInstance = pu32XCInst_private;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(gSrcInfo[MAIN_WINDOW].bBlackscreenEnabled==FALSE)
    {
        //Check timing 2s
        if(((MsOS_GetSystemTime()- u32DTVPatchTimer)>2000))
        {
            u32DTVPatchTimer = MsOS_GetSystemTime();
            u16FDMaskCount=0;
        }

        //Check FD mask
        if(bPreFDMaskStatse != (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_67_L, BIT(4))==0))
        {
            bPreFDMaskStatse =(SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_67_L, BIT(4))==0);
            u16FDMaskCount++;
        }

        if(u16FDMaskCount>6)
        {
            if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
            {
                //UC_CTL off
                _MLOAD_ENTRY(pInstance);
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK17_01_L, 0 ,BIT(0));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK57_23_L, 0 ,0x40);
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_67_L, 0x80 ,0xF0);
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK12_07_L, 0 ,BIT(0));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK11_20_L, 0 ,BIT(7));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK11_21_L, 0 ,BIT(15));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK05_78_L, 0 ,0xC000);
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK2A_02_L, BIT(1) ,BIT(1)|BIT(15));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK05_20_L, 0 ,BIT(0));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK05_12_L, 0 ,BIT(0));
                MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK2A_07_L, 0 ,BIT(0));
                MDrv_XC_MLoad_Fire(pInstance, TRUE);
                _MLOAD_RETURN(pInstance);
            }
            else
            {
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK17_01_L, 0 ,BIT(0));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK57_23_L, 0 ,0x40);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_67_L, 0x80 ,0xF0);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, 0 ,BIT(0));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK11_20_L, 0 ,BIT(7));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK11_21_L, 0 ,BIT(15));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_78_L, 0 ,0xC000);
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK2A_02_L, BIT(1) ,BIT(1)|BIT(15));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_20_L, 0 ,BIT(0));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK05_12_L, 0 ,BIT(0));
                SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK2A_07_L, 0 ,BIT(0));
            }

            u16FDMaskCount=0;

            if(TRUE == MDrv_XC_InterruptIsAttached(pInstance, SC_INT_VSINT, MHal_XC_DTVPatchISR, (void *)NULL))
            {
                //Disable ISR
                MDrv_XC_InterruptDeAttachWithoutMutex(pInstance, SC_INT_VSINT, MHal_XC_DTVPatchISR, (void *)NULL);
            }
        }
    }
}

void MHal_XC_DTVPatch(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(eWindow ==MAIN_WINDOW)
    {
        if(IsSrcTypeDTV(gSrcInfo[MAIN_WINDOW].enInputSourceType)
            &&(gSrcInfo[MAIN_WINDOW].stCapWin.width==1920)
            &&(gSrcInfo[MAIN_WINDOW].stCapWin.height==1080)
            &&(gSrcInfo[MAIN_WINDOW].bInterlace==TRUE))
        {
            //DTV 1080i patch
            if(FALSE == MDrv_XC_InterruptIsAttached(pInstance, SC_INT_VSINT,MHal_XC_DTVPatchISR, (void *)NULL))
            {
                //Start DTV 1080i patch, enable ISR
                MDrv_XC_InterruptAttachWithoutMutex(pInstance, SC_INT_VSINT,MHal_XC_DTVPatchISR, (void *)NULL);
            }
        }
        else
        {
            if(TRUE == MDrv_XC_InterruptIsAttached(pInstance, SC_INT_VSINT, MHal_XC_DTVPatchISR, (void *)NULL))
            {
                //Disable ISR
                MDrv_XC_InterruptDeAttachWithoutMutex(pInstance, SC_INT_VSINT, MHal_XC_DTVPatchISR, (void *)NULL);
            }
        }
    }
}


#ifndef DONT_USE_CMA
#if (XC_SUPPORT_CMA ==TRUE)
MS_U64 MHal_XC_Get_CMA_Addr(void *pInstance, XC_CMA_CLIENT enCmaClient, MS_U32 u32GetCMASize, SCALER_WIN eWindow)
{
    MS_U64 u64CMAAddr = 0;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if (u32GetCMASize == 0)
    {
        return u64CMAAddr;
    }

    struct CMA_Pool_Alloc_Param CMA_Pool_GetMem;
    CMA_Pool_GetMem.pool_handle_id = CMA_Pool_Init_PARAM[enCmaClient].pool_handle_id;
    CMA_Pool_GetMem.offset_in_pool = stXC_CMA_Config[enCmaClient].u64AddrHeapOffset;
    CMA_Pool_GetMem.flags = CMA_FLAG_VIRT_ADDR;
    if(CMA_Pool_Init_PARAM[enCmaClient].heap_length >= u32GetCMASize)
    {
        CMA_Pool_GetMem.length = u32GetCMASize;
    }
    else
    {
        printf("\033[35m   Function = %s, Line = %d, CMA_POOL_INIT GetMem ERROR!!\033[m\n", __PRETTY_FUNCTION__, __LINE__);
        CMA_Pool_GetMem.length = CMA_Pool_Init_PARAM[enCmaClient].heap_length;
    }

    MApi_CMA_Pool_GetMem(&CMA_Pool_GetMem);
    u64CMAAddr = CMA_Pool_Init_PARAM[enCmaClient].heap_miu_start_offset;
    if(CMA_Pool_Init_PARAM[enCmaClient].miu==E_CHIP_MIU_1)
    {
        u64CMAAddr= CMA_Pool_Init_PARAM[enCmaClient].heap_miu_start_offset+HAL_MIU1_BASE;
    }
    else if(CMA_Pool_Init_PARAM[enCmaClient].miu==E_CHIP_MIU_2)
    {
        u64CMAAddr= CMA_Pool_Init_PARAM[enCmaClient].heap_miu_start_offset+HAL_MIU2_BASE;
    }

    return u64CMAAddr;
}

static void _Hal_SC_Limit_WriteMem(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    MS_PHY u32WriteLimitAddr = 0;
    MS_BOOL bNeedRestore = FALSE;

    if (pXCResourcePrivate->stdrvXC_MVideo_Context.g_u32MLoadBufByteLen_Suspend > MS_MLOAD_MAX_CMD_CNT*MS_MLOAD_CMD_LEN + BYTE_PER_WORD)
    {
        // using mload last 32byte
        u32WriteLimitAddr = pXCResourcePrivate->stdrvXC_MVideo_Context.g_u32MLoadPhyAddr_Suspend + pXCResourcePrivate->stdrvXC_MVideo_Context.g_u32MLoadBufByteLen_Suspend - BYTE_PER_WORD;
    }
    else
    {
        printf("\033[35m   Function = %s, Line = %d, _Hal_SC_Limit_WriteMem ,no buff for xc fbl to write!!\033[m\n", __PRETTY_FUNCTION__, __LINE__);
        assert(0);
    }

    if (Hal_SC_Is_InputSource_Disable(pInstance, eWindow)==0)
    {
        bNeedRestore = TRUE;
        MDrv_XC_DisableInputSource(pInstance, TRUE, eWindow);
    }
    MDrv_XC_SetFrameBufferAddress(pInstance, u32WriteLimitAddr, 0, eWindow);
    if (bNeedRestore == TRUE)
    {
        bNeedRestore = FALSE;
        MDrv_XC_DisableInputSource(pInstance, FALSE, eWindow);
    }
}

static void _Hal_SC_Limit_Dual_WriteMem(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    MS_BOOL bNeedRestore = FALSE;

    if (Hal_SC_Is_InputSource_Disable(pInstance, eWindow)==0)
    {
        bNeedRestore = TRUE;
        MDrv_XC_DisableInputSource(pInstance, TRUE, eWindow);
    }

    if(eWindow == MAIN_WINDOW)
    {
        /// need to disable the r/w request, when change the write limit base
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_07_L, BIT(0)|BIT(1), BIT(0)|BIT(1));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK0D_38_L, BIT(4),BIT(4)); //F2 memory address limit enable
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK11_29_L, 0, BIT(15));   // disable dual to defect xc dual write miu
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_48_L, 0x00); //F2 memory min address
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK0D_4A_L, 0x00); //F2 memory max address
    }
    pXCResourcePrivate->stdrvXC_Scaling._u32PreDualFBAddress[eWindow] = 0;
    pXCResourcePrivate->stdrvXC_Scaling._u32PreDualFBSize[eWindow] = 0;

    if (bNeedRestore == TRUE)
    {
        bNeedRestore = FALSE;
        MDrv_XC_DisableInputSource(pInstance, FALSE, eWindow);
    }
}

MS_BOOL MHal_XC_Release_CMA(void *pInstance, XC_CMA_CLIENT enCmaClient, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    struct CMA_Pool_Free_Param stCMAFreeParam;
    if ((gSrcInfo[eWindow].u32PreCMAMemSCMSize[enCmaClient]+gSrcInfo[eWindow].u32PreCMAMemFRCMSize[enCmaClient])!=0)
    {
        _Hal_SC_Limit_WriteMem(pInstance, eWindow);
        stCMAFreeParam.pool_handle_id = CMA_Pool_Init_PARAM[enCmaClient].heap_id; //in: pool handle id, when pool init, returned by kernel
        stCMAFreeParam.offset_in_pool = stXC_CMA_Config[enCmaClient].u64AddrHeapOffset;
        stCMAFreeParam.length = gSrcInfo[eWindow].u32PreCMAMemSCMSize[enCmaClient]+gSrcInfo[eWindow].u32PreCMAMemFRCMSize[enCmaClient];
        MApi_CMA_Pool_PutMem(&stCMAFreeParam);

        gSrcInfo[eWindow].u32PreCMAMemSCMSize[enCmaClient] = 0;
        gSrcInfo[eWindow].u32PreCMAMemFRCMSize[enCmaClient] = 0;
    }

    if ((gSrcInfo[MAIN_WINDOW].Status2.u32PreCMAMemDualSCMSize != 0) && (enCmaClient == CMA_XC_COBUFF_MEM))
    {
        _Hal_SC_Limit_Dual_WriteMem(pInstance, eWindow);
        stCMAFreeParam.pool_handle_id = CMA_Pool_Init_PARAM[enCmaClient].heap_id; //in: pool handle id, when pool init, returned by kernel
        stCMAFreeParam.offset_in_pool = stXC_CMA_Config[enCmaClient].u64AddrHeapOffset;
        stCMAFreeParam.length = gSrcInfo[MAIN_WINDOW].Status2.u32PreCMAMemDualSCMSize;
        MApi_CMA_Pool_PutMem(&stCMAFreeParam);

        gSrcInfo[MAIN_WINDOW].Status2.u32PreCMAMemDualSCMSize = 0;
    }

    return TRUE;
}

MS_BOOL MHal_XC_Get_CMA_UsingCondition(void *pInstance, MS_BOOL bIsGetCMABuff[], MS_U32 au32CMAMemSCMSize[],MS_U32 au32CMAMemFRCMSize[], MS_U32* pu32DualMiuMemSize, MS_U32 u32DataSize, SCALER_WIN eWindow)
{
    MS_U32 u32CMAMemSCMSize = 0;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if (u32DataSize < CMA_XC_MEM_NUM)
    {
        return FALSE;
    }

    if ((MHal_XC_Is_DSForceIndexEnabled(pInstance, MAIN_WINDOW)||MHAL_SC_Get_DynamicScaling_Status(pInstance))
        && IsSrcTypeStorage(gSrcInfo[eWindow].enInputSourceType))
    {
        if(pXCResourcePrivate->stdrvXC_MVideo_Context.g_XC_Init_Misc.u32MISC_B & E_XC_INIT_MISC_B_DISABLE_SUPPORT_4K2K)
        {
            u32CMAMemSCMSize = XC_CMA_24MB;
        }
        else
        {
            // MM source and DS on
            if(gSrcInfo[eWindow].bInterlace)
            {
                //DS ON , FHD case
                u32CMAMemSCMSize = XC_CMA_24MB;
            }
            else
            {
                //DS ON , 4K2K case
                u32CMAMemSCMSize = 0;
            }
        }
    }
    else if (IsSrcTypeStorage(gSrcInfo[eWindow].enInputSourceType))
    {
        u32CMAMemSCMSize = XC_CMA_24MB;
    }
    else if (  (IsSrcTypeAV(gSrcInfo[eWindow].enInputSourceType))
             ||(IsSrcTypeSV(gSrcInfo[eWindow].enInputSourceType))
             ||(IsSrcTypeATV(gSrcInfo[eWindow].enInputSourceType))
             ||(IsSrcTypeScart(gSrcInfo[eWindow].enInputSourceType)))
    {
        u32CMAMemSCMSize = XC_CMA_19MB;
    }
    else
    {
        u32CMAMemSCMSize = XC_CMA_24MB;
    }

    if (stXC_CMA_Config[CMA_XC_COBUFF_MEM].u32HeapID == XC_INVALID_HEAP_ID || IsSrcTypeStorage(gSrcInfo[eWindow].enInputSourceType) || IsSrcTypeDTV(gSrcInfo[eWindow].enInputSourceType))
    {
        bIsGetCMABuff[CMA_XC_SELF_MEM] = TRUE;
        bIsGetCMABuff[CMA_XC_COBUFF_MEM] = FALSE;
        au32CMAMemSCMSize[CMA_XC_SELF_MEM] = u32CMAMemSCMSize;
        au32CMAMemSCMSize[CMA_XC_COBUFF_MEM] = 0;
    }
    else
    {
        bIsGetCMABuff[CMA_XC_SELF_MEM] = FALSE;
        bIsGetCMABuff[CMA_XC_COBUFF_MEM] = TRUE;
        au32CMAMemSCMSize[CMA_XC_SELF_MEM] = 0;
        au32CMAMemSCMSize[CMA_XC_COBUFF_MEM] = u32CMAMemSCMSize;
    }
    *pu32DualMiuMemSize = 0;

    au32CMAMemFRCMSize[CMA_XC_SELF_MEM] = 0;
    au32CMAMemFRCMSize[CMA_XC_COBUFF_MEM] = 0;

    return TRUE;
}

static void  MHal_XC_CMAPatchISR(SC_INT_SRC eIntNum, void * pParam)
{
    void *pInstance = pu32XCInst_private;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));


    if(((MsOS_GetSystemTime()- u32CMAPatchTimer_Main)>6000))
    {
        u32CMAPatchTimer_Main = MsOS_GetSystemTime();
    }

    if((MDrv_XC_IsInputSourceDisabled(pInstance, MAIN_WINDOW)==TRUE)
       &&(   ((gSrcInfo[MAIN_WINDOW].u32PreCMAMemSCMSize[CMA_XC_SELF_MEM]+gSrcInfo[MAIN_WINDOW].u32PreCMAMemFRCMSize[CMA_XC_SELF_MEM])!=0)
           ||((gSrcInfo[MAIN_WINDOW].u32PreCMAMemSCMSize[CMA_XC_COBUFF_MEM]+gSrcInfo[MAIN_WINDOW].u32PreCMAMemFRCMSize[CMA_XC_COBUFF_MEM])!=0)
#ifdef SUPPORT_DUAL_MIU
           ||(gSrcInfo[MAIN_WINDOW].Status2.u32PreCMAMemDualSCMSize!=0)
#endif
         )
       )
    {
        //Check timing 5s
        if(((MsOS_GetSystemTime()- u32CMAPatchTimer_Main)>5000))
        {
            u32CMAPatchTimer_Main = MsOS_GetSystemTime();

            MHal_XC_Release_CMA(pInstance, CMA_XC_SELF_MEM, MAIN_WINDOW);
            MHal_XC_Release_CMA(pInstance, CMA_XC_COBUFF_MEM, MAIN_WINDOW);
        }
    }
    else
    {
        u32CMAPatchTimer_Main = MsOS_GetSystemTime();
    }
}

void MHal_XC_CMAPatch(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(eWindow ==MAIN_WINDOW)
    {
        if(FALSE == MDrv_XC_InterruptIsAttached(pInstance, SC_INT_VSINT,MHal_XC_CMAPatchISR, (void *)NULL))
        {
           //Start CMA  patch, enable ISR
           //FIXME: PATCH
           MDrv_XC_InterruptAttachWithoutMutex(pInstance, SC_INT_VSINT,MHal_XC_CMAPatchISR, (void *)NULL);
        }
    }
}

void MHal_XC_CMAPatchClose(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(eWindow ==MAIN_WINDOW)
    {
        if(TRUE == MDrv_XC_InterruptIsAttached(pInstance, SC_INT_VSINT, MHal_XC_CMAPatchISR, (void *)NULL))
        {
            //Disable ISR
            MDrv_XC_InterruptDeAttachWithoutMutex(pInstance, SC_INT_VSINT, MHal_XC_CMAPatchISR, (void *)NULL);
        }
    }
}
#endif
#endif

void MHAL_SC_set_r2y_en(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK18_06_L, bEnable?BIT(0):0x00, BIT(0));
    }
    else if(eWindow == SUB_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK18_76_L, bEnable?BIT(0):0x00, BIT(0));
    }
}

MS_BOOL MHAL_SC_get_r2y_en_status(void *pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    MS_BOOL bstatus = FALSE;

    if(eWindow == MAIN_WINDOW)
    {
        bstatus = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK18_06_L, BIT(0));
    }
    else if(eWindow == SUB_WINDOW)
    {
        bstatus = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK18_76_L, BIT(0));
    }

    return bstatus;
}

void Hal_SC_set_T3D_setting(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK62_63_L, 0x00, BIT(0)); // default disable T3D SRAM
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK62_63_L, 0x00, BIT(0)); // default disable T3D SRAM
    }

}

void Hal_SC_set_T3D_H_size(void *pInstance, MS_U16 u16Hsize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK63_55_L, u16Hsize, 0x1FFF); //horizontal pixel number
}

MS_BOOL Hal_SC_3D_Is_LR_Sbs2Line(void *pInstance)
{
    if(SC_R2BYTEMSK(0, REG_SC_BK23_53_L, BIT(15)))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

void Hal_SC_3D_SetLRChgMode(void *pInstance, HAL_SC_3D_LRCHGMODE eLRChgMode)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_63_L, eLRChgMode, BIT(1)|BIT(0));
}

// 0: L is the first frame, 1: R is the first frame
void Hal_SC_3D_SetInitialLRIndex(void *pInstance, MS_BOOL bRFirst)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_63_L, (bRFirst==TRUE)?BIT(4):0, BIT(4));
}

// Split 1 frame into 2 frames
void Hal_SC_3D_SetSplitHalf(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_63_L, (bEnable==TRUE)?BIT(8):0, BIT(8));
}

void Hal_SC_set_frcm_to_FD_mask(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_02_L, (bEnable==TRUE)?BIT(2):0, BIT(2));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_02_L, (bEnable==TRUE)?BIT(10):0, BIT(10));
    }
}

void Hal_SC_3D_set_top_win_6Tap(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK57_23_L, (bEnable==TRUE)?BIT(10):0, BIT(10)); //force top window using 6line
}

void Hal_SC_3D_SetActiveVideoHeight(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_65_L,u16VideoSize,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_65_L, u16VideoSize, 0x1FFF);//v_active region
    }
}

// 0 for blank area 0
//v blanking between field1&field2 or field3&field4
void Hal_SC_3D_SetActiveBlankSize0(void *pInstance, MS_U16 u16BlankSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    #if _ENABLE_SW_DS
        if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
        {
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_66_L,u16BlankSize,DS_IP);
        }
        else
    #endif
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_66_L, u16BlankSize, 0x1FFF);
        }
}

// 1 for blank area 1
//v blanking between field2&field3
void Hal_SC_3D_SetActiveBlankSize1(void *pInstance, MS_U16 u16BlankSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    #if _ENABLE_SW_DS
        if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
        {
            Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_67_L,u16BlankSize,DS_IP);
        }
        else
    #endif
        {
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_67_L, u16BlankSize, 0x1FFF);//v blanking between field1&field2 or field3&field4
        }
}

void Hal_SC_3D_SetActiveVideoWidth(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    MS_U16 u16ActiveWidthUsrEnable = 0;
    if (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_2F_L, BIT(15)) == BIT(15))
    {
        u16ActiveWidthUsrEnable = BIT(15);
    }

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_7F_L,u16VideoSize | u16ActiveWidthUsrEnable,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_7F_L, u16VideoSize | u16ActiveWidthUsrEnable, 0x9FFF);//v_active region
    }
}


void Hal_SC_3D_SetActiveVideoHeightAfterVSD(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    MS_U16 u16Enable = BIT(15);

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_38_L,u16VideoSize | u16Enable,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_38_L, u16VideoSize | u16Enable, 0x9FFF);
    }
}

void Hal_SC_3D_SetFRCMActiveVideoHeightAfterVSD(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    MS_U16 u16Enable = BIT(15);

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK48_38_L,u16VideoSize | u16Enable,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK48_38_L, u16VideoSize | u16Enable, 0x9FFF);
    }
}

void Hal_SC_3D_SetPixelSeparationWidth(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    MS_U16 u16ActiveWidthUsrEnable = 0;
#if (HW_DESIGN_3D_VER >= 3)
    if (SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_2F_L, BIT(15)) == BIT(15))
    {
        u16ActiveWidthUsrEnable = BIT(15);
    }
#endif

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK02_6C_L,u16VideoSize | u16ActiveWidthUsrEnable,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK02_6C_L, u16VideoSize | u16ActiveWidthUsrEnable, 0x87FF);
    }
}

void Hal_SC_3D_SetSoftware_F1VBottomEndPosition(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK57_4F_L,u16VideoSize,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK57_4F_L, u16VideoSize, 0x0FFF);
    }
}

void Hal_SC_3D_SetSoftware_F2VBottomEndPosition(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK57_4D_L,u16VideoSize,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK57_4D_L, u16VideoSize, 0x0FFF);
    }
}

void Hal_SC_3D_SetSoftware_F1VBottomStartPosition(void *pInstance, MS_U16 u16VideoSize)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

#if _ENABLE_SW_DS
    if(MHAL_SC_Get_DynamicScaling_Status(pInstance))
    {
        Hal_SC_WriteSWDSCommand(pInstance,MAIN_WINDOW,REG_SC_BK57_4E_L,u16VideoSize,DS_IP);
    }
    else
#endif
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK57_4E_L, u16VideoSize, 0x0FFF);
    }
}

void Hal_SC_set_frcm_to_freeze(void *pInstance, MS_BOOL bEnable, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_02_L, (bEnable==TRUE)?BIT(0):0, BIT(0));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_02_L, (bEnable==TRUE)?BIT(8):0, BIT(8));
    }
}

E_APIXC_ReturnValue Hal_SC_SetOSDDetect(void *pInstance, MS_BOOL bEnable, MS_U32 Threhold)
{
    MS_U16 u16Reg = 0;
	XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if(Threhold == 0)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_6A_L, 0x0, (BIT(15)+BMASK(11:0)));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK25_2E_L, BIT(1), BIT(1));

    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK25_2E_L, 0x0, BIT(1));
        u16Reg = ((MS_U16)Threhold*2)|(bEnable << 15);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_6A_L, u16Reg, (BIT(15)+BMASK(11:0)));
    }
    return E_APIXC_RET_OK;
}

E_APIXC_ReturnValue Hal_SC_GetOSDDetect(void *pInstance, MS_BOOL *pbOSD)
{
    MS_U16 u16Reg = 0;
	XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    u16Reg = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK10_6A_L);
    *pbOSD = ((u16Reg&BIT(14))>>14);
    return E_APIXC_RET_OK;
}

void Hal_SC_SetHDMI_Spliter(void *pInstance,XC_IP_SYNC_STATUS *sXC_Sync_Status,E_MUX_INPUTPORT enInputPort ,SCALER_WIN eWindow)
{

#if 0//SUPPORT_HDMI20
	XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    MS_U16 u16HDE_temp_size,u16HDE_size =0;

        if((sXC_Sync_Status->u8SyncStatus & XC_MD_SYNC_LOSS) != XC_MD_SYNC_LOSS)
        {
            if(MDrv_HDMI_CheckHDMI20_Setting(enInputPort))
            {
                //printf("[%s][%d]HDMI 4K2K 2P mode\n", __FUNCTION__, __LINE__);
                if(eWindow == MAIN_WINDOW)
                    W2BYTEMSK(0x102e02,0x0010,BMASK(7:4)); // ipmux sel=0xb
                else if(eWindow == SUB_WINDOW)
                    W2BYTEMSK(0x102e02,0x0001,BMASK(3:0)); // ipmux sel=0xb

            }
            else
            {
                //SUPPORT_HDMI20_420
                //printf("[%s][%d]HDMI 4K2K 2P mode\n", __FUNCTION__, __LINE__);
                //printf("[%s][%d]sXC_Sync_Status->u16Vtotal=%x, sXC_Sync_Status->u16Hperiod=%x\n",
                //    __FUNCTION__, __LINE__, sXC_Sync_Status->u16Vtotal, sXC_Sync_Status->u16Hperiod);
                if((sXC_Sync_Status->u16Vtotal >= 0x8C0)
                 &&(sXC_Sync_Status->u16Hperiod>= 0x50))
                {
                    if((MDrv_HDMI_avi_infoframe_info(_BYTE_1)& 0x60) == 0x60)
                    {
                        //printf("@@#@@4K2K@60 420\n");
                        // clkgen2
                        W2BYTE(0x100a80,0x0004); // spt_l0 1: hdmi d: mhl
                        // ipmux
                        if(eWindow == MAIN_WINDOW)
                        {
                            W2BYTEMSK(0x102e02,0x00b0,BMASK(7:4)); // ipmux sel=0xb
                        }
                        else if(eWindow == SUB_WINDOW)
                        {
                            W2BYTEMSK(0x102e02,0x000b,BMASK(3:0)); // ipmux sel=0xb
                        }

                        //BK40_SPT4k
                        SC_W2BYTE(0, REG_SC_BK40_01_L,0x0000); // [3:0]  reg_spt_ipmux_sel0
                                                            // [11:8] reg_spt_ipmux_sel1
                        SC_W2BYTE(0, REG_SC_BK40_03_L,0x0001); // [7] reg_spt_2p_oe_en [0] reg_spt_420_en
                        SC_W2BYTE(0, REG_SC_BK40_04_L,0x0180); // [7] reg_spt_2p_oe_out_en [9] hsd_en
                                                            // [8] reg_spt_2poe_out_sel 1'b0: dual ch eo in
                                                            //                                    1'b1: dual ch LR in or 420
                        SC_W2BYTE(0, REG_SC_BK40_30_L, 0x0003); // de_only
                        SC_W2BYTE(0, REG_SC_BK40_0B_L, 0x0000); // gb_size

                        u16HDE_temp_size = MDrv_HDMI_GetHDE();
                        //printf("[%s][%d]u16HDE_size=%u\n", __FUNCTION__, __LINE__,u16HDE_temp_size);
                        if((u16HDE_temp_size >= 2028)&&(u16HDE_temp_size<= 2068))
                        {
                            u16HDE_size = 2048;
                        }
                        else //if((u16HDE_temp_size >= 1900)&&(u16HDE_temp_size<= 1940))
                        {
                            u16HDE_size = 1920;
                        }
                        SC_W2BYTE(0, REG_SC_BK40_08_L, u16HDE_size); // de_in_size
                        SC_W2BYTE(0, REG_SC_BK40_0A_L, u16HDE_size); // de_out_with_gb_size

                        SC_W2BYTE(0, REG_SC_BK40_20_L, 0x0000); // ra
                        SC_W2BYTE(0, REG_SC_BK40_21_L, u16HDE_size/2-2); //
                        SC_W2BYTE(0, REG_SC_BK40_22_L, 0x0001);
                        SC_W2BYTE(0, REG_SC_BK40_23_L, u16HDE_size/2-1);

                        SC_W2BYTE(0, REG_SC_BK40_24_L, 0x0000); // wa
                        SC_W2BYTE(0, REG_SC_BK40_25_L, u16HDE_size/2-2);
                        SC_W2BYTE(0, REG_SC_BK40_26_L, 0x0001);
                        SC_W2BYTE(0, REG_SC_BK40_27_L, u16HDE_size/2-1);
                    }
                    else
                    {
                        //printf("@@#@@4K2K@30\n");
                        /// for 4K2K@30Hz
                        if(eWindow == MAIN_WINDOW)
                        {
                            W2BYTEMSK(0x102e02,0x0010,BMASK(7:4)); // ipmux sel=0xb
                        }
                        else if(eWindow == SUB_WINDOW)
                        {
                            W2BYTEMSK(0x102e02,0x0001,BMASK(3:0)); // ipmux sel=0xb
                        }
                    }
                }
            }
        }
#endif
}

void Hal_SC_Set_2pmode(void *pInstance,MS_BOOL benable_IP2p,MS_BOOL benable_OP2p,MS_BOOL benable_bypass_all_2p,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    if(eWindow == MAIN_WINDOW)
    {
        SC_W2BYTEMSK(0, REG_SC_BK01_07_L,(benable_IP2p ? BIT(15):0), BIT(15));//reg_sprange_hdc_2p
        SC_W2BYTEMSK(0, REG_SC_BK20_01_L,(benable_OP2p ? BIT(1):0), BIT(1));//reg_opm_2p_mode
        SC_W2BYTEMSK(0, REG_SC_BK12_04_L,(benable_bypass_all_2p ? BIT(6):0), BIT(6));//reg_bypass_all_2p_f2
    }
}

void MHal_SC_set_manual_rbank_switch_cnt(void *pInstance, MS_BOOL bEnable, MS_U16 u16SwitchCnt, SCALER_WIN eWindow)
{
    if (eWindow >= MAX_WINDOW)
    {
        printf("unsupported eWindow, return!\n");
        return;
    }

    if( eWindow == MAIN_WINDOW)
    {
        // these two registers must be set simultaneously for this feature to work
        // frame rate convert dependence with IP write line count
        SC_W2BYTEMSK(0,REG_SC_BK12_05_L, bEnable? BIT(3):0, BIT(3));
        // frame rate convert dependence with IP write line count FULL
        SC_W2BYTEMSK(0,REG_SC_BK11_18_L, bEnable? BIT(15):0, BIT(15));

        // set specific line count according to when you will change rbank switch
        // this line count starts at VDE rising edge, ends at u16SwitchCnt
        SC_W2BYTEMSK(0,REG_SC_BK11_18_L, u16SwitchCnt, 0x1FFF);
    }
    else
    {
        // these two registers must be set simultaneously for this feature to work
        // frame rate convert dependence with IP write line count
        SC_W2BYTEMSK(0,REG_SC_BK12_45_L, bEnable? BIT(3):0, BIT(3));
        // frame rate convert dependence with IP write line count FULL
        SC_W2BYTEMSK(0,REG_SC_BK11_58_L, bEnable? BIT(15):0, BIT(15));

        // set specific line count according to when you will change rbank switch
        // this line count starts at VDE rising edge, ends at u16SwitchCnt
        SC_W2BYTEMSK(0,REG_SC_BK11_58_L, u16SwitchCnt, 0x1FFF);
    }
}

#define  IsEnableDualMode(eWindow)  (gSrcInfo[eWindow].Status2.stMiuDualModCfg.bEnableMiuDualMod == TRUE)
#ifdef SUPPORT_BWD
static void _HAL_SC_BWR_set_base_address(void *pInstance, MS_U16 u16MemCfgValue,MS_U16 u16MemCfgIndex, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    E_XC_BWR_MEM_CONFIG u8Memtype = E_XC_BWR_MEM_CONFIG_1;
    E_XC_BWR_MEM_CFG_BPP_TYPE eBPPType = E_XC_BWR_MEM_CFG_BPP_24;
    for(u8Memtype=E_XC_BWR_MEM_CONFIG_1;u8Memtype<E_XC_BWR_MEM_CONFIG_Max;u8Memtype++)
    {
        if(u16MemCfgValue == gSrcInfo[eWindow].Status2.stMemCfgMap[u8Memtype].u16BWR_MEM_CFG_VALUE)
        {
            eBPPType = gSrcInfo[eWindow].Status2.stMemCfgMap[u8Memtype].eBitPerPixelType;
            break;
        }
    }

#ifdef  SUPPORT_DUAL_MIU
    if (IsEnableDualMode(eWindow))
    {
        //SCMI: IPM address 0
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x40 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x41 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>16), 0x03FF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x48 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase0>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x49 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase0>>16), 0x03FF);
        //SCMI: IPM address 1
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x50 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x51 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>16), 0x03FF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x58 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase1>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x59 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase1>>16), 0x03FF);
        //SCMI: OPM address 0
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x60 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x61 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>16), 0x03FF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x68 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase0>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x69 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase0>>16), 0x03FF);
        //SCMI: OPM address 1
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x70 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x71 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>16), 0x03FF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x78 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase1>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x79 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase1>>16), 0x03FF);
    }
    else
#endif
    {
        //SCMI: IPM address 0
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x40 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x41 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>16), 0x03FF);
        //SCMI: IPM address 1
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x50 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x51 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>16), 0x03FF);
        //SCMI: OPM address 0
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x60 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x61 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>16), 0x03FF);
        //SCMI: OPM address 1
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x70 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>00), 0xFFFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, _PK_L_(0x46, (0x71 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>16), 0x03FF);
    }
}

void _HAL_SC_BWR_set_vlen(void * pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    if(gSrcInfo[eWindow].bPreV_ScalingDown)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3D_L, gSrcInfo[eWindow].u16V_SizeAfterPreScaling, 0x0FFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3D_L, BIT(15), BIT(15));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3D_L, 0, BIT(15));
    }

     //update BWR Configuration vlen,IP 3D source: LA
    if(MDrv_XC_Get_3D_Input_Mode(pInstance, eWindow) == E_XC_3D_INPUT_LINE_ALTERNATIVE)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3D_L, gSrcInfo[eWindow].u16V_SizeAfterPreScaling/2, 0x0FFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3D_L, BIT(15), BIT(15));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3D_L, 0, BIT(15));
    }

     //update BWR Configuration vlen,OP 3D output: LA
    if(MDrv_XC_Get_3D_Output_Mode(pInstance) == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3E_L, gSrcInfo[eWindow].u16V_Length*2, 0x0FFF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3E_L, BIT(15), BIT(15));
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3E_L, 0, BIT(15));
    }
}

static void _HAL_SC_BWR_set_3d_mode(void * pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    //BWR 422 to 420 set drop mode register
    if((MDrv_XC_Get_3D_Input_Mode(pInstance, eWindow) == E_XC_3D_INPUT_LINE_ALTERNATIVE) && (gSrcInfo[eWindow].stCapWin.width > 1920))
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_38_L, BIT(7), BIT(7));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3A_L, 0, BIT(2));
    }

    //BWR 422 to 420 set TB mode register
    if(MDrv_XC_Get_3D_Output_Mode(pInstance) == E_XC_3D_OUTPUT_TOP_BOTTOM)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_3A_L, BIT(4), BIT(4));
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_10_L, 0, BIT(11));
    }

    //OP1 must turn off initial process
    if(MDrv_XC_Get_3D_Output_Mode(pInstance) == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_29_L, 0, 0x0F0F);
    }
}

static void _HAL_SC_BWR_set_base_address_burst(void *pInstance, MS_U16 u16MemCfgValue,MS_U16 u16MemCfgIndex, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    E_XC_BWR_MEM_CONFIG u8Memtype = E_XC_BWR_MEM_CONFIG_1;
    E_XC_BWR_MEM_CFG_BPP_TYPE eBPPType = E_XC_BWR_MEM_CFG_BPP_24;
    for(u8Memtype=E_XC_BWR_MEM_CONFIG_1;u8Memtype<E_XC_BWR_MEM_CONFIG_Max;u8Memtype++)
    {
        if(u16MemCfgValue == gSrcInfo[eWindow].Status2.stMemCfgMap[u8Memtype].u16BWR_MEM_CFG_VALUE)
        {
            eBPPType = gSrcInfo[eWindow].Status2.stMemCfgMap[u8Memtype].eBitPerPixelType;
            break;
        }
    }

#ifdef SUPPORT_DUAL_MIU
    if (IsEnableDualMode(eWindow))
    {
        //SCMI: IPM address 0
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x40 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x41 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>16), 0x03FF);

        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x48 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase0>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x49 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase0>>16), 0x03FF);

        //SCMI: IPM address 1
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x50 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x51 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>16), 0x03FF);

        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x58 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x59 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_DNRBase1>>16), 0x03FF);

        //SCMI: OPM address 0
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x60 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x61 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>16), 0x03FF);

        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x68 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase0>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x69 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase0>>16), 0x03FF);

        //SCMI: OPM address 1
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x70 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x71 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>16), 0x03FF);

        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x78 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x79 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Right_OPMBase1>>16), 0x03FF);
    }
    else // Disbale dual
#endif
    {
        //SCMI: IPM address 0
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x40 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x41 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase0>>16), 0x03FF);

        //SCMI: IPM address 1
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x50 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x51 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_DNRBase1>>16), 0x03FF);

        //SCMI: OPM address 0
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x60 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x61 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase0>>16), 0x03FF);

        //SCMI: OPM address 1
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x70 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>00), 0xFFFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, _PK_L_(0x46, (0x71 + u16MemCfgIndex * 2)), (MS_U16)(gSrcInfo[eWindow].Status2.stBWRBase[eBPPType].u32BWR_Miu_Left_OPMBase1>>16), 0x03FF);
    }
}

static void _HAL_SC_BWR_set_vlen_burst(void * pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    //update BWR Configuration vlen,OP 3D output: LA
    if(gSrcInfo[eWindow].bPreV_ScalingDown)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3D_L, gSrcInfo[eWindow].u16V_SizeAfterPreScaling, 0x0FFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3D_L, BIT(15), BIT(15));
    }
    else
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3D_L, 0, BIT(15));
    }

     //update BWR Configuration vlen,IP 3D source: LA
    if(MDrv_XC_Get_3D_Input_Mode(pInstance, eWindow) == E_XC_3D_INPUT_LINE_ALTERNATIVE)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3D_L, gSrcInfo[eWindow].u16V_SizeAfterPreScaling/2, 0x0FFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3D_L, BIT(15), BIT(15));
    }
    else
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3D_L, 0, BIT(15));

    }

     //update BWR Configuration vlen,OP 3D output: LA
    if(MDrv_XC_Get_3D_Output_Mode(pInstance) == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3E_L, gSrcInfo[eWindow].u16V_Length*2, 0x0FFF);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3E_L, BIT(15), BIT(15));
    }
    else
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3E_L, 0, BIT(15));
    }
}

static void _HAL_SC_BWR_set_3d_mode_burst(void * pInstance, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    //BWR 422 to 420 set drop mode register
    if((MDrv_XC_Get_3D_Input_Mode(pInstance, eWindow) == E_XC_3D_INPUT_LINE_ALTERNATIVE) && (gSrcInfo[eWindow].stCapWin.width > 1920))
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_38_L, BIT(7), BIT(7));
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3A_L, 0, BIT(2));
    }

    //BWR 422 to 420 set TB mode register
    if(MDrv_XC_Get_3D_Output_Mode(pInstance) == E_XC_3D_OUTPUT_TOP_BOTTOM)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_3A_L, BIT(4),BIT(4));
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_10_L, 0, BIT(11));
    }

    //OP1 must turn off initial process
    if(MDrv_XC_Get_3D_Output_Mode(pInstance) == E_XC_3D_OUTPUT_LINE_ALTERNATIVE)
    {
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK20_29_L, 0, 0x0F0F);
    }
}
#endif

MS_BOOL HAL_SC_set_bwr_config_burst(void *pInstance, void *pstParam, SCALER_WIN eWindow)
{
#ifdef SUPPORT_BWD
    MS_U16 u16BwrMemCfgTmp = 0;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    u16BwrMemCfgTmp = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_17_L, 0xFFFF);
    _HAL_SC_BWR_set_base_address_burst(pInstance, (u16BwrMemCfgTmp&0x000F) >> 0,  E_XC_BWR_MME_CFG_INDEX_0, eWindow);
    _HAL_SC_BWR_set_base_address_burst(pInstance, (u16BwrMemCfgTmp&0x00F0) >> 4,  E_XC_BWR_MME_CFG_INDEX_1, eWindow);
    _HAL_SC_BWR_set_base_address_burst(pInstance, (u16BwrMemCfgTmp&0x0F00) >> 8,  E_XC_BWR_MME_CFG_INDEX_2, eWindow);
    _HAL_SC_BWR_set_base_address_burst(pInstance, (u16BwrMemCfgTmp&0xF000) >> 12, E_XC_BWR_MME_CFG_INDEX_3, eWindow);
    u16BwrMemCfgTmp = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_16_L, 0xF);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_28_L, u16BwrMemCfgTmp, 0x0F);
    MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK46_29_L, u16BwrMemCfgTmp, 0x0F);

    _HAL_SC_BWR_set_vlen_burst(pInstance, eWindow);
    _HAL_SC_BWR_set_3d_mode_burst(pInstance, eWindow);

    MDrv_XC_MLoad_Fire(pInstance, TRUE);
    return TRUE;
#else
    return FALSE;
#endif
}

MS_BOOL HAL_SC_set_bwr_config(void *pInstance, void *pstParam, SCALER_WIN eWindow)
{
#ifdef SUPPORT_BWD
    MS_U16 u16BwrMemCfgTmp = 0;
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

        u16BwrMemCfgTmp = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_17_L, 0xFFFF);
        _HAL_SC_BWR_set_base_address(pInstance, (u16BwrMemCfgTmp&0x000F) >> 0,  E_XC_BWR_MME_CFG_INDEX_0, eWindow);
        _HAL_SC_BWR_set_base_address(pInstance, (u16BwrMemCfgTmp&0x00F0) >> 4,  E_XC_BWR_MME_CFG_INDEX_1, eWindow);
        _HAL_SC_BWR_set_base_address(pInstance, (u16BwrMemCfgTmp&0x0F00) >> 8,  E_XC_BWR_MME_CFG_INDEX_2, eWindow);
        _HAL_SC_BWR_set_base_address(pInstance, (u16BwrMemCfgTmp&0xF000) >> 12, E_XC_BWR_MME_CFG_INDEX_3, eWindow);
        u16BwrMemCfgTmp = SC_R2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_16_L, 0xF);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_28_L, u16BwrMemCfgTmp, 0x0F);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK46_29_L, u16BwrMemCfgTmp, 0x0F);

    _HAL_SC_BWR_set_vlen(pInstance, eWindow);
    _HAL_SC_BWR_set_3d_mode(pInstance, eWindow);
    return TRUE;
#else
    return FALSE;
#endif
}

void Hal_SC_3D_Adjust_FP_PreHscaling(void *pInstance, XC_InternalStatus *pSrcInfo, MS_BOOL *pb3DPreHScaling)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if(pXCResourcePrivate->stdrvXC_3D._eOutput3DMode != E_XC_3D_OUTPUT_FRAME_ALTERNATIVE)
    {
        *pb3DPreHScaling = TRUE;
        pSrcInfo->Status2.u16PreHCusScalingSrc = pSrcInfo->stCapWin.width;
        pSrcInfo->Status2.u16PreHCusScalingDst = MAX(640, (MS_U32)MIN(1920, pSrcInfo->stDispWin.width) * 2 / 3);
    }
}

void Hal_SC_3D_Adjust_FA_PreHscaling(void *pInstance, XC_InternalStatus *pSrcInfo, MS_BOOL *pb3DPreHScaling)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    *pb3DPreHScaling = TRUE;
    pSrcInfo->Status2.u16PreHCusScalingSrc = pSrcInfo->stCapWin.width;
    pSrcInfo->Status2.u16PreHCusScalingDst = MIN(1280, pSrcInfo->stDispWin.width);
}
#undef  MHAL_SC_C