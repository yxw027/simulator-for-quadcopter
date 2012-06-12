/**
 * @file thread_ahrs.c
 * @brief AHRS thread, for attitude calculation
 */

#include <rtthread.h>
#include <math/math.h>
 #include <stdio.h>
#include "sensor.h"

struct rt_messagequeue mq_gyro;
char msg_pool[128];


static void ahrs_thread_entry(void *parameter)
{
    struct sensor_event event;
    float q[4] = { 1, 0, 0, 0 };
    float q0 = 1, q1 = 0, q2 = 0, q3 = 0;
    float z[3];
    float u[3];
    int i = 0;
    while (1) {
        if (rt_mq_recv(&mq_gyro, &event, sizeof(struct sensor_event), RT_WAITING_FOREVER) == RT_EOK) {
            float p = toRadians(event.vec.x * 0.00875);
            float q = toRadians(event.vec.y * 0.00875);
            float r = toRadians(event.vec.z * 0.00875);
            rt_kprintf("%x %x %x\n", p, q, r);

            q0 += (-p * q1 - q * q2 - r * q3) / 2 * 0.0025;
            q1 += (p * q0 - q * q3 + r * q2) / 2 * 0.0025;
            q2 += (p * q3 + q * q0 - r * q1) / 2 * 0.0025;
            q3 += (-p * q2 + q * q1 + r * q0) / 2 * 0.0025;
            z[0] = atan2(2 * (q2 * q3 + q0 * q1), 1 - 2 * (q1 * q1 + q2 * q2));
            z[1] = -asin(2 * (q1 * q3 - q0 * q2));
            z[2] = atan2(2 * (q1 * q2 + q0 * q3), 1 - 2 * (q2 * q2 + q3 * q3));
/*
            u[0] = toRadians(event.vec.x * 0.00875);
            u[1] = toRadians(event.vec.y * 0.00875);
            u[2] = toRadians(event.vec.z * 0.00875);
*/
            i++;
        }
        if (i)
            rt_kprintf("%f %f %f\n", u[0], u[1], u[2]);
    };
    /* something wrong */

}
#define THREAD_STACK_SIZE   2048
#define THREAD_PRIORITY     RT_THREAD_PRIORITY_MAX/3
#define THREAD_TIMESLICE    30
void ahrs_thread_init(void)
{
    static struct rt_thread tid; 
    ALIGN(8) static unsigned char stack[THREAD_STACK_SIZE];

    /* Initialize mq */
    rt_mq_init(&mq_gyro, "mq_gyro", &msg_pool[0], sizeof(struct sensor_event), sizeof(msg_pool), RT_IPC_FLAG_FIFO);

    /* Create thread */
    if(rt_thread_init(&tid, 
						"ahrs", 
						ahrs_thread_entry, 
						RT_NULL,
						&stack,THREAD_STACK_SIZE, 
						THREAD_PRIORITY, THREAD_TIMESLICE) == RT_EOK)
		rt_thread_startup(&tid);
}

int gyro_isr(struct sensor_event *event)
{
    int retval = -1;

    if (event)
        retval = rt_mq_send(&mq_gyro, event, sizeof(struct sensor_event));

    return retval;
}
