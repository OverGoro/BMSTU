#include "elevatordoor.h"
#include "elevatorcontroller.h"

ElevatorDoor::ElevatorDoor()
{
    _status = CLOSED;

    QObject::connect(&_openingTimer, &QTimer::timeout,
                     this, &ElevatorDoor::openedSlot);
    QObject::connect(&_openedTimer,  &QTimer::timeout,
                     this, &ElevatorDoor::closingSlot);
    QObject::connect(&_closingTimer, &QTimer::timeout,
                     this, &ElevatorDoor::closedSlot);
}

void ElevatorDoor::openingSlot()
{
    if (_status == CLOSED || _status == CLOSING)
    {
        qDebug() << "Двери открываются.";

        if (_status == CLOSED)
        {
            _status = OPENING;
            _openingTimer.start(DOORS_TIME);
        }
        else
        {
            _status = OPENING;
            auto timer = _closingTimer.remainingTime();
            _closingTimer.stop();
            _openingTimer.start(DOORS_TIME - timer);
        }
    }
}

void ElevatorDoor::openedSlot()
{
    if (_status == OPENING)
    {
        _status = OPEN;
        qDebug() << "Двери открыты.";
        _openedTimer.start(DOORS_TIME);
    }
}

void ElevatorDoor::closingSlot()
{
    if (_status == OPEN)
    {
        _status = CLOSING;
        qDebug() << "Двери закрываются.";
        _closingTimer.start(DOORS_TIME);
    }
}

void ElevatorDoor::closedSlot()
{
    if (_status == CLOSING)
    {
        _status = CLOSED;
        qDebug() << "Двери закрыты.";
        emit closedSignal();
    }
}
