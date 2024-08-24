#ifndef __PolygonMODEL_H__
#define __PolygonMODEL_H__
#include "BaseModel.h"
#include "polygondata.h"

class PolygonModel : public BaseModel
{
    friend class MovePolygonModelAdapter;
    friend class ScalePolygonModelAdapter;
    friend class RotatePolygonModelAdapter;
    friend class CenterPolygonModelAdapter;
    friend class DrawPolygonModelAdapter;
public:
    PolygonModel();
    PolygonModel(const PolygonModel &model);
    PolygonModel &operator=(const PolygonModel &model);
    PolygonModel(const PolygonData &data);
    ~PolygonModel() = default;

protected:
    PolygonData data;
};

#endif // __PolygonMODEL_H__
