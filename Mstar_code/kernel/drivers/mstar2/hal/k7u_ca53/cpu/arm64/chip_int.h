#ifndef __CHIP_INT_H__
#define __CHIP_INT_H__

#include <mach/platform.h>

/******************************************************
       GIC-400
*******************************************************/
#define INT_PPI_VTIMER                  27 // Virtual timer event
#define INT_PPI_FIQ                     28 // Legacy nFIQ input
#define INT_ID_PTIMER                   29 // Secure EL1 physical timer event
#define INT_PPI_IRQ                     31 // Legacy nIRQ input

#define CONFIG_SPI                      1

#if CONFIG_SPI
   #define CONFIG_SPI_IRQ               1
   #define INT_SPI_IRQ_HOST0            63
   #define INT_SPI_IRQ_HOST1            64
   #define INT_SPI_IRQ_HOST2            65
   #define INT_SPI_IRQ_HOST3            66
   #define INT_SPI_FIQ_HOST0            67
   #define INT_SPI_FIQ_HOST1            68
   #define INT_SPI_FIQ_HOST2            69
   #define INT_SPI_FIQ_HOST3            70
   #define INT_SPI_IRQ                  INT_SPI_IRQ_HOST0
   #define SPI_MIN_NUM                  32
   #define SPI_MAX_NUM                  1020

#endif // end of CONFIG_SPI

//Cortex-A9 GIC PPI
#define IRQ_LOCALTIMER                  29
#define IRQ_LOCALWDOG                   30

//Cortex-A9 PMU(Performance Monitor Unit)
#define CHIP_IRQ_PMU0                   166
#define CHIP_IRQ_PMU1                   172
#define CHIP_IRQ_PMU2                   178
#define CHIP_IRQ_PMU3                   184

extern ptrdiff_t mstar_pm_base;

#define REG_INT_BASE_PA                 (0x1F000000UL  + (0x101900UL << 1))
#define REG_INT_BASE                    (mstar_pm_base + (0x101900UL << 1))
#define REG_INT_HYP_BASE_PA             (0x1F000000UL  + (0x101000UL << 1))
#define REG_INT_HYP_BASE                (mstar_pm_base + (0x101000UL << 1))

#ifndef NR_IRQS
#define NR_IRQS                         384
#endif

//IRQ registers
#define REG_IRQ_MASK_L                  (REG_INT_BASE + (0x0054 << 2))
#define REG_IRQ_MASK_H                  (REG_INT_BASE + (0x0055 << 2))
#define REG_IRQ_PENDING_L               (REG_INT_BASE + (0x005c << 2))
#define REG_IRQ_PENDING_H               (REG_INT_BASE + (0x005d << 2))

//IRQ EXP registers
#define REG_IRQ_EXP_MASK_L              (REG_INT_BASE + (0x0056 << 2))
#define REG_IRQ_EXP_MASK_H              (REG_INT_BASE + (0x0057 << 2))
#define REG_IRQ_EXP_PENDING_L           (REG_INT_BASE + (0x005e << 2))
#define REG_IRQ_EXP_PENDING_H           (REG_INT_BASE + (0x005f << 2))

//IRQ HYP registers
#define REG_IRQ_HYP_MASK_L              (REG_INT_HYP_BASE + (0x0054 << 2))
#define REG_IRQ_HYP_MASK_H              (REG_INT_HYP_BASE + (0x0055 << 2))
#define REG_IRQ_HYP_PENDING_L           (REG_INT_HYP_BASE + (0x005c << 2))
#define REG_IRQ_HYP_PENDING_H           (REG_INT_HYP_BASE + (0x005d << 2))

//IRQ SUP registers
#define REG_IRQ_SUP_MASK_L        	(REG_INT_HYP_BASE + (0x0056 << 2))
#define REG_IRQ_SUP_MASK_H          	(REG_INT_HYP_BASE + (0x0057 << 2))
#define REG_IRQ_SUP_PENDING_L       	(REG_INT_HYP_BASE + (0x005e << 2))
#define REG_IRQ_SUP_PENDING_H       	(REG_INT_HYP_BASE + (0x005f << 2))

#if defined(CONFIG_MP_PLATFORM_MSTAR_LEGANCY_INTR)
//FIQ registers
#define REG_FIQ_MASK_L                  (REG_INT_BASE + (0x0044 << 2))
#define REG_FIQ_MASK_H                  (REG_INT_BASE + (0x0045 << 2))
#define REG_FIQ_CLEAR_L                 (REG_INT_BASE + (0x004c << 2))
#define REG_FIQ_CLEAR_H                 (REG_INT_BASE + (0x004d << 2))
#define REG_FIQ_PENDING_L               (REG_INT_BASE + (0x004c << 2))
#define REG_FIQ_PENDING_H               (REG_INT_BASE + (0x004d << 2))

//FIQ EXP registers
#define REG_FIQ_EXP_MASK_L              (REG_INT_BASE + (0x0046 << 2))
#define REG_FIQ_EXP_MASK_H              (REG_INT_BASE + (0x0047 << 2))
#define REG_FIQ_EXP_CLEAR_L             (REG_INT_BASE + (0x004e << 2))
#define REG_FIQ_EXP_CLEAR_H             (REG_INT_BASE + (0x004f << 2))
#define REG_FIQ_EXP_PENDING_L           (REG_INT_BASE + (0x004e << 2))
#define REG_FIQ_EXP_PENDING_H           (REG_INT_BASE + (0x004f << 2))

//FIQ HYP register
#define REG_FIQ_HYP_MASK_L              (REG_INT_HYP_BASE + (0x0044 << 2))
#define REG_FIQ_HYP_MASK_H              (REG_INT_HYP_BASE + (0x0045 << 2))
#define REG_FIQ_HYP_CLEAR_L             (REG_INT_HYP_BASE + (0x004c << 2))
#define REG_FIQ_HYP_CLEAR_H             (REG_INT_HYP_BASE + (0x004d << 2))
#define REG_FIQ_HYP_PENDING_L           (REG_INT_HYP_BASE + (0x004c << 2))
#define REG_FIQ_HYP_PENDING_H           (REG_INT_HYP_BASE + (0x004d << 2))

//FIQ SUP registers
#define REG_FIQ_SUP_MASK_L              (REG_INT_HYP_BASE + (0x0046 << 2))
#define REG_FIQ_SUP_MASK_H              (REG_INT_HYP_BASE + (0x0047 << 2))
#define REG_FIQ_SUP_CLEAR_L             (REG_INT_HYP_BASE + (0x004e << 2))
#define REG_FIQ_SUP_CLEAR_H             (REG_INT_HYP_BASE + (0x004f << 2))
#define REG_FIQ_SUP_PENDING_L           (REG_INT_HYP_BASE + (0x004e << 2))
#define REG_FIQ_SUP_PENDING_H           (REG_INT_HYP_BASE + (0x004f << 2))
#else

//FIQ registers
#define REG_FIQ_MASK_L                  (REG_INT_BASE + (0x0004 << 2))
#define REG_FIQ_MASK_H                  (REG_INT_BASE + (0x0005 << 2))
#define REG_FIQ_CLEAR_L                 (REG_INT_BASE + (0x000c << 2))
#define REG_FIQ_CLEAR_H                 (REG_INT_BASE + (0x000d << 2))
#define REG_FIQ_PENDING_L               (REG_INT_BASE + (0x000c << 2))
#define REG_FIQ_PENDING_H               (REG_INT_BASE + (0x000d << 2))

//FIQ EXP registers
#define REG_FIQ_EXP_MASK_L              (REG_INT_BASE + (0x0006 << 2))
#define REG_FIQ_EXP_MASK_H              (REG_INT_BASE + (0x0007 << 2))
#define REG_FIQ_EXP_CLEAR_L             (REG_INT_BASE + (0x000e << 2))
#define REG_FIQ_EXP_CLEAR_H             (REG_INT_BASE + (0x000f << 2))
#define REG_FIQ_EXP_PENDING_L           (REG_INT_BASE + (0x000e << 2))
#define REG_FIQ_EXP_PENDING_H           (REG_INT_BASE + (0x000f << 2))

#define REG_FIQ_HYP_MASK_L              (REG_INT_HYP_BASE + (0x0004 << 2))
#define REG_FIQ_HYP_MASK_H              (REG_INT_HYP_BASE + (0x0005 << 2))
#define REG_FIQ_HYP_CLEAR_L             (REG_INT_HYP_BASE + (0x000c << 2))
#define REG_FIQ_HYP_CLEAR_H             (REG_INT_HYP_BASE + (0x000d << 2))
#define REG_FIQ_HYP_PENDING_L           (REG_INT_HYP_BASE + (0x000c << 2))
#define REG_FIQ_HYP_PENDING_H           (REG_INT_HYP_BASE + (0x000d << 2))

#endif /* CONFIG_MP_PLATFORM_MSTAR_LEGANCY_INTR */

#ifdef CONFIG_MP_PLATFORM_INT_1_to_1_SPI
#define MSTAR_IRQ_BASE                  32
#define MSTAR_FIQ_BASE                  96
#define MSTAR_IRQ_HYP_BASE              192
#define MSTAR_FIQ_HYP_BASE              224
#define MSTAR_INT_BASE                  MSTAR_IRQ_BASE
#define MSTAR_CHIP_INT_END              255 
#else
#define MSTAR_IRQ_BASE                  192
#define MSTAR_FIQ_BASE                  128
#define MSTAR_IRQ_HYP_BASE              320
#define MSTAR_FIQ_HYP_BASE              256
#define MSTAR_INT_BASE                  MSTAR_FIQ_BASE
#define MSTAR_CHIP_INT_END              384
#endif


/*******************************************************/
/*   THE IRQ AND FIQ ARE NOT COMPLETED.                */
/*   FOR EACH IP OWNER, PLEASE REVIEW IT BY YOURSELF   */
/*******************************************************/
enum {
    E_IRQL_START	= MSTAR_IRQ_BASE,
    E_IRQH_START    = MSTAR_IRQ_BASE + 16,
    E_IRQEXPL_START = MSTAR_IRQ_BASE + 32,
    E_IRQEXPH_START = MSTAR_IRQ_BASE + 48,

	E_IRQHYPL_START = MSTAR_IRQ_HYP_BASE,
	E_IRQHYPH_START = MSTAR_IRQ_HYP_BASE + 16,
	E_IRQSUPL_START = MSTAR_IRQ_HYP_BASE + 32,
	E_IRQSUPH_START = MSTAR_IRQ_HYP_BASE + 48,

    E_FIQL_START    = MSTAR_FIQ_BASE,
    E_FIQH_START    = MSTAR_FIQ_BASE + 16,
    E_FIQEXPL_START = MSTAR_FIQ_BASE + 32,
    E_FIQEXPH_START = MSTAR_FIQ_BASE + 48,

	E_FIQHYPL_START = MSTAR_FIQ_HYP_BASE,
	E_FIQHYPH_START = MSTAR_FIQ_HYP_BASE + 16,
	E_FIQSUPL_START = MSTAR_FIQ_HYP_BASE + 32,
	E_FIQSUPH_START = MSTAR_FIQ_HYP_BASE + 48,
};

typedef enum {
    /* irq */
    E_IRQ_UART0         	= MSTAR_IRQ_BASE + 0,
    E_IRQ_MIIC1			= MSTAR_IRQ_BASE + 1,
    E_IRQ_MVD2MIPS      	= MSTAR_IRQ_BASE + 2,
    E_IRQ_MVD           	= MSTAR_IRQ_BASE + 3,
    E_IRQ_RESERVED4     	= MSTAR_IRQ_BASE + 4, /* ~reg_top_gpio_in[2] --> x */
    E_IRQ_CA_NSK        	= MSTAR_IRQ_BASE + 5,
    E_IRQ_USB           	= MSTAR_IRQ_BASE + 6,
    E_IRQ_UHC           	= MSTAR_IRQ_BASE + 7,
    E_IRQ_ZDEC			= MSTAR_IRQ_BASE + 8,
    E_IRQ_GMAC          	= MSTAR_IRQ_BASE + 9,
    E_IRQ_DISP          	= MSTAR_IRQ_BASE + 10,
    E_IRQ_TSIO          	= MSTAR_IRQ_BASE + 11,
    E_IRQ_MSPI          	= MSTAR_IRQ_BASE + 12,
    E_IRQ_EVD           	= MSTAR_IRQ_BASE + 13,
    E_IRQ_SATA_PHY      	= MSTAR_IRQ_BASE + 14,
    E_IRQ_SATA_INT      	= MSTAR_IRQ_BASE + 15,
    
    E_IRQ_TSP2HK        	= MSTAR_IRQ_BASE + 16,
    E_IRQ_VE            	= MSTAR_IRQ_BASE + 17,
    E_IRQ_AEON2HI       	= MSTAR_IRQ_BASE + 18,
    E_IRQ_DC            	= MSTAR_IRQ_BASE + 19,
    E_IRQ_GOP           	= MSTAR_IRQ_BASE + 20,
    E_IRQ_FCIE_TEE      	= MSTAR_IRQ_BASE + 21,
    E_IRQ_MIIC0         	= MSTAR_IRQ_BASE + 22,
    E_IRQ_RTC0          	= MSTAR_IRQ_BASE + 23,
    E_IRQ_KEYPAD        	= MSTAR_IRQ_BASE + 24,
    E_IRQ_PM            	= MSTAR_IRQ_BASE + 25,
    E_IRQ_MFE           	= MSTAR_IRQ_BASE + 26,
    E_IRQ_USB30M1_SS		= MSTAR_IRQ_BASE + 27,
    E_IRQ_USB30M1_HS_UHC	= MSTAR_IRQ_BASE + 28,
    E_IRQ_RTC1          	= MSTAR_IRQ_BASE + 29,
    E_IRQ_CA_IP         	= MSTAR_IRQ_BASE + 30,		
    E_IRQ_USB30M1_HS_USB	= MSTAR_IRQ_BASE + 31,
    
    E_IRQEXPL_TSP_TSO0      	= MSTAR_IRQ_BASE + 32,
    E_IRQEXPL_USB1		= MSTAR_IRQ_BASE + 33,
    E_IRQEXPL_UHC1          	= MSTAR_IRQ_BASE + 34,
    E_IRQEXPL_MIU           	= MSTAR_IRQ_BASE + 35,
    E_IRQEXPL_ERROR_RESP    	= MSTAR_IRQ_BASE + 36,
    E_IRQEXPL_OTG           	= MSTAR_IRQ_BASE + 37,
    E_IRQEXPL_U3_PCIE_PHY	= MSTAR_IRQ_BASE + 38,
    E_IRQEXPL_UART1		= MSTAR_IRQ_BASE + 39,
    E_IRQEXPL_HVD          	= MSTAR_IRQ_BASE + 40,
    E_IRQEXPL_RESERVED41    	= MSTAR_IRQ_BASE + 41, /* reg_top_gpio_in[4] --> x */
    E_IRQEXPL_RESERVED42    	= MSTAR_IRQ_BASE + 42, /* ~reg_top_gpio_in[4] --> x */
    E_IRQEXPL_NOE0     		= MSTAR_IRQ_BASE + 43,
    E_IRQEXPL_CA_CRYPTO_DMA	= MSTAR_IRQ_BASE + 44,
    E_IRQEXPL_JPD		= MSTAR_IRQ_BASE + 45,
    E_IRQEXPL_DISP1     	= MSTAR_IRQ_BASE + 46,
    E_IRQEXPL_AKL           	= MSTAR_IRQ_BASE + 47,
    
    E_IRQEXPH_BDMA0         	= MSTAR_IRQ_BASE + 48,
    E_IRQEXPH_BDMA1         	= MSTAR_IRQ_BASE + 49,
    E_IRQEXPH_UART2MCU    	= MSTAR_IRQ_BASE + 50,
    E_IRQEXPH_URDMA2MCU    	= MSTAR_IRQ_BASE + 51,
    E_IRQEXPH_DVI_HDMI_HDCP	= MSTAR_IRQ_BASE + 52,
    E_IRQEXPH_CEC		= MSTAR_IRQ_BASE + 53,
    E_IRQEXPH_HDMITX        	= MSTAR_IRQ_BASE + 54,
    E_IRQEXPH_FCIE          	= MSTAR_IRQ_BASE + 55,
    E_IRQEXPH_GPIO_TRIGGER  	= MSTAR_IRQ_BASE + 56,
    E_IRQEXPH_GPD           	= MSTAR_IRQ_BASE + 57,
    E_IRQEXPH_SAR1          	= MSTAR_IRQ_BASE + 58,
    E_IRQEXPH_DAC_PLUG_DET  	= MSTAR_IRQ_BASE + 59,
    E_IRQEXPH_RESERVED60    	= MSTAR_IRQ_BASE + 60, /* reg_top_gpio_in[2] --> x */
    E_IRQEXPH_RASP0		= MSTAR_IRQ_BASE + 61,
    E_IRQEXPH_FI_QUEUE      	= MSTAR_IRQ_BASE + 62,
    E_IRQEXPH_FRM_PM        	= MSTAR_IRQ_BASE + 63,
    
    /* irq hyper, start from 64@interrupt_table */
    E_IRQHYPL_MIIC2         			= MSTAR_IRQ_HYP_BASE + 0,
    E_IRQHYPL_MIIC3         			= MSTAR_IRQ_HYP_BASE + 1,
    E_IRQHYPL_MIIC4         			= MSTAR_IRQ_HYP_BASE + 2,
    E_IRQHYPL_TSIO_LOC_DEC  			= MSTAR_IRQ_HYP_BASE + 3,
    E_IRQHYPL_HDMITX_PHY    			= MSTAR_IRQ_HYP_BASE + 4,
    E_IRQHYPL_GE            			= MSTAR_IRQ_HYP_BASE + 5,
    E_IRQHYPL_MIU_SECURITY			= MSTAR_IRQ_HYP_BASE + 6,  //70
    E_IRQHYPL_U3_PHY        			= MSTAR_IRQ_HYP_BASE + 7,
    E_IRQHYPL_G3D2MCU_DFT   			= MSTAR_IRQ_HYP_BASE + 8,
    E_IRQHYPL_CMDQ          			= MSTAR_IRQ_HYP_BASE + 9,
    E_IRQHYPL_AUDMA_V2      			= MSTAR_IRQ_HYP_BASE + 10,
    E_IRQHYPL_SCDC_PM				= MSTAR_IRQ_HYP_BASE + 11,
    E_IRQHYPL_MSPI2         			= MSTAR_IRQ_HYP_BASE + 12,
    E_IRQHYPL_SMART0        			= MSTAR_IRQ_HYP_BASE + 13,
    E_IRQHYPL_SMART1				= MSTAR_IRQ_HYP_BASE + 14,
    E_IRQHYPL_DC_SUB        			= MSTAR_IRQ_HYP_BASE + 15,
    
    E_IRQHYPH_SDIO				= MSTAR_IRQ_HYP_BASE + 16,  //80
    E_IRQHYPH_USB30_SS				= MSTAR_IRQ_HYP_BASE + 17,
    E_IRQHYPH_MIU_CMA_CLR			= MSTAR_IRQ_HYP_BASE + 18,
    E_IRQHYPH_TSP_SPARE_CA2PM_8			= MSTAR_IRQ_HYP_BASE + 19,
    E_IRQHYPH_USB30_HS_USB			= MSTAR_IRQ_HYP_BASE + 20,
    E_IRQHYPH_USB30_HS_UHC			= MSTAR_IRQ_HYP_BASE + 21, /* usb30_hs_usc --> usb30_hs_uhc */
    E_IRQHYPH_DIAMOND_RXIU_TIMEOUT		= MSTAR_IRQ_HYP_BASE + 22,
    E_IRQHYPH_RESERVED87			= MSTAR_IRQ_HYP_BASE + 23,
    E_IRQHYPH_IM_INVALID			= MSTAR_IRQ_HYP_BASE + 24,
    E_IRQHYPH_PCIE_RC				= MSTAR_IRQ_HYP_BASE + 25,
    E_IRQHYPH_V9_MUI_AL				= MSTAR_IRQ_HYP_BASE + 26, /* mui? miu? */
    E_IRQHYPH_SDIO_OSP				= MSTAR_IRQ_HYP_BASE + 27,
    E_IRQHYPH_MIU_TLB				= MSTAR_IRQ_HYP_BASE + 28,
    E_IRQHYPH_DIPW				= MSTAR_IRQ_HYP_BASE + 29,
    E_IRQHYPH_SECGMAC               		= MSTAR_IRQ_HYP_BASE + 30,
    E_IRQHYPH_PAS_PTS_INTRL_COMBINE		= MSTAR_IRQ_HYP_BASE + 31,//95
    
    E_IRQHYPH_TSP_TSO1				= MSTAR_IRQ_HYP_BASE + 32,
    E_IRQHYPH_IMI_TOP				= MSTAR_IRQ_HYP_BASE + 33,
    E_IRQHYPH_PE2_RC				= MSTAR_IRQ_HYP_BASE + 34,
    E_IRQHYPH_FOSSIL_RXIU_TIMEOUT		= MSTAR_IRQ_HYP_BASE + 35,
    E_IRQHYPH_EVD_LITE				= MSTAR_IRQ_HYP_BASE + 36,
    E_IRQHYPH_COMPA				= MSTAR_IRQ_HYP_BASE + 37,
    E_IRQHYPH_NOE1				= MSTAR_IRQ_HYP_BASE + 38,
    E_IRQHYPH_WED0				= MSTAR_IRQ_HYP_BASE + 39,
    E_IRQHYPH_WED1				= MSTAR_IRQ_HYP_BASE + 40,
    E_IRQHYPH_AU_VREC				= MSTAR_IRQ_HYP_BASE + 41,
    E_IRQHYPH_RESERVED106			= MSTAR_IRQ_HYP_BASE + 42,
    E_IRQHYPH_RESERVED107			= MSTAR_IRQ_HYP_BASE + 43,
    E_IRQHYPH_RESERVED108			= MSTAR_IRQ_HYP_BASE + 44,
    E_IRQHYPH_RESERVED109			= MSTAR_IRQ_HYP_BASE + 45,
    E_IRQHYPH_MVD2				= MSTAR_IRQ_HYP_BASE + 46,
    E_IRQHYPH_MVD22MIPS				= MSTAR_IRQ_HYP_BASE + 47,
    
    E_IRQHYPH_CILINK_SOC_IF			= MSTAR_IRQ_HYP_BASE + 48,
    E_IRQHYPH_GMAC_TX				= MSTAR_IRQ_HYP_BASE + 49,
    E_IRQHYPH_SEC_GMAC_TX			= MSTAR_IRQ_HYP_BASE + 50,
    E_IRQSUPH_RESERVED115			= MSTAR_IRQ_HYP_BASE + 51,
    E_IRQSUPH_RESERVED116			= MSTAR_IRQ_HYP_BASE + 52,
    E_IRQSUPH_RESERVED117			= MSTAR_IRQ_HYP_BASE + 53,
    E_IRQSUPH_RESERVED118			= MSTAR_IRQ_HYP_BASE + 54,
    E_IRQSUPH_RESERVED119			= MSTAR_IRQ_HYP_BASE + 55,
    E_IRQSUPH_RESERVED120			= MSTAR_IRQ_HYP_BASE + 56,
    E_IRQSUPH_RESERVED121			= MSTAR_IRQ_HYP_BASE + 57,
    E_IRQSUPH_RESERVED122			= MSTAR_IRQ_HYP_BASE + 58,
    E_IRQSUPH_RESERVED123			= MSTAR_IRQ_HYP_BASE + 59,
    E_IRQSUPH_RESERVED124			= MSTAR_IRQ_HYP_BASE + 60,
    E_IRQSUPH_RESERVED125			= MSTAR_IRQ_HYP_BASE + 61,
    E_IRQSUPH_RESERVED126			= MSTAR_IRQ_HYP_BASE + 62,
    E_IRQSUPH_RESERVED127			= MSTAR_IRQ_HYP_BASE + 63,
    
    /* fiq */
    E_FIQ_EXTIMER0          	= MSTAR_FIQ_BASE + 0, /* timer0 --> extimer0 */
    E_FIQ_EXTIMER1          	= MSTAR_FIQ_BASE + 1, /* timer1 --> extimer1 */
    E_FIQ_WDT               	= MSTAR_FIQ_BASE + 2,
    E_FIQ_SEC_TIMER0        	= MSTAR_FIQ_BASE + 3,
    E_FIQ_SEC_TIMER1        	= MSTAR_FIQ_BASE + 4,
    E_FIQ_MB_AUR2TO_MCU0    	= MSTAR_FIQ_BASE + 5,
    E_FIQ_MB_DSP2TOMCU0		= MSTAR_FIQ_BASE + 6,
    E_FIQ_MB_DSP2TOMCU1     	= MSTAR_FIQ_BASE + 7,
    E_FIQ_MB_AUR2TO_MCU1    	= MSTAR_FIQ_BASE + 8,
    E_FIQ_MB_AUR2TO_MCU2    	= MSTAR_FIQ_BASE + 9,
    E_FIQ_HDMI_NON_PCM_MODE	= MSTAR_FIQ_BASE + 10,
    E_FIQ_SPDIF_IN_NON_PCM	= MSTAR_FIQ_BASE + 11,
    E_FIQ_LAN_ESD           	= MSTAR_FIQ_BASE + 12,
    E_FIQ_SE_DSP2UP         	= MSTAR_FIQ_BASE + 13,
    E_FIQ_TSP2AEON          	= MSTAR_FIQ_BASE + 14,
    E_FIQ_VIVALDI_STR       	= MSTAR_FIQ_BASE + 15,
    
    E_FIQ_VIVALDI_PTS       	= MSTAR_FIQ_BASE + 16,
    E_FIQ_DSP_MIU_PROT		= MSTAR_FIQ_BASE + 17,
    E_FIQ_XIU_TIMEOUT       	= MSTAR_FIQ_BASE + 18,
    E_FIQ_VE_VBI_F0         	= MSTAR_FIQ_BASE + 19,
    E_FIQ_VE_VBI_F1         	= MSTAR_FIQ_BASE + 20,
    E_FIQ_MB_AUR2TO_MCU3    	= MSTAR_FIQ_BASE + 21,
    E_FIQ_VE_DONE_TT        	= MSTAR_FIQ_BASE + 22,
    E_FIQ_IR			= MSTAR_FIQ_BASE + 23,
    E_FIQ_AU_SPDIF_TX_CS0	= MSTAR_FIQ_BASE + 24,
    E_FIQ_AU_SPDIF_TX_CS1   	= MSTAR_FIQ_BASE + 25,
    E_FIQ_DSP2MIPS          	= MSTAR_FIQ_BASE + 26,
    E_FIQ_IR_RC			= MSTAR_FIQ_BASE + 27,
    E_FIQ_AU_DMA_BUFFER 	= MSTAR_FIQ_BASE + 28,
    E_FIQ_VE_SW_WR2BUF  	= MSTAR_FIQ_BASE + 29,
    E_FIQH_HST0To3       	= MSTAR_FIQ_BASE + 30,
    E_FIQH_HST0To2       	= MSTAR_FIQ_BASE + 31,
    
    E_FIQEXPL_HST0TO1		= MSTAR_FIQ_BASE + 32,
    E_FIQEXPL_HST0TO4		= MSTAR_FIQ_BASE + 33,
    E_FIQEXPL_HST1TO3       	= MSTAR_FIQ_BASE + 34,
    E_FIQEXPL_HST1TO2       	= MSTAR_FIQ_BASE + 35,
    E_FIQEXPL_HST1TO5		= MSTAR_FIQ_BASE + 36,
    E_FIQEXPL_HST1TO4		= MSTAR_FIQ_BASE + 37,
    E_FIQEXPL_HST2TO3       	= MSTAR_FIQ_BASE + 38,
    E_FIQEXPL_HST2TO1       	= MSTAR_FIQ_BASE + 39,
    E_FIQEXPL_HST2TO5       	= MSTAR_FIQ_BASE + 40,
    E_FIQEXPL_HST2TO4       	= MSTAR_FIQ_BASE + 41,
    E_FIQEXPL_HST3TO2		= MSTAR_FIQ_BASE + 42,
    E_FIQEXPL_HST3TO1       	= MSTAR_FIQ_BASE + 43,
    E_FIQEXPL_HST3TO5       	= MSTAR_FIQ_BASE + 44,
    E_FIQEXPL_HST3TO4       	= MSTAR_FIQ_BASE + 45,
    E_FIQEXPL_HDMITX        	= MSTAR_FIQ_BASE + 46,
    E_FIQEXPL_CRYPTO_DMA    	= MSTAR_FIQ_BASE + 47,
    
    E_FIQEXPH_HST4TO3       	= MSTAR_FIQ_BASE + 48,
    E_FIQEXPH_HST4TO2       	= MSTAR_FIQ_BASE + 49,
    E_FIQEXPH_HST4TO1       	= MSTAR_FIQ_BASE + 50,
    E_FIQEXPH_HST4TO5       	= MSTAR_FIQ_BASE + 51,
    E_FIQEXPH_FRM_PM        	= MSTAR_FIQ_BASE + 52,
    E_FIQEXPH_SEC_GUARD		= MSTAR_FIQ_BASE + 53,
    E_FIQEXPH_SD_CDZ    	= MSTAR_FIQ_BASE + 54,
    E_FIQEXPH_IR2    		= MSTAR_FIQ_BASE + 55,
    E_FIQEXPH_IR2_RC    	= MSTAR_FIQ_BASE + 56,
    E_FIQEXPH_MB_AUR2TO_MCU4    = MSTAR_FIQ_BASE + 57,
    E_FIQEXPH_MB_AUR2TO_MCU5    = MSTAR_FIQ_BASE + 58,
    E_FIQEXPH_RTC2_SEC_INT	= MSTAR_FIQ_BASE + 59,
    E_FIQEXPH_USB_INT_P2    	= MSTAR_FIQ_BASE + 60,
    E_FIQEXPH_UHC_INT_P2    	= MSTAR_FIQ_BASE + 61,
    E_FIQEXPH_USB_INT_P0    	= MSTAR_FIQ_BASE + 62,
    E_FIQEXPH_UHC_INT_P0    	= MSTAR_FIQ_BASE + 63,
    
    
    /* fiq hyper, start from 64@interrupt_table */
    E_FIQHYPL_USB30_SS_INT   	= MSTAR_FIQ_HYP_BASE + 0,
    E_FIQHYPL_OTG_INT_P0    	= MSTAR_FIQ_HYP_BASE + 1,
    E_FIQHYPL_USB_INT_P1    	= MSTAR_FIQ_HYP_BASE + 2,
    E_FIQHYPL_UHC_INT_P1    	= MSTAR_FIQ_HYP_BASE + 3,	
    E_FIQHYPL_USB31_HS_USB  	= MSTAR_FIQ_HYP_BASE + 4,
    E_FIQHYPL_USB30_HS_UHC  	= MSTAR_FIQ_HYP_BASE + 5,
    E_FIQHYPL_HST0TO5       	= MSTAR_FIQ_HYP_BASE + 6,
    E_FIQHYPL_HST5TO4       	= MSTAR_FIQ_HYP_BASE + 7,
    E_FIQHYPL_HST5TO3       	= MSTAR_FIQ_HYP_BASE + 8,
    E_FIQHYPL_HST5TO2       	= MSTAR_FIQ_HYP_BASE + 9,
    E_FIQHYPL_HST5TO1       	= MSTAR_FIQ_HYP_BASE + 10,
    E_FIQHYPL_HST5TO0       	= MSTAR_FIQ_HYP_BASE + 11,
    E_FIQHYPL_RESERVED76    	= MSTAR_FIQ_HYP_BASE + 12,
    E_FIQHYPL_RESERVED77    	= MSTAR_FIQ_HYP_BASE + 13,
    E_FIQHYPL_RESERVED78    	= MSTAR_FIQ_HYP_BASE + 14,
    E_FIQHYPL_RESERVED79    	= MSTAR_FIQ_HYP_BASE + 15,
    
    E_FIQHYPH_RESERVED80    	= MSTAR_FIQ_HYP_BASE + 16,
    E_FIQHYPH_RESERVED81    	= MSTAR_FIQ_HYP_BASE + 17,
    E_FIQHYPH_RESERVED82    	= MSTAR_FIQ_HYP_BASE + 18,
    E_FIQHYPH_RESERVED83    	= MSTAR_FIQ_HYP_BASE + 19,
    E_FIQHYPH_RESERVED84    	= MSTAR_FIQ_HYP_BASE + 20,
    E_FIQHYPH_RESERVED85    	= MSTAR_FIQ_HYP_BASE + 21,
    E_FIQHYPH_RESERVED86    	= MSTAR_FIQ_HYP_BASE + 22,
    E_FIQHYPH_RESERVED87    	= MSTAR_FIQ_HYP_BASE + 23,
    E_FIQHYPH_RESERVED88    	= MSTAR_FIQ_HYP_BASE + 24,	
    E_FIQHYPH_RESERVED89    	= MSTAR_FIQ_HYP_BASE + 25,
    E_FIQHYPH_RESERVED90    	= MSTAR_FIQ_HYP_BASE + 26,
    E_FIQHYPH_RESERVED91    	= MSTAR_FIQ_HYP_BASE + 27,
    E_FIQHYPH_RESERVED92    	= MSTAR_FIQ_HYP_BASE + 28,
    E_FIQHYPH_RESERVED93    	= MSTAR_FIQ_HYP_BASE + 29,
    E_FIQHYPH_RESERVED94    	= MSTAR_FIQ_HYP_BASE + 30,	
    E_FIQHYPH_FOSSILToSECR2  	= MSTAR_FIQ_HYP_BASE + 31,
    
    E_FIQSUPL_FOSSILToSEC51    	= MSTAR_FIQ_HYP_BASE + 32,
    E_FIQSUPL_FOSSILToDIAMOND   = MSTAR_FIQ_HYP_BASE + 33,
    E_FIQSUPL_DIAMONDToSECR2    = MSTAR_FIQ_HYP_BASE + 34,
    E_FIQSUPL_DIAMONDToSEC51    = MSTAR_FIQ_HYP_BASE + 35,
    E_FIQSUPL_DIAMONDToFOSSIL   = MSTAR_FIQ_HYP_BASE + 36,
    E_FIQSUPL_SECR2ToSEC51    	= MSTAR_FIQ_HYP_BASE + 37,
    E_FIQSUPL_SECR2ToFOSSIL    	= MSTAR_FIQ_HYP_BASE + 38,
    E_FIQSUPL_SECR2ToDIAMOND    = MSTAR_FIQ_HYP_BASE + 39,
    E_FIQSUPL_SEC51ToSECR2    	= MSTAR_FIQ_HYP_BASE + 40,
    E_FIQSUPL_SEC51ToFOSSIL    	= MSTAR_FIQ_HYP_BASE + 41,
    E_FIQSUPL_SEC51ToDIAMOND    = MSTAR_FIQ_HYP_BASE + 42,
    E_FIQSUPL_HST1To0    	= MSTAR_FIQ_HYP_BASE + 43,
    E_FIQSUPL_HST2To0    	= MSTAR_FIQ_HYP_BASE + 44,
    E_FIQSUPL_HST3To0    	= MSTAR_FIQ_HYP_BASE + 45,
    E_FIQSUPL_HST4To0    	= MSTAR_FIQ_HYP_BASE + 46,
    E_FIQSUPL_RESERVED111    	= MSTAR_FIQ_HYP_BASE + 47,
    
    E_FIQSUPH_RESERVED112    	= MSTAR_FIQ_HYP_BASE + 48,
    E_FIQSUPH_RESERVED113    	= MSTAR_FIQ_HYP_BASE + 49,
    E_FIQSUPH_RESERVED114    	= MSTAR_FIQ_HYP_BASE + 50,
    E_FIQSUPH_RESERVED115    	= MSTAR_FIQ_HYP_BASE + 51,
    E_FIQSUPH_RESERVED116    	= MSTAR_FIQ_HYP_BASE + 52,
    E_FIQSUPH_RESERVED117    	= MSTAR_FIQ_HYP_BASE + 53,
    E_FIQSUPH_RESERVED118    	= MSTAR_FIQ_HYP_BASE + 54,
    E_FIQSUPH_RESERVED119    	= MSTAR_FIQ_HYP_BASE + 55,
    E_FIQSUPH_RESERVED120    	= MSTAR_FIQ_HYP_BASE + 56,
    E_FIQSUPH_RESERVED121    	= MSTAR_FIQ_HYP_BASE + 57,
    E_FIQSUPH_RESERVED122    	= MSTAR_FIQ_HYP_BASE + 58,
    E_FIQSUPH_RESERVED123    	= MSTAR_FIQ_HYP_BASE + 59,
    E_FIQSUPH_RESERVED124    	= MSTAR_FIQ_HYP_BASE + 60,
    E_FIQSUPH_RESERVED125    	= MSTAR_FIQ_HYP_BASE + 61,
    E_FIQSUPH_RESERVED126    	= MSTAR_FIQ_HYP_BASE + 62,
    E_FIQSUPH_RESERVED127    	= MSTAR_FIQ_HYP_BASE + 63,

    E_IRQ_FIQ_ALL                       = 0xFF /* all IRQs & FIQs */
} InterruptNum;

/* for backward compatibility */
/* #define name_used_in_driver name_defined_here */
#define E_FIQ_VSYNC_VE4VBI	E_FIQ_VE_VBI_F0
#define E_IRQ_NFIE			E_IRQEXPH_FCIE
#define E_IRQEXPH_SDIO		E_IRQHYPH_SDIO
#define E_IRQ_PM_SLEEP		E_IRQ_PM

//array index is SPI number
extern unsigned int spi_to_ppi[NR_IRQS];

#define IRQL_EXP_ALL                    0xFFFF
#define IRQH_EXP_ALL                    0xFFFF
#define FIQL_EXP_ALL                    0xFFFF
#define FIQH_EXP_ALL                    0xFFFF


extern unsigned int interrupt_configs[MSTAR_CHIP_INT_END/16];

void init_chip_spi_config(void);

#endif // #ifndef __CHIP_INT_H__
