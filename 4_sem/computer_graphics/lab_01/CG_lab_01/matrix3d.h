#ifndef MATRIX3D_H
#define MATRIX3D_H

#include <QVector3D>

template <typename T>
class Matrix3D
{
public:
    T values[3][3];
    Matrix3D();
};

#endif // MATRIX3D_H
