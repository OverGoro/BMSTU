#ifndef MOVEACTION_H
#define MOVEACTION_H

#include "painterwidget.h"
#include <QUndoCommand>

class MoveAction : public QUndoCommand
{
private:
    PainterWidget *painterWidget;
    double dx, dy;
public:
    MoveAction(PainterWidget *pw, double dx, double dy);
    void undo() override;
    void redo() override;
};

#endif // MOVEACTION_H
