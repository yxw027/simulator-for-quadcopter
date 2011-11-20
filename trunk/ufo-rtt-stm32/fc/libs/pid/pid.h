/**
 * @file pid.h
 * @brief PID controller interface
 */
#ifndef _PID_H
#define _PID_H

/**
 * @defgroup PID PID Controller
 * @ingroup ufo
 * @{
 */

/**
 * @struct pid_t pid.h
 * @brief Describe a pid controller
 *
 * The PID control scheme is named after its three correcting terms, whose sum constitutes the manipulated variable(MV)\n
 * The proportional integral, and derivative terms are summed to calculate the output of the PID controller.\n
 * Defining \f$ u(t) \f$ as the controller output, the final form of the PID is:\n
 * \f[ u(t)=MV(t)=K_pe(t)+K_i\int_{0}^Te(t)dt+K_d\frac{d}{dt}e(t) \f]
 * where\n
 * \f$ K_p \f$ : Proportional gain, a tuning paramter\n
 * \f$ K_i \f$ : Integral gain, a tuning parameter\n
 * \f$ K_d \f$ : Derivative gain, a tuning parameter\n
 * \f$ e \f$ : Errorr = SP - PV\n
 * \f$ t \f$ : Time or instantaneous time(the present)
 */
struct pid_t {
    int e;      /**< Error, SP(set point) - PV(process value) */
    int i;      /**< Integral variable */
    int d;      /**< Derivative variable */
    int sp;     /**< Set point */
    int Kp;     /**< Proportional gain, a tuning parameter */
    int Ki;     /**< Integral gain, a tuning parameter */
    int Kd;     /**< Derivative gain, a tuning parameter */
};
#define SAT_FILTER(val, min, max)   val > max ? max : (val < min ? min : val)
/**
 * PID controller parameter initialization
 *
 * @param pid The pointer to a pid_t sturcture
 * @param Kp The initial proportional gian
 * @param Ki The initial integral gian
 * @param Kd The inital derivative gain
 * @param sp The process set point
 * @return None
 * @note Should be initialized before invoked
 */
void pid_init(struct pid_t *pid, int Kp, int Ki, int Kd, int sp);
#define pid_init(pid, Kp, Ki, Kd, err)  {}
/**
 * PID update routine in it's ideal
 *
 * @param pid The pointer to a pid_t sturcture
 * @param pv The process value from feedback
 * @param dt The time stamp
 * @return Return the PV(manipulated value)
 */
int pid_update(struct pid_t *pid, int pv, int dt);

/** @} */

#endif /* _PID_H */