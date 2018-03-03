#include "hal_clk.h"
#include "mdrv_cwa.h"

#define BANK_TOP_RESET  (BANK_CAL(0x101e))
#define BANK_TOP_CLK    (BANK_CAL(0x112a))
#define BANK_WD_EN      (BANK_CAL(0x1410))
#define BANK_PLL        (BANK_CAL(0x162e))

#if (!DUMP_REGISTER)
#define REGR(base,idx)      ms_readw(((uint)base+(idx)*4))
#define REGW(base,idx,val)  ms_writew(val,((uint)base+(idx)*4))
#else
#define REGR(base,idx)      ms_readw(((uint)base+(idx)*4))
#define REGW(base,idx,val)  do{CWA_MSG(CWA_MSG_DBG, "write 0x%08X = 0x%04X\n", ((uint)base+(idx)*4), val); } while(0)
#endif

/*******************************************************************************************************************
 * clk_hal_init
 *   init device clock
 *
 * Parameters:
 *   RIU_BASE_ADDR:  clock base address
 *
 * Return:
 *   0: OK, othes: failed
 */
//<MStar Software>//CEVA PLL: 600MHz setting
int clk_hal_init(void)
{
    int err_state = 0;
    unsigned short reg_cevapll_pd = 0;

    reg_cevapll_pd = REGR(BANK_PLL, 0x11);
    reg_cevapll_pd = reg_cevapll_pd & 0x00ff;//& 0x00ff;

    REGW(BANK_PLL, 0x60, 0x978c);
    REGW(BANK_PLL, 0x61, 0x006e);
    REGW(BANK_PLL, 0x62, 0x0001);
    REGW(BANK_PLL, 0x11, reg_cevapll_pd);//0x0000);

    REGW(BANK_TOP_RESET, 0x24, 0x0005);//0x0007);

    REGW(BANK_TOP_CLK, 0x20, 0x0001);
    REGW(BANK_WD_EN, 0x50, 0x00c6);

#if (CHECK_REGISTER)
    CWA_MSG(CWA_MSG_WRN, "BANK_PLL: addr 0x%02X,  value 0x%08X\n", 0x60, 0x978c);
    CWA_MSG(CWA_MSG_WRN, "BANK_PLL: addr 0x%02X,  value 0x%08X\n", 0x61, 0x006e);
    CWA_MSG(CWA_MSG_WRN, "BANK_PLL: addr 0x%02X,  value 0x%08X\n", 0x62, 0x0001);
    CWA_MSG(CWA_MSG_WRN, "BANK_PLL: addr 0x%02X,  value 0x%08X\n", 0x11, reg_cevapll_pd);
    CWA_MSG(CWA_MSG_WRN, "BANK_TOP_RESET: addr 0x%02X,  value 0x%08X\n", 0x24, 0x0005);
    CWA_MSG(CWA_MSG_WRN, "BANK_TOP_CLK: addr 0x%02X,  value 0x%08X\n", 0x20, 0x0001);
    CWA_MSG(CWA_MSG_WRN, "BANK_WD_EN: addr 0x%02X,  value 0x%08X\n", 0x50, 0x00c6);
#endif

    return err_state;
}