/*
 * (C) Copyright 2011 Freescale Semiconductor, Inc.
 * Author: Fabio Estevam <fabio.estevam@freescale.com>
 *
 * Based on m28evk.h:
 * Copyright (C) 2011 Marek Vasut <marek.vasut@gmail.com>
 * on behalf of DENX Software Engineering GmbH
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __CONFIGS_MX28_WIRENBOARD_H__
#define __CONFIGS_MX28_WIRENBOARD_H__

/* System configurations */
#define CONFIG_MX28				/* i.MX28 SoC */
#define CONFIG_MACH_TYPE	MACH_TYPE_MX28EVK

/* U-Boot Commands */
#define CONFIG_SYS_NO_FLASH
#define CONFIG_DISPLAY_CPUINFO
#define CONFIG_DOS_PARTITION

#define CONFIG_CMD_CACHE
#define CONFIG_CMD_GPIO
#define CONFIG_CMD_MMC
#define CONFIG_CMD_USB
#define CONFIG_CMD_FUSE
#define CONFIG_CMD_DATE

#define CONFIG_CMD_FS_GENERIC
#define CONFIG_CMD_EXT4
#define CONFIG_CMD_FAT

/* bootz: zImage/initrd.img support */
#define CONFIG_CMD_BOOTZ
#define CONFIG_SUPPORT_RAW_INITRD

/* Memory configuration */
#define CONFIG_NR_DRAM_BANKS		1		/* 1 bank of DRAM */
#define PHYS_SDRAM_1			0x40000000	/* Base address */
#define PHYS_SDRAM_1_SIZE		0x40000000	/* Max 1 GB RAM */
#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM_1

/* Environment */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_ENV_SIZE			(16 * 1024)

/* Environment is in MMC */
#if defined(CONFIG_CMD_MMC) && defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(256 * 1024)
#define CONFIG_SYS_MMC_ENV_DEV	0
#endif

/* FEC Ethernet on SoC */
#ifdef	CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_NET_MULTI
#define CONFIG_MX28_FEC_MAC_IN_OCOTP
#define CONFIG_CMD_MII
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#endif

/* RTC */
#ifdef	CONFIG_CMD_DATE
#define	CONFIG_RTC_MXS
#endif

/* USB */
#ifdef	CONFIG_CMD_USB
/* #define CONFIG_EHCI_MXS_PORT1 */
#define CONFIG_EHCI_MXS_PORT0
#define CONFIG_USB_MAX_CONTROLLER_COUNT	1
#endif


#define CONFIG_SYS_CACHELINE_SIZE 16

/* USB gadget, and mass storage protocol */
#define CONFIG_USB_MAX_CONTROLLER_COUNT        1
/* Disable USB host */

#define CONFIG_CI_UDC          /* ChipIdea CI13xxx UDC */
#define CONFIG_USB_REG_BASE    0x80080000
#define CONFIG_USB_GADGET_DUALSPEED

#define CONFIG_CMD_USB_MASS_STORAGE
#define CONFIG_USB_GADGET
#define CONFIG_USB_GADGET_MASS_STORAGE

#define CONFIG_USB_ETHER
#define CONFIG_USB_ETH_RNDIS
#define CONFIG_USBNET_HOST_ADDR	"de:ad:be:af:00:00"


#define CONFIG_USBDOWNLOAD_GADGET

#define CONFIG_USB_GADGET_VBUS_DRAW    2

#define CONFIG_G_DNL_VENDOR_NUM 0x0525
#define CONFIG_G_DNL_PRODUCT_NUM 0xa4a5
#define CONFIG_G_DNL_MANUFACTURER "Contactlesss Devices"

/*
#define CONFIG_CMD_DFU
#define CONFIG_DFU_FUNCTION
#define CONFIG_DFU_MMC
*/

/* Status LED */
#define CONFIG_CMD_LED

#define CONFIG_STATUS_LED
#define CONFIG_GPIO_LED
#define CONFIG_BOARD_SPECIFIC_LED
#define STATUS_LED_BOOT		1
#define STATUS_LED_BIT		MX28_PAD_SAIF1_SDATA0__GPIO_3_26
#define STATUS_LED_STATE	STATUS_LED_ON
#define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)




/* Booting Linux */
#define CONFIG_BOOTDELAY	1
#define CONFIG_BOOTFILE		"uImage"
#define CONFIG_LOADADDR		0x42000000
#define CONFIG_SYS_LOAD_ADDR	CONFIG_LOADADDR

#ifndef CONFIG_BOOT_USBGADGET
#define CONFIG_BOOTCOUNT_LIMIT
#define CONFIG_BOOTCOUNT_ENV
#endif

/* Extra Environment */
#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttyAMA0\0" \
	"fdt_file=/boot/dtbs/imx28-wirenboard52.dtb\0" \
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

#ifdef CONFIG_BOOT_USBGADGET
#define CONFIG_BOOTCOMMAND \
	"setenv bootargs \"console=ttyAMA0,115200\";" \
		"bootz"
	/*"setenv ipaddr 192.168.0.34; " \
	"setenv serverip 192.168.0.1; " \
	"setenv bootargs \"console=ttyAMA0,115200 video= g_mass_storage.file=/dev/mmcblk0 " \
		"root=/dev/nfs nfsroot=${serverip}:/var/nfs/wb_debian,vers=3 rw " \
		"ip=${ipaddr}:${serverip}:${serverip}:255.255.255.0:ev_imx287:eth0:off\"; " \
		"bootz"*/
#else
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
#endif
/* The rest of the configuration is shared */
#include <configs/mxs.h>

#endif /* __CONFIGS_MX28_WIRENBOARD_H__ */
