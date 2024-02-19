#include "paintertext.h"

const QString &PainterText::getText() const
{
    return text;
}

void PainterText::setText(const QString &newText)
{
    text = newText;
}

bool PainterText::intersects(const PainterText &pt)
{
    return box.intersects(pt.getBox());
}

QRectF PainterText::intersection(const PainterText &pt)
{
    return box.intersected(pt.getBox());
}

void PainterText::draw(QPainter *painter)
{
    painter->setFont(font);
    painter->drawText(box.left(), box.top(), text);
}

void PainterText::move(qreal dx, qreal dy)
{
    this->box.moveBottomLeft(QPoint(dx,dy));
}

void PainterText::moveTo(qreal x, qreal y)
{
    this->box.moveTo(x,y);
}

const QRectF &PainterText::getBox() const
{
    return box;
}

void PainterText::setBox(const QRectF &newBox)
{
    box = newBox;
}

qreal PainterText::getTop()
{
    return box.top();
}

qreal PainterText::getBottom()
{
    return box.bottom();
}

qreal PainterText::getLeft()
{
    return box.left();
}

qreal PainterText::getRight()
{
    return box.right();
}

PainterText::PainterText()
{
    text = "";
    box = QRectF(0,0,0,0);
}

PainterText::PainterText(const QPointF &position, const QString &text, const QFont &font)
{
    this->text = text;
    this->font = font;
    QFontMetrics qfm(font);
    this->box = qfm.boundingRect(text);
    this->box.moveTo(position);
}
