/*
 * Board specific MUX configuration file.
 *
 * Copyright (C) 2011 LG Electronics Inc.
 *
 * Author: Seungho Park <seungho1.park@lge.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 */

#include <linux/gpio.h>
#include <mach-omap2/control.h>
#include <lge/common.h>
#include <lge/board.h>
#include <lge/board_rev.h>

#ifdef CONFIG_OMAP_MUX
static struct omap_board_mux board_mux[] __initdata = {
#if 0
	/* wifi pads setting */ 
	OMAP4_MUX(SDMMC5_CMD, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	OMAP4_MUX(SDMMC5_CLK, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	OMAP4_MUX(SDMMC5_DAT0, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	OMAP4_MUX(SDMMC5_DAT1, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	OMAP4_MUX(SDMMC5_DAT2, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
	OMAP4_MUX(SDMMC5_DAT3, OMAP_MUX_MODE0 | OMAP_PIN_INPUT_PULLUP),
#endif

/* LGE_SJIT_S 2011-12-23 [jongrak.kwon@lge.com] Disable Pull UP due to H/W Pull Up */
	OMAP4_MUX(I2C1_SCL, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C1_SDA, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C2_SCL, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C2_SDA, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C3_SCL, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C3_SDA, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C4_SCL, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
	OMAP4_MUX(I2C4_SDA, OMAP_PIN_INPUT | OMAP_MUX_MODE0),
/* LGE_SJIT_E 2011-12-23 [jongrak.kwon@lge.com] Disable Pull UP due to H/W Pull Up */
	{ .reg_offset = OMAP_MUX_TERMINATOR },
};
#else
#define board_mux	NULL
#endif

static struct lge_mux_gpio_info mux_gpios[] __initdata = {
// LGE_SJIT_S 09/28/2011 [mohamed.khadri@lge.com] GPS GPIO configuration
#if defined(CONFIG_GPS)
	LGE_MUX_GPIO(GPS_PWR_ON_GPIO, OMAP_PIN_OUTPUT),
	// LGE_SJIT 01/26/2012 [mohamed.khadri@lge.com] Configure for pull up as suggested in BCM47511 Pinouts
	LGE_MUX_GPIO(GPS_RESET_N_GPIO, OMAP_PIN_OUTPUT | OMAP_PIN_OFF_OUTPUT_HIGH),
#if defined(CONFIG_P940_GPS_LNA_SD_USE)
	LGE_MUX_GPIO(GPS_LNA_SD_GPIO, OMAP_PIN_OUTPUT),
#endif  /* CONFIG_P940_GPS_LNA_SD_USE */
#endif /* CONFIG_GPS */
// LGE_SJIT_E 09/28/2011 [mohamed.khadri@lge.com] GPS GPIO configuration

/* LGE_SJIT_S 2011-12-23 [jongrak.kwon@lge.com] Correct mux setting to optimize standby current */
	LGE_MUX_GPIO(GPIO_MHL_INT, OMAP_PIN_INPUT),
	LGE_MUX_GPIO(GPIO_IFX_USB_VBUS_EN, OMAP_PIN_OUTPUT),
	LGE_MUX_GPIO(GPIO_FRONT_KEY_LED_EN, OMAP_PIN_OUTPUT | OMAP_PIN_OFF_OUTPUT_LOW),
	LGE_MUX_GPIO(GPIO_CHG_STATUS_N, OMAP_PIN_INPUT),
	LGE_MUX_GPIO(GPIO_CAM_SUBPM_EN, OMAP_PIN_OUTPUT | OMAP_PIN_OFF_OUTPUT_LOW),
	LGE_MUX_GPIO(GPIO_MUIC_INT, OMAP_PIN_INPUT),
	LGE_MUX_GPIO(GPIO_RESET_PMU_N, OMAP_PIN_OUTPUT),
	LGE_MUX_GPIO(GPIO_PROXI_INT, OMAP_PIN_INPUT | OMAP_WAKEUP_EN),
	LGE_MUX_GPIO(GPIO_LCD_POWER_EN, OMAP_PIN_OUTPUT | OMAP_PIN_OFF_OUTPUT_LOW),
	LGE_MUX_GPIO(GPIO_TOUCH_IRQ, OMAP_PIN_INPUT),
/* LGE_SJIT_E 2011-12-23 [jongrak.kwon@lge.com] Correct mux setting to optimize standby current */

	{ .gpio = LGE_MUX_GPIO_TERMINATOR },
};

int __init p720_mux_init(void)
{
	lge_set_mux_gpios(mux_gpios);
	lge_set_mux_info(board_mux);
	
	return 0;
}
lge_machine_initcall(p720_mux_init);

/* LGE_SJIT_S 2012-01-17 [jongrak.kwon] Apply patch for NFC_MODE mux setting */
static __init int p720_nfc_gpio_init(void)
{
	/*
	 * Bootloader sets both gpio 42 and gpio 49 to output for NFC_MODE
	 * Resetting the gpio42 and 49 to reduce suspend power consumption
	 */
#if 0
	if (system_rev <= LGE_PCB_1_0)
	{
		/* Set HALL_INT gpio_42 (unused) until revision 1.0 */
		omap_mux_init_signal("gpmc_a18.safe_mode", OMAP_PIN_INPUT);
	}
	else
	{
		/* Set gpio 49 unused from revision 1.1 */
		omap_mux_init_signal("gpmc_a25.safe_mode", 0);
	}
#endif
	return 0;
}
arch_initcall(p720_nfc_gpio_init);
/* LGE_SJIT_E 2012-01-17 [jongrak.kwon] Apply patch from GB c79469ae2c8ac0c6aa1b66112425462140b59bb6 */
