#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QPointF>
#include <QVector>
#include <QVector3D>
#include <QMatrix3x3>

class PainterWidget : public QWidget
{
    Q_OBJECT
private:
    QPainter *painter;        // Объект отрисовщика

    double countWidth, countHeight; // Ширина и высота поля в реальной системе

    // Объекты:
    QVector<QVector<QPointF>> closedLines;  // Замкнутые ломаные
    QVector<QPair<QPointF, QPointF>> lines; // Отрезки
    QVector<QVector<QPointF>> polylines;    // Ломаные линии

    // Матрицы преобразований
    QMatrix3x3 moveMatrix;      // Матрица переноса

    QMatrix3x3 scaleMatrix;     // Матрица масштабирования
    QPointF scaleCenter;        // Центр масштабирования

    QMatrix3x3 rotationMatrix;  // Матрица поворота
    QPointF rotationCenter;     // Центр поворота

public:
    PainterWidget(QWidget *parrent = 0);
    PainterWidget(const PainterWidget &pw);
    void load(const PainterWidget &pw);
private:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void movePoint(QPointF &point);
    void scalePoint(QPointF &point);
    void rotatePoint(QPointF &point);

    /**
     * @brief applyToAll Применияет функцию ко всем точкам всех объектов
     * @param f Функция
     */
    void applyToAll(void (PainterWidget::*f)(QPointF &));

public:
    /**
     * @brief getCountSize Преобразует вектор на экране в пикселях в вектор на расетной плоскости
     * @param screen_vector Вектор на экране
     * @return Вектор в расчетной плоскости
     */
    QVector2D getCountVector(const QVector2D &screen_vector);

    /**
     * @brief getCountSize Преобразует точку на экране в пикселях в точку на расетной плоскости
     * @param screen_vector Точка на экране
     * @return Точка в расчетной плоскости
     */
    QPointF getCountPoint(const QPointF &screen_point);

    /**
     * @brief getCountSize Преобразует точку на расетной плоскости в точку на экране в пикселях
     * @param screen_vector Точка на плоскости
     * @return Точка на экране
     */
    QPointF getScreenPoint(const QPointF &point, int screen_min_size);


public slots:
    // Настройка параметров матриц преобразований
    /**
     * @brief setMoveMatrix Задать матрицу сдвига
     * @param dx Смещение по Х
     * @param dy Смещение по У
     */
    void setMoveMatrix(double dx, double dy);

    /**
     * @brief setMoveMatrixPx Задать матрицу сдвига
     * @param dx Смещениие по оси Х в пикселях
     * @param dy Смещениие по оси Y в пикселях
     */
    void setMoveMatrixPx(double dx, double dy);

    /**
     * @brief setScaleMatrix Задать матрицу масштабирования
     * @param cx Центр масштабирование по оси Х
     * @param cy Центр масштабирование по оси Х
     * @param kx Масштабирование по оси Х
     * @param ky Масштабирование по оси У
     */
    void setScaleMatrix(double cx, double cy, double kx, double ky);

    /**
     * @brief setScaleMatrix Задать матрицу масштабирования
     * @param cx Центр масштабирование по оси Х в пикселях
     * @param cy Центр масштабирование по оси Х в пикселях
     * @param kx Масштабирование по оси Х
     * @param ky Масштабирование по оси У
     */
    void setScaleMatrixPx(double cx, double cy, double kx, double ky);

    /**
     * @brief setRotationMatrixPx Задать матрицу поворота
     * @param cx Координата Х центра поворота
     * @param cy Координата Y центра поворота
     * @param angle Угол поворота
     */
    void setRotationMatrix(double cx, double cy, double angle);

    /**
     * @brief setRotationMatrixPx Задать матрицу поворота
     * @param cx Координата Х в пикселях центра поворота
     * @param cy Координата Y в пикселях центра поворота
     * @param angle Угол поворота
     */
    void setRotationMatrixPx(double cx, double cy, double angle);

    // Трансформация объектов
    void moveAll();
    void scaleAll();
    void rotateAll();

public:
    // Добавление объектов
    /**
     * @brief drawClosedLines Доабавляет замкнутую ломаную для отрисовки.
     * Последняя точка соединится с первой
     * @param points Точки
     */
    void addClosedLines(const QVector<QPointF> &points);

    /**
     * @brief addLines Добавляет незамкнутые отрезки
     * @param lines Отрезки
     */
    void addLines(const QVector<QPair<QPointF, QPointF>> &lines);

    /**
     * @brief addPolyline Добавляет ломаную линию
     * @param points Точки ломаной
     */
    void addPolyline(const QVector<QPointF> &points);

    /**
     * @brief addByFunc Добавление отрезков по функции
     * @param f Функция
     * @param start_x Начало интервала
     * @param end_x Конец интервала
     * @param points_num Число точек
     */
    void addByFunc(double f(double x), double start_x, double end_x, size_t points_num);

    /**
     * @brief clear Очищает все объекты для отрисовки
     */
    void clear();


    // Отрисовка
    /**
     * @brief drawClosedLines Отрисовка замкнутых линий
     */
    void drawClosedLines();

    /**
     * @brief drawLines Отрисовка незамкнутых линий
     */
    void drawLines();

    /**
     * @brief drawPolylines Отрисовка ломаных
     */
    void drawPolylines();

    double getCountWidth() const;
    void setCountWidth(double newCountWidth);
    double getCountHeight() const;
    void setCountHeight(double newCountHeight);
};

#endif // PAINTERWIDGET_H
