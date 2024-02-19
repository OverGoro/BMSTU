#ifndef GEOMETRICOPERATIONS_H
#define GEOMETRICOPERATIONS_H

#include "error.h"

#include <QVector3D>
#include <QPointF>



/**
 * @brief getLineEquation Получает уравнение прямой по 2 точкам
 * Ax + By + C = 0
 * equation = (A,B,C)
 * @param p1 Точка 1
 * @param p2 Точка 2
 * @param equation Полученное уравнение
 * @return Код ошибки
 */
int getLineEquation(const QPointF &p1, const QPointF &p2, QVector3D &equation);

/**
 * @brief getIntersectionPoint Получает точку пересечения 2 прямых
 * @param equation_1 Первая прямая
 * @param equation_2 Вторая прямая
 * @param res_point Полученная точка пересечения
 * @return Код ошибки
 */
int getIntersectionPoint(const QVector3D &equation_1, const QVector3D &equation_2, QPointF &res_point);

/**
 * @brief getAngleBisectorEquation Получает угол по 3 точкам
 * @param p_top Вершина угла
 * @param p2 Певая точка
 * @param p3 Вторая точка
 * @param res_equation Полученное уравнение
 * @return Код ошибки
 */
int getAngleBisectorEquation(const QPointF& p_top, const QPointF& p2, const QPointF& p3, QVector3D &res_equation);
int getAngleBisectorPoint(const QPointF& p_top, const QPointF& p2, const QPointF& p3, QPointF &res_point);
/**
 * @brief setLineEquationThroughPoint Меняет уравнение прямой, чтобы она проходила через точку
 * @param equation Уравнение
 * @param point Точка
 * @return Код ошибки
 */
int setLineEquationThroughPoint(QVector3D &equation, const QPointF &point);

/**
 * @brief getPerpEquation Получает уравнение перпендикулярной прямой
 * @param equation Уравнение исходной прямой
 * @param perp_equation Уравнение перпендикулярной прямой
 * @return Код ошибки
 */
int getPerpEquation(const QVector3D &equation, QVector3D &perp_equation);

/**
 * @brief getAngleBetweenLines Получает угол между 2
 * @param line_1 Уравнение первой прямой
 * @param line_2 Уравнение второй пярмой
 * @param angle Угол
 * @return Код ошибки
 */
int getAngleBetweenLines(const QVector3D &line_1, const QVector3D &line_2, qreal &angle);

#endif // GEOMETRICOPERATIONS_H
