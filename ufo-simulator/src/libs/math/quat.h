#ifndef _QUAT_H
#define _QUAT_H

namespace math {

class QVector;
class Euler;

class Quat {
public:
    Quat();
    Quat(double q0, double q1, double q2, double q3);
    ~Quat();
    
    Euler toEuler();
    Quat fromEuler(const Euler& euler);

private:
    QVector<double> m_quad(4);
};

} // namespace math

#endif // _QUAT_H