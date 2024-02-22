#include "Switch.h"
#include "GPIO.h"

/**
 * @brief Configuration array for switches
 *
 * This array holds the configurations for all switches.
 */
const Switch_cfg_t switcheS[_SWITCH_NUM] = {
    [switch_ONE] = {
        .switch_Port = GPIOA,
        .switch_Pin = GPIO_pin0,
        .switch_Connection = SWITCH_PULL_DOWN
    }
};
