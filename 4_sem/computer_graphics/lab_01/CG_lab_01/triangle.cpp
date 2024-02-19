#include "triangle.h"
#include "geometricoperations.h"
void Triangle::checkPoints()
{
    this->isCorrect = false;
    QVector2D s1(points[0] - points[1]), s2(points[1] - points[2]), s3(points[2] - points[0]);
    s1.normalize();
    s2.normalize();
    s3.normalize();
    if (points[0] != points[1] && points[1] != points[2] && points[2] != points[0] &&
        s1 != s2 && s2 != s3 && s3 != s1)
        this->isCorrect = true;
}

Triangle::Triangle()
{

}

Triangle::Triangle(QPointF p1, QPointF p2, QPointF p3, QString p1_t, QString p2_t, QString p3_t)
{
    this->points[0] = p1;
    this->points[1] = p2;
    this->points[2] = p3;
    this->pointsText[0] = p1_t;
    this->pointsText[1] = p2_t;
    this->pointsText[2] = p3_t;
    checkPoints();
}

void Triangle::setPoints(QPointF p1, QPointF p2, QPointF p3)
{
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
    checkPoints();
}

int Triangle::getBisectorEquation(qsizetype index, QVector3D &equation)
{
    checkPoints();
    int rc = OK;

    // Проверка значения индекса точки
    if (index < 0 || index > 2)
        rc = ERR_INDEX_OUT_OF_RANGE;

    // Проверка корректности треугольника
    if (!rc && !isCorrect)
        rc = ERR_INCORRECT_TRIANGLE;

    // Получение уравнения
    if (!rc)
    {
        rc = getAngleBisectorEquation(points[index],
                                      points[(index + 1) % 3],
                                      points[(index + 2) % 3],
                                      equation);
    }
    if (!rc) equation.normalize();
    return rc;
}

int Triangle::getBisectorPoint(qsizetype index, QPointF &point)
{
    checkPoints();
    // Получение уравнения стороны треугольника
    int rc = OK;
    if (!isCorrect)
        rc = ERR_INCORRECT_TRIANGLE;
    if (!rc)
    {
        rc = getAngleBisectorPoint( points[index],
                    points[(index + 1) % 3],
                    points[(index + 2) % 3],
                    point);
    }
    return rc;
}

int Triangle::getHeightEquation(qsizetype index, QVector3D &equation)
{
    checkPoints();
    QVector3D side_equation; // Уравнение противоположной стороны треугольника
    int rc = OK;

    // Проверка значения индекса точки
    if (index < 0 || index > 2)
        rc = ERR_INDEX_OUT_OF_RANGE;

    // Проверка корректности треугольника
    if (!rc && !isCorrect)
        rc = ERR_INCORRECT_TRIANGLE;

    // Получение уравнения стороны
    if (!rc)
    {
        rc = getLineEquation(points[(index + 1) % 3],
                             points[(index + 2) % 3],
                             side_equation);
    }
    if (!rc) side_equation.normalize();
    // Получение уравнения высоты треугольника
    if (!rc)
        rc = getPerpEquation(side_equation, equation);
    // Проведение уравнения прямой через вершину треугольника
    if (!rc)
        rc = setLineEquationThroughPoint(equation, points[index]);
    if (!rc) equation.normalize();
    return rc;
}

int Triangle::getHeightPoint(qsizetype index, QPointF &point)
{
    checkPoints();
    QVector3D height_equation;  // Уравнение высоты
    QVector3D side_equation;    // Уравнение стороны треугольника

    // Получение уравнения высоты
    int rc = getHeightEquation(index, height_equation);

    // Получение уравнения стороны треугольника
    if (!rc)
    {
        rc = getLineEquation(points[(index + 1) % 3],
                             points[(index + 2) % 3],
                             side_equation);
    }
    // Получение точки пересечения
    if (!rc)
        rc = getIntersectionPoint(height_equation, side_equation, point);
    return rc;
}

int Triangle::getMaxBHAngle(double &angle, QPointF &p_top, QPointF &p_bis, QPointF &p_height)
{
    checkPoints();
    double curAngle; // текущий угол между высотой и биссектрисой
    QPointF curPoint, curBisecPoint, curHeightPoint; // Текущие точки результата
    QVector3D curBisecEquation, curHeightEquation;   // Текущие уравнения высоты и биссектрисы

    bool resSet = false;

    int rc = OK;

    // Проверка корректности треугольника
    if (!isCorrect)
        rc = ERR_INCORRECT_TRIANGLE;

    for (size_t i = 0; !rc && i < 3; i++)
    {
        // Получение уравнения биссектрисы
        rc = getBisectorEquation(i, curBisecEquation);
        // Получение уравнения высоты
        if (!rc) rc = getHeightEquation(i, curHeightEquation);
        // Получение угла между высотой и биссектрисой
        if (!rc) rc = getAngleBetweenLines(curBisecEquation, curHeightEquation, curAngle);
        // Получение точки биссектрисы
        if (!rc) rc = getBisectorPoint(i, curBisecPoint);
        // Получение точки биссектрисы
        if (!rc) rc = getHeightPoint(i, curHeightPoint);
        // Установка текущей вершины для результата
        if (!rc) curPoint = points[i];
        if (!rc && (!resSet || curAngle > angle))
        {
            resSet = true;
            angle = curAngle;
            p_top = curPoint;
            p_bis = curBisecPoint;
            p_height = curHeightPoint;
        }
    }
    return rc;
}

int Triangle::getMaxBHAngle(double &angle)
{
    checkPoints();
    double curAngle;
    QPointF curPoint, curBisecPoint, curHeightPoint;
    QVector3D curBisecEquation, curHeightEquation;

    bool resSet = false;

    int rc = OK;

    // Проверка корректности треугольника
    if (!isCorrect)
        rc = ERR_INCORRECT_TRIANGLE;

    for (size_t i = 1; !rc && i < 3; i++)
    {
        // Получение уравнения биссектрисы
        rc = getBisectorEquation(i, curBisecEquation);
        // Получение уравнения высоты
        if (!rc) rc = getHeightEquation(i, curHeightEquation);
        // Получение величины угла между высотой и биссектрисой
        if (!rc) rc = getAngleBetweenLines(curBisecEquation, curHeightEquation, curAngle);
        // Получение точки биссектрисы
        if (!rc) rc = getBisectorPoint(i, curBisecPoint);
        // Получение точки высоты
        if (!rc) rc = getHeightPoint(i, curHeightPoint);
        // Установка текущей вершины для результата
        if (!rc) curPoint = points[i];
        if (!rc && (!resSet || curAngle > angle))
        {
            resSet = true;
            angle = curAngle;
        }
    }
    return rc;
}


QVector<Triangle> formTriangleVector(QVector<QPointF> points)
{
    QVector<Triangle> res = QVector<Triangle>();
    for (qsizetype i = 0; i < points.size(); i++)
    {
        for (qsizetype j = i + 1; j < points.size(); j++)
        {
            for (qsizetype k = j + 1; k < points.size(); k++)
            {
                // Можно ли пострить на точках треугольник
                QVector2D s1(points[i] - points[j]), s2(points[j] - points[k]), s3(points[k] - points[i]);
                s1.normalize();
                s2.normalize();
                s3.normalize();
                if (points[i] != points[j] && points[j] != points[k] && points[i] != points[k] &&
                    s1 != s2 && s2 != s3 && s3 != s1)
                {
                    res.push_back(Triangle(points[i],
                                            points[j],
                                            points[k],
                                            QString::number(i),
                                            QString::number(j),
                                            QString::number(k)));
                }
            }
        }
    }

    return res;
}
