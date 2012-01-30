#ifndef _AHRS_H
#define _AHRS_H

class AHRS_EKF : public Kalman::EKFilter<double, 7> {
public:
    AhrsEKF();
    ~AhrsEKF();

protected:
    virtual void makeA();
    virtual void makeH();
    virtual void makeV();
    virtual void makeR();
    virtual void makeW();
    virtual void makeQ();
    virtual void makeProcess();
    virtual void makeMeasure();

    virtual void predict();
    virtual void correct();
    virtual void step();

private:
    Vector gyro(3);
    double measurement_noise_covariance;

    void propagate_state();
    void propagate_covariance();
};

typedef AHRS_EKF::Vector Vector;
typedef AHRS_EKF::Matrix Matrix;

#endif // _AHRS_H