# <- this is for comment / total file size must be less than 4KB

#fatload mmc 0 0x44000000 uImage
#setenv mtdparts=nand0:0x60000@0x140000(IPL0),0x60000(IPL1),0x60000(IPL_CUST0),0x60000(IPL_CUST1),0xC0000(UBOOT0),0xC0000(UBOOT1),0x60000(ENV),0x340000(KERNEL),0x340000(RECOVERY),-(UBI)

tftp 0x21000000 IPL.bin
nand erase.part IPL0
nand erase.part IPL1
nand write.e 0x21000000 IPL0 $(filesize)
nand write.e 0x21000000 IPL1 $(filesize)

#tftp 0x21000000 IPL_CUST.bin
#nand erase.part IPL_CUST0
#nand erase.part IPL_CUST1
#nand write.e 0x21000000 IPL_CUST0 $(filesize)
#nand write.e 0x21000000 IPL_CUST1 $(filesize)

% <- this is end of file symbol
