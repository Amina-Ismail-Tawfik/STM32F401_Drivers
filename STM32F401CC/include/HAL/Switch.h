#ifndef SWITCH_H
#define SWITCH_H

#include "STD_TYPES.h"
#include "Errors.h"
#include "Switch_cfg.h"

/* Switch connection types */
#define SWITCH_PULL_DOWN    2
#define SWITCH_PULL_UP      1

/**
 * @brief Switch configuration structure
 *
 * This structure holds the configuration parameters for each switch.
 */
typedef struct {
    void* switch_Port;          /**< Pointer to the GPIO port of the switch */
    u8 switch_Pin;              /**< Pin number of the switch */
    u8 switch_Connection;       /**< Connection type of the switch (PULL_DOWN or PULL_UP) */
} Switch_cfg_t;

/**
 * @brief Initializes switches
 *
 * This function initializes all switches based on their configurations.
 *
 * @return ErrorStatus_t: OK if initialization is successful, error status otherwise
 */
ErrorStatus_t Switch_init(void);

/**
 * @brief Gets the state of a specific switch
 *
 * This function retrieves the state (pressed or released) of a specific switch.
 *
 * @param Switch: The index of the switch to get its state
 * @param Switch_State: Pointer to where the switch state will be stored
 * @return ErrorStatus_t: OK if retrieval is successful, error status otherwise
 */
ErrorStatus_t Switch_getKey(uint16 Switch, u8* Switch_State);

#endif /* SWITCH_H */

