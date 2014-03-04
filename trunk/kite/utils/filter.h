#ifndef _FILTER_H
#define _FILTER_H

void low_pass_init(void);

/**
 * @brief low passer filter
 * @param[in] input input samples
 * @param[out] filtered the filtered result
 * @return None
 */
void low_pass(float input[3], float filtered[3]);

void high_pass_init(void);

/**
 * @brief high pass filter
 * @param[in] input
 * @param filtered[out] filtered the filtered result
 * @return None
 */
void high_pass(float input[3], float filtered[3]);

#endif /* _FILTER_H */
