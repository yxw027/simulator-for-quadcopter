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
 * @addtogroup drivers
 * @{
 */

#define LED_NUM_1       (1 << 0)
#define LED_NUM_2       (1 << 1)
#define LED_NUM_3       (1 << 2)

#define LED_NUM_MAX     4

#define LED_STATE_ON        0
#define LED_STATE_OFF       1
#define LED_STATE_TOOGLE    2
#define LED_STATE_BLINK     3

struct led_struct {
    int num;
    int state;
};

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
void led_on(int led);

/**
 * @brief Turn off LED
 *
 * @param led The LED number
 * @return None
 */
void led_off(int led);

/**
 * @brief Toogle LED
 *
 * @param led The LED number
 * @return None
 */ 
void led_toggle(int led);


/** @} */

/** @} */

#endif /* _LED_H */
