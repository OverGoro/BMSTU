#include "CarcasData.h"
#include "MovePointAdapter.h"
#include "ScalePointAdapter.h"
#include "RotatePointAdapter.h"
CarcasData::CarcasData(const points_type &points, const edges_type &edges)
{
    setPoints(points);
    setEdges(edges);
}

CarcasData::CarcasData(const CarcasData &data)
{
    setPoints(data.points);
    setEdges(data.edges);
}

CarcasData &CarcasData::operator=(const CarcasData &data)
{
    setPoints(data.points);
    setEdges(data.edges);
    return *this;
}

CarcasData::CarcasData(CarcasData &&data)
{
    setPoints(data.points);
    setEdges(data.edges);
}

CarcasData::points_type CarcasData::getPoints() const
{
    return points;
}

void CarcasData::setPoints(const points_type &points)
{
    this->points = points;
}

void CarcasData::addPoint(const Point &point)
{
    points.push_back(point);
}

void CarcasData::addEdge(const Edge &edge)
{
    edges.push_back(edge);
}

CarcasData::edges_type CarcasData::getEdges() const
{
    return edges;
}

void CarcasData::setEdges(const edges_type &edges)
{
    this->edges = edges;
}

void CarcasData::move(const MoveParams &params)
{
    for (auto &point : points)
    {
        MovePointAdapter(std::make_shared<Point>(point), params).request();
    }
}

void CarcasData::scale(const ScaleParams &params)
{
    for (auto &point : points)
    {
        ScalePointAdapter(std::make_shared<Point>(point), params).request();
    }
}

void CarcasData::rotate(const RotateParams &params)
{
    for (auto &point : points)
    {
        RotatePointAdapter(std::make_shared<Point>(point), params).request();
    }
}
