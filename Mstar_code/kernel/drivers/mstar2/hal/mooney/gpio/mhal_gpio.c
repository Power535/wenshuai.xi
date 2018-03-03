///////////////////////////////////////////////////////////////////////////////////////////////////
//
// * Copyright (c) 2006 - 2007 MStar Semiconductor, Inc.
// This program is free software.
// You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
///////////////////////////////////////////////////////////////////////////////////////////////////

//-------------------------------------------------------------------------------------------------
//  Include Files
//-------------------------------------------------------------------------------------------------
//#include "MsCommon.h"
#include <linux/autoconf.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/delay.h>
#include <linux/kdev_t.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/ioport.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/poll.h>
#include <linux/wait.h>
#include <linux/cdev.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <asm/io.h>

#include "mhal_gpio.h"
#include "mhal_gpio_reg.h"

//-------------------------------------------------------------------------------------------------
//  Local Defines
//-------------------------------------------------------------------------------------------------

#define _CONCAT( a, b )     a##b
#define CONCAT( a, b )      _CONCAT( a, b )

/*
#define BIT0    BIT(0)
#define BIT1    BIT(1)
#define BIT2    BIT(2)
#define BIT3    BIT(3)
#define BIT4    BIT(4)
#define BIT5    BIT(5)
#define BIT6    BIT(6)
#define BIT7    BIT(7)
*/

// Dummy
#define GPIO999_OEN     0, 0
#define GPIO999_OUT     0, 0
#define GPIO999_IN      0, 0

#define GPIO1_PAD PAD_IRIN
#define GPIO1_OEN 0x0f26, BIT0
#define GPIO1_OUT 0x0f26, BIT1
#define GPIO1_IN  0x0f26, BIT2

#define GPIO2_PAD PAD_CEC0
#define GPIO2_OEN 0x0f2a, BIT0
#define GPIO2_OUT 0x0f2a, BIT1
#define GPIO2_IN  0x0f2a, BIT2

#define GPIO3_PAD PAD_PWM_PM
#define GPIO3_OEN 0x0f28, BIT0
#define GPIO3_OUT 0x0f28, BIT1
#define GPIO3_IN  0x0f28, BIT2

#define GPIO4_PAD PAD_DDCA_CK
#define GPIO4_OEN 0x0494, BIT1
#define GPIO4_OUT 0x0494, BIT2
#define GPIO4_IN  0x0494, BIT0

#define GPIO5_PAD PAD_DDCA_DA
#define GPIO5_OEN 0x0494, BIT5
#define GPIO5_OUT 0x0494, BIT6
#define GPIO5_IN  0x0494, BIT4

#define GPIO6_PAD PAD_GPIO_PM0
#define GPIO6_OEN 0x0f00, BIT0
#define GPIO6_OUT 0x0f00, BIT1
#define GPIO6_IN  0x0f00, BIT2

#define GPIO7_PAD PAD_GPIO_PM1
#define GPIO7_OEN 0x0f02, BIT0
#define GPIO7_OUT 0x0f02, BIT1
#define GPIO7_IN  0x0f02, BIT2

#define GPIO8_PAD PAD_GPIO_PM2
#define GPIO8_OEN 0x0f04, BIT0
#define GPIO8_OUT 0x0f04, BIT1
#define GPIO8_IN  0x0f04, BIT2

#define GPIO9_PAD PAD_GPIO_PM3
#define GPIO9_OEN 0x0f06, BIT0
#define GPIO9_OUT 0x0f06, BIT1
#define GPIO9_IN  0x0f06, BIT2

#define GPIO10_PAD PAD_GPIO_PM4
#define GPIO10_OEN 0x0f08, BIT0
#define GPIO10_OUT 0x0f08, BIT1
#define GPIO10_IN  0x0f08, BIT2

#define GPIO11_PAD PAD_GPIO_PM5
#define GPIO11_OEN 0x0f0a, BIT0
#define GPIO11_OUT 0x0f0a, BIT1
#define GPIO11_IN  0x0f0a, BIT2

#define GPIO12_PAD PAD_GPIO_PM6
#define GPIO12_OEN 0x0f0c, BIT0
#define GPIO12_OUT 0x0f0c, BIT1
#define GPIO12_IN  0x0f0c, BIT2

#define GPIO13_PAD PAD_GPIO_PM7
#define GPIO13_OEN 0x0f0e, BIT0
#define GPIO13_OUT 0x0f0e, BIT1
#define GPIO13_IN  0x0f0e, BIT2

#define GPIO14_PAD PAD_GPIO_PM8
#define GPIO14_OEN 0x0f10, BIT0
#define GPIO14_OUT 0x0f10, BIT1
#define GPIO14_IN  0x0f10, BIT2

#define GPIO15_PAD PAD_GPIO_PM9
#define GPIO15_OEN 0x0f12, BIT0
#define GPIO15_OUT 0x0f12, BIT1
#define GPIO15_IN  0x0f12, BIT2

#define GPIO16_PAD PAD_GPIO_PM10
#define GPIO16_OEN 0x0f14, BIT0
#define GPIO16_OUT 0x0f14, BIT1
#define GPIO16_IN  0x0f14, BIT2

#define GPIO17_PAD PAD_LED0
#define GPIO17_OEN 0x2e80, BIT1
#define GPIO17_OUT 0x2e80, BIT0
#define GPIO17_IN  0x2e80, BIT2

#define GPIO18_PAD PAD_LED1
#define GPIO18_OEN 0x2e81, BIT1
#define GPIO18_OUT 0x2e81, BIT0
#define GPIO18_IN  0x2e81, BIT2

#define GPIO19_PAD PAD_HOTPLUGA
#define GPIO19_OEN 0x0e4e, BIT0
#define GPIO19_OUT 0x0e4e, BIT4
#define GPIO19_IN  0x0e4f, BIT0

#define GPIO20_PAD PAD_HOTPLUGB
#define GPIO20_OEN 0x0e4e, BIT1
#define GPIO20_OUT 0x0e4e, BIT5
#define GPIO20_IN  0x0e4f, BIT1

#define GPIO21_PAD PAD_HOTPLUGA_HDMI20_5V
#define GPIO21_OEN 0x010218, BIT5
#define GPIO21_OUT 0x010218, BIT4
#define GPIO21_IN  0x010218, BIT6

#define GPIO22_PAD PAD_HOTPLUGB_HDMI20_5V
#define GPIO22_OEN 0x010318, BIT5
#define GPIO22_OUT 0x010318, BIT4
#define GPIO22_IN  0x010318, BIT6

#define GPIO23_PAD PAD_HOTPLUGC_HDMI20_5V
#define GPIO23_OEN 0x010418, BIT5
#define GPIO23_OUT 0x010418, BIT4
#define GPIO23_IN  0x010418, BIT6

#define GPIO24_PAD PAD_DDCDA_CK
#define GPIO24_OEN 0x0496, BIT1
#define GPIO24_OUT 0x0496, BIT2
#define GPIO24_IN  0x0496, BIT0

#define GPIO25_PAD PAD_DDCDA_DA
#define GPIO25_OEN 0x0496, BIT5
#define GPIO25_OUT 0x0496, BIT6
#define GPIO25_IN  0x0496, BIT4

#define GPIO26_PAD PAD_DDCDB_CK
#define GPIO26_OEN 0x0497, BIT1
#define GPIO26_OUT 0x0497, BIT2
#define GPIO26_IN  0x0497, BIT0

#define GPIO27_PAD PAD_DDCDB_DA
#define GPIO27_OEN 0x0497, BIT5
#define GPIO27_OUT 0x0497, BIT6
#define GPIO27_IN  0x0497, BIT4

#define GPIO28_PAD PAD_DDCDC_CK
#define GPIO28_OEN 0x0498, BIT1
#define GPIO28_OUT 0x0498, BIT2
#define GPIO28_IN  0x0498, BIT0

#define GPIO29_PAD PAD_DDCDC_DA
#define GPIO29_OEN 0x0498, BIT5
#define GPIO29_OUT 0x0498, BIT6
#define GPIO29_IN  0x0498, BIT4

#define GPIO30_PAD PAD_SAR0
#define GPIO30_OEN 0x1423, BIT0
#define GPIO30_OUT 0x1424, BIT0
#define GPIO30_IN  0x1425, BIT0

#define GPIO31_PAD PAD_SAR1
#define GPIO31_OEN 0x1423, BIT1
#define GPIO31_OUT 0x1424, BIT1
#define GPIO31_IN  0x1425, BIT1

#define GPIO32_PAD PAD_SAR2
#define GPIO32_OEN 0x1423, BIT2
#define GPIO32_OUT 0x1424, BIT2
#define GPIO32_IN  0x1425, BIT2

#define GPIO33_PAD PAD_SAR3
#define GPIO33_OEN 0x1423, BIT3
#define GPIO33_OUT 0x1424, BIT3
#define GPIO33_IN  0x1425, BIT3

#define GPIO34_PAD PAD_SAR4
#define GPIO34_OEN 0x1423, BIT4
#define GPIO34_OUT 0x1424, BIT4
#define GPIO34_IN  0x1425, BIT4

#define GPIO35_PAD PAD_SAR5
#define GPIO35_OEN 0x1423, BIT5
#define GPIO35_OUT 0x1424, BIT5
#define GPIO35_IN  0x1425, BIT5

#define GPIO36_PAD PAD_ARC0
#define GPIO36_OEN 0x110320, BIT1
#define GPIO36_OUT 0x110320, BIT0
#define GPIO36_IN  0x110320, BIT2

#define GPIO37_PAD PAD_DDCR_DA
#define GPIO37_OEN 0x102b86, BIT1
#define GPIO37_OUT 0x102b86, BIT0
#define GPIO37_IN  0x102b86, BIT2

#define GPIO38_PAD PAD_DDCR_CK
#define GPIO38_OEN 0x102b87, BIT1
#define GPIO38_OUT 0x102b87, BIT0
#define GPIO38_IN  0x102b87, BIT2

#define GPIO39_PAD PAD_GPIO0
#define GPIO39_OEN 0x102b00, BIT1
#define GPIO39_OUT 0x102b00, BIT0
#define GPIO39_IN  0x102b00, BIT2

#define GPIO40_PAD PAD_GPIO1
#define GPIO40_OEN 0x102b01, BIT1
#define GPIO40_OUT 0x102b01, BIT0
#define GPIO40_IN  0x102b01, BIT2

#define GPIO41_PAD PAD_SPDIF_OUT
#define GPIO41_OEN 0x102b36, BIT1
#define GPIO41_OUT 0x102b36, BIT0
#define GPIO41_IN  0x102b36, BIT2

#define GPIO42_PAD PAD_SPDIF_IN
#define GPIO42_OEN 0x102b37, BIT1
#define GPIO42_OUT 0x102b37, BIT0
#define GPIO42_IN  0x102b37, BIT2

#define GPIO43_PAD PAD_I2S_OUT_SD
#define GPIO43_OEN 0x102b38, BIT1
#define GPIO43_OUT 0x102b38, BIT0
#define GPIO43_IN  0x102b38, BIT2

#define GPIO44_PAD PAD_I2S_OUT_MCK
#define GPIO44_OEN 0x102b39, BIT1
#define GPIO44_OUT 0x102b39, BIT0
#define GPIO44_IN  0x102b39, BIT2

#define GPIO45_PAD PAD_I2S_OUT_WS
#define GPIO45_OEN 0x102b3a, BIT1
#define GPIO45_OUT 0x102b3a, BIT0
#define GPIO45_IN  0x102b3a, BIT2

#define GPIO46_PAD PAD_I2S_OUT_BCK
#define GPIO46_OEN 0x102b3b, BIT1
#define GPIO46_OUT 0x102b3b, BIT0
#define GPIO46_IN  0x102b3b, BIT2

#define GPIO47_PAD PAD_EMMC_IO0
#define GPIO47_OEN 0x102b78, BIT1
#define GPIO47_OUT 0x102b78, BIT0
#define GPIO47_IN  0x102b78, BIT2

#define GPIO48_PAD PAD_EMMC_IO1
#define GPIO48_OEN 0x102b79, BIT1
#define GPIO48_OUT 0x102b79, BIT0
#define GPIO48_IN  0x102b79, BIT2

#define GPIO49_PAD PAD_EMMC_IO2
#define GPIO49_OEN 0x102b7a, BIT1
#define GPIO49_OUT 0x102b7a, BIT0
#define GPIO49_IN  0x102b7a, BIT2

#define GPIO50_PAD PAD_EMMC_IO3
#define GPIO50_OEN 0x102b7b, BIT1
#define GPIO50_OUT 0x102b7b, BIT0
#define GPIO50_IN  0x102b7b, BIT2

#define GPIO51_PAD PAD_EMMC_IO4
#define GPIO51_OEN 0x102b7c, BIT1
#define GPIO51_OUT 0x102b7c, BIT0
#define GPIO51_IN  0x102b7c, BIT2

#define GPIO52_PAD PAD_EMMC_IO5
#define GPIO52_OEN 0x102b7d, BIT1
#define GPIO52_OUT 0x102b7d, BIT0
#define GPIO52_IN  0x102b7d, BIT2

#define GPIO53_PAD PAD_EMMC_IO6
#define GPIO53_OEN 0x102b7e, BIT1
#define GPIO53_OUT 0x102b7e, BIT0
#define GPIO53_IN  0x102b7e, BIT2

#define GPIO54_PAD PAD_EMMC_IO7
#define GPIO54_OEN 0x102b7f, BIT1
#define GPIO54_OUT 0x102b7f, BIT0
#define GPIO54_IN  0x102b7f, BIT2

#define GPIO55_PAD PAD_EMMC_IO8
#define GPIO55_OEN 0x102b80, BIT1
#define GPIO55_OUT 0x102b80, BIT0
#define GPIO55_IN  0x102b80, BIT2

#define GPIO56_PAD PAD_EMMC_IO9
#define GPIO56_OEN 0x102b81, BIT1
#define GPIO56_OUT 0x102b81, BIT0
#define GPIO56_IN  0x102b81, BIT2

#define GPIO57_PAD PAD_EMMC_IO10
#define GPIO57_OEN 0x102b82, BIT1
#define GPIO57_OUT 0x102b82, BIT0
#define GPIO57_IN  0x102b82, BIT2

#define GPIO58_PAD PAD_EMMC_IO11
#define GPIO58_OEN 0x102b83, BIT1
#define GPIO58_OUT 0x102b83, BIT0
#define GPIO58_IN  0x102b83, BIT2

#define GPIO59_PAD PAD_PWM0
#define GPIO59_OEN 0x102b88, BIT1
#define GPIO59_OUT 0x102b88, BIT0
#define GPIO59_IN  0x102b88, BIT2

#define GPIO60_PAD PAD_PWM1
#define GPIO60_OEN 0x102b89, BIT1
#define GPIO60_OUT 0x102b89, BIT0
#define GPIO60_IN  0x102b89, BIT2

#define GPIO61_PAD PAD_PWM2
#define GPIO61_OEN 0x102b8a, BIT1
#define GPIO61_OUT 0x102b8a, BIT0
#define GPIO61_IN  0x102b8a, BIT2

#define GPIO62_PAD PAD_PWM3
#define GPIO62_OEN 0x102b8b, BIT1
#define GPIO62_OUT 0x102b8b, BIT0
#define GPIO62_IN  0x102b8b, BIT2

#define GPIO63_PAD PAD_PWM4
#define GPIO63_OEN 0x102b8c, BIT1
#define GPIO63_OUT 0x102b8c, BIT0
#define GPIO63_IN  0x102b8c, BIT2

#define GPIO64_PAD PAD_SD_D0
#define GPIO64_OEN 0x102bac, BIT1
#define GPIO64_OUT 0x102bac, BIT0
#define GPIO64_IN  0x102bac, BIT2

#define GPIO65_PAD PAD_SD_D1
#define GPIO65_OEN 0x102bad, BIT1
#define GPIO65_OUT 0x102bad, BIT0
#define GPIO65_IN  0x102bad, BIT2

#define GPIO66_PAD PAD_SD_D2
#define GPIO66_OEN 0x102bae, BIT1
#define GPIO66_OUT 0x102bae, BIT0
#define GPIO66_IN  0x102bae, BIT2

#define GPIO67_PAD PAD_SD_D3
#define GPIO67_OEN 0x102bf9, BIT1
#define GPIO67_OUT 0x102bf9, BIT0
#define GPIO67_IN  0x102bf9, BIT2

#define GPIO68_PAD PAD_SD_CLK
#define GPIO68_OEN 0x102bfa, BIT1
#define GPIO68_OUT 0x102bfa, BIT0
#define GPIO68_IN  0x102bfa, BIT2

#define GPIO69_PAD PAD_SD_CMD
#define GPIO69_OEN 0x102bfb, BIT1
#define GPIO69_OUT 0x102bfb, BIT0
#define GPIO69_IN  0x102bfb, BIT2

#define GPIO70_PAD PAD_TCON0
#define GPIO70_OEN 0x102b93, BIT1
#define GPIO70_OUT 0x102b93, BIT0
#define GPIO70_IN  0x102b93, BIT2

#define GPIO71_PAD PAD_TCON1
#define GPIO71_OEN 0x102b92, BIT1
#define GPIO71_OUT 0x102b92, BIT0
#define GPIO71_IN  0x102b92, BIT2

#define GPIO72_PAD PAD_TCON2
#define GPIO72_OEN 0x102b95, BIT1
#define GPIO72_OUT 0x102b95, BIT0
#define GPIO72_IN  0x102b95, BIT2

#define GPIO73_PAD PAD_TCON3
#define GPIO73_OEN 0x102b94, BIT1
#define GPIO73_OUT 0x102b94, BIT0
#define GPIO73_IN  0x102b94, BIT2

#define GPIO74_PAD PAD_TCON4
#define GPIO74_OEN 0x102b97, BIT1
#define GPIO74_OUT 0x102b97, BIT0
#define GPIO74_IN  0x102b97, BIT2

#define GPIO75_PAD PAD_TCON5
#define GPIO75_OEN 0x102b96, BIT1
#define GPIO75_OUT 0x102b96, BIT0
#define GPIO75_IN  0x102b96, BIT2

#define GPIO76_PAD PAD_TCON6
#define GPIO76_OEN 0x102b99, BIT1
#define GPIO76_OUT 0x102b99, BIT0
#define GPIO76_IN  0x102b99, BIT2

#define GPIO77_PAD PAD_TCON7
#define GPIO77_OEN 0x102b98, BIT1
#define GPIO77_OUT 0x102b98, BIT0
#define GPIO77_IN  0x102b98, BIT2

#define GPIO78_PAD PAD_TGPIO0
#define GPIO78_OEN 0x102b8d, BIT1
#define GPIO78_OUT 0x102b8d, BIT0
#define GPIO78_IN  0x102b8d, BIT2

#define GPIO79_PAD PAD_TGPIO1
#define GPIO79_OEN 0x102b8e, BIT1
#define GPIO79_OUT 0x102b8e, BIT0
#define GPIO79_IN  0x102b8e, BIT2

#define GPIO80_PAD PAD_TS0_D0
#define GPIO80_OEN 0x102b1c, BIT1
#define GPIO80_OUT 0x102b1c, BIT0
#define GPIO80_IN  0x102b1c, BIT2

#define GPIO81_PAD PAD_TS0_D1
#define GPIO81_OEN 0x102b1d, BIT1
#define GPIO81_OUT 0x102b1d, BIT0
#define GPIO81_IN  0x102b1d, BIT2

#define GPIO82_PAD PAD_TS0_D2
#define GPIO82_OEN 0x102b1e, BIT1
#define GPIO82_OUT 0x102b1e, BIT0
#define GPIO82_IN  0x102b1e, BIT2

#define GPIO83_PAD PAD_TS0_D3
#define GPIO83_OEN 0x102b1f, BIT1
#define GPIO83_OUT 0x102b1f, BIT0
#define GPIO83_IN  0x102b1f, BIT2

#define GPIO84_PAD PAD_TS0_D4
#define GPIO84_OEN 0x102b20, BIT1
#define GPIO84_OUT 0x102b20, BIT0
#define GPIO84_IN  0x102b20, BIT2

#define GPIO85_PAD PAD_TS0_D5
#define GPIO85_OEN 0x102b21, BIT1
#define GPIO85_OUT 0x102b21, BIT0
#define GPIO85_IN  0x102b21, BIT2

#define GPIO86_PAD PAD_TS0_D6
#define GPIO86_OEN 0x102b22, BIT1
#define GPIO86_OUT 0x102b22, BIT0
#define GPIO86_IN  0x102b22, BIT2

#define GPIO87_PAD PAD_TS0_D7
#define GPIO87_OEN 0x102b23, BIT1
#define GPIO87_OUT 0x102b23, BIT0
#define GPIO87_IN  0x102b23, BIT2

#define GPIO88_PAD PAD_TS0_VLD
#define GPIO88_OEN 0x102b24, BIT1
#define GPIO88_OUT 0x102b24, BIT0
#define GPIO88_IN  0x102b24, BIT2

#define GPIO89_PAD PAD_TS0_SYNC
#define GPIO89_OEN 0x102b25, BIT1
#define GPIO89_OUT 0x102b25, BIT0
#define GPIO89_IN  0x102b25, BIT2

#define GPIO90_PAD PAD_TS0_CLK
#define GPIO90_OEN 0x102b26, BIT1
#define GPIO90_OUT 0x102b26, BIT0
#define GPIO90_IN  0x102b26, BIT2

//-------------------------------------------------------------------------------------------------
//  Local Structures
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Variables
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Variables
//-------------------------------------------------------------------------------------------------
static const struct gpio_setting
{
    U32 r_oen;
    U8  m_oen;
    U32 r_out;
    U8  m_out;
    U32 r_in;
    U8  m_in;
} gpio_table[] =
{
#define __GPIO__(_x_)   { CONCAT(CONCAT(GPIO, _x_), _OEN),   \
                          CONCAT(CONCAT(GPIO, _x_), _OUT),   \
                          CONCAT(CONCAT(GPIO, _x_), _IN) }
#define __GPIO(_x_)     __GPIO__(_x_)

//
// !! WARNING !! DO NOT MODIFIY !!!!
//
// These defines order must match following
// 1. the PAD name in GPIO excel
// 2. the perl script to generate the package header file
//
    //__GPIO(999), // 0 is not used

    __GPIO(1), __GPIO(2), __GPIO(3), __GPIO(4),
    __GPIO(5), __GPIO(6), __GPIO(7), __GPIO(8), __GPIO(9),
    __GPIO(10), __GPIO(11), __GPIO(12), __GPIO(13), __GPIO(14),
    __GPIO(15), __GPIO(16), __GPIO(17), __GPIO(18), __GPIO(19),
    __GPIO(20), __GPIO(21), __GPIO(22), __GPIO(23), __GPIO(24),
    __GPIO(25), __GPIO(26), __GPIO(27), __GPIO(28), __GPIO(29),
    __GPIO(30), __GPIO(31), __GPIO(32), __GPIO(33), __GPIO(34),
    __GPIO(35), __GPIO(36), __GPIO(37), __GPIO(38), __GPIO(39),
    __GPIO(40), __GPIO(41), __GPIO(42), __GPIO(43), __GPIO(44),
    __GPIO(45), __GPIO(46), __GPIO(47), __GPIO(48), __GPIO(49),
    __GPIO(50), __GPIO(51), __GPIO(52), __GPIO(53), __GPIO(54),
    __GPIO(55), __GPIO(56), __GPIO(57), __GPIO(58), __GPIO(59),
    __GPIO(60), __GPIO(61), __GPIO(62), __GPIO(63), __GPIO(64),
    __GPIO(65), __GPIO(66), __GPIO(67), __GPIO(68), __GPIO(69),
    __GPIO(70), __GPIO(71), __GPIO(72), __GPIO(73), __GPIO(74),
    __GPIO(75), __GPIO(76), __GPIO(77), __GPIO(78), __GPIO(79),
    __GPIO(80), __GPIO(81), __GPIO(82), __GPIO(83), __GPIO(84),
    __GPIO(85), __GPIO(86), __GPIO(87), __GPIO(88), __GPIO(89),
    __GPIO(90)
};

//-------------------------------------------------------------------------------------------------
//  Debug Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Local Functions
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------
//  Global Functions
//-------------------------------------------------------------------------------------------------

//the functions of this section set to initialize
void MHal_GPIO_Init(void)
{
    MHal_GPIO_REG(REG_ALL_PAD_IN) &= ~BIT7;
}

void MHal_GPIO_WriteRegBit(U32 u32Reg, U8 u8Enable, U8 u8BitMsk)
{
    if(u8Enable)
        MHal_GPIO_REG(u32Reg) |= u8BitMsk;
    else
        MHal_GPIO_REG(u32Reg) &= (~u8BitMsk);
}

U8 MHal_GPIO_ReadRegBit(U32 u32Reg, U8 u8BitMsk)
{
    return ((MHal_GPIO_REG(u32Reg)&u8BitMsk)? 1 : 0);
}

void MHal_GPIO_Pad_Set(U8 u8IndexGPIO)
{

}
void MHal_GPIO_Pad_Oen(U8 u8IndexGPIO)
{
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_oen) &= (~gpio_table[u8IndexGPIO].m_oen);
}

void MHal_GPIO_Pad_Odn(U8 u8IndexGPIO)
{
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_oen) |= gpio_table[u8IndexGPIO].m_oen;
}

U8 MHal_GPIO_Pad_Level(U8 u8IndexGPIO)
{
    return ((MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_in)&gpio_table[u8IndexGPIO].m_in)? 1 : 0);
}

U8 MHal_GPIO_Pad_InOut(U8 u8IndexGPIO)
{
    return ((MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_oen)&gpio_table[u8IndexGPIO].m_oen)? 1 : 0);
}

void MHal_GPIO_Pull_High(U8 u8IndexGPIO)
{
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_out) |= gpio_table[u8IndexGPIO].m_out;
}

void MHal_GPIO_Pull_Low(U8 u8IndexGPIO)
{
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_out) &= (~gpio_table[u8IndexGPIO].m_out);
}

void MHal_GPIO_Set_High(U8 u8IndexGPIO)
{
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_oen) &= (~gpio_table[u8IndexGPIO].m_oen);
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_out) |= gpio_table[u8IndexGPIO].m_out;
}

void MHal_GPIO_Set_Low(U8 u8IndexGPIO)
{
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_oen) &= (~gpio_table[u8IndexGPIO].m_oen);
    MHal_GPIO_REG(gpio_table[u8IndexGPIO].r_out) &= (~gpio_table[u8IndexGPIO].m_out);
}