#include <QDebug>

#include "elevatorcabin.h"

ElevatorCabin::ElevatorCabin(QObject *parent) : QObject(parent)
{
    _status = STOPPED;
    _targetExist = false;

    QObject::connect(this, &ElevatorCabin::_movingSignal,
                     this, &ElevatorCabin::_moveSlot);

    QObject::connect(&_moveTimer, &QTimer::timeout,
                     this, &ElevatorCabin::_moveSlot);

    QObject::connect(this, &ElevatorCabin::_openDoorsSignal,
                     &_door, &ElevatorDoor::openingSlot);

    QObject::connect(&_door, &ElevatorDoor::closedSignal,
                     this, &ElevatorCabin::_moveSlot);
}

void ElevatorCabin::_moveSlot()
{
    if (_targetExist)
    {
        if (_status == GOT_TARGET || _status == STOPPED)
            _status = MOVING;
        else
            _currentFloor += _direction;

        qDebug() << "Лифт на" << _currentFloor << "этаже";

        if (_currentFloor != _targetFloor)
            _moveTimer.start(MOVING_TIME);

        emit _floorPassedSignal(_currentFloor, _direction);
    }
}

void ElevatorCabin::getTargetSlot(ssize_t &targetFloor, ssize_t &currentFloor)
{
    if (_status == STOPPED)
    {
        _status = GOT_TARGET;
        _targetExist = true;
        saveState(targetFloor, currentFloor);
        emit _movingSignal();
    }
}

void ElevatorCabin::stoppedSlot(bool isLast, ssize_t currentFloor, ssize_t targetFloor)
{
    if (_status == MOVING || _status == STOPPED)
    {
        _status = STOPPED;
        saveState(targetFloor, currentFloor);
        qDebug() << "Лифт остановился на этаже: " << _currentFloor;

        if (isLast)
            _targetExist = false;

        _moveTimer.stop();
        emit _openDoorsSignal();
    }
}

void ElevatorCabin::saveState(const ssize_t &targetFloor, const ssize_t &currentFloor)
{
    _targetFloor = targetFloor;
    _currentFloor = currentFloor;
    _direction = _currentFloor > _targetFloor ? DOWN : UP;
}
