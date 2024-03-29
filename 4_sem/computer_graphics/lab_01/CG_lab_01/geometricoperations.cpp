#include "geometricoperations.h"

#include <QVector3D>
#include <QPointF>

#define EPS 1e-6

int getLineEquation(const QPointF &p1, const QPointF &p2, QVector3D &equation)
{
    if (p1 == p2)
        return ERR_SAME_POINT;
    // уравнение прямой: (ax + by + c = 0)
    qreal a = p1.y() - p2.y();
    qreal b = p2.x() - p1.x();
    qreal c = p1.x() * p2.y() - p2.x() * p1.y();
    equation = QVector3D(a, b, c);
    equation.normalize();
    return OK;
}

int getIntersectionPoint(const QVector3D &equation_1, const QVector3D &equation_2, QPointF &res_point)
{
    qreal determinant = equation_1.x() * equation_2.y() - equation_2.x() * equation_1.y();
    int rc = OK;
    if (qAbs(determinant) < EPS)
        rc = ERR_PARALLEL_LINES;
    if (!rc)
    {
        qreal x = -(equation_2.y() * equation_1.z() - equation_1.y() * equation_2.z()) / determinant;
        qreal y = -(equation_1.x() * equation_2.z() - equation_2.x() * equation_1.z()) / determinant;
        res_point = QPointF(x, y);
    }
    return rc;
}

int getAngleBisectorEquation(const QPointF& p_top, const QPointF& p2, const QPointF& p3, QVector3D &res_equation)
{
    QVector2D side_12, side_13, side_23;    // Уравнения сторон угла
    QPointF bisec_point;                    // Точка пересечения биссектрисы и противоположной стороны

    side_12 = QVector2D(p2.x() - p_top.x(), p2.y() - p_top.y());
    side_13 = QVector2D(p3.x() - p_top.x(), p3.y() - p_top.y());
    side_23 = QVector2D(p3.x() - p2.x(), p3.y() - p2.y());
    int rc = OK;
    if (side_12.length() == 0 || side_13.length() == 0 || side_23.length() == 0)
        rc = ERR_NULL_LINE_EQUATION;
    if (!rc) bisec_point = p2 + (side_23 / (1 + side_13.length() / side_12.length())).toPointF();
    if (!rc) rc = getLineEquation(p_top, bisec_point, res_equation);
    return rc;
}
int getAngleBisectorPoint(const QPointF& p_top, const QPointF& p2, const QPointF& p3, QPointF &res_point)
{
    QVector2D side_12, side_13, side_23;    // Уравнения сторон угла
    QPointF bisec_point;                    // Точка пересечения биссектрисы и противоположной стороны

    side_12 = QVector2D(p2.x() - p_top.x(), p2.y() - p_top.y());
    side_13 = QVector2D(p3.x() - p_top.x(), p3.y() - p_top.y());
    side_23 = QVector2D(p3.x() - p2.x(), p3.y() - p2.y());
    int rc = OK;
    if (side_12.length() == 0 || side_13.length() == 0 || side_23.length() == 0)
        rc = ERR_NULL_LINE_EQUATION;
    if (!rc) bisec_point = p2 + (side_23 / (1 + side_13.length() / side_12.length())).toPointF();
    if (!rc) res_point = bisec_point;
    return rc;
}

int setLineEquationThroughPoint(QVector3D &equation, const QPointF &point)
{
    int rc = OK;
    if (equation.x() == 0 && equation.y() == 0)
        rc = ERR_NULL_LINE_EQUATION;
    if (!rc)
    {
        equation = QVector3D(equation.x(),
                             equation.y(),
                             -(equation.x() * point.x() + equation.y() * point.y()));
    }
    if (!rc) equation.normalize();
    return rc;
}

int getPerpEquation(const QVector3D &equation, QVector3D &perp_equation)
{
    qreal b = equation.y();
    qreal a = equation.x();
    int rc = OK;

    if (a == 0 && b == 0)
        rc = ERR_NULL_LINE_EQUATION;

    if (!rc)
        perp_equation = QVector3D(-b, a, 0.0);
    if (!rc) perp_equation.normalize();
    return rc;
}

int getAngleBetweenLines(const QVector3D &line_1, const QVector3D &line_2, qreal &angle)
{
    int rc = OK;
    if (line_1.x() == 0 && line_1.y() == 0)
        rc = ERR_NULL_LINE_EQUATION;
    else if (line_2.x() == 0 && line_2.y() == 0)
        rc = ERR_NULL_LINE_EQUATION;

    if (!rc)
    {
        // Вычисляем нормали к прямымBBBHHBH
        QVector2D normal1(line_1.x(), line_1.y());
        QVector2D normal2(line_2.x(), line_2.y());

        // Вычисляем косинус угла между нормалями
        qreal dotProduct = QVector2D::dotProduct(normal1, normal2);
        qreal length1 = normal1.length();
        qreal length2 = normal2.length();
        double cosine = dotProduct / (length1 * length2);
        cosine = qMin(1.0, cosine);
        cosine = qMax(-1.0, cosine);

        // Находим угол в радианах
        double radians = qAcos(cosine);

        // Конвертируем радианы в градусы
        angle = qRadiansToDegrees(radians);
        angle = qMin(angle, 180 - angle);
    }
    return rc;
}
