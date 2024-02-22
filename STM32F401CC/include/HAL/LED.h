#ifndef LED_H
#define LED_H

#include "STD_TYPES.h"
#include "Errors.h"
#include "LED_cfg.h"

/* LED active state */
#define LED_ACTIVE_HIGH 0
#define LED_ACTIVE_LOW 1

/* LED initial state */
#define LED_STAT_ON 1
#define LED_STAT_OFF 0

/**
 * @brief LED configuration structure
 *
 * This structure holds the configuration parameters for each LED.
 */
typedef struct {
    void* LED_Port;         /**< Pointer to the GPIO port of the LED */
    u8 LED_Pin;             /**< Pin number of the LED */
    u8 LED_ActiveState;     /**< Active state of the LED (HIGH or LOW) */
    u8 LED_InitState;       /**< Initial state of the LED (ON or OFF) */
} LED_cfg_t;

/**
 * @brief Initializes LEDs
 *
 * This function initializes all LEDs based on their configurations.
 *
 * @return ErrorStatus_t Returns OK if the initialization is successful, otherwise returns an error status.
 */
ErrorStatus_t LED_init(void);

/**
 * @brief Sets status of an LED
 *
 * This function sets the status of a specific LED.
 *
 * @param LED: LED index
 * @param LED_STAT: LED status (ON or OFF)
 * @return ErrorStatus_t Returns OK if the initialization is successful, otherwise returns an error status.
 */
ErrorStatus_t LED_SetStatus(uint16 LED, u8 LED_STAT);

#endif /* LED_H */
