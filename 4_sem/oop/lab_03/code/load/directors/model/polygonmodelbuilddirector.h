#ifndef BASEPolygonModelBUILDDIRECTOR_H
#define BASEPolygonModelBUILDDIRECTOR_H


#include "BaseDirector.h"
#include "polygon_model/polygonmodel.h"
#include "polygonmodelbuilder.h"

class PolygonModelBuildDirector : public BaseDirector
{
public:
    virtual std::shared_ptr<PolygonModel> create(std::shared_ptr<PolygonModelBuilder> builder);
};

#endif // BASEPolygonModelBUILDDIRECTOR_H
