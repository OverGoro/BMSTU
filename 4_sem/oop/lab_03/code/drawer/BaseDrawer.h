#ifndef __BASEDRAWER_H__
#define __BASEDRAWER_H__

#include "Point.h"
class BaseDrawer
{

public:
    virtual void drawLine(double x_1, double y_1, double x_2, double y_2) = 0;
    virtual void drawPoint(double x_1, double x_2) = 0;
    virtual void clearPoint(double x_1, double x_2) = 0;
    virtual void clear() = 0;
    virtual void initializeZBuffer(int width, int height) = 0;
    virtual void clearZBuffer() = 0;
    virtual void setTriangleZBuffer(const Point & p1, const Point & p2, const Point & p3) = 0;
    virtual void drawLineWithZBuffer(const Point &start, const Point &end) = 0;
    virtual void fillLineZbuffer(const Point &start, const Point &end) = 0;

protected:
    virtual bool isInBounds(int x, int y) = 0;

};

#endif // __BASEDRAWER_H__
