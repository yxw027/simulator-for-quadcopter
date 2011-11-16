#ifndef _EULER_H
#define _EULER_H

#include "math_global.h"

#include <QVector>

namespace math {

class MATH_EXPORT Euler
{
public:
    Euler();
    Euler(double phi, double theta, double psi);
    ~Euler();
    
    double getPitch() const;
    double getRoll() const;
    double getYaw() const;

private:
    QVector<double> m_euler;
};

} // namespace math

#endif // _EULER_H
