/*
 * Copyright (C) 2015 Freescale Semiconductor, Inc.
 *
 * Configuration settings for the Freescale i.MX6UL 14x14 EVK board.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */
#ifndef __MX6UL_WIRENBOARD_CONFIG_H
#define __MX6UL_WIRENBOARD_CONFIG_H

#define CONFIG_MX6UL_14X14_EVK_EMMC_REWORK

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/imx-common/gpio.h>

/* SPL options */
#include "imx6_spl.h"

#define CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART1_BASE

/* MMC Configs */
#ifdef CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	USDHC2_BASE_ADDR

/* NAND pin conflicts with usdhc2 */
#ifdef CONFIG_NAND_MXS
#define CONFIG_SYS_FSL_USDHC_NUM	1
#else
#define CONFIG_SYS_FSL_USDHC_NUM	2
#endif

#endif

/* I2C configs */
#ifdef CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1		/* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2		/* enable I2C bus 2 */
#define CONFIG_SYS_I2C_SPEED		100000
#endif

/* Status LED */
#define CONFIG_CMD_LED

#define CONFIG_STATUS_LED
#define CONFIG_GPIO_LED
#define CONFIG_BOARD_SPECIFIC_LED
#define STATUS_LED_BOOT		1
#define STATUS_LED_BIT		1
#define STATUS_LED_STATE	STATUS_LED_ON
#define STATUS_LED_PERIOD	(CONFIG_SYS_HZ / 2)



#define CONFIG_SYS_MMC_IMG_LOAD_PART	1

#define CONFIG_EXTRA_ENV_SETTINGS \
	"console=ttymxc0\0" \
	"fdt_file=undefined\0" \
	"fdt_addr=0x83000000\0" \
	"ip_dyn=yes\0" \
	"videomode=video=ctfb:x:480,y:272,depth:24,pclk:108695,le:8,ri:4,up:2,lo:4,hs:41,vs:10,sync:0,vmode:0\0" \
	"mmcdev="__stringify(CONFIG_SYS_MMC_ENV_DEV)"\0" \
	"mmcpart=" __stringify(CONFIG_SYS_MMC_IMG_LOAD_PART) "\0" \
	"mmcargs=setenv bootargs console=${console},${baudrate} " \
		"${optargs} " \
		"root=/dev/mmcblk${mmcdev}p${mmcpart} rootwait ro \0" \
	"loadbootenv=load mmc ${mmcdev}:${mmcpart} ${loadaddr} /boot/uEnv.txt\0" \
	"importbootenv=echo Importing environment from mmc (uEnv.txt)...; " \
		"env import -t ${loadaddr} ${filesize}\0" \
	"loadzimage=load mmc ${mmcdev}:${mmcpart} ${loadaddr} /boot/zImage\0" \
	"loadfdt=load mmc ${mmcdev}:${mmcpart} ${fdt_addr} ${fdt_file}\0" \
	"mmcboot=echo Booting from mmc ...; " \
		"run mmcargs; " \
		"bootz ${loadaddr} - ${fdt_addr}\0" \
	"netargs=setenv bootargs console=${console},${baudrate} " \
		"${optargs} " \
		"root=/dev/nfs " \
		"ip=dhcp nfsroot=${serverip}:${nfsroot},v3,tcp\0" \
	"netboot=echo Booting from net ...; " \
		"run netargs; " \
		"tftp zImage; " \
		"if ${get_cmd} ${fdt_addr} ${fdt_file}; then " \
			"bootz ${loadaddr} - ${fdt_addr}; " \
		"else " \
			"bootz; " \
		"fi;\0" \
	"bootcount=0\0" \
	"bootlimit=3\0" \
	"upgrade_available=0\0" \
	"altbootcmd=if test ${mmcpart} -eq 2; then " \
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

/* Miscellaneous configurable options */
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x8000000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define CONFIG_CMDLINE_EDITING
#define CONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */
#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_SIZE			SZ_8K
#define CONFIG_ENV_IS_IN_MMC
#define CONFIG_ENV_OFFSET		(8 * SZ_64K)
#define CONFIG_SYS_MMC_ENV_DEV		0   /* USDHC2 */
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */

#define CONFIG_CMD_BMODE

#ifndef CONFIG_SYS_DCACHE_OFF
#endif

#ifdef CONFIG_FSL_QSPI
#define CONFIG_SF_DEFAULT_BUS		0
#define CONFIG_SF_DEFAULT_CS		0
#define CONFIG_SF_DEFAULT_SPEED	40000000
#define CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
#define FSL_QSPI_FLASH_NUM		1
#define FSL_QSPI_FLASH_SIZE		SZ_32M
#endif

/* USB Configs */
#ifdef CONFIG_CMD_USB
#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS   0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2



#define CONFIG_CI_UDC
#define CONFIG_USBD_HS
#define CONFIG_USB_GADGET_DUALSPEED

#define CONFIG_USB_GADGET
#define CONFIG_CMD_USB_MASS_STORAGE
#define CONFIG_USB_FUNCTION_MASS_STORAGE
#define CONFIG_USB_GADGET_DOWNLOAD
#define CONFIG_USB_GADGET_VBUS_DRAW 2

#define CONFIG_G_DNL_VENDOR_NUM     0x18d1
#define CONFIG_G_DNL_PRODUCT_NUM    0x0d02
#define CONFIG_G_DNL_MANUFACTURER   "FSL"



#endif

#ifdef CONFIG_CMD_NET
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define CONFIG_FEC_ENET_DEV		0

#if (CONFIG_FEC_ENET_DEV == 0)
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0
#define CONFIG_FEC_XCV_TYPE             RMII
#elif (CONFIG_FEC_ENET_DEV == 1)
#define IMX_FEC_BASE			ENET2_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR		0x1
#define CONFIG_FEC_XCV_TYPE		RMII
#endif
#define CONFIG_ETHPRIME			"FEC"

#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#endif

#define CONFIG_IMX_THERMAL

#ifndef CONFIG_SPL_BUILD
#ifdef CONFIG_VIDEO
#define CONFIG_VIDEO_MXS
#define CONFIG_VIDEO_LOGO
#define CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define CONFIG_CMD_BMP
#define CONFIG_BMP_16BPP
#define CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_LOGO
#define MXS_LCDIF_BASE MX6UL_LCDIF1_BASE_ADDR
#endif
#endif


#endif
