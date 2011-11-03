#ifndef QMATH_GLOBAL_H
#define QMATH_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(QMATH_DLL)
#   define Q_MATH_EXPORT    Q_DECL_EXPORT
#else
#   define Q_MATH_EXPORT    Q_DECL_IMPORT
#endif
/*
#ifndef Q_MATH_EXPORT
#define Q_MATH_EXPORT
#endif
*/
#endif // QMATH_GLOBAL_H
