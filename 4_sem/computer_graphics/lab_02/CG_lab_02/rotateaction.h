#ifndef ROTATEACTION_H
#define ROTATEACTION_H


#include "painterwidget.h"
#include <QUndoCommand>

class RotateAction : public QUndoCommand
{
private:
    PainterWidget *painterWidget;
    double cx, cy;
    double angle;
public:
    RotateAction(PainterWidget *pw, double cx, double cy, double angle);
    void undo() override;
    void redo() override;
};

#endif // ROTATEACTION_H
