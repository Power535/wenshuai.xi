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
// (!��MStar Confidential Information!�L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////
//==============================================================================
// Common Definition
#ifndef MHAL_DYNAMICSCALING_C
#define MHAL_DYNAMICSCALING_C

#include "MsCommon.h"
#include "MsOS.h"
#include "mhal_xc_chip_config.h"
#include "utopia.h"
#include "utopia_dapi.h"
#if (SUPPORT_KERNEL_DS == 1)
#include "../../../drv/xc/mdrv_xc_st.h"
#include "../../../drv/xc/mdrv_xc_io.h"
#ifndef MSOS_TYPE_LINUX_KERNEL
#if (defined MSOS_TYPE_LINUX) || (defined ANDROID)
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#endif
#endif
#endif

#include "halCHIP.h"
#include "drvXC_IOPort.h"
#include "xc_hwreg_utility2.h"
#include "hwreg_sc.h"
#include "apiXC.h"
#include "apiXC_Adc.h"
#include "apiXC_Auto.h"
#include "drv_sc_display.h"
#include "drv_sc_isr.h"
#include "apiXC_PCMonitor.h"
#include "apiXC_ModeParse.h"
#include "drvXC_HDMI_if.h"
#include "mvideo_context.h"
#include "drv_sc_ip.h"
#if (LD_ENABLE==1)
#include "mdrv_ld.h"
#include "mdrv_ldalgo.h"
#endif
#include "mdrv_sc_3d.h"
#include "drv_sc_menuload.h"
#include "drvXC_ADC_Internal.h"
#include "mhal_dynamicscaling.h"
#include "mhal_sc.h"
#if FRC_INSIDE
#include "mdrv_frc.h"
#include "mhal_frc.h"
#endif
#include "mhal_menuload.h"
#include "XC_private.h"
#include "apiXC_v2.h"

#define DS_DBG(x)   //x
#define SLZ_DBG(x)  //x

//clear DS Buffer

#if (SUPPORT_KERNEL_DS == 1)
#if (defined MSOS_TYPE_LINUX) || (defined ANDROID)
static MS_S32   _s32FdScaler = -1;
#endif
#endif

#if (SUPPORT_KERNEL_DS == 1)
#ifdef MSOS_TYPE_LINUX_KERNEL
extern E_K_APIXC_ReturnValue KApi_XC_Set_DSForceIndex(EN_KDRV_SC_DEVICE u32DeviceID, MS_BOOL bEnable, MS_U8 u8Index, EN_KDRV_WINDOW  eWindow);
extern void KApi_XC_WriteSWDSCommand(EN_KDRV_SC_DEVICE u32DeviceID,EN_KDRV_WINDOW eWindow,E_DS_CLIENT client, MS_U32 u32CmdRegAddr, MS_U16 u16CmdRegValue,k_ds_reg_ip_op_sel IPOP_Sel,k_ds_reg_source_sel Source_Select,K_XC_DS_CMDCNT *pstXC_DS_CmdCnt);
extern void KApi_XC_WriteSWDSCommandNonXC(EN_KDRV_SC_DEVICE u32DeviceID, EN_KDRV_WINDOW eWindow, E_DS_CLIENT client, MS_U32 u32Bank, MS_U16 u32Addr, MS_U32 u16Data, MS_U16 u16Mask, k_ds_reg_ip_op_sel IPOP_Sel, K_XC_DS_CMDCNT *pstXC_DS_CmdCnt);
extern void KApi_XC_Add_NullCommand(EN_KDRV_SC_DEVICE u32DeviceID,EN_KDRV_WINDOW eWindow,E_DS_CLIENT client,k_ds_reg_ip_op_sel IPOP_Sel,K_XC_DS_CMDCNT *pstXC_DS_CmdCnt);
#endif
#endif

void Hal_SC_ResetSWDSCommand(void *pInstance,SCALER_WIN eWindow, MS_U8 u8DSIndex)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

#if ENABLE_64BITS_SPREAD_MODE

    MS_PHY u32IndexBase = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr;

    MS_U16 u16TotalCmdCnt = pXCResourcePrivate->sthal_SC.u32DynamicScalingBufSize/DS_CMD_LEN_64BITS;
    MS_U16 i = 0;

    MS_U64 *pu64Data = NULL;
    u16TotalCmdCnt /= 2;

    for(i = 0; i < u16TotalCmdCnt; i++)
    {
        pu64Data  = (MS_U64*)MsOS_PA2KSEG1(u32IndexBase + i*DS_CMD_LEN_64BITS);
        *pu64Data = 0x00000009FFFF0000;
    }

    u32IndexBase = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM;
    for(i = 0; i < u16TotalCmdCnt; i++)
    {
        pu64Data  = (MS_U64*)MsOS_PA2KSEG1(u32IndexBase + i*DS_CMD_LEN_64BITS);
        *pu64Data = 0x00000009FFFF0000;
    }

#else
    MS_PHY u32IndexBase = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr + (MS_U32)u8DSIndex * pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT;

    MS_U32 *pu32Data = NULL;
    int i = 0;

    //XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32DSBaseAddr:%lx  u32IndexBase:%ld  u8DSIndexDepth:%d  \n",__func__,__LINE__,pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr,u32IndexBase,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);

    for(i = 0; i < (pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT)/4; i++) //need check
    {
        if(i % 8 < 4)
        {
            if(MAIN_WINDOW == eWindow)
            {
                if(i % 4 < 2)
                {
                    pu32Data = (MS_U32*)MsOS_PA2KSEG1(u32IndexBase + (i*4));
                    if(0 == pu32Data)
                    {
                        printf("%s :pu32Data_1 = 0!,error!!!\n", __FUNCTION__);
                        assert(pu32Data != 0);
                    }
                    *pu32Data = 0xFFFF0000;
                }
            }
            else //SUB_WINDOW == eWindow
            {
                if(i % 4 >= 2)
                {
                    pu32Data = (MS_U32*)MsOS_PA2KSEG1(u32IndexBase + (i*4));
                    if(0 == pu32Data)
                    {
                        printf("%s :pu32Data_2 = 0!,error!!!\n", __FUNCTION__);
                        assert(pu32Data != 0);
                    }
                    *pu32Data = 0xFFFF0000;
                }
            }
        }
        else
        {
            if(MAIN_WINDOW == eWindow)
            {
                if(i % 4 < 2)
                {
                    pu32Data = (MS_U32*)MsOS_PA2KSEG1(u32IndexBase + (i*4));
                    if(0 == pu32Data)
                    {
                        printf("%s :pu32Data_3 = 0!,error!!!\n", __FUNCTION__);
                        assert(pu32Data != 0);
                    }
                    *pu32Data = 0xFFFF0000;//0;

                    //printf("[szuhua] [%s,%5d] [IP] 0xFFFF0000 \n",__func__,__LINE__);
                }
            }
            else //SUB_WINDOW == eWindow
            {
                if(i % 4 >= 2)
                {
                    pu32Data = (MS_U32*)MsOS_PA2KSEG1(u32IndexBase + (i*4));
                    if(0 == pu32Data)
                    {
                        printf("%s :pu32Data_4 = 0!,error!!!\n", __FUNCTION__);
                        assert(pu32Data != 0);
                    }
                    *pu32Data = 0xFFFF0000;
                }
            }
        }
    }
#endif
}

void Hal_SC_WriteSWDSCommand(void *pInstance,SCALER_WIN eWindow, MS_U32 u32CmdRegAddr, MS_U16 u16CmdRegValue,ds_reg_ip_op_sel IPOP_Sel,ds_reg_source_sel Source_Select,XC_DS_CMDCNT *pstXC_DS_CmdCnt)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
#if (SUPPORT_KERNEL_DS == 1)
#ifdef MSOS_TYPE_LINUX_KERNEL
        EN_KDRV_SC_DEVICE u32DeviceID;
        if(psXCInstPri->u32DeviceID == 0)
        {
            u32DeviceID = E_KDRV_XC_SC0;
        }
        else
        {
            u32DeviceID = E_KDRV_XC_SC1;
        }
        KApi_XC_WriteSWDSCommand(u32DeviceID,eWindow,E_DS_CLIENT_XC,u32CmdRegAddr,u16CmdRegValue,IPOP_Sel,Source_Select,(K_XC_DS_CMDCNT *)pstXC_DS_CmdCnt);
        return;
#else
#if (defined MSOS_TYPE_LINUX) || (defined ANDROID)
        if(0 > _s32FdScaler)
        {
            _s32FdScaler = open("/dev/scaler", O_WRONLY | O_NDELAY);
        }

        if (0 > _s32FdScaler)
        {
            printf("\nUnable to open /dev/scaler\n");
            return ;
        }
        else
        {
            ST_KDRV_DS_WriteSWDSCommand k_ds_WriteSWDSCommand;
            if(psXCInstPri->u32DeviceID == 0)
                k_ds_WriteSWDSCommand.u32DeviceID = E_KDRV_XC_SC0;
            else
                k_ds_WriteSWDSCommand.u32DeviceID = E_KDRV_XC_SC1;
            k_ds_WriteSWDSCommand.eWindow = eWindow;
            k_ds_WriteSWDSCommand.client = E_DS_CLIENT_XC;
            k_ds_WriteSWDSCommand.u32CmdRegAddr = u32CmdRegAddr;
            k_ds_WriteSWDSCommand.u16CmdRegValue = u16CmdRegValue;
            k_ds_WriteSWDSCommand.IPOP_Sel = IPOP_Sel;
            k_ds_WriteSWDSCommand.Source_Select = Source_Select;
            k_ds_WriteSWDSCommand.pstXC_DS_CmdCnt = (K_XC_DS_CMDCNT *)pstXC_DS_CmdCnt;
            if (-1 == ioctl(_s32FdScaler, MDRV_XC_IOC_DS_WRITE_SWDS_CMD,&k_ds_WriteSWDSCommand))
            {
                perror("ioctl");
                return ;
            }
            return ;
        }
#endif
#endif
#else

#if ENABLE_DS_4_BASEADDR_MODE
    MS_PHY u32Addr = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr + pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] * pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT;
    MS_PHY u32Addr_OPM = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM + pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] * pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT;
    MS_PHY u32Addr_IPS = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_IPS + pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] * pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT;
    MS_PHY u32Addr_OPS = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPS + pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] * pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT;
#else
    MS_PHY u32Addr = pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr + pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] * pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * MS_MLOAD_MEM_BASE_UNIT;
#endif

    //XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32DynamicScalingBaseAddr:%x  CurIdx:%d  IdxDepth:%d  BYTE_PER_WORD:%d  \n",__func__,__LINE__,(int)pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr,(int)pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow],(int)pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth,(int)BYTE_PER_WORD);
    //XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32Addr:%x  \n",__func__,__LINE__,(int)u32Addr);

#if ENABLE_DS_4_BASEADDR_MODE

    MS_U64 *pu64Data = NULL;
    MS_U64 u64CmdTemp = 0;
    MS_U8  u8AddrTemp = 0;
    MS_U16 u16BankTemp = 0;
    MS_U16 u16DataTemp = 0;
    MS_U16 u16MaskTemp = 0;
    MS_U8 u8MaxCmdCnt = pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * 2;


//===========================================================//
//  64bit command format (spread mode)
//  |-------------|-------------|----------------------------|-------------|
//  |    Bit-En   |    Unused   |    Addr(FULL RIU ADDR)     |     Data    |
//  |-------------|-------------|----------------------------|-------------|
//  |   [63:48]   |   [47:40]   |           [39:16]          |   [15:0]    |
//  |-------------|-------------|----------------------------|-------------|

//Addr: FULL RIU ADDRESS !!!

//For example:  Subbank:0x01            addr:0x40 Data:0x0001
//              Spread mode :  0x1301   addr:0x40 Data:0x0001

//|----------------------------------------------------|
//|                      Bank             |    addr    |
//|----------------------------------------------------|
//|                     0x1301            |    0x40    |
//|----------------------------------------------------|
// FULL RIU ADDRESS: |0001 0011 0000 0001 |  100 0000  |
// FULL RIU ADDRESS:              0x0980C1
//===========================================================//

    if(Source_Select == DS_XC)
    {
        u16MaskTemp = 0xFFFF;
        u16DataTemp = u16CmdRegValue;

        u8AddrTemp= (u32CmdRegAddr & 0x000000FF) >> 1;
        u16BankTemp= 0x1300 | ((u32CmdRegAddr >> 8) & 0x000000FF); // 0x13XX xc sread mode address

        u64CmdTemp|= (MS_U64)u16DataTemp;
        u64CmdTemp|= ((MS_U64)u8AddrTemp<<16);
        u64CmdTemp|= ((MS_U64)u16BankTemp<<23);
        u64CmdTemp|= ((MS_U64)u16MaskTemp<<48);

        if(IPOP_Sel == DS_IP)
        {
            if(eWindow == MAIN_WINDOW)
            {
                MS_U32 u32MemShift_IPM;

                if((pstXC_DS_CmdCnt->u16CMDCNT_IPM % 2) == 0)
                {
                    u32MemShift_IPM = (pstXC_DS_CmdCnt->u16CMDCNT_IPM / 2) * MS_MLOAD_MEM_BASE_UNIT;
                }
                else
                {
                    u32MemShift_IPM = (pstXC_DS_CmdCnt->u16CMDCNT_IPM / 2) * MS_MLOAD_MEM_BASE_UNIT  + DS_CMD_LEN_64BITS;
                }
                //XC_PRINTF("[%s,%5d] [DS_IP]pstXC_DS_CmdCnt->u16CMDCNT_IPM:%d u32MemShift_IPM:%lx \n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_IPM,(MS_U32)u32MemShift_IPM);
                //u32Addr = u32Addr + DS_CMD_LEN_64BITS * pstXC_DS_CmdCnt->u16CMDCNT_IPM;
                u32Addr = u32Addr + u32MemShift_IPM;
                pu64Data = (MS_U64*)MsOS_PA2KSEG1(u32Addr);//IPM

                if(pstXC_DS_CmdCnt->u16CMDCNT_IPM < u8MaxCmdCnt)
                {
                    *pu64Data = u64CmdTemp;
                    pstXC_DS_CmdCnt->u16CMDCNT_IPM++;
                }
                else
                {
                    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] IPM Command count overflow !!  u16CMDCNT_IPM:%d  Max command count: %d\n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_IPM,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);
                }
            }
            else//subwindow
            {
                u32Addr_IPS = u32Addr_IPS + DS_CMD_LEN_64BITS * pstXC_DS_CmdCnt->u16CMDCNT_IPS;
                pu64Data = (MS_U64*)MsOS_PA2KSEG1(u32Addr_IPS); // IPS

                if(pstXC_DS_CmdCnt->u16CMDCNT_IPS < u8MaxCmdCnt)
                {
                    *pu64Data = u64CmdTemp;
                    pstXC_DS_CmdCnt->u16CMDCNT_IPS++;
                }
                else
                {
                    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] IPS Command count overflow !!  u16CMDCNT_IPS:%d  Max command count: %d\n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_IPS,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);
                }
            }
        }
        else//DS_OP
        {
            if(eWindow == MAIN_WINDOW)
            {
                MS_U32 u32MemShift_OPM;

                if((pstXC_DS_CmdCnt->u16CMDCNT_OPM % 2) == 0)
                {
                    u32MemShift_OPM = (pstXC_DS_CmdCnt->u16CMDCNT_OPM / 2) * MS_MLOAD_MEM_BASE_UNIT;
                }
                else
                {
                    u32MemShift_OPM = (pstXC_DS_CmdCnt->u16CMDCNT_OPM / 2) * MS_MLOAD_MEM_BASE_UNIT  + DS_CMD_LEN_64BITS;
                }
                //XC_PRINTF("[%s,%5d] [DS_OP]pstXC_DS_CmdCnt->u16CMDCNT_OPM:%d u32MemShift_OPM:%lx \n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_OPM,(MS_U32)u32MemShift_OPM);
                //u32Addr_OPM = u32Addr_OPM + DS_CMD_LEN_64BITS * pstXC_DS_CmdCnt->u16CMDCNT_OPM;
                u32Addr_OPM = u32Addr_OPM + u32MemShift_OPM;
                pu64Data = (MS_U64*)MsOS_PA2KSEG1(u32Addr_OPM);//OPM

                //XC_PRINTF("[%s,%5d] u64CmdTemp:%llx  \n",__func__,__LINE__,u64CmdTemp);

                if(pstXC_DS_CmdCnt->u16CMDCNT_OPM < u8MaxCmdCnt)
                {
                    *pu64Data = u64CmdTemp;
                    pstXC_DS_CmdCnt->u16CMDCNT_OPM++;
                }
                else
                {
                    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] OPM Command count overflow !!  u16CMDCNT_OPM:%d  Max command count: %d\n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_OPM,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);
                }
            }
            else
            {
                u32Addr_OPS = u32Addr_OPS + DS_CMD_LEN_64BITS * pstXC_DS_CmdCnt->u16CMDCNT_OPS;
                pu64Data = (MS_U64*)MsOS_PA2KSEG1(u32Addr_OPS); // OPS

                if(pstXC_DS_CmdCnt->u16CMDCNT_OPS < u8MaxCmdCnt)
                {
                    *pu64Data = u64CmdTemp;
                    pstXC_DS_CmdCnt->u16CMDCNT_OPS++;
                }
                else
                {
                    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] OPS Command count overflow !!  u16CMDCNT_OPS:%d  Max command count: %d\n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_OPS,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);
                }
            }
        }
    }
    else if(Source_Select == DS_MVOP)// only in IP cmd
    {
        if(IPOP_Sel == DS_IP)
        {
            u16DataTemp = u16CmdRegValue;
            u8AddrTemp = (u32CmdRegAddr&0x000000FF);
            u16BankTemp = (u32CmdRegAddr&0x00FFFF00) >> 8; //EX: mvop mainwinodw: 0x1014 mvop bank
            u16MaskTemp = 0xFFFF;

            u64CmdTemp|= (MS_U64)u16DataTemp;
            u64CmdTemp|= ((MS_U64)u8AddrTemp<<16);
            u64CmdTemp|= ((MS_U64)u16BankTemp<<23);
            u64CmdTemp|= ((MS_U64)u16MaskTemp<<48);

            if(eWindow == MAIN_WINDOW)
            {
                MS_U32 u32MemShift_IPM;

                if((pstXC_DS_CmdCnt->u16CMDCNT_IPM % 2) == 0)
                {
                    u32MemShift_IPM = (pstXC_DS_CmdCnt->u16CMDCNT_IPM / 2) * MS_MLOAD_MEM_BASE_UNIT;
                }
                else
                {
                    u32MemShift_IPM = (pstXC_DS_CmdCnt->u16CMDCNT_IPM / 2) * MS_MLOAD_MEM_BASE_UNIT  + DS_CMD_LEN_64BITS;
                }
                //XC_PRINTF("[%s,%5d] [DS_IP(MVOP)]pstXC_DS_CmdCnt->u16CMDCNT_IPM:%d u32MemShift_IPM:%lx \n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_IPM,(MS_U32)u32MemShift_IPM);
                //u32Addr = u32Addr + DS_CMD_LEN_64BITS * pstXC_DS_CmdCnt->u16CMDCNT_IPM;
                u32Addr = u32Addr + u32MemShift_IPM;
                pu64Data = (MS_U64*)MsOS_PA2KSEG1(u32Addr);//IPM

                if(pstXC_DS_CmdCnt->u16CMDCNT_IPM < u8MaxCmdCnt)
                {
                    *pu64Data = u64CmdTemp;
                    pstXC_DS_CmdCnt->u16CMDCNT_IPM++;
                }
                else
                {
                    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] Command count overflow !!  u16CMDCNT_IPM:%d  Max command count: %d\n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_IPM,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);
                }
            }
            else
            {
                pu64Data = (MS_U64*)MsOS_PA2KSEG1(u32Addr_IPS);//IPS

                if(pstXC_DS_CmdCnt->u16CMDCNT_IPS < u8MaxCmdCnt)
                {
                    *pu64Data = u64CmdTemp;
                    pstXC_DS_CmdCnt->u16CMDCNT_IPS++;
                }
                else
                {
                    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] Command count overflow !!  u16CMDCNT_IPS:%d  Max command count: %d\n",__func__,__LINE__,pstXC_DS_CmdCnt->u16CMDCNT_IPS,pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth);
                }
            }
        }
        else
        {
            XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] MVOP is IP cmd not OP cmd !! \n",__func__,__LINE__);
        }

    }
    else if(Source_Select == DS_GOP)
    {

    }
    else
    {
        XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] Only can support XC/MVOP/GOP NOW !! \n",__func__,__LINE__);
    }

#else

//=============================================//
//  32bit command format
//  |-------------|-------------|-------------|
//  |     Bank    |     Addr    |     Data    |
//  |-------------|-------------|-------------|
//  |   [31:24]   |   [23:16]   |    [15:0]   |
//  |-------------|-------------|-------------|

//Bank: Subbank
//=============================================//

    if(IPOP_Sel == DS_OP)
    {
        MS_PHY u32OPAddr = u32Addr;
        MS_U32 *pu32Data = NULL;
        MS_U8 u8OPCount = pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth;
       // MS_U8 u8OPCount = IdxDepth;
        MS_PHY u32Command = 0;

        u32Command = u16CmdRegValue + ((u32CmdRegAddr & 0x00FF) << 15) + ((u32CmdRegAddr & 0xFF00) << 16);

        while(u8OPCount > 0)
        {
            pu32Data = (MS_U32*)MsOS_PA2KSEG1(u32OPAddr);
            if(0 == pu32Data)
            {
                printf("%s :pu32Data = 0!,error!!!\n", __FUNCTION__);

                assert(pu32Data != 0);
            }
            // Found null command
            if((MS_U32)(*pu32Data) == 0xFFFF0000)
            {
                break;
            }
            // Found duplicated command
            if((MS_U32)(*pu32Data) == u32Command)
            {
                //SC_DBG(printf("Command duplicated\n"));

                return;
            }
            u32OPAddr += MS_MLOAD_MEM_BASE_UNIT;
            u8OPCount--;
        }

        if((MS_U32)(*pu32Data) == 0xFFFF0000)
        {
            *pu32Data = u32Command;
        }
        else
        {
           printf("DS OP command buffer is full for this index %u!\n", pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow]);
        }
    //printf("@@[%s][%u]u16CmdRegAddr=%x, u16CmdRegValue=%x\n",__FUNCTION__, __LINE__, u16CmdRegAddr, u16CmdRegValue);
    }

    else
    {
        // (OP : IP : Unused : Unused) (4 byte : 4 byte : 4 byte : 4 byte) if MIU 128bit
        // (OPmain : IPmain : OPsub : IPsub) (4 byte : 4 byte : 4 byte : 4 byte) if MIU 128bit

        MS_PHY u32IPAddr = u32Addr + DS_OP_CMD_LEN;
        MS_U32 *pu32Data = NULL;
        MS_U8 u8IPCount = pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth;
        //MS_U8 u8IPCount = IdxDepth;
        MS_PHY u32Command = 0;

        u32Command = u16CmdRegValue + ((u32CmdRegAddr & 0x00FF) << 15) + ((u32CmdRegAddr & 0xFF00) << 16);

        while(u8IPCount > 0)
        {
            pu32Data = (MS_U32*)MsOS_PA2KSEG1(u32IPAddr);
            if(0 == pu32Data)
            {
                printf("%s :pu32Data = 0!,error!!!\n", __FUNCTION__);

                assert(pu32Data != 0);
            }
            // Found null command
            if((MS_U32)(*pu32Data) == 0xFFFF0000)
            {
                break;
            }
            // Found duplicated command
            if((MS_U32)(*pu32Data) == u32Command)
            {
                return;
            }
            u32IPAddr += MS_MLOAD_MEM_BASE_UNIT;
            u8IPCount--;
        }

        if((MS_U32)(*pu32Data) == 0xFFFF0000)
        {
            *pu32Data = u32Command;
        }
        else
        {
           printf("DS IP command buffer is full for this index %u!\n", pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow]);
        }
    //printf("@@[%s][%u]u16CmdRegAddr=%x, u16CmdRegValue=%x\n",__FUNCTION__, __LINE__, u16CmdRegAddr, u16CmdRegValue);
    }
#endif
#endif

}

void Hal_SC_Add_NullCommand(void *pInstance,SCALER_WIN eWindow,ds_reg_ip_op_sel IPOP_Sel,XC_DS_CMDCNT *pstXC_DS_CmdCnt)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

#if (SUPPORT_KERNEL_DS == 1)
#ifdef MSOS_TYPE_LINUX_KERNEL
        EN_KDRV_SC_DEVICE u32DeviceID;
        if(psXCInstPri->u32DeviceID == 0)
        {
            u32DeviceID = E_KDRV_XC_SC0;
        }
        else
        {
            u32DeviceID = E_KDRV_XC_SC1;
        }
        KApi_XC_Add_NullCommand(u32DeviceID,eWindow,E_DS_CLIENT_XC,IPOP_Sel,(K_XC_DS_CMDCNT *)pstXC_DS_CmdCnt);
        return;
#else
#if (defined MSOS_TYPE_LINUX) || (defined ANDROID)
        if(0 > _s32FdScaler)
        {
            _s32FdScaler = open("/dev/scaler", O_WRONLY | O_NDELAY);
        }

        if (0 > _s32FdScaler)
        {
            printf("\nUnable to open /dev/scaler\n");
            return ;
        }
        else
        {
            ST_KDRV_DS_Add_NullCommand k_ds_Add_NullCommand;
            if(psXCInstPri->u32DeviceID == 0)
                k_ds_Add_NullCommand.u32DeviceID = E_KDRV_XC_SC0;
            else
                k_ds_Add_NullCommand.u32DeviceID = E_KDRV_XC_SC1;
            k_ds_Add_NullCommand.eWindow = eWindow;
            k_ds_Add_NullCommand.client = E_DS_CLIENT_XC;
            k_ds_Add_NullCommand.IPOP_Sel = IPOP_Sel;
            k_ds_Add_NullCommand.pstXC_DS_CmdCnt = (K_XC_DS_CMDCNT *)pstXC_DS_CmdCnt;
            if (-1 == ioctl(_s32FdScaler, MDRV_XC_IOC_DS_ADD_NULL_CMD,&k_ds_Add_NullCommand))
            {
                perror("ioctl");
                return ;
            }

            return ;
        }
#endif
#endif
#else

    MS_U16 u16MaxCmdCnt = pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth * 2; // It has two 64bit commands per MIU bus width
    MS_U64 *pu64Data = NULL;
    MS_U16 i;

    if(eWindow == MAIN_WINDOW)
    {
        if(IPOP_Sel == DS_IP)
        {
            for(i=pstXC_DS_CmdCnt->u16CMDCNT_IPM;i<u16MaxCmdCnt;i++)
            {
                //Offset is u16MaxCmdCnt * 2 * one_ds_command_byte
                //because of depth * 2 = MaxCount, offset is depth * 4 (one depth can contain 4 ds commands (two of them are dummy command))
                MS_PHY u32IndexBase= (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr +
                    (MS_U32)pXCResourcePrivate->sthal_SC.u8DynamicScalingNextIndex[eWindow] * u16MaxCmdCnt * 2 * DS_CMD_LEN_64BITS +
                    (i / 2) * BYTE_PER_WORD + (i % 2) * DS_CMD_LEN_64BITS);
                pu64Data  = (MS_U64*)MsOS_PA2KSEG1(u32IndexBase);
                *pu64Data = 0x00000009FFFF0000;
            }
        }
        else
        {
            for(i=pstXC_DS_CmdCnt->u16CMDCNT_OPM;i<u16MaxCmdCnt;i++)
            {
                MS_PHY u32IndexBase= (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM +
                    (MS_U32)pXCResourcePrivate->sthal_SC.u8DynamicScalingNextIndex[eWindow] * u16MaxCmdCnt * 2 * DS_CMD_LEN_64BITS +
                    (i / 2) * BYTE_PER_WORD + (i % 2) * DS_CMD_LEN_64BITS);
                pu64Data  = (MS_U64*)MsOS_PA2KSEG1(u32IndexBase);
                *pu64Data = 0x00000009FFFF0000;
            }
        }
    }
    else
    {
        if(IPOP_Sel == DS_IP)
        {
            for(i=pstXC_DS_CmdCnt->u16CMDCNT_IPS;i<u16MaxCmdCnt;i++)
            {
                MS_PHY u32IndexBase= (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_IPS +
                    (MS_U32)pXCResourcePrivate->sthal_SC.u8DynamicScalingNextIndex[eWindow] * u16MaxCmdCnt * 2 * DS_CMD_LEN_64BITS +
                    (i / 2) * BYTE_PER_WORD + (i % 2) * DS_CMD_LEN_64BITS);
                pu64Data  = (MS_U64*)MsOS_PA2KSEG1(u32IndexBase);
                *pu64Data = 0x00000009FFFF0000;
            }
        }
        else
        {
            for(i=pstXC_DS_CmdCnt->u16CMDCNT_OPS;i<u16MaxCmdCnt;i++)
            {
                MS_PHY u32IndexBase= (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPS +
                    (MS_U32)pXCResourcePrivate->sthal_SC.u8DynamicScalingNextIndex[eWindow] * u16MaxCmdCnt * 2 * DS_CMD_LEN_64BITS +
                    (i / 2) * BYTE_PER_WORD + (i % 2) * DS_CMD_LEN_64BITS);
                pu64Data  = (MS_U64*)MsOS_PA2KSEG1(u32IndexBase);
                *pu64Data = 0x00000009FFFF0000;
            }
        }
    }
#endif

}

MS_BOOL MHAL_SC_Set_DynamicScaling(void *pInstance,MS_PHY u32MemBaseAddr, MS_U8 u8MIU_Select, MS_U8 u8IdxDepth, MS_BOOL bOP_On, MS_BOOL bIPS_On, MS_BOOL bIPM_On,SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    MS_U16 u16OnOff = 0;
    MS_U16 u16MIU_Sel_bit1 = 0;

    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u8MIU_Select:%d  \n",__func__,__LINE__,u8MIU_Select);
    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] bOP_On:%d  bIPS_On:%d bIPM_On:%d  \n",__func__,__LINE__,bOP_On,bIPS_On,bIPM_On);

    // disable DS before modifying DS configuration
    if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
    {
        _MLOAD_ENTRY(pInstance);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK1F_10_L, 0, 0x0E00);
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
        _MLOAD_RETURN(pInstance);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_10_L, 0, 0x0E00);
    }

    // enable/disable
    // we only memorize riu enable bit because mload and ds shares the same riu enable bit
    u16OnOff = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK1F_10_L) & 0x1000;

    u16OnOff |= ((bOP_On << 9) | (bIPS_On << 10) | (bIPM_On << 11));

#if ENABLE_DS_4_BASEADDR_MODE

//===============================================================//
//  old 32bit command in DRAM  (per 16 Byte)
//  |-------------|-------------|-------------|-------------|
//  | DS_OP(main) | DS_IP(main) |  DS_OP(sub) |  DS_IP(sub) |
//  |-------------|-------------|-------------|-------------|
//  |   4 byte    |   4 byte    |   4 byte    |   4 byte    |
//  |-------------|-------------|-------------|-------------|

//  new 64bit command in DRAM (per 16 Byte)
//  |---------------------------|---------------------------|
//  |        DS_IP(main)        |        DS_IP(main)        |
//  |---------------------------|---------------------------|
//  |          8 byte           |          8 byte           |
//  |---------------------------|---------------------------|

// For example: IPM command
// For new 64bit command, it has two DS command per 16 byte.
// Therefore,u8DynamicScalingIndexDepth is divided 2 in this case.
//===============================================================//
    pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth = u8IdxDepth / 2 / (MS_MLOAD_MEM_BASE_UNIT/MS_MLOAD_BUS_WIDTH);
    pXCResourcePrivate->sthal_SC.u32DynamicScalingBufSize = BYTE_PER_WORD * u8IdxDepth * DS_MAX_INDEX;
    //for FRC DS need enlarge DRAM size from 3K to 6K (After FW release CL#1342372)

    MS_U32 u32DSBufLen = pXCResourcePrivate->sthal_SC.u32DynamicScalingBufSize / 4;

    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32DynamicScalingBufSize:%d u32DSBufLen:%d  \n",__func__,__LINE__,pXCResourcePrivate->sthal_SC.u32DynamicScalingBufSize,u32DSBufLen);

    if(eWindow == MAIN_WINDOW)
    {
        pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr = u32MemBaseAddr; //IPM
        pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM = u32MemBaseAddr + u32DSBufLen*2;
        XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32DynamicScalingBaseAddr_IPM:%x  u32DynamicScalingBaseAddr_OPM:%x  \n",__func__,__LINE__,(int)pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr,(int)pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM);
    }

    if(eWindow == SUB_WINDOW)
    {
        pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_IPS = u32MemBaseAddr + u32DSBufLen;
        pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPS = u32MemBaseAddr + u32DSBufLen*3;
        XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32DynamicScalingBaseAddr_IPS:%x  u32DynamicScalingBaseAddr_OPS:%x  \n",__func__,__LINE__,(int)pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM,(int)pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPS);
    }
    Hal_XC_Enable_DS_4_Baseaddress_Mode(pInstance, TRUE);
#else
    pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr = u32MemBaseAddr;
    pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth = u8IdxDepth; //MaxDepth(IP/OP)
    pXCResourcePrivate->sthal_SC.u32DynamicScalingBufSize = BYTE_PER_WORD * u8IdxDepth * DS_MAX_INDEX;
#endif

    XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u32DynamicScalingBaseAddr:%x  u8DynamicScalingIndexDepth:%d u32DynamicScalingBufSize:%d   \n",__func__,__LINE__,(int)pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr,(int)pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth,pXCResourcePrivate->sthal_SC.u32DynamicScalingBufSize);

    //Befor DS On, Clean the DS memory
    if(u16OnOff & 0x0E00)
    {
        if( (pXCResourcePrivate->stdrvXC_3D.ePreInputMode == E_XC_3D_INPUT_MODE_NONE) && (pXCResourcePrivate->stdrvXC_3D.ePreOutputMode == E_XC_3D_OUTPUT_MODE_NONE)
        && (pXCResourcePrivate->stdrvXC_3D._eInput3DMode[MAIN_WINDOW] == E_XC_3D_INPUT_MODE_NONE) && (pXCResourcePrivate->stdrvXC_3D._eOutput3DMode == E_XC_3D_OUTPUT_MODE_NONE) ) //mantis:0740226
        {
            XC_LOG_TRACE(XC_DBGLEVEL_SETWINDOW,"[%s,%5d] [DS] u8IdxDepth:%d DS_MAX_INDEX:%d BYTE_PER_WORD:%d  \n",__func__,__LINE__,u8IdxDepth,DS_MAX_INDEX,BYTE_PER_WORD);

            pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex[eWindow] = 0;
            pXCResourcePrivate->sthal_SC.u8DynamicScalingNextIndex[eWindow] = 0;
            pXCResourcePrivate->sthal_SC.u8DynamicScalingCurrentIndex_Ring[eWindow] = 0;

#if ENABLE_DS_4_BASEADDR_MODE
            Hal_SC_ResetSWDSCommand(pInstance,eWindow,0);
#else
            MS_U8 u8index = 0;

            for(u8index=0; u8index < DS_MAX_INDEX; u8index++)
            {
                Hal_SC_ResetSWDSCommand(pInstance,eWindow, u8index);
            }
#endif
        }
    }

    if(u16OnOff & 0x0E00)
    {
        // ENABLE DS
        u16OnOff |= BIT(12);     // enable write register through RIU
        pXCResourcePrivate->sthal_SC.bDynamicScalingEnable[eWindow] = TRUE;

        // currently, these 3 will use same MIU
        u16OnOff |= ((u8MIU_Select & 0x01) << 13);                       // MIU select of OP
        u16OnOff |= ((u8MIU_Select & 0x01) << 14);                       // MIU select of IPS
        u16OnOff |= ((u8MIU_Select & 0x01) << 15);                       // MIU select of IPM

        u16MIU_Sel_bit1 |= ((u8MIU_Select & 0x02) << 12);                // MIU select of OP
        u16MIU_Sel_bit1 |= ((u8MIU_Select & 0x02) << 13);                // MIU select of IPS
        u16MIU_Sel_bit1 |= ((u8MIU_Select & 0x02) << 14);                // MIU select of IPM

        // patch IP1F2_21[15:14] r/w bank

        //if(pXCResourcePrivate->sthal_SC.sbOldValueReaded == FALSE)
        //{
        //	pXCResourcePrivate->sthal_SC.su16OldValue = SC_R2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_21_L);
        //	pXCResourcePrivate->sthal_SC.sbOldValueReaded = TRUE;
        //}
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK01_21_L, 0x4000, 0xC000);

        Hal_XC_MLoad_set_opm_lock(pInstance, OPM_LOCK_DS);

        // ENABLE DS Read/Write Handshaking
        SC_W2BYTEMSK(0, REG_SC_BK23_5F_L, 0x03, 0x03);
    }
    else
    {
        pXCResourcePrivate->sthal_SC.bDynamicScalingEnable[eWindow] = FALSE;
        // DISABLE DS
        //if(pXCResourcePrivate->sthal_SC.sbOldValueReaded)
        //{
        //    SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK01_21_L, pXCResourcePrivate->sthal_SC.su16OldValue);
        //    pXCResourcePrivate->sthal_SC.sbOldValueReaded = FALSE;
        //}
        Hal_XC_MLoad_set_opm_lock(pInstance, OPM_LOCK_INIT_STATE);
        // DISABLE DS Read/Write Handshaking
        SC_W2BYTEMSK(0, REG_SC_BK23_5F_L, 0x00, 0x03);
    }

    // if disabled, need to set dynamic scaling ratio to 1:1
    if(!bOP_On)
    {
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_1C_L, 0x00100000);
        SC_W4BYTE(psXCInstPri->u32DeviceID, REG_SC_BK23_1E_L, 0x00100000);
    }

    if(u16OnOff & 0x0E00)
    {
        //for now, we do not need to change trigger point setting
        Hal_XC_Set_DS_BaseAddress(pInstance,u32MemBaseAddr);
        Hal_XC_Set_DS_IndexDepth(pInstance);
        Hal_XC_Set_DS_MIU_Sel(pInstance,u16OnOff,u16MIU_Sel_bit1);

        // set DMA threthold, length, fixed value, no need to change
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_10_L, 0x88, 0x00FF);

        // store
        Hal_XC_MLoad_get_trig_p(pInstance, &pXCResourcePrivate->sthal_SC.u16OldValue[E_STORE_VALUE_AUTO_TUNE_AREA_TRIG], &pXCResourcePrivate->sthal_SC.u16OldValue[E_STORE_VALUE_DISP_AREA_TRIG]);
        pXCResourcePrivate->sthal_SC.bTrig_pStored = TRUE;

        // set the trigger point from delayed line,  DS: 0x08, Train:0x14, Disp:0x18
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_21_L, 0x08, 0xFF);  // ds_trig_dly
        //Hal_XC_MLoad_set_trig_p(pInstance, 0x14, 0x18);
        //Hal_XC_MLoad_set_trig_p(pInstance, 0x0A, 0x18);

        //add
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK10_5D_L, 0x0828, 0xFFFF);

        // set trigger source to trigger
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_19_L, 0x08B8, 0x08BC);

        //set the delay line cnt to vfde end
        //SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK20_19_L, BIT(6), BIT(6)|BIT(0));

#if ENABLE_64BITS_COMMAND
        Hal_XC_Enable_DS_64Bits_Command(pInstance,TRUE);
        if(ENABLE_64BITS_SPREAD_MODE)
        {
            Hal_XC_Enable_DS_64Bits_Sread_Mode(pInstance,TRUE);
        }
        Hal_XC_Set_DS_64Bits_MIU_Bus_Sel(pInstance);
#endif
    }

    // set DS in IPS[10],ipm[11] On/Off
    if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
    {
        _MLOAD_ENTRY(pInstance);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK1F_10_L, u16OnOff & 0x1D00, 0x1D00);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK1F_17_L, (bIPM_On)? 0x400 : 0x0, 0x400);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK1F_17_L, 0x10, 0x10);
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
        _MLOAD_RETURN(pInstance);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_10_L, u16OnOff & 0x1D00, 0x1D00);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_17_L, (bIPM_On)? 0x400 : 0x0, 0x400);
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_17_L, 0x10, 0x10);
    }

    // set DS in OP[9] On/Off
    if (MDrv_XC_MLoad_GetStatus(pInstance) == E_MLOAD_ENABLED)
    {
        _MLOAD_ENTRY(pInstance);
        MDrv_XC_MLoad_WriteCmd(pInstance, REG_SC_BK1F_10_L, u16OnOff & 0x0200, 0x0200);
        MDrv_XC_MLoad_Fire(pInstance, TRUE);
        _MLOAD_RETURN(pInstance);
    }
    else
    {
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_10_L, u16OnOff & 0x0200, 0x0200);
    }
    // set mload timing
    if(u16OnOff & 0x0E00)
    {
        SC_W2BYTE(0, REG_SC_BK20_19_L, 0x33F8);
    }
    else
    {
        SC_W2BYTE(0, REG_SC_BK20_19_L, 0x30F8);
    }

    return TRUE;
}

void MHAL_SC_Set_DynamicScalingFlag(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    pXCResourcePrivate->sthal_SC.bDynamicScalingEnable[MAIN_WINDOW] = bEnable;
}

MS_BOOL MHAL_SC_Get_DynamicScaling_Status(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));
    return pXCResourcePrivate->sthal_SC.bDynamicScalingEnable[MAIN_WINDOW];
}

MS_BOOL MHAL_SC_Enable_IPMTuneAfterDS(void *pInstance, MS_BOOL bEnable)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    // ENABLE IPM TUNE AFTER DS
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK12_06_L, BIT(7), BIT(7));

    // Clear DS active pulse every vsync
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_17_L, BIT(6), BIT(6));

    //
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_17_L, BIT(14), BIT(14));
    return TRUE;
}

void MHal_SC_DynamicScaling_SWReset(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, 0x400, 0x400);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, 0x800, 0x800);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, 0x1000, 0x1000);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, 0x0, 0x1000);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, 0x0, 0x800);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, 0x0, 0x400);
}

MS_BOOL MHal_XC_Get_DSForceIndexSupported(void *pInstance, SCALER_WIN eWindow)
{
    if (eWindow >= MAX_WINDOW)
    {
        printf("[%s,%5d] maximum window exceeded",__FUNCTION__,__LINE__);
        return FALSE;
    }

    return TRUE;
}

void MHal_XC_Set_DSForceIndex(void *pInstance, MS_BOOL bEnable, MS_U8 u8Index, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
#if (SUPPORT_KERNEL_DS == 1)
#ifdef MSOS_TYPE_LINUX_KERNEL
        EN_KDRV_SC_DEVICE u32DeviceID;
        if(psXCInstPri->u32DeviceID == 0)
        {
            u32DeviceID = E_KDRV_XC_SC0;
        }
        else
        {
            u32DeviceID = E_KDRV_XC_SC1;
        }
        KApi_XC_Set_DSForceIndex(u32DeviceID,bEnable,u8Index,eWindow);
        return;
#else
#if (defined MSOS_TYPE_LINUX) || (defined ANDROID)
        if(0 > _s32FdScaler)
        {
            _s32FdScaler = open("/dev/scaler", O_WRONLY | O_NDELAY);
        }

        if (0 > _s32FdScaler)
        {
            printf("\nUnable to open /dev/scaler\n");
            return ;
        }
        else
        {
            ST_KDRV_DS_SET_DSForceIndex k_ds_set_ForceIndex;
            if(psXCInstPri->u32DeviceID == 0)
                k_ds_set_ForceIndex.u32DeviceID = E_KDRV_XC_SC0;
            else
                k_ds_set_ForceIndex.u32DeviceID = E_KDRV_XC_SC1;
            k_ds_set_ForceIndex.bEnable = bEnable;
            k_ds_set_ForceIndex.u8Index = u8Index;
            k_ds_set_ForceIndex.eWindow = eWindow;
            if (-1 == ioctl(_s32FdScaler, MDRV_XC_IOC_DS_SET_DSFORCE_INDEX,&k_ds_set_ForceIndex))
            {
                perror("ioctl");
                return ;
            }

            return ;
        }
#endif
#endif
#else

    if (eWindow >= MAX_WINDOW)
    {
        printf("[%s,%5d] maximum window exceeded",__FUNCTION__,__LINE__);
        return;
    }

    if (eWindow == MAIN_WINDOW)
    {
        // reg_idxg_force_en
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_77_L, bEnable?BIT(0):0 , BIT(0));
        // reg_idxg_force_en
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_77_L, bEnable?BIT(2):0 , BIT(2));
        // reg_idxg_force_idx_f2
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_76_L, (MS_U16)u8Index << 8 , 0xFF00);
    }
    else // eWindow == SUB_WINDOW
    {
        // reg_idxg_force_en
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_77_L, bEnable?BIT(8):0 , BIT(8));

        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_77_L, bEnable?BIT(10):0 , BIT(10));
        // reg_idxg_force_idx_f1
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_75_L, (MS_U16)u8Index << 8 , 0xFF00);
    }
#endif
}

void MHal_XC_Set_DSIndexSourceSelect(void *pInstance, E_XC_DS_INDEX_SOURCE eDSIdxSrc, SCALER_WIN eWindow)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    if (eWindow >= MAX_WINDOW)
    {
        printf("[%s,%5d] maximum window exceeded",__FUNCTION__,__LINE__);
        return;
    }

    if (eDSIdxSrc >= E_XC_DS_INDEX_MAX)
    {
        printf("[%s,%5d] Maximum index exceeded, the index is (%d)\n",__FUNCTION__,__LINE__,eDSIdxSrc);
        return;
    }

    if(eWindow == MAIN_WINDOW)
    {
        // reg_idxg_en_f2
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_77_L, eDSIdxSrc, BIT(0));
    }
    else
    {
        // reg_idxg_en_f1
        SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_77_L, eDSIdxSrc << 8, BIT(8));
    }
}

void Hal_XC_Enable_DS_64Bits_Command(void *pInstance,MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID,REG_SC_BK1F_70_L, bEn?BIT(0):0x00, BIT(0));
}

void Hal_XC_Enable_DS_64Bits_Sread_Mode(void *pInstance,MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID,REG_SC_BK1F_70_L, bEn?BIT(15):0x00, BIT(15));
}

void Hal_XC_Enable_DS_4_Baseaddress_Mode(void *pInstance,MS_BOOL bEn)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID,REG_SC_BK1F_17_L, bEn?BIT(7):0x00, BIT(7));
}

void Hal_XC_Set_DS_64Bits_MIU_Bus_Sel(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    MS_U16 u16sel = 0x00;

    if( MS_MLOAD_BUS_WIDTH == 8 )
    {
        u16sel = 0x00;
    }
    else if( MS_MLOAD_BUS_WIDTH == 16 )
    {
        u16sel = 0x01;
    }
    else if( MS_MLOAD_BUS_WIDTH == 32 )
    {
        u16sel = 0x3;
    }
    else
    {
        printf("MIU Bus not support !!!!!!!!!!!!!!!!!\n");
        u16sel = 0x00;
    }

    u16sel = (u16sel & 0x0003)<<14;
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID,REG_SC_BK1F_13_L, u16sel, 0xC000);
}

void Hal_XC_Set_DS_BaseAddress(void *pInstance,MS_PHY u32Base)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    if( u32Base > HAL_MIU1_BASE)
    {
        u32Base = u32Base - HAL_MIU1_BASE;
    }
    u32Base = u32Base/MS_MLOAD_MEM_BASE_UNIT;

    #if ENABLE_DS_4_BASEADDR_MODE
            // set IPM
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK1F_11_L, u32Base & 0xFFFF);
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_12_L, (u32Base >> 16),0x03FF);

            //set OPM
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK1F_0E_L, (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM / MS_MLOAD_MEM_BASE_UNIT) & 0xFFFF);
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_0F_L, ((pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPM / MS_MLOAD_MEM_BASE_UNIT) >> 16),0x03FF);

            //set IPS
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK1F_0C_L, (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_IPS / MS_MLOAD_MEM_BASE_UNIT) & 0xFFFF);
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_0D_L, ((pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_IPS / MS_MLOAD_MEM_BASE_UNIT) >> 16),0x03FF);

            //set OPS
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK1F_60_L, (pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPS / MS_MLOAD_MEM_BASE_UNIT) & 0xFFFF);
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_61_L, ((pXCResourcePrivate->sthal_SC.u32DynamicScalingBaseAddr_OPS / MS_MLOAD_MEM_BASE_UNIT) >> 16),0x03FF);
    #else
            // set DS base address
            SC_W2BYTE(psXCInstPri->u32DeviceID, REG_SC_BK1F_11_L, u32Base & 0xFFFF);
            SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_12_L, (u32Base >> 16),0x03FF);
    #endif

}

void Hal_XC_Set_DS_IndexDepth(void *pInstance)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);
    XC_RESOURCE_PRIVATE* pXCResourcePrivate = NULL;
    UtopiaResourceGetPrivate(g_pXCResource[_XC_SELECT_INTERNAL_VARIABLE(psXCInstPri->u32DeviceID)],(void**)(&pXCResourcePrivate));

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_13_L, pXCResourcePrivate->sthal_SC.u8DynamicScalingIndexDepth , 0x00FF);
}

void Hal_XC_Set_DS_MIU_Sel(void *pInstance,MS_U16 u16DSOnOff,MS_U16 u16DS_MIU_Sel_bit1)
{
    XC_INSTANCE_PRIVATE *psXCInstPri = NULL;
    UtopiaInstanceGetPrivate(pInstance, (void**)&psXCInstPri);

    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_10_L, u16DSOnOff & 0xE000, 0xE000);
    SC_W2BYTEMSK(psXCInstPri->u32DeviceID, REG_SC_BK1F_71_L, u16DS_MIU_Sel_bit1 & 0xE000, 0xE000);
}

#endif // MHAL_DYNAMICSCALING_C
