#ifndef _FILTER_H
#define _FILTER_H

/**
 * @brief low passer filter
 * @param[in] input
 * @param[out]
 * @return None
 */
void low_pass(float input[3], float filtered[3]);

/**
 * @brief high pass filter
 * @param[in] input
 * @param filtered[out]
 * @return None
 */
void high_pass(float input[3], float filtered[3]);

#endif /* _FILTER_H */
