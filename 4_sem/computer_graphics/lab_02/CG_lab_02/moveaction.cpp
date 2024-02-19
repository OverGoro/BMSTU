#include "moveaction.h"

MoveAction::MoveAction(PainterWidget *pw, double dx, double dy)
{
    this->painterWidget = pw;
    this->dx = dx;
    this->dy = dy;
    setText(QString("Сдвиг"));
}

void MoveAction::undo()
{
    this->painterWidget->setMoveMatrix(-dx, -dy);
    this->painterWidget->moveAll();
}

void MoveAction::redo()
{
    this->painterWidget->setMoveMatrix(dx, dy);
    this->painterWidget->moveAll();
}

