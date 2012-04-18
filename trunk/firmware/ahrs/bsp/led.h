/**
 * @file led.h
 * @brief LED interface
 */

#ifndef _LED_H
#define _LED_H

/**
 * @addtogroup kite
 * @{
 */

/**
 * @addtogroup BSP
 * @{
 */


/**
 * @brief Initialize LEDs
 *
 * @param None
 * @return None
 */
void led_init(void);

/**
 * @brief Turn on LED
 *
 * @param led The LED number
 * @return None
 */
void led_on(led);

/**
 * @brief Turn off LED
 *
 * @param led The LED number
 * @return None
 */
void led_off(led);

/**
 * @brief Toogle LED
 *
 * @param led The LED number
 * @return None
 */ 
void led_toggle(led);


/** @} */

/** @} */

#endif /* _LED_H */