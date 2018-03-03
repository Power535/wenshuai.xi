#include <linux/types.h>

#ifndef _CHIP_SETUP_H_
#define _CHIP_SETUP_H_

#define ARM_MIU0_BASE              (0x80000000UL)
#define ARM_MIU1_BASE              (0xE0000000UL)
#define MIU1_BUS_BASE               (0xA0000000UL)
#define HIGH_MEM_BUS_BASE           (0x50000000UL)
#define HIGH_MEM_PHY_BASE           (0x10000000UL)
#define HIGH_MEM_MAX_BUS_ADDR       (0x80000000UL)
#define RIU_VIRT_BASE               mstar_pm_base 

#define SECOND_MAGIC_NUMBER_ADRESS	0xC0008000UL
#define SECOND_START_ADDR		0xC0008004UL

#define REG(addr) (*(volatile unsigned int *)(addr))

extern ptrdiff_t mstar_pm_base;

void* Chip_mphy_cachevirt( unsigned long mphyaddr );
void* Chip_mphy_noncachevirt( unsigned long mphyaddr );
unsigned long Chip_mphy_bus( unsigned long phyaddress );
unsigned long Chip_bus_mphy( unsigned long busaddress );

extern void _chip_flush_miu_pipe(void); //flush miu pipe
extern void Chip_Flush_Memory(void);  //flush miu pipe
extern void Chip_Read_Memory(void) ;  //flush miu pipe
extern void Chip_Flush_Memory_Range(unsigned long pAddress , unsigned long  size);  //flush miu pipe
extern void Chip_Read_Memory_Range(unsigned long pAddress , unsigned long  size ) ;  //flush miu pipe


extern void Chip_Flush_Cache_Range(unsigned long u32Addr, unsigned long u32Size); //Clean & Invalid L1/L2 cache
extern void Chip_Clean_Cache_Range(unsigned long u32Addr, unsigned long u32Size); //Clean L1/L2 cache, keep valid
extern void Chip_Inv_Cache_Range(unsigned long u32Addr, unsigned long u32Size);  //Invalid L1/L2 cache

extern void Chip_Flush_Cache_Range_VA_PA(unsigned long u32VAddr,unsigned long u32PAddr,unsigned long u32Size); //Clean & Invalid L1/L2 cache
extern void Chip_Clean_Cache_Range_VA_PA(unsigned long u32VAddr, unsigned long u32PAddr,unsigned long u32Size); //Clean L1/L2 cache, keep valid
extern void Chip_Inv_Cache_Range_VA_PA(unsigned long u32VAddr, unsigned long u32PAddr,unsigned long u32Size);  //Invalid L1/L2 cache
extern void Chip_Flush_Cache_All(void); //Clean & Invalid L1/L2 cache
extern void Chip_Flush_Cache_All_Single(void);

extern unsigned int Chip_Query_CLK(void);
extern unsigned int Chip_Query_Rev(void);
extern void Chip_Query_L2_Config(void);

#endif

