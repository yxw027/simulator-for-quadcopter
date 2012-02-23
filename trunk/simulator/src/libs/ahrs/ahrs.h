#ifndef _AHRS_H
#define _AHRS_H

class AHRS_EKF : public Kalman::EKFilter<double, 7, false, true, false> {
public:
    AHRS_EKF();
    ~AHRS_EKF();

protected:
    virtual void makeA();
    virtual void makeH();
    virtual void makeV();
    virtual void makeR();
    virtual void makeW();
    virtual void makeQ();
    virtual void makeProcess();
    virtual void makeMeasure();
    /**
     * @brief Convert quaternion to direction-cosine-matrix
     *
     * \f[ DCM = \left [ \begin{array}{ccc}
     *  1 - 2 *(q2^2 + q3^2) & 2*(q1q2 + q0q3) & 2*(q1q3 - q0q2 \\ \\
     *  2 * (q1q2 - q0q3) & 1 - 2 * (q1^2 + q3^2) & 2 * (q2q3 + q0q1) \\ \\
     *  2 * (q1q3 + q0q2) & 2 * (q2q3 - q0q1) & 1 - 2 * (q1^2 + q2^2) \\ \\
     * \end{array} \right ] \f]
     */
    virtual void makeDCM();
private:
    Vector gyro(3);
    Matrix DCM(3, 3);
    double measurement_noise_covariance;
};

typedef AHRS_EKF::Vector Vector;
typedef AHRS_EKF::Matrix Matrix;

#endif // _AHRS_H