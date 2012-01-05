/**
 * @file debug.h
 * Debug interface
 */

#ifndef _DEBUG_H
#define _DEBUG_H


/**
 * debug macros
 */
#define DEBUG_ACCEL     1
#define DEBUG_GYRO      0
#define DEBUG_IMU       1

#if DBG_VS



/**
 * VisualScope adapter
 */
void dbg();

#else
#define dbg()   NULL
#endif 


#endif /* _DEBUG_H */
