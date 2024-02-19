#ifndef HISTORYWIDGET_H
#define HISTORYWIDGET_H

#include <QWidget>
#include <QUndoStack>
namespace Ui {
class HistoryWidget;
}

class HistoryWidget : public QWidget
{
    Q_OBJECT
public:
    QUndoStack commandStack;
public:
    explicit HistoryWidget(QWidget *parent = nullptr);
    ~HistoryWidget();

private slots:
    void on_undoView_clicked(const QModelIndex &index);
public slots:
    void undo();
    void redo();
signals:
    void changed();
private:
    Ui::HistoryWidget *ui;

};

#endif // HISTORYWIDGET_H
