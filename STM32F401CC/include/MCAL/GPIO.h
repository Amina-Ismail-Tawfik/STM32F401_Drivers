#ifndef GPIO_H
#define GPIO_H

#include "STD_TYPES.h"
#include "Errors.h"

/**************** GPIO Base Addresses ****************/
#define GPIOA_BASE_ADDRESS        0x40020000
#define GPIOB_BASE_ADDRESS        0x40020400
#define GPIOC_BASE_ADDRESS        0x40020800
#define GPIOD_BASE_ADDRESS        0x40020C00
#define GPIOE_BASE_ADDRESS        0x40021000
#define GPIOH_BASE_ADDRESS        0x40021C00

/**************** GPIO Port Macros ****************/
#define GPIOA     (void *)GPIOA_BASE_ADDRESS
#define GPIOB     (void *)GPIOB_BASE_ADDRESS
#define GPIOC     (void *)GPIOC_BASE_ADDRESS
#define GPIOD     (void *)GPIOD_BASE_ADDRESS
#define GPIOE     (void *)GPIOE_BASE_ADDRESS
#define GPIOH     (void *)GPIOH_BASE_ADDRESS

/**************** GPIO Modes ****************/
#define GPIO_MODE_OUTPUT_PP		0x00000001
#define GPIO_MODE_OUTPUT_OD		0x00000101
#define GPIO_MODE_INPUT			0x00000000
#define GPIO_MODE_AF			0x00000002
#define GPIO_MODE_ANALOG 		0x00000003

/**************** GPIO Pull Configurations ****************/
#define GPIO_NOPULL          0x00000000
#define GPIO_PULLUP			0x00000001
#define GPIO_PULLDOWN		0x00000002

/**************** GPIO Output Speed ****************/
#define GPIO_LOW_SPEED           0x00000000
#define GPIO_MEDIUM_SPEED        0x00000001
#define GPIO_HIGH_SPEED          0x00000002
#define GPIO_VHIGH_SPEED     	 0x00000003

/**************** GPIO Pin States ****************/
#define GPIO_STATE_HIGH        0x00000001
#define GPIO_STATE_LOW         0x00000000

/**************** GPIO Alternate Functions ****************/
#define GPIO_AF_SYSTEM          0x00000000
#define GPIO_AF_TIM1_2          0x00000001
#define GPIO_AF_TIM3_5         	0x00000002
#define GPIO_AF_TIME9_11       	0x00000003
#define GPIO_AF_I2C1_3         	0x00000004
#define GPIO_AF_SPI1_4         	0x00000005
#define GPIO_AF_SPI3            0x00000006
#define GPIO_AF_USART1_2        0x00000007
#define GPIO_AF_USART6          0x00000008
#define GPIO_AF_I2C2_3          0x00000009
#define GPIO_AF_OTG_FS          0x0000000A
#define GPIO_AF_SDIO            0x0000000C
#define GPIO_AF_EVENTOUT        0x0000000F

/**************** GPIO Configuration Structure ****************/
typedef struct
{
    void* GPIO_Port_Num;
    u8 GPIO_Pin_Num;
    uint16 GPIO_Mode;
    u8 GPIO_OutPut_Speed;
    u8 GPIO_Pull;
    u8 GPIO_AF;
} GPIO_cfg_t;

/**************** GPIO Pin Enumeration ****************/
typedef enum{
    GPIO_pin0,
    GPIO_pin1,
    GPIO_pin2,
    GPIO_pin3,
    GPIO_pin4,
    GPIO_pin5,
    GPIO_pin6,
    GPIO_pin7,
    GPIO_pin8,
    GPIO_pin9,
    GPIO_pin10,
    GPIO_pin11,
    GPIO_pin12,
    GPIO_pin13,
    GPIO_pin14,
    GPIO_pin15
} GPIO_Pin_t;

/***************** Function Prototypes *****************/

/**
 * @brief Initializes a GPIO pin with the given configuration.
 *
 * This function initializes a GPIO pin with the configuration specified in the
 * provided GPIO_cfg_t structure.
 *
 * @param add_pin Pointer to the GPIO configuration structure.
 * @return ErrorStatus_t Returns OK if the initialization is successful, otherwise returns an error status.
 */
ErrorStatus_t GPIO_initPin (GPIO_cfg_t* add_pin);

/**
 * @brief Sets the value of a GPIO pin.
 *
 * This function sets the value of the specified GPIO pin.
 *
 * @param GPIOx Pointer to the GPIO port.
 * @param GPIO_pin GPIO pin number.
 * @param GPIO_STATE GPIO state to set (HIGH or LOW).
 * @return ErrorStatus_t Returns OK if the operation is successful, otherwise returns an error status.
 */
ErrorStatus_t GPIO_setPinValue(void* GPIOx, u8 GPIO_pin, u8 GPIO_STATE);

/**
 * @brief Gets the value of a GPIO pin.
 *
 * This function gets the value of the specified GPIO pin.
 *
 * @param GPIOx Pointer to the GPIO port.
 * @param GPIO_pin GPIO pin number.
 * @param Pin_Stat Pointer to store the GPIO pin value.
 * @return ErrorStatus_t Returns OK if the operation is successful, otherwise returns an error status.
 */
ErrorStatus_t GPIO_getPinValue(void* GPIOx, u8 GPIO_pin, u8* Pin_Stat);

#endif
