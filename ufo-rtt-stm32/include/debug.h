/**
 * @file debug.h
 * Debug interface
 */

#ifndef _DEBUG_H
#define _DEBUG_H

#if DBG_VS


 
/**
 * VisualScope adapter
 */
void dbg();

#else
#define dbg()   NULL
#endif 


#endif /* _DEBUG_H */
