/**
 * @file thread_led.c
 * @brief led module
 */

#include <rtthread.h>

#include "led.h"

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

static void led_thread_entry(void *parameter)
{
    do {
        if (rt_mq_recv(&mq_led, &buf[0], sizeof(ARRAY_SIZE(buf)), RT_WAITING_FOREVER) == RT_EOK) {
            if (timer != RT_NULL)
                rt_timer_delete(timer);

            if (led.state == LED_STATE_BLINK)
                timer = rt_timer_create("timer", timeout, &led, 10, RT_TIMER_FLAG_PERIODIC);
            else if (led.state == LED_STATE_ON)
                led_on(led.num);
            else if(led.state == LED_STATE_OFF)
                led_off(led.num);
            else if (led.state == LED_STATE_TOOGLE)
                led_toggle(led.num);
        }
    } while (1);
}

void led_thread_init(void)
{
    
}  
