#ifndef PAINTERTEXT_H
#define PAINTERTEXT_H

#include <QPainter>
#include <QString>
#include <QPointF>
#include <QVector2D>
#include <QVector3D>

class PainterText
{
private:
    QFont font;
    QString text;
    QRectF box;
public:
    PainterText();
    PainterText(const QPointF &position, const QString &text, const QFont &font);

    const QString &getText() const;
    void setText(const QString &newText);

    const QRectF &getBox() const;
    void setBox(const QRectF &newBox);

    qreal getTop();
    qreal getBottom();
    qreal getLeft();
    qreal getRight();

    bool intersects(const PainterText &pt);
    QRectF intersection(const PainterText &pt);
    void draw(QPainter *painter);
    void move(qreal dx, qreal dy);
    void moveTo(qreal x, qreal y);
};

#endif // PAINTERTEXT_H
