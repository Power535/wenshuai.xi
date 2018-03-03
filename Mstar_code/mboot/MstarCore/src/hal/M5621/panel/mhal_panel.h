
#ifndef __MHAL_PANEL_H__
#define __MHAL_PANEL_H__

//LINK_TTL
#define PANEL_LINK_TTL_CFG0_7     0x0000
#define PANEL_LINK_TTL_CFG8_15    0x0000
#define PANEL_LINK_TTL_CFG16_21   0x0000
//LINK_LVDS
#define PANEL_LINK_LVDS_CFG0_7     0x5550
#define PANEL_LINK_LVDS_CFG8_15    0x0555
#define PANEL_LINK_LVDS_CFG16_21   0x0000
//LINK_EXT_8LANE
#if (ENABLE_MSTAR_BD_MST253A_D01A_S_MAXIM ==1 || ENABLE_MSTAR_BD_MST108B_X_X_MAXIM ==1 || ENABLE_MSTAR_BD_MST110B_20AUYGO_16183_MAXIM ==1 || ENABLE_MSTAR_BD_MST110B_20AUYGO_16183_MAXIM_23p5 ==1 || ((ENABLE_MSTAR_BD_MST111D_X_X_MAXIM == 1) && (ENABLE_TV_HDMITX_MSTAR == 0)))
#define PANEL_LINK_EXT_8LANE_CFG0_7     0x5500
#define PANEL_LINK_EXT_8LANE_CFG8_15    0x0055
#define PANEL_LINK_EXT_8LANE_CFG16_21   0x0000
#else
#define PANEL_LINK_EXT_8LANE_CFG0_7     0x5555
#define PANEL_LINK_EXT_8LANE_CFG8_15    0x0000
#define PANEL_LINK_EXT_8LANE_CFG16_21   0x0000
#endif

//LINK_EXT_16LANE
#define PANEL_LINK_EXT_16LANE_CFG0_7    0x5555
#define PANEL_LINK_EXT_16LANE_CFG8_15   0x5555
#define PANEL_LINK_EXT_16LANE_CFG16_21  0x0000
//LINK_EXT_4LANE
#define PANEL_LINK_EXT_4LANE_CFG0_7     0x0055
#define PANEL_LINK_EXT_4LANE_CFG8_15    0x0055
#define PANEL_LINK_EXT_4LANE_CFG16_21   0x0000
//LINK_EXT_2LANE
#define PANEL_LINK_EXT_2LANE_CFG0_7     0x0005
#define PANEL_LINK_EXT_2LANE_CFG8_15    0x0000
#define PANEL_LINK_EXT_2LANE_CFG16_21   0x0000
//LINK_EXT_1LANE
#define PANEL_LINK_EXT_1LANE_CFG0_7     0x0101
#define PANEL_LINK_EXT_1LANE_CFG8_15    0x0000
#define PANEL_LINK_EXT_1LANE_CFG16_21   0x0000

#endif //__MHAL_PANEL_H__