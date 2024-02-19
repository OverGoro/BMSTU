#include "rotateaction.h"

RotateAction::RotateAction(PainterWidget *pw, double cx, double cy, double angle)
{
    this->painterWidget = pw;
    this->cx = cx;
    this->cy = cy;
    this->angle = angle;
    setText(QString("Пворот: %1°").arg(angle));
}

void RotateAction::redo()
{
    this->painterWidget->setRotationMatrix(cx, cy, angle);
    this->painterWidget->rotateAll();
}

void RotateAction::undo()
{
    this->painterWidget->setRotationMatrix(cx, cy, -angle);
    this->painterWidget->rotateAll();
}
