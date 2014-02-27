/**
 * @file time.h
 * @brief
 */
#ifndef _TIME_H
#define _TIME_H

/**
 * return true if the time a is after b
 */
#define time_after(a, b) \
    ((long)(b) - (long)(a) < 0)

/**
 * return true if the time a is before b
 */ 
#define time_before(a, b)   time_after(b, a)

#define time_after_eq(a, b) \
    ((long)(b) - (long)(a) <= 0)

#endif /* _TIME_H */