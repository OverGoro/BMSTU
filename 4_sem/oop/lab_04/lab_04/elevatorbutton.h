#ifndef ELEVATORBUTTON_H
#define ELEVATORBUTTON_H

#include <QPushButton>
#include <QObject>
enum ButtonState
{
    UNACTIVE,
    ACTIVE
};

class ElevatorButton : public QPushButton
{
    Q_OBJECT;
public:
    ElevatorButton (QWidget *parrent = nullptr);
    ~ElevatorButton() = default;

    void setFloor(const ssize_t &floor);
public slots:
    void unpressSlot();
private slots:
    void pressSlot();
signals:
    void pressSignal(const ssize_t &floor);
    void unpressSignal();
protected:
    ButtonState _state;
    ssize_t _floor;
};

#endif // ELEVATORBUTTON_H
