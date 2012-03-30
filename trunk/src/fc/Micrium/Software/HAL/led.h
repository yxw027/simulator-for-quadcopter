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


/**
 * @brief Initialize LEDs
 *
 * @param None
 * @return None
 */
extern void LED_Init(void);

/**
 * @brief Turn on LED
 *
 * @param ledno The LED number
 * @return None
 */
extern void LED_On(ledno);

/**
 * @brief Turn off LED
 *
 * @param ledno The LED number
 * @return None
 */
void LED_Off(ledno);

/**
 * @brief Toogle LED
 *
 * @param ledno The LED number
 * @return None
 */ 
void LED_Toggle(ledno);

/** @} */

/** @} */

#endif /* _LED_H */
