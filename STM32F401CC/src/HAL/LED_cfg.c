/*****
 * LED_cfg.c
 *
 *  Created on: Feb 20, 2024
 *      Author: Amina
 *****/

#include "LED.h"
#include "GPIO.h"

/**
 * @brief Array of LED configurations
 *
 * This array holds the configurations for all the LEDs connected to the microcontroller.
 */
const LED_cfg_t LEDS[_LEDS_NUM] = {
    [LED_ONE] = {
        .LED_Port = GPIOA,
        .LED_Pin = GPIO_pin0,
        .LED_ActiveState = LED_ACTIVE_HIGH,
        .LED_InitState = LED_STAT_ON
    }
};

