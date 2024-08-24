#ifndef QTDRAWER_H
#define QTDRAWER_H

#include <qgraphicsscene.h>
#include "BaseDrawer.h"
#include "Point.h"

class QtDrawer : public BaseDrawer
{
public:
    QtDrawer() = default;
    explicit QtDrawer(QGraphicsScene *scene)
        : scene(scene)
    {
        initializeZBuffer(scene->width(), scene->height());
    };
    QtDrawer(const QtDrawer &drawer)
        : scene(drawer.scene){};

    void drawLine(double x_1, double y_1, double x_2, double y_2) override;
    void drawPoint(double x, double y) override;
    void clearPoint(double x, double y) override;
    void clear() override;

    void initializeZBuffer(int width, int height) override;
    void clearZBuffer() override;
    void setTriangleZBuffer(const Point &p1, const Point &p2, const Point &p3) override;
    void drawLineWithZBuffer(const Point &start, const Point &end) override;
    void fillLineZbuffer(const Point &start, const Point &end) override;
private:
    bool isInBounds(int x, int y) override;
    std::vector<std::vector<double>> z_buffer;
    QGraphicsScene *scene;
};

#endif // QTDRAWER_H
