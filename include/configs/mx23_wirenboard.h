/*
 * Copyright (C) 2013 Marek Vasut <marex@denx.de>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIGS_MX23_WIRENBOARD4_H__
#define __CONFIGS_MX23_WIRENBOARD4_H__

/* System configurations */
#define CONFIG_MX23				/* i.MX23 SoC */
#define CONFIG_MACH_TYPE	4105

/* U-Boot Commands */
#define CONFIG_SYS_NO_FLASH
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DOS_PARTITION

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_GPIO
#define CONFIG_CMD_MMC
#define CONFIG_CMD_USB
#define CONFIG_CMD_FUSE

#define CONFIG_CMD_FS_GENERIC
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_FAT

/* bootz: zImage/initrd.img support */
#define CONFIG_CMD_BOOTZ
#define CONFIG_SUPPORT_RAW_INITRD

/* Memory configuration */
#define CONFIG_NR_DRAM_BANKS		1		/* 1 bank of DRAM */
#define PHYS_SDRAM_1			0x40000000	/* Base address */
#define PHYS_SDRAM_1_SIZE		0x08000000	/* Max 128 MB RAM */
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/* Environment */
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_OVERWRITE

/* Environment is in MMC */
#if defined(CONFIG_CMD_MMC) && defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(256 * 1024)
#define CONFIG_ENV_SIZE			(16 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV	0
#endif

/* Status LED */
#define CONFIG_CMD_LED

#define CONFIG_STATUS_LED
#define CONFIG_GPIO_LED
#define CONFIG_BOARD_SPECIFIC_LED
#define STATUS_LED_BOOT		1
#define STATUS_LED_BIT		MX23_PAD_SSP1_DETECT__GPIO_2_1
#define STATUS_LED_STATE	STATUS_LED_ON
#define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)

/* USB */
#ifdef CONFIG_CMD_USB
#define CONFIG_EHCI_MXS_PORT0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 1
#define CONFIG_USB_STORAGE
#endif

/* Ethernet */
#ifdef CONFIG_CMD_NET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_SMSC95XX
#define CONFIG_CMD_DHCP
#endif

/* Booting Linux */
#define CONFIG_BOOTDELAY	1
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_LOADADDR		0x42000000
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_ENV

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttyAMA0\0" \
	"fdt_file=/boot/dtbs/imx23-wirenboard41.dtb\0" \
	"fdt_addr=0x41000000\0" \
	"optargs=ro rootwait fixrtc\0" \
	"video=\0" \
	"mmcdev=" __stringify(CONFIG_SYS_MMC_ENV_DEV) "\0" \
	"mmcpart=2\0" \
	"mmcrootfstype=ext4\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"${optargs} " \
		"root=/dev/mmcblk0p${mmcpart} " \
		"rootfstype=${mmcrootfstype} " \
		"video=${video}\0" \
	"loadbootenv=load mmc ${mmcdev}:${mmcpart} ${loadaddr} /boot/uEnv.txt\0" \
	"importbootenv=echo Importing environment from mmc (uEnv.txt)...; " \
		"env import -t ${loadaddr} ${filesize}\0" \
	"loadzimage=load mmc ${mmcdev}:${mmcpart} ${loadaddr} /boot/zImage\0" \
	"loadfdt=load mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"bootz ${loadaddr} - ${fdt_addr}\0" \
	"bootcount=0\0" \
	"bootlimit=3\0" \
	"upgrade_available=1\0" \
	"altbootcmd=if test ${boot_part} -eq 2; then " \
			"echo Switching to rootfs on partition 3;" \
			"setenv mmcpart 3;" \
		"else; " \
			"echo Switching to rootfs on partition 2;" \
			"setenv mmcpart 2;" \
		"fi;" \
		"setenv bootcount 0;" \
		"saveenv; boot\0"

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev};" \
	"if mmc rescan; then " \
		"echo SD/MMC found on device ${mmcdev};" \
		"if run loadbootenv; then " \
			"run importbootenv;" \
		"fi;" \
		"echo Checking if uenvcmd is set ...;" \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...;" \
			"run uenvcmd;" \
		"fi;" \
		"echo Running default loadzimage ...;" \
		"if run loadzimage; then " \
			"run loadfdt;" \
			"run mmcboot;" \
		"fi;" \
	"fi;"

/* The rest of the configuration is shared */
#include <configs/mxs.h>

#endif /* __CONFIGS_MX23_WIRENBOARD4_H__ */
