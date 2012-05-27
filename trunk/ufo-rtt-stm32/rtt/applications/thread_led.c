/**
 * @file thread_led.c
 * @brief led module
 */

#include <rtthread.h>

#include "led.h"
/*
struct rt_messagequeue mq_led;

static struct rt_timer timer;

static char mq_buf[8];

struct led_struct led;

static void timeout(void *parameter)
{
    struct led_struct *led = (struct led_struct)parameter;
    led_toogle(led.num);
	rt_kprintf("periodic timer is timeout\n");
}
*/
static void led_thread_entry(void *parameter)
{
    do {
        led_toggle(0);
        rt_thread_delay(10);
    } while (1);
}
#define THREAD_STACK_SIZE   2048
#define THREAD_PRIORITY     RT_THREAD_PRIORITY_MAX/3
#define THREAD_TIMESLICE    30 
void led_thread_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("led", led_thread_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);
	if (tid != RT_NULL)
        rt_thread_startup(tid);    
}  
