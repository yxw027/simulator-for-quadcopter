/**
 * @file led.h
 * @brief LED interface
 */

#ifndef _LED_H
#define _LED_H

/**
 * @addtogroup UFO
 * @{
 */

/**
 * @addtogroup HAL
 * @{
 */

enum led_state {
    LED_ON,         /**< turn led on */
    LED_OFF,        /**< turn led off */
    LED_TOGGLED     /**< toggled led */
};

/**
 * Initialize led
 *
 * @param led The led gpio pin
 * @param state The led status
 * @return None
 */
void led_init(void);

void led_on(ledno);

void led_off(ledno);

void led_toggle(ledno);

/** @} */

/** @} */

#endif /* _LED_H */