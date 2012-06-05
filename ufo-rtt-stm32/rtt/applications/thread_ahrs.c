/**
 * @file thread_ahrs.c
 * @brief AHRS thread, for attitude calculation
 */

#include <rtthread.h>

#include "sensor.h"

struct rt_messagequeue mq_gyro;
char msg_pool[8];


static void ahrs_thread_entry(void *parameter)
{
    struct sensor_event gyro;

    while (1) {
        if (rt_mq_recv(&mq_gyro, &gyro, sizeof(struct sensor_event), RT_WAITING_FOREVER) == RT_EOK) {
        }
    };
    /* something wrong */

}
#define THREAD_STACK_SIZE   2048
#define THREAD_PRIORITY     RT_THREAD_PRIORITY_MAX/3
#define THREAD_TIMESLICE    30
void ahrs_thread_init(void)
{
    rt_thread_t tid = RT_NULL;

    /* Initialize mq */
    rt_mq_init(&mq_gyro, "mq_gyro", &msg_pool[0], 128, /* ????*/sizeof(msg_pool), RT_IPC_FLAG_FIFO);

    /* Create thread */
    tid = rt_thread_create("ahrs", ahrs_thread_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
    if (tid != RT_NULL)
        rt_thread_startup(tid);
}

int gyro_isr(struct sensor_event *event)
{
    int retval = -1;

    if (event)
        retval = rt_mq_send(&mq_gyro, event, sizeof(struct sensor_event));

    return retval;
}
