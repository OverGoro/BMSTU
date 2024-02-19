#include "painterwidget.h"
bool PainterWidget::getSaveScale() const
{
    return this->saveScale;
}

void PainterWidget::setSaveScale(bool newSaveScale)
{
    this->saveScale = newSaveScale;
}

PainterWidget::PainterWidget(QWidget *parrent)
    : QWidget(parrent)
{
    this->painter = NULL;
    this->scaleMatrix = {1, 1};
    this->moveMatrix = {0, 0};
    this->marginVector = {12,12};
    this->font = QFont("Arial",11);
    this->saveScale = true;
}

PainterWidget::~PainterWidget()
{
}

void PainterWidget::paintEvent(QPaintEvent *event)
{
    QPen closedLinesPen;
    QPen linesPen;
    QPen pointLinesPen;
    QPen pointsPen;

    closedLinesPen.setColor(Qt::black);
    linesPen.setColor(Qt::blue);
    pointLinesPen.setColor(Qt::blue);
    pointLinesPen.setStyle(Qt::DotLine);
    pointsPen.setWidth(5);
    pointsPen.setColor(Qt::red);

    transformedPoints = points;
    transformedLines = lines;
    transformedPointLines = pointLines;
    transformedTexts = texts;
    transformedClosedLines = closedLines;

    setTransformations();
    transformAll();
    setTransformationsUI();
    transformAll();
    transformAllToDecart();

    painter = new QPainter(this);
    painter->setPen(closedLinesPen);
    drawClosedLines();
    painter->setPen(linesPen);
    drawLines();
    painter->setPen(pointLinesPen);
    drawPointLines();
    painter->setPen(pointsPen);
    drawPoints();
    drawTexts();
    painter->end();
}

QPointF PainterWidget::transformPoint(const QPointF &p)
{
    qreal x = p.x() + moveMatrix.x();
    qreal y = p.y() + moveMatrix.y();
    x = x * scaleMatrix.x() + marginVector.x();
    y = height() - y * scaleMatrix.y() - marginVector.y();

    return QPointF(x, y);

}

void PainterWidget::transformTexts()
{
    for (auto &t : transformedTexts)
    {
        QPointF p = QPointF(t.getLeft(), t.getTop());
        p = transformPoint(p);
        t.moveTo(p.x(), p.y());
    }
//    bool hasIntersected = true; // есть пересечения надписей
//    while (hasIntersected)
//    {
//        hasIntersected = false;
//        for (qsizetype i = 0; i < transformedTexts.size(); i++)
//        {
//            for (qsizetype j = i + 1; j < transformedTexts.size(); j++)
//            {
//                if (transformedTexts[i].intersects(transformedTexts[j]) &&
//                        transformedTexts[i].getText() != transformedTexts[j].getText())
//                {
//                    hasIntersected = true;
//                    QRectF intersectedBox = transformedTexts[i].intersection(transformedTexts[j]);
//                    if (transformedTexts[i].getLeft() < transformedTexts[j].getLeft())
//                        transformedTexts[j].move(intersectedBox.width(), intersectedBox.height());
//                    else
//                        transformedTexts[i].move(intersectedBox.width(), intersectedBox.height());
//                }
//            }
//        }
//    }
}

void PainterWidget::transformAll()
{
    transformTexts();

    for (auto &p : transformedPoints)
        p = transformPoint(p);

    for (auto &cl : transformedClosedLines)
    {
        for (auto &p : cl)
        {
            p = transformPoint(p);
        }
    }

    for (auto &l : transformedLines)
    {
        l.first = transformPoint(l.first);
        l.second = transformPoint(l.second);
    }
    for (auto &pl : transformedPointLines)
    {
        pl.first = transformPoint(pl.first);
        pl.second = transformPoint(pl.second);
    }
}

void PainterWidget::transformAllToDecart()
{
    for (auto &t : transformedTexts)
    {
        t.moveTo(t.getLeft(), height() - t.getTop());
    }
    for (auto &p : transformedPoints)
        p.setY(height() - p.y());

    for (auto &cl : transformedClosedLines)
    {
        for (auto &p : cl)
        {
            p.setY(height() - p.y());
        }
    }

    for (auto &l : transformedLines)
    {
        l.first.setY(height() - l.first.y());
        l.second.setY(height() - l.second.y());
    }
    for (auto &pl : transformedPointLines)
    {
        pl.first.setY(height() - pl.first.y());
        pl.second.setY(height() - pl.second.y());
    }
}

void PainterWidget::addClosedLines(const QVector<QPointF> &points)
{
    this->closedLines.append(points);
    transformedClosedLines = closedLines;
}

void PainterWidget::addLines(const QVector<QPair<QPointF, QPointF> > &lines)
{
    this->lines.append(lines);
    transformedLines = lines;
}

void PainterWidget::addPointLines(const QVector<QPair<QPointF, QPointF> > &pointLines)
{
    this->pointLines.append(pointLines);
    transformedPointLines = pointLines;
}

void PainterWidget::addPoints(const QVector<QPointF> &points)
{
    this->points.append(points);
    this->addPointsText(points);
    transformedPoints = points;
}

void PainterWidget::addText(const QPointF &point, const QString &text)
{
    texts.push_back(PainterText(point, text, font));
    transformedTexts = texts;
}

void PainterWidget::addPointsText(const QVector<QPointF> &points)
{
    for (auto &p : points)
    {
        QString p_text = QString("(%1, %2)").arg(p.x()).arg(p.y());
        addText(p, p_text);
    }
}

void PainterWidget::clear()
{
    this->lines.clear();
    this->pointLines.clear();
    this->closedLines.clear();
    this->points.clear();
    this->texts.clear();

    this->transformedLines.clear();
    this->transformedPointLines.clear();
    this->transformedClosedLines.clear();
    this->transformedPoints.clear();
    this->transformedTexts.clear();

    this->moveMatrix.setX(0);
    this->moveMatrix.setY(0);
    this->scaleMatrix.setX(0);
    this->scaleMatrix.setY(0);
}

void PainterWidget::setTransformationsByPoints(const QVector<QPointF> &points)
{
    if (points.size() > 0)
    {
        float minX = points[0].x(), maxX = points[0].x();
        float minY = points[0].y(), maxY = points[0].y();
        for (QPointF p : points)
        {
            minX = qMin(p.x(), minX);
            minY = qMin(p.y(), minY);
            maxX = qMax(p.x(), maxX);
            maxY = qMax(p.y(), maxY);
        }
        float dX = maxX - minX;
        float dY = maxY - minY;
        float scaleX = 1, scaleY = 1;

        if (!qFuzzyIsNull(dX))
            scaleX = (this->width() - 2 * marginVector.x()) / dX;
        if (!qFuzzyIsNull(dX))
            scaleY = (this->height() - 2 * marginVector.y()) / dY;

        if (this->saveScale)
        {
            float minScale = qMin(scaleX, scaleY);
            scaleMatrix.setX(minScale);
            scaleMatrix.setY(minScale);
        }
        else
        {
            scaleMatrix.setX(scaleX);
            scaleMatrix.setY(scaleY);
        }

        moveMatrix.setX(-minX);
        moveMatrix.setY(-minY);
    }
}

void PainterWidget::setTransformations()
{
    QVector<QPointF> allPoints;
    for (auto p : points)
        allPoints.push_back(p);
    for (auto l : lines)
    {
        allPoints.push_back(l.first);
        allPoints.push_back(l.second);
    }
    for (auto cl : closedLines)
    {
        for (auto p : cl)
        {
            allPoints.append(p);
        }
    }
    for (auto pl : pointLines)
    {
        allPoints.push_back(pl.first);
        allPoints.push_back(pl.second);
    }

    setTransformationsByPoints(allPoints);
}

void PainterWidget::setTransformationsUI()
{
    QVector<QPointF> allPoints;
    for (auto &p : transformedPoints)
        allPoints.push_back(p);
    for (auto &l : transformedLines)
    {
        allPoints.push_back(l.first);
        allPoints.push_back(l.second);
    }
    for (auto &pl : transformedPointLines)
    {
        allPoints.push_back(pl.first);
        allPoints.push_back(pl.second);
    }
    for (auto &cl : transformedClosedLines)
    {
        for (auto &p : cl)
        {
            allPoints.append(p);
        }
    }
    for (auto &t : transformedTexts)
    {
        allPoints.push_back(QPointF(t.getLeft(), t.getTop()));
        allPoints.push_back(QPointF(t.getRight(), t.getBottom()));
    }

    setTransformationsByPoints(allPoints);
}

void PainterWidget::drawClosedLines()
{
    for (auto &cl : transformedClosedLines)
    {
        if (cl.size() > 1)
        {
            qsizetype i = 0;
            do
            {
                this->painter->drawLine(cl[i], cl[(i + 1) % cl.size()]);
                i++;
            } while (i < cl.size());
        }
    }
}

void PainterWidget::drawLines()
{
    for (auto &l : transformedLines)
    {
        painter->drawLine(l.first, l.second);
    }
}

void PainterWidget::drawPointLines()
{
    for (auto &pl : transformedPointLines)
    {
        painter->drawLine(pl.first, pl.second);
    }
}

void PainterWidget::drawPoints()
{
    for (auto &p : transformedPoints)
    {
        painter->drawPoint(p);
    }
}

void PainterWidget::drawTexts()
{
    for (auto &t : transformedTexts)
    {
        t.draw(this->painter);
    }
}



