#ifndef __CARCASDATA_H__
#define __CARCASDATA_H__

#include "Edge.h"
#include "Point.h"
#include "VectorContainer.h"
#include "TransformParams.hpp"
class CarcasData
{
    friend class CenterCarcasDataAdapter;
    friend class MoveCarcasDataAdapter;
    friend class ScaleCarcasDataAdapter;
    friend class RotateCarcasDataAdapter;
    friend class DrawCarcasDataAdapter;

    using points_type = Vector<Point>;
    using edges_type = Vector<Edge>;
public:
    CarcasData() {};
    CarcasData(const points_type &points, const edges_type &edges);
    CarcasData(const CarcasData &data);
    CarcasData &operator=(const CarcasData &data);
    CarcasData(CarcasData &&data);
    ~CarcasData() = default;
    
    points_type getPoints() const;
    void setPoints(const points_type &points);

    void addPoint(const Point &point);
    void addEdge(const Edge &edge);

    edges_type getEdges() const;
    void setEdges(const edges_type &edges);


    void move(const MoveParams &params);
    void scale(const ScaleParams &params);
    void rotate(const RotateParams &params);
    
protected:
    points_type points;
    edges_type edges;
};

#endif // __CARCASDATA_H__
