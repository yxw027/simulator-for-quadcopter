/**
 * @file ins.c
 * @brief INS library implementation
 *
 * 13-state EKF
 */

/**
 * @defgroup INS Inertial Navigation System
 * @{
 */

/**
 * \f[
    x = f(x_{k-1},u_{k-1},w_{k-1}) =
    \left[ \begin{array}{c}
    posx \\ \\ posy \\ \\ posz \\ \\ velx \\ \\ vely \\ \\ velz \\ \\ q0 \\ \\ q1 \\ \\ q2 \\ \\ q3 \\ \\ bp \\ \\ bq \\ \\ br
    \end{array} \right] =
    \left[ \begin{array}{c}
    velx \\ \\ vely \\ \\ velz \\ \\
    (q0^2 + q1^2 - q2^2 - q3^2)ax + 2(q1q2 - q0q3)ay + 2(q1q3 + q0q2)az \\ \\
    2(q1q2 + q0q3)ax + (q0^2 - q1^2 + q2^2 - q3^2)ay + 2(q2q3 - q0q1)az \\ \\
    2(q1q3 - q0q2)ax + 2(q2q3 + q0q1)ay + (q0^2 - q1^2 - q2^2 + q3^2)az + g \\ \\
    -q1wx - q2wy - q3wz \\ \\
    q0wx - q3wy + q2wz \\ \\
    q3wx + q0wy - q1wz \\ \\
    -q2wx + q1wy + q0wz \\ \\
    0 \\ \\ 0 \\ \\ 0
    \end{array} \right] 
 * \f]
 */
 void make_process(struct ekf *ekf)
 {
 }
 
 /**
  * A is a \a n by \a n jacobian matrix of partial derivatives
  *
  * \f[
    A_{[i,j]} = \frac{\partial f_{[i]}}{\partial x_{[j]}} =
    \left[ \begin{array}{ccccccccccccc}
    0 & 0 & 0 & 1 & 1 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 2(q0ax - q3ay + q2az) & 2(q1ax + q2ay + q3az) & 2(-q2ax + q1ay + q0az) & 2(-q3ax - q0ay + q1az) & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 2(q3ax + q0ay - q1az) & 2(q2ax - q1ay - q0az) & 2(q1ax + q2ay + q3az) & 2(q0ax - q3ay + q2ay) & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 2(-q2ax + q1ay + q0az) & 2(q3ax + q0ay -q1az) & 2(-q0ax + q3ay - q2az) & 2(q1ax + q2ay + q2az) & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & \frac{-wx}{2} & \frac{-wy}{2} & \frac{-wz}{2} & \frac{q1}{2} & \frac{q2}{2} & \frac{q3}{2} \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & \frac{wx}{2} & 0 & \frac{wz}{2} & \frac{-wy}{2} & \frac{-q0}{2} & \frac{q3}{2} & \frac{-q2}{2} \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & \frac{wy}{2} & \frac{-wz}{2} & 0 & \frac{wx}{2} & \frac{-q3}{2} & \frac{-q0}{} & \frac{q1}{2} \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & \frac{wz}{2} & \frac{wy}{2} & \frac{-wx}{2} & 0 & \frac{q2}{2} & \frac{-q1}{2} & \frac{-q0}{2} \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0
    \end{array} \right]
    \f]
 */
void make_A(struct ekf *ekf)
{
}

/**
 * z is measure vector
 * \f[
    z = h(x_k, v_k) =
    \left[ \begin{array}{c}
    posx \\ \\ posy \\ \\ posz \\ \\
    velx \\ \\ vely \\ \\ velz \\ \\
    (q0^2 + q1^2 - q2^2 - q3^2)Be + 2(q1q2 + q0q3)Be + 2(q1q3 - q0q2)Be \\ \\
    2(q1q2 - q0q3)Be + (q0^2 - q1^2 + q2^2 - q3^2)Be + 2(q2q3 + q0q1)Be \\ \\
    2(q1q3 + q0q2)Be + 2(q2q3 - q0q1)Be + (q0^2 - q1^2 - q2^2 + q3^2)Be \\ \\
    -posz
    \end{array} \right]
 * \f]
 */
void make_measure(struct ekf *ekf)
{
}

/**
 * H is a \a m by \a n jacobian matrix
 * \f[
    H_{[i,j]} = \frac{\partial h_{[i]}}{\partial x_{[j]}} =
    \left[ \begin{array}{ccccccccccccc}
    1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 \\ \\
    0 & 0 & -1 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0 & 0   
    \end{array} \right]
 * \f]
 */
void make_H(struct ekf *ekf)
{
}

/**
 * \f[
   DCM =
    \left[ \begin{array}{ccc}
    1 - 2(q_2^2 + q_3^2) & 2(q_1q_2 + q_0q_3) & 2(q_1q_3 - q_0q_2) \\ \\
    2(q_1q_2 - q_0q_3) & 1 - 2(q_1^2 + q_3^2) & 2(q_2q_3 + q_0q_1) \\ \\
    2(q_1q_3 + q_0q_2) & 2(q_2q_3 - q_0q_1) & 1 - 2(q_1^2 + q_2^2) 
    \end{array} \right]
 * \f]
 */
void make_DCM(struct ekf *ekf)
{
}