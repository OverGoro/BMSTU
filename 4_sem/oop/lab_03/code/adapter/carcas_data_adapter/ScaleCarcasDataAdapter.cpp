#include "ScaleCarcasDataAdapter.h"
#include "ScalePointAdapter.h"
void ScaleCarcasDataAdapter::request()
{
    for (auto &point : carcas_data->points)
    {
        ScalePointAdapter(std::shared_ptr<Point>(&point, [](Point *){}), params).request();
    }
}
