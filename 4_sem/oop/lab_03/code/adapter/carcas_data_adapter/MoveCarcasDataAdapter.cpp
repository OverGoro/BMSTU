#include "MoveCarcasDataAdapter.h"
#include "MovePointAdapter.h"
void MoveCarcasDataAdapter::request()
{
    for (auto &point : carcas_data->points)
    {
        MovePointAdapter(std::shared_ptr<Point>(&point, [](Point *){}), params).request();
    }
}
