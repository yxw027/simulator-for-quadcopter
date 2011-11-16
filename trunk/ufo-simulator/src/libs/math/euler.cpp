#include "euler.h"

#include <QVector>

using namespace math;

Euler::Euler()
{
}

Euler::Euler(double phi, double theta, double psi)
{
    m_euler.insert(0, phi);
    m_euler.insert(1, theta);
    m_euler.insert(2, psi);
}

Euler::~Euler()
{
}

double Euler::getPitch() const
{
    return m_euler.at(0);
}

double Euler::getRoll() const
{
    return m_euler.at(1);
}

double Euler::getYaw() const
{
    return m_euler.at(2);
}
