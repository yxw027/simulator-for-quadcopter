#include "euler.h"

Euler::Euler() : m_roll(0), m_pitch(0), m_yaw(0)
{
}

Euler::Euler(const Quaternion &quaternion)
{
}

Euler::~Euler()
{
}

void Euler::setRoll(double roll)
{
    m_roll = roll;
}

double Euler::getRoll()
{
    return m_roll;
}

void Euler::setPitch(double pitch)
{
    m_pitch = pitch;
}

double Euler::getPitch()
{
    return m_pitch;
}

void Euler::setYaw(double yaw)
{
    m_yaw = yaw;
}
    
double Euler::getYaw()
{
    return m_yaw;
}