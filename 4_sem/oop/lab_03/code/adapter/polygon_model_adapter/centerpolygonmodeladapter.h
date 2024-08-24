#ifndef CENTERPolygonMODELADAPTER_H
#define CENTERPolygonMODELADAPTER_H

#include "basepolygonmodeladapter.h"

class CenterPolygonModelAdapter : public BasePolygonModelAdapter
{
public:
    CenterPolygonModelAdapter() = default;
    CenterPolygonModelAdapter(const std::shared_ptr<PolygonModel> &model,
                           const std::shared_ptr<Point> &center)
    {
        this->model = model;
        this->center = center;
    }
    ~CenterPolygonModelAdapter() = default;
    void request() override;

protected:
    std::shared_ptr<Point> center;
    std::shared_ptr<PolygonModel> model;
};

#endif // CENTERPolygonMODELADAPTER_H
