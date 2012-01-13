#ifndef _AHRS_H
#define _AHRS_H

class AHRS_EKF : public Kalman::EKFilter<double 7> {
public:
    AhrsEKF();
    ~AhrsEKF();

protected:
    virtual void makeA();
    virtual void makeH();
    virtual void makeV();
    virtual void makeW();
    virtual void makeQ();
    virtual void makeProcess();
    virtual void makeMeasure();

private:
    //double ...
};

#endif // _AHRS_H