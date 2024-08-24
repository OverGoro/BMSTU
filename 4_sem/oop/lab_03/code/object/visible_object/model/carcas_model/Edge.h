#ifndef __EDGE_H__
#define __EDGE_H__

#include <cstddef>

class Edge
{
public:
    Edge() = default;
    Edge(std::size_t i_1, std::size_t i_2);
    Edge(const Edge &edge);
    Edge &operator=(const Edge &edge);
    ~Edge() = default;

    std::size_t getFirstPointID() const;
    void setFirstPointID(std::size_t index);
    std::size_t getSecondPointID() const;
    void setSecondPointID(std::size_t index);

    bool operator ==(const Edge &edge) const;
    bool operator <(const Edge &edge) const;
    bool operator >(const Edge &edge) const;
protected:
    std::size_t i_1, i_2;
};

#endif // __EDGE_H__
