#ifndef QTFACTORY_H
#define QTFACTORY_H


#include "AbstractDrawerFactory.h"
#include "QTDrawer.h"


class QtFactory : public AbstractDrawerFactory
{
public:
    explicit QtFactory(QGraphicsScene *scene);

    std::unique_ptr<BaseDrawer> createDrawer() override;

private:
    QGraphicsScene *_scene;
};

#endif // QTFACTORY_H
