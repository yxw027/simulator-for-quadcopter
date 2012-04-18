/**
 * @file board.h
 * @brief board interface
 */

#ifndef _BOARD_H
#define _BOARD_H

/**
 * @addtogroup kite
 * @{
 */

/**
 * @addtogroup BSP
 * @{
 */

typedef enum 
{
    LED1 = 0,
    LED2 = 1,
    LED3 = 2
} Led_TypeDef;

/**
 * @brief board hardware initialization
 *
 * @param None
 * @return 0 if success, negative otherwise
 */
int board_init(void);

/** @} */

/** @} */

#endif /* _BOARD_H */
