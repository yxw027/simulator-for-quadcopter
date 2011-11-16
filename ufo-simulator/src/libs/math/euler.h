#ifndef _EULER_H
#define _EULER_H

namespace math {

class Euler {
public:
    Euler();
    Euler(double phi, double theta, double psi);
    ~Euler();
    
    double getPitch() const;
    double getRoll() const;
    double getYaw() const;

private:
    QVector<double> m_euler(3);
};

} // namespace math

#endif // _EULER_H