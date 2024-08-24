#ifndef PolygonModelBUILDER_H
#define PolygonModelBUILDER_H

#include "BaseBuilder.h"

#include "basepolygonmodelreader.h"
#include "polygon_model/polygonmodel.h"

class PolygonModelBuilder : public BaseBuilder
{
public:
    PolygonModelBuilder() = default;
    explicit PolygonModelBuilder(std::shared_ptr<BasePolygonModelReader> reader);
    ~PolygonModelBuilder() = default;

    void build() ;
    void buildPolygons() ;
    bool isBuild() const ;

    std::shared_ptr<PolygonModel> get() ;
protected:
    std::shared_ptr<BasePolygonModelReader> _reader;
    std::shared_ptr<PolygonData> _model;
};

#endif //BUILDER_PolygonModel_H
