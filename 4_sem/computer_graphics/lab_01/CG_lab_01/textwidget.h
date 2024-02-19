#ifndef TEXTWIDGET_H
#define TEXTWIDGET_H

#include <QWidget>

namespace Ui {
class textWidget;
}

class textWidget : public QWidget
{
    Q_OBJECT

public:
    explicit textWidget(QWidget *parent = nullptr);
    ~textWidget();

private:
    Ui::textWidget *ui;
};

#endif // TEXTWIDGET_H
