#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <QVector>
#include <QString>
#include <QPointF>
#include "geometricoperations.h"

class Triangle
{
private:
    bool isCorrect; // Можно ли на указанных точках построить треугольник
public:
    QPointF points[3];      // Точки
    QString pointsText[3];  // Имена точек
private:
    /**
     * @brief checkPoints Проверяет, можно ли на указанных точках построить треугольник
     */
    void checkPoints();
public:
    Triangle();
    Triangle(QPointF p1, QPointF p2, QPointF p3, QString p1_t = "1", QString p2_t = "2", QString p3_t = "3");
    void setPoints(QPointF p1, QPointF p2, QPointF p3);

    /**
     * @brief getBisectorEquation Получает уравнение биссектрисы из точки треугольника
     * @param index Индекс точки треугольника
     * @param equation Полученное уравнение
     * @return Код ошибки
     */
    int getBisectorEquation(qsizetype index, QVector3D &equation);

    /**
     * @brief getBisectorPoint Получает точку пересечения биссектрисы из точки
     * и прямой через противоположную сторону треугольника
     * @param index Индекс точки треугольника
     * @param point Полученная точка
     * @return Код ошибки
     */
    int getBisectorPoint(qsizetype index, QPointF &point);

    /**
     * @brief getHeightEquation Получает уравнение высоты из точки треугольника
     * @param index Индекс точки треугольника
     * @param equation Полученное уравнение
     * @return Код ошибки
     */
    int getHeightEquation(qsizetype index, QVector3D &equation);

    /**
     * @brief getHeightPoint Получает точку пересечения высоты из точки
     * и прямой через противоположную сторону треугольника
     * @param index Индекс точки треугольника
     * @param point Полученная точка
     * @return Код ошибки
     */
    int getHeightPoint(qsizetype index, QPointF &point);

    /**
     * @brief getMaxBHAngle Получает значение максимального угла между
     * биссектрисой и высотой из вершины треугольника
     * @param angle Полученный угол
     * @return Код ошибки
     */
    int getMaxBHAngle(double &angle);

    /**
     * @brief getMaxBHAngle Получает максимальный угол между
     * биссектрисой и высотой из вершины треугольника
     * @param angle Значение угла
     * @param p_top Вершина угла
     * @param p_bis Точка пересечения биссектрисы с противоположной стороной
     * @param p_height Точка пересечения высоты с противоположной стороной
     * @return Код ошибки
     */
    int getMaxBHAngle(double &angle, QPointF &p_top, QPointF &p_bis, QPointF &p_height);
};

QVector<Triangle> formTriangleVector(QVector<QPointF> points);

#endif // TRIANGLE_H
