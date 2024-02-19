#include "historywidget.h"
#include "ui_historywidget.h"

HistoryWidget::HistoryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HistoryWidget)
{
    ui->setupUi(this);
    ui->undoView->setStack(&commandStack);
}

HistoryWidget::~HistoryWidget()
{
    delete ui;
}

void HistoryWidget::on_undoView_clicked(const QModelIndex &index)
{
    emit changed();
}

void HistoryWidget::undo()
{
    if (commandStack.canUndo())
        commandStack.undo();
}

void HistoryWidget::redo()
{
    if (commandStack.canRedo())
        commandStack.redo();
}
