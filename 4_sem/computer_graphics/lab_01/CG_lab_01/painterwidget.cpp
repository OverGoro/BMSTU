#include "painterwidget.h"
bool PainterWidget::getSaveScale() const
{
    return this->saveScale;
}

void PainterWidget::setSaveScale(bool newSaveScale)
{
    this->saveScale = newSaveScale;
}

int PainterWidget::getWidth()
{
    return width();
}

int PainterWidget::getHeight()
{
    return height();
}

PainterWidget::PainterWidget(QWidget *parrent)
    : QWidget(parrent)
{
    this->painter = NULL;
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

    setTransformations();

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

void PainterWidget::addClosedLines(const QVector<QPointF> &points)
{
    this->closedLines.append(points);
}

void PainterWidget::addLines(const QVector<QPair<QPointF, QPointF> > &lines)
{
    this->lines.append(lines);
}

void PainterWidget::addPointLines(const QVector<QPair<QPointF, QPointF> > &pointLines)
{
    this->pointLines.append(pointLines);
}

void PainterWidget::addPoints(const QVector<QPointF> &points)
{
    this->points.append(points);
    this->addPointsText(points);
}

void PainterWidget::addText(const QPointF &point, const QString &text)
{
    texts.push_back(PainterText(point, text, font));
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
        this->zeroX = minX;
        this->zeroY = minY;

        this->countWidth = maxX - minX;
        this->countHeight = maxY - minY;
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

QPointF PainterWidget::getScreenPoint(QPointF count_point)
{
    double x = 0, y = 0;
    if (saveScale)
    {

        double screen_width = qMin(width() - 2 * marginVector.x(), (height() - 2 * marginVector.y()) * countWidth / countHeight);
        double screen_height = qMin(height() - 2 * marginVector.y(), (width() - 2 * marginVector.x()) * countHeight / countWidth);
        x = (count_point.x() - zeroX) / countWidth * screen_width + marginVector.x();
        y = screen_height - (count_point.y() - zeroY) / countHeight * screen_height + marginVector.y();
    }
    else
    {
        x = (count_point.x() - zeroX) / countWidth * (width() - marginVector.x() * 2) + marginVector.x();
        y = (height() - marginVector.y() * 2 -
             (count_point.y() - zeroY) / countHeight * (height() - marginVector.y() * 2)) + marginVector.y();
    }
    return QPointF(x,y);
}


void PainterWidget::drawClosedLines()
{
    for (auto &cl : closedLines)
    {
        if (cl.size() > 1)
        {
            qsizetype i = 0;
            do
            {
                this->painter->drawLine(getScreenPoint(cl[i]), getScreenPoint(cl[(i + 1) % cl.size()]));
                i++;
            } while (i < cl.size());
        }
    }
}

void PainterWidget::drawLines()
{
    for (auto &l : lines)
    {
        painter->drawLine(getScreenPoint(l.first), getScreenPoint(l.second));
    }
}

void PainterWidget::drawPointLines()
{
    for (auto &pl : pointLines)
    {
        painter->drawLine(getScreenPoint(pl.first), getScreenPoint(pl.second));
    }
}

void PainterWidget::drawPoints()
{
    for (auto &p : points)
    {
        painter->drawPoint(getScreenPoint(p));
    }
}

void PainterWidget::drawTexts()
{
    for (auto &t : texts)
    {
        QPointF p = getScreenPoint(t.getBox().topLeft());
        PainterText pt = PainterText(p, t.getText(), font);

        if (pt.getRight() > width() - marginVector.x())
            pt.move(-pt.getBox().width(), 0);
        if (pt.getBottom() > height() - marginVector.y())
            pt.move(0, -pt.getBox().height());
        pt.draw(this->painter);
    }
}
