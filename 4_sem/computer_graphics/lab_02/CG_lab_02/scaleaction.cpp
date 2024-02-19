#include "scaleaction.h"

ScaleAction::ScaleAction(PainterWidget *pw, double cx, double cy, double kx, double ky)
{
    this->painterWidget = pw;
    this->cx = cx;
    this->cy = cy;
    this->kx = kx;
    this->ky = ky;
    if (kx == 0 || ky == 0)
    {
        this->painterWidgetCopy = new PainterWidget();
        this->painterWidgetCopy->load(*pw);
    }
    setText(QString("Масштабирование: kx = %1, ky = %2").arg(kx).arg(ky));
}

void ScaleAction::redo()
{
    this->painterWidget->setScaleMatrix(cx, cy, kx, ky);
    this->painterWidget->scaleAll();
}

void ScaleAction::undo()
{
    if (kx == 0 || ky == 0)
    {
        this->painterWidget->load(*painterWidgetCopy);
    }
    else
    {
        this->painterWidget->setScaleMatrix(cx, cy, 1 / kx, 1/ ky);
        this->painterWidget->scaleAll();
    }
}
