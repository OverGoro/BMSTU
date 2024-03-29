#ifndef PAINTERWIDGET_H
#define PAINTERWIDGET_H

#include "paintertext.h"

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
public:
    QPainter *painter;        // Объект отрисовщика
private:
    QFont font; // Шрифт подписей

    // Трансформациии:
    bool saveScale;                 // Сохранять масштаб 1 к 1
    QVector2D marginVector;         // Отступы от границ поля рисования (слева-справа, сверху-снизу)
    double countWidth, countHeight; // Ширина и высота расчетного поля в отрисовщике
    double zeroX, zeroY;            // Стартовые координаты

    // Объекты:
    QVector<QVector<QPointF>> closedLines;          // Замкнутые ломаные
    QVector<QPair<QPointF, QPointF>> lines;         // Отрезки
    QVector<QPair<QPointF, QPointF>> pointLines;    // Отрезки штрихами
    QVector<QPointF> points;                        // Точки
    QVector<PainterText> texts;                     // Подписи к точкам

public:
    PainterWidget(QWidget *parrent = 0);
    ~PainterWidget();
private:
    void paintEvent(QPaintEvent *event);
public:
    // Добавление и отрисовка объектов
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
     * @brief addLines Добавляет незамкнутые отрезки
     * @param lines Отрезки
     */
    void addPointLines(const QVector<QPair<QPointF, QPointF>> &pointLines);

    /**
     * @brief addPoints Добавляет точки для отрисовки
     * @param points Точки
     */
    void addPoints(const QVector<QPointF> &points);

    /**
     * @brief addText Добавляет текст для отрисовки
     * @param point Координаты текста (minX, minY)
     * @param text Текст
     */
    void addText(const QPointF &point, const QString &text);

    /**
     * @brief addPointsText Добавляет подписи к точкам для отрисовки
     * @param points Точки
     */
    void addPointsText(const QVector<QPointF> &points);

    /**
     * @brief clear Очищает все объекты для отрисовки
     */
    void clear();

    /**
     * @brief drawClosedLines Отрисовка замкнутых линий
     */
    void drawClosedLines();

    /**
     * @brief drawLines Отрисовка незамкнутых линий
     */
    void drawLines();

    /**
     * @brief drawPointLines Отрисовка незамкнутых линий штрихами
     */
    void drawPointLines();

    /**
     * @brief drawPoints Отрисовка точек
     */
    void drawPoints();

    /**
     * @brief drawTexts Отрисовка текстов
     */
    void drawTexts();





    // Установка масштабирования и переноса
    void setTransformationsByPoints(const QVector<QPointF> &points);
    void setTransformations();

    // Получение координат точек
    QPointF getScreenPoint(QPointF count_point);

    bool getSaveScale() const;
    void setSaveScale(bool newSaveScale);
    int getWidth();
    int getHeight();
};

#endif // PAINTERWIDGET_H
