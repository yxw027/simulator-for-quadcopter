

/**
 * @defgroup fc flight controller
 * @ingroup ufo
 * @{
 */

/**
 * @defgroup core
 * @ingroup fc
 * @{
 */

typedef struct core_task_data {
    struct gyro_event_t     gyro;
    struct gyro_bias_t      gyro_bias;
    struct accl_event_t     accl;
    struct accl_offset_t    accl_offset;
//    struct euler_t          euler;
//    struct quat_t           quat;
} core_task_core;
/**
 * main task
 * The flight controller core(attitude estimation)
 */
void core_task_init();

/** @} */

/**
 * @defgroup brushless
 * @ingroup flight controller 
 * @{
 */
/** @} */

/** @} */
