/***************************************************************************************************************
 *
 * FileName hal_sd_base.h
 *     @author jeremy.wang (2017/09/14)
 * Desc:
 *     This header file is independent.
 *     We could put different hal_card_base.h in different build code folder but the same name.
 *     We want to distinguish between this and others settings but the same project.
 *     Specific define is freedom for each project, but we need to put it at inner code of project define.
 *
 *     For Base Setting:
 *     (1) BASE OS/CPU/FPGA define              <=====
 *     (2) BASE OS/CPU include files
 *     (3) BASE Debug System (OS)
 *     (4) BASE Project Type Define             <=====
 *     (5) BASE Project/FCIE_Ver Define         <=====
 *
 *     P.S. D_XX for define and D_XX__ two under line("__") to distinguish define and its define option.
 *
 ***************************************************************************************************************/

#ifndef __HAL_SD_BASE_H
#define __HAL_SD_BASE_H

#include "hal_sd_base_ref.h"   //put other define to refference file for more clear view.

//***********************************************************************************************************
// (1) BASE OS/CPU/FPGA Define
//***********************************************************************************************************
#define D_OS                D_OS__LINUX
#define D_CPU               D_CPU__ARM
#define EN_FPGA_TEST        (FALSE)
#define EN_CHIP_TEST        (TRUE)


//***********************************************************************************************************
// (2) BASE OS/CPU include files
//***********************************************************************************************************

//###########################################################################################################
#if (D_OS == D_OS__LINUX)
//###########################################################################################################
#include <linux/kernel.h>
//###########################################################################################################
#elif (D_OS == D_OS__UBOOT)
//###########################################################################################################
#include <common.h>
//###########################################################################################################
#elif (D_OS == D_OS__RTK)
//###########################################################################################################
#include "sys_sys_isw_uart.h"
//###########################################################################################################
#elif (D_OS == D_OS__ROM)
//###########################################################################################################
#include <drvUART.h>
//###########################################################################################################
#elif (D_OS == D_OS__YBOX)
//###########################################################################################################
#include <MsCommon.h>
//###########################################################################################################
#endif
//###########################################################################################################


//***********************************************************************************************************
// (3) BASE Debug System (OS)
//***********************************************************************************************************

//###########################################################################################################
#if (D_OS == D_OS__LINUX)
//###########################################################################################################
#define prtstring(s)    pr_cont(s)               //printk(s)
#define prtUInt(v)      pr_cont("%u", v)         //printk("%u", v)
#define prtU8(v)        pr_cont("%u", v)         //printk("%u", v)
#define prtU8Hex(v)     pr_cont("0x%02X", v)     //printk("0x%02X", v)
#define prtU16Hex(v)    pr_cont("0x%04X", v)     //printk("0x%04X", v)
#define prtU32Hex(v)    pr_cont("0x%08X", v)     //printk("0x%08X", v)
//###########################################################################################################
#elif (D_OS == D_OS__UBOOT) || (D_OS == D_OS__MBOOT)
//###########################################################################################################
#define prtstring(s)    printf(s)
#define prtUInt(v)      printf("%u", v)
#define prtU8(v)        printf("%u", v)
#define prtU8Hex(v)     printf("0x%02X", v)
#define prtU16Hex(v)    printf("0x%04X", v)
#define prtU32Hex(v)    printf("0x%08X", v)
//###########################################################################################################
#elif (D_OS == D_OS__RTK)
//###########################################################################################################
#define prtstring(s)    UartSendTrace(s)
#define prtCH(c)        UartSendTrace("%c", c)
#define prtUInt(v)      UartSendTrace("%u", v)
#define prtU8(v)        UartSendTrace("%u", v)
#define prtU16(v)       UartSendTrace("%u", v)
#define prtU8Hex(v)     UartSendTrace("0x%02X", v)
#define prtU16Hex(v)    UartSendTrace("0x%04X", v)
#define prtU32Hex(v)    UartSendTrace("0x%08X", v)
//###########################################################################################################
#elif (D_OS == D_OS__ROM)
//###########################################################################################################
#define prtstring(s)    uart_write_string((unsigned char*)s)
#define prtCH(c)        uart_write_byte(c)
#define prtUInt(v)      { prtstring("0x");  uart_write_U32_hex(v); }
#define prtU8(v)        { prtstring("0x");  uart_write_U8_hex(v); }
#define prtU16(v)       { prtstring("0x");  uart_write_U16_hex(v); }
#define prtU8Hex(v)     { prtstring("0x");  uart_write_U8_hex(v); }
#define prtU16Hex(v)    { prtstring("0x");  uart_write_U16_hex(v); }
#define prtU32Hex(v)    { prtstring("0x");  uart_write_U32_hex(v); }
//###########################################################################################################
#elif (D_OS == D_OS__YBOX)
//###########################################################################################################
#define prtstring(s)    printf(s)
#define prtCH(c)        printf("%c", c)
#define prtUInt(v)      printf("%u", v)
#define prtU8(v)        printf("%u", v)
#define prtU16(v)       printf("%u", v)
#define prtU8Hex(v)     printf("0x%02X", v)
#define prtU16Hex(v)    printf("0x%04X", v)
#define prtU32Hex(v)    printf("0x%08X", v)
//###########################################################################################################
#else
//###########################################################################################################
#define prtstring(s)    printf(s)
#define prtUInt(v)      printf("%u", v)
#define prtU8(v)        printf("0x%02X", v)
#define prtU8Hex(v)     printf("0x%02X", v)
#define prtU16Hex(v)    printf("0x%04X", v)
#define prtU32Hex(v)    printf("0x%08X", v)
//###########################################################################################################
#endif
//###########################################################################################################


//***********************************************************************************************************
// (4) BASE Project Type Define
//***********************************************************************************************************

#define D_PROJECT__iNF    1    //iNfinity Project
#define D_PROJECT__iNF3   2    //iNfinity3 Project
#define D_PROJECT__MV5    3    //Mercury5 Project
#define D_PROJECT__C4P    4    //Cleveland Project
#define D_PROJECT__iNF2   5    //iNfinity2 Project
#define D_PROJECT__C3    99
#define D_PROJECT__C4    98


//***********************************************************************************************************
// (5) BASE Project/FCIE_Ver Define
//***********************************************************************************************************

//###########################################################################################################
#if defined(CONFIG_ARCH_INFINITY2)
//###########################################################################################################
#define D_PROJECT           D_PROJECT__iNF2
#define D_FCIE_M_VER        D_FCIE_M_VER__05
//###########################################################################################################
#elif defined(CONFIG_ARCH_CLEVELAND)
//###########################################################################################################
#define D_PROJECT           D_PROJECT__C4P
#define D_FCIE_M_VER        D_FCIE_M_VER__05
//###########################################################################################################
#elif defined(CONFIG_ARCH_MV5)
//###########################################################################################################
#define D_PROJECT           D_PROJECT__MV5
#define D_FCIE_M_VER        D_FCIE_M_VER__05
//###########################################################################################################
#elif defined(CONFIG_ARCH_INFINITY)
//###########################################################################################################
#define D_PROJECT           D_PROJECT__iNF
#define D_FCIE_M_VER        D_FCIE_M_VER__05
//###########################################################################################################
#elif defined(CONFIG_ARCH_INFINITY3)
//###########################################################################################################
#define D_PROJECT           D_PROJECT__iNF3
#define D_FCIE_M_VER        D_FCIE_M_VER__05
//###########################################################################################################
#endif


#endif //End of __HAL_SD_BASE_H