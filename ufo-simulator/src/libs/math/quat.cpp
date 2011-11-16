#include "quat.h"
#include "euler.h"

#include <QVector>

using namespace math;

Quat::Quat()
{
    m_quat.insert(0, 1);
    m_quat.insert(1, 0);
    m_quat.insert(2, 0);
    m_quat.insert(3, 0);    
}

Quat::Quat(double q0, double q1, double q2, double q3)
{
    m_quat.insert(0, q0);
    m_quat.insert(1, q1);
    m_quat.insert(2, q2);
    m_quat.insert(3, q3);
}

Quat::~Quat()
{
}

Euler Quat::toEuler()
{
    const double q0 = m_quat.at(0);
    const double q1 = m_quat.at(1);
    const double q2 = m_quat.at(2);
    const double q3 = m_quat.at(3);

    double theta = -asin(2*(q1*q3 - q0*q2));

    double phi = atan2(2*(q2*q3 + q0*q1), 1-2*(q1*q1 + q2*q2));

    double psi = atan2(2*(q1*q2 + q0*q3), 1-2*(q2*q2 + q3*q3));

    return Euler(phi, theta, psi);
}

Quat Quat::fromEuler(const Euler& euler)
{
    return Quat(1, 0, 0, 0);
}