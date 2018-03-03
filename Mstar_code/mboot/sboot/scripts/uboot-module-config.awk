# Copyright (c) 2008-2009 MStar Semiconductor, Inc.
# All rights reserved.
#
# AWK script to automatically generate uboot config file for module options

$2 == "ENABLE_COMPRESS" {print "#define ENABLE_MODULE_COMPRESS " $3}
$2 == "ENABLE_DONT_OVERWRITE" {print "#define ENABLE_MODULE_DONT_OVERWRITE " $3}
$2 == "ENABLE_USB" {print "#define ENABLE_MODULE_USB " $3}
$2 == "ENABLE_FAT" {print "#define ENABLE_MODULE_FAT " $3}
$2 == "ENABLE_USB_AUTO_UPDATE" {print "#define ENABLE_USB_AUTO_UPDATE " $3}
$2 == "ENABLE_BFN_WRITE_NAND" {print "#define ENABLE_MODULE_BFN_WRITE_NAND " $3}
$2 == "ENABLE_FLASH" {print "#define ENABLE_MODULE_FLASH " $3}
$2 == "ENABLE_FAT_WRITE" {print "#define ENABLE_MODULE_FAT_WRITE " $3}
$2 == "ENABLE_NAND_FLASH" {print "#define ENABLE_MODULE_NAND_FLASH " $3}
$2 == "ENABLE_SPI_NAND_FLASH" {print "#define ENABLE_MODULE_SPI_NAND_FLASH " $3}
$2 == "ENABLE_MMC" {print "#define ENABLE_MODULE_MMC " $3}
$2 == "ENABLE_SD" {print "#define ENABLE_MODULE_SD " $3}
$2 == "ENABLE_BFN_WRITE_NAND" {print "#define ENABLE_MODULE_BFN_WRITE_NAND " $3}
$2 == "ENABLE_UBI" {print "#define ENABLE_MODULE_UBI " $3}
$2 == "ENABLE_UBI_MLC_BACKUP_LSB" {print "#define ENABLE_MODULE_UBI_MLC_BACKUP_LSB " $3}
$2 == "ENABLE_UBI_FS" {print "#define ENABLE_MODULE_UBI_FS " $3}
$2 == "ENABLE_UBI_ENHANCE_INIT" {print "#define ENABLE_MODULE_UBI_ENHANCE_INIT " $3}
$2 == "ENABLE_ENV_IN_UBI" {print "#define ENABLE_MODULE_ENV_IN_UBI " $3}
$2 == "ENABLE_ENV_IN_NAND" {print "#define ENABLE_MODULE_ENV_IN_NAND " $3}
$2 == "ENABLE_ENV_IN_MMC" {print "#define ENABLE_MODULE_ENV_IN_MMC " $3}
$2 == "ENABLE_ENV_IN_SERIAL" {print "#define ENABLE_MODULE_ENV_IN_SERIAL " $3}
$2 == "ENABLE_SECURITY_BOOT" {print "#define ENABLE_MODULE_SECURITY_BOOT " $3}
$2 == "ENABLE_NET" {print "#define ENABLE_MODULE_NET " $3}
$2 == "ENABLE_LWIP" {print "#define ENABLE_MODULE_LWIP " $3}
$2 == "ENABLE_USB_LAN" {print "#define ENABLE_MODULE_USB_LAN " $3}
$2 == "ENABLE_SPI" {print "#define ENABLE_MODULE_SPI " $3}
$2 == "ENABLE_EEPROM" {print "#define ENABLE_MODULE_EEPROM " $3}
$2 == "ENABLE_KEYPAD" {print "#define ENABLE_MODULE_KEYPAD " $3}
$2 == "ENABLE_BOOT_KEYPAD" {print "#define ENABLE_MODULE_BOOT_KEYPAD " $3}
$2 == "ENABLE_STANDBY" {print "#define ENABLE_MODULE_STANDBY " $3}
$2 == "ENABLE_JFFS2" {print "#define ENABLE_MODULE_JFFS2 " $3}
$2 == "ENABLE_DISPLAY_LOGO" {print "#define ENABLE_MODULE_DISPLAY_LOGO " $3}
$2 == "ENABLE_DISPLAY_OSD" {print "#define ENABLE_MODULE_DISPLAY_OSD " $3}
$2 == "ENABLE_POWER_MUSIC" {print "#define ENABLE_MODULE_POWER_MUSIC " $3}
$2 == "ENABLE_PANEL_INIT" {print "#define ENABLE_MODULE_PANEL_INIT " $3}
$2 == "ENABLE_MICOM" {print "#define ENABLE_MODULE_MICOM " $3}
$2 == "ENABLE_FRONT_END" {print "#define ENABLE_MODULE_FRONT_END " $3}
$2 == "ENABLE_MSTAR_MSB123x_DEMOD" {print "#define ENABLE_MODULE_DEMOD_MSTAR_MSB123x " $3}
$2 == "ENABLE_MSTAR_MSB122x_DEMOD" {print "#define ENABLE_MODULE_DEMOD_MSTAR_MSB122x " $3}
$2 == "ENABLE_DIBCOM_DIB8096_DEMOD" {print "#define ENABLE_MODULE_DEMOD_DIBCOM_DIB8096 " $3}
$2 == "ENABLE_LGDT3305_DEMOD" {print "#define ENABLE_MODULE_DEMOD_LGDT3305 " $3}
$2 == "ENABLE_MSTAR_TUNER_NUTUNE_FT2125" {print "#define ENABLE_MODULE_TUNER_NUTUNE_FT2125 " $3}
$2 == "ENABLE_MSTAR_TUNER_NUTUNE_FJ2207" {print "#define ENABLE_MODULE_TUNER_NUTUNE_FJ2207 " $3}
$2 == "ENABLE_MSTAR_TUNER_DIBCOM_DIB8096" {print "#define ENABLE_MODULE_TUNER_DIBCOM_DIB8096 " $3}
$2 == "ENABLE_TDVG_TUNER_H252F" {print "#define ENABLE_MODULE_TUNER_TDVG_H252F " $3}
$2 == "ENABLE_DEMO_CODE" {print "#define ENABLE_MODULE_DEMO_CODE " $3}
$2 == "ENABLE_WDT_ENABLE" {print "#define ENABLE_MODULE_WDT_ENABLE " $3}
$2 == "ENABLE_MSTAR_NAND" {print "#define ENABLE_MODULE_MSTAR_NAND " $3}
$2 == "ENABLE_MSTAR_TUNER_NXP_CD1616LF" {print "#define ENABLE_MODULE_TUNER_NXP_CD1616LF " $3}
$2 == "ENABLE_MSTAR_TUNER_NXP_TD1611ALF" {print "#define ENABLE_MODULE_TUNER_NXP_TD1611ALF " $3}
$2 == "ENABLE_MSTAR_TUNER_MXL_MXL5007" {print "#define ENABLE_MODULE_TUNER_MXL_MXL5007 " $3}
$2 == "ENABLE_MSTAR_TUNER_MXL201RF" {print "#define ENABLE_MODULE_TUNER_MXL201RF " $3}
$2 == "ENABLE_MSTAR_URANUS4_INTERNAL_DEMOD" {print "#define ENABLE_MODULE_DEMOD_URANUS4_INTERNAL " $3}
$2 == "ENABLE_MSTAR_KRONUS_INTERNAL_DEMOD" {print "#define ENABLE_MODULE_DEMOD_KRONUS_INTERNAL " $3}
$2 == "ENABLE_MSTAR_KAISERIN_INTERNAL_DEMOD" {print "#define ENABLE_MODULE_DEMOD_KAISERIN_INTERNAL " $3}
$2 == "ENABLE_MSTAR_KAPPA_INTERNAL_DEMOD" {print "#define ENABLE_MODULE_DEMOD_KAPPA_INTERNAL " $3}
$2 == "ENABLE_MSTAR_KRITI_INTERNAL_DEMOD" {print "#define ENABLE_MODULE_DEMOD_KRITI_INTERNAL " $3}
$2 == "ENABLE_OAD" {print "#define ENABLE_MODULE_OAD " $3}
$2 == "ENABLE_NETUPDATE" {print "#define ENABLE_MODULE_NETUPDATE " $3}
$2 == "ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51" {print "#define ENABLE_BOOTING_FROM_EXT_SPI_WITH_PM51 " $3}
$2 == "ENABLE_INFO_IN_SERIAL_ENV" {print "#define ENABLE_MODULE_INFO_IN_SERIAL_ENV " $3}
$2 == "ENABLE_INFO_IN_MMC_ENV" {print "#define ENABLE_MODULE_INFO_IN_MMC_ENV " $3}
$2 == "ENABLE_INFO_IN_UBI_FILE" {print "#define ENABLE_MODULE_INFO_IN_UBI_FILE " $3}
$2 == "ENABLE_ANDROID_BOOT" {print "#define ENABLE_MODULE_ANDROID_BOOT " $3}
$2 == "ENABLE_IR" {print "#define ENABLE_MODULE_IR " $3}
$2 == "ENABLE_BOOT_IR" {print "#define ENABLE_MODULE_BOOT_IR " $3}
$2 == "ENABLE_MSTARI2C" {print "#define ENABLE_MODULE_MSTARI2C " $3}
$2 == "ENABLE_LOAD_ENV_FROM_SN" {print "#define ENABLE_MODULE_LOAD_ENV_FROM_SN " $3}
$2 == "ENABLE_ENABLE_EEPROM" {print "#define ENABLE_MODULE_EEPROM " $3}
$2 == "ENABLE_ACTIVE_ACTIVE_STANDBY" {print "#define ENABLE_MODULE_ACTIVE_STANDBY " $3}
$2 == "ENABLE_USE_EMAC" {print "#define ENABLE_MODULE_USE_EMAC " $3}
$2 == "ENABLE_USE_GMAC" {print "#define ENABLE_MODULE_USE_GMAC " $3}
$2 == "ENABLE_TEE" {print "#define ENABLE_MODULE_TEE " $3}

