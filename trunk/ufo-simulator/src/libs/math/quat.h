#ifndef _QUAT_H
#define _QUAT_H

#include "math_global.h"

#include <QVector>

namespace math {

class Euler;

class MATH_EXPORT Quat
{
public:
    Quat();
    Quat(double q0, double q1, double q2, double q3);
    ~Quat();
    
    Euler toEuler();
    Quat fromEuler(const Euler& euler);

private:
    QVector<double> m_quat;
};

} // namespace math

#endif // _QUAT_H
