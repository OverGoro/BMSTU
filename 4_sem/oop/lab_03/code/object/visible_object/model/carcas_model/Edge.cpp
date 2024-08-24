#include "Edge.h"

Edge::Edge(std::size_t i_1, std::size_t i_2)
{
    setFirstPointID(i_1);
    setSecondPointID(i_2);
}

Edge::Edge(const Edge &edge)
{
    setFirstPointID(edge.getFirstPointID());
    setSecondPointID(edge.getSecondPointID());
}

Edge &Edge::operator=(const Edge &edge)
{
    setFirstPointID(edge.getFirstPointID());
    setSecondPointID(edge.getSecondPointID());
    return *this;
}

std::size_t Edge::getFirstPointID() const
{
    return i_1;
}

void Edge::setFirstPointID(std::size_t index)
{
    i_1 = index;
}

std::size_t Edge::getSecondPointID() const
{
    return i_2;
}

void Edge::setSecondPointID(std::size_t index)
{
    i_2 = index;
}

bool Edge::operator ==(const Edge &edge) const
{
    return (i_1 == edge.i_1 && i_2 == edge.i_2);
}

bool Edge::operator <(const Edge &edge) const
{
    return (i_1 < edge.i_1 || (i_1 == edge.i_1 && i_2 < edge.i_2));
}
bool Edge::operator >(const Edge &edge) const
{
    return (i_1 > edge.i_1 || (i_1 == edge.i_1 && i_2 > edge.i_2));
}
