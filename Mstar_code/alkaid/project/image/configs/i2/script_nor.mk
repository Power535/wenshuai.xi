TFTPDOWNLOADADDR:=0x21000000
KERNELBOOTADDR:=0x22000000

TARGET_SCRIPT:=$(foreach n,$(IMAGE_LIST),$(n)_$(PAT_TABLE)_$(FLASH_TYPE)_$($(n)$(FSTYPE))_script) $(PAT_TABLE)_$(FLASH_TYPE)_partition_script $(PAT_TABLE)_$(FLASH_TYPE)_config_script

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

#for spi nor flash kernel.
%_spi_nor__script:
	@echo tftp $(TFTPDOWNLOADADDR) $(patsubst %_spi_nor__script,%,$@) > $(SCRIPTDIR)/[[$(patsubst %_spi_nor__script,%,$@)
	@echo spi wrc.p $(TFTPDOWNLOADADDR) $(patsubst %_spi_nor__script,%,$@) 0 \$${filesize} >> $(SCRIPTDIR)/[[$(patsubst %_spi_nor__script,%,$@)
	@echo setenv bootcmd spi rdc.p 0x205FFFC0 $(patsubst %_spi_nor__script,%,$@) 0 $(kernel$(PATSIZE)) \\\; bootm $(KERNELBOOTADDR) >> $(SCRIPTDIR)/[[$(patsubst %_spi_nor__script,%,$@)
	@echo saveenv >> $(SCRIPTDIR)/[[$(patsubst %_spi_nor__script,%,$@)

%_spi_nor_squashfs_script:
	@echo tftp $(TFTPDOWNLOADADDR) $(patsubst %_spi_nor_squashfs_script,%,$@).sqfs > $(SCRIPTDIR)/[[$(patsubst %_spi_nor_squashfs_script,%,$@)
	@echo spi wrc.p $(TFTPDOWNLOADADDR) $(patsubst %_spi_nor_squashfs_script,%,$@) 0 \$${filesize} >> $(SCRIPTDIR)/[[$(patsubst %_spi_nor_squashfs_script,%,$@)

%_spi_nor_jffs2_script:
	@echo tftp $(TFTPDOWNLOADADDR) $(patsubst %_spi_nor_jffs2_script,%,$@).jffs2 > $(SCRIPTDIR)/[[$(patsubst %_spi_nor_jffs2_script,%,$@)
	@echo spi wrc.p $(TFTPDOWNLOADADDR) $(patsubst %_spi_nor_jffs2_script,%,$@) 0 \$${filesize} >> $(SCRIPTDIR)/[[$(patsubst %_spi_nor_jffs2_script,%,$@)

spi_nor_partition_script:
	@echo setenv mtdparts > $(SCRIPTDIR)/set_partition
	@echo saveenv >> $(SCRIPTDIR)/set_partition
	@echo spi rmgpt >> $(SCRIPTDIR)/set_partition
	@echo spi create kernel $(kernel$(PATSIZE)) >> $(SCRIPTDIR)/set_partition
	@echo spi create rootfs $(rootfs$(PATSIZE)) >> $(SCRIPTDIR)/set_partition
	@echo spi create nvrservice $(nvrservice$(PATSIZE)) >> $(SCRIPTDIR)/set_partition
	@echo saveenv >> $(SCRIPTDIR)/set_partition

spi_nor_config_script:
	@echo setenv bootargs console=ttyS0,115200 $(rootfs$(BOOTENV)) $(kernel$(BOOTENV)) $(EXBOOTARGS) > $(SCRIPTDIR)/set_config
	@echo saveenv >> $(SCRIPTDIR)/set_config
	@echo reset >> $(SCRIPTDIR)/set_config
