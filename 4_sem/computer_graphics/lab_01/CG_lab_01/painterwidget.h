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
private:
    QPainter *painter;        // Объект отрисовщика

    QFont font; // Шрифт подписей

    // Трансформациии:
    bool saveScale;         // Сохранять масштаб 1 к 1
    QVector2D scaleMatrix;  // Матрица масштабирования
    QVector2D moveMatrix;   // Матрица переноса
    QVector2D marginVector; // Отступы от границ поля рисования (слева-справа, сверху-снизу)

    // Объекты:
    QVector<QVector<QPointF>> closedLines;          // Замкнутые ломаные
    QVector<QPair<QPointF, QPointF>> lines;         // Ломаные
    QVector<QPair<QPointF, QPointF>> pointLines;    // Ломаные штрихами
    QVector<QPointF> points;                        // Точки
    QVector<PainterText> texts;                     // Подписи к точкам

    QVector<QVector<QPointF>> transformedClosedLines;  // Трансформированные замкнутые ломаные
    QVector<QPair<QPointF, QPointF>> transformedLines; // Трансформированные ломаные
    QVector<QPair<QPointF, QPointF>> transformedPointLines; // Трансформированные ломаные штрихами
    QVector<QPointF> transformedPoints;                // Трансформированные точки
    QVector<PainterText> transformedTexts;             // Трансформированные подписи к точкам
public:
    PainterWidget(QWidget *parrent = 0);
    ~PainterWidget();
private:
    void paintEvent(QPaintEvent *event);
    QPointF transformPoint(const QPointF &p);
    void transformTexts();
    void transformAll();
    void transformAllToDecart();
public:
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
     * @brief setTransformationsByPoints Задает матрицу масштабирования
     * и переноса таким образом, чтобы указанный список точек отрисовался
     * в оптимальном масштабе
     * @param points Точки
     */
    void setTransformationsByPoints(const QVector<QPointF> &points);

    /**
     * @brief setTransformationsPointsOnly Задает матрицу масштабирования
     * и переноса таким образом, чтобы все объекты для отрисовки отрисовались
     * в оптимальном масштабе
     */
    void setTransformations();

    /**
     * @brief setTransformationsUI Здает матрицу масштабирования таким образом,
     * чтобы текст отрисовался в оптимальном масштабе
     */
    void setTransformationsUI();

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
    bool getSaveScale() const;
    void setSaveScale(bool newSaveScale);
};

#endif // PAINTERWIDGET_H
