/**
 * @file pid.c
 * @brief PID controller implementation
 */
#include "pid.h"

/**
 * @addtogroup PID
 * PID controller algorithm
 * @{
 */

void pid_init(struct pid_t *pid, int Kp, int Ki, int Kd, int sp)
{
    pid->e = 0;
    pid->i = 0;
    pid->d = 0;
    pid->sp = sp;    
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
}

pid_update(struct pid_t *pid, int pv, int dt)
{
    int error;
    int mv;
    
    /* calculate error */
    error = pid->sp - pv;
    /* error integration */
    pid->i += error * dt;
    /* error derivation */
    d = (error - e) / dt;
    /* update error */
    e = error;
    
    /* calculate output */
    mv = (pid->Kp * e) + (pid->Ki * i) + (pid->Kd * d);
    
    return mv;
}

/** @} */