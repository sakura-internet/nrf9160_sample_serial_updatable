/*
 * Copyright (c) 2016 Intel Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/led.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, CONFIG_LOG_DEFAULT_LEVEL);

/* The devicetree node identifier for the "led0" alias. */
#if DT_NODE_HAS_STATUS(DT_INST(0, pwm_leds), okay)
#define LED_PWM_NODE_ID		DT_INST(0, pwm_leds)
#define LED_PWM_DEV_NAME	DEVICE_DT_NAME(LED_PWM_NODE_ID)
#else
#error "No LED PWM device found"
#endif

#define LED_PWM_LABEL(led_node_id) DT_PROP_OR(led_node_id, label, NULL),

const char *led_label[] = {
	DT_FOREACH_CHILD(LED_PWM_NODE_ID, LED_PWM_LABEL)
};

const int num_leds = ARRAY_SIZE(led_label);

#define LED_PTN_TICK_PAR_MS		(10)
#define LED_PTN_TICK_MAX		(200)
#define LED_PTN_TICK_TERM		(255)
typedef struct {
	uint8_t tick;
	uint8_t brightness;
} led_ptn;

led_ptn led_a_ptn[] = {
	{0, 0,},
	{10, 10},
	{20, 20},
	{30, 30},
	{40, 40},
	{50, 50},
	{60, 40},
	{70, 30},
	{80, 20},
	{90, 10},
	{100, 0},
	{LED_PTN_TICK_TERM, 0}
};

void main(void)
{
	const struct device *dev;

	dev = device_get_binding(LED_PWM_DEV_NAME);
	if (dev == NULL) {
		LOG_ERR("device_get_binding() failed.");
		return;
	}

	led_set_brightness(dev, 0, 50);

	int led_tick = 0;
	led_ptn *next_ptn = led_a_ptn;
	while (1) {
		if (next_ptn->tick == LED_PTN_TICK_TERM) {
			next_ptn = led_a_ptn;
		}

		if (next_ptn->tick == led_tick) {
			led_set_brightness(dev, 0, next_ptn->brightness);
			next_ptn++;
		}
		
		led_tick = (led_tick + 1) % LED_PTN_TICK_MAX;
		k_sleep(K_MSEC(LED_PTN_TICK_PAR_MS));
	}
}
