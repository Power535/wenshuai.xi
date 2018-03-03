TFTPDOWNLOADADDR:=0x21000000
KERNELBOOTADDR:=0x22000000

TARGET_SCRIPT:=$(foreach n,$(IMAGE_LIST),$(n)_$(PAT_TABLE)_$($(n)$(FSTYPE))_script) $(PAT_TABLE)_partition_script $(PAT_TABLE)_config_script

TARGET_FS:=$(filter-out $(patsubst %_fs__,%,$(filter %_fs__, $(foreach n,$(IMAGE_LIST),$(n)_fs_$($(n)$(FSTYPE))_))), $(IMAGE_LIST))

SCRIPTDIR:=$(IMAGEDIR)/scripts

scripts:
	mkdir -p $(SCRIPTDIR) 
	$(MAKE) $(TARGET_SCRIPT)
	@echo mstar scripts/set_partition > $(IMAGEDIR)/auto_update.txt
	@echo -e $(foreach n,$(IMAGE_LIST),\\n#$(n)\\nmstar scripts/[[$(n)\\n) >> $(IMAGEDIR)/auto_update.txt
	@echo mstar scripts/set_config >> $(IMAGEDIR)/auto_update.txt
	@echo saveenv >> $(IMAGEDIR)/auto_update.txt
	@echo printenv >> $(IMAGEDIR)/auto_update.txt
	@echo reset >> $(IMAGEDIR)/auto_update.txt

%_ubi_ubifs_script:
	@echo ubi part UBI > $(SCRIPTDIR)/[[$(patsubst %_ubi_ubifs_script,%,$@)
	@echo tftp $(TFTPDOWNLOADADDR) $(patsubst %_ubi_ubifs_script,%,$@).ubifs >> $(SCRIPTDIR)/[[$(patsubst %_ubi_ubifs_script,%,$@)
	@echo ubi write $(TFTPDOWNLOADADDR) $(patsubst %_ubi_ubifs_script,%,$@) \$${filesize} >> $(SCRIPTDIR)/[[$(patsubst %_ubi_ubifs_script,%,$@)
	@echo setenv $(patsubst %_ubi_ubifs_script,%,$@)$(BOOTENV) $($(patsubst %_ubi_ubifs_script,%,$@)$(BOOTENV)) >> $(SCRIPTDIR)/[[$(patsubst %_ubi_ubifs_script,%,$@)

%_ubi__script:
	@echo tftp $(TFTPDOWNLOADADDR) $(patsubst %_ubi__script,%,$@) > $(SCRIPTDIR)/[[$(patsubst %_ubi__script,%,$@)
	@echo nand erase $(patsubst %_ubi__script,%,$@) >> $(SCRIPTDIR)/[[$(patsubst %_ubi__script,%,$@)
	@echo nand write.e $(TFTPDOWNLOADADDR) $(patsubst %_ubi__script,%,$@) \$${filesize} >> $(SCRIPTDIR)/[[$(patsubst %_ubi__script,%,$@)
	@echo setenv $(patsubst %_ubi__script,%,$@)$(BOOTENV) $($(patsubst %_ubi__script,%,$@)$(BOOTENV)) >> $(SCRIPTDIR)/[[$(patsubst %_ubi__script,%,$@)

%_spi_squashfs_script:

%_mmc_ext4_script:

kernel_spi__script:
	@echo tftp $(TFTPDOWNLOADADDR) KERNEL > $(SCRIPTDIR)/[[kernel
	@echo nand erase KERNEL >> $(SCRIPTDIR)/[[kernel
	@echo nand write.e $(TFTPDOWNLOADADDR) KERNEL \$${filesize} >> $(SCRIPTDIR)/[[kernel
	@echo setenv kernel_bootenv $(kernel$(BOOTENV)) >> $(SCRIPTDIR)/[[kernel
	@echo saveenv >> $(SCRIPTDIR)/[[kernel

rootfs_spi_squashfs_script:
	@echo tftp $(TFTPDOWNLOADADDR) rootfs.sqfs > $(SCRIPTDIR)/[[rootfs
	@echo nand erase rootfs >> $(SCRIPTDIR)/[[rootfs
	@echo nand write.e $(TFTPDOWNLOADADDR) rootfs \$${filesize} >> $(SCRIPTDIR)/[[rootfs
	@echo setenv rootfs_bootenv $(rootfs$(BOOTENV)) >> $(SCRIPTDIR)/[[rootfs
	@echo saveenv >> $(SCRIPTDIR)/[[rootfs

nvrservice_spi_squashfs_script:
	@echo tftp $(TFTPDOWNLOADADDR) nvrservice.sqfs > $(SCRIPTDIR)/[[nvrservice
	@echo nand erase nvrservice >> $(SCRIPTDIR)/[[nvrservice
	@echo nand write.e $(TFTPDOWNLOADADDR) nvrservice \$${filesize} >> $(SCRIPTDIR)/[[nvrservice
	@echo saveenv >> $(SCRIPTDIR)/[[nvrservice

nvrservice_spi_ubifs_script:
	@echo ubi part UBI > $(SCRIPTDIR)/[[nvrservice
	@echo tftp $(TFTPDOWNLOADADDR) nvrservice.ubifs >> $(SCRIPTDIR)/[[nvrservice
	@echo ubi write $(TFTPDOWNLOADADDR) nvrservice \$${filesize} >> $(SCRIPTDIR)/[[nvrservice
	@echo saveenv >> $(SCRIPTDIR)/[[nvrservice

vendor_spi_ubifs_script:
	@echo ubi part UBI > $(SCRIPTDIR)/[[vendor
	@echo tftp $(TFTPDOWNLOADADDR) vendor.ubifs >> $(SCRIPTDIR)/[[vendor
	@echo ubi write $(TFTPDOWNLOADADDR) vendor \$${filesize} >> $(SCRIPTDIR)/[[vendor
	@echo saveenv >> $(SCRIPTDIR)/[[vendor

customer_spi_ubifs_script:
	@echo ubi part UBI > $(SCRIPTDIR)/[[customer
	@echo tftp $(TFTPDOWNLOADADDR) customer.ubifs >> $(SCRIPTDIR)/[[customer
	@echo ubi write $(TFTPDOWNLOADADDR) customer \$${filesize} >> $(SCRIPTDIR)/[[customer
	@echo saveenv >> $(SCRIPTDIR)/[[customer


ubi_partition_script:
	@echo nand erase.chip > $(SCRIPTDIR)/set_partition
	@echo "dynpart edb64M-nand:$(kernel$(PATSIZE))(kernel),-(UBI)" >> $(SCRIPTDIR)/set_partition
	@echo ubi part UBI >> $(SCRIPTDIR)/set_partition
	@echo saveenv >> $(SCRIPTDIR)/set_partition
	@echo -e $(foreach n,$(TARGET_FS),\\n#$(n)\\nubi create $(n) $($(n)$(PATSIZE))\\n) >> $(SCRIPTDIR)/set_partition

ubi_config_script:
	@echo setenv bootargs \' $(rootfs$(BOOTENV)) $(kernel$(BOOTENV)) $(EXBOOTARGS) > $(SCRIPTDIR)/set_config
	@echo setenv bootcmd \' nand read.e $(KERNELBOOTADDR) KERNEL $(kernel$(PATSIZE))\; bootm $(KERNELBOOTADDR)\;nand read.e $(KERNELBOOTADDR) RECOVERY $(kernel$(PATSIZE))\; bootm $(KERNELBOOTADDR) >> $(SCRIPTDIR)/set_config
	@echo saveenv >> $(SCRIPTDIR)/set_config
	@echo reset >> $(SCRIPTDIR)/set_config

spi_partition_script:
	@echo nand erase.chip > $(SCRIPTDIR)/set_partition
	@echo "dynpart edb64M-nand:$(kernel$(PATSIZE))(kernel),$(rootfs$(PATSIZE))(rootfs),-(UBI)" >> $(SCRIPTDIR)/set_partition
	@echo ubi part UBI >> $(SCRIPTDIR)/set_partition
	@echo saveenv >> $(SCRIPTDIR)/set_partition
	@echo ubi create nvrservice $(nvrservice$(PATSIZE)) >> $(SCRIPTDIR)/set_partition
	@echo ubi create vendor $(vendor$(PATSIZE)) >> $(SCRIPTDIR)/set_partition
	@echo ubi create customer $(customer$(PATSIZE)) >> $(SCRIPTDIR)/set_partition
	@echo saveenv >> $(SCRIPTDIR)/set_partition

spi_config_script:
	@echo setenv bootargs \' $(rootfs$(BOOTENV)) $(kernel$(BOOTENV)) $(EXBOOTARGS) > $(SCRIPTDIR)/set_config
	@echo setenv bootcmd \' nand read.e $(KERNELBOOTADDR) KERNEL $(kernel$(PATSIZE))\; bootm $(KERNELBOOTADDR)\;nand read.e $(KERNELBOOTADDR) RECOVERY $(kernel$(PATSIZE))\; bootm $(KERNELBOOTADDR) >> $(SCRIPTDIR)/set_config
	@echo saveenv >> $(SCRIPTDIR)/set_config
	@echo reset >> $(SCRIPTDIR)/set_config

mmc_partition_script:

mmc_config_script: