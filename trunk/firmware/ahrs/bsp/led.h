/**
 * @file led.h
 * @brief LED interface
 */

#ifndef _LED_H
#define _LED_H

#include "led_hw.h"

/**
 * @addtogroup ORL
 * @{
 */

/**
 * @addtogroup HAL
 * @{
 */

enum led_index {
    LED_GREEN,
    LED_RED
};

enum led_state {
    LED_ON,         /**< turn led on */
    LED_OFF,        /**< turn led off */
    LED_TOGGLED     /**< toggled led */
};

/**
 * Initialize led hardware
 *
 * @param led The led index
 * @param state The led status
 * @return None
 */
void led_init(int led, enum led_state state);

/**
 * Set led status
 *
 * @param The led index
 * @param status The led status
 * @return None
 */
void led_set(int led, enum led_state state);

#define LED_ON(n)   led_hw_on(n)
#define LED_OFF(n)  led_hw_off(n)
#define LED_TOOGLE(n)   led_hw_toogle(n)

/** @} */

/** @} */

#endif /* _LED_H */