#ifndef SCALEACTION_H
#define SCALEACTION_H

#include <QUndoCommand>
#include "painterwidget.h"

class ScaleAction : public QUndoCommand
{
private:
    PainterWidget *painterWidgetCopy;
    PainterWidget *painterWidget;
    double cx, cy;
    double kx, ky;
public:
    ScaleAction(PainterWidget *pw, double cx, double cy, double kx, double ky);
    void undo() override;
    void redo() override;
};

#endif // SCALEACTION_H
