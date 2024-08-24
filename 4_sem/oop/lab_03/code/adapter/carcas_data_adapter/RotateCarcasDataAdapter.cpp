#include "RotateCarcasDataAdapter.h"
#include "RotatePointAdapter.h"
void RotateCarcasDataAdapter::request()
{
    for (auto &point : carcas_data->points)
    {
        RotatePointAdapter(std::shared_ptr<Point>(&point, [](Point *){}), params).request();
    }
}
