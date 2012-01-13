#ifndef _QUATERNION_H
#define _QUATERNION_H

class Euler;

class Quaternion {
public:
    Quaternion();
    Quaternion(const Euler &euler);
    ~Quaternion();

    void normalize();

private:
    double q0;
    double q1;
    double q2;
    double q3;
};

#endif // _QUATERNION_H