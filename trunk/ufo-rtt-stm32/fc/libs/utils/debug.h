/**
 * @file debug.h
 * Debug interface
 */

#ifndef _DEBUG_H
#define _DEBUG_H


/*
 * debug macros
 */
#define GYRO_DEBUG      0
#define IMU_DEBUG       1

#if DBG_VS



/**
 * VisualScope adapter
 */
void dbg();

#else
#define dbg()   NULL
#endif 


#endif /* _DEBUG_H */
