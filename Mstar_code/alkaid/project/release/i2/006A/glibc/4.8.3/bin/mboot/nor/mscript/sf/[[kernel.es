# <- this is for comment / total file size must be less than 4KB

mxp r.info KERNEL
sf probe 0
sf erase $(sf_part_start) $(sf_part_size)
tftp 0x21000000 kernel
sf write 0x21000000 $(sf_part_start) $(filesize)

# update kernel start address
setenv sf_kernel_start $(sf_part_start)
setenv sf_kernel_size $(sf_part_size)
setenv bootcmd ' sf probe 0;sf read 0x22000000 $(sf_kernel_start) $(sf_kernel_size);bootm 0x22000000
saveenv


% <- this is end of file symbol
