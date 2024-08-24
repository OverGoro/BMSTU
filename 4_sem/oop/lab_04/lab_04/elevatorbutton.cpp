#include "elevatorbutton.h"

ElevatorButton::ElevatorButton(QWidget *parrent)
    :QPushButton(parrent)
{
    connect(this, &ElevatorButton::clicked, this, &ElevatorButton::pressSlot);
    connect(this, &ElevatorButton::unpressSignal, this, &ElevatorButton::unpressSlot);
    _state = UNACTIVE;
    _floor = 1;
    this->setStyleSheet("background-color: #c0c5ce;"
                        "font: bold 14px;"
                        "padding: 6px;"
                        "border-radius: 10px;"
                        "border: 2px solid #555;"
                        "color: black;"
                        "min-width: 80px;"
                        "text-align: center;");
}

void ElevatorButton::setFloor(const ssize_t &floor)
{
    _floor = floor;
}


void ElevatorButton::pressSlot()
{
    if (_state == UNACTIVE)
    {
        this->setStyleSheet("background-color: #65737e;"
                            "font: bold 14px;"
                            "padding: 6px;"
                            "border-radius: 10px;"
                            "border: 2px solid red;"
                            "color: black;"
                            "min-width: 80px;"
                            "text-align: center;");

        this->update();

        _state = ACTIVE;
        this->setDisabled(true);
        emit pressSignal(_floor);
    }
}

void ElevatorButton::unpressSlot()
{
    if (_state == ACTIVE)
    {
        this->setStyleSheet("background-color: #c0c5ce;"
                            "font: bold 14px;"
                            "padding: 6px;"
                            "border-radius: 10px;"
                            "border: 2px solid #555;"
                            "color: black;"
                            "min-width: 80px;"
                            "text-align: center;");
        this->update();

        _state = UNACTIVE;
        this->setDisabled(false);
        emit unpressSignal();
    }
}
