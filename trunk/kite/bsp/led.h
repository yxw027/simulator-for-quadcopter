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

typedef enum led {
	LED_GREEN = 0,
	LED_YELLOW,
	LED_RED,
	LED_BLUE,
	LED_MAX_NUM
} led_t;

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
void led_on(led_t led);

/**
 * @brief Turn off LED
 *
 * @param led The LED number
 * @return None
 */
void led_off(led_t led);

/**
 * @brief Toogle LED
 *
 * @param led The LED number
 * @return None
 */
void led_toggle(led_t led);


/** @} */

/** @} */

#endif /* _LED_H */
