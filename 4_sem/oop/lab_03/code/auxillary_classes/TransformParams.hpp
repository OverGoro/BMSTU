#ifndef __TRANSFORMPARAMS_H__
#define __TRANSFORMPARAMS_H__
#include "Point.h"
class BaseTransformParams
{
public:
    virtual ~BaseTransformParams() = 0;
};

inline BaseTransformParams::~BaseTransformParams() {} // Provide the definition for the destructor

class RotateParams : public BaseTransformParams
{
public:
    RotateParams(){};
    ~RotateParams(){};
    RotateParams(double ax, double ay, double az, const Point &center) : ax(ax), ay(ay), az(az), center(center) {}

#pragma region getters and setters
    double getAx() const { return ax; }
    void setAx(double value) { ax = value; }

    double getAy() const { return ay; }
    void setAy(double value) { ay = value; }

    double getAz() const { return az; }
    void setAz(double value) { az = value; }

    const Point &getCenter() const { return center; }
    void setCenter(const Point &value) { center = value; }

#pragma endregion getters and setters

protected:
    double ax, ay, az;
    Point center;
};

class ScaleParams : public BaseTransformParams
{
public:
    ScaleParams(){};
    ~ScaleParams(){};
    ScaleParams(double kx, double ky, double kz, const Point &center) : kx(kx), ky(ky), kz(kz), center(center) {}

#pragma region getters and setters
    double getKx() const { return kx; }
    void setKx(double value) { kx = value; }

    double getKy() const { return ky; }
    void setKy(double value) { ky = value; }

    double getKz() const { return kz; }
    void setKz(double value) { kz = value; }

    const Point &getCenter() const { return center; }
    void setCenter(const Point &value) { center = value; }

#pragma endregion getters and setters

protected:
    double kx, ky, kz;
    Point center;
};

class MoveParams : public BaseTransformParams
{
public:
    MoveParams(){};
    ~MoveParams(){};
    MoveParams(double dx, double dy, double dz) : dx(dx), dy(dy), dz(dz) {}

#pragma region getters and setters
    double getDx() const { return dx; }
    void setDx(double value) { dx = value; }

    double getDy() const { return dy; }
    void setDy(double value) { dy = value; }

    double getDz() const { return dz; }
    void setDz(double value) { dz = value; }

#pragma endregion getters and setters

protected:
    double dx, dy, dz;
};



#endif // __TRANSFORMPARAMS_H__
